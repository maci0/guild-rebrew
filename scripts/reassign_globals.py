#!/usr/bin/env python3
"""Re-assign global ownership so each TU owns one contiguous address run.

Fixes the audit's SPAN/ORDER violations by moving symbol definitions between
TUs (bracketing TU owns the symbol), and emits the 31 unowned toml symbols
with their original bytes.  All source edits are recorded, removable, and
verifiable via scripts/audit_layout.py.

Usage: python3 scripts/reassign_globals.py [--dry-run]
"""
import argparse
import pathlib
import re
import sys
import tomllib

ROOT = pathlib.Path(__file__).parent.parent
DATA_BASE = 0x10027000
DATA_OFF = 0x27000
RAW_END = DATA_BASE + 0xE000

DEF_RE = r"(?m)^[ \t]*([\w\s\*]+?)\s+(NAME)(\[\d+\])?\s*=\s*(?:\{[^;]*?\}|[^;\n]*);\s*$"


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
    return {v.get("name", ""): (int(k.split(".")[1], 16), v.get("type", "int"))
            for k, v in db.items() if v.get("section") == ".data"}


def tu_path(tu):
    # link_order entries already carry the src/server.dll/ prefix
    p = ROOT / tu
    if p.exists():
        return p
    p = ROOT / "src" / "server.dll" / tu.split("/")[-1]
    return p if p.exists() else None


def find_def(text, name):
    """line-based: returns (start, end, type, size_suffix) or None"""
    pat = re.compile(r"^[ \t]*([\w\s\*]+)\s+" + re.escape(name) +
                     r"(\[\d+\])?\s*=\s*\{")
    start = None
    typ = None
    sz = ""
    lines = text.split("\n")
    pos = 0
    for ln in lines:
        m = pat.match(ln)
        if m:
            start, typ, sz = pos, m.group(1).strip(), m.group(2) or ""
            break
        pos += len(ln) + 1
    if start is None:
        # scalar definition: TYPE name = value;  (type must be non-empty so
        # plain assignments like `name = expr;` are never mistaken)
        pat2 = re.compile(r"^[ \t]*([\w\s\*]+\s*\*?)\s+" + re.escape(name) + r"\s*=\s*[^;]+;\s*$")
        pos = 0
        for ln in lines:
            m = pat2.match(ln)
            if m and m.group(1).strip():
                start, typ, sz = pos, m.group(1).strip(), ""
                break
            pos += len(ln) + 1
    if start is None:
        return None
    # end: from start, consume until the definition's terminating ';' (brace-aware)
    depth = 0
    i = start
    n = len(text)
    while i < n:
        c = text[i]
        if c == '{':
            depth += 1
        elif c == '}':
            depth -= 1
        elif c == ';' and depth == 0:
            return start, i + 1, typ, sz
        i += 1
    return start, len(text), typ, sz




def decl_info(text, name):
    """existing declaration of name in text -> (type, size) or None"""
    m = re.search(r"^[ \t]*([\w\s\*]+?)\s+" + re.escape(name) +
                  r"(\[\s*\d*\s*\])?\s*(?:=|;)", text, re.M)
    if not m:
        return None
    size_m = re.search(r"\[(\d+)\]", m.group(2) or "")
    return m.group(1).strip(), (int(size_m.group(1)) if size_m else None)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--rounds", type=int, default=8)
    args = ap.parse_args()

    orig = (ROOT / "original" / "Server" / "server.dll").read_bytes()
    toml = load_toml()
    tus = link_order()

    # current ownership from sources: single pass per file
    owner = {}
    def_re = re.compile(r"^[ \t]*[\w\s\*]+\s+(\w+)(?:\[\d+\])?\s*=")
    for tu in tus:
        p = tu_path(tu)
        if p is None:
            continue
        for ln in p.read_text().split("\n"):
            m = def_re.match(ln)
            if m and m.group(1) in toml:
                owner[m.group(1)] = tu

    original_owner = dict(owner)

    original_owner = dict(owner)

    # Contiguous partitioning: data-contributing TUs in LINK ORDER own
    # contiguous, address-ordered symbol runs.  Partition boundaries go at the
    # K-1 largest address gaps among owned+unowned symbols.
    data_tus = [tu for tu in tus if any(n in owner for n in toml if owner.get(n) == tu)]
    if data_tus:
        # order TUs by link order (tus already is); ensure unique
        data_tus = list(dict.fromkeys(data_tus))
        # include TUs that currently own nothing but are in link order? no - only owners
        all_syms = sorted(toml.keys(), key=lambda n: toml[n][0])
        if len(data_tus) > 1:
            gaps = []
            for i in range(1, len(all_syms)):
                gaps.append((toml[all_syms[i]][0] - toml[all_syms[i-1]][0], i))
            cuts = sorted(gaps, reverse=True)[:len(data_tus)-1]
            cuts = sorted(i for _, i in cuts)
            seg = 0
            new_owner = {}
            for i, n in enumerate(all_syms):
                if seg < len(cuts) and i >= cuts[seg]:
                    seg += 1
                if seg < len(data_tus):
                    new_owner[n] = data_tus[seg]
            for n in toml:
                if n in new_owner and (n not in owner or owner[n] != new_owner[n]):
                    owner[n] = new_owner[n]

    # build edits: removals from old owners + additions to new owners
    removals = {}   # tu -> [(name, def_text)]
    additions = {}  # tu -> [def_line]
    for name, (addr, typ) in sorted(toml.items(), key=lambda kv: kv[1][0]):
        tu = owner.get(name)
        if tu is None:
            print(f"  no TU for {name} @{addr:#x}", file=sys.stderr)
            continue
        # content
        off = DATA_OFF + (addr - DATA_BASE)
        base = typ.replace("*", "").strip()
        elemsize = 4
        if base in ("char", "unsigned char"):
            elemsize = 1
        elif base in ("short", "unsigned short"):
            elemsize = 2
        if addr < RAW_END:
            end = orig.find(b"\x00", off, off + 0x200)
            if elemsize == 1 and 0 <= end < RAW_END - DATA_BASE:
                size = end - off + 1
            else:
                size = elemsize
            data = orig[off:off + size]
            init = "{\n" + "\n".join(
                "    " + ", ".join("0x%02x" % b for b in data[i:i+16]) + ","
                for i in range(0, len(data), 16)) + "\n}"
            def_line = f"{typ} {name}[{size}] = {init};"
        else:
            def_line = f"{typ} {name} = 0;"

        # remove existing definition wherever it lives
        for other_tu in set(owner.values()):
            pass
        cur = original_owner.get(name)
        if cur and cur != tu:
            removals.setdefault(cur, []).append(name)
        additions.setdefault(tu, []).append(def_line)

    # apply
    n_edit = 0
    for tu, names in removals.items():
        p = tu_path(tu)
        text = p.read_text()
        for name in names:
            r = find_def(text, name)
            if r:
                s, e, typ, sz = r
                # keep a declaration so this TU still compiles
                decl = f"extern {typ} {name}{sz};"
                text = text[:s] + decl + text[e:]
                n_edit += 1
        if not args.dry_run:
            p.write_text(text)
        print(f"  removed from {tu}: {names}", file=sys.stderr)
    for tu, lines in additions.items():
        p = tu_path(tu)
        text = p.read_text().rstrip("\n") + "\n"
        for line in lines:
            name_m = re.search(r"\s(\w+)(?:\[|\s*=)", line)
            if not name_m:
                continue
            name = name_m.group(1)
            if find_def(text, name):
                continue  # already defined here
            di = decl_info(text, name)
            if di and not di[0].startswith("extern"):
                continue  # tentative definition already present
            if di:
                # honor this TU's existing declaration type/size
                dtyp, dsize = di
                init_m = re.search(r"=\s*(\{[^;]*\}|[^;]+);?$", line)
                init = init_m.group(1) if init_m else "0"
                if dsize is not None and init.startswith("{"):
                    line = f"{dtyp} {name}[{dsize}] = {init};"
                else:
                    line = f"{dtyp} {name} = {init};"
            text += line + "\n"
            n_edit += 1
        if not args.dry_run:
            p.write_text(text)
        print(f"  added to {tu}: {len(lines)} defs", file=sys.stderr)
    print(f"edits: {n_edit}", file=sys.stderr)


if __name__ == "__main__":
    main()
