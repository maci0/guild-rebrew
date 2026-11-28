"""German edits outside function bodies that scripts/de_port_edits.py reports for a manual merge.

usage: uv run --frozen python scripts/de_replay_fixups.py [--names names.json --data-from REF]

Re-applies, idempotently, after a replay onto a new upstream tree:
- `#include "d2_capacity.h"` in every C file that uses d2_ELEMENT_CAPACITY without including it
  (relative inside src/Develop/Units/d2.v1, by path elsewhere);
- in d2_SetElementValue.c, the client branch's GUI id limit as d2_ELEMENT_CAPACITY;
- in Error.c, `#if !defined(REBREW_SERVERDE)` around the LogMessageInternal definition.
With --names and --data-from, also adds renames of data globals (same address, new name in
rebrew-data.toml since REF) to the name map used by de_port_edits.py --names.
"""
import json, re, subprocess, sys, tomllib
from pathlib import Path

INC = re.compile(r'^\s*#\s*include\s*"[^"]*d2_capacity\.h"', re.M)
for f in subprocess.run(["git", "grep", "-l", "d2_ELEMENT_CAPACITY", "--", "src/*.c"], capture_output=True, text=True).stdout.split():
    p = Path(f); t = p.read_text(encoding="latin-1")
    if INC.search(t): continue
    inc = '#include "d2_capacity.h"' if f.startswith("src/Develop/Units/d2.v1/") else '#include "Develop/Units/d2.v1/d2_capacity.h"'
    p.write_text(inc + "\n" + t, encoding="latin-1", newline=""); print("include", f)
for p in Path("src").rglob("d2_SetElementValue.c"):
    t = p.read_text(encoding="latin-1"); t2 = t
    if not INC.search(t2): t2 = t2.replace('#include "d2_gui.h"\n', '#include "d2_gui.h"\n#include "d2_capacity.h"\n', 1)
    t2 = re.sub(r"(#else\n#define d2_GUI_POOL [^\n]*\n)#define d2_GUI_ID_LIMIT 0x400\n", r"\1#define d2_GUI_ID_LIMIT d2_ELEMENT_CAPACITY\n", t2)
    if t2 != t: p.write_text(t2, encoding="latin-1", newline=""); print("limit", p)
for p in Path("src").rglob("Error.c"):
    t = p.read_text(encoding="latin-1")
    sig = "void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity)\n{"
    if sig not in t or "the German server has no LogMessageInternal" in t: continue
    start = t.rfind("\n\n", 0, t.index(sig)) + 2
    while t[start:].startswith("/*") and not t[start:].startswith("/* ADDRESS"):
        start = t.index("*/", start) + 3
    end = t.index("\n}\n", t.index(sig)) + 3
    t = t[:start] + "#if !defined(REBREW_SERVERDE) /* the German server has no LogMessageInternal (serverde_build.h) */\n" + t[start:end] + "#endif\n" + t[end:]
    p.write_text(t, encoding="latin-1", newline=""); print("guard", p)
if "--names" in sys.argv:
    names_path = sys.argv[sys.argv.index("--names") + 1]; ref = sys.argv[sys.argv.index("--data-from") + 1]
    names = json.load(open(names_path))
    old = tomllib.loads(subprocess.run(["git", "show", f"{ref}:rebrew-data.toml"], capture_output=True, text=True, check=True).stdout)
    new = tomllib.loads(open("rebrew-data.toml").read()); n = 0
    for k, v in old.items():
        if isinstance(v, dict) and v.get("name") and isinstance(new.get(k), dict) and new[k].get("name") and new[k]["name"] != v["name"]:
            names.setdefault(v["name"], new[k]["name"]); n += 1
    json.dump(names, open(names_path, "w")); print("data renames", n)
