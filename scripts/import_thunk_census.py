#!/usr/bin/env python3
"""Count import thunks vs direct IAT calls in a PE, the way MSVC6 emits them.

Why this exists (round 7).  The server's `.text` overshoot is 642 bytes, and
~566 of them are `jmp dword ptr [IAT]` thunks that the reference does not have.
The only signal available was `split_audit.py`'s trailing-content block, which
counts the thunks as symbols but cannot say whether they are *needed*.

The distinction that matters:

    __declspec(dllimport)  ->  the compiler emits `call dword ptr [IAT]`
                               (ff 15) and LINK needs no thunk.
    plain extern, no dllimport ->  the compiler emits `call _X@N` and LINK
                               resolves it to a `jmp dword ptr [IAT]` thunk.

The reference calls imports directly (211 `ff 15`) and has 11 thunks.  Counting
both numbers is what proves the tree's call sites are already faithful and the
thunks are pure linker overhead, rather than a symptom of wrong call sites.

**Measure `.text` only.**  A raw scan of the first N bytes of the file runs past
the end of `.text` into `.rdata` and counts unrelated `ff 25` byte pairs; that is
how round 6 compared "97 thunks" against "101 thunks" and wrongly refuted the
`/INCLUDE:__imp__X` explanation.  Both binaries must be counted identically.

Usage:
    python3 scripts/import_thunk_census.py build/split_poc.dll
    python3 scripts/import_thunk_census.py build/split_poc.dll \\
        --reference original/Server/server.dll --iat-rva 0x24000 --iat-size 0x1a0
"""

from __future__ import annotations

import argparse
import struct
from pathlib import Path

DEFAULT_IAT_RVA = 0x24000
DEFAULT_IAT_SIZE = 0x1A0
IMAGE_BASE = 0x10000000


def sections(d: bytes) -> dict[str, tuple[int, int, int, int]]:
    pe = struct.unpack_from("<I", d, 0x3C)[0]
    n = struct.unpack_from("<H", d, pe + 6)[0]
    oh = struct.unpack_from("<H", d, pe + 20)[0]
    off = pe + 24 + oh
    out = {}
    for i in range(n):
        s = off + i * 40
        name = d[s:s + 8].rstrip(b"\x00").decode(errors="ignore")
        vs, va, rs, rp = struct.unpack_from("<IIII", d, s + 8)
        out[name] = (va, vs, rs, rp)
    return out


def imported_symbols(d: bytes) -> int:
    """Count imported symbols across all import descriptors.

    Data directory index **1** is Import; index 0 is Export.  Reading index 0
    returns the export table, which for this DLL yields 0 and looks exactly
    like "the build has no imports" -- which is how round 7 concluded the
    `/INCLUDE` directives were load-bearing when they were not measured at all.
    Count this with the same care as the thunk census.
    """
    secs = sections(d)
    pe = struct.unpack_from("<I", d, 0x3C)[0]
    irva = struct.unpack_from("<I", d, pe + 24 + 96 + 8)[0]   # index 1
    if not irva:
        return 0

    def r2f(r: int):
        for _name, (va, vs, _rs, rp) in secs.items():
            if va <= r < va + max(vs, _rs):
                return rp + (r - va)
        return None

    total, k = 0, irva
    while True:
        f = r2f(k)
        if f is None:
            break
        oft, _ts, _fc, nm, _ft = struct.unpack_from("<IIIII", d, f)
        if not nm:
            break
        j = r2f(oft)
        if j is None:
            break
        c = 0
        while struct.unpack_from("<I", d, j + c * 4)[0]:
            c += 1
        total += c
        k += 20
    return total


def imported_names(d: bytes) -> list[str]:
    """Every imported symbol, in IAT order.  Ordinals come back as 'ord<N>'.

    Needed because the presence of a `__imp__X` symbol in a LINK map does NOT
    mean the import survives: under `/OPT:REF` the `__imp_` symbol can be linked
    while its import descriptor is dropped, and the import table then has fewer
    entries.  Only the descriptor decides.
    """
    secs = sections(d)
    pe = struct.unpack_from("<I", d, 0x3C)[0]
    irva = struct.unpack_from("<I", d, pe + 24 + 96 + 8)[0]   # index 1 = Import
    if not irva:
        return []

    def r2f(r: int):
        for _name, (va, vs, _rs, rp) in secs.items():
            if va <= r < va + max(vs, _rs):
                return rp + (r - va)
        return None

    out: list[str] = []
    k = irva
    while True:
        f = r2f(k)
        if f is None:
            break
        oft, _ts, _fc, nm, _ft = struct.unpack_from("<IIIII", d, f)
        if not nm:
            break
        j = r2f(oft)
        if j is None:
            break
        c = 0
        while True:
            v = struct.unpack_from("<I", d, j + c * 4)[0]
            if v == 0:
                break
            if v & 0x80000000:
                out.append("ord%d" % (v & 0xFFFF))
            else:
                p = r2f(v)
                out.append(d[p + 2:d.find(b"\0", p + 2)].decode(errors="replace"))
            c += 1
        k += 20
    return out


def census(path: str, iat_rva: int, iat_size: int) -> dict:
    d = Path(path).read_bytes()
    secs = sections(d)
    if ".text" not in secs:
        raise SystemExit(f"{path}: no .text section")
    va, vs, _rs, rp = secs[".text"]
    text = d[rp:rp + vs]              # .text ONLY -- never past the section
    lo = IMAGE_BASE + iat_rva
    hi = lo + iat_size
    thunks = []
    calls = 0
    for i in range(len(text) - 5):
        if text[i] == 0xFF and text[i + 1] == 0x25:
            thunks.append((IMAGE_BASE + va + i, struct.unpack_from("<I", text, i + 2)[0]))
        elif text[i] == 0xFF and text[i + 1] == 0x15:
            calls += 1
    into_iat = [t for t in thunks if lo <= t[1] < hi]
    return {
        "path": path,
        "text_vsize": vs,
        "imports": imported_symbols(d),
        "thunks": len(thunks),
        "thunks_into_iat": len(into_iat),
        "direct_calls": calls,
        "first_thunk": thunks[0][0] if thunks else None,
        "last_thunk": thunks[-1][0] if thunks else None,
    }


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("binary")
    ap.add_argument("--reference", help="compare against this PE")
    ap.add_argument("--iat-rva", type=lambda s: int(s, 0), default=DEFAULT_IAT_RVA)
    ap.add_argument("--iat-size", type=lambda s: int(s, 0), default=DEFAULT_IAT_SIZE)
    args = ap.parse_args()

    for p in filter(None, (args.binary, args.reference)):
        c = census(p, args.iat_rva, args.iat_size)
        print(f"{c['path']}")
        print(f"  .text VirtualSize   {c['text_vsize']:#x}")
        print(f"  imported symbols    {c['imports']}")
        print(f"  jmp [abs] thunks    {c['thunks']}  ({c['thunks_into_iat']} into the IAT)")
        print(f"  call [abs] direct   {c['direct_calls']}")
        if c["first_thunk"] is not None:
            print(f"  thunk range         {c['first_thunk']:#x}..{c['last_thunk']:#x}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
