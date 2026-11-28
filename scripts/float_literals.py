"""Write English .rdata float constants as C literals in non-matching German twins.

usage: uv run --frozen python scripts/float_literals.py [--apply]

`*(float*) 0xVA` / `*(double*) 0xVA` (also `*(float*) &g_<va>`) with VA in the English TL .rdata
reads a compiler literal-pool constant. It becomes the literal itself (`100.0f`, `0.01`), the
shortest decimal that reproduces the same bytes, so the compiler emits its own pool entry for each
build. 0.0 and 1.0 are left alone (msvc would use fldz/fld1, not a memory operand). Scope as for
the address symbolizers (German twins that do not match, English twin EXACT/RELOC, no English,
Gold or server row of the definition EXACT). Measure every target and restore files whose verdicts
fall.
"""
import re, struct, sys
from collections import defaultdict
from pathlib import Path
import lief
from rebrew.cli import require_config
from rebrew.metadata.functions import load_metadata

ROOT = Path.cwd()
PAT = re.compile(r"\*\s*\(\s*(float|double)\s*\*\s*\)\s*(?:0x([0-9a-fA-F]{6,8})\b|\(\s*\(\s*int\s*\)\s*&\s*g_([0-9a-f]{6,8})\s*\)|&\s*g_([0-9a-f]{6,8})\b)")

def literal(kind, raw):
    fmt = "<f" if kind == "float" else "<d"
    v = struct.unpack(fmt, raw)[0]
    if v != v or v in (float("inf"), float("-inf")): return None
    for p in range(1, 18):
        s = "%.*g" % (p, v)
        if struct.pack(fmt, float(s)) == raw: break
    else: return None
    if "e" not in s and "." not in s: s += ".0"
    return s + ("f" if kind == "float" else "")

def body_span(text, name):
    m = re.search(r"\b%s\s*\([^;{]*\)\s*\{" % re.escape(name), text)
    if not m: return None
    i, d = m.end(), 1
    while d and i < len(text): d += {"{": 1, "}": -1}.get(text[i], 0); i += 1
    return m.end(), i

def main():
    apply = "--apply" in sys.argv
    pe = lief.parse(str(ROOT / "original/Europa1400Gold_TL.exe")); b = pe.optional_header.imagebase
    rd = next(s for s in pe.sections if s.name == ".rdata"); lo, hi = b + rd.virtual_address, b + rd.virtual_address + rd.virtual_size
    meta = load_metadata(require_config(target="GildeGold_TL.exe", json_mode=True).metadata_dir)
    by = defaultdict(list)
    for (m, va), r in meta.items():
        if r.get("file") and r.get("name"): by[(r["file"], r["name"])].append((m, r.get("status")))
    work = defaultdict(set)
    for (m, va), r in meta.items():
        if m != "GOLDDE" or r.get("status") not in ("NEAR_MATCHING", "STUB"): continue
        o = by[(r["file"], r["name"])]
        if not any(x == "GOLDTL" and s in ("EXACT", "RELOC") for x, s in o): continue
        if any(x in ("GOLDTL", "GOLD", "SERVER") and s == "EXACT" for x, s in o): continue
        work[r["file"]].add(r["name"])
    files = sites = 0
    for rel, names in sorted(work.items()):
        path = ROOT / rel; t = orig = path.read_text(encoding="latin-1")
        for start, end in sorted(filter(None, (body_span(t, n) for n in names)), reverse=True):
            def repl(m):
                nonlocal sites
                va = int(m.group(2) or m.group(3) or m.group(4), 16)
                if not lo <= va < hi: return m.group(0)
                raw = bytes(pe.get_content_from_virtual_address(va - b, 4 if m.group(1) == "float" else 8))
                s = literal(m.group(1), raw)
                if s is None or float(s.rstrip("f")) in (0.0, 1.0): return m.group(0)
                sites += 1
                return "(%s)" % s if s.startswith("-") else s
            t = t[:start] + PAT.sub(repl, t[start:end]) + t[end:]
        if t != orig:
            files += 1
            if apply: path.write_text(t, encoding="latin-1", newline="")
    print(f"{len(work)} candidate files, {files} changed, {sites} sites" + ("" if apply else " (dry run)"))

if __name__ == "__main__":
    main()
