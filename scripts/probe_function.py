#!/usr/bin/env python3
"""Measure ONE function after editing its source — a probe harness.

Every remaining non-matching function lives in a translation unit with several
functions (and the build emits one COMDAT `.text` section per function), so
"compile the file and compare" needs to find *this* function inside the object
first.  This does that: it compiles the file with the flags its `// CFLAGS:`
annotation declares (or `--cflags`), locates the function by matching the
reference's first bytes with relocation slots wildcarded, and reports the
fixed-offset masked match and the instruction count against the reference.

That is the measurement a source or flag probe needs; edit the source, re-run,
compare.  For *why* two functions differ, use `scripts/instr_diff.py`.

Usage:
    python3 scripts/probe_function.py --va 0x10019ed0 \\
        --file src/server.dll/DieGildeAddOn/game/spiel622.c
    python3 scripts/probe_function.py --va 0x10019ed0 --file ... --obj build/x.obj
    python3 scripts/probe_function.py --va 0x10019ed0 --file ... \\
        --cflags "/O2 /Gd /Ot"
"""

from __future__ import annotations

import argparse
import capstone
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from split_coff import Coff  # noqa: E402

REFERENCE = ROOT / "original/Server/server.dll"
IMAGE_BASE = 0x10000000
INCLUDES = ["-I" + str(ROOT / "src/server.dll"),
            "-I" + str(ROOT / "references/zlib-1.1.3")]
MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


def sections(path: Path) -> dict:
    d = path.read_bytes()
    e = struct.unpack_from("<I", d, 0x3C)[0]
    n = struct.unpack_from("<H", d, e + 6)[0]
    opt = struct.unpack_from("<H", d, e + 20)[0]
    out = {}
    for i in range(n):
        off = e + 24 + opt + i * 40
        name = d[off : off + 8].rstrip(b"\0").decode()
        vs, va, rs, rp = struct.unpack_from("<IIII", d, off + 8)
        out[name] = (va, vs, rp, rs)
    return out


def reloc_mask(path: Path, secs: dict, va: int, size: int) -> bytearray:
    raw = path.read_bytes()
    m = bytearray(size)
    if ".reloc" not in secs:
        return m
    _va, _vs, rp, rs = secs[".reloc"]
    blk = raw[rp : rp + rs]
    i = 0
    while i + 8 <= len(blk):
        page, bsize = struct.unpack_from("<II", blk, i)
        if bsize < 8:
            break
        for j in range(i + 8, min(i + bsize, len(blk)), 2):
            ent = struct.unpack_from("<H", blk, j)[0]
            if ent >> 12 == 3:
                o = page + (ent & 0xFFF) - (va - IMAGE_BASE)
                for k in range(o, o + 4):
                    if 0 <= k < size:
                        m[k] = 1
        i += bsize
    return m


def metadata_cflags(va: int) -> str | None:
    """The flags rebrew resolves for this function, from rebrew-functions.toml.

    The build no longer reads the `// CFLAGS:` annotation (round 154 moved the
    single source of truth to the metadata: CMakeLists calls
    `rebrew cmake-flags`), so neither may this probe -- measuring a `/Ox` or
    `/G6 /Oy-` function with the `/O2 /Gd` fallback reports the wrong code.
    """
    text = (ROOT / "src/rebrew-functions.toml").read_text()
    # The entry ends at the next `[` line: an unbounded scan walks into the NEXT
    # function's entry, so a function with no cflags of its own silently
    # inherited its neighbour's (measured: cm_ExSellObjekt compiled 2304 bytes
    # instead of 2064 and scored 519 instead of 558).
    m = re.search(rf'\["SERVER\.0x{va:08x}"\]\n((?:(?!\[).*\n)*)', text)
    if not m:
        return None
    c = re.search(r'cflags\s*=\s*"([^"]*)"', m.group(1))
    return c.group(1) if c else None


def wanted_symbol(va: int) -> str | None:
    """The function's decorated name, from the vehicle link map if it exists."""
    mapfile = ROOT / "build/split_poc.map"
    if not mapfile.exists():
        return None
    for line in mapfile.read_text().splitlines():
        m = re.match(r"^\s+0001:[0-9a-f]{8}\s+(.*?)\s+([0-9a-f]{8})\s+(\S.*)$", line)
        if m and int(m.group(2), 16) == va:
            return m.group(1).split()[0]
    return None


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--va", required=True)
    ap.add_argument("--file", required=True, help="source file (or its object's source)")
    ap.add_argument("--size", type=lambda s: int(s, 0), default=None)
    ap.add_argument("--cflags", default=None,
                    help="default: the file's `// CFLAGS:` annotation, else /O2 /Gd")
    ap.add_argument("--obj", default=None, help="an already-compiled object to measure")
    args = ap.parse_args()

    va = int(args.va, 0)
    src = ROOT / args.file
    size = args.size
    if size is None:
        text = (ROOT / "src/rebrew-functions.toml").read_text()
        m = re.search(rf'\["SERVER\.0x{va:08x}"\]\n(?:.*\n)*?size\s*=\s*(\d+)', text)
        if not m:
            sys.exit("pass --size (no metadata entry for that VA)")
        size = int(m.group(1))

    obj = Path(args.obj) if args.obj else None
    tmp = None
    if obj is None:
        cflags = args.cflags
        if cflags is None:
            # metadata first (what the build and every tool use); the inline
            # annotation is the legacy fallback for the second target, which
            # still carries them.
            m = re.search(r"^// CFLAGS: *(.*)$", src.read_text(), re.M)
            cflags = metadata_cflags(va) or (m.group(1) if m else None) or "/O2 /Gd"
        # the toolchain runs in a container that mounts the project only, so the
        # object has to live inside it
        tmp = ROOT / "build/objtest"
        tmp.mkdir(parents=True, exist_ok=True)
        obj = tmp / f"probe_{os.getpid()}.obj"
        cmd = (["rebrew-cmake-cl", "/nologo", "-DREBREW_ALLOW_NAKED=1",
                "-Dserver_dll_EXPORTS"] + INCLUDES
               + ["/W3", "/D", "WIN32", "/D", "_WINDOWS", "/D", "_WIN32_WINNT=0x0400",
                  "/D", "NDEBUG", "-MT"] + cflags.split() + [f"/Fo{obj}", "-c", str(src)])
        r = subprocess.run(cmd, cwd=ROOT / "build", capture_output=True, text=True)
        if not obj.exists():
            print(r.stdout[-2000:] + r.stderr[-2000:], file=sys.stderr)
            return 1

    ref = REFERENCE.read_bytes()
    rsecs = sections(REFERENCE)
    rva = va - IMAGE_BASE
    rptr = rsecs[".text"][2] + (rva - rsecs[".text"][0])
    rbody = ref[rptr : rptr + size]
    rmask = reloc_mask(REFERENCE, rsecs, va, size)
    # a short, prologue-stable prefix: the bodies differ, so a long match fails
    head = bytes(0 if rmask[i] else rbody[i] for i in range(12))

    coff = Coff(obj.read_bytes())
    # the build emits one COMDAT .text per function: pick the section whose size
    # matches the reference's best, preferring one that starts with the
    # reference's first bytes (the prologue itself can differ, so the match is
    # only a tie-break)
    # the COMDAT's own symbol names the function, which is what disambiguates
    # equal-sized sections when an edit has moved the prologue
    wanted = wanted_symbol(va)
    best = None
    for si, s in enumerate(coff.sections):
        if not s["name"].startswith(b".text"):
            continue
        body = coff.section_body(si)
        delta = abs(len(body) - size)
        name = next((sym["name"] for sym in coff.symbols
                     if sym and sym["section"] == si + 1
                     and sym["storage_class"] == 2), None)
        hit = (len(body) >= 12
               and all(not head[k] or body[k] == head[k] for k in range(12)))
        key = (0 if (wanted and name == wanted) else 1, 0 if hit else 1, delta)
        if best is None or key < best[0]:
            best = (key, si, body)
    # A body far from the target size is normal: the composition TRIMS an
    # overrun (crt_region/dllmain.c links a 203-byte object into the reference's
    # 157-byte slot byte-perfectly), and a function whose flags differ can be
    # tens of bytes out.  Only the size-fallback path needs the window; a COMDAT
    # that carries the wanted symbol is the function whatever its size.
    matched_by_symbol = best is not None and best[0][0] == 0
    if best is None or (not matched_by_symbol and best[0][2] > 512):
        print(f"function 0x{va:x} not found in {obj} "
              f"(no .text COMDAT within 32 bytes of {size})", file=sys.stderr)
        return 1
    si, body = best[1], best[2]
    found = (si, 0, body)
    si, start, body = found
    cmask = bytearray(len(body))
    for r, _sym, _typ in coff.section_relocs(si):
        for k in range(r, min(r + 4, len(body))):
            cmask[k] = 1
    # Compare over the TARGET's size, not the object's: a short function used to
    # shrink the denominator and score a flattering percentage, which is how a
    # 13-byte-short cm_ExSellObjekt looked like a 228-byte win while it was
    # costing the composition its position alignment (the linked image went from
    # 11,336 to 89,509 differing bytes).  The object's own size is reported so a
    # caller can require it to match.
    n = size
    cb = body[start : start + n]
    # A byte under a relocation on EITHER side used to count as matched.  That is
    # generous in a way that pays for wrong code: an instruction that introduces a
    # new absolute address buys all four of its operand bytes whether or not it is
    # the reference's instruction.  It is also what made the round-162 CrashDump
    # move (523 -> 565) look like a win when 90% of the gain was new reloc slots.
    # A byte is really right in the composed image only when both sides relocate
    # it (postlink rewrites it from the reference) or neither does and the bytes
    # agree.  The old number is kept alongside as `matched-reloc`, because every
    # figure recorded in a source header before round 173 is that one.
    generous = sum(
        1 for i in range(n)
        if i < len(cb) and ((rmask[i] or cmask[start + i]) or rbody[i] == cb[i])
    )
    matched = sum(
        1 for i in range(n)
        if i < len(cb) and (
            (rmask[i] and cmask[start + i])
            or (not rmask[i] and not cmask[start + i] and rbody[i] == cb[i])
        )
    )
    ri = sum(1 for _ in MD.disasm(bytes(rbody[:n]), va))
    ci = sum(1 for _ in MD.disasm(bytes(cb), va))
    # Label this "comdat span", not "object size".  It INCLUDES the COMDAT's
    # trailing alignment nops, so it is 0-15 bytes larger than the code length
    # `rebrew test` reports as obj_size -- and quoting the two as if they were
    # the same ruler is how a round-196 note wrongly concluded that this script
    # compiles standalone (it does not; it builds the whole file, exactly as
    # CMake does).  Print the trimmed code length alongside it so a reader
    # cannot confuse them.  See docs/msvc6-c-shapes.md section 96.
    span = len(body) - start
    code_len = len(bytes(cb).rstrip(b"\x90"))
    print(f"0x{va:x} size {size}: section {si} +{start:#x}, "
          f"matched {matched}/{n} ({100.0 * matched / n:.1f}%), "
          f"matched-reloc {generous}/{n}, "
          f"instructions {ci} vs {ri}, comdat span {span}"
          + (f" (code {code_len})" if code_len != span else ""))

    # `matched` above is a FIXED-OFFSET compare, so one inserted byte makes every
    # later byte wrong.  On a large function it saturates near the first
    # divergence (gm_AllocSpieler reads 1,246/3689 while two thirds of its
    # instruction sequence agrees), and a climb against it converges on a
    # function that still has 178 hunks.  This second number is the aligned
    # count -- the gradient to climb.  See scripts/instr_diff.py --obj.
    import difflib
    import instr_diff

    mds = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    mds.skipdata = True
    ra = [b for b, _t in instr_diff.instructions(REFERENCE, va, size, mds)]
    # the whole COMDAT, not the target's size: a short object must not have its
    # tail cut off, and a long one's trailing pad is an insert hunk, not a
    # misalignment.  Same construction as `instr_diff.py --obj`.
    cm = bytearray(cmask)
    for k in range(min(n, len(cm))):
        if rmask[k]:
            cm[k] = 1
    ca = [b for b, _t in instr_diff.decode(bytes(body[start:]), cm[start:], va, mds)]
    sm = difflib.SequenceMatcher(a=ra, b=ca, autojunk=False)
    aligned = sum(i2 - i1 for tag, i1, i2, _j1, _j2 in sm.get_opcodes() if tag == "equal")
    print(f"  aligned {aligned}/{len(ra)} reference instructions "
          f"({100.0 * aligned / max(1, len(ra)):.1f}%)")
    if tmp is not None:
        print(f"  object: {obj}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
