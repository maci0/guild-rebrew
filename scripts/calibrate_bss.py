#!/usr/bin/env python3
"""Calibrate the link_stubs.c BSS tail so the RAW link's .data VS == 0x174059c.

MSVC LINK's .data VirtualSize from the zero-init stub globals + the tail pad
is not exactly predictable (per-symbol alignment, obj .bss interleaving, the
CRT <common> tail), so the g_bss_tail size is calibrated empirically.

This script automates the goal's calibration loop:
  1. relink the project raw (reusing the CMake link command, /out redirected)
  2. measure the raw .data VirtualSize
  3. adjust g_bss_tail in src/link_stubs.c by the delta
  4. recompile link_stubs.c.obj and repeat until VS == the target

Usage:
    python3 scripts/calibrate_bss.py [--target 0x174059c] [--max-iters 8]
"""
import argparse
import re
import struct
import subprocess
import sys
from pathlib import Path

PROJECT = Path(__file__).resolve().parent.parent
LINK_STUBS = PROJECT / "src/link_stubs.c"
OBJ = PROJECT / "build/CMakeFiles/server_dll.dir/src/link_stubs.c.obj"
TARGET_VS = 0x174059C
MAX_ITERS = 8


def find_link_cmd():
    hits = sorted((PROJECT / "build/CMakeFiles").glob("*/link.txt"))
    if not hits:
        sys.exit("no build/CMakeFiles/*/link.txt found")
    txt = hits[0].read_text().strip()
    txt = re.sub(r"/out:[^ ]+", "/out:{out}", txt)
    txt = re.sub(r"/pdb:[^ ]+", "/pdb:{out}.pdb", txt)
    txt = f"{txt} {{options}}"
    return PROJECT / "build", txt


def read_data_vs(path):
    d = path.read_bytes()
    e = struct.unpack_from("<I", d, 0x3C)[0]
    n = struct.unpack_from("<H", d, e + 6)[0]
    optsz = struct.unpack_from("<H", d, e + 20)[0]
    sh = e + 24 + optsz
    for i in range(n):
        h = sh + i * 40
        if d[h:h + 8].rstrip(b"\0") == b".data":
            return struct.unpack_from("<I", d, h + 8)[0]
    raise SystemExit("no .data section")


def recompile():
    subprocess.run(
        ["rebrew-cmake-cl", "/nologo", "/c", "/O2", "/Gd",
         f"/Fo{OBJ}", str(LINK_STUBS)],
        cwd=PROJECT, check=True, capture_output=True,
    )


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--target", default=f"0x{TARGET_VS:x}")
    ap.add_argument("--max-iters", type=int, default=MAX_ITERS)
    args = ap.parse_args()
    target = int(args.target, 0)

    workdir, cmd_tpl = find_link_cmd()
    scratch = Path("/tmp/calibrate_bss.dll")
    for it in range(args.max_iters):
        cmd = cmd_tpl.format(out=scratch, options="")
        subprocess.run(cmd, shell=True, cwd=workdir, check=True, capture_output=True)
        vs = read_data_vs(scratch)
        delta = target - vs
        print(f"iter {it}: raw .data VS=0x{vs:x} delta={delta:+d}")
        if delta == 0:
            print("calibrated OK")
            scratch.unlink(missing_ok=True)
            return
        # adjust the tail by the delta
        text = LINK_STUBS.read_text()
        m = re.search(r"g_bss_tail\[0x([0-9a-f]+)\]", text)
        if not m:
            sys.exit("no g_bss_tail in link_stubs.c")
        new_tail = int(m.group(1), 16) + delta
        if new_tail <= 0:
            sys.exit(f"tail would go non-positive ({new_tail:#x}); manual fix needed")
        text = text.replace(f"g_bss_tail[0x{m.group(1)}]", f"g_bss_tail[0x{new_tail:x}]")
        LINK_STUBS.write_text(text)
        print(f"  tail 0x{m.group(1)} -> 0x{new_tail:x}")
        recompile()
    sys.exit(f"did not converge in {args.max_iters} iterations")


if __name__ == "__main__":
    main()
