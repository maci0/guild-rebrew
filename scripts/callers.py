#!/usr/bin/env python3
"""List unreversed inventory functions that call one of the given addresses.

A reversed callee is a family key: its unreversed callers share the call
protocol, so once one member is understood the rest are cheap (rounds 1436-37
closed three message builders this way).  ``e8`` displacements are resolved
directly in the raw bytes; no disassembler needed.

Usage: python3 scripts/callers.py 0x4c6c30 [0x51af00 ...] [--max-size N]
"""
from __future__ import annotations

import glob
import json
import re
import sys

import pefile

TARGET = 'Europa1400Gold_TL.exe'


def main() -> int:
    args = sys.argv[1:]
    max_size = 400
    if '--max-size' in args:
        i = args.index('--max-size')
        max_size = int(args[i + 1])
        del args[i:i + 2]
    targets = {int(a, 16) for a in args}
    if not targets:
        print(__doc__)
        return 2

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
    for f in glob.glob('src/**/*.c', recursive=True):
        t = open(f, encoding='utf-8', errors='ignore').read()
        for m in re.finditer(r'^// FUNCTION: GOLDTL 0x([0-9a-f]+)', t, re.M):
            claimed.add(int(m.group(1), 16))
        m2 = re.search(r'fcn_([0-9a-fA-F]{8})\.c$', f)
        if m2:
            claimed.add(int(m2.group(1), 16))

    inv = json.load(open(f'db/inventory-{TARGET}.json'))
    hits: dict[int, list[tuple[str, int, int]]] = {t: [] for t in targets}
    for e in inv:
        va, size = e['va'], e['size']
        if va in claimed or not (16 <= size <= max_size):
            continue
        if not (0x400000 < va < 0x5e0000):
            continue
        o = off(va)
        if o is None:
            continue
        b = data[o:o + size]
        for i in range(len(b) - 4):
            if b[i] != 0xE8:
                continue
            rel = int.from_bytes(b[i + 1:i + 5], 'little', signed=True)
            callee = va + i + 5 + rel
            if callee in hits:
                hits[callee].append((hex(va), size, i))
    for t in sorted(targets):
        rows = sorted(hits[t], key=lambda r: r[1])
        print(f'--- callers of 0x{t:x}: {len(rows)}')
        for r in rows:
            print('   ', r)
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
