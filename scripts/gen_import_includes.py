"""Write layout/server.dll/import-includes.rsp: the /INCLUDEs that make LINK load the reference's import order.

LINK numbers IAT slots by sorting the loaded import contributions with the runtime's qsort, keyed only by DLL
name (docs/msvc6-link-layout.md section 73), so the slot order is a fixed function of the load order. The
reference's hint/name table records that load order. Its KERNEL32 imports came in three library passes: the
ones the game objects reference, then (after USER32, WS2_32 and WINMM) the ones LIBCMT's members reference,
then RtlUnwind and the rest once exsup.obj loaded. Only the first group and the other DLLs are forced here, in
hint/name order; LIBCMT's own references load the rest. WS2_32 imports by ordinal and has no hint/name entries;
its includes run in reverse IAT order, which section 5c measured to reproduce its slots.
"""

import re
from pathlib import Path

import pefile

REFERENCE = "original/Server/server.dll"
SOURCE = "src/crt_region/crt_imports.c"
# KERNEL32 imports the game objects reference: the reference's first KERNEL32 load pass, which ends where its
# qsort permutation places the WS2_32 block; load index 30 (GetLocalTime) starts the second pass.
GAME_KERNEL32_IMPORTS = 30


def project_root() -> Path:
    here = Path(__file__).resolve()
    for parent in here.parents:
        if (parent / "rebrew-project.toml").exists():
            return parent
    raise SystemExit("rebrew-project.toml not found above " + str(here))


def main() -> None:
    root = project_root()
    decorated = {
        m[1].split("@")[0]: m[1]
        for m in re.finditer(r'/include:__imp__([^"]+)"', (root / SOURCE).read_text())
    }
    pe = pefile.PE(str(root / REFERENCE))
    load_order: dict[str, list[str]] = {}
    for entry in pe.DIRECTORY_ENTRY_IMPORT:
        rows = sorted(enumerate(entry.imports), key=lambda p: (p[1].hint_name_table_rva or 0, p[0]))
        load_order[entry.dll.decode().upper()] = [imp.name.decode() for _, imp in rows]
    ordered = (
        load_order["KERNEL32.DLL"][:GAME_KERNEL32_IMPORTS]
        + load_order["USER32.DLL"]
        + load_order["WS2_32.DLL"][::-1]
        + load_order["WINMM.DLL"]
    )
    out = root / "layout/server.dll/import-includes.rsp"
    out.write_text("".join(f"/INCLUDE:__imp__{decorated[n]}\n" for n in ordered))
    print(f"{len(ordered)} imports -> {out.relative_to(root)}")


if __name__ == "__main__":
    main()
