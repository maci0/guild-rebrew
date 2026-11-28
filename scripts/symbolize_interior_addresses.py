"""Express raw English interior/end addresses as offsets from a global the same function already uses.

usage: uv run --frozen python scripts/symbolize_interior_addresses.py [--apply]

In German twins that do not match (GOLDDE NEAR_MATCHING/STUB, English twin EXACT/RELOC), a raw
number X inside the English TL image, e.g. the loop bound in

    p = ch_CharacterSlots; do { ... p++; } while ((int) p < 0x14d0c20);

becomes `((int) &SYM + 0xOFF)` when the same function body names a global SYM whose English
address B satisfies B <= X <= B + 0x4000 (the closest such B). SYM's address comes from its
`g_<va>` name or its GOLDTL data row. The function's own use of SYM is the evidence for the
backing object (AGENTS.md: an interior address is a view of its backing object); the extent is
not verified. Addresses in the English .rdata (compiler literal pools, constants) are excluded. Code generation is unchanged apart from the relocation. Rows whose English or Gold
definition is EXACT are skipped (a relocated operand would demote them). Measure every target
afterwards and restore files whose verdicts fall.
"""

import re
import sys
import tomllib
from collections import defaultdict
from pathlib import Path

from rebrew.cli import require_config
from rebrew.metadata.functions import load_metadata

ROOT = Path.cwd()
HEX = re.compile(r"(?<![\w&])0x([0-9a-fA-F]{6,8})\b")
IDENT = re.compile(r"\b(g_([0-9a-f]{6,8})|[A-Za-z_]\w*)\b")
LO, HI, SPAN = 0x400000, 0x1581000, 0x4000
RDATA = (0x662000, 0x675000)  # English TL .rdata: compiler literals and constants are separate objects


def body_span(text, name):
    m = re.search(r"\b%s\s*\([^;{]*\)\s*\{" % re.escape(name), text)
    if not m:
        return None
    i, depth = m.end(), 1
    while depth and i < len(text):
        depth += {"{": 1, "}": -1}.get(text[i], 0)
        i += 1
    return m.end(), i


def main() -> int:
    apply = "--apply" in sys.argv
    cfg = require_config(target="GildeGold_TL.exe", json_mode=True)
    meta = load_metadata(cfg.metadata_dir)
    data = tomllib.loads((ROOT / "rebrew-data.toml").read_text())
    named = {v["name"]: int(k.split(".0x")[1], 16) for k, v in data.items()
             if k.startswith("GOLDTL.0x") and isinstance(v, dict) and v.get("name")}
    by_def = defaultdict(list)
    for (module, va), row in meta.items():
        if row.get("file") and row.get("name"):
            by_def[(row["file"], row["name"])].append((module, row))
    work = defaultdict(set)
    for (module, va), row in meta.items():
        if module != "GOLDDE" or row.get("status") not in ("NEAR_MATCHING", "STUB"):
            continue
        others = by_def[(row["file"], row["name"])]
        if not any(m == "GOLDTL" and r.get("status") in ("EXACT", "RELOC") for m, r in others):
            continue
        if "--allow-exact" not in sys.argv and any(m in ("GOLDTL", "GOLD", "SERVER") and r.get("status") == "EXACT" for m, r in others):
            continue
        work[row["file"]].add(row["name"])

    files = sites = 0
    for rel, names in sorted(work.items()):
        path = ROOT / rel
        text = path.read_text(encoding="latin-1")
        spans = sorted(filter(None, (body_span(text, n) for n in names)), reverse=True)
        changed = False
        for start, end in spans:
            body = text[start:end]
            bases = {}
            for m in IDENT.finditer(body):
                sym = m.group(1)
                if m.group(2):
                    bases[sym] = int(m.group(2), 16)
                elif sym in named:
                    bases[sym] = named[sym]

            def repl(m):
                nonlocal sites
                x = int(m.group(1), 16)
                if not LO <= x < HI or RDATA[0] <= x < RDATA[1]:
                    return m.group(0)
                cands = [(b, s) for s, b in bases.items() if b <= x <= b + SPAN and not RDATA[0] <= b < RDATA[1]]
                if not cands:
                    return m.group(0)
                b, sym = max(cands)
                sites += 1
                return "((int) &%s)" % sym if x == b else "((int) &%s + 0x%x)" % (sym, x - b)

            new_body = HEX.sub(repl, body)
            if new_body != body:
                text = text[:start] + new_body + text[end:]
                changed = True
        if changed:
            files += 1
            if apply:
                path.write_text(text, encoding="latin-1", newline="")
    print(f"{len(work)} candidate files, {files} changed, {sites} sites" + ("" if apply else " (dry run)"))
    return 0


if __name__ == "__main__":
    sys.exit(main())
