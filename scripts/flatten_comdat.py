#!/usr/bin/env python3
"""Re-emit a COFF object's `.text` sections as ordinary, non-COMDAT objects.

Why (round 18).  Under `/OPT:REF` LINK does not treat a *data-only* reference
as a reference when deciding where to put a COMDAT section.  A function reached
only from a `.data` table (91 of them in server.dll, `cm_ChainNoop` being the
first that mattered) has its section kept -- the table's relocations still need
it -- but relocated after every command-line object, and the `.data`
relocations are left pointing at the old address.  The result links, matches
`.text` size, import count, thunk count and call count, and is silently wrong:
a dispatch table calls the wrong function.  See docs/TODO.md rounds 14 and 17.

An ordinary (non-COMDAT) section has no such rule: it is placed in link order,
so the object lands at the reference address its response-file position implies
and the relocations stay correct.

VC6 marks function sections COMDAT by default, so this cannot be switched off
with a flag; it has to be done to the object.  `scripts/split_coff.py`'s
`build_object` already rebuilds a section with its relocations intact (it is
what the library split uses), so this only has to clear
`IMAGE_SCN_LNK_COMDAT` (0x1000) in the characteristics of what comes back.

Usage:
    python3 scripts/flatten_comdat.py --rsp build/split_poc/rsp.rsp \\
        --objects a.c.obj b.c.obj --out-dir build/flat --out-rsp build/rsp_flat.rsp
"""

from __future__ import annotations

import argparse
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from split_coff import Coff  # noqa: E402  (kept for the section scan)

COMDAT = 0x1000


def strip_comdat(obj: bytes) -> bytes:
    """Clear IMAGE_SCN_LNK_COMDAT on every section of a COFF object.

    A byte-level patch of the original object, deliberately not a rebuild: the
    first attempt rebuilt the `.text` alone with `split_coff.build_object` and
    every `??_C@...` string literal went unresolved, because those live in the
    same object's `.rdata`.  Patching the section headers in place keeps the
    relocations, the `.rdata` and the line numbers exactly as CL emitted them,
    and the only thing that changes is one characteristics bit.
    """
    b = bytearray(obj)
    n = struct.unpack_from("<H", b, 2)[0]
    opt = struct.unpack_from("<H", b, 16)[0]
    off = 20 + opt
    for _ in range(n):
        chars = struct.unpack_from("<I", b, off + 36)[0]
        struct.pack_into("<I", b, off + 36, chars & ~COMDAT)
        off += 40
    return bytes(b)


def flatten(path: Path, out_dir: Path, stem: str) -> list[str]:
    """Write the object with its COMDAT bits cleared.  Returns its file name."""
    out = out_dir / f"{stem}.obj"
    out.write_bytes(strip_comdat(path.read_bytes()))
    return [out.name]


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--rsp", required=True)
    ap.add_argument("--objects", nargs="+", required=True,
                    help="object basenames to flatten")
    ap.add_argument("--out-dir", required=True)
    ap.add_argument("--out-rsp", required=True)
    args = ap.parse_args()

    out_dir = Path(args.out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)
    workdir = Path(args.rsp).parent.parent          # .../split_poc -> build
    rsp = Path(args.rsp).read_text().split()

    wanted = {Path(o).name for o in args.objects}
    flat: dict[str, list[str]] = {}
    for o in rsp:
        name = Path(o).name
        if name not in wanted:
            continue
        p = Path(o) if Path(o).exists() else workdir / o
        if not p.exists():
            print(f"skip {name}: not found", file=sys.stderr)
            continue
        stem = name[:-4] if name.endswith(".obj") else name
        made = flatten(p, out_dir, stem)
        if made:
            flat[name] = made
        else:
            print(f"skip {name}: no .text section", file=sys.stderr)

    lines = []
    for o in rsp:
        name = Path(o).name
        if name in flat:
            lines += [f"{out_dir.name}/{n}" for n in flat[name]]
        else:
            lines.append(o)
    Path(args.out_rsp).write_text("\n".join(lines) + "\n")
    print(f"flattened {len(flat)} object(s) into {out_dir}; "
          f"wrote {args.out_rsp}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
