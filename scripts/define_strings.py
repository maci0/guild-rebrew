#!/usr/bin/env python3
"""Give the remaining asm-referenced s_<hint>_<0xADDR> globals real content.

After scripts/inline_strings.py rewrites C-level uses to inline literals, the
only remaining references live inside naked __asm blocks (push offset s_x).
This script turns each file's `extern char s_x[];` into a definition
`char s_x[] = "<bytes from original .data at 0xADDR>";` so the string gets
real content AND lands in the owning translation unit's .data slot (placement
fix).  Tokens referenced from several files get exactly one owner definition
(file with the most uses); the rest keep extern.

Usage:
  python3 scripts/define_strings.py [--dry-run]
"""
import argparse
import pathlib
import re
import sys
from collections import defaultdict

sys.path.insert(0, str(pathlib.Path(__file__).parent))
from inline_strings import load_orig, read_string, c_literal  # noqa: E402

TOKEN_RE = re.compile(r"\bs_[A-Za-z0-9_]+_(100[0-9a-fA-F]{5,6})\b")
EXTERN_RE = re.compile(r"^(\s*extern\s+char\s+)(s_[A-Za-z0-9_]+_100[0-9a-fA-F]{5,6})(\[\];.*)$")


def real_uses(files):
    """token -> {files} where it appears outside comments/extern lines."""
    uses = defaultdict(set)
    for f in files:
        for ln in f.read_text().splitlines():
            s = ln.strip()
            if s.startswith("//") or s.startswith("*") or s.startswith("/*") or s.startswith("extern"):
                continue
            for m in TOKEN_RE.finditer(ln):
                uses[m.group(0)].add(f)
    return uses


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    orig = load_orig()
    files = sorted(pathlib.Path("src/server.dll").rglob("*.c"))
    uses = real_uses(files)
    if not uses:
        print("no remaining s_ uses", file=sys.stderr)
        return

    # owners: single-file -> that file; multi-file -> file with most uses
    owners = {}
    for tok, fs in uses.items():
        best = max(fs, key=lambda f: sum(1 for ln in f.read_text().splitlines() if tok in ln))
        owners[tok] = best

    done = 0
    for f in files:
        lines = f.read_text().splitlines()
        changed = False
        for i, ln in enumerate(lines):
            m = EXTERN_RE.match(ln)
            if not m:
                continue
            tok = m.group(2)
            if tok not in uses or tok not in owners:
                continue
            if owners[tok] != f:
                continue  # another TU owns the definition
            addr = int(tok.rsplit("_", 1)[1], 16)
            data = read_string(orig, addr)
            if data is None:
                print(f"  no string at {addr:#x} for {tok}", file=sys.stderr)
                continue
            lines[i] = f"{m.group(1)}{tok}[] = {c_literal(data)};"
            changed = True
            done += 1
        if changed:
            if not args.dry_run:
                f.write_text("\n".join(lines) + "\n")
            print(f"{f}: {done} definitions", file=sys.stderr)
    print(f"definitions written: {done}", file=sys.stderr)


if __name__ == "__main__":
    main()
