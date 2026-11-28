"""Port function-level source edits of an earlier branch onto the current tree.

usage: uv run --frozen python scripts/de_port_edits.py <base-ref> <edited-ref> <files.txt> [--names names.json] [--apply]

For every file listed (paths as of <base-ref>), the functions whose text differs between
<base-ref> and <edited-ref> (ADDRESS anchor lines ignored) are located in the current tree by
their definition name. If the current definition still equals the <base-ref> one (whitespace and
anchors ignored), it is replaced by the <edited-ref> definition; otherwise it is reported for a
manual merge. Lines added outside function bodies (declarations, includes, macros) are inserted at
the top of the current file unless already present. Prints a report; nothing is written without
--apply.
"""
import json, re, subprocess, sys
from collections import defaultdict
from pathlib import Path

base, edited, listing = sys.argv[1], sys.argv[2], sys.argv[3]
apply = "--apply" in sys.argv
RENAMED = json.load(open(sys.argv[sys.argv.index("--names") + 1])) if "--names" in sys.argv else {}

def renamed(text):
    """Old definition and callee names rewritten to their current names (whole identifiers)."""
    if not RENAMED: return text
    return re.sub(r"\b[A-Za-z_]\w*\b", lambda m: RENAMED.get(m.group(0), m.group(0)), text)
ANCHOR = re.compile(r"^/\* ADDRESS: \w+ 0x[0-9a-f]+ \*/\n", re.M)
DEF = re.compile(r"^[A-Za-z_][\w \t\*\(\)]*?\b([A-Za-z_]\w*)\s*\(([^;{}]|\n)*?\)\s*\{", re.M)

def show(ref, path):
    r = subprocess.run(["git", "show", f"{ref}:{path}"], capture_output=True, text=True, encoding="latin-1")
    return r.stdout if r.returncode == 0 else None

def defs(text):
    """name -> (start, end) of each definition (signature through closing brace); duplicates keep a list."""
    out = defaultdict(list)
    for m in DEF.finditer(text):
        name = m.group(1)
        if name in ("if", "while", "for", "switch", "return", "sizeof"): continue
        i, d = m.end(), 1
        while d and i < len(text):
            d += {"{": 1, "}": -1}.get(text[i], 0); i += 1
        out[name].append((m.start(), i))
    return out

norm = lambda s: re.sub(r"\s+", " ", ANCHOR.sub("", s)).strip()

def find_current(name, hint_paths):
    for p in hint_paths:
        if p.exists():
            d = defs(p.read_text(encoding="latin-1")).get(name)
            if d: return p
    r = subprocess.run(["git", "grep", "-l", "-E", r"\b%s\s*\(" % name, "--", "src"], capture_output=True, text=True)
    for f in r.stdout.split():
        if f.endswith(".c") and defs(Path(f).read_text(encoding="latin-1")).get(name): return Path(f)
    return None

report = defaultdict(list); writes = {}
for old_path in [l.strip() for l in open(listing) if l.strip()]:
    b, e = show(base, old_path), show(edited, old_path)
    if b is None or e is None: report["missing in refs"].append(old_path); continue
    bd, ed = defs(b), defs(e)
    changed = [n for n in ed if n in bd and len(ed[n]) == len(bd[n]) and any(norm(b[s:t]) != norm(e[s2:t2]) for (s, t), (s2, t2) in zip(bd[n], ed[n]))]
    # text outside definitions
    def outside(text, d):
        spans = sorted(x for v in d.values() for x in v); out, last = [], 0
        for s, t in spans: out.append(text[last:s]); last = t
        out.append(text[last:]); return "".join(out)
    added_top = [l for l in ANCHOR.sub("", outside(e, ed)).splitlines() if l.strip() and l not in ANCHOR.sub("", outside(b, bd)).splitlines()]
    for name in changed:
        cur = find_current(RENAMED.get(name, name), [Path(old_path)])
        if cur is None: report["definition not found"].append(f"{old_path}:{name}"); continue
        t = writes.get(cur) or cur.read_text(encoding="latin-1")
        cd = defs(t)[RENAMED.get(name, name)]
        bi = [norm(renamed(b[s:x])) for s, x in bd[name]]; ei = [renamed(e[s:x]) for s, x in ed[name]]
        done = False
        for s, x in sorted(cd, reverse=True):  # every alternative definition (#if copies), back to front
            cur_norm = norm(t[s:x])
            for j, bn in enumerate(bi):
                if cur_norm == bn and norm(ei[j]) != bn:
                    t = t[:s] + ANCHOR.sub("", ei[j]) + t[x:]; done = True; break
        if done:
            writes[cur] = t; report["ported"].append(f"{cur}:{name}")
        else: report["changed upstream, merge by hand"].append(f"{old_path}:{name} -> {cur}")
    if added_top:
        cur = find_current(RENAMED.get(changed[0], changed[0]), [Path(old_path)]) if changed else (Path(old_path) if Path(old_path).exists() else None)
        if cur is None: report["top-level lines without target"].append(old_path); continue
        t = writes.get(cur) or cur.read_text(encoding="latin-1")
        decl = re.compile(r"^\s*(extern\s|__declspec\(dllimport\)|typedef\s|[A-Za-z_][\w\s\*]*\([^;{]*\)\s*;\s*$)")
        other = [l for l in added_top if not decl.match(l)]
        if other: report["non-declaration top-level lines, merge by hand"].append(f"{old_path}: {other[:3]}")
        new = [renamed(l) for l in added_top if decl.match(l) and renamed(l) not in t.splitlines()]
        if new:
            t = "\n".join(new) + "\n" + t; writes[cur] = t; report["top lines added"].append(f"{cur}: {len(new)}")
for k, v in report.items():
    print(f"{k}: {len(v)}")
    if k != "ported" and k != "top lines added":
        for x in v[:40]: print("   ", x)
if apply:
    for p, t in writes.items(): p.write_text(t, encoding="latin-1", newline="")
    print("written", len(writes))
