#!/usr/bin/env python3
"""Mass-generate `// GLOBAL:` annotation markers from rebrew-data.toml.

For every .data/.rdata/.bss symbol in rebrew-data.toml, insert
`// GLOBAL: SERVER 0x<VA>` immediately above the first declaration/definition
of that name in each source file that mentions it (extern or definition).
This unblocks `rebrew data --bss --json` and `rebrew data --fix-bss`.

Usage: python3 scripts/annotate_globals.py [--dry-run]
"""
import argparse
import pathlib
import re
import sys
import tomllib

ROOT = pathlib.Path(__file__).parent.parent
TARGET = "SERVER"


def load_toml():
    with open(ROOT / "src" / "rebrew-data.toml", "rb") as f:
        db = tomllib.load(f)
    out = {}
    for k, v in db.items():
        mod = k.split(".")[0]
        addr = int(k.split(".")[1], 16)
        out[v.get("name", "")] = (mod, addr)
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    toml = load_toml()
    print(f"toml entries: {len(toml)}", file=sys.stderr)

    decl_re_cache = {}
    files = sorted(pathlib.Path(ROOT / "src" / "server.dll").rglob("*.c"))
    total = 0
    for f in files:
        text = f.read_text()
        lines = text.splitlines()
        # find marker lines already present
        existing = set()
        for i, ln in enumerate(lines):
            m = re.match(r"^\s*//\s*GLOBAL:\s*\S+\s+0x([0-9a-fA-F]+)", ln)
            if m:
                existing.add(int(m.group(1), 16))
        insertions = []  # (line_index, marker)
        used_lines = set()
        for name, (mod, addr) in sorted(toml.items(), key=lambda kv: kv[1][1]):
            if addr in existing:
                continue
            # first line declaring/defining the name
            hit = None
            for i, ln in enumerate(lines):
                if i in used_lines:
                    continue
                if re.match(r"^\s*(?:extern\s+)?[\w\s\*]+\s+" + re.escape(name) +
                            r"(\[\d*\])?\s*(?:=\s*[^;]*|\s*;)", ln):
                    hit = i
                    break
            if hit is None:
                continue
            # skip if a // DATA: marker already annotates this declaration
            if hit > 0 and re.match(r"^\s*//\s*DATA:", lines[hit-1]):
                continue
            used_lines.add(hit)
            marker = f"// GLOBAL: {TARGET} 0x{addr:08x}"
            insertions.append((hit, marker))
        if not insertions:
            continue
        # insert markers above their target lines (careful with prior insert shifts)
        shift = 0
        for hit, marker in insertions:
            idx = hit + shift
            lines.insert(idx, marker)
            shift += 1
            total += 1
        if not args.dry_run:
            f.write_text("\n".join(lines) + "\n")
        print(f"{f.relative_to(ROOT)}: {len(insertions)} markers", file=sys.stderr)
    print(f"markers inserted: {total}", file=sys.stderr)


if __name__ == "__main__":
    main()
