#!/usr/bin/env python3
"""Per-function placement drift of the linked DLL against the reference.

Why this exists: `rebrew postlink --layout` patches by `.text`-relative
offset, so it only converges when every function links at the reference's VA.
Nothing measured *where* the link actually put each function until now;
`rebrew postlink` reports a single global coverage percentage and
`split_audit.py` only covers the split (LIBCMT) set.

This walks the tracked functions from `db/verify_results.json`, masks the
bytes that a relocation legitimately changes (rel32 of every branch/call, and
any immediate/displacement that points into the image), then finds the offset
in the built `.text` that maximises the number of matching unmasked bytes.
`drift = built_offset - reference_offset`, so

    drift == 0    the function is at its reference VA
    drift < 0     the link is that many bytes *short* of the reference here
    drift > 0     the link is that many bytes *long*

The drift is piecewise constant, and it changes value only where an object's
`.text` is the wrong length.  Read it as a map of which objects break the
layout, then compare the change against each object's own size error.

Usage:
    python3 scripts/link_drift.py                       # default paths
    python3 scripts/link_drift.py --built build/x.dll --reference original/Server/server.dll
    python3 scripts/link_drift.py --object-errors       # per-object size error table
    python3 scripts/link_drift.py --json
"""

from __future__ import annotations

import argparse
import json
import os
import shlex
import struct
import sys
from pathlib import Path

try:
    import capstone
except ImportError:  # pragma: no cover - the harness python always has it
    capstone = None

IMAGE_SLACK = 0x6000000
BRANCHES = {
    "call", "jmp", "je", "jne", "jl", "jle", "jg", "jge", "jb", "jbe", "ja",
    "jae", "js", "jns", "jo", "jno", "jp", "jnp", "jecxz", "loop", "loope",
    "loopne",
}


def section(path: str, name: str):
    """Return (bytes, pointer_to_raw_data, virtual_size) for one PE section."""
    blob = Path(path).read_bytes()
    e_lfanew = struct.unpack_from("<I", blob, 0x3C)[0]
    nsec = struct.unpack_from("<H", blob, e_lfanew + 6)[0]
    optsz = struct.unpack_from("<H", blob, e_lfanew + 20)[0]
    base = e_lfanew + 24 + optsz
    for i in range(nsec):
        hdr = blob[base + i * 40:base + (i + 1) * 40]
        if hdr[0:len(name)] == name.encode():
            return (blob,
                    struct.unpack_from("<I", hdr, 20)[0],
                    struct.unpack_from("<I", hdr, 8)[0])
    raise KeyError(name)


def image_base(path: str) -> int:
    blob = Path(path).read_bytes()
    e_lfanew = struct.unpack_from("<I", blob, 0x3C)[0]
    return struct.unpack_from("<I", blob, e_lfanew + 52)[0]


def build_mask(md, code: bytes, va: int, image: int) -> bytearray:
    """Mask every byte a relocation is allowed to change."""
    mask = bytearray(len(code))
    imm = capstone.x86.X86_OP_IMM
    mem = capstone.x86.X86_OP_MEM
    for ins in md.disasm(bytes(code), va):
        off = ins.address - va
        if ins.mnemonic in BRANCHES and 2 <= ins.size <= 6:
            for j in range(max(0, off + ins.size - 4), off + ins.size):
                if j < len(mask):
                    mask[j] = 1
            continue
        for op in ins.operands:
            value = None
            if op.type == imm:
                value = op.imm & 0xFFFFFFFF
            elif op.type == mem and op.mem.disp:
                value = op.mem.disp & 0xFFFFFFFF
            if value is None or not (image <= value < image + IMAGE_SLACK):
                continue
            k = ins.bytes.find(struct.pack("<I", value))
            if k >= 0:
                for j in range(4):
                    p = off + k + j
                    if p < len(mask):
                        mask[p] = 1
    return mask


def object_text_size(path: str) -> int:
    blob = Path(path).read_bytes()
    nsec = int.from_bytes(blob[2:4], "little")
    optsz = int.from_bytes(blob[16:18], "little")
    base = 20 + optsz
    total = 0
    for i in range(nsec):
        hdr = blob[base + i * 40:base + (i + 1) * 40]
        if hdr[0:5] == b".text":
            total += int.from_bytes(hdr[16:20], "little")
    return total


def object_errors(project: Path, db: list) -> list:
    """Per-object `.text` size against the reference span it has to cover.

    The span is the distance to the next object's first reference VA, so it is
    only meaningful where the objects tile the region densely; objects that
    sit before a block of untracked code report a large negative error and
    should be ignored.
    """
    by_file: dict = {}
    for row in db:
        by_file.setdefault(row["filepath"], []).append(int(row["va"], 16))
    rsp = shlex.split(
        (project / "build/CMakeFiles/server_dll.dir/objects1.rsp").read_text())
    objs = []
    for token in rsp:
        base = os.path.basename(token)
        hits = [f for f in by_file
                if os.path.basename(f).replace(".c", ".c.obj") == base]
        if hits:
            path = project / "build" / token
            if path.exists():
                objs.append((min(by_file[hits[0]]), base, path))
    objs.sort()
    out = []
    for i, (va, base, path) in enumerate(objs):
        nxt = objs[i + 1][0] if i + 1 < len(objs) else None
        if nxt is None:
            continue
        span = nxt - va
        built = object_text_size(str(path))
        out.append((va, base, span, built, built - span))
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--built", default=".scratch/server.dll.prelayout",
                    help="linked DLL before postlink (default: the POST_BUILD copy)")
    ap.add_argument("--reference", default="original/Server/server.dll")
    ap.add_argument("--db", default="db/verify_results.json")
    ap.add_argument("--project", default=".")
    ap.add_argument("--window", type=lambda s: int(s, 0), default=0x4000,
                    help="search radius around the reference offset (default 0x4000)")
    ap.add_argument("--object-errors", action="store_true",
                    help="also print the per-object size error table")
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()

    if capstone is None:
        print("capstone is required", file=sys.stderr)
        return 2

    project = Path(args.project)
    built, bptr, bvsz = section(args.built, ".text")
    ref, rptr, rvsz = section(args.reference, ".text")
    image = image_base(args.reference)
    built_bytes = built[bptr:bptr + bvsz]

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True

    db = json.loads((project / args.db).read_text())["results"]
    rows = []
    for row in db:
        va = int(row["va"], 16)
        size = row["size"]
        off = va - image - 0x1000
        if size < 24 or off < 0 or off + size > rvsz:
            continue
        target = ref[rptr + off:rptr + off + size]
        if len(target) < size:
            continue
        mask = build_mask(md, target, va, image)
        probes = [i for i in range(size) if not mask[i]]
        if len(probes) < 16:
            continue
        step = max(1, len(probes) // 48)
        probes = probes[::step][:48]
        # Several functions in this binary are byte-identical twins (the
        # cm_ExAllocAlchemist / cm_ExAllocGraveyardWorker thunks, amt_FindEntity26
        # / 27), so a plain "highest score wins" search can latch onto the
        # wrong copy and report a spurious 80-byte drift.  Break ties towards
        # the reference offset: a real placement error is at most a few tens of
        # bytes, and the neighbourhood is continuous.
        best, best_score, best_dist = None, -1, 1 << 30
        lo = max(0, off - args.window)
        hi = min(bvsz - size, off + args.window)
        for cand in range(lo, hi + 1):
            score = 0
            for i in probes:
                if built_bytes[cand + i] == target[i]:
                    score += 1
            dist = abs(cand - off)
            if score > best_score or (score == best_score and dist < best_dist):
                best_score, best, best_dist = score, cand, dist
        rows.append({
            "va": row["va"],
            "name": row["name"],
            "size": size,
            "drift": best - off,
            "confidence": best_score / len(probes),
        })

    errors = object_errors(project, db) if args.object_errors else []

    if args.json:
        print(json.dumps({
            "built_text_size": bvsz,
            "reference_text_size": rvsz,
            "delta": bvsz - rvsz,
            "functions": rows,
            "object_errors": [
                {"va": hex(v), "object": b, "span": s, "built": g, "error": e}
                for v, b, s, g, e in errors],
        }, indent=1))
        return 0

    print("built .text %#x  reference %#x  delta %+d" % (bvsz, rvsz, bvsz - rvsz))
    print()
    print("%-12s %-42s %6s %8s %6s" % ("va", "name", "size", "drift", "conf"))
    prev = None
    for r in rows:
        mark = ""
        if r["confidence"] >= 0.9 and r["drift"] != prev:
            mark = "  <== drift changes"
            prev = r["drift"]
        print("%#12x %-42s %6d %+8d %5.0f%%%s"
              % (int(r["va"], 16), r["name"], r["size"], r["drift"],
                 r["confidence"] * 100, mark))

    if errors:
        print()
        print("per-object .text size against its reference span "
              "(|error| < 200 shown; larger means untracked code follows):")
        for va, base, span, got, err in errors:
            if abs(err) < 200:
                print("  %-42s span=%-6d built=%-6d err=%+d"
                      % (base, span, got, err))
    return 0


if __name__ == "__main__":
    sys.exit(main())
