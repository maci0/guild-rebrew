#!/bin/bash
# split_link.sh - reproduce the split-set PoC link end to end.
#
#   LIBCMT is never reversed: scripts/map_libcmt.py says which stock member
#   body the reference has at each VA, scripts/locate_sections.py completes
#   that map with the member sections the catalog mapping cannot reach,
#   scripts/split_coff.py turns each mapped section into a command-line object,
#   scripts/emit_commons.py defines the members' commons, scripts/emit_thunks.py
#   restores the socket IAT thunks, scripts/emit_defs.py defines whatever is
#   still undefined, and scripts/make_split_rsp.py assembles the response file.
#
# Requires a configured and built CMake tree (build/CMakeFiles/server_dll.dir/
# objects1.rsp).  Usage:
#
#   scripts/split_link.sh [workdir]        # default build/split_poc
#
# Prints the built .text VirtualSize against the reference's 0x22846 and the
# per-object placement audit.
set -euo pipefail
cd "$(dirname "$0")/.."

WORK=${1:-build/split_poc}
# These five stock archives live in gitignored .scratch/, so a clean checkout
# (or a scratch cleanup -- round 172) will not have them.  Re-extract with:
#   for p in sp6:6.0-sp6-win32:msvc6.0-sp6 sp5:6.0-sp5-win32:msvc6.0-sp5 \
#            sp4:6.0-sp4-win32:msvc6.0-sp4 base:6.0-win32:msvc6.0; do
#     n=${p%%:*}; r=${p#*:}; cid=$(docker create "rebrew/msvc:${r%%:*}")
#     docker cp "$cid:/opt/${r#*:}/VC98/Lib/LIBCMT.LIB" ".scratch/libcmt/LIBCMT.$n.LIB"
#     docker rm -f "$cid"
#   done
# (sp4's path is lowercase `lib/libcmt.lib`; vc7 comes from
#  rebrew/msvc:7.0-win32 at /opt/msvc7.0/Vc7/lib/libcmt.lib.)
LIBS=(
  --lib .scratch/libcmt/LIBCMT.sp6.LIB
  --lib .scratch/libcmt/LIBCMT.sp5.LIB
  --lib .scratch/libcmt/LIBCMT.base.LIB
  --lib .scratch/libcmt/LIBCMT.vc7.LIB
  --lib .scratch/libcmt/LIBCMT.sp4.LIB
)
OBJ_RSP=build/CMakeFiles/server_dll.dir/objects1.rsp
MAP=.scratch/libcmt_map_u.json

mkdir -p "$WORK"
echo "== map"
python3 scripts/map_libcmt.py "${LIBS[@]}" --json > "$MAP"

echo "== map completion (locate member sections the catalog mapping missed)"
python3 scripts/locate_sections.py --members "${LIBS[@]}" --map "$MAP" --json \
    > "$WORK/extra.json"
python3 - "$MAP" "$WORK/extra.json" "$WORK/map_full.json" <<'PY'
import json, sys
base, extra, out = sys.argv[1], sys.argv[2], sys.argv[3]
m = json.load(open(base))
x = json.load(open(extra))["matched"]
have_va = {int(e["va"], 16) for e in m["matched"]}
have_ms = {(e["member"], e.get("section")) for e in m["matched"]}
add = [e for e in x
       if int(e["va"], 16) not in have_va and (e["member"], e.get("section")) not in have_ms]
m["matched"] = sorted(m["matched"] + add, key=lambda e: int(e["va"], 16))
json.dump(m, open(out, "w"), indent=1)
print(f"{len(add)} extra sections merged")
PY
MAP="$WORK/map_full.json"

echo "== split (member data, trimmed to the reference function's size)"
rm -rf "$WORK/split"
# `--split-rdata` puts each member's `.rdata` sections in their own objects so
# they can be ordered independently (the split blob); it also lets them fold on
# their own, which is worth 0xa0 of the prefix surplus with the prefix bytes
# still byte-identical.  `--promote-statics` makes a split member's own data
# statics external so its functions still resolve them; without it `/FORCE`
# leaves those references at RVA 0 and ~74 layout-map entries fail with a built
# value of exactly image_base (docs/TODO.md round 137).  See rounds 129-138.
python3 scripts/split_coff.py "${LIBS[@]}" --map "$MAP" \
    --out "$WORK/split" --with-data --trim --split-rdata --promote-statics \
    --drop-data crt0msg.obj --drop-data tzset.obj --drop-data intrncvt.obj \
    --drop-data mbctype.obj

echo "== import thunks"
rm -rf "$WORK/thunks"
python3 scripts/emit_thunks.py --target-bin original/Server/server.dll \
    --out "$WORK/thunks"

echo "== commons"
rm -rf "$WORK/commons"
python3 scripts/emit_commons.py "${LIBS[@]}" --map "$MAP" --out "$WORK/commons"

echo "== response file (pass 1, so emit_defs can see the real object set)"
python3 scripts/make_split_rsp.py --split "$WORK/split" --objects "$OBJ_RSP" \
    --thunks "$WORK/thunks" --commons "$WORK/commons" --out "$WORK/rsp1.rsp"

echo "== CRT .data band (library sections, reference order, before the tail)"
rm -rf "$WORK/crt_data"
python3 scripts/emit_crt_data.py --lib .scratch/libcmt/LIBCMT.sp6.LIB \
    --out "$WORK/crt_data"
CRT_SKIP=()
while IFS= read -r sym; do
    [ -n "$sym" ] && CRT_SKIP+=(--skip "$sym")
done < "$WORK/crt_data/skip.txt"

echo "== definitions (iterated to a fixed point)"
rm -rf "$WORK/defs"
python3 scripts/emit_defs.py "${LIBS[@]}" "${CRT_SKIP[@]}" --rsp "$WORK/rsp1.rsp" \
    --out "$WORK/defs"

echo "== response file (final) and link"
python3 scripts/make_split_rsp.py --split "$WORK/split" --objects "$OBJ_RSP" \
    --thunks "$WORK/thunks" --commons "$WORK/commons" --defs "$WORK/defs" \
    --out "$WORK/rsp.rsp"

if [ "${REBREW_SKIP_SPLIT_BLOB:-0}" != "1" ]; then
echo "== split blob (member .rdata sections at their reference offsets)"
# The member .rdata sections the link keeps (string literals, ___lookuptable,
# the unnamed pointer tables, the __real@8@ constants, ___dnames/___mnames)
# have reference offsets *inside* rdata_restore.c's range, which one array
# cannot express: cut it into pieces around them.  Verified: zero mismatching
# bytes in [0x1a0, 0x2608), .text placement and all four raw sizes unchanged.
# Only the all-zero literals ("", L"\0") cannot be placed unambiguously;
# crt_region/rdata_fold.c folds those.
python3 scripts/split_blob.py --rsp "$WORK/rsp.rsp" --split "$WORK/split" \
    --defs "$WORK/defs" --work "$WORK" --byte-align \
    --blob crt_region/rdata_restore.c.obj
fi

echo "== place mlock critsects and __bufin at the reference addresses"
# The four mlock critsects are one .bss block. Raw .data's lock table stores
# their reference VAs; the block currently links 0x190 too early. Growing the
# section in front moves only those symbols. __bufin is a 0x1000 common whose
# reference address is 0x11766580; an absolute definition writes that into the
# _iob slots without allocating the common.
python3 - <<'PY'
import struct
from pathlib import Path
obj = Path("build/split_poc/split/1001cfa1_.text.obj")
data = bytearray(obj.read_bytes())
nsec = struct.unpack_from("<H", data, 2)[0]
symptr, nsyms = struct.unpack_from("<II", data, 8)
bss = None
for i in range(nsec):
    off = 20 + i * 40
    name = data[off:off+8].rstrip(b"\0")
    if name == b".bss":
        bss = (i + 1, off)
        break
if bss is None:
    raise SystemExit("mlock object has no .bss")
secno, off = bss
pad = 0x190
size = struct.unpack_from("<I", data, off + 16)[0]
struct.pack_into("<I", data, off + 8, struct.unpack_from("<I", data, off + 8)[0] + pad)
struct.pack_into("<I", data, off + 16, size + pad)
# symbol values in this section, and the section aux length.
# Names longer than 8 bytes live in the string table; those are the critsects.
strtab = symptr + nsyms * 18
def sym_name(ent):
    raw = data[ent:ent+8]
    if raw[:4] == b"\0\0\0\0":
        so = struct.unpack_from("<I", raw, 4)[0]
        end = data.index(b"\0", strtab + so)
        return data[strtab + so:end]
    return raw.split(b"\0", 1)[0]
moved = []
i = 0
while i < nsyms:
    ent = symptr + i * 18
    sec = struct.unpack_from("<h", data, ent + 12)[0]
    naux = data[ent + 17]
    name = sym_name(ent)
    if sec == secno and name.startswith(b".") and naux:
        ln = struct.unpack_from("<I", data, ent + 18)[0]
        if ln == size:
            struct.pack_into("<I", data, ent + 18, size + pad)
    elif sec == secno and not name.startswith(b"."):
        struct.pack_into("<I", data, ent + 8, struct.unpack_from("<I", data, ent + 8)[0] + pad)
        moved.append(name.decode())
    i += 1 + naux
obj.write_bytes(data)
print(f"mlock .bss {size:#x} -> {size+pad:#x} moved {moved}")

# __bufin is a common in this object (sec 0, value = size). A separate
# absolute object loses to it under /FORCE:MULTIPLE, and the _iob slots then
# store the common's address. An in-object absolute is what LINK honours.
buf = Path("build/split_poc/split/1001baa4_.text.obj")
bdata = bytearray(buf.read_bytes())
bsym, bn = struct.unpack_from("<II", bdata, 8)
bstr = bsym + bn * 18
bi = 0
bufin_fixed = False
while bi < bn:
    ent = bsym + bi * 18
    naux = bdata[ent + 17]
    raw = bdata[ent:ent+8]
    if raw[:4] == b"\0\0\0\0":
        so = struct.unpack_from("<I", raw, 4)[0]
        nm = bdata[bstr+so:bdata.index(b"\0", bstr+so)]
    else:
        nm = raw.split(b"\0", 1)[0]
    if nm == b"__bufin":
        struct.pack_into("<IhHBB", bdata, ent + 8, 0x11766580, -1, 0, 2, 0)
        bufin_fixed = True
    bi += 1 + naux
if not bufin_fixed:
    raise SystemExit("__bufin missing from the _iob object")
buf.write_bytes(bdata)
print("pinned __bufin at 0x11766580")
PY
python3 - <<'PY'
import struct
from pathlib import Path

def coff_syms(data):
    symptr, nsyms, opt = struct.unpack_from("<IIH", data, 8)
    strtab = symptr + nsyms * 18
    def name_at(ent):
        raw = data[ent:ent+8]
        if raw[:4] == b"\0\0\0\0":
            so = struct.unpack_from("<I", raw, 4)[0]
            end = data.index(b"\0", strtab + so)
            return data[strtab+so:end]
        return raw.split(b"\0", 1)[0]
    return symptr, nsyms, opt, strtab, name_at

# inflate.c's "1.1.3" is the COMDAT ??_C@_05NLJN@1?41?43?$AA@. deflate's
# 8-byte array is the reference's copy but a different symbol, so inflate's
# COMDAT stays and shifts every later .data byte by 8. An external of that
# name on the array, linked first, makes LINK drop inflate's section.
alias = b"??_C@_05NLJN@1?41?43?$AA@"
defl = Path("build/CMakeFiles/server_dll.dir/references/zlib-1.1.3/deflate.c.obj")
data = bytearray(defl.read_bytes())
symptr, nsyms, opt, strtab, name_at = coff_syms(data)
have = False
i = 0
while i < nsyms:
    ent = symptr + i * 18
    if name_at(ent) == alias:
        have = True
    i += 1 + data[ent + 17]
if not have:
    nsec = struct.unpack_from("<H", data, 2)[0]
    secno = None
    off = 20 + opt
    for si in range(nsec):
        rsize, rptr = struct.unpack_from("<II", data, off + 16)
        if rptr and data[rptr:rptr+8] == b"1.1.3\x00\x00\x00":
            secno = si + 1
        for delta in (20, 24, 28):
            ptr = struct.unpack_from("<I", data, off + delta)[0]
            if ptr >= symptr:
                raise SystemExit("deflate object layout is not header-then-symtab")
        off += 40
    if secno is None:
        raise SystemExit("deflate version bytes not found")
    strlen = struct.unpack_from("<I", data, strtab)[0]
    sym = bytearray(18)
    struct.pack_into("<II", sym, 0, 0, strlen)
    struct.pack_into("<IhHBB", sym, 8, 0, secno, 0, 2, 0)
    newstr = bytearray(data[strtab:strtab+strlen]) + alias + b"\0"
    struct.pack_into("<I", newstr, 0, len(newstr))
    data = data[:strtab] + sym + newstr
    struct.pack_into("<I", data, 12, nsyms + 1)
    defl.write_bytes(data)
    print(f"aliased {alias.decode()} onto deflate .data section {secno}")
else:
    print("deflate version COMDAT alias already present")

# rdata_fold.c's pointer array is the only non-zero at the end of raw .data.
# The two empty-string COMDATs in the same object are the zeros the reference
# already has; dropping the pointer section keeps those COMDATs so the library
# copies stay folded out.
fold = Path("build/CMakeFiles/server_dll.dir/src/crt_region/rdata_fold.c.obj")
fdata = bytearray(fold.read_bytes())
symptr, nsyms, opt, strtab, name_at = coff_syms(fdata)
secno = None
i = 0
while i < nsyms:
    ent = symptr + i * 18
    if name_at(ent) == b"_g_rdata_fold_refs":
        secno = struct.unpack_from("<h", fdata, ent + 12)[0]
    i += 1 + fdata[ent + 17]
if secno is None:
    raise SystemExit("g_rdata_fold_refs missing")
off = 20 + opt + (secno - 1) * 40
name = bytes(fdata[off:off+8]).rstrip(b"\0")
if name != b".discard":
    fdata[off:off+8] = b".discard"
    flags = struct.unpack_from("<I", fdata, off + 36)[0]
    struct.pack_into("<I", fdata, off + 36, flags | 0x800)  # IMAGE_SCN_LNK_REMOVE
    fold.write_bytes(fdata)
    print("discarded g_rdata_fold_refs section")
else:
    print("g_rdata_fold_refs section already discarded")
PY
mkdir -p "$WORK/abs"
python3 scripts/emit_absolute_obj.py --name _z_errmsg_empty --value 0x10034620 \
    --out "$WORK/abs/abs__z_errmsg_empty.obj"
echo "wrote absolute _z_errmsg_empty"
# The rsp is rebuilt below; this object is added with the other absolutes.

echo "== absolute definitions for the static labels the split leaves undefined"
# split_coff splits a member per section, so a relocation to a local label in
# another of its sections ($T17396, the LIBCMT SEH scopetable malloc's prologue
# pushes) survives as an undefined *static*.  LINK never reports those: it
# defines them as absolute 0, so the seven SEH prologues in the composition
# pushed 0x10000000 where the reference pushes the scopetable address (21 bytes
# and 7 of postlink's failing operand entries; every non-split build resolves
# all seven).  Statics are object-local, so the fix is in place: promote the
# symbol to an external ABSOLUTE definition at the address the reference's own
# link wrote.  No section bytes are added, so the geometry is untouched.
python3 scripts/resolve_static_labels.py --rsp "$WORK/rsp.rsp" \
    --reference original/Server/server.dll --out "$WORK/abs" --rewrite
# z_errmsg empty-string anchor. The CMake link already carries the same
# absolute object; appending a second copy is a duplicate symbol. __bufin
# is pinned inside its own object, above.
if ! grep -q 'abs__z_errmsg_empty\.obj' "$WORK/rsp.rsp"; then
  printf ' %s' "${WORK#build/}/abs/abs__z_errmsg_empty.obj" >> "$WORK/rsp.rsp"
fi
# LIBCMT .data for the band before the historical tail. After every other
# contribution and before the gap blob, so the blob cannot cover 0xcbb0.
python3 - "$WORK/rsp.rsp" "$WORK/crt_data" <<'PY'
import sys
from pathlib import Path
rsp, folder = Path(sys.argv[1]), Path(sys.argv[2])
objs = sorted(folder.glob("crt_*.obj"))
if not objs:
    raise SystemExit("no CRT .data objects")
text = rsp.read_text().rstrip()
extra = " ".join(p.relative_to(Path("build")).as_posix() for p in objs)
rsp.write_text(text + " " + extra + "\n")
print(f"appended {len(objs)} CRT .data objects ahead of the gap blob")
PY

echo "== drop the reference .data splice"
# data_restore.c.obj is a copy of reference .data. lconv and constpow now
# come from LIBCMT (emit_crt_data.py), and the bytes after constpow through
# the file-alignment boundary are zeros, so the section still rounds to
# raw 0xe000 without pasting the reference.
python3 - "$WORK/rsp.rsp" <<'RSP'
import shlex, sys
from pathlib import Path
rsp = Path(sys.argv[1])
tokens = shlex.split(rsp.read_text())
kept = [t for t in tokens if not t.endswith("/crt_region/data_restore.c.obj")
        and not t.endswith("/data_restore_split.obj")]
rsp.write_text(" ".join(kept) + "\n")
print(f"dropped the reference .data splice ({len(tokens) - len(kept)} object(s))")
RSP

echo "== pin ___lconv_static_null at 0x10035864"
# lconv's nine empty-string slots relocate to this address. The byte sits
# inside the ioinit commons span (___pioinfo runs 0xe7f8..0xe8f8), which is
# uninitialized, so naming offset 0x74 of that section does not move any
# later BSS symbol and does emit a base reloc. An absolute symbol would
# write the same value and leave the reloc out.
python3 - "$WORK/commons/commons_ioinit.obj.obj" <<'PY'
import struct, sys
from pathlib import Path
path = Path(sys.argv[1])
data = bytearray(path.read_bytes())
symptr, nsyms = struct.unpack_from("<II", data, 8)
strtab = symptr + nsyms * 18
name = b"___lconv_static_null"
# section: __nhandle at 0, ___pioinfo at 8, size 0x108, placed at 0xe7f0.
# 0xe864 - 0xe7f0 = 0x74.
NULL_OFF = 0x74
nsec = struct.unpack_from("<H", data, 2)[0]
if nsec != 1:
    raise SystemExit(f"ioinit commons has {nsec} sections")
size = struct.unpack_from("<I", data, 20 + 16)[0]
if size < NULL_OFF + 1:
    raise SystemExit(f"ioinit .bss is {size:#x}, null wants {NULL_OFF:#x}")
i = 0
while i < nsyms:
    ent = symptr + i * 18
    naux = data[ent + 17]
    raw = data[ent:ent + 8]
    if raw[:4] == b"\0\0\0\0":
        so = struct.unpack_from("<I", raw, 4)[0]
        end = data.index(b"\0", strtab + so)
        nm = data[strtab + so:end]
    else:
        nm = raw.split(b"\0", 1)[0]
    if nm == name:
        print("___lconv_static_null already pinned")
        break
    i += 1 + naux
else:
    strlen = struct.unpack_from("<I", data, strtab)[0]
    sym = bytearray(18)
    struct.pack_into("<II", sym, 0, 0, strlen)
    struct.pack_into("<IhHBB", sym, 8, NULL_OFF, 1, 0, 2, 0)
    newstr = bytearray(data[strtab:strtab + strlen]) + name + b"\0"
    struct.pack_into("<I", newstr, 0, len(newstr))
    data = data[:strtab] + sym + newstr
    struct.pack_into("<I", data, 12, nsyms + 1)
    path.write_bytes(data)
    print(f"pinned ___lconv_static_null at section+{NULL_OFF:#x}")
PY

echo "== pad short functions (so the symbols after them keep their reference VAs)"
# `make_split_rsp.py` orders the link by reference VA, so an object whose .text
# comes out SHORT drags everything after it and the composition stops being
# position-aligned -- which makes a better-shaped but differently-sized function
# unusable.  A .text-only pad object is inserted after each short one; see
# scripts/pad_short_functions.py.
python3 scripts/pad_short_functions.py --rsp "$WORK/rsp.rsp" \
    --out-dir "$WORK/pad" --out-rsp "$WORK/rsp_pad.rsp"
RSP_PAD="${WORK#build/}/rsp_pad.rsp"

cmd=$(sed "s#@CMakeFiles/server_dll.dir/objects1.rsp#@${RSP_PAD#build/}#;
           s#/out:server.dll#/out:split_poc.dll /MAP:split_poc.map#;
           s#/implib:server.lib#/implib:split_poc.lib#;
           s# /pdb:[^ ]*##" build/CMakeFiles/server_dll.dir/link.txt)
( cd build && eval "$cmd" >/dev/null 2>&1 )
if grep -q '_g_data_restore_gap' build/split_poc.map; then
    echo "g_data_restore_gap is still in build/split_poc.map; the reference .data splice is linked" >&2
    exit 1
fi
python3 - <<'PY'
import struct
def vsize(path):
    b = open(path, 'rb').read()
    e = struct.unpack_from('<I', b, 0x3c)[0]
    n = struct.unpack_from('<H', b, e + 6)[0]
    o = struct.unpack_from('<H', b, e + 20)[0]
    off = e + 24 + o
    for i in range(n):
        s = b[off + i * 40:off + (i + 1) * 40]
        if s[0:5] == b'.text':
            return struct.unpack_from('<I', s, 8)[0]
ref = vsize('original/Server/server.dll')
got = vsize('build/split_poc.dll')
print('reference .text %#x' % ref)
print('split-set .text %#x  (%+d)' % (got, got - ref))
PY
# head closes the pipe after four lines. Under pipefail that SIGPIPE is a
# failure even when the link and the audit both succeeded.
set +o pipefail
python3 scripts/split_audit.py build/split_poc.map | head -4
set -o pipefail
