#!/usr/bin/env python3
"""How byte-identical is the built .text to the reference, really?

`rebrew verify` counts PROVEN as passed without a byte compare, and
`rebrew diff`'s positional count is meaningless once the link drifts, so
neither can answer "how far from byte-identical are we".  This can.

Two figures per range:

  raw     -- bytes equal at the same .text offset
  masked  -- bytes equal, or a byte the linker is allowed to fill in: every
             DIR32 slot the image's own base-relocation table lists, and every
             rel32 operand.  What is left is the part the compiler controls --
             opcodes, ModRM, register allocation, displacements, constants.

`masked == 100%` in a range means the code there is exactly the reference's
code, differing only where the linker patched an address in.  Whether the
addresses themselves land right is a separate question, answered by
`scripts/link_drift.py`: masked 100% plus drift 0 everywhere is byte identity.

Because drift is piecewise constant and shifts whole objects, a fixed-offset
comparison understates the game region.  Pass `--drift` (a `link_drift.py
--json` file, or the word `auto` to run it) and each tracked function is
compared at its own drifted offset.

Usage:
    python3 scripts/text_match.py                          # whole .text
    python3 scripts/text_match.py --drift auto             # drift-aware
    python3 scripts/text_match.py --region game -v         # worst offenders
"""

from __future__ import annotations

import json
import re
import struct
import subprocess
import sys
from pathlib import Path

import capstone as cs

ROOT = Path(__file__).resolve().parents[1]
REFERENCE = ROOT / "original/Server/server.dll"
BUILT = ROOT / "build/split_poc.dll"
IMAGE_LO, IMAGE_HI = 0x10000000, 0x10200000
BRANCHES = {
    "call", "jmp", "jz", "jnz", "je", "jne", "jl", "jle", "jg", "jge",
    "jb", "jbe", "ja", "jae", "js", "jns", "jo", "jno", "jp", "jnp",
    "jcxz", "loop", "loope", "loopne",
}


def pe_sections(path) -> dict:
    d = Path(path).read_bytes()
    e = struct.unpack_from("<I", d, 0x3C)[0]
    nsec = struct.unpack_from("<H", d, e + 6)[0]
    opt = struct.unpack_from("<H", d, e + 20)[0]
    base = struct.unpack_from("<I", d, e + 24 + 28)[0]
    off = e + 24 + opt
    out = {"__base__": base}
    for i in range(nsec):
        s = d[off + i * 40 : off + i * 40 + 40]
        name = s[:8].rstrip(b"\0").decode()
        vs, va, rs, pr = struct.unpack_from("<IIII", s, 8)
        out[name] = (base + va, d[pr : pr + rs], vs, pr)
    return out


def image_mask(path, body, va) -> bytearray:
    """1 = the linker fills this byte in, so do not compare it."""
    mask = bytearray(len(body))
    secs = pe_sections(path)
    base = secs["__base__"]
    if ".reloc" in secs:
        _rva, blk, _vs, _pr = secs[".reloc"]
        i = 0
        while i + 8 <= len(blk):
            page, size = struct.unpack_from("<II", blk, i)
            if size < 8:
                break
            for j in range(i + 8, min(i + size, len(blk)), 2):
                ent = struct.unpack_from("<H", blk, j)[0]
                if ent >> 12 == 3:  # IMAGE_REL_BASED_HIGHLOW
                    o = (base + page + (ent & 0xFFF)) - va
                    for k in range(o, o + 4):
                        if 0 <= k < len(mask):
                            mask[k] = 1
            i += size
    md = cs.Cs(cs.CS_ARCH_X86, cs.CS_MODE_32)
    md.detail = True
    off = 0
    while off < len(body):
        started = False
        # A linear sweep stops at the first undecodable byte, and .text holds
        # jump tables; resume one byte on instead of losing the rest.
        for insn in md.disasm(body[off:], va + off):
            started = True
            rel = insn.mnemonic in BRANCHES
            for op in insn.operands:
                if op.type == cs.x86.X86_OP_IMM:
                    addr_like = (
                        rel
                        or IMAGE_LO <= (op.imm & 0xFFFFFFFF) < IMAGE_HI
                        or op.imm == 0
                    )
                elif op.type == cs.x86.X86_OP_MEM:
                    addr_like = (
                        op.mem.base == cs.x86.X86_REG_INVALID
                        and op.mem.index == cs.x86.X86_REG_INVALID
                        and (
                            IMAGE_LO <= (op.mem.disp & 0xFFFFFFFF) < IMAGE_HI
                            or op.mem.disp == 0
                        )
                    )
                else:
                    continue
                if addr_like:
                    lo = max(0, insn.size - max(op.size, 1))
                    for k in range(lo, insn.size):
                        mask[insn.address - va + k] = 1
            off = insn.address - va + insn.size
        if not started:
            off += 1
    return mask


def boundaries() -> list[tuple[int, int, str, str]]:
    """(va, size, name, region) covering .text, CRT ranges first."""
    out = []
    catalog = ROOT / "build/split_poc/map_full.json"
    if catalog.exists():
        for e in json.loads(catalog.read_text())["matched"]:
            out.append((int(e["va"], 16), e["size"], e["name"], "crt"))
    for line in (ROOT / "src/rebrew-functions.toml").read_text().splitlines():
        m = re.match(r'\["SERVER\.(0x[0-9a-fA-F]+)"\]', line)
        if m:
            out.append((int(m.group(1), 16), 0, "", "game"))
    out.sort()
    merged = []
    for i, (va, size, name, region) in enumerate(out):
        nxt = out[i + 1][0] if i + 1 < len(out) else IMAGE_HI
        merged.append((va, max(size, nxt - va), name or f"sub_{va:x}", region))
    return merged


def drift_table(spec: str) -> list[tuple[int, int, str, int]]:
    if spec == "auto":
        spec = "/tmp/link_drift.json"
        r = subprocess.run(
            [sys.executable, str(ROOT / "scripts/link_drift.py"),
             "--built", str(BUILT), "--json"],
            capture_output=True, text=True, cwd=ROOT,
        )
        if r.returncode:
            sys.exit(f"link_drift.py failed:\n{r.stderr[-2000:]}")
        Path(spec).write_text(r.stdout)
    d = json.loads(Path(spec).read_text())
    return [
        (int(f["va"], 16), f["size"], f["name"], f["drift"])
        for f in d["functions"]
    ]


def main() -> int:
    argv = list(sys.argv[1:])
    value_flags = ("--region", "--drift", "--built")
    opt = {}
    for flag in value_flags:
        if flag in argv:
            i = argv.index(flag)
            opt[flag] = argv[i + 1]
            del argv[i : i + 2]
    built_path = Path(opt.get("--built", BUILT))
    verbose = "-v" in argv

    rva, rbody, rvs, _ = pe_sections(REFERENCE)[".text"]
    bva, bbody, bvs, _ = pe_sections(built_path)[".text"]
    assert rva == bva, (hex(rva), hex(bva))
    n = min(rvs, len(rbody))
    rmask = image_mask(str(REFERENCE), rbody[:n], rva)
    bmask = image_mask(str(built_path), bbody[:bvs], bva) if "--drift" in opt else None

    def score(lo, hi, shift=0):
        raw = ok = tot = 0
        for i in range(lo, hi):
            j = i + shift
            if i >= n or j < 0 or j >= len(bbody):
                tot += 1
                continue
            tot += 1
            if rbody[i] == bbody[j]:
                raw += 1
            if rmask[i] or (bmask is not None and bmask[j]) or rbody[i] == bbody[j]:
                ok += 1
        return raw, ok, tot

    raw, ok, tot = score(0, n)
    print(f"whole .text  raw {raw}/{tot} = {100.0 * raw / tot:.2f}%   "
          f"masked {ok}/{tot} = {100.0 * ok / tot:.2f}%")
    print(f"built .text 0x{bvs:x}  reference 0x{rvs:x}  delta {bvs - rvs:+d}")

    if "--drift" in opt:
        rows = []
        for va, size, name, drift in drift_table(opt["--drift"]):
            lo = va - rva
            hi = min(lo + size, n)
            if lo >= n or hi <= lo:
                continue
            r, o, t = score(lo, hi, drift)
            rows.append((o / t if t else 1.0, name, "game", t, r, o, va))
    else:
        rows = []
        for va, size, name, region in boundaries():
            lo = va - rva
            hi = min(lo + size, n)
            if lo >= n or hi <= lo:
                continue
            r, o, t = score(lo, hi)
            rows.append((o / t if t else 1.0, name, region, t, r, o, va))

    order = ["crt", "game"] if "--drift" not in opt else ["game"]
    for region in order:
        rs = [x for x in rows if x[2] == region]
        tt = sum(x[3] for x in rs)
        rr = sum(x[4] for x in rs)
        oo = sum(x[5] for x in rs)
        if tt:
            print(f"{region:5s}  raw {100.0 * rr / tt:6.2f}%   "
                  f"masked {100.0 * oo / tt:6.2f}%   "
                  f"({tt} bytes, {len(rs)} ranges, {tt - oo} differ)")

    if opt.get("--region"):
        rows = [x for x in rows if x[2] == opt["--region"]]
    print(f"{'masked':>7s}  {'bytes':>7s}  {'differ':>7s}  region  name")
    for frac, name, region, t, r, o, va in sorted(rows)[: 60 if verbose else 15]:
        print(f"{100 * frac:6.1f}%  {t:7d}  {t - o:7d}  {region:5s}  "
              f"{name}  @0x{va:x}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
