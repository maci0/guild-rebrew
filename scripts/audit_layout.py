#!/usr/bin/env python3
"""Per-TU .data/.bss layout feasibility audit.

The linked .data section is the concatenation of per-TU contributions in link
order.  For the layout to converge, every TU's owned symbols must form a
contiguous, non-decreasing address region (no TU may own symbols in two
disjoint regions, and ownership order must match link order).  This audit
reports exactly the violations that block convergence.

Usage: python3 scripts/audit_layout.py
"""
import pathlib
import re
import subprocess
import sys
import tomllib

ROOT = pathlib.Path(__file__).parent.parent


def link_order():
    rsp = (ROOT / "build/CMakeFiles/server_dll.dir/objects1.rsp").read_text()
    objs = re.findall(r'"([^"]+\.obj)"|(?:^|\s)(\S+\.obj)(?=\s|$)', rsp)
    return [pathlib.Path(ROOT / "build") / (a or b) for a, b in objs]


def obj_symbols(obj):
    h = subprocess.run(["objdump", "-h", str(obj)], capture_output=True, text=True).stdout
    secs = re.findall(r"^\s+(\d+)\s+(\S+)\s+([0-9a-f]+)\s", h, re.M)
    secname = {int(a): b for a, b, _ in secs}
    dsize = sum(int(c, 16) for a, b, c in secs if b == ".data")
    bsize = sum(int(c, 16) for a, b, c in secs if b == ".bss")
    t = subprocess.run(["objdump", "-t", str(obj)], capture_output=True, text=True).stdout
    dsyms, bsyms = set(), set()
    for line in t.splitlines():
        m = re.match(r"\[ *\d+\]\(sec +(-?\d+)\)", line)
        if not m:
            continue
        sec = int(m.group(1))
        vm = re.search(r"\s(?:0x)?([0-9a-f]{8})\s+(\S+)\s*$", line[m.end():])
        if not vm:
            continue
        sym = vm.group(2).lstrip("_")
        if sym.startswith(".") or sym.startswith("@") or not sym:
            continue
        sname = secname.get(sec - 1)
        if sname == ".data":
            dsyms.add(sym)
        elif sname == ".bss":
            bsyms.add(sym)
    return dsize, bsize, dsyms, bsyms


def load_toml():
    with open(ROOT / "src" / "rebrew-data.toml", "rb") as f:
        db = tomllib.load(f)
    return {v.get("name", ""): int(k.split(".")[1], 16)
            for k, v in db.items() if v.get("section") == ".data"}


def main():
    toml = load_toml()
    objs = link_order()
    owner = {}
    rows = []
    for obj in objs:
        dsize, bsize, dsyms, bsyms = obj_symbols(obj)
        name = str(obj).split("server_dll.dir/")[-1]
        rows.append({"obj": name, "dsize": dsize, "bsize": bsize,
                     "dsyms": dsyms, "bsyms": bsyms})
        for sym in dsyms | bsyms:
            if sym in toml:
                owner.setdefault(sym, []).append(name)

    print(f"{'TU':58} {'#sym':>4} {'min addr':>10} {'max addr':>10} {'data':>7} {'bss':>7}")
    print("-" * 104)
    prev_max = None
    violations = 0
    for r in rows:
        syms = sorted(toml[s] for s in (r["dsyms"] | r["bsyms"]) if s in toml)
        lo = syms[0] if syms else 0
        hi = syms[-1] if syms else 0
        flag = ""
        if syms and prev_max is not None and lo < prev_max:
            flag = "  <== ORDER VIOLATION"
            violations += 1
        if syms and hi - lo > 0x4000:
            flag = "  <== SPAN VIOLATION"
            violations += 1
        print(f"{r['obj']:58} {len(syms):4} {lo:#10x} {hi:#10x} {r['dsize']:#7x} {r['bsize']:#7x}{flag}")
        if hi:
            prev_max = max(prev_max or 0, hi)
    print("-" * 104)
    print(f"violations: {violations}", file=sys.stderr)

    unowned = [s for s in toml if s not in owner]
    print(f"unowned toml symbols ({len(unowned)}):", file=sys.stderr)
    for s in sorted(unowned, key=lambda x: toml[x]):
        print(f"  {s:34} {toml[s]:#010x}", file=sys.stderr)

    dup = {s: fs for s, fs in owner.items() if len(fs) > 1}
    print(f"duplicate-owned ({len(dup)}):", file=sys.stderr)
    for s, fs in sorted(dup.items(), key=lambda kv: toml[kv[0]]):
        print(f"  {s:34} {toml[s]:#010x} -> {fs}", file=sys.stderr)


if __name__ == "__main__":
    main()
