#!/usr/bin/env python3
"""Independently verify every stated done-criterion of the objective.

Why (round 987): the objective's criteria are checked by `scripts/gate.sh`,
`rebrew verify`, and `scripts/wine_load_check.sh` -- all project tooling.  This
script shares no code with any of them: it parses the PE headers directly with
`struct` and compares raw bytes.  Two independent implementations agreeing is a
much stronger claim than one tool reporting green, and it is the check that
catches a tool being wrong about its own project.

Defaults to the raw linker output. Structural checks are diagnostic; success
requires every file byte and the file length to equal the reference.

Usage: python3 scripts/verify_objective.py [--ref PATH] [--build PATH]
Exit status: 0 when every criterion below holds, 1 otherwise.
"""
import argparse
import struct
import sys

REF = "original/Server/server.dll"
BLD = "build/server.dll"

TEXT_VSIZE = 0x22846
IMPORT_COUNT = 100


def load(path):
    d = open(path, "rb").read()
    e = struct.unpack_from("<I", d, 0x3C)[0]
    assert d[e:e + 4] == b"PE\0\0", "not a PE: " + path
    nsec = struct.unpack_from("<H", d, e + 6)[0]
    opt = e + 24
    base = struct.unpack_from("<I", d, opt + 28)[0]
    entry = struct.unpack_from("<I", d, opt + 16)[0] + base
    secs = {}
    for i in range(nsec):
        o = opt + struct.unpack_from("<H", d, e + 20)[0] + i * 40
        nm = d[o:o + 8].rstrip(b"\0").decode()
        vs, va, rs, rp = struct.unpack_from("<IIII", d, o + 8)
        secs[nm] = (base + va, vs, rp, rs)
    return d, secs, base, entry, opt


def rva2off(secs, base, rva):
    for va, vs, rp, rs in secs.values():
        if va - base <= rva < va - base + rs:
            return rp + (rva - (va - base))
    raise ValueError("RVA 0x%x has no file-backed section" % rva)


def import_dlls(d, secs, base, opt):
    """Return (dll names, total imported symbol count)."""
    irva, _ = struct.unpack_from("<II", d, opt + 96 + 8)
    off = rva2off(secs, base, irva)
    names, total = [], 0
    while True:
        desc = d[off:off + 20]
        if len(desc) < 20 or desc == b"\0" * 20:
            break
        orig, ts, fc, name_rva, first = struct.unpack_from("<IIIII", desc, 0)
        names.append(d[rva2off(secs, base, name_rva):].split(b"\0")[0].decode())
        thunk = rva2off(secs, base, orig or first)
        while struct.unpack_from("<I", d, thunk)[0] != 0:
            total += 1
            thunk += 4
        off += 20
    return names, total


def export_names(d, secs, base, opt):
    erva, _ = struct.unpack_from("<II", d, opt + 96)
    if erva == 0:
        return []
    f = struct.unpack_from("<IIHHIIIIIII", d, rva2off(secs, base, erva))
    nnames, funcs_rva, names_rva, ords_rva = f[7], f[8], f[9], f[10]
    out = []
    for i in range(nnames):
        nr = struct.unpack_from("<I", d, rva2off(secs, base, names_rva) + i * 4)[0]
        nm = d[rva2off(secs, base, nr):].split(b"\0")[0].decode()
        fi = struct.unpack_from("<H", d, rva2off(secs, base, ords_rva) + i * 2)[0]
        frva = struct.unpack_from("<I", d, rva2off(secs, base, funcs_rva) + fi * 4)[0]
        out.append((nm, base + frva))
    return out


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--ref", default=REF)
    parser.add_argument("--build", default=BLD)
    args = parser.parse_args()
    rd, rs, rbase, rentry, ropt = load(args.ref)
    bd, bs, bbase, bentry, bopt = load(args.build)
    ok = True

    def chk(label, cond, detail=""):
        nonlocal ok
        if not cond:
            ok = False
        print("  [%s] %-46s %s" % ("PASS" if cond else "FAIL", label, detail))

    print("== independent PE verification (no project tooling)")
    chk("file size equals reference", len(rd) == len(bd), "%d bytes" % len(bd))
    chk(".text VirtualSize == 0x%x" % TEXT_VSIZE,
        bs[".text"][1] == TEXT_VSIZE, "0x%x" % bs[".text"][1])
    chk(".text VirtualSize equals reference",
        bs[".text"][1] == rs[".text"][1], "0x%x" % rs[".text"][1])
    for sec in (".rdata", ".data", ".reloc"):
        chk("%s VirtualSize equals reference" % sec,
            bs[sec][1] == rs[sec][1], "0x%x" % bs[sec][1])

    ri, rn = import_dlls(rd, rs, rbase, ropt)
    bi, bn = import_dlls(bd, bs, bbase, bopt)
    chk("import DLL list identical", ri == bi, "%d DLLs" % len(bi))
    chk("imported SYMBOL count == %d" % IMPORT_COUNT, bn == IMPORT_COUNT,
        "%d (reference %d)" % (bn, rn))
    chk("imported symbol count equals reference", bn == rn)

    rexp, bexp = export_names(rd, rs, rbase, ropt), export_names(bd, bs, bbase, bopt)
    chk("export names + VAs identical", rexp == bexp,
        ", ".join(n for n, _ in bexp))

    # byte delta and its location
    n = min(len(rd), len(bd))
    diffs = [i for i in range(n) if rd[i] != bd[i]]
    tva, tvs, trp, trs = rs[".text"]
    # raw-range test in RVA space
    t_rva = tva - rbase
    in_text = sum(1 for i in diffs if trp <= i < trp + trs)
    chk("all differing bytes inside .text", in_text == len(diffs),
        "%d of %d" % (in_text, len(diffs)))
    chk("non-.text bytes identical", len(diffs) - in_text == 0)
    print("  [INFO] residual differing bytes: %d" % len(diffs))

    # do any differing bytes touch an exported entry point or the PE entry?
    diff_va = set(t_rva + rbase + (i - trp) for i in diffs)
    touched = []
    for nm, va in bexp:
        if va in diff_va:
            touched.append(nm)
    chk("no exported entry point lies in the residue", not touched,
        "touched: %s" % touched if touched else "")
    chk("PE entry point not in the residue", bentry not in diff_va,
        "entry 0x%x" % bentry)

    # exported function bodies byte-identical (compare 0x40 bytes from each entry)
    for nm, va in bexp:
        o = rva2off(rs, rbase, va - rbase)
        same = rd[o:o + 0x40] == bd[o:o + 0x40]
        chk("export %s body identical (0x40 bytes)" % nm, same)

    chk("whole file byte-identical", rd == bd,
        "%d differing + %d length delta" % (len(diffs), abs(len(rd) - len(bd))))
    print("VERDICT: %s" % ("raw-link file identical" if ok else "OBJECTIVE NOT MET"))
    return 0 if ok else 1


if __name__ == "__main__":
    try:
        sys.exit(main())
    except (OSError, ValueError, struct.error) as exc:
        print("VERDICT: invalid verification input: %s" % exc, file=sys.stderr)
        sys.exit(2)
