#!/usr/bin/env python3
"""Compare a built DLL's section geometry against the reference's.

`rebrew verify` compares function bytes and `scripts/text_match.py` compares
`.text` content; neither says whether the *file* can ever be byte-identical,
which is decided by the four raw sizes and the file offsets they imply
(`file_offset(n+1) = file_offset(n) + raw(n)`, see docs/msvc6-link-layout.md).

Usage:
    python3 scripts/section_geometry.py [built.dll ...]

Defaults to `.scratch/server.dll.prelayout` — postlink deletes `server.dll`
when it refuses a build, and the POST_BUILD step copies the honest link
output there one command earlier.

Exit status is 0 only when every raw size matches the reference's.
"""

import struct
import sys
from pathlib import Path

REFERENCE = Path("original/Server/server.dll")
DEFAULT_BUILT = [Path(".scratch/server.dll.prelayout")]


def sections(path):
    data = path.read_bytes()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    nsec = struct.unpack_from("<H", data, pe + 6)[0]
    opt = pe + 24
    out = []
    for i in range(nsec):
        off = opt + struct.unpack_from("<H", data, pe + 20)[0] + i * 40
        name = data[off : off + 8].rstrip(b"\0").decode()
        vs, va, raw, ptr = struct.unpack_from("<IIII", data, off + 8)
        out.append({"name": name, "vs": vs, "raw": raw, "ptr": ptr})
    return len(data), out


def main(argv):
    paths = [Path(a) for a in argv[1:]] or DEFAULT_BUILT
    size, ref = sections(REFERENCE)
    print(f"{REFERENCE}: {size:#x} bytes")
    bad = 0
    for path in paths:
        if not path.exists():
            print(f"{path}: missing (build first, or pass a path)")
            bad = 1
            continue
        bsize, built = sections(path)
        print(f"\n{path}: {bsize:#x} bytes")
        print(f"  {'section':9s} {'ref raw':>9s} {'raw':>9s} {'ref off':>9s} {'off':>9s}  raw")
        for r in ref:
            b = next((s for s in built if s["name"] == r["name"]), None)
            if b is None:
                print(f"  {r['name']:9s} {r['raw']:#9x} {'-':>9s} {'-':>9s} {'-':>9s}  MISSING")
                bad = 1
                continue
            ok = "ok" if b["raw"] == r["raw"] else f"raw {b['raw'] - r['raw']:+#x}"
            # .reloc is replaced wholesale by postlink, which grows it to the
            # reference's raw size — a pre-postlink difference is expected.
            if b["raw"] != r["raw"]:
                if r["name"] == ".reloc":
                    ok += "  (postlink replaces this)"
                else:
                    bad = 1
            print(
                f"  {r['name']:9s} {r['raw']:#9x} {b['raw']:#9x} "
                f"{r['ptr']:#9x} {b['ptr']:#9x}  {ok}"
            )
        for b in built:
            if not any(s["name"] == b["name"] for s in ref):
                print(f"  {b['name']:9s} {'-':>9s} {b['raw']:#9x}  extra section")
                bad = 1
        if bsize != size:
            print(f"  file size {bsize:#x} vs reference {size:#x}")
    return bad


if __name__ == "__main__":
    sys.exit(main(sys.argv))
