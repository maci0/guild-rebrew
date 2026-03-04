#!/usr/bin/env python3
"""Reorganize src/server.dll/ into subdirectories mirroring original source structure."""

import os
import re
import subprocess
import sys

SRC = "src/server.dll"
DRY_RUN = "--dry-run" in sys.argv

# ── Helpers ──────────────────────────────────────────────────────────────────


def read_header(path):
    with open(path) as f:
        return f.read(2000)


def get_va(content):
    m = re.search(r"// (?:FUNCTION|LIBRARY|STUB): SERVER (0x[0-9a-fA-F]+)", content)
    return int(m.group(1), 16) if m else 0


def get_origin(content):
    m = re.search(r"// ORIGIN: (\w+)", content)
    return m.group(1) if m else "UNKNOWN"


# ── Address range definitions (from Ghidra xref analysis) ────────────────────
# Each tuple: (start_va, end_va_exclusive, directory)
# Functions with VA in [start, end) go to that directory.

GAME_RANGES = [
    # Units\net\broadcast.c — single function at 0x10001130
    (0x10001130, 0x10001131, "units/net"),
    # Units\Error\Error.c — log/error handlers 0x10002640..0x10003640
    (0x10002640, 0x100036D0, "units/error"),
    # gzio/stream — check_header through write_uint32_le
    # These are VFS-adjacent stream helpers
    (0x100036D0, 0x10003D20, "units/vfs"),
    # game object alloc helpers (game_object_reset through dispatch_3calls)
    # Small cluster in zlib gap, part of spiel.c-like object management
    (0x10003D20, 0x10003EA0, "game"),
    (0x10004B40, 0x10004BC0, "game"),  # dispatch_3calls, alloc_and_init
    (0x10005370, 0x10005380, "game"),  # dispatch_call
    (0x10005720, 0x100057C0, "game"),  # reset_subobject, cleanup_subobject
    (0x10006410, 0x10006440, "game"),  # get_4globals
    # Units\m_alloc\m_alloc.c — 0x10006580..0x10006E30 + pool + InitPacketPool
    (0x10006580, 0x10006EC0, "units/m_alloc"),
    # game misc between m_alloc and vfs
    (0x10006F30, 0x10006FB0, "game"),  # noop_ret1, init_player_struct
    # Units\vfs\vfs.c — 0x10008A50..0x10009020 end (cleanup, read, close, open)
    (0x10008A50, 0x10009100, "units/vfs"),
    # zlib alloc wrappers + exit handler (boundary between vfs and server)
    (0x100092E0, 0x10009320, "server"),  # alloc_mul, free_wrap, exit_handler
    # DieGildeAddOnServer\server.c — 0x10009320..0x1000AD40 end
    (0x10009320, 0x1000AFA0, "server"),
    # DieGildeAddOn\game\aemter.c — 0x1000B040..0x1000BAF0 end
    (0x1000B040, 0x1000BD50, "game"),
    # DieGildeAddOn\game\alchemistry_logic.c — 0x1000BD50..0x1000C1E0
    (0x1000BD50, 0x1000C1E0, "game"),
    # Misc game entity utilities — 0x1000C1E0..0x1000CB20
    (0x1000C1E0, 0x1000CB20, "game"),
    # DieGildeAddOn\command\command.c — 0x1000CB20..0x10010530
    (0x1000CB20, 0x10010530, "command"),
    # DieGildeAddOn\game\friedhof_logic.c — 0x10010530..0x10012000
    (0x10010530, 0x10012000, "game"),
    # DieGildeAddOn\loadsave\loadsave.c — 0x10012000..0x10014260 end
    (0x10012000, 0x10014500, "loadsave"),
    # DieGildeAddOn\command\lobbycommands.c — 0x100145E0..0x10014DB0 end
    (0x100145E0, 0x10014EE0, "command"),
    # zone/record + auxillary\plant.c — 0x10014EE0..0x100150A0 end
    (0x10014EE0, 0x100151B0, "auxillary"),
    # DieGildeAddOn\game\sim.c — 0x100151B0..0x100156C0
    (0x100151B0, 0x100156C0, "game"),
    # DieGildeAddOn\game\spiel.c — 0x100156C0..0x1001A140
    (0x100156C0, 0x1001A140, "game"),
]

# Special overrides for isolated functions in wrong ranges
OVERRIDES = {
    # GAME functions in zlib address space — actually zlib helper code
    "crc32_update.c": "zlib",
    "deflate_stored.c": "zlib",
    "fill_window.c": "zlib",
    "longest_match.c": "zlib",
    "deflate_slow.c": "zlib",
    "inflate_flush.c": "zlib",
    "bit_reverse.c": "zlib",
    "gzread.c": "units/vfs",  # gzio is a VFS-layer function
    "game_getbyte.c": "units/vfs",  # gzio helper
    "free_wrap.c": "zlib",  # zlib allocator wrapper (zcalloc/zcfree)
    # CRT-range game function
    "game_check_bits_clear.c": "crt",  # at 0x10021538, in CRT region
}

# ── Build complete mapping ───────────────────────────────────────────────────

files = sorted(f for f in os.listdir(SRC) if f.endswith(".c"))
moves = {}  # filename -> target_dir
stats = {
    "zlib": 0,
    "crt": 0,
    "server": 0,
    "game": 0,
    "command": 0,
    "loadsave": 0,
    "auxillary": 0,
    "units/net": 0,
    "units/error": 0,
    "units/m_alloc": 0,
    "units/vfs": 0,
    "unmapped": 0,
}

for fname in files:
    path = os.path.join(SRC, fname)
    content = read_header(path)
    origin = get_origin(content)
    va = get_va(content)

    # Check overrides first
    if fname in OVERRIDES:
        target = OVERRIDES[fname]
    # ZLIB origin → zlib/
    elif origin == "ZLIB":
        target = "zlib"
    # MSVCRT origin → crt/
    elif origin == "MSVCRT":
        target = "crt"
    # GAME origin → use address ranges
    elif origin == "GAME":
        target = None
        for start, end, directory in GAME_RANGES:
            if start <= va < end:
                target = directory
                break
        if target is None:
            # Fallback: if in zlib range (0x10001000-0x100089B0 roughly)
            if va < 0x10002640 or (0x100036D0 <= va < 0x10003D20):
                target = "zlib"
            else:
                target = "game"  # default for unmapped GAME
                stats["unmapped"] += 1
    else:
        target = "game"

    moves[fname] = target
    if target in stats:
        stats[target] += 1

# ── Print plan ───────────────────────────────────────────────────────────────

print("=== Reorganization Plan ===\n")
for d in sorted(set(moves.values())):
    flist = sorted(f for f, t in moves.items() if t == d)
    print(f"{d}/ ({len(flist)} files)")
    for f in flist[:5]:
        print(f"  {f}")
    if len(flist) > 5:
        print(f"  ... and {len(flist) - 5} more")
    print()

print(f"\n=== Stats ===")
for k, v in sorted(stats.items(), key=lambda x: -x[1]):
    if v:
        print(f"  {k}: {v}")
print(f"  TOTAL: {len(moves)}")

if DRY_RUN:
    print("\n[DRY RUN] No files moved.")
    sys.exit(0)

# ── Execute moves ────────────────────────────────────────────────────────────

print("\n=== Executing moves ===")

# Create directories
dirs = sorted(set(moves.values()))
for d in dirs:
    target_path = os.path.join(SRC, d)
    os.makedirs(target_path, exist_ok=True)
    print(f"  mkdir -p {target_path}")

# Move files with git mv
moved = 0
errors = 0
for fname, target in sorted(moves.items()):
    src_path = os.path.join(SRC, fname)
    dst_path = os.path.join(SRC, target, fname)
    if not os.path.exists(src_path):
        print(f"  SKIP (missing): {fname}")
        continue
    try:
        os.rename(src_path, dst_path)
        moved += 1
    except OSError as e:
        print(f"  ERROR: {fname} -> {target}/: {e}")
        errors += 1

print(f"\nDone: {moved} moved, {errors} errors")

# Also move CATALOG.md to root (it stays at top level)
# CATALOG.md is auto-generated, leave it where it is
