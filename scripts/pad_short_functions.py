#!/usr/bin/env python3
"""Pad a short function's object so the symbols after it keep their reference VAs.

`make_split_rsp.py` orders the link so every object lands at its reference VA,
which only holds while each object's `.text` is as big as the reference's
functions.  A function that compiles short therefore drags everything after it
(measured: cm_ExCopyEntityData shrinking 912 -> 896 during a source edit took
`exactly at their reference VA` from 246/319 to 1/319 and the residue from
10,934 to 86,425), which makes every *better-shaped but differently-sized*
function unusable -- the measured +50-byte clamp rewrite on that same function
cannot be adopted at all.

This emits one small `.text`-only object per short function and inserts it into
the response file immediately after the object it pads, so the following symbols
land where they belong.  The padding bytes are zeros: they differ from the
reference's code, but so does the code they replace, and now only *this*
function's slot pays for it instead of the whole composition.

Only SHORT objects are padded.  A longer one cannot be cut without losing code;
those are reported so the size gap is visible.

Usage:
    python3 scripts/pad_short_functions.py --rsp build/split_poc/rsp.rsp \\
        --out-dir build/split_poc/pad --out-rsp build/split_poc/rsp_pad.rsp
"""

from __future__ import annotations

import argparse
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

#: exactly what CL.EXE emits for a `.text` section (code, execute, read, align 16).
#: With `/Gy` off every function of a file shares one plain `.text`, so there is
#: no COMDAT flag here -- setting it made LINK reject the object.
TEXT_CHARS = 0x60501020


def function_sizes() -> dict[int, int]:
    """VA -> reference size, from the metadata (the build's own source of truth)."""
    text = (ROOT / "src/rebrew-functions.toml").read_text()
    out: dict[int, int] = {}
    for m in re.finditer(r'^\["SERVER\.0x([0-9a-f]{8})"\]\n((?:(?!\[).*\n)*)', text, re.M):
        s = re.search(r"^size\s*=\s*(\d+)", m.group(2), re.M)
        if s:
            out[int(m.group(1), 16)] = int(s.group(1))
    return out


def map_entries() -> dict[str, list[int]]:
    """object basename -> the VAs of the functions it defines."""
    out: dict[str, list[int]] = {}
    # The map is written by the split link itself (/MAP:split_poc.map), so a
    # fresh build directory has none on the first run and this step has nothing
    # to key on.  Return no pad entries instead of raising: the link then runs,
    # produces the map, and the next run pads as usual.
    mapfile = ROOT / "build/split_poc.map"
    if not mapfile.exists():
        print("pad: no build/split_poc.map yet (first link) -- nothing to pad")
        return {}
    for line in mapfile.read_text().splitlines():
        m = re.match(r"^\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+f\s+(\S+)\s*$",
                     line)
        if m and m.group(3).endswith(".obj"):
            out.setdefault(Path(m.group(3)).name, []).append(int(m.group(2), 16))
    return out


def text_size(path: Path) -> int:
    try:
        d = path.read_bytes()
    except OSError:
        return 0
    if len(d) < 20 or d[:2] != b"\x4c\x01":
        return 0
    nsec = struct.unpack_from("<H", d, 2)[0]
    opt = struct.unpack_from("<H", d, 16)[0]
    total = 0
    for i in range(nsec):
        off = 20 + opt + i * 40
        name = d[off:off + 8].rstrip(b"\0").decode("latin1")
        if name.startswith(".text"):
            total += struct.unpack_from("<I", d, off + 16)[0]
    return total


def pad_object(name: str, size: int) -> bytes:
    """A one-section COFF object: `.text` of `size` zeros and a marker symbol.

    The section needs its own SECTION symbol (name `.text`, storage class 3,
    one aux record) before any other symbol -- without it LINK rejects the file
    with `LNK1143: invalid or corrupt file: no symbol for comdat section 0x1`.
    Copied from the split member objects, which link.
    """
    symname = f"_pad_{name.replace('.', '_')}"
    strtab = bytearray(b"\0\0\0\0")
    if len(symname) <= 8:
        rawname = symname.encode().ljust(8, b"\0")
    else:
        off = len(strtab)
        strtab += symname.encode() + b"\0"
        rawname = b"\0\0\0\0" + struct.pack("<I", off)

    raw_ptr = 20 + 40
    symptr = raw_ptr + size
    symbols = bytearray()
    symbols += struct.pack("<8sIhHBB", b".text\0\0\0", 0, 1, 0, 3, 1)
    # SectionDefinition aux: length, relocs, linenumbers, checksum, number, sel
    # 18 bytes exactly: Length, NumberOfRelocations, NumberOfLinenumbers,
    # CheckSum, Number, Selection, 3 unused.  Packing fewer shifts every
    # following symbol and LINK reads garbage offsets (LNK1106).
    symbols += struct.pack("<IHHIHB", size, 0, 0, 0, 1, 0) + b"\0\0\0"
    symbols += struct.pack("<8sIhHBB", rawname, 0, 1, 0, 2, 0)
    struct.pack_into("<I", strtab, 0, len(strtab))

    out = bytearray()
    out += struct.pack("<HHIIIHH", 0x14C, 1, 0, symptr, 3, 0, 0)
    out += struct.pack("<8sIIIIIIHHI", b".text", 0, 0, size, raw_ptr,
                       0, 0, 0, 0, TEXT_CHARS)
    out += b"\x00" * size
    out += symbols
    out += strtab
    return bytes(out)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--rsp", required=True)
    ap.add_argument("--out-dir", required=True)
    ap.add_argument("--out-rsp", required=True)
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    tokens = (ROOT / args.rsp).read_text().split()
    sizes = function_sizes()
    by_obj = map_entries()
    outdir = ROOT / args.out_dir
    outdir.mkdir(parents=True, exist_ok=True)

    newtokens: list[str] = []
    padded = short = 0
    for tok in tokens:
        newtokens.append(tok)
        path = Path(tok)
        if not path.is_absolute():
            path = ROOT / "build" / tok
        # Our OBJECTS only: the split members (`<va>_<section>.obj`) are LIBCMT
        # sections that `split_coff.py` trims to the reference function's size on
        # purpose, and padding them would corrupt the CRT half of the link.
        if path.suffix != ".obj" or not path.name.endswith(".c.obj") or not path.exists():
            continue
        vas = by_obj.get(path.name)
        if not vas:
            continue
        want = sum(sizes.get(v, 0) for v in vas)
        have = text_size(path)
        if not want or have >= want:
            # The pad *decision* is `have >= want` and is unchanged.  The *report*
            # must compare against the reference's padded span instead: cl rounds
            # `have` up to a 16-byte multiple while `want` is the unaligned sum of
            # the reference sizes, so comparing them directly labels every object
            # whose reference size is not a multiple of 16 as too long -- 149 of
            # 319 in this tree, burying the handful that genuinely drag.  What
            # actually moves the following symbols is `have > 16*ceil(want/16)`;
            # see docs/msvc6-allocator.md Finding 58.
            #
            # Caveat: `want` is only as complete as the metadata.  An object
            # holds code for functions `rebrew-functions.toml` may not describe,
            # and then `want` understates the reference span and this still
            # reports a phantom drag -- `trees.c.obj` shows +5376, which cannot
            # be real (the built image's largest symbol displacement is 796).
            # Treat a hit as a lead to confirm against the map, not as proof.
            span = 16 * ((want + 15) // 16)
            if want and have > span:
                short += 1
                print(f"LONG  {path.name}: {have} > {span} (+{have - span} over the "
                      f"padded span; want {want}) -- not padded")
            continue
        pad = want - have
        dest = outdir / f"{path.stem}_pad.obj"
        if not args.dry_run:
            dest.write_bytes(pad_object(path.stem, pad))
        newtokens.append(str(dest.relative_to(ROOT / "build")))
        padded += 1
        print(f"pad   {path.name}: {have} -> {want} (+{pad})")
    if not args.dry_run:
        (ROOT / args.out_rsp).write_text(" ".join(newtokens) + "\n")
    print(f"\n{padded} object(s) padded, {short} too long -> {args.out_rsp}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
