"""Name raw English code addresses (function pointers) in non-matching German twins.

usage: uv run --frozen python scripts/name_code_addresses.py [--allow-exact] [--apply]

A hexadecimal literal X inside the English TL .text that is the start of a named GOLDTL function
row (callbacks pushed as constants, e.g. `d2_SetIdleHandler(0x525e90)`) becomes `(int) name`, or
`(T*) name` after a pointer cast, so each build gets its own address from the linker. Scope as for
the address symbolizers: German twins that do not match, English twin EXACT/RELOC, no English,
Gold or server row of the definition EXACT (unless --allow-exact). A declaration is added at the
top of the file when the translation unit does not declare the name: `__cdecl` from a `_name`
object symbol, `__stdcall` with N/4 int parameters from `_name@N`; other decorations are skipped.
Measure every target and restore files whose verdicts fall.
"""
import re, sys
from collections import defaultdict
from pathlib import Path
import lief
from rebrew.cli import require_config
from rebrew.metadata.functions import load_metadata

ROOT = Path.cwd()
HEX = re.compile(r"(?<![\w&])0x([0-9a-fA-F]{6,8})\b")
INCLUDE = re.compile(r'^\s*#\s*include\s*"([^"]+)"', re.M)
COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
CAST = re.compile(r"\(\s*(?:(?:const|volatile|signed|unsigned|struct)\s+)*[A-Za-z_]\w*\s*\*+\s*\)\s*$")

def resolve_include(path, inc):
    for b in (path.parent, ROOT / "src/Develop", ROOT / "src", ROOT / "references/zlib-1.1.3"):
        c = (b / inc).resolve()
        if c.exists(): return c
    return (path.parent / inc).resolve()

def closure_text(path, seen=None):
    seen = seen if seen is not None else set()
    if path in seen or not path.exists(): return ""
    seen.add(path)
    t = COMMENT.sub(" ", path.read_text(encoding="latin-1"))
    return t + "".join(closure_text(resolve_include(path, i), seen) for i in INCLUDE.findall(t))

def body_span(text, name):
    m = re.search(r"\b%s\s*\([^;{]*\)\s*\{" % re.escape(name), text)
    if not m: return None
    i, d = m.end(), 1
    while d and i < len(text): d += {"{": 1, "}": -1}.get(text[i], 0); i += 1
    return m.end(), i

def main():
    apply, allow_exact = "--apply" in sys.argv, "--allow-exact" in sys.argv
    pe = lief.parse(str(ROOT / "original/Europa1400Gold_TL.exe")); lo = pe.optional_header.imagebase
    text = next(s for s in pe.sections if s.name == ".text"); t_lo = lo + text.virtual_address; t_hi = t_lo + text.virtual_size
    meta = load_metadata(require_config(target="GildeGold_TL.exe", json_mode=True).metadata_dir)
    funcs = {va: r for (m, va), r in meta.items() if m == "GOLDTL" and r.get("kind") == "FUNCTION" and r.get("name") and r.get("symbol")}
    by = defaultdict(list)
    for (m, va), r in meta.items():
        if r.get("file") and r.get("name"): by[(r["file"], r["name"])].append((m, r.get("status")))
    work = defaultdict(set)
    for (m, va), r in meta.items():
        if m != "GOLDDE" or r.get("status") not in ("NEAR_MATCHING", "STUB"): continue
        o = by[(r["file"], r["name"])]
        if not any(x == "GOLDTL" and s in ("EXACT", "RELOC") for x, s in o): continue
        if not allow_exact and any(x in ("GOLDTL", "GOLD", "SERVER") and s == "EXACT" for x, s in o): continue
        work[r["file"]].add(r["name"])
    files = sites = 0
    for rel, names in sorted(work.items()):
        path = ROOT / rel; t = path.read_text(encoding="latin-1")
        closure = closure_text(path.resolve()); used = {}
        for start, end in sorted(filter(None, (body_span(t, n) for n in names)), reverse=True):
            body = t[start:end]; stripped = COMMENT.sub(lambda m: " " * len(m.group(0)), body)
            out, last = [], 0
            for m in HEX.finditer(stripped):
                v = int(m.group(1), 16)
                if not t_lo <= v < t_hi or v not in funcs: continue
                r = funcs[v]; sym = r["symbol"]
                sm = re.fullmatch(r"_([A-Za-z_]\w*)(?:@(\d+))?", sym)
                if not sm or sm.group(1) != r["name"]: continue
                name = r["name"]; used[name] = sm.group(2)
                rep = name if CAST.search(body[:m.start()].rstrip()) else "(int) %s" % name
                out.append(body[last:m.start()] + rep); last = m.end(); sites += 1
            out.append(body[last:])
            t = t[:start] + "".join(out) + t[end:]
        if not used: continue
        decls = []
        for name, at in used.items():
            if re.search(r"\b%s\s*\(" % re.escape(name), closure.split("/* ADDRESS")[0]) or re.search(r"[;}]\s*[\w\s\*]*\b%s\s*\(" % re.escape(name), closure):
                continue
            if at is None: decls.append("void __cdecl %s();\n" % name)
            else: decls.append("void __stdcall %s(%s);\n" % (name, ", ".join(["int"] * (int(at) // 4)) or "void"))
        files += 1
        if apply: path.write_text("".join(decls) + t, encoding="latin-1", newline="")
    print(f"{len(work)} candidate files, {files} changed, {sites} sites" + ("" if apply else " (dry run)"))

if __name__ == "__main__":
    main()
