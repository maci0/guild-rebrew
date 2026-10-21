"""Write the linked scaffold manifest from an MSVC map.

The map is the link result. A symbol is scaffold storage when its object
is ``symbol_stubs.c.obj`` or ``abi_stubs.c.obj``. ``WinMain`` and a renamed function that the map
attributes to another object are real definitions, not scaffold.

    uv run python stubs/linked_manifest.py \
        build/Europa1400Gold.map stubs/gold/symbols.json
    uv run python stubs/linked_manifest.py \
        build/Europa1400Gold_TL.map stubs/goldtl/symbols.json
"""

from __future__ import annotations

import json
import sys
from pathlib import Path

from rebrew.data_ownership import parse_link_map


def publics(text: str) -> list[tuple[str, str]]:
    """``(symbol, object)`` from the map's public-symbol lines."""
    rows = []
    for row in parse_link_map(text):
        origin = row.object or f"{row.library}:{row.member}"
        if ".obj" in origin:
            rows.append((row.name, origin))
    return rows


def main() -> None:
    if len(sys.argv) != 3:
        raise SystemExit("usage: linked_manifest.py MAP OUT.json")
    map_path = Path(sys.argv[1])
    rows = publics(map_path.read_text(encoding="utf-8", errors="replace"))
    stub_objects = {"symbol_stubs.c.obj", "abi_stubs.c.obj"}
    stub = sorted(sym for sym, obj in rows if obj in stub_objects)
    real = {
        sym: obj
        for sym, obj in rows
        if sym in {"_WinMain@16", "_fcn_004959f0", "_cm_TestCommandResult", "_DirectInput8Create@20"}
        or sym.startswith("_IID_IDirect")
        or sym in {"_inflate", "_crc32", "_g_slot_table"}
    }
    doc = {
        "map": str(map_path),
        "stub_object": "symbol_stubs.c.obj",
        "stub_objects": sorted({obj for _, obj in rows if obj in stub_objects}),
        "stub_symbol_count": len(stub),
        "checked_symbols": real,
        "stub_symbols": stub,
    }
    Path(sys.argv[2]).write_text(json.dumps(doc, indent=2) + "\n", encoding="utf-8")
    print(f"wrote {sys.argv[2]} ({len(stub)} stub symbols)")


if __name__ == "__main__":
    main()
