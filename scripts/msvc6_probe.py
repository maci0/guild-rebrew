#!/usr/bin/env python3
"""Compile a C snippet with the project's msvc6 and disassemble the result.

The point of this script is to answer "what does msvc6 actually emit for THIS
source" without going through the whole position-aligned composition.  That
question comes up whenever a difference is attributed to the backend: the
reference was compiled by this compiler, so the emitted order is a *function* of
the source, and the function can be sampled directly.

Each run costs one `cl` invocation (the wrapper handles the wine path
translation), so a batch of variants is fast enough to sweep a hypothesis rather
than reason about it.

Usage
-----
    # inline
    python3 scripts/msvc6_probe.py 'int f(int*p){int a=*p;return a+g;}'

    # a file, with the project's default flags
    python3 scripts/msvc6_probe.py --file probe.c

    # sweep one axis: each VARIANT line is compiled and dumped
    python3 scripts/msvc6_probe.py --sweep 'int g, h;' \\
        'int f(int*p){int a=*p;int b=g;return a+b;}' \\
        'int f(int*p){int b=g;int a=*p;return a+b;}'

Output is one block per variant: the instructions with their bytes, which is the
form the codegen docs quote.  Nothing is written outside `.scratch/msvc6-probe/`,
so a probe never touches the tree.
"""

from __future__ import annotations

import argparse
import shutil
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
WORK = ROOT / ".scratch/msvc6-probe"

#: The project's own compiler entry point.  It is the console script CMake uses,
#: so a probe is compiled by exactly the compiler the build uses.
CL = "rebrew-cmake-cl"

#: Flags the project's tree compiles with by default (`/O2 /Gd`), so a probe's
#: output is comparable to the reference's code.
DEFAULT_FLAGS = ["/O2", "/Gd"]


def _coff_text_sections(obj: bytes) -> list[tuple[str, bytes, int]]:
    """[(name, raw bytes, VA)] for every section carrying file bytes."""
    if len(obj) < 20:
        raise SystemExit("msvc6-probe: object too small to be COFF")
    nsec = struct.unpack_from("<H", obj, 2)[0]
    opt_size = struct.unpack_from("<H", obj, 16)[0]
    out: list[tuple[str, bytes, int]] = []
    for i in range(nsec):
        off = 20 + opt_size + i * 40
        sec = obj[off : off + 40]
        if len(sec) < 40:
            break
        name = sec[:8].rstrip(b"\0").decode("latin1")
        vsize, vaddr, raw_size, raw_ptr = struct.unpack_from("<IIII", sec, 8)
        if raw_size and raw_ptr:
            out.append((name, obj[raw_ptr : raw_ptr + raw_size], vaddr))
    return out


def _disassemble(code: bytes, va: int) -> list[tuple[int, str, str, str]]:
    try:
        import capstone
    except ImportError:  # pragma: no cover - environment guard
        sys.exit("msvc6-probe: capstone is required (run from the project venv)")
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    return [(i.address, i.mnemonic, i.op_str, i.bytes.hex()) for i in md.disasm(code, va)]


def compile_source(source: str, stem: str, flags: list[str]) -> Path:
    """Compile *source* and return the object path."""
    WORK.mkdir(parents=True, exist_ok=True)
    cfile = WORK / f"{stem}.c"
    objfile = WORK / f"{stem}.obj"
    cfile.write_text(source)
    if objfile.exists():
        objfile.unlink()
    cmd = [CL, "/nologo", "/c", *flags, f"/Fo{objfile.relative_to(ROOT)}", str(cfile.relative_to(ROOT))]
    proc = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    if not objfile.exists():
        detail = (proc.stdout + proc.stderr).strip().splitlines()
        raise SystemExit(f"msvc6-probe: compile failed for {stem}:\n  " + "\n  ".join(detail[-6:]))
    return objfile


def dump(objfile: Path, label: str, show_headers: bool = False) -> None:
    obj = objfile.read_bytes()
    print(f"--- {label}")
    for name, code, va in _coff_text_sections(obj):
        if not name.startswith(".text"):
            continue
        for addr, mnem, ops, raw in _disassemble(code, va or 0x1000):
            print(f"  {addr:#06x}  {raw:<20} {mnem:<9} {ops}")
        if show_headers:
            print(f"  ({name}: {len(code)} bytes)")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("source", nargs="*", help="C source text (one per variant)")
    ap.add_argument("--file", help="read the source from a file instead")
    ap.add_argument("--sweep", nargs="+", metavar="SRC", help="same as positional: several variants")
    ap.add_argument("--flags", default=" ".join(DEFAULT_FLAGS), help="cl flags (default '/O2 /Gd')")
    ap.add_argument("--keep", action="store_true", help="leave the .c/.obj files in place")
    args = ap.parse_args()

    variants: list[str] = list(args.sweep or []) or list(args.source)
    if args.file:
        variants.append(Path(args.file).read_text())
    if not variants:
        ap.error("give source text, --file, or --sweep")
    if not shutil.which(CL):
        sys.exit(f"msvc6-probe: {CL} not on PATH (is the rebrew tool install current?)")

    flags = args.flags.split()
    for n, src in enumerate(variants):
        objfile = compile_source(src, f"v{n}", flags)
        first = next((ln for ln in src.splitlines() if ln.strip()), "")
        dump(objfile, f"variant {n}: {first[:88]}")

    if not args.keep:
        for n in range(len(variants)):
            for suffix in (".c", ".obj"):
                p = WORK / f"v{n}{suffix}"
                if p.exists():
                    p.unlink()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
