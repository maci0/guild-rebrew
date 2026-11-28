"""Map the German rows of an earlier branch state onto the current tree, through the English twins.

usage: uv run --frozen python scripts/de_replay_map.py <old-ref> rows.json names.json

For every GOLDDE/SERVERDE row of <old-ref>, its English twin there (same file and name; GOLDTL for
GOLDDE, SERVER for SERVERDE) gives an English address. The current English row at that address
names the definition now (file, name, object symbol), which survives upstream moves, merges and
renames. Rows without such a twin fall back to the same object symbol, then the same path; LIBRARY
rows keep their vendored file. rows.json feeds scripts/de_replay_rows.py. names.json maps every
English definition name of <old-ref> to its current name (by address, all English modules) for
scripts/de_port_edits.py --names.
"""
import collections, json, os, subprocess, sys, tomllib
from rebrew.cli import require_config
from rebrew.metadata.functions import load_metadata

ref, out_rows, out_names = sys.argv[1:4]
old = tomllib.loads(subprocess.run(["git", "show", f"{ref}:rebrew-functions.toml"], capture_output=True, text=True, check=True).stdout)
cur = load_metadata(require_config(target="GildeGold_TL.exe", json_mode=True).metadata_dir)
olds = {}
for k, v in old.items():
    if isinstance(v, dict) and "." in k and k.split(".")[1].startswith("0x"):
        olds[(k.split(".")[0], int(k.split(".")[1], 16))] = v
twin = {}
for (m, va), v in olds.items():
    if m in ("GOLDTL", "SERVER", "GOLD") and v.get("file") and v.get("name"): twin.setdefault((m, v["file"], v["name"]), va)
by_sym = collections.defaultdict(set)
for (m, va), r in cur.items():
    if r.get("symbol") and r.get("file"): by_sym[(m, r["symbol"])].add((r["file"], r.get("name"), r["symbol"]))
names = {}
for (m, va), v in olds.items():
    r = cur.get((m, va))
    if m in ("GOLDTL", "SERVER", "GOLD") and v.get("name") and r and r.get("name") and r["name"] != v["name"]:
        names[v["name"]] = r["name"]
rows, how = [], collections.Counter()
for (m, va), v in olds.items():
    if m not in ("GOLDDE", "SERVERDE") or not v.get("file"): continue
    en = "GOLDTL" if m == "GOLDDE" else "SERVER"
    new = None
    if v.get("kind") == "LIBRARY" and os.path.exists(v["file"]):
        new, h = (v["file"], v.get("name"), v.get("symbol")), "library"
    else:
        eva = twin.get((en, v["file"], v.get("name")))
        r = cur.get((en, eva)) if eva is not None else None
        if r and r.get("file") and r.get("symbol"): new, h = (r["file"], r["name"], r["symbol"]), "twin address"
        elif len(by_sym.get((en, v.get("symbol")), ())) == 1: new, h = next(iter(by_sym[(en, v["symbol"])])), "symbol"
        elif os.path.exists(v["file"]): new, h = (v["file"], v.get("name"), v.get("symbol")), "same path"
        else: h = "UNMAPPED"
    how[(m, h)] += 1
    rows.append({"module": m, "va": va, "old_file": v["file"], "new_file": new[0] if new else None,
                 "name": new[1] if new else v.get("name"), "symbol": new[2] if new else v.get("symbol"),
                 **{x: v.get(x) for x in ("kind", "size", "cflags", "toolchain", "blocker", "status")}})
json.dump(rows, open(out_rows, "w")); json.dump(names, open(out_names, "w"))
print(dict(how), "renamed English definitions:", len(names))
