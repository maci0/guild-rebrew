#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../../../../" && pwd)"
CL="$ROOT/tools/MSVC600/VC98/Bin/CL.EXE"
LINK="$ROOT/tools/MSVC600/VC98/Bin/LINK.EXE"

WORK="$ROOT/rebuild/experiments/msvc6_purec/fcn_10003170"
VAR_DIR="$WORK/variants_linked"
OUT="$WORK/bruteforce_fcn_10003170_linked.tsv"
BEST="$WORK/bruteforce_fcn_10003170_linked_best.tsv"
ORIG="$WORK/fcn_10003170_original_95.bin"

mkdir -p "$VAR_DIR"

if [[ ! -f "$ORIG" ]]; then
  dd if="$ROOT/original/Server/server.dll" of="$ORIG" bs=1 skip=$((0x3170)) count=95 2>/dev/null
fi

flags_list=(
  "/O2 /MT /Gd"
  "/Ox /MT /Gd"
  "/O1 /MT /Gd"
  "/Od /MT /Gd"
  "/O2 /MT /Gd /Og"
  "/O2 /MT /Gd /Oi"
  "/O2 /MT /Gd /Ot"
  "/O2 /MT /Gd /Os"
  "/O2 /MT /Gd /Oy"
  "/O2 /MT /Gd /Oy-"
  "/O2 /MT /Gd /Ob0"
  "/O2 /MT /Gd /Ob1"
  "/O2 /MT /Gd /Ob2"
  "/O2 /MT /Gd /Oa"
)

python3 - <<'PY'
from pathlib import Path

work = Path('rebuild/experiments/msvc6_purec/fcn_10003170')
var_dir = work / 'variants_linked'
tbl = (work / 'fcn_10003170_table_127.bin')

if not tbl.exists():
    # Extract from original if missing
    import subprocess
    subprocess.check_call(
        "dd if=original/Server/server.dll of=%s bs=1 skip=$((0x31dc)) count=127 2>/dev/null" % str(tbl),
        shell=True,
    )

b = tbl.read_bytes()
assert len(b) == 127

tbl_lines = []
for i in range(0, 127, 16):
    chunk = b[i:i+16]
    s = ', '.join(str(x) for x in chunk)
    if i + 16 < 127:
        s += ','
    tbl_lines.append('  ' + s)

common_preamble = r'''
typedef unsigned char u8;
typedef unsigned long u32;

#ifndef _MSC_VER
#ifndef __declspec
#define __declspec(x)
#endif
#ifndef __cdecl
#define __cdecl
#endif
#ifndef __stdcall
#define __stdcall
#endif
#endif

typedef void (__stdcall *stack_init_fn_t)(u32, void *, u32);

#pragma data_seg(".text$A")
u8 __pad_text[0x2170] = { 0 };
#pragma data_seg()

#pragma code_seg(".text$B")
'''

v0 = common_preamble + r'''
#pragma data_seg(".text$C")
u8 kClass[127] = {
%s
};
#pragma data_seg()

// FUNCTION: SERVER 0x10003170
__declspec(dllexport) u8 __cdecl fcn_10003170(u32 arg0) {
  u8 local[0x1c];
  u32 ecx;
  u32 eax;
  u8 cls;

  ((stack_init_fn_t)(*(u32*)0x10024018))(0x10003170, local, 0x1c);

  ecx = arg0;
  ecx &= 0xff;
  eax = ecx - 2;
  if (eax > 0x7e) {
    return 0;
  }

  cls = kClass[eax];
  switch (cls) {
    case 0:
      eax = *(u32 *)(local + 0x14);
      if (eax == 2) {
        return 1;
      }
      if (eax == 4) {
        return 1;
      }
      return 0;
    case 1:
      return 1;
    default:
      return 0;
  }
}

#pragma code_seg()
''' % ('\n'.join(tbl_lines))

(var_dir / 'v0000_small_switch.c').write_text(v0, encoding='ascii')

v1 = common_preamble + r'''
#pragma data_seg(".text$C")
u8 kClass[127] = {
%s
};
#pragma data_seg()

// FUNCTION: SERVER 0x10003170
__declspec(dllexport) u8 __cdecl fcn_10003170(u32 arg0) {
  u8 local[0x1c];
  u32 ecx;
  u32 eax;
  u32 edx;

  ((stack_init_fn_t)(*(u32*)0x10024018))(0x10003170, local, 0x1c);

  ecx = arg0;
  ecx &= 0xff;
  eax = ecx - 2;
  if (eax > 0x7e) {
    return 0;
  }

  edx = 0;
  ((u8 *)&edx)[0] = kClass[eax];
  switch (edx) {
    case 0:
      eax = *(u32 *)(local + 0x14);
      if (eax == 2) {
        return 1;
      }
      if (eax == 4) {
        return 1;
      }
      return 0;
    case 1:
      return 1;
    default:
      return 0;
  }
}

#pragma code_seg()
''' % ('\n'.join(tbl_lines))

(var_dir / 'v0001_small_switch_edx.c').write_text(v1, encoding='ascii')

PY

printf "diff\tflags\tvariant\n" > "$OUT"

cd "$ROOT"

for src in "$VAR_DIR"/*.c; do
  bname="$(basename "$src")"
  relsrc="${src#$ROOT/}"
  obj="rebuild/experiments/msvc6_purec/fcn_10003170/_bf_$(basename "$src" .c).obj"
  dll="rebuild/experiments/msvc6_purec/fcn_10003170/_bf_$(basename "$src" .c).dll"
  slice="rebuild/experiments/msvc6_purec/fcn_10003170/_bf_slice.bin"
  for fl in "${flags_list[@]}"; do
    set +e
    wine "$CL" /nologo /c $fl /Fo"$obj" "$relsrc" >/dev/null 2>&1
    rc=$?
    set -e
    if [[ $rc -ne 0 ]]; then
      printf "9999\t%s\t%s\n" "$fl" "$bname" >> "$OUT"
      continue
    fi
    set +e
    wine "$LINK" /nologo /DLL /NOENTRY /BASE:0x10000000 /MACHINE:IX86 \
      /ALIGN:4096 /FILEALIGN:4096 /OPT:NOREF /OPT:NOICF /INCREMENTAL:NO /NODEFAULTLIB \
      /OUT:"$dll" "$obj" >/dev/null 2>&1
    rc=$?
    set -e
    if [[ $rc -ne 0 || ! -f "$dll" ]]; then
      printf "9998\t%s\t%s\n" "$fl" "$bname" >> "$OUT"
      continue
    fi

    dd if="$dll" of="$slice" bs=1 skip=$((0x3170)) count=95 2>/dev/null
    cmp -l "$slice" "$ORIG" > "$WORK/_bf_cmp.txt" 2>/dev/null || true
    if [[ -s "$WORK/_bf_cmp.txt" ]]; then
      diffc=$(wc -l < "$WORK/_bf_cmp.txt")
    else
      diffc=0
    fi
    printf "%s\t%s\t%s\n" "$diffc" "$fl" "$bname" >> "$OUT"
  done
done

{ head -1 "$OUT"; tail -n +2 "$OUT" | sort -t$'\t' -n -k1,1 | head -200; } > "$BEST"
echo "Wrote: $OUT"
echo "Top:   $BEST"
