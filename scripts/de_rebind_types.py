"""Re-bind type records that lint reports stale (W031) after German anchor comments changed their sources.

usage: uv run --frozen python scripts/de_rebind_types.py <lint.json>

<lint.json> is `rebrew lint --all-targets --json`. Every `type <id>:<MODULE>` W031 finding is re-bound
with `rebrew types bind` and its stored values (file, symbol, sizes, extent, cflags, offsets); the
evidence gains one sentence saying why. Only for comment-only source changes: anything else needs
the type reviewed again.
"""
import json, re, subprocess, sys, tomllib
TARGET = {"GOLDTL": "Europa1400Gold_TL.exe", "GOLD": "Europa1400Gold.exe", "SERVER": "server.dll", "GOLDDE": "GildeGold_TL.exe", "SERVERDE": "server_de.dll"}
lint = json.load(open(sys.argv[1])); types = tomllib.loads(open("rebrew-types.toml").read())["types"]
todo = set()
for t, v in lint["targets"].items():
    for f in v["files"]:
        for w in f["warnings"] + f["errors"]:
            m = re.match(r"type (\S+):(\w+): stale type evidence", w["message"]) if w["code"] == "W031" else None
            if m: todo.add((m.group(1), m.group(2)))
for ident, mod in sorted(todo):
    rec = types[ident][mod]
    note = " Rebound after German ADDRESS anchor comments were added to its source; definition, native extent and offsets unchanged."
    ev = rec["evidence"].rstrip() + ("" if rec["evidence"].rstrip().endswith(note.strip()) else note)
    cmd = ["uv", "run", "--frozen", "rebrew", "types", "bind", ident, rec["file"], rec["symbol"], "--size", str(rec["size"]),
           "--native-size", str(rec["native_size"]), "--evidence", ev, "--extent", rec.get("extent", "allocation"), "--target", TARGET[mod], "--json"]
    if rec.get("cflags"): cmd += ["--cflags", rec["cflags"]]
    for k, val in (rec.get("offsets") or {}).items(): cmd += ["--field", f"{k}={val}"]
    r = subprocess.run(cmd, capture_output=True, text=True)
    print(ident, mod, "ok" if r.returncode == 0 else "FAIL " + (r.stdout + r.stderr)[-300:])
