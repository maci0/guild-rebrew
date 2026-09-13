#!/usr/bin/env python3
"""What kind of difference is left in one function?

The remaining work is 19 non-byte-matched functions, and each one's residual is
either

* **kind-different** — instructions the reference has and we do not (or the
  reverse), i.e. the C source has a different shape, or
* **operand-different** — the same instruction kinds in the same order, with a
  register or an address spelled differently, i.e. an allocator/schedule
  decision.

The distinction decides whether to read the disassembly or to probe spellings,
and the existing measurements blur it two ways: a raw mnemonic multiset counts
*absolute addresses* as different instruction kinds, and a fixed-offset byte
count loses everything after the first size difference.  So this aligns the two
instruction streams (LCS over relocation-masked bytes), reports the hunks with
each differing pair classified, and compares kind multisets with every absolute
address collapsed.

Usage:
    python3 scripts/instr_diff.py 0x1000e140                 # built vehicle
    python3 scripts/instr_diff.py 0x1000e140 --built build/server.dll -v
"""

from __future__ import annotations

import argparse
import difflib
import re
import struct
import sys
from collections import Counter
from pathlib import Path

import capstone

ROOT = Path(__file__).resolve().parents[1]
REFERENCE = ROOT / "original/Server/server.dll"
BUILT = ROOT / "build/split_poc.dll"
IMAGE_BASE = 0x10000000
BRANCHES = {
    "call", "jmp", "jz", "jnz", "je", "jne", "jl", "jle", "jg", "jge",
    "jb", "jbe", "ja", "jae", "js", "jns", "jo", "jno", "jp", "jnp",
    "jcxz", "loop", "loope", "loopne",
}
#: collapse registers and absolute addresses, so one instruction *kind* survives
#: the difference between `mov [esi+4],1` and `mov [edi+4],1`
REGS = re.compile(r"\b(eax|ebx|ecx|edx|esi|edi|ebp|esp|al|bl|cl|dl|ah|bh|ch|dh|"
                  r"ax|bx|cx|dx|si|di|bp|sp)\b")
ABSR = re.compile(r"0x1[0-9a-f]{7}")


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


def mask(path: Path, secs: dict, va: int, size: int) -> bytearray:
    """1 = the linker fills this byte in (base relocation slot)."""
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


def decode(body: bytes, m: bytearray, va: int, md) -> list[tuple[bytes, str]]:
    out = []
    for insn in md.disasm(body, va):
        i = insn.address - va
        b = bytes(0 if (i + k) < len(m) and m[i + k] else x for k, x in enumerate(insn.bytes))
        if insn.mnemonic in BRANCHES:  # targets move with the layout
            b = b[:1] + bytes(len(b) - 1)
        out.append((b, f"{insn.mnemonic} {insn.op_str}"))
    return out


def instructions(path: Path, va: int, size: int, md, extra: bytearray | None = None) -> list[tuple[bytes, str]]:
    secs = sections(path)
    tva, tvs, tptr, trs = secs[".text"]
    off = tptr + (va - tva - IMAGE_BASE)
    body = path.read_bytes()[off : off + size]
    m = mask(path, secs, va, size)
    if extra is not None:  # the union: a slot either image relocates is masked
        for i in range(min(len(m), len(extra))):
            if extra[i]:
                m[i] = 1
    return decode(body, m, va, md)


def object_instructions(obj: Path, refmask: bytearray, va: int, md,
                        size: int | None = None) -> list[tuple[bytes, str]]:
    """The same decode for a single compiled object's COMDAT, so a probe can be
    scored without relinking the whole vehicle.

    The COMDAT is picked the way probe_function.py picks it: the symbol the
    vehicle map gives for this VA, else the section closest to the target size.
    ``refmask`` is the reference's relocation slots -- a slot either side
    relocates is masked, because an object's operand holds an addend and the
    reference's holds the resolved address.
    """
    sys.path.insert(0, str(ROOT / "scripts"))
    from split_coff import Coff  # noqa: E402

    coff = Coff(obj.read_bytes())
    wanted = None
    mapfile = ROOT / "build/split_poc.map"
    if mapfile.exists():
        for line in mapfile.read_text().splitlines():
            m = re.match(r"^\s+0001:[0-9a-f]{8}\s+(.*?)\s+([0-9a-f]{8})\s+(\S.*)$", line)
            if m and int(m.group(2), 16) == va:
                wanted = m.group(1).split()[0]
    best = None
    for si, s in enumerate(coff.sections):
        if not s["name"].startswith(b".text"):
            continue
        body = coff.section_body(si)
        name = next((sym["name"] for sym in coff.symbols
                     if sym and sym["section"] == si + 1 and sym["storage_class"] == 2), None)
        key = (0 if (wanted and name == wanted) else 1,
               abs(len(body) - (size or len(body))))
        if best is None or key < best[0]:
            best = (key, si, body)
    if best is None:
        sys.exit(f"no .text COMDAT in {obj}")
    si, body = best[1], best[2]
    m = bytearray(len(body))
    for r, _sym, _typ in coff.section_relocs(si):
        for k in range(r, min(r + 4, len(body))):
            m[k] = 1
    for k in range(min(len(body), len(refmask))):
        if refmask[k]:
            m[k] = 1
    return decode(body, m, va, md)


def kind(text: str) -> str:
    """Fold registers and absolute addresses, so one instruction *kind*
    survives the difference between `mov [esi+4],1` and `mov [edi+4],1`.

    An object's operand is its addend (0 at a relocation slot, see
    ``object_instructions``) where the reference's is the resolved address, so
    those fold onto ADDR too -- without it every relocated global reads as a
    kind the other side does not have.
    """
    text = ABSR.sub("ADDR", REGS.sub("R", text))
    text = text.replace("[0]", "[ADDR]").replace("[0 + ", "[ADDR + ")
    if text.endswith(" 0"):
        text = text[:-2] + " ADDR"
    return text


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("va", help="function VA, e.g. 0x1000e140")
    ap.add_argument("--built", default=str(BUILT))
    ap.add_argument("--obj", default=None,
                    help="score one compiled object's COMDAT instead of the vehicle")
    ap.add_argument("--size", type=lambda s: int(s, 0), default=None,
                    help="function size (default: from src/rebrew-functions.toml)")
    ap.add_argument("-v", "--verbose", action="store_true")
    args = ap.parse_args()
    va = int(args.va, 0)
    size = args.size
    if size is None:
        text = (ROOT / "src/rebrew-functions.toml").read_text()
        m = re.search(rf'\["SERVER\.0x{va:08x}"\]\n(?:.*\n)*?size\s*=\s*(\d+)', text)
        if not m:
            sys.exit("pass --size (no metadata entry for that VA)")
        size = int(m.group(1))

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    rmask = mask(REFERENCE, sections(REFERENCE), va, size)
    if args.obj:
        r = instructions(REFERENCE, va, size, md)
        b = object_instructions(Path(args.obj), rmask, va, md, size)
    else:
        bmask = mask(Path(args.built), sections(Path(args.built)), va, size)
        union = bytearray(1 if (rmask[i] or bmask[i]) else 0 for i in range(size))
        r = instructions(REFERENCE, va, size, md, union)
        b = instructions(Path(args.built), va, size, md, union)
    ra = [x[0] for x in r]
    ba = [x[0] for x in b]
    sm = difflib.SequenceMatcher(a=ra, b=ba, autojunk=False)
    ops = sm.get_opcodes()
    matched = sum(i2 - i1 for tag, i1, i2, _j1, _j2 in ops if tag == "equal")
    print(f"{va:#x} size {size}: reference {len(r)} instructions, built {len(b)}")
    print(f"  aligned match: {matched}/{len(r)} reference instructions "
          f"({100.0 * matched / max(1, len(r)):.1f}%), "
          f"{matched}/{len(b)} built ({100.0 * matched / max(1, len(b)):.1f}%)")
    hunks = [op for op in ops if op[0] != "equal"]
    reg_only = kind_only = other = 0
    print(f"  {len(hunks)} hunks")
    for tag, i1, i2, j1, j2 in hunks:
        if tag == "equal":
            continue
        if tag == "replace" and i2 - i1 == j2 - j1:
            pairs = list(zip(range(i1, i2), range(j1, j2)))
            if all(kind(r[i][1]) == kind(b[j][1]) for i, j in pairs):
                reg_only += 1
            else:
                kind_only += 1
        else:
            other += 1
        if args.verbose or len(hunks) <= 8:
            print(f"    {tag} ref[{i1}:{i2}] built[{j1}:{j2}]")
            for k in range(i1, min(i2, i1 + 3)):
                print(f"      ref   {r[k][1]}")
            for k in range(j1, min(j2, j1 + 3)):
                print(f"      built {b[k][1]}")
    print(f"  hunks: {reg_only} same-kind (registers/addresses), {kind_only} different-kind, "
          f"{other} insert/delete")

    ca = Counter(kind(t) for _, t in r)
    cb = Counter(kind(t) for _, t in b)
    missing = ca - cb
    extra = cb - ca
    print(f"  kind multiset: {sum(missing.values())} reference-only, "
          f"{sum(extra.values())} built-only (addresses and registers collapsed)")
    for k, n in missing.most_common(6 if not args.verbose else 40):
        print(f"    ref-only x{n}: {k}")
    for k, n in extra.most_common(6 if not args.verbose else 40):
        print(f"    built-only x{n}: {k}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
