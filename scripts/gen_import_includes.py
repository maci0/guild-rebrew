"""Write layout/server.dll/import-includes.rsp: the /INCLUDEs that make LINK load the reference's import order.

LINK numbers IAT slots by sorting the loaded import contributions with the runtime's qsort, keyed only by DLL
name (docs/msvc6-link-layout.md section 73), so the slot order is a fixed function of the load order. The
reference's hint/name table records that load order. Its KERNEL32 imports came in three library passes: the
ones the game objects reference, then (after USER32, WS2_32 and WINMM) the ones LIBCMT's members reference,
then RtlUnwind and the rest once exsup.obj loaded. Only the start of the first group and the other DLLs are
forced here, in hint/name order; the objects and LIBCMT's own references load the rest. WS2_32 imports by
ordinal and has no hint/name entries; its includes run in reverse IAT order, which section 5c measured to
reproduce its slots.
"""

import re
from pathlib import Path

import lief

from rebrew.config import load_config

SOURCE = "src/crt_region/crt_imports.c"
# KERNEL32 imports forced in the reference's load order: Error.c's twenty, the first of the game's library
# pass. The game objects' own references load the rest of that pass in object order (vfs.c's discarded file
# search imports, then server.c's eight, docs/msvc6-link-layout.md 5f). An /INCLUDE keeps its import past
# /OPT:REF, so an import the reference drops cannot be forced here.
GAME_KERNEL32_IMPORTS = 20


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
    cfg = load_config(root, target="server.dll")
    pe = lief.PE.parse(str(cfg.target_binary))
    if pe is None:
        raise SystemExit(f"cannot parse {cfg.target_binary}")
    # Proven WinSock ordinal spellings in this server's import recipe.
    ordinals = {1: "accept", 2: "bind", 3: "closesocket", 8: "htonl", 9: "htons",
                10: "ioctlsocket", 13: "listen", 16: "recv", 19: "send",
                20: "sendto", 21: "setsockopt", 22: "shutdown", 23: "socket",
                111: "WSAGetLastError", 115: "WSAStartup", 116: "WSACleanup"}
    load_order: dict[str, list[str]] = {}
    for entry in pe.imports:
        rows = sorted(enumerate(entry.entries), key=lambda p: (0 if p[1].is_ordinal else p[1].data, p[0]))
        names = []
        for _, imp in rows:
            if imp.is_ordinal:
                if entry.name.upper() != "WS2_32.DLL" or imp.ordinal not in ordinals:
                    raise SystemExit(f"unsupported ordinal {entry.name}!{imp.ordinal}")
                names.append(ordinals[imp.ordinal])
            else:
                names.append(imp.name)
        load_order[entry.name.upper()] = names
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
