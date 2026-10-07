#!/usr/bin/env python3
"""Function list for the project scripts, from the coverage document.

Replaces the old `db/<target>_functions.csv` (a reccmp-format export rebrew no
longer writes).  Two sources, unioned, because the CSV carried both:

  * `db/coverage-<target>.toml` -- the annotated rows, with canonical sizes
    and a `markerType` that says LIBRARY / FUNCTION.
  * `db/inventory-<target>.json` -- every function the discoverer found, so an
    unreversed function still bounds the one before it.

Stdlib only (tomllib, json): the project venv has no rebrew import.
"""
from __future__ import annotations

import json
import tomllib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def coverage_document(target: str = "server.dll") -> dict:
    """The parsed `db/coverage-<target>.toml`; raises if it was never built."""
    path = ROOT / "db" / f"coverage-{target}.toml"
    if not path.is_file():
        raise SystemExit(f"{path} not found; run 'rebrew coverage build --target {target}'")
    return tomllib.loads(path.read_text(encoding="utf-8"))


def annotated_functions(target: str = "server.dll") -> list[dict]:
    """`functions` rows of the coverage document, verbatim."""
    return list(coverage_document(target).get("functions", []))


def load_functions(target: str = "server.dll") -> list[tuple[int, str, int]]:
    """`(va, name, size)` for every function, sorted by VA.

    A function in the document wins over the inventory's row for the same VA:
    its size is the canonical one, not the discoverer's guess.
    """
    by_va: dict[int, tuple[int, str, int]] = {}
    inventory = ROOT / "db" / f"inventory-{target}.json"
    if inventory.is_file():
        for entry in json.loads(inventory.read_text(encoding="utf-8")):
            by_va[int(entry["va"])] = (int(entry["va"]), str(entry.get("name", "")), int(entry["size"]))
    for row in annotated_functions(target):
        by_va[int(row["va"])] = (int(row["va"]), str(row.get("name", "")), int(row.get("size", 0)))
    return sorted(by_va.values())


def library_functions(target: str = "server.dll") -> dict[str, tuple[int, int]]:
    """normalized name -> (VA, size) for every LIBRARY row, as zlibcheck wants."""
    out: dict[str, tuple[int, int]] = {}
    for row in annotated_functions(target):
        if row.get("markerType") == "LIBRARY":
            out.setdefault(str(row.get("name", "")).lower(), (int(row["va"]), int(row.get("size", 0))))
    return out
