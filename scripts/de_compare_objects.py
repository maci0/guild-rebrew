"""Compare the COFF objects of two builds: which translation units differ in code or data?

usage: python3 scripts/de_compare_objects.py <build-dir-a> <build-dir-b>

For every .obj present in both trees (same relative path), compares the raw contents of all
sections except debug sections (.debug$*) and the relocation records with their target symbol
names; COFF timestamps are ignored. Prints the objects that differ. German ADDRESS comments do not
change an object, so the objects that differ are exactly the translation units whose English (or
Gold) code a German edit touched; only those need a measurement.
"""
import struct, sys
from pathlib import Path

def parse(path):
    b = path.read_bytes()
    if len(b) < 20: return None
    nsec, _, symptr, nsym, opthdr = struct.unpack_from("<HIIIH", b, 2)
    strtab_off = symptr + nsym * 18
    def symname(i):
        off = symptr + i * 18; raw = b[off:off + 8]
        if raw[:4] == b"\0\0\0\0":
            s = struct.unpack_from("<I", raw, 4)[0]; e = b.index(b"\0", strtab_off + s); return b[strtab_off + s:e].decode("latin-1")
        return raw.rstrip(b"\0").decode("latin-1")
    out = []
    for i in range(nsec):
        h = 20 + opthdr + i * 40
        name = b[h:h + 8].rstrip(b"\0").decode("latin-1")
        if name.startswith("/"):
            s = int(name[1:]); name = b[strtab_off + s:b.index(b"\0", strtab_off + s)].decode("latin-1")
        size, ptr, rptr, _, nrel = struct.unpack_from("<IIIIH", b, h + 16)
        if name.startswith(".debug") or name == ".drectve": continue
        data = b[ptr:ptr + size] if ptr else b""
        rels = []
        for r in range(nrel):
            va, si, typ = struct.unpack_from("<IIH", b, rptr + r * 10); rels.append((va, symname(si), typ))
        out.append((name, data, tuple(rels)))
    return out

a, bdir = Path(sys.argv[1]), Path(sys.argv[2])
diff = same = only = 0
for p in sorted(a.rglob("*.obj")):
    q = bdir / p.relative_to(a)
    if not q.exists(): only += 1; continue
    if parse(p) == parse(q): same += 1
    else: diff += 1; print("DIFF", p.relative_to(a))
print(f"same {same}, differ {diff}, only in first {only}")
