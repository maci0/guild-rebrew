"""Write layout/server.dll/game-includes.rsp: /INCLUDE anchors for the SERVER game code and its read-only data.

The server link uses /OPT:REF so unreferenced library code and import thunks drop out, but the game
functions are reached by address, not by symbol, and so are the shared float constants. Each function
symbol is anchored in VA order (that order fixes how the linker lays them out), followed by every
`__declspec(selectany)` constant that `game_float_constants.c` defines.
Re-run after a function row or a constant is added, renamed or removed.
"""

import re
import tomllib
from pathlib import Path

CONSTANTS = "src/Develop/DieGildeAddOn/game/game_float_constants.c"
SELECTANY = re.compile(r"^__declspec\(selectany\)\s+const\s+[\w ]+?\s+(\w+)\s*(?:\[|=)", re.M)


def project_root() -> Path:
    here = Path(__file__).resolve()
    for parent in here.parents:
        if (parent / "rebrew-project.toml").exists():
            return parent
    raise SystemExit("rebrew-project.toml not found above " + str(here))


def main() -> None:
    root = project_root()
    rows = tomllib.loads((root / "rebrew-functions.toml").read_text())
    by_va: dict[int, str] = {}
    for key, row in rows.items():
        if (
            key.startswith("SERVER.0x")
            and isinstance(row, dict)
            and row.get("marker_type") != "LIBRARY"
            and row.get("symbol")
        ):
            by_va[int(key.rpartition(".0x")[2], 16)] = row["symbol"]
    constants = sorted(SELECTANY.findall((root / CONSTANTS).read_text()))
    out = root / "layout/server.dll/game-includes.rsp"
    lines = [f"/INCLUDE:{by_va[va]}\n" for va in sorted(by_va)]
    lines += [f"/INCLUDE:_{name}\n" for name in constants]
    out.write_text("".join(lines))
    print(f"{len(by_va)} functions, {len(constants)} constants -> {out.relative_to(root)}")


if __name__ == "__main__":
    main()
