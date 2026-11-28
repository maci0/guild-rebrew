"""Bind German v2.06 twins (GOLDDE client, SERVERDE server) to the shared English definitions.

usage: uv run python scripts/de_bind_twins.py [client|server] [--apply]

For every EN->DE pair in the mode's maps (docs/de/) whose English row (GOLDTL or SERVER)
has a C definition (status EXACT, RELOC, NEAR_MATCHING or SIZE_MISMATCH) and whose German
identity is still unbound, add `/* ADDRESS: GOLDDE|SERVERDE 0x... */` above that definition in
the shared source. The German rows (same file, name and symbol) and their SIZE (plus any
per-function compiler options, both taken from the English twin) are written through
Rebrew's locked metadata writers. No STATUS is written:
`rebrew test --all --target GildeGold_TL.exe` measures the German bytes.
Sources change only by the added comments; English objects are unaffected.
The anchor goes above every definition of the name; run scripts/de_dedupe_anchors.py --apply
afterwards to keep it only on the copy the German target compiles (#if alternatives).
"""

import csv
import sys
from collections import defaultdict
from pathlib import Path

from rebrew.cli import require_config
from rebrew.metadata.anchors import add_address_anchor
from rebrew.metadata.functions import load_metadata, record_function_rows, set_fields_batch

ROOT = Path(__file__).resolve().parent.parent
MODES = {
    "client": dict(target="GildeGold_TL.exe", en="GOLDTL", de="GOLDDE",
                   maps=["docs/de/map-en-de.csv", "docs/de/map-en-de-aligned.csv", "docs/de/map-en-de-native.csv",
                         "docs/de/map-en-de-sig.csv", "docs/de/map-en-de-measured.csv",
                         "docs/de/map-en-de-gapmnem.csv", "docs/de/map-en-de-callee.csv",
                         "docs/de/map-en-de-global.csv"]),
    "server": dict(target="server_de.dll", en="SERVER", de="SERVERDE",
                   maps=["docs/de/map-server-en-de.csv", "docs/de/map-server-en-de-native.csv",
                         "docs/de/map-server-en-de-callee.csv", "docs/de/map-server-en-de-review.csv"]),
}
BINDABLE = {"EXACT", "RELOC", "NEAR_MATCHING", "SIZE_MISMATCH"}
COPIED_FIELDS = ("cflags", "toolchain")


def pair_rank(name: str, row: dict) -> int:
    """Individually reviewed pairs (docs/de/*-review.csv) first, then exact body-hash pairs, then normalized native bodies, pairs Lennard's work measured RELOC and callee pairs from measured twins, then link-order alignment (gap/dup, gap-mnemonic), then signature pairs."""
    if "review" in name:
        return -1
    if "native" in name or "measured" in name or "callee" in name:
        return 1
    if "-sig" in name:
        return 3
    return 0 if row.get("method", "") in ("", "hash") else 2


def pairs(maps):
    ranked = sorted(
        (pair_rank(name, row), i, int(row["en_va"], 16), int(row["de_va"], 16))
        for name in maps
        for i, row in enumerate(csv.DictReader(open(ROOT / name, encoding="utf-8")))
    )
    out: dict[int, int] = {}
    used: set[int] = set()
    for _, _, en, de in ranked:
        if en not in out and de not in used:
            out[en] = de
            used.add(de)
    return out


def main() -> int:
    apply = "--apply" in sys.argv
    mode = MODES[next((a for a in sys.argv[1:] if a in MODES), "client")]
    en_mod, de_mod = mode["en"], mode["de"]
    cfg = require_config(target=mode["target"], json_mode=True)
    meta = load_metadata(cfg.metadata_dir)
    by_file: dict[str, list[tuple[int, int, dict]]] = defaultdict(list)
    skipped: dict[str, int] = defaultdict(int)
    for en, de in sorted(pairs(mode["maps"]).items()):
        row = meta.get((en_mod, en))
        if not row or row.get("kind") != "FUNCTION" or not row.get("file") or not row.get("name"):
            skipped[f"no {en_mod} definition"] += 1
            continue
        if row.get("status") not in BINDABLE:
            skipped[f"{en_mod} {row.get('status')}"] += 1
            continue
        if (de_mod, de) in meta:
            skipped[f"{de_mod} already bound"] += 1
            continue
        by_file[row["file"]].append((en, de, row))

    changed: dict[Path, str] = {}
    bound: list[tuple[int, int, dict]] = []
    for rel, items in sorted(by_file.items()):
        path = ROOT / rel
        if not path.is_file():
            skipped["source missing"] += len(items)
            continue
        text = original = path.read_text(encoding="latin-1")
        for en, de, row in items:
            try:
                text = add_address_anchor(text, de_mod, de, row["name"])
            except ValueError:
                skipped["definition not found"] += 1
                continue
            bound.append((en, de, row))
        if text != original:
            changed[path] = text

    print(f"bind {len(bound)} {de_mod} twins in {len(changed)} files; skipped {dict(skipped)}")
    if not apply:
        return 0
    for path, text in changed.items():
        path.write_text(text, encoding="latin-1", newline="")
    # Same row shape as `rebrew source register`, restricted to the German anchors added here
    # (registering whole files would also re-validate unrelated pre-existing anchors).
    functions = [
        {"module": de_mod, "va": de,
         "identity": {"file": row["file"], "name": row["name"], "kind": "FUNCTION", "symbol": row["symbol"]}}
        for en, de, row in bound
    ]
    record_function_rows(cfg.metadata_dir, functions)
    updates = []
    for en, de, row in bound:
        fields = {"size": row["size"]}
        fields.update({k: row[k] for k in COPIED_FIELDS if k in row})
        updates.append({"module": de_mod, "va": de, "fields": fields})
    set_fields_batch(cfg.metadata_dir, updates)
    print(f"registered {len(functions)} function rows; sizes set for {len(updates)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
