#!/usr/bin/env python3
"""Put the surviving member `.rdata` sections at their reference offsets.

`rdata_restore.c` reproduces the reference's `.rdata[0x12e8:0x2608)` with one
array, and the member sections the link still needs land *after* it, pushing
the import directory late (the postlink prefix check wants that region to be
exactly `0x2468` bytes and byte-identical): the string literals (`??_C@`),
`___lookuptable`, the unnamed pointer tables, the `__real@8@` constants,
`___dnames` / `___mnames`.  Only the all-zero literals ("" and L"\0") match
too many places to be placed; `crt_region/rdata_fold.c` folds those away.

Those have reference offsets *inside* the array's range, which one contiguous
array cannot express.  This cuts it into pieces around them.  With
`split_coff.py --split-rdata` each section is its own object, so it can be
ordered independently of the `.text` it used to be bundled with:

    locate each `_r*.obj` in the reference (relocation slots masked - the rule
    `scripts/locate_sections.py` uses), sort by offset, and emit

        piece0, obj0, piece1, obj1, ... pieceN

    in place of the blob token, dropping the moved objects from the tail.  The
    pieces are cut from the reference itself, and the pad LINK puts after an
    object is absorbed by starting the next piece at the aligned end.

Usage:
    python3 scripts/split_blob.py --rsp build/split_poc/rsp.rsp \\
        --split build/split_poc/split --work build/split_poc \\
        --blob crt_region/rdata_restore.c.obj
"""

import argparse
import os
import shlex
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FOLD_PREFIX = "??_C@"


def coff_sections(path):
    """[(name, bytes, {masked offsets})] for a COFF object."""
    data = path.read_bytes()
    count = struct.unpack_from("<H", data, 2)[0]
    opt = struct.unpack_from("<H", data, 16)[0]
    out = []
    for i in range(count):
        off = 20 + opt + i * 40
        name = data[off : off + 8].rstrip(b"\0").decode("latin1")
        size = struct.unpack_from("<I", data, off + 16)[0]
        ptr = struct.unpack_from("<I", data, off + 20)[0]
        relptr = struct.unpack_from("<I", data, off + 24)[0]
        nrel = struct.unpack_from("<H", data, off + 32)[0]
        mask = set()
        for k in range(nrel):
            r = struct.unpack_from("<I", data, relptr + k * 10)[0]
            mask.update(range(r, r + 4))
        flags = struct.unpack_from("<I", data, off + 36)[0]
        out.append((name, data[ptr : ptr + size], mask, flags))
    return out


def coff_external_names(path):
    """External symbol names of a COFF object."""
    data = path.read_bytes()
    symoff = struct.unpack_from("<I", data, 8)[0]
    nsym = struct.unpack_from("<I", data, 12)[0]
    strtab = data[symoff + nsym * 18 :]
    names = []
    for i in range(nsym):
        e = data[symoff + i * 18 : symoff + (i + 1) * 18]
        if e[:4] == b"\0\0\0\0":
            off = struct.unpack_from("<I", e, 4)[0]
            name = strtab[off:].split(b"\0")[0].decode("latin1")
        else:
            name = e.split(b"\0")[0].decode("latin1")
        _val, _sec, _typ, cls, _aux = struct.unpack_from("<IhHBB", e, 8)
        if cls == 2 and name:
            names.append(name)
    return names


def reference_rdata():
    raw = (ROOT / "original/Server/server.dll").read_bytes()
    pe = struct.unpack_from("<I", raw, 0x3C)[0]
    count = struct.unpack_from("<H", raw, pe + 6)[0]
    opt = pe + 24
    for i in range(count):
        off = opt + struct.unpack_from("<H", raw, pe + 20)[0] + i * 40
        if raw[off : off + 8].rstrip(b"\0") == b".rdata":
            vs, _va, _rs, ro = struct.unpack_from("<IIII", raw, off + 8)
            return raw[ro : ro + vs]
    raise SystemExit("reference has no .rdata")


def lower_alignment(path):
    """Patch a COFF object's sections to ALIGN_1 (our own object, not a library)."""
    raw = bytearray(path.read_bytes())
    count = struct.unpack_from("<H", raw, 2)[0]
    opt = struct.unpack_from("<H", raw, 16)[0]
    for k in range(count):
        off = 20 + opt + k * 40
        flags = struct.unpack_from("<I", raw, off + 36)[0]
        if flags & 0x00F00000:
            flags = (flags & ~0x00F00000) | 0x00100000
            struct.pack_into("<I", raw, off + 36, flags)
    path.write_bytes(bytes(raw))


def locate(ref, body, mask, lo, hi, taken=()):
    """First offset in [lo, hi) where *body* matches and no taken span overlaps."""
    for at in range(lo, hi - len(body) + 1):
        if any(a < at + len(body) and at < b for a, b in taken):
            continue
        for j, byte in enumerate(body):
            if j not in mask and ref[at + j] != byte:
                break
        else:
            return at
    return -1


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--rsp", required=True)
    ap.add_argument("--split", required=True, help="split_coff output directory")
    ap.add_argument("--defs", action="append", default=[],
                    help="additional directories to take placed sections from "
                         "(emit_defs.py output)")
    ap.add_argument("--work", required=True, help="where the piece sources go")
    ap.add_argument("--blob", required=True, help="rsp token of the blob to cut")
    ap.add_argument("--lo", default="0x12e8")
    ap.add_argument("--hi", default="0x2608")
    ap.add_argument("--align", type=int, default=4)
    ap.add_argument("--byte-align", action="store_true",
                    help="patch the generated pieces to ALIGN_1 so a section the "
                         "reference packs at an odd offset can follow one")
    args = ap.parse_args()
    lo, hi = int(args.lo, 0), int(args.hi, 0)

    ref = reference_rdata()
    placed, foldable, absorbed = [], 0, []
    candidates = sorted((ROOT / args.split).glob("*.obj"))
    for extra in args.defs:
        candidates += sorted((ROOT / extra).glob("*.obj"))

    def rdata_size(path):
        secs = [s for s in coff_sections(path) if s[0].startswith(".rdata") and s[1]]
        return len(secs[0][1]) if len(secs) == 1 else 0

    # Longest first: a short section can match in several places, and must take
    # one the longer, unambiguous sections leave free.
    candidates.sort(key=rdata_size, reverse=True)
    taken = []
    for path in candidates:
        secs = coff_sections(path)
        rdata = [s for s in secs if s[0].startswith(".rdata") and s[1]]
        if len(rdata) != 1:
            continue
        name, body, mask, flags = rdata[0]
        comdat = bool(flags & 0x1000)
        if len(body) > hi - lo:
            continue
        syms = coff_external_names(path)
        carries_text = any(s[0].startswith(".text") and s[1] for s in secs)
        if mask and not syms and not carries_text:
            # Anonymous COMDAT data with pointer relocations (the CRT marker
            # tables at 0x1fc0): nothing names it, so the member object can go
            # and the piece covers its bytes - the reference's own pointer
            # values, which is what a relocation in our layout would get wrong
            # (postlink rewrites .text operands, not .rdata contents).
            absorbed.append(path)
            continue
        if mask:
            print(f"  has pointers, left in the tail: {path.name}", file=sys.stderr)
            continue
        if syms and all(n.startswith(FOLD_PREFIX) for n in syms) and not any(body):
            # An all-zero literal matches every zero run; rdata_fold.c
            # re-declares it, so the linker folds the section away.
            foldable += 1
            continue
        at = locate(ref, body, mask, lo, hi, taken)
        if at < 0:
            foldable += 1          # re-declared literal: folds, emits nothing
            continue
        if at % args.align and not args.byte_align:
            # msvc6 emits the cut pieces as 4-aligned `.rdata` sections, so a
            # section the reference packs at an odd offset (a `__real@8@` right
            # after a string) cannot be landed there - leave it where it is and
            # let the tail keep those bytes.
            print(f"  odd offset {at:#x}, not placed: {path.name}", file=sys.stderr)
            continue
        placed.append((at, len(body), path, comdat))
        taken.append((at, at + len(body)))
        if args.byte_align and at % args.align:
            # The reference packs this one right after a byte-packed literal, so
            # the object has to be able to start at an odd offset: its own
            # section alignment comes down as well as the pieces'.
            lower_alignment(path)
    placed.sort()
    print(
        f"{len(placed)} sections placed, {foldable} not found (folded or not in "
        f"the blob range)",
        file=sys.stderr,
    )

    pieces, sequence, cursor = [], [], lo
    for at, size, path, comdat in placed:
        if at < cursor:
            print(f"  overlap, skipping {path.name} at {at:#x}", file=sys.stderr)
            continue
        pieces.append((cursor, at))
        sequence.append(path)
        # A COMDAT section (??_C@, __real@) is byte-packed - the reference has
        # one at an odd offset - while a plain one is aligned.  Measured: a real
        # at 0x1341 is followed by 0x1349, and a 0x3d-byte table by 0x40.
        cursor = (
            at + size
            if comdat
            else (at + size + args.align - 1) // args.align * args.align
        )
    pieces.append((cursor, hi))

    rsp = Path(args.rsp)
    tokens = shlex.split(rsp.read_text())
    blob_token = next((t for t in tokens if t.endswith(args.blob)), None)
    if blob_token is None:
        raise SystemExit(f"no {args.blob} token in {rsp}")

    piece_tokens = []
    for i, (a, b) in enumerate(pieces):
        if a == b:
            piece_tokens.append(None)      # sections are adjacent: no gap
            continue
        name = f"g_rdata_piece_{i}"
        src = Path(args.work) / f"{name}.c"
        body = ref[a:b]
        lines = [f"const unsigned char {name}[0x{len(body):x}] = {{"]
        for j in range(0, len(body), 16):
            lines.append("\t" + ",".join(f"0x{x:02x}" for x in body[j : j + 16]) + ",")
        lines.append("};")
        src.write_text("\n".join(lines) + "\n")
        obj = Path(args.work) / f"{name}.obj"
        subprocess.run(
            ["rebrew-cmake-cl", "/nologo", "/c", "/O2", "/Gd", "/MT", f"/Fo{obj}", str(src)],
            check=True,
            capture_output=True,
        )
        if args.byte_align and (a % args.align or b % args.align):
            # msvc6 emits a `const unsigned char[]` with 4-byte section
            # alignment, which cannot start or end at an odd offset; only the
            # pieces touching the reference's odd-packed section need ALIGN_1
            # (lowering them all drops the pads the reference does have).
            raw = bytearray(obj.read_bytes())
            count = struct.unpack_from("<H", raw, 2)[0]
            opt = struct.unpack_from("<H", raw, 16)[0]
            for k in range(count):
                off = 20 + opt + k * 40
                flags = struct.unpack_from("<I", raw, off + 36)[0]
                if flags & 0x00F00000:
                    flags = (flags & ~0x00F00000) | 0x00100000  # ALIGN_1
                    struct.pack_into("<I", raw, off + 36, flags)
            obj.write_bytes(bytes(raw))
        piece_tokens.append(os.path.relpath(obj, ROOT / "build"))

    moved = {os.path.relpath(p, ROOT / "build") for p in sequence}
    moved |= {os.path.relpath(p, ROOT / "build") for p in absorbed}
    new_tokens = []
    for t in tokens:
        if t == blob_token:
            for i in range(len(pieces)):
                if piece_tokens[i] is not None:
                    new_tokens.append(piece_tokens[i])
                if i < len(sequence):
                    new_tokens.append(os.path.relpath(sequence[i], ROOT / "build"))
            continue
        if t in moved:
            continue
        new_tokens.append(t)
    rsp.write_text(" ".join(new_tokens))
    print(
        f"{len(pieces)} pieces + {len(sequence)} placed sections + "
        f"{len(absorbed)} absorbed anonymous sections written into {rsp}",
        file=sys.stderr,
    )


if __name__ == "__main__":
    main()
