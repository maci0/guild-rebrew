"""Replace raw English data addresses by globals the client links already define, for German twins.

usage: uv run --frozen python scripts/symbolize_known_globals.py <cmake-sources dir> [--allow-new] [--apply]

<cmake-sources dir> holds `rebrew build cmake-sources --target T -o DIR/src-T.cmake` for
Europa1400Gold_TL.exe, Europa1400Gold.exe and server.dll (the link inputs this script checks).

A raw cast `(T *) 0xVA` (VA inside the English TL image) in the body of a German twin that does
not match (GOLDDE NEAR_MATCHING/STUB, English twin EXACT/RELOC) becomes `(T *) &g_<va>` when
- every link that compiles the file already defines `g_<va>` (a non-extern definition in that
  link's sources or stubs), so the change can add no unresolved external, and
- no English or Gold row of the same definition is EXACT (a relocated operand would demote it).
The file gets `extern ... g_<va>;` at its top, copied from an existing declaration in the
translation unit, else `extern char g_<va>[];`. This is the named-global form the project already
uses for raw addresses; German operand identities stay unproven until checked separately.

With --allow-new, names that no link defines yet are used too, but only for addresses in the
English data sections (never .text, never the import address table). The client links then report them as LNK2001; their
placeholders come from `rebrew build symbol-stubs --log <link log>`, as for the naming batches.
"""

import re
import sys
from collections import defaultdict
from pathlib import Path

import lief

from rebrew.cli import require_config
from rebrew.metadata.functions import load_metadata

ROOT = Path.cwd()
CAST = re.compile(r"\(\s*((?:const\s+)?[A-Za-z_]\w*\s*\*+)\s*\)\s*0x([0-9a-fA-F]{6,8})\b")
DEFINITION = re.compile(
    r"^(?!\s*extern\b)(?!\s*typedef\b)[ \t]*[A-Za-z_][\w \t\*]*?\b(g_[0-9a-f]{6,8})\b\s*(\[[^\]]*\])*\s*(=|;)", re.M
)
INCLUDE = re.compile(r'^\s*#\s*include\s*"([^"]+)"', re.M)
BASIC = re.compile(r"(?:(?:const|volatile|signed|unsigned|short|long|int|char|float|double|void)\s*)+\**\s*")
COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
LINKS = {
    "Europa1400Gold_TL.exe": ("GOLDTL", "stubs/goldtl"),
    "Europa1400Gold.exe": ("GOLD", "stubs/gold"),
    "server.dll": ("SERVER", None),
}


def defined_names(paths):
    names = set()
    for p in paths:
        try:
            names |= {m.group(1) for m in DEFINITION.finditer(COMMENT.sub(" ", p.read_text(encoding="latin-1")))}
        except OSError:
            pass
    return names


def closure_text(path, seen=None):
    seen = seen if seen is not None else set()
    if path in seen or not path.exists():
        return ""
    seen.add(path)
    text = COMMENT.sub(" ", path.read_text(encoding="latin-1"))
    return text + "".join(closure_text(resolve_include(path, inc), seen) for inc in INCLUDE.findall(text))


def resolve_include(path, inc):
    """Quoted include: the including file's directory first, then the compiler include dirs."""
    for base in (path.parent, ROOT / "src/Develop", ROOT / "src", ROOT / "references/zlib-1.1.3"):
        candidate = (base / inc).resolve()
        if candidate.exists():
            return candidate
    return (path.parent / inc).resolve()


def body_span(text, name):
    m = re.search(r"\b%s\s*\([^;{]*\)\s*\{" % re.escape(name), text)
    if not m:
        return None
    i, depth = m.end(), 1
    while depth and i < len(text):
        depth += {"{": 1, "}": -1}.get(text[i], 0)
        i += 1
    return m.start(), i


def main() -> int:
    src_dir, apply, allow_new = Path(sys.argv[1]), "--apply" in sys.argv, "--allow-new" in sys.argv
    pe = lief.parse(str(ROOT / "original/Europa1400Gold_TL.exe"))
    lo, hi = pe.optional_header.imagebase, pe.optional_header.imagebase + pe.optional_header.sizeof_image
    text = next(sec for sec in pe.sections if sec.name == ".text")
    data_lo = lo + text.virtual_address + text.virtual_size  # everything after .text: .rdata, .data, .data1
    iat = pe.data_directory(lief.PE.DataDirectory.TYPES.IAT)
    iat_lo, iat_hi = lo + iat.rva, lo + iat.rva + iat.size  # import slots are linker-owned, never globals
    link_files, link_names = {}, {}
    for target, (_, stubs) in LINKS.items():
        listed = re.findall(r'"([^"]+\.c)"', (src_dir / f"src-{target}.cmake").read_text())
        files = {Path(p.replace("${CMAKE_CURRENT_SOURCE_DIR}", str(ROOT))).resolve() for p in listed}
        link_files[target] = files
        link_names[target] = defined_names(list(files) + (list((ROOT / stubs).glob("*.c")) if stubs else []))

    cfg = require_config(target="GildeGold_TL.exe", json_mode=True)
    meta = load_metadata(cfg.metadata_dir)
    rows_by_def = defaultdict(list)
    for (module, va), row in meta.items():
        if row.get("file") and row.get("name"):
            rows_by_def[(row["file"], row["name"])].append((module, row))

    work = defaultdict(set)
    for (module, va), row in meta.items():
        if module != "GOLDDE" or row.get("status") not in ("NEAR_MATCHING", "STUB"):
            continue
        others = rows_by_def[(row["file"], row["name"])]
        if not any(m == "GOLDTL" and r.get("status") in ("EXACT", "RELOC") for m, r in others):
            continue
        if "--allow-exact" not in sys.argv and any(m in ("GOLDTL", "GOLD", "SERVER") and r.get("status") == "EXACT" for m, r in others):
            continue
        work[row["file"]].add(row["name"])

    changed_files = sites = skipped_undefined = 0
    for rel, names in sorted(work.items()):
        path = ROOT / rel
        text = path.read_text(encoding="latin-1")
        linked_by = [t for t, files in link_files.items() if path.resolve() in files]
        closure = closure_text(path.resolve())
        new_names = []
        spans = sorted(filter(None, (body_span(text, n) for n in names)), reverse=True)
        for start, end in spans:
            def repl(m):
                nonlocal sites, skipped_undefined
                va = int(m.group(2), 16)
                if not lo <= va < hi or iat_lo <= va < iat_hi:
                    return m.group(0)
                name = "g_%x" % va
                known = linked_by and all(name in link_names[t] for t in linked_by)
                if not known and not (allow_new and linked_by and data_lo <= va < hi):
                    skipped_undefined += 1
                    return m.group(0)
                existing = re.search(r"\bextern\s+([^;{}()]*?)\b%s\b\s*(\[[^\];]*\])?\s*;" % name, closure)
                if existing and not BASIC.fullmatch(existing.group(1).strip()):
                    skipped_undefined += 1  # its type is declared later in the TU; the top-of-file copy would not compile
                    return m.group(0)
                if name not in new_names:
                    new_names.append(name)
                sites += 1
                return "(%s) &%s" % (m.group(1), name)

            text = text[:start] + CAST.sub(repl, text[start:end]) + text[end:]
        if not new_names:
            continue
        decls = []
        for n in new_names:
            m = re.search(r"\bextern\s+([^;{}()]*?)\b%s\b\s*(\[[^\];]*\])?\s*;" % n, closure)
            decls.append("extern %s %s%s;\n" % (m.group(1).strip(), n, m.group(2) or "") if m else "extern char %s[];\n" % n)
        changed_files += 1
        if apply:
            path.write_text("".join(decls) + text, encoding="latin-1", newline="")
    print(f"{len(work)} candidate files, {changed_files} changed, {sites} sites rewritten, "
          f"{skipped_undefined} kept (name not defined in every link)" + ("" if apply else " (dry run)"))
    return 0


if __name__ == "__main__":
    sys.exit(main())
