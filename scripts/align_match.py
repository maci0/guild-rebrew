#!/usr/bin/env python3
"""Alignment-corrected byte-match metric for the non-exact functions.

Why this exists: `rebrew diff` aligns the target and candidate instruction
streams *positionally*.  One inserted or deleted instruction desyncs that
alignment for the rest of the function, so its `structural` count explodes and
its `exact` count collapses even when the two streams are almost the same
program.  Measured 2026-09-13 (round 25):

    cm_ProcessCommandQueue   rebrew diff 15.6% positionally   88.3% aligned
    ls_LoadBuildingEntityState  rebrew diff 34.0%            88.8% aligned
    srv_LoadBuf              24.8%                           75.7%
    ServerMainThread         81.7%                           86.9%

This script instead computes the longest common subsequence of *normalized
instruction text*, which is the largest number of target instructions that can
be matched, in order, by an instruction that will be byte-identical in the
linked image.  Normalization lowercases, drops `;` comments and segment
prefixes, masks bracketed symbol operands and any number >= 0x10000 (image
addresses / relocations), canonicalises small immediates to decimal, and keeps
only the mnemonic for branches and calls (their target is a relocation).  It
deliberately keeps register names and small displacements, so a frame-offset
or register-role difference is still counted as a mismatch.

Caveats: the candidate for a few functions comes back much shorter than the
target (CrashDump, gm_AllocGebaeude, vfs_OpenStream) because objdump splits the
COMDAT differently; those rows are printed with `!` and their percentage is
meaningless.  Immediates >= 0x10000 are masked, so a genuine large-constant
difference would be missed.

Usage:
    python3 scripts/align_match.py            # all non-exact functions
    python3 scripts/align_match.py --va 0x1000aac0
    python3 scripts/align_match.py --json
"""

from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
OBJ = ROOT / ".scratch" / "asmprobe" / "align_match.obj"

REGS = {
    "eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "esp",
    "ax", "bx", "cx", "dx", "si", "di", "bp", "sp",
    "al", "bl", "cl", "dl", "ah", "bh", "ch", "dh",
    "st", "st0", "st1", "st2", "st3",
}


def _bracket(match: re.Match) -> str:
    parts = re.split(r"([a-z_][a-z0-9_]*)", match.group(1))
    out = []
    for part in parts:
        if re.fullmatch(r"[a-z_][a-z0-9_]*", part) and part not in REGS:
            out.append("#")
        else:
            out.append(part)
    return "[" + "".join(out) + "]"


def _num(match: re.Match) -> str:
    tok = match.group(0)
    value = int(tok, 16) if tok.lower().startswith("0x") else int(tok)
    return "#" if value >= 0x10000 else str(value)


def normalize(text: str) -> str:
    s = text.lower()
    s = re.sub(r";.*$", "", s)
    s = re.sub(r"\b(ds|es|cs|ss|fs|gs):", "", s)
    s = re.sub(r"\[([^\]]*)\]", _bracket, s)
    s = re.sub(r"0x[0-9a-f]+|-?\d+", _num, s)
    s = re.sub(r"\s+", " ", s).strip()
    mnemonic = s.split(" ")[0]
    if mnemonic.startswith("j") or mnemonic in ("call", "loop"):
        return mnemonic
    return s.replace(" ", "").replace(",", "")


def target_instrs(va: str, size: int) -> list[str]:
    out = subprocess.run(
        ["rebrew", "asm", va, "--size", str(size)],
        cwd=ROOT, capture_output=True, text=True, timeout=900,
    ).stdout
    res = []
    for line in out.splitlines():
        m = re.match(r"\s+0x[0-9a-f]+:\s+[0-9a-f ]+?\s{2,}(\S+)\s*(.*)$", line)
        if m:
            res.append(normalize(m.group(1) + " " + m.group(2)))
    return res


def candidate_instrs(rel_path: str, cflags: str, symbol: str) -> list[str] | None:
    OBJ.parent.mkdir(parents=True, exist_ok=True)
    cmd = ["rebrew-cmake-cl", "/nologo", "/c", *cflags.split(),
           "/MT", "/D", "_WIN32_WINNT=0x0400",
           "/I", "src/server.dll", "/I", "references/zlib-1.1.3",
           "/Fo.scratch/asmprobe/align_match.obj", "src/server.dll/" + rel_path]
    subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, timeout=900)
    out = subprocess.run(["objdump", "-d", "-Mintel", str(OBJ)],
                         cwd=ROOT, capture_output=True, text=True).stdout
    blocks: list[tuple[str, list[str]]] = []
    cur: list[str] | None = None
    for line in out.splitlines():
        m = re.match(r"^[0-9a-f]+ <(\S+)>:", line)
        if m:
            cur = []
            blocks.append((m.group(1), cur))
            continue
        if cur is None:
            continue
        m2 = re.match(r"\s+[0-9a-f]+:\t[0-9a-f ]+\t(.+)$", line)
        if m2:
            cur.append(normalize(m2.group(1)))
    for name, ins in blocks:
        if name == symbol:
            return ins
    base = symbol.strip("_").split("@")[0].lower()
    for name, ins in blocks:
        if base in name.lower():
            return ins
    return None


def lcs(a: list[str], b: list[str]) -> int:
    n, m = len(a), len(b)
    prev = [0] * (m + 1)
    for i in range(1, n + 1):
        cur = [0] * (m + 1)
        ai = a[i - 1]
        for j in range(1, m + 1):
            if ai == b[j - 1]:
                cur[j] = prev[j - 1] + 1
            else:
                cur[j] = prev[j] if prev[j] >= cur[j - 1] else cur[j - 1]
        prev = cur
    return prev[m]


def load_cflags() -> dict[str, str]:
    text = (ROOT / "src" / "rebrew-functions.toml").read_text()
    blocks = dict(re.findall(
        r'\["SERVER\.(0x[0-9a-fA-F]+)"\]\n((?:[a-z_]+ = .*\n?)*)', text))
    out = {}
    for va, body in blocks.items():
        m = re.search(r'cflags = "(.*?)"', body)
        out[va] = m.group(1) if m else "/O2 /Gd"
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--va", help="only this function")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--all", action="store_true",
                    help="include byte-exact functions too")
    args = ap.parse_args()

    results = json.loads((ROOT / "db" / "verify_results.json").read_text())["results"]
    cflags = load_cflags()
    rows = []
    for r in results:
        va = r["va"]
        if args.va and va.lower() != args.va.lower():
            continue
        exact = r.get("match_percent", 0) == 100.0 and not r.get("delta")
        if exact and not args.all:
            continue
        tm = target_instrs(va, r["size"])
        cm = candidate_instrs(r["filepath"], cflags.get(va, "/O2 /Gd"), r["symbol"])
        if cm is None:
            rows.append((r["name"], va, len(tm), 0, 0, False))
            continue
        matched = lcs(tm, cm)
        reliable = len(cm) >= 0.5 * len(tm)
        rows.append((r["name"], va, len(tm), len(cm), matched, reliable))
    rows.sort(key=lambda x: -(x[4] / x[2] if x[2] else 0))
    if args.json:
        print(json.dumps([
            {"name": n, "va": va, "target_instrs": t, "cand_instrs": c,
             "identical_in_order": m, "reliable": ok}
            for n, va, t, c, m, ok in rows], indent=1))
        return 0
    print(f"{'function':32} {'va':12} {'tgt':>5} {'cand':>5} {'identical':>10} {'pct':>6}")
    for name, va, t, c, m, ok in rows:
        flag = " " if ok else "!"
        pct = 100.0 * m / t if t else 0.0
        print(f"{flag}{name:31} {va:12} {t:5} {c:5} {m:10} {pct:5.1f}%")
    print("!  candidate slice much shorter than the target - objdump split the "
          "COMDAT; ignore that row")
    return 0


if __name__ == "__main__":
    sys.exit(main())
