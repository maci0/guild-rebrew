"""Remove German ADDRESS anchors from definitions their target does not compile.

usage: uv run --frozen python scripts/de_dedupe_anchors.py [--apply]

`de_bind_twins.py` placed a German anchor above every definition of the bound name; where a file
holds alternative definitions under #if (server / client / Gold), only one is compiled for the
German target. The #if stack above each copy is evaluated with that target's defines (GOLDDE:
REBREW_GOLDDE; SERVERDE: REBREW_SERVER, REBREW_LEGACY_SERVER_LAYOUT, REBREW_SERVERDE); the anchor is
kept on the compiled copy and removed from the others. Ambiguous cases are reported and left alone.
"""
import re, sys
from collections import defaultdict
from pathlib import Path

DEFINES = {"GOLDDE": {"REBREW_GOLDDE"}, "SERVERDE": {"REBREW_SERVER", "REBREW_LEGACY_SERVER_LAYOUT", "REBREW_SERVERDE"}}
ANCHOR = re.compile(r"^/\* ADDRESS: (GOLDDE|SERVERDE) (0x[0-9a-f]+) \*/\n", re.M)

def evaluate(expr, defs):
    expr = re.sub(r"/\*.*?\*/|//.*", "", expr)
    expr = re.sub(r"defined\s*\(\s*(\w+)\s*\)|defined\s+(\w+)", lambda m: "1" if (m.group(1) or m.group(2)) in defs else "0", expr)
    expr = re.sub(r"\b[A-Za-z_]\w*\b", "0", expr)
    expr = expr.replace("&&", " and ").replace("||", " or ").replace("!", " not ")
    return bool(eval(expr))

def active_lines(text, defs):
    """For each line, whether it is compiled under defs (only this file's conditionals)."""
    stack, out = [], []
    for line in text.split("\n"):
        m = re.match(r"\s*#\s*(if|ifdef|ifndef|elif|else|endif)\b(.*)", line)
        if m:
            kw, rest = m.group(1), m.group(2)
            if kw in ("if", "ifdef", "ifndef"):
                cond = evaluate(rest, defs) if kw == "if" else ((rest.split()[0] in defs) == (kw == "ifdef"))
                parent = all(s[0] for s in stack)
                stack.append([cond, cond])  # [current branch active, any branch taken]
            elif kw == "elif":
                taken = stack[-1][1]; c = (not taken) and evaluate(rest, defs)
                stack[-1] = [c, taken or c]
            elif kw == "else":
                stack[-1] = [not stack[-1][1], True]
            elif kw == "endif":
                stack.pop()
        out.append(all(s[0] for s in stack))
    return out

apply = "--apply" in sys.argv
where = defaultdict(list)
for path in Path("src").rglob("*.c"):
    text = path.read_text(encoding="latin-1")
    for m in ANCHOR.finditer(text):
        where[(m.group(1), m.group(2))].append((path, m.start()))
edits = defaultdict(list); report = []
for key, sites in sorted(where.items()):
    if len(sites) < 2: continue
    mod = key[0]
    status = []
    for path, pos in sites:
        text = path.read_text(encoding="latin-1")
        line = text.count("\n", 0, pos)
        status.append(active_lines(text, DEFINES[mod])[line])
    if sum(status) == 1:
        for (path, pos), act in zip(sites, status):
            if not act: edits[path].append(pos)
    else:
        report.append((key, [(str(p), s) for (p, _), s in zip(sites, status)]))
for key, s in report: print("left alone:", key, s)
n = sum(len(v) for v in edits.values())
print(f"remove {n} inactive anchors in {len(edits)} files")
if apply:
    for path, poss in edits.items():
        text = path.read_text(encoding="latin-1")
        for pos in sorted(poss, reverse=True):
            end = text.index("\n", pos) + 1
            text = text[:pos] + text[end:]
        path.write_text(text, encoding="latin-1", newline="")
