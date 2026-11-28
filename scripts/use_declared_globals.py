"""Use header-declared globals directly instead of casts of their address (German twins).

usage: uv run --frozen python scripts/use_declared_globals.py [--apply]

`*(T*) 0xVA` and `*(T*) &g_<va>` become `g_<va>` when a project header declares
`extern [volatile] T g_<va>;` with the same type T (qualifiers aside): the declared type, including
`volatile`, then governs the access as in the original. The header's declaration is copied to the
top of the file; a placeholder `extern char g_<va>[];` line added there by the address symbolizers
is replaced by it. Scope as for the address symbolizers: German twins that do not match, English
twin EXACT/RELOC, no English, Gold or server row of the definition EXACT. Measure every target and
restore files whose verdicts fall.
"""
import re, sys
from collections import defaultdict
from pathlib import Path
from rebrew.cli import require_config
from rebrew.metadata.functions import load_metadata

ROOT = Path.cwd()
DECL = re.compile(r"^\s*extern\s+((?:volatile\s+|const\s+|unsigned\s+|signed\s+)*\w+)\s+(g_[0-9a-f]{6,8})\s*;", re.M)
CAST = re.compile(r"\*\s*\(\s*((?:volatile\s+|unsigned\s+|signed\s+)*\w+)\s*\*\s*\)\s*(?:&\s*(g_[0-9a-f]{6,8})|0x([0-9a-fA-F]{6,8}))\b(?!\s*[\[+])")
base = lambda t: re.sub(r"\b(volatile|const)\s+", "", t).strip()

def body_span(text, name):
    m = re.search(r"\b%s\s*\([^;{]*\)\s*\{" % re.escape(name), text)
    if not m: return None
    i, d = m.end(), 1
    while d and i < len(text): d += {"{": 1, "}": -1}.get(text[i], 0); i += 1
    return m.end(), i

def main():
    apply = "--apply" in sys.argv
    decl = defaultdict(set)
    for h in (ROOT / "src").rglob("*.h"):
        for m in DECL.finditer(h.read_text(encoding="latin-1")): decl[m.group(2)].add(m.group(1).strip())
    decl = {k: next(iter(v)) for k, v in decl.items() if len({base(x) for x in v}) == 1 and len(v) == 1}
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
        path = ROOT / rel; t = orig = path.read_text(encoding="latin-1"); used = set()
        for start, end in sorted(filter(None, (body_span(t, n) for n in names)), reverse=True):
            def repl(m):
                nonlocal sites
                name = m.group(2) or "g_%x" % int(m.group(3), 16)
                if name not in decl or base(decl[name]) != base(m.group(1)): return m.group(0)
                used.add(name); sites += 1
                return name
            t = t[:start] + CAST.sub(repl, t[start:end]) + t[end:]
        if t == orig: continue
        top = []
        for name in sorted(used):
            line = "extern %s %s;\n" % (decl[name], name)
            if re.search(r"^extern char %s\[\];\n" % name, t, re.M):
                t = re.sub(r"^extern char %s\[\];\n" % name, line, t, count=1, flags=re.M)
            elif not re.search(r"\b%s\b\s*;" % name, t.split("/* ADDRESS")[0]):
                top.append(line)
        files += 1
        if apply: path.write_text("".join(top) + t, encoding="latin-1", newline="")
    print(f"{len(work)} candidate files, {files} changed, {sites} sites" + ("" if apply else " (dry run)"))

if __name__ == "__main__":
    main()
