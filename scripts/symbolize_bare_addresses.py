"""Name bare English data addresses in non-matching German twins (integer literals, not casts).

usage: uv run --frozen python scripts/symbolize_bare_addresses.py [--only FILES.txt] [--exclude PAIRS.json] [--apply]

--only limits the run to the files listed (one path per line); --include-only PAIRS.json limits it to those [file, function] pairs; --no-rdata leaves English .rdata addresses alone; --span N widens the base+offset
window (default 0x4000). --exclude skips the [file, function]
pairs listed in a JSON file (functions whose rows fell when rewritten).

Companion of scripts/symbolize_known_globals.py (D6/D12) for addresses written as plain integers,
e.g. `for (a = 0x14d0020; a < 0x14d0c20; a += 4)`. In the body of a German twin that does not match
(GOLDDE NEAR_MATCHING/STUB, English twin EXACT/RELOC, no English/Gold/server row of the same
definition EXACT), a hexadecimal literal X inside the English TL data sections (after .text,
outside the import address table) becomes `(int) &g_<X>`; a further literal Y of the same body with
X < Y <= X + 0x4000 becomes `((int) &g_<X> + 0x<Y-X>)`, the view of the same backing object. A
missing declaration is added at the top of the file as `extern char g_<X>[];` unless the
translation unit already declares the name. GoldTL placeholders for new names come from
`rebrew build symbol-stubs`, as for D12. Measure every target afterwards and restore files whose
verdicts fall: a literal in that range can also be a plain number (single-bit values are skipped
as masks, e.g. 0x800000).
"""
import re, sys
from collections import defaultdict
from pathlib import Path
import lief
from rebrew.cli import require_config
from rebrew.metadata.functions import load_metadata

ROOT = Path.cwd()
HEX = re.compile(r"(?<![\w&])0x([0-9a-fA-F]{6,8})\b(?!\s*\])")
INCLUDE = re.compile(r'^\s*#\s*include\s*"([^"]+)"', re.M)
COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
SPAN = 0x4000  # --span N widens it (loop bounds at the end of large tables)

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
    apply = "--apply" in sys.argv
    global SPAN
    if "--span" in sys.argv: SPAN = int(sys.argv[sys.argv.index("--span") + 1], 0)
    import json as _json
    only = {l.strip() for l in open(sys.argv[sys.argv.index("--only") + 1]) if l.strip()} if "--only" in sys.argv else None
    incl = {tuple(x) for x in _json.load(open(sys.argv[sys.argv.index("--include-only") + 1]))} if "--include-only" in sys.argv else None
    exclude = {tuple(x) for x in _json.load(open(sys.argv[sys.argv.index("--exclude") + 1]))} if "--exclude" in sys.argv else set()
    pe = lief.parse(str(ROOT / "original/Europa1400Gold_TL.exe"))
    lo = pe.optional_header.imagebase; hi = lo + pe.optional_header.sizeof_image
    text = next(s for s in pe.sections if s.name == ".text"); data_lo = lo + text.virtual_address + text.virtual_size
    iat = pe.data_directory(lief.PE.DataDirectory.TYPES.IAT); iat_lo, iat_hi = lo + iat.rva, lo + iat.rva + iat.size
    if "--no-rdata" in sys.argv:  # .rdata holds compiler literal pools: see float_literals.py
        rd = next(s for s in pe.sections if s.name == ".rdata"); data_lo = lo + rd.virtual_address + rd.virtual_size
    meta = load_metadata(require_config(target="GildeGold_TL.exe", json_mode=True).metadata_dir)
    by_def = defaultdict(list)
    for (m, va), r in meta.items():
        if r.get("file") and r.get("name"): by_def[(r["file"], r["name"])].append((m, r))
    work = defaultdict(set)
    for (m, va), r in meta.items():
        if m != "GOLDDE" or r.get("status") not in ("NEAR_MATCHING", "STUB"): continue
        others = by_def[(r["file"], r["name"])]
        if not any(o == "GOLDTL" and x.get("status") in ("EXACT", "RELOC") for o, x in others): continue
        if "--allow-exact" not in sys.argv and any(o in ("GOLDTL", "GOLD", "SERVER") and x.get("status") == "EXACT" for o, x in others): continue
        if incl is not None and (r["file"], r["name"]) not in incl: continue
        if (only is None or r["file"] in only) and (r["file"], r["name"]) not in exclude:
            work[r["file"]].add(r["name"])
    files = sites = 0
    for rel, names in sorted(work.items()):
        path = ROOT / rel
        t = path.read_text(encoding="latin-1")
        closure = closure_text(path.resolve())
        new_names = []
        for start, end in sorted(filter(None, (body_span(t, n) for n in names)), reverse=True):
            body = t[start:end]
            stripped = COMMENT.sub(lambda m: " " * len(m.group(0)), body)
            vals = sorted({int(m.group(1), 16) for m in HEX.finditer(stripped)
                           if data_lo <= int(m.group(1), 16) < hi and not iat_lo <= int(m.group(1), 16) < iat_hi
                           and bin(int(m.group(1), 16)).count("1") > 1})  # single-bit values are masks
            if not vals: continue
            base = {}
            for v in vals:
                b = next((base[u] for u in sorted(base) if base[u] <= v <= base[u] + SPAN), None)
                base[v] = b if b is not None else v
            out, last = [], 0
            for m in HEX.finditer(stripped):
                v = int(m.group(1), 16)
                if v not in base: continue
                b = base[v]; name = "g_%x" % b
                if name not in new_names: new_names.append(name)
                rep = "(int) &%s" % name if v == b else "((int) &%s + 0x%x)" % (name, v - b)
                # a cast in front (T*) 0x.. keeps its cast: (T*) ((int) &g + off) / (T*) &g
                pre = body[:m.start()].rstrip()
                if pre.endswith(")") and re.search(r"\(\s*(?:(?:const|volatile|signed|unsigned|struct)\s+)*[A-Za-z_]\w*\s*\*+\s*\)$", pre) and v == b:
                    rep = "&%s" % name
                out.append(body[last:m.start()] + rep); last = m.end(); sites += 1
            out.append(body[last:])
            t = t[:start] + "".join(out) + t[end:]
        if not new_names: continue
        decls = []
        for n in new_names:
            if re.search(r"\b%s\b" % n, closure):
                continue  # declared (or defined) somewhere in the translation unit already
            decls.append("extern char %s[];\n" % n)
        files += 1
        if apply: path.write_text("".join(decls) + t, encoding="latin-1", newline="")
    print(f"{len(work)} candidate files, {files} changed, {sites} sites" + ("" if apply else " (dry run)"))

if __name__ == "__main__":
    main()
