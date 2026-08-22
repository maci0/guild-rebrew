#!/usr/bin/env python3
"""Fill initialized named arrays (raw .data region) with original bytes.

Covers link_stubs array/scalar placeholders that have a rebrew-data.toml entry
in the initialized region ([0x10027000, 0x10035000)) and are still stubbed:
- char arrays: NUL-terminated size (strlen+1)
- other arrays: size = gap to next toml entry (capped at raw end)
Content = verbatim bytes from the original DLL; owner = most-referencing TU.

Usage: python3 scripts/own_init_arrays.py [--dry-run]
"""
import argparse
import pathlib
import re
import sys
import tomllib
from collections import defaultdict

ROOT = pathlib.Path(__file__).parent.parent
DATA_BASE = 0x10027000
DATA_OFF = 0x27000
RAW_END = DATA_BASE + 0xE000


def load_toml():
    with open(ROOT / "src" / "rebrew-data.toml", "rb") as f:
        db = tomllib.load(f)
    return {v.get("name", ""): int(k.split(".")[1], 16)
            for k, v in db.items() if v.get("section") == ".data"}


def parse_stubs():
    text = (ROOT / "src" / "link_stubs.c").read_text()
    stubs = {}
    for line in text.splitlines():
        m = re.match(r"^\s*([\w\s\*]+)\s+(\w+)(?:\[(\d+)\])?\s*;\s*$", line)
        if m:
            typ = " ".join(m.group(1).split())
            stubs[m.group(2)] = (typ, int(m.group(3)) if m.group(3) else None)
    return stubs


def refs(name, files):
    c = defaultdict(int)
    for f in files:
        try:
            c[str(f)] += len(re.findall(rf"\b{re.escape(name)}\b", f.read_text()))
        except OSError:
            pass
    return c


def hex_list(data):
    out = []
    for i in range(0, len(data), 16):
        out.append("    " + ", ".join("0x%02x" % b for b in data[i:i+16]) + ",")
    return "{\n" + "\n".join(out) + "\n}"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    orig = (ROOT / "original" / "Server" / "server.dll").read_bytes()
    toml = load_toml()
    stubs = parse_stubs()
    files = sorted((ROOT / "src" / "server.dll").rglob("*.c"))
    by_addr = sorted(toml.items(), key=lambda kv: kv[1])
    toml_next = {n: by_addr[i + 1][1] if i + 1 < len(by_addr) else RAW_END
                 for i, (n, a) in enumerate(by_addr)}

    done = 0
    for name, addr in by_addr:
        if addr >= RAW_END:
            continue
        if name not in stubs:
            continue
        typ, decl_n = stubs[name]
        off = DATA_OFF + (addr - DATA_BASE)
        nxt = toml_next[name]
        cap = min(nxt, RAW_END) - addr
        if cap <= 0:
            continue
        elemsize = 4
        base = typ.replace("*", "").strip()
        if base in ("char", "unsigned char"):
            elemsize = 1
        elif base in ("short", "unsigned short"):
            elemsize = 2
        elif base in ("double",):
            elemsize = 8
        if decl_n is None:
            size = elemsize                      # scalar
        else:
            data_end = orig.find(b"\x00", off, off + cap)
            is_char = elemsize == 1
            if is_char and data_end >= 0:
                size = data_end - off + 1        # NUL-terminated string
            elif decl_n > 1:
                size = decl_n * elemsize         # declared element count
            else:
                size = cap                       # unknown array -> full gap
        size = min(size, cap)
        data = orig[off:off + size]
        base = typ.replace("*", "").strip() or "unsigned char"
        if base not in ("int", "short", "char", "unsigned char", "unsigned short",
                        "unsigned int", "float", "double"):
            base = "unsigned char"
        init = hex_list(data)
        # owner
        counts = refs(name, files)
        owner = pathlib.Path(max(counts, key=counts.get)) if counts else None
        if owner is None:
            print(f"  no owner for {name}", file=sys.stderr)
            continue
        lines = owner.read_text().splitlines()
        extern_re = re.compile(r"^(\s*)extern\s+([\w\s\*]+)\s+" + re.escape(name) +
                               r"\s*(?:\[\s*\d*\s*\])\s*;\s*$")
        def_line = f"{typ} {name}[{size}] = {init};"
        placed = False
        for i, ln in enumerate(lines):
            if extern_re.match(ln):
                lines[i] = def_line
                placed = True
                break
        if not placed:
            lines.append(def_line)
        if not args.dry_run:
            owner.write_text("\n".join(lines) + "\n")
        done += 1
        print(f"  {name:28} {typ:12} @{addr:#010x} size {size:#x} -> {owner.relative_to(ROOT)}",
              file=sys.stderr)
    print(f"initialized arrays filled: {done}", file=sys.stderr)


if __name__ == "__main__":
    main()
