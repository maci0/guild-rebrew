#!/usr/bin/env python3
"""Move scalar global definitions from link_stubs.c into owning .c files.

Each link_stubs global (int/char/float/pointer placeholder) has a known
original .data address in rebrew-data.toml.  This script:
  1. parses link_stubs.c scalar definitions,
  2. reads each global's original initial bytes from the original DLL,
  3. picks the owning translation unit (most references),
  4. replaces that file's `extern TYPE name;` with `TYPE name = <value>;`
     so the global is defined once, in the TU whose .data slot lands near
     its original address (link-order placement).

link_stubs.c is then regenerated (gen_link_stubs.py) and the moved globals
drop out of the unresolved set automatically.

Usage:
  python3 scripts/own_globals.py [--dry-run]
"""
import argparse
import pathlib
import re
import struct
import sys
import tomllib
from collections import defaultdict

sys.path.insert(0, str(pathlib.Path(__file__).parent))
from inline_strings import load_orig  # noqa: E402

DATA_BASE = 0x10027000
DATA_OFF = 0x27000
ROOT = pathlib.Path(__file__).parent.parent

# sizes from the C type (link_stubs uses simplified types)
TSIZE = {
    "int": 4, "unsigned int": 4, "float": 4, "double": 8,
    "short": 2, "unsigned short": 2, "char": 1, "unsigned char": 1,
    "char*": 4, "void*": 4, "int*": 4, "unsigned short*": 4,
    "unsigned char*": 4, "float*": 4,
}


def parse_stubs_globals():
    text = (ROOT / "src" / "link_stubs.c").read_text()
    globals_ = []
    in_globals = False
    for line in text.splitlines():
        s = line.strip()
        if s == "/* Global variable stubs */":
            in_globals = True
            continue
        if in_globals:
            if s.startswith("/*") or not s:
                continue
            if s.startswith("#"):
                continue
            # scalars only: TYPE name;  (skip arrays name[N])
            m = re.match(r"^(\S+(?:\s+\S+)*)\s+(\w+);\s*$", s)
            if m:
                globals_.append((m.group(1).strip(), m.group(2)))
            elif "[" in s:
                continue  # arrays handled separately
            else:
                break
    return globals_


def load_toml():
    with open(ROOT / "src" / "rebrew-data.toml", "rb") as f:
        db = tomllib.load(f)
    out = {}
    for k, v in db.items():
        if v.get("section") == ".data":
            addr = int(k.split(".")[1], 16)
            out[v.get("name", "")] = (addr, v.get("type", "int"), v.get("note", ""))
    return out


def read_value(orig, addr, size):
    off = DATA_OFF + (addr - DATA_BASE)
    # beyond .data raw (0xe000) = BSS -> zero-initialized
    if addr - DATA_BASE >= 0xE000:
        return b"\x00" * size
    if off < 0 or off + size > len(orig):
        return None
    return orig[off:off + size]


def c_value(data, tsize):
    if tsize == 1:
        return str(data[0])
    if tsize == 2:
        return str(struct.unpack_from("<H", data)[0])
    if tsize == 4:
        v = struct.unpack_from("<I", data)[0]
        if v >= 0x10000000:
            return f"0x{v:08x}"
        return str(v)
    if tsize == 8:
        v = struct.unpack_from("<Q", data)[0]
        return f"0x{v:016x}"
    return "0"


def ref_count(name, files):
    counts = defaultdict(int)
    for f in files:
        try:
            t = f.read_text()
        except OSError:
            continue
        counts[str(f)] += len(re.findall(rf"\b{re.escape(name)}\b", t))
    return counts


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    orig = load_orig()
    toml = load_toml()
    stubs = parse_stubs_globals()
    print(f"link_stubs globals: {len(stubs)}", file=sys.stderr)

    files = sorted(pathlib.Path(ROOT / "src" / "server.dll").rglob("*.c"))
    moved = 0
    unmapped = []
    for ctype, name in stubs:
        if name not in toml:
            unmapped.append(name)
            continue
        addr, toml_type, note = toml[name]
        base = ctype.rstrip("*").strip()
        ptr = ctype.endswith("*")
        tsize = TSIZE.get(ctype)
        if tsize is None:
            tsize = 4
        data = read_value(orig, addr, tsize)
        if data is None:
            print(f"  no bytes for {name} at {addr:#x}", file=sys.stderr)
            continue
        counts = ref_count(name, files)
        if not counts:
            # referenced nowhere in src? keep in link_stubs
            continue
        owner = max(counts, key=counts.get)
        op = pathlib.Path(owner)
        lines = op.read_text().splitlines()
        # replace `extern TYPE name;` with a definition
        extern_re = re.compile(
            r"^(\s*)extern\s+([A-Za-z_][\w\s]*\**)\s+" + re.escape(name) + r"\s*;\s*$")
        done = False
        for i, ln in enumerate(lines):
            m = extern_re.match(ln)
            if m:
                decl_type = m.group(2).strip()
                val = c_value(data, tsize)
                lines[i] = f"{m.group(1)}{decl_type} {name} = {val};"
                done = True
                break
        if not done:
            # no extern line in owner — append definition at end
            val = c_value(data, tsize)
            lines.append(f"{ctype} {name} = {val};")
        if not args.dry_run:
            op.write_text("\n".join(lines) + "\n")
        moved += 1
        print(f"  {name:30} {ctype:12} -> {op.relative_to(ROOT)}  = {c_value(data, tsize)}", file=sys.stderr)

    print(f"moved: {moved}, unmapped: {len(unmapped)}", file=sys.stderr)
    if unmapped:
        print("unmapped (no toml entry):", file=sys.stderr)
        for n in unmapped:
            print(f"  {n}", file=sys.stderr)


if __name__ == "__main__":
    main()
