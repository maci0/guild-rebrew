#!/usr/bin/env python3
"""List unreversed functions whose bodies have no conditional branch.

These are the cheapest functions in the inventory: a pure call/argument
sequence compiles from a C transcription that needs no shape search at all.
Round 119 closed 14 in one pass this way; ten turned out to be already
claimed by a file named after a DIFFERENT address, so the tracked set here is
built from every `// FUNCTION: GOLDTL 0x...` marker in the tree, not from the
file names.

Usage: python3 scripts/straight_line.py [max-size]
"""
from __future__ import annotations

import glob
import json
import os
import re
import sys

import pefile

TARGET = 'Europa1400Gold_TL.exe'
REV = 'src'


def main() -> int:
    maxsize = int(sys.argv[1]) if len(sys.argv) > 1 else 180
    pe = pefile.PE(f'original/{TARGET}', fast_load=True)
    base = pe.OPTIONAL_HEADER.ImageBase
    data = open(f'original/{TARGET}', 'rb').read()
    secs = [(base + s.VirtualAddress, max(s.Misc_VirtualSize, s.SizeOfRawData),
             s.PointerToRawData) for s in pe.sections]

    def off(va: int) -> int | None:
        for va0, vs, pr in secs:
            if va0 <= va < va0 + vs:
                return pr + (va - va0)
        return None

    claimed = set()
    for f in glob.glob(f'{REV}/**/*.c', recursive=True):
        t = open(f, encoding='utf-8', errors='ignore').read()
        for m in re.finditer(r'^// FUNCTION: GOLDTL 0x([0-9a-f]+)', t, re.M):
            claimed.add(int(m.group(1), 16))
        b = os.path.basename(f)
        if b.startswith('fcn_') and b.endswith('.c'):
            claimed.add(int(b[4:12], 16))

    inv = json.load(open(f'db/inventory-{TARGET}.json'))
    out = []
    for e in inv:
        va, size = e['va'], e['size']
        if va in claimed or not (16 <= size <= maxsize):
            continue
        if not (0x400000 < va < 0x5e0000):
            continue
        o = off(va)
        if o is None:
            continue
        b = data[o:o + size]
        cond = calls = 0
        ok = True
        i = 0
        while i < len(b):
            op = b[i]
            if 0x70 <= op <= 0x7f:
                cond += 1
                i += 2
            elif op == 0x0f and i + 1 < len(b) and 0x80 <= b[i + 1] <= 0x8f:
                cond += 1
                i += 6
            elif op == 0xe8:
                calls += 1
                i += 5
            elif op in (0xe9, 0xeb):
                ok = False
                break
            else:
                i += 1
        if ok and cond == 0 and 1 <= calls <= 4:
            out.append((size, hex(va), calls))
    out.sort()
    for row in out:
        print(row)
    print(f'{len(out)} candidates (max size {maxsize})')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
