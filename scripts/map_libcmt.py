#!/usr/bin/env python3
"""Map every reference .text function to the static-library member that supplies it.

`rebrew lib-match` answers "is this *reversed* function actually library code?".
This answers the next question, which the LIBCMT placement work needs: for each
function in the *reference*, which archive member body is it?  The output is an
ordered (VA, member, symbol, size) list, i.e. the order the member objects have
to appear on the link line for the region to land at the reference's VAs.

Why this exists: MSVC LINK appends every archive member after every
command-line object, so linking `LIBCMT.lib` leaves all CRT code at the end of
`.text`, while the reference interleaves members with game/CRT objects (srand
at 0x1001a150, __initterm at 0x1001a758, DllMain at 0x1001b9d4).  The fix is
to put the stock member objects on the command line in reference-VA order.
This script produces that order.

Matching rule (same as the retired check_library_code.py): a reference body is
a member body when the only differing offsets are covered by the member
section's relocation fields, and at least half the bytes are fixed.  Two traps:

  * Do NOT pre-filter candidates on their raw first bytes.  A resolved `a1
    imm32` in the target against the member's zeroed reloc slot makes the
    first 8 bytes differ even though the bodies match; an 8-byte pre-filter
    silently drops ~35% of the true matches.  Scan with the mask rule.
  * `_initterm` and friends are COFF storage class 3 (static) in LIBCMT and
    are absent from the archive symbol index; class 3 must be indexed too.

Usage:
    python3 scripts/map_libcmt.py                 # text report
    python3 scripts/map_libcmt.py --json          # ordered list, machine-readable
    python3 scripts/map_libcmt.py --lib path.LIB  # non-default archive
"""

from __future__ import annotations

import argparse
import json
import struct
import sys
from pathlib import Path

MIN_BYTES = 8
MIN_FIXED_FRACTION = 0.5
IMAGE_BASE = 0x10000000

DEFAULT_LIB = Path(".scratch/libcmt/LIBCMT.sp6.LIB")
DEFAULT_STOCK = "LIBCMT.LIB"


# --------------------------------------------------------------------------
# COFF / archive parsing (kept here so the script has no project imports)
# --------------------------------------------------------------------------


def ar_members(data: bytes) -> list[tuple[str, bytes]]:
    if data[:8] != b"!<arch>\n":
        return []
    pos, out = 8, []
    while pos + 60 <= len(data):
        header = data[pos : pos + 60]
        if len(header) < 60:
            break
        name = header[0:16].decode("ascii", "replace").strip()
        try:
            size = int(header[48:58].decode().strip())
        except ValueError:
            break
        out.append((name, data[pos + 60 : pos + 60 + size]))
        pos += 60 + size + (size & 1)
    return out


def make_name_resolver(members: list[tuple[str, bytes]]):
    longnames = next((body for name, body in members if name.startswith("//")), None)

    def resolve(name: str) -> str:
        if name.startswith("/") and name[1:].isdigit() and longnames is not None:
            off = int(name[1:])
            return longnames[off : longnames.find(b"\0", off)].decode()
        return name.rstrip("/")

    return resolve


def coff_sections(obj: bytes) -> list[dict]:
    count = struct.unpack_from("<H", obj, 2)[0]
    sections = []
    for i in range(count):
        off = 20 + i * 40
        name = obj[off : off + 8].rstrip(b"\0").decode("ascii", "replace")
        raw_size, raw_ptr = struct.unpack_from("<II", obj, off + 16)
        reloc_ptr = struct.unpack_from("<I", obj, off + 24)[0]
        reloc_count = struct.unpack_from("<H", obj, off + 32)[0]
        sections.append(
            {
                "name": name,
                "raw_ptr": raw_ptr,
                "raw_size": raw_size,
                "reloc_ptr": reloc_ptr,
                "reloc_count": reloc_count,
            }
        )
    return sections


def coff_symbols(obj: bytes) -> list[tuple[str, int, int, int]]:
    ptr, count = struct.unpack_from("<II", obj, 8)
    if ptr == 0 or count == 0 or ptr + count * 18 > len(obj):
        return []
    strtab = ptr + count * 18
    out, i = [], 0
    while i < count:
        entry = obj[ptr + i * 18 : ptr + i * 18 + 18]
        raw = entry[0:8]
        if raw[0:4] == b"\0\0\0\0":
            off = struct.unpack_from("<I", raw, 4)[0]
            end = obj.find(b"\0", strtab + off)
            name = obj[strtab + off : end].decode("ascii", "replace")
        else:
            name = raw.rstrip(b"\0").decode("ascii", "replace")
        value = struct.unpack_from("<I", entry, 8)[0]
        section = struct.unpack_from("<h", entry, 12)[0]
        storage_class = entry[16]
        out.append((name, value, section, storage_class))
        i += 1 + entry[17]
    return out


def reloc_mask(obj: bytes, section: dict) -> set[int]:
    """Section-relative byte offsets covered by a relocation field."""
    mask: set[int] = set()
    for i in range(section["reloc_count"]):
        off = section["reloc_ptr"] + i * 10
        if off + 10 > len(obj):
            break
        addr = struct.unpack_from("<I", obj, off)[0]
        mask.update(range(addr, addr + 4))
    return mask


def index_library(path: Path) -> list[tuple[str, str, bytes, dict, int, set[int]]]:
    """(symbol, member, object bytes, section, symbol value, reloc mask)."""
    members = ar_members(path.read_bytes())
    resolve = make_name_resolver(members)
    index = []
    for raw_name, obj in members:
        name = resolve(raw_name)
        if not name.endswith(".obj") or len(obj) < 20:
            continue
        try:
            sections = coff_sections(obj)
            symbols = coff_symbols(obj)
        except (struct.error, IndexError):
            continue
        for sym, value, section, storage_class in symbols:
            # 2 = external, 3 = static (CRT helpers such as _initterm).
            if section <= 0 or storage_class not in (2, 3) or section > len(sections):
                continue
            if sym.startswith("."):
                continue
            sec = sections[section - 1]
            if sec["raw_size"] <= value:
                continue
            index.append((sym, name, obj, sec, value, reloc_mask(obj, sec)))
    return index


# --------------------------------------------------------------------------
# Reference side
# --------------------------------------------------------------------------


class Reference:
    def __init__(self, path: Path):
        self.img = path.read_bytes()
        e = struct.unpack_from("<I", self.img, 0x3C)[0]
        nsec = struct.unpack_from("<H", self.img, e + 6)[0]
        opt = struct.unpack_from("<H", self.img, e + 20)[0]
        base = e + 24 + opt
        self.sections = []
        for i in range(nsec):
            off = base + 40 * i
            name = self.img[off : off + 8].rstrip(b"\0").decode()
            vs, va, rs, rp = struct.unpack_from("<IIII", self.img, off + 8)
            self.sections.append((name, va, vs, rp))

    def offset(self, rva: int) -> int | None:
        for _name, va, vs, rp in self.sections:
            if va <= rva < va + max(vs, 1):
                return rp + (rva - va)
        return None

    def body(self, va: int, size: int) -> bytes | None:
        off = self.offset(va - IMAGE_BASE)
        if off is None:
            return None
        return self.img[off : off + size]


def match(index, data: bytes):
    for sym, member, obj, sec, value, mask in index:
        body = obj[sec["raw_ptr"] + value : sec["raw_ptr"] + sec["raw_size"]]
        # The catalog's size for a function is often padded (or truncated)
        # relative to the member's COMDAT section, so compare the common
        # prefix rather than requiring the member to be at least as long.
        n = min(len(body), len(data))
        if n < MIN_BYTES:
            continue
        slots = {x - value for x in mask if value <= x < value + n}
        if n - len(slots) < MIN_FIXED_FRACTION * n:
            continue
        for i in range(n):
            if body[i] != data[i] and i not in slots:
                break
        else:
            return member, sym
    return None


def load_catalog(root: Path) -> list[tuple[int, str, int]]:
    """(va, name, size) from the reccmp-format catalog CSV."""
    out = []
    for line in (root / "db/server.dll_functions.csv").read_text().splitlines():
        if line.startswith("#") or line.startswith("address"):
            continue
        parts = line.split("|")
        if len(parts) < 5:
            continue
        out.append((int(parts[0], 16), parts[1], int(parts[4])))
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--lib", default=str(DEFAULT_LIB))
    ap.add_argument("--target-bin", default="original/Server/server.dll")
    ap.add_argument("--catalog", default="db/server.dll_functions.csv")
    ap.add_argument("--from", dest="from_va", default="0x1001a150")
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()

    root = Path(__file__).resolve().parent.parent
    lib = Path(args.lib)
    if not lib.is_absolute():
        lib = root / lib
    if not lib.exists():
        sys.exit(
            f"map_libcmt: {lib} not found.  Extract it once with\n"
            f"  rebrew lib-match --stock-lib {DEFAULT_STOCK}\n"
            "or point --lib at the toolchain's LIBCMT.LIB."
        )

    index = index_library(lib)
    ref = Reference(root / args.target_bin)
    rows = load_catalog(root)
    floor = int(args.from_va, 16)

    hits, miss = [], []
    for va, name, size in rows:
        if size < MIN_BYTES:
            continue
        data = ref.body(va, size)
        if data is None:
            continue
        got = match(index, data)
        if got:
            hits.append((va, name, size, got[0], got[1]))
        else:
            miss.append((va, name, size))

    in_region = [(v, n, s) for v, n, s in rows if v >= floor and s >= MIN_BYTES]
    reg_hits = [h for h in hits if h[0] >= floor]
    if args.json:
        print(
            json.dumps(
                {
                    "library": str(lib),
                    "matched": [
                        {
                            "va": f"0x{va:x}",
                            "name": name,
                            "size": size,
                            "member": member,
                            "symbol": sym,
                        }
                        for va, name, size, member, sym in sorted(hits)
                    ],
                    "matched_bytes": sum(h[2] for h in hits),
                    "region_total": len(in_region),
                    "region_matched": len(reg_hits),
                },
                indent=1,
            )
        )
        return 0

    print(f"library: {lib}")
    print(f"indexed sections: {len(index)}")
    print(f"matched {len(hits)} functions ({sum(h[2] for h in hits)} B)")
    print(
        f"region >= {args.from_va}: {len(reg_hits)}/{len(in_region)} "
        f"({sum(h[2] for h in reg_hits)}/{sum(s for _v, _n, s in in_region)} B)"
    )
    print()
    # member order by first VA: this is the link-object order
    by_member: dict[str, list[tuple[int, str]]] = {}
    for va, name, size, member, sym in sorted(hits):
        if va >= floor:
            by_member.setdefault(member, []).append((va, sym))
    for member, funcs in sorted(by_member.items(), key=lambda kv: min(v for v, _ in kv[1])):
        order = {v: i for i, (v, _n, _s) in enumerate(sorted((r for r in rows)))}
        ids = sorted(order[v] for v, _ in funcs)
        flag = "" if all(ids[i + 1] - ids[i] == 1 for i in range(len(ids) - 1)) else "  NON-CONTIGUOUS"
        print(f"  {member:28s} {len(funcs):3d} funcs  first 0x{min(v for v,_ in funcs):x}{flag}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
