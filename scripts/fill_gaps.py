#!/usr/bin/env python3
"""Fill initialized .data gaps with original bytes, coverage-aware.

Computes which byte ranges of the raw region [0x27000,0x35000) are already
covered by known symbols (toml addresses + inferred sizes: NUL strings,
declared arrays, scalars) and emits `unsigned char _dpad_<addr>[N] = {<orig
bytes>};` for the uncovered runs only — so the compiler-emitted string
COMDATs are never duplicated.  Owner TU = most-referencing file of the next
covered symbol.

Usage: python3 scripts/fill_gaps.py [--dry-run]
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
    return {v.get("name", ""): (int(k.split(".")[1], 16), v.get("type", "int"))
            for k, v in db.items() if v.get("section") == ".data"}


def parse_stubs():
    text = (ROOT / "src" / "link_stubs.c").read_text()
    stubs = {}
    for line in text.splitlines():
        m = re.match(r"^\s*([\w\s\*]+)\s+(\w+)(?:\[(\d+)\])?\s*;\s*$", line)
        if m:
            stubs[m.group(2)] = (m.group(1).strip(), int(m.group(3)) if m.group(3) else None)
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
    by_addr = sorted(toml.items(), key=lambda kv: kv[1][0])

    # covered ranges in the raw region
    covered = []
    for i, (name, (addr, typ)) in enumerate(by_addr):
        if addr >= RAW_END:
            continue
        nxt = by_addr[i + 1][1][0] if i + 1 < len(by_addr) else RAW_END
        cap = min(nxt, RAW_END) - addr
        base = typ.replace("*", "").strip()
        elemsize = 4
        if base in ("char", "unsigned char"):
            elemsize = 1
        elif base in ("short", "unsigned short"):
            elemsize = 2
        elif base == "double":
            elemsize = 8
        decl_n = stubs.get(name, (None, None))[1]
        off = DATA_OFF + (addr - DATA_BASE)
        if elemsize == 1:
            end = orig.find(b"\x00", off, off + cap)
            size = (end - off + 1) if end >= 0 else min(cap, 1)
        elif decl_n is None:
            size = elemsize
        elif decl_n > 1:
            size = decl_n * elemsize
        else:
            size = cap
        size = min(size, cap)
        covered.append((addr, addr + size, name))

    # uncovered runs
    cursor = DATA_BASE
    runs = []
    prev_name = None
    for a, b, name in sorted(covered):
        if a > cursor:
            runs.append((cursor, a, name or prev_name))
        cursor = max(cursor, b)
        prev_name = name or prev_name
    if cursor < RAW_END:
        runs.append((cursor, RAW_END, prev_name))

    n = 0
    for a, b, next_name in runs:
        size = b - a
        if size < 0x10:
            continue
        # skip the leading pre-first-symbol pad? no — include it, it's real data
        owner = None
        if next_name:
            counts = refs(next_name, files)
            owner = pathlib.Path(max(counts, key=counts.get)) if counts else None
        if owner is None:
            print(f"  no owner for run {a:#x}+{size:#x}", file=sys.stderr)
            continue
        data = orig[DATA_OFF + (a - DATA_BASE):DATA_OFF + (b - DATA_BASE)]
        init = hex_list(data)
        def_line = f"unsigned char _dpad_{a:x}[{size}] = {init};"
        lines = owner.read_text().splitlines()
        lines.append(def_line)
        if not args.dry_run:
            owner.write_text("\n".join(lines) + "\n")
        n += 1
        print(f"  gap {a:#x}+{size:#x} -> {owner.relative_to(ROOT)}", file=sys.stderr)
    print(f"gap pads: {n}", file=sys.stderr)


if __name__ == "__main__":
    main()
