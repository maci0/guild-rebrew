#!/usr/bin/env python3
"""Resolve the static labels the split set leaves undefined, at their reference
addresses.

`split_coff.py` splits a member per section, so a relocation to a local label
that lives in one of the member's *other* sections survives as an undefined
**static** symbol -- the SEH scopetable `$T17396` that `malloc`'s prologue
pushes, for instance.  LINK does not report an undefined static: it treats it as
absolute 0, so the split-set DLL pushes `0x10000000` where the reference pushes
the scopetable's address.  Measured: 7 sites in `server.dll` (the `malloc`/
`realloc`/`_malloc_dbg`-family members), 21 bytes and 7 of postlink's failing
operand entries -- every non-split build resolves all 7.

An undefined static *cannot* be satisfied from another object: statics are
object-local, so a separate `abs` object (as `emit_defs.py` emits for
`__except_list`) is ignored, and an in-object ABSOLUTE symbol is honoured only
when its storage class is external (measured: same object, `scl 3` -> 0,
`scl 2` -> the value).  So each such symbol is promoted in place to an external
ABSOLUTE definition whose value is read from the reference: the reloc site's VA
is the object's own name prefix (the split objects carry section VA 0; the
pipeline orders them back onto the reference layout) plus the reloc offset, and
the reference's dword there is what the reference's own link wrote.

No section bytes are added, so the section geometry the layout package checks is
untouched.

Usage:
    python3 scripts/resolve_static_labels.py --rsp build/split_poc/rsp.rsp \\
        --reference original/Server/server.dll --out build/split_poc/abs
    # or, rewriting the response file to point at the patched copies:
    python3 scripts/resolve_static_labels.py --rsp ... --reference ... --out ... --rewrite
"""

from __future__ import annotations

import argparse
import os
import shlex
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from split_coff import Coff  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
IMAGE_BASE = 0x10000000


def reference_sections(raw: bytes) -> list[tuple[int, int, int, int]]:
    """(va, vsize, raw_ptr, raw_size) per section."""
    pe = struct.unpack_from("<I", raw, 0x3C)[0]
    nsec = struct.unpack_from("<H", raw, pe + 6)[0]
    opt = struct.unpack_from("<H", raw, pe + 20)[0]
    out = []
    for i in range(nsec):
        off = pe + 24 + opt + i * 40
        vs, va, rs, rp = struct.unpack_from("<IIII", raw, off + 8)
        out.append((va, vs, rp, rs))
    return out


def reference_dword(secs, raw: bytes, va: int) -> int | None:
    rva = va - IMAGE_BASE
    for sva, vs, rp, rs in secs:
        if sva <= rva < sva + vs and rva - sva < rs:
            return struct.unpack_from("<I", raw, rp + (rva - sva))[0]
    return None


def object_va(token: str) -> int | None:
    head = os.path.basename(token).split("_", 1)[0]
    if len(head) < 5 or head.startswith("0x"):
        return None
    try:
        return int(head, 16)
    except ValueError:
        return None


def patch_object(path: str, va: int, secs, raw: bytes) -> tuple[bytes, list[tuple[str, int, int]]]:
    """Promote every undefined static referenced by a .text reloc to an external
    ABSOLUTE definition.  Returns the new bytes and (name, value, site) rows."""
    data = bytearray(Path(path).read_bytes())
    coff = Coff(bytes(data))
    symptr = struct.unpack_from("<I", data, 8)[0]
    fixed: list[tuple[str, int, int]] = []
    for si, sec in enumerate(coff.sections):
        if not sec["name"].startswith(b".text"):
            continue
        for rva, symidx, _typ in coff.section_relocs(si):
            if symidx >= len(coff.symbols) or coff.symbols[symidx] is None:
                continue
            sym = coff.symbols[symidx]
            if sym["section"] != 0 or sym["storage_class"] not in (3, 6):
                continue
            site = va + rva
            value = reference_dword(secs, raw, site)
            if value is None:
                continue
            off = symptr + symidx * 18 + 8  # SymbolName[8] precedes the fields
            name = sym["name"]
            struct.pack_into("<IhHBB", data, off, value, -1, 0, 2, 0)
            fixed.append((name, value, site))
    return bytes(data), fixed


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--rsp", required=True)
    ap.add_argument("--reference", required=True)
    ap.add_argument("--out", required=True, help="directory for the patched copies")
    ap.add_argument("--rewrite", action="store_true",
                    help="rewrite --rsp to point at the patched copies")
    args = ap.parse_args()

    ref_path = Path(args.reference)
    if not ref_path.is_absolute():
        ref_path = ROOT / ref_path
    raw = ref_path.read_bytes()
    secs = reference_sections(raw)

    rsp = ROOT / args.rsp
    outdir = Path(args.out)
    outdir.mkdir(parents=True, exist_ok=True)

    tokens = shlex.split(rsp.read_text())
    new_tokens: list[str] = []
    emitted = 0
    for token in tokens:
        path = token if os.path.isabs(token) else str(ROOT / "build" / token)
        va = object_va(token) if os.path.exists(path) and path.endswith(".obj") else None
        if va is None:
            new_tokens.append(token)
            continue
        try:
            body, fixed = patch_object(path, va, secs, raw)
        except (struct.error, ValueError):
            new_tokens.append(token)
            continue
        if not fixed:
            new_tokens.append(token)
            continue
        dest = outdir / os.path.basename(token)
        dest.write_bytes(body)
        for name, value, site in fixed:
            print(f"{os.path.basename(token)}: {name} = {value:#x} (site {site:#x})")
        rel = os.path.relpath(dest, ROOT / "build")
        new_tokens.append(rel)
        emitted += 1

    print(f"{emitted} object(s) patched in {outdir}")
    if args.rewrite and emitted:
        rsp.write_text(" ".join(new_tokens))
        print(f"rewrote {rsp} to point at the patched copies")
    return 0


if __name__ == "__main__":
    sys.exit(main())
