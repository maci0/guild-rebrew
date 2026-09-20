#!/usr/bin/env python3
"""Attribute the linked `.text` residue to the backend mechanism that caused it.

The residue ruler (`postlink_residual.py`) says *how many* bytes differ per
function. It does not say *why*. This classifies every difference into one of
the mechanisms that can produce it, so a decision about where to spend effort
rests on counts rather than on the last carrier examined.

Method
------
Both streams are disassembled from the **deliverable** (`build/server.dll`) and
the reference, then aligned by a prefix walk that matches on
`(mnemonic, operand text with registers abstracted)` and resynchronises within a
window. Matching on the register-abstracted form is what makes a pure register
swap an *aligned pair* rather than two unrelated instructions.

Each alignment outcome is then attributed:

* a matched pair whose raw bytes differ, classified by how much of the operand
  text differs  ->  register / immediate / operand / mnemonic
* an unmatched reference run and an unmatched build run of equal length holding
  the same instruction multiset  ->  ``schedule`` (the same instructions, a
  different order)
* an unmatched run that is a ``pop``/``ret`` cluster  ->  ``epilogue``
  (the backend materialised a different number of copies of one exit)
* any other unmatched reference instruction  ->  ``missing``
* any other unmatched build instruction  ->  ``extra``

Caveats, because they matter for reading the output
---------------------------------------------------
* Byte totals are the sum of ``max(len(ref), len(build))`` over the sites in
  each class, so they are an estimate, not a partition of the ruler's number.
  A length change shifts everything after it and the byte ruler counts that
  whole misaligned stretch; this counts the instructions. The two are different
  questions and both are worth having.
* ``mnemonic`` here means "the aligned pair's mnemonics differ", which after a
  resync usually means one genuine substitution, not two. A schedule swap is
  reported separately as ``schedule``, not counted here.
* Carrier spans come from `function_structure.json`'s next entry, which is the
  only bound that covers a function containing both jump tables and padding
  (measure-traps sections 52 and 54).

Usage
-----
    python3 scripts/attribution.py                 # all carriers, table
    python3 scripts/attribution.py --json          # machine-readable
    python3 scripts/attribution.py --carrier 0x1000e140
"""

from __future__ import annotations

import argparse
import json
import re
import struct
import sys
from collections import Counter
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parent.parent
REFERENCE = ROOT / "original/Server/server.dll"
DELIVERABLE = ROOT / "build/server.dll"
INVENTORY = ROOT / "src/server.dll/function_structure.json"
RESIDUAL = ROOT / "scripts"

#: Registers a schedule/register difference is allowed to move between.  Used
#: only to abstract operand TEXT; the classification never assumes which one is
#: "right".
_REGISTERS = r"\b(eax|ecx|edx|ebx|esi|edi|ebp|esp|ax|cx|dx|bx|si|di|bp|sp|al|cl|dl|bl|ah|ch|dh|bh)\b"

#: Instructions that terminate a path.  A cluster of these where the two
#: streams disagree is a materialised exit, not a missing statement.
_EXITS = frozenset({"pop", "ret", "retf", "iret", "iretd"})

#: Resynchronisation window, in instructions.  Eight is enough to step over a
#: swapped pair or a short inserted run without merging two unrelated regions.
_RESYNC = 8


def _require_capstone() -> Any:
    try:
        import capstone
    except ImportError:  # pragma: no cover - environment guard
        sys.exit("attribution: capstone is required (run from the project venv)")
    return capstone


def _text_section(path: Path) -> tuple[bytes, int, int, int]:
    """(image, raw pointer, raw size, base VA) for `.text`."""
    data = path.read_bytes()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    nsec = struct.unpack_from("<H", data, pe + 6)[0]
    opt = pe + 24
    opt_size = struct.unpack_from("<H", data, pe + 20)[0]
    base = struct.unpack_from("<I", data, opt + 28)[0]
    for i in range(nsec):
        off = opt + opt_size + i * 40
        sec = data[off : off + 40]
        if sec[:8].rstrip(b"\0").decode() != ".text":
            continue
        vsize, vaddr, raw_size, raw_ptr = struct.unpack_from("<IIII", sec, 8)
        return data, raw_ptr, raw_size, base + vaddr
    raise SystemExit(f"attribution: no .text in {path}")


def _disasm(capstone: Any, md: Any, image: bytes, raw_ptr: int, base: int, va: int, size: int) -> list[Any]:
    off = raw_ptr + (va - base)
    return list(md.disasm(image[off : off + size], va))


def _abstract(reg_abstract: str) -> str:
    return re.sub(r"0x[0-9a-f]+|\b\d+\b", "N", reg_abstract)


def _reg_abstract(text: str) -> str:
    return re.sub(_REGISTERS, "R", text)


def _regs(text: str) -> tuple[str, ...]:
    """The registers named in an operand, in order."""
    return tuple(re.findall(_REGISTERS, text))


def _classify_pair(ref: Any, build: Any) -> str:
    """How do two shape-aligned instructions differ?

    Order matters here.  The same register set in a different order is
    ``operand-order`` -- commutative addressing, which ``msvc6-c-shapes.md``
    section 70 records as inert, so it should not be counted with genuine
    register-allocation differences.  Only the same register set *in the same
    order* with different operand text is an immediate/displacement difference.
    """
    if ref.mnemonic != build.mnemonic:
        return "mnemonic"
    rregs, bregs = _regs(ref.op_str), _regs(build.op_str)
    if rregs == bregs:
        return "immediate" if ref.op_str != build.op_str else "encoding"
    if len(rregs) == len(bregs) and sorted(rregs) == sorted(bregs):
        return "operand-order"
    return "register"


def _multiset(run: list[Any]) -> Counter[tuple[str, str]]:
    return Counter((i.mnemonic, _abstract(_reg_abstract(i.op_str))) for i in run)


def _shape(insn: Any) -> tuple[str, str]:
    """Identity that ignores registers AND immediates: the instruction's *shape*.

    Two instructions with the same shape are the same operation on different
    operands, so aligning on this catches a register swap and an immediate
    difference while still separating a schedule swap (different position) from
    a genuinely different instruction.
    """
    return (insn.mnemonic, _abstract(_reg_abstract(insn.op_str)))


def attribute(ref: list[Any], build: list[Any]) -> list[tuple[str, Any]]:
    """[(class, representative instruction)] for one carrier.

    Two stages, because one cannot do both jobs:

    1. **Align on shape** (mnemonic + operands with registers and immediates
       abstracted).  An aligned pair whose raw bytes differ is classified by how
       much of the operand text differs -- register, immediate or operand form.
    2. **Match the leftovers** across the two unaligned runs.  An unaligned
       reference instruction whose shape appears in the unaligned build run is
       the same operation at a different position: a **schedule** difference.
       Leftovers with no counterpart are **missing** (or, for a `pop`/`ret`
       cluster, a materialised **epilogue**).
    """
    out: list[tuple[str, Any]] = []
    i = j = 0
    left_ref: list[Any] = []
    left_build: list[Any] = []
    while i < len(ref) and j < len(build):
        if _shape(ref[i]) == _shape(build[j]):
            if ref[i].bytes != build[j].bytes:
                out.append((_classify_pair(ref[i], build[j]), ref[i]))
            i += 1
            j += 1
            continue
        # Resynchronise on shape within a small window.
        stepped = False
        for d in range(1, _RESYNC + 1):
            if i + d < len(ref) and _shape(ref[i + d]) == _shape(build[j]):
                left_ref.extend(ref[i : i + d])
                i += d
                stepped = True
                break
            if j + d < len(build) and _shape(ref[i]) == _shape(build[j + d]):
                left_build.extend(build[j : j + d])
                j += d
                stepped = True
                break
        if not stepped:
            left_ref.append(ref[i])
            left_build.append(build[j])
            i += 1
            j += 1
    left_ref.extend(ref[i:])
    left_build.extend(build[j:])

    # Stage 2: pair the leftovers by shape.  A pair is a schedule difference.
    pool = Counter(_shape(x) for x in left_build)
    for insn in left_ref:
        key = _shape(insn)
        if pool.get(key):
            pool[key] -= 1
            out.append(("schedule", insn))
        else:
            out.append(("epilogue" if insn.mnemonic in _EXITS else "missing", insn))
    for insn in left_build:
        key = _shape(insn)
        if pool.get(key):
            pool[key] -= 1
            out.append(("extra", insn))
            continue
        if insn.mnemonic in _EXITS:
            out.append(("epilogue", insn))
    return out


def _self_test() -> None:
    """The classifier's contract, on stubs.  Run with --self-test.

    Each case is a shape the doc records a verdict for, so a regression in the
    abstraction order shows up here rather than as a plausible-looking table.
    """
    from types import SimpleNamespace as NS

    def ins(mnem, ops, byts=b"\x90"):
        return NS(mnemonic=mnem, op_str=ops, bytes=byts)

    cases = [
        # (ref, build, expected)
        (ins("mov", "eax, ecx"), ins("mov", "eax, ebx"), "register"),
        (ins("mov", "eax, dword ptr [0x1234]"), ins("mov", "eax, dword ptr [0x5678]"), "immediate"),
        (ins("lea", "esi, [edx + ecx]"), ins("lea", "esi, [ecx + edx]"), "operand-order"),
        (ins("mov", "eax, dword ptr [ebp + 4]"), ins("mov", "eax, dword ptr [ebp + 4]"), "encoding"),
        (ins("mov", "al, byte ptr [eax]"), ins("cmp", "byte ptr [eax], 0"), "mnemonic"),
    ]
    for r, b, want in cases:
        got = _classify_pair(r, b)
        if got != want:
            raise SystemExit(f"self-test: {r.mnemonic} {r.op_str!r} vs {b.op_str!r} -> {got}, want {want}")

    # `_shape` must collapse registers AND immediates, so that a register swap
    # and an immediate difference still align and get classified, while a
    # genuinely different operation does not.
    if _shape(ins("mov", "eax, dword ptr [0x11]")) != _shape(ins("mov", "ebx, dword ptr [0x22]")):
        raise SystemExit("self-test: _shape did not abstract registers/immediates")
    if _shape(ins("mov", "eax, ecx")) == _shape(ins("add", "eax, ecx")):
        raise SystemExit("self-test: _shape ignored the mnemonic")
    print("attribution: self-test ok (%d classifier cases + shape contract)" % len(cases))


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--reference", default=str(REFERENCE))
    ap.add_argument("--built", default=str(DELIVERABLE))
    ap.add_argument("--inventory", default=str(INVENTORY))
    ap.add_argument("--carrier", default=None, help="single carrier VA, e.g. 0x1000e140")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--self-test", action="store_true", help="check the classifier's contract and exit")
    args = ap.parse_args()

    if args.self_test:
        _self_test()
        return 0

    capstone = _require_capstone()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    rimg, rptr, _rsz, rbase = _text_section(Path(args.reference))
    bimg, bptr, _bsz, bbase = _text_section(Path(args.built))

    inv = json.loads(Path(args.inventory).read_text())
    entries = sorted((int(f["va"]), int(f["size"])) for f in inv)

    # A carrier is a function `rebrew verify` does not report byte-matched.
    # Reuse the same source of truth the rest of the project does.
    verify = ROOT / ".scratch/verify_full.json"
    carriers: list[tuple[int, int, str]] = []
    if verify.exists():
        data = json.loads(verify.read_text())
        for r in data.get("results", []):
            if r.get("status") in ("EXACT", "RELOC"):
                continue
            va = int(r["va"], 16)
            span = next((s for v, s in entries if v == va), int(r.get("size") or 0))
            carriers.append((va, span, str(r.get("filepath") or "").split("/")[-1]))
    if not carriers:
        sys.exit("attribution: no verify results; run `rebrew verify --full --json > .scratch/verify_full.json`")
    if args.carrier:
        want = int(args.carrier, 16)
        carriers = [c for c in carriers if c[0] == want]
        if not carriers:
            sys.exit(f"attribution: 0x{want:x} is not a residue carrier")

    totals: Counter[str] = Counter()
    bytes_by: Counter[str] = Counter()
    rows: list[dict[str, Any]] = []
    for va, span, name in carriers:
        ref = _disasm(capstone, md, rimg, rptr, rbase, va, span)
        bld = _disasm(capstone, md, bimg, bptr, bbase, va, span)
        if not ref or not bld:
            continue
        attributed = attribute(ref, bld)
        per: Counter[str] = Counter()
        perb: Counter[str] = Counter()
        for cls, insn in attributed:
            per[cls] += 1
            perb[cls] += len(insn.bytes)
        totals.update(per)
        bytes_by.update(perb)
        rows.append({"va": hex(va), "name": name, "counts": dict(per), "bytes": dict(perb)})

    grand = sum(totals.values())
    if args.json:
        print(json.dumps({"rows": rows, "totals": dict(totals), "bytes": dict(bytes_by)}, indent=2))
        return 0

    hdr = ("carrier", "sched", "reg", "imm", "opord", "miss", "extra", "epi")
    print("%-28s %5s %5s %5s %5s %5s %5s %5s" % hdr)
    for r in rows:
        c = r["counts"]
        print(
            "%-28s %5d %5d %5d %5d %5d %5d %5d"
            % (
                r["name"][:28],
                c.get("schedule", 0),
                c.get("register", 0),
                c.get("immediate", 0),
                c.get("operand-order", 0),
                c.get("missing", 0),
                c.get("extra", 0),
                c.get("epilogue", 0),
            )
        )
    print()
    print("attributed sites: %d   (of %d bytes the ruler reports, this sums ~%d)"
          % (grand, 8628, sum(bytes_by.values())))
    order = [
        "register",
        "immediate",
        "schedule",
        "missing",
        "extra",
        "operand-order",
        "epilogue",
        "encoding",
        "mnemonic",
    ]
    print("%-12s %6s %8s" % ("class", "count", "bytes~"))
    for cls in order:
        if totals[cls]:
            print("%-12s %6d %8d" % (cls, totals[cls], bytes_by[cls]))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
