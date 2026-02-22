#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
CL="$ROOT/tools/MSVC600/VC98/Bin/CL.EXE"
WORK="$ROOT/rebuild/c"
VAR_DIR="$WORK/variants"
OBJ="$WORK/_bf.obj"
BIN="$WORK/_bf.bin"
SRC="$WORK/_bf.c"
OUT="$WORK/bruteforce_results.tsv"
BEST="$WORK/bruteforce_best.tsv"
ORIG="$WORK/init_original_48.bin"

mkdir -p "$VAR_DIR"

if [[ ! -f "$ORIG" ]]; then
  dd if="$ROOT/original/Server/server.dll" of="$ORIG" bs=1 skip=$((0x9320)) count=48 2>/dev/null
fi

flags_list=(
  "/O2 /MT /Gd"
  "/Ox /MT /Gd"
  "/O1 /MT /Gd"
  "/Od /MT /Gd"
  "/O2 /MT /Gz"
  "/Ox /MT /Gz"
  "/O2 /MT /Gd /Ob0"
  "/O2 /MT /Gd /Ob1"
  "/O2 /MT /Gd /Ob2"
  "/O2 /MT /Gd /Oy"
  "/O2 /MT /Gd /Oy-"
  "/Ox /MT /Gd /Oy"
  "/Ox /MT /Gd /Oy-"
  "/O1 /MT /Gd /Oy"
  "/O1 /MT /Gd /Oy-"
  "/O2 /MT /Gd /Og"
  "/O2 /MT /Gd /Oi"
  "/O2 /MT /Gd /Ot"
  "/O2 /MT /Gd /Os"
  "/O2 /MT /Gd /Oa"
  "/Ox /MT /Gd /Ob2 /Oy"
  "/O2 /MT /Gz /Ob2 /Oy"
  "/O2 /MT /Gd /GF"
  "/O2 /MT /Gd /Gy"
)

ptr_types=("__stdcall" "__cdecl")
global_types=("volatile u32*" "u32*")

call_forms=(
  'result = (*(fn_t*)0x10024050)(0,0,0x100093A0,(u32)param,0,(u32)&param);'
  'fn_t f=(fn_t)*(u32*)0x10024050; result=f(0,0,0x100093A0,(u32)param,0,(u32)&param);'
  'u32 t=*(u32*)0x10024050; result=((fn_t)t)(0,0,0x100093A0,(u32)param,0,(u32)&param);'
  'result = ((fn_t)(*(u32*)0x10024050))(0,0,0x100093A0,(u32)param,0,(u32)&param);'
)

ret_forms=(
  '*(G)=result; return result!=0;'
  'int r=(result!=0); *(G)=result; return r;'
  'u32 r=0; *(G)=result; if(result) r=1; return (int)r;'
  'int r=0; if(result) r=1; *(G)=result; return r;'
  'int r; *(G)=result; r=(result!=0); return r;'
  '*(G)=result; {int r=0; if(result) r=1; return r;}'
)

printf "diff\ttext_size\tflags\tvariant\n" > "$OUT"

vid=0
for pt in "${ptr_types[@]}"; do
  for gt in "${global_types[@]}"; do
    for cf in "${call_forms[@]}"; do
      for rf in "${ret_forms[@]}"; do
        vname="v$(printf "%04d" "$vid")"
        ((vid+=1))
        cat > "$VAR_DIR/$vname.c" <<EOF
typedef unsigned long u32;
typedef u32 ($pt *fn_t)(u32,u32,u32,u32,u32,u32);
__declspec(dllexport) int __cdecl Init(void *param){
  u32 result;
  $gt G = ($gt)0x11764094;
  $cf
  $rf
}
EOF
      done
    done
  done
done

for src in "$VAR_DIR"/*.c; do
  bname="$(basename "$src")"
  for fl in "${flags_list[@]}"; do
    set +e
    wine "$CL" /nologo /c $fl /Fo"$OBJ" "$src" >/dev/null 2>&1
    rc=$?
    set -e
    if [[ $rc -ne 0 ]]; then
      printf "9999\t0\t%s\t%s\n" "$fl" "$bname" >> "$OUT"
      continue
    fi
    if ! objcopy -O binary --only-section=.text "$OBJ" "$BIN" >/dev/null 2>&1; then
      printf "9998\t0\t%s\t%s\n" "$fl" "$bname" >> "$OUT"
      continue
    fi
    tsize=$(stat -c%s "$BIN" 2>/dev/null || echo 0)
    if [[ "$tsize" -lt 48 ]]; then
      diffc=$((48 - tsize + 1000))
      printf "%s\t%s\t%s\t%s\n" "$diffc" "$tsize" "$fl" "$bname" >> "$OUT"
      continue
    fi
    dd if="$BIN" of="$WORK/_bf48.bin" bs=1 count=48 2>/dev/null
    cmp -l "$WORK/_bf48.bin" "$ORIG" > "$WORK/_bfcmp.txt" 2>/dev/null || true
    if [[ -s "$WORK/_bfcmp.txt" ]]; then
      diffc=$(wc -l < "$WORK/_bfcmp.txt")
    else
      diffc=0
    fi
    printf "%s\t%s\t%s\t%s\n" "$diffc" "$tsize" "$fl" "$bname" >> "$OUT"
  done
done

sort -t$'\t' -n -k1,1 -k2,2 "$OUT" | head -50 > "$BEST"
echo "Wrote: $OUT"
echo "Top:   $BEST"
