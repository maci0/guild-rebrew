#!/usr/bin/env python3
"""Where does our compiled function's size diverge from the reference's?

The remaining functions are size problems before they are byte problems: byte
identity implies size identity, and `scripts/instr_diff.py` says *what kind* of
difference is left but not *where the length goes*.  For a function that
compiles +1 byte (or -11), this walks the instruction alignment and reports the
cumulative byte-length difference, so the sites that actually spend or save bytes
can be read off instead of guessed.

Usage:
    python3 scripts/sizediff.py 0x10018850
    python3 scripts/sizediff.py 0x10018850 --built build/server.dll -v
"""

from __future__ import annotations

import argparse
import difflib
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from instr_diff import BUILT, REFERENCE, instructions, mask, sections  # noqa: E402

import capstone  # noqa: E402

MD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


def load(path: Path, va: int, size: int):
    secs = sections(path)
    tva, tvs, tptr, trs = secs[".text"]
    m = mask(path, secs, va, size)
    raw = path.read_bytes()
    off = tptr + (va - tva - 0x10000000)
    body = raw[off : off + size]
    out = []
    for ins in MD.disasm(body, va):
        masked = bytes(0 if m[ins.address - va + k] else ins.bytes[k]
                       for k in range(ins.size))
        out.append((masked, ins))
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("va", type=lambda s: int(s, 0))
    ap.add_argument("--built", default=None)
    ap.add_argument("--size", type=int, default=None)
    ap.add_argument("--min-delta", type=int, default=1)
    args = ap.parse_args()

    import tomllib
    md = tomllib.loads((ROOT / "src/rebrew-functions.toml").read_text())
    size = args.size or md[f"SERVER.0x{args.va:08x}"]["size"]

    ref = load(REFERENCE, args.va, size)
    pat = load(Path(args.built or BUILT), args.va, size)
    print(f"0x{args.va:x} size {size}: reference {len(ref)} insns, "
          f"built {len(pat)} insns")

    sm = difflib.SequenceMatcher(None, [b for b, _ in ref], [b for b, _ in pat],
                                 autojunk=False)
    cum = 0
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        rlen = sum(ins.size for _, ins in ref[i1:i2])
        plen = sum(ins.size for _, ins in pat[j1:j2])
        step = plen - rlen
        # This tool is about SIZE: a hunk that neither spends nor saves bytes
        # is instr_diff's business, not its.
        if tag == "equal" or abs(step) < args.min_delta:
            cum += step
            continue
        cum += step
        print(f"\n  {tag}: ref[{i1}:{i2}] {rlen}B -> built[{j1}:{j2}] {plen}B "
              f"({step:+d}), running {cum:+d}")
        for _, ins in ref[i1:i2][:6]:
            print(f"      ref   {ins.address:08x} {ins.mnemonic:7s} {ins.op_str}")
        for _, ins in pat[j1:j2][:6]:
            print(f"      built {ins.address:08x} {ins.mnemonic:7s} {ins.op_str}")
    print(f"\ntotal: reference {sum(i.size for _, i in ref)}B, "
          f"built {sum(i.size for _, i in pat)}B, delta {cum:+d}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
