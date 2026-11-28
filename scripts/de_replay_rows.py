"""Replay the German rows (GOLDDE, SERVERDE) of an earlier branch state onto the current tree.

usage: uv run --frozen python scripts/de_replay_rows.py <rows.json> [--apply]

rows.json lists the earlier rows (module, va, name, symbol, kind, size, cflags, toolchain, blocker)
with `new_file`: the file of the current English row with the same object symbol (GOLDDE -> GOLDTL,
SERVERDE -> SERVER), as `rebrew` names it after upstream moves and merges. For each row an
ADDRESS anchor is added above that definition (`add_address_anchor`) and the row is written through
the locked writers; verdicts are measured afterwards. Run scripts/de_dedupe_anchors.py --apply
next (alternative #if definitions).
"""
import json, sys
from collections import defaultdict
from pathlib import Path
from rebrew.cli import require_config
from rebrew.metadata.anchors import add_address_anchor
from rebrew.metadata.functions import record_function_rows, set_fields_batch

rows = json.load(open(sys.argv[1])); apply = "--apply" in sys.argv
by_file = defaultdict(list)
for r in rows:
    if r["new_file"]: by_file[r["new_file"]].append(r)
changed, done, missing = {}, [], []
for f, rs in sorted(by_file.items()):
    p = Path(f); text = orig = p.read_text(encoding="latin-1")
    for r in rs:
        if r.get("kind") == "LIBRARY": done.append(r); continue  # library rows bind to vendored sources without anchors
        if "/* ADDRESS: %s 0x%08x */" % (r["module"], r["va"]) in text: done.append(r); continue
        try: text = add_address_anchor(text, r["module"], r["va"], r["name"]); done.append(r)
        except ValueError: missing.append(r)
    if text != orig: changed[p] = text
print(f"anchors in {len(changed)} files; rows {len(done)}; definition not found {len(missing)}")
for r in missing[:10]: print("  missing", r["module"], hex(r["va"]), r["name"], r["new_file"])
if apply:
    for p, t in changed.items(): p.write_text(t, encoding="latin-1", newline="")
    for target, mod in (("GildeGold_TL.exe", "GOLDDE"), ("server_de.dll", "SERVERDE")):
        cfg = require_config(target=target, json_mode=True)
        sel = [r for r in done if r["module"] == mod]
        record_function_rows(cfg.metadata_dir, [{"module": mod, "va": r["va"], "identity": {"file": r["new_file"], "name": r["name"], "kind": r["kind"] or "FUNCTION", "symbol": r["symbol"]}} for r in sel])
        set_fields_batch(cfg.metadata_dir, [{"module": mod, "va": r["va"], "fields": {k: r[k] for k in ("size", "cflags", "toolchain", "blocker") if r.get(k) is not None}} for r in sel])
    print("written")
