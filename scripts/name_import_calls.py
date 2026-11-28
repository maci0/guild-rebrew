"""Replace calls through raw English import slots by calls of the imported function (German twins).

usage: uv run --frozen python scripts/name_import_calls.py [--apply]

`(*(T*) 0x6623c4)(a1)` or `((R (CC*)(P)) *(void**) 0x6623c4)(a1)`, with T a function-pointer typedef and 0x6623c4 an entry of the English TL
import address table (mss32.dll `_AIL_start_sample@4`), becomes `AIL_start_sample(a1)` with
`__declspec(dllimport) R CC AIL_start_sample(P);` taken from T, the form the project already uses
(e.g. msx_ReacquireWaveDriver). Import slots are linker-owned; the import library supplies them.
Scope as for symbolize_known_globals.py: German twins that do not match, English twin EXACT/RELOC,
no English, Gold or server row of the definition EXACT. Measure every target and restore files
whose verdicts fall (a declaration can clash with a system header's).
"""
import re, sys
from collections import defaultdict
from pathlib import Path
import lief
from rebrew.cli import require_config
from rebrew.metadata.functions import load_metadata

ROOT = Path.cwd()
INCLUDE = re.compile(r'^\s*#\s*include\s*[<"]([^">]+)[">]', re.M)

def closure_text(path, seen=None):
    """Text of the file and its quoted includes (system headers are not followed)."""
    seen = seen if seen is not None else set()
    if path in seen or not path.exists(): return ""
    seen.add(path)
    text = path.read_text(encoding="latin-1")
    out = text
    for inc in INCLUDE.findall(text):
        for base in (path.parent, ROOT / "src/Develop", ROOT / "src"):
            c = (base / inc).resolve()
            if c.exists(): out += closure_text(c, seen); break
    return out
CALL = re.compile(r"\(\*\s*\(\s*(\w+)\s*\*\s*\)\s*0x([0-9a-fA-F]{6,8})\s*\)\s*\(")
INLINE = re.compile(r"\(\(\s*([\w\s\*]+?)\s*\(\s*(__\w+)?\s*\*\s*\)\s*(\([^()]*\))\s*\)\s*\*\s*\(\s*void\s*\*\s*\*\s*\)\s*0x([0-9a-fA-F]{6,8})\s*\)\s*\(")

def body_span(text, name):
    m = re.search(r"\b%s\s*\([^;{]*\)\s*\{" % re.escape(name), text)
    if not m: return None
    i, d = m.end(), 1
    while d and i < len(text): d += {"{": 1, "}": -1}.get(text[i], 0); i += 1
    return m.start(), i

def main():
    apply = "--apply" in sys.argv
    pe = lief.parse(str(ROOT / "original/Europa1400Gold_TL.exe")); b = pe.optional_header.imagebase
    slots = {b + e.iat_address: e.name for imp in pe.imports for e in imp.entries if e.name}
    system = {b + e.iat_address for imp in pe.imports for e in imp.entries
              if imp.name.upper() in ("KERNEL32.DLL", "USER32.DLL", "GDI32.DLL", "ADVAPI32.DLL", "WINMM.DLL", "WSOCK32.DLL", "WS2_32.DLL", "SHELL32.DLL", "OLE32.DLL")}
    meta = load_metadata(require_config(target="GildeGold_TL.exe", json_mode=True).metadata_dir)
    by = defaultdict(list)
    for (m, va), r in meta.items():
        if r.get("file") and r.get("name"): by[(r["file"], r["name"])].append((m, r.get("status")))
    work = defaultdict(set)
    for (m, va), r in meta.items():
        if m != "GOLDDE" or r.get("status") not in ("NEAR_MATCHING", "STUB"): continue
        o = by[(r["file"], r["name"])]
        if not any(x == "GOLDTL" and s in ("EXACT", "RELOC") for x, s in o): continue
        if "--allow-exact" not in sys.argv and any(x in ("GOLDTL", "GOLD", "SERVER") and s == "EXACT" for x, s in o): continue
        work[r["file"]].add(r["name"])
    files = sites = 0
    for rel, names in sorted(work.items()):
        path = ROOT / rel; t = orig = path.read_text(encoding="latin-1")
        decls = {}
        for start, end in sorted(filter(None, (body_span(t, n) for n in names)), reverse=True):
            def repl(m):
                nonlocal sites
                typ, va = m.group(1), int(m.group(2), 16)
                raw = slots.get(va)
                td = re.search(r"typedef\s+([\w\s\*]+?)\s*\(\s*(__\w+)?\s*\*\s*%s\s*\)\s*(\([^;]*\))\s*;" % re.escape(typ), t)
                if not raw or not td: return m.group(0)
                fn = re.sub(r"@\d+$", "", raw.lstrip("_")) if raw.startswith("_") else raw
                decls[fn] = "__declspec(dllimport) %s %s %s%s;\n" % (td.group(1).strip(), td.group(2) or "__cdecl", fn, td.group(3))
                sites += 1
                return fn + "("
            def repl_inline(m):
                nonlocal sites
                raw = slots.get(int(m.group(4), 16))
                if not raw: return m.group(0)
                if int(m.group(4), 16) in system and "windows.h" in t.lower():
                    sites += 1  # windows.h already declares the API
                    return (re.sub(r"@\d+$", "", raw.lstrip("_")) if raw.startswith("_") else raw) + "("
                fn = re.sub(r"@\d+$", "", raw.lstrip("_")) if raw.startswith("_") else raw
                decls[fn] = "__declspec(dllimport) %s %s %s%s;\n" % (m.group(1).strip(), m.group(2) or "__cdecl", fn, m.group(3))
                sites += 1
                return fn + "("
            seg = INLINE.sub(repl_inline, CALL.sub(repl, t[start:end]))
            t = t[:start] + seg + t[end:]
        if t == orig: continue
        closure = closure_text(path.resolve())
        new = [d for f, d in decls.items() if not re.search(r"\b%s\s*\(" % re.escape(f), closure.split("/* ADDRESS")[0])
               and not re.search(r"\b(WINAPI|__stdcall|APIENTRY)\s+%s\s*\(" % re.escape(f), closure)]
        files += 1
        if apply: path.write_text("".join(new) + t, encoding="latin-1", newline="")
    print(f"{len(work)} candidate files, {files} changed, {sites} sites" + ("" if apply else " (dry run)"))

if __name__ == "__main__":
    main()
