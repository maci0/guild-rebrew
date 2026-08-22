#!/usr/bin/env python3
"""Fixed-point convergence for .data placement.

Per-OBJ walk of the build (COMDAT sections count toward their OBJ, in link
order) gives each TU's actual .data start.  For every TU owning toml symbols,
compute delta = (expected address of its first toml symbol) - (its current
address) and insert/adjust a leading pad `unsigned char _dlead_<n>[] = {...}`
at the top of the TU's source so the contribution shifts by delta.  Original
bytes fill the pad for byte-exact content.  Iterate: rebuild -> measure.

Usage:
  python3 scripts/converge_layout.py [--dry-run] [--rounds N]
"""
import argparse
import pathlib
import re
import subprocess
import sys
import tomllib

ROOT = pathlib.Path(__file__).parent.parent

def _build_data_va():
    """image-base-correct .data VA of the current build (never hardcode)."""
    try:
        import pefile
        pe = pefile.PE(str(ROOT / "build" / "server.dll"))
        for s in pe.sections:
            if s.Name.rstrip(b"\x00") == b".data":
                return pe.OPTIONAL_HEADER.ImageBase + s.VirtualAddress
    except Exception:
        pass
    return 0x1002E000

DATA_BASE = 0x10027000
DATA_OFF = 0x27000
RAW_END = DATA_BASE + 0xE000

DLEAD_RE = re.compile(r"^unsigned char (_dlead_\w+)\[(\d+)\]")


def link_order():
    rsp = (ROOT / "build/CMakeFiles/server_dll.dir/objects1.rsp").read_text()
    objs = re.findall(r'"([^"]+\.obj)"|(?:^|\s)(\S+\.obj)(?=\s|$)', rsp)
    out = []
    for a, b in objs:
        p = (a or b).replace("CMakeFiles/server_dll.dir/", "")
        if p.endswith(".obj"):
            p = p[:-4]
        out.append(p)
    return out


def load_toml():
    with open(ROOT / "src" / "rebrew-data.toml", "rb") as f:
        db = tomllib.load(f)
    return {v.get("name", ""): int(k.split(".")[1], 16)
            for k, v in db.items() if v.get("section") == ".data"}


def tu_path(tu):
    p = ROOT / tu
    if p.exists():
        return p
    p = ROOT / "src" / "server.dll" / tu.split("/")[-1]
    return p if p.exists() else None


def walk():
    """per-TU (start, size, symbols{name:va}) of .data contributions."""
    toml = load_toml()
    objs = link_order()
    data_va = _build_data_va()
    tot = 0
    rows = []
    for tu in objs:
        obj = pathlib.Path(ROOT / "build" / "CMakeFiles/server_dll.dir") / (tu + ".obj")
        h = subprocess.run(["objdump", "-h", str(obj)], capture_output=True, text=True).stdout
        secs = re.findall(r"^\s+(\d+)\s+(\S+)\s+([0-9a-f]+)\s", h, re.M)
        secname = {int(a): b for a, b, _ in secs}
        t = subprocess.run(["objdump", "-t", str(obj)], capture_output=True, text=True).stdout
        syms = {}
        for line in t.splitlines():
            m = re.match(r"\[ *\d+\]\(sec +(-?\d+)\)", line)
            if not m:
                continue
            sec = int(m.group(1))
            vm = re.search(r"\s(?:0x)?([0-9a-f]{8})\s+(\S+)\s*$", line[m.end():])
            if not vm:
                continue
            off = int(vm.group(1), 16)
            sym = vm.group(2).lstrip("_")
            sname = secname.get(sec - 1)
            if sname != ".data" or sym.startswith(".") or sym.startswith("@"):
                continue
            if sym in toml:
                # COMDAT symbols all report offset 0 within their own section;
                # approximate their VA as TU start + running offset below.
                syms[sym] = None
        # sizes: regular .data sections + COMDAT .data sections
        dsize = sum(int(c, 16) for a, b, c in secs if b == ".data")
        rows.append({"tu": tu, "start": data_va + tot, "size": dsize, "syms": syms})
        tot += dsize
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--rounds", type=int, default=1)
    args = ap.parse_args()

    toml = load_toml()
    orig = (ROOT / "original" / "Server" / "server.dll").read_bytes()

    for rnd in range(args.rounds):
        rows = walk()
        for r in rows:
            if not r["syms"]:
                continue
            first = min(r["syms"], key=lambda s: toml[s])
            exp = toml[first]
            # current address: approximate from cumulative walk via objdump offsets
            # (COMDAT-free symbols only)
            obj = pathlib.Path(ROOT / "build" / "CMakeFiles/server_dll.dir") / (r["tu"] + ".obj")
            t = subprocess.run(["objdump", "-t", str(obj)], capture_output=True, text=True).stdout
            h = subprocess.run(["objdump", "-h", str(obj)], capture_output=True, text=True).stdout
            secs = re.findall(r"^\s+(\d+)\s+(\S+)\s+([0-9a-f]+)\s", h, re.M)
            secname = {int(a): b for a, b, _ in secs}
            off_first = None
            for line in t.splitlines():
                m = re.match(r"\[ *\d+\]\(sec +(-?\d+)\)", line)
                if not m:
                    continue
                sec = int(m.group(1))
                vm = re.search(r"\s(?:0x)?([0-9a-f]{8})\s+(\S+)\s*$", line[m.end():])
                if not vm:
                    continue
                sym = vm.group(2).lstrip("_")
                if sym == first and secname.get(sec - 1) == ".data":
                    off_first = int(vm.group(1), 16)
                    break
            if off_first is None:
                print(f"  {r['tu']}: {first} not found in OBJ", file=sys.stderr)
                continue
            cur = r["start"] + off_first
            # RELATIVE mode: section-offset convergence (absolute placement is
            # gated by .text size -> section VA shift; offsets are not)
            cur_off = cur - _build_data_va()
            exp_off = exp - 0x10027000
            delta = exp_off - cur_off
            if abs(delta) < 4:
                continue
            p = tu_path(r["tu"])
            if p is None:
                continue
            text = p.read_text()
            # existing dlead
            m = DLEAD_RE.search(text)
            if m:
                old_size = int(m.group(2))
            else:
                old_size = 0
            new_size = max(0, old_size + delta)
            pad_name = "_dlead_" + re.sub(r"\W", "_", r["tu"].split("/")[-1][:-2])
            # content: original bytes over [exp - new_size, exp)
            if new_size > 0 and exp - new_size >= DATA_BASE:
                off = DATA_OFF + (exp - new_size - DATA_BASE)
                data = orig[off:off + new_size]
                init = "{\n" + "\n".join(
                    "    " + ", ".join("0x%02x" % b for b in data[i:i+16]) + ","
                    for i in range(0, len(data), 16)) + "\n}"
                line = f"unsigned char {pad_name}[{new_size}] = {init};"
            else:
                line = f"unsigned char {pad_name}[{new_size}];"
            if m:
                text = text[:m.start()] + line + text[m.end():]
            else:
                # insert after the includes/annotations header: before first code
                text = re.sub(r"(\n)(?=\s*(?:extern|static|__declspec|// FUNCTION|// GLOBAL))",
                              r"\1" + line + "\n", text, count=1)
                if line not in text:
                    text = line + "\n" + text
            print(f"  {r['tu']:60} first {first:28} exp {exp:#010x} cur {cur:#010x} "
                  f"delta {delta:+#x} pad {old_size:#x}->{new_size:#x}", file=sys.stderr)
            if not args.dry_run:
                p.write_text(text)


if __name__ == "__main__":
    main()
