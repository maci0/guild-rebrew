#!/usr/bin/env python3
"""Complete .data/.bss layout: BSS arrays sized from address gaps, and the
initialized region ([0x27000,0x35000) raw) filled byte-exact from the original.

- BSS arrays: every toml .data symbol at >= 0x10035000 gets a zero-init
  definition in its owning TU, sized as the gap to the next toml entry
  (g_player_slot_0 becomes 0x1321320 = 8 * 0x264264, etc.).
- Initialized gaps: byte runs between consecutive toml symbols inside the raw
  region are emitted as `unsigned char _dpad_<addr>[N] = {<orig bytes>};` in
  the owner TU of the next symbol, so content and order reproduce the original.
- The pre-first-symbol run (0x27000..first symbol) is padded likewise.

Ownership heuristic: most referencing TU of the following symbol (first
symbol's owner for the leading pad).  Verified empirically after build.

Usage: python3 scripts/fill_data.py [--dry-run]
"""
import argparse
import pathlib
import re
import sys
import tomllib
from collections import defaultdict

ROOT = pathlib.Path(__file__).parent.parent
DATA_BASE = 0x10027000
DATA_OFF = 0x27000
RAW_SIZE = 0xE000
RAW_END = DATA_BASE + RAW_SIZE  # 0x10035000


def load_toml():
    with open(ROOT / "src" / "rebrew-data.toml", "rb") as f:
        db = tomllib.load(f)
    entries = {}
    for k, v in db.items():
        if v.get("section") == ".data":
            addr = int(k.split(".")[1], 16)
            entries[v.get("name", "")] = {
                "addr": addr,
                "type": v.get("type", "int"),
                "note": v.get("note", ""),
            }
    return entries


def ref_counts(name, files):
    counts = defaultdict(int)
    for f in files:
        try:
            t = f.read_text()
        except OSError:
            continue
        counts[str(f)] += len(re.findall(rf"\b{re.escape(name)}\b", t))
    return counts


def owner_of(names, files):
    """most-referencing file over a set of names"""
    counts = defaultdict(int)
    for n in names:
        for f, c in ref_counts(n, files).items():
            counts[f] += c
    if not counts:
        return None
    return pathlib.Path(max(counts, key=counts.get))


def hex_list(data):
    out = []
    for i in range(0, len(data), 16):
        out.append("    " + ", ".join("0x%02x" % b for b in data[i:i+16]) + ",")
    return "{\n" + "\n".join(out) + "\n}"


def insert_definition(f, name, ctype, size, init_text, dry_run):
    lines = f.read_text().splitlines()
    extern_re = re.compile(
        r"^(\s*)extern\s+([A-Za-z_][\w\s]*\**)\s+" + re.escape(name) +
        r"\s*(?:\[\s*\d*\s*\])\s*;\s*$")
    def_line = f"{ctype} {name}[{size}]"
    if init_text:
        def_line += f" = {init_text}"
    def_line += ";"
    for i, ln in enumerate(lines):
        m = extern_re.match(ln)
        if m:
            lines[i] = m.group(1) + def_line
            if not dry_run:
                f.write_text("\n".join(lines) + "\n")
            return True
    lines.append(def_line)
    if not dry_run:
        f.write_text("\n".join(lines) + "\n")
    return True


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--bss-only", action="store_true", help="skip initialized-region pads")
    args = ap.parse_args()

    orig = (ROOT / "original" / "Server" / "server.dll").read_bytes()
    toml = load_toml()
    files = sorted((ROOT / "src" / "server.dll").rglob("*.c"))
    by_addr = sorted(toml.items(), key=lambda kv: kv[1]["addr"])
    print(f"toml .data entries: {len(by_addr)}", file=sys.stderr)

    # only touch symbols still defined in link_stubs (not yet owned by a TU)
    stubs_text = (ROOT / "src" / "link_stubs.c").read_text()
    stubs_names = set(re.findall(r"([A-Za-z_]\w*)(?:\[\d+\])?\s*;$", stubs_text, re.M))

    n_bss = n_pad = 0

    # tail: last symbol -> section end (VS 0x174059c)
    SECTION_END = DATA_BASE + 0x174059C

    # leading pad: raw section start -> first symbol
    first_name, first = by_addr[0]
    lead = first["addr"] - DATA_BASE
    if lead > 0 and first["addr"] < RAW_END and not args.bss_only:
        owner = owner_of([first_name], files)
        if owner:
            data = orig[DATA_OFF:DATA_OFF + lead]
            init = hex_list(data)
            if insert_definition(owner, f"_dpad_{DATA_BASE:x}", "unsigned char",
                                 lead, init, args.dry_run):
                n_pad += 1
                print(f"  pad @{DATA_BASE:#x} +{lead:#x} -> {owner.relative_to(ROOT)}",
                      file=sys.stderr)

    for i, (name, info) in enumerate(by_addr):
        addr = info["addr"]
        nxt_addr = by_addr[i + 1][1]["addr"] if i + 1 < len(by_addr) else SECTION_END
        gap = nxt_addr - addr
        if gap <= 0x40:
            continue  # small alignment gaps only
        owner = owner_of([name] + ([by_addr[i + 1][0]] if i + 1 < len(by_addr) else []), files)
        if owner is None:
            print(f"  no owner for gap after {name} @{addr:#x}", file=sys.stderr)
            continue
        if args.bss_only and addr < RAW_END:
            continue
        if addr >= RAW_END:
            # BSS region: anonymous zero-init pad (named symbols keep their
            # scalar/field identity; the array region is the gap itself)
            if insert_definition(owner, f"_dpad_{addr:x}", "unsigned char",
                                 gap, None, args.dry_run):
                n_bss += 1
                print(f"  bss pad @{addr:#010x} +{gap:#x} -> {owner.relative_to(ROOT)}",
                      file=sys.stderr)
        else:
            # initialized region: byte-exact run from the original
            start = addr - DATA_BASE
            end = min(nxt_addr, RAW_END) - DATA_BASE
            if end > start:
                data = orig[DATA_OFF + start:DATA_OFF + end]
                init = hex_list(data)
                if insert_definition(owner, f"_dpad_{addr:x}", "unsigned char",
                                     end - start, init, args.dry_run):
                    n_pad += 1
                    print(f"  pad @{addr:#x} +{end - start:#x} -> {owner.relative_to(ROOT)}",
                          file=sys.stderr)
    print(f"bss pads: {n_bss}, init pads: {n_pad}", file=sys.stderr)


if __name__ == "__main__":
    main()
