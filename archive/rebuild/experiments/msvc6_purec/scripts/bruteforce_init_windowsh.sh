#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"

CL="tools/MSVC600/VC98/Bin/CL.EXE"
INC="tools/MSVC600/VC98/Include"
WORK="rebuild/c"
VAR_DIR="$WORK/variants_winh"
OBJ="$WORK/_winh.obj"
BIN="$WORK/_winh.bin"
ORIG="$WORK/init_original_48.bin"
OUT="$WORK/bruteforce_winh_results.tsv"
BEST="$WORK/bruteforce_winh_best.tsv"

mkdir -p "$VAR_DIR"

if [[ ! -f "$ORIG" ]]; then
  dd if=original/Server/server.dll of="$ORIG" bs=1 skip=$((0x9320)) count=48 2>/dev/null
fi

flags_list=(
  "/O2 /MT /Gd"
  "/Ox /MT /Gd"
  "/O2 /MT /Gz"
  "/O2 /MT /Gd /Ob0"
  "/O2 /MT /Gd /Ob1"
  "/O2 /MT /Gd /Ob2"
  "/O2 /MT /Gd /Oy"
  "/O2 /MT /Gd /Oy-"
  "/O2 /MT /Gd /Oa"
  "/O2 /MT /Gd /Oi"
  "/O2 /MT /Gd /Og"
  "/O1 /MT /Gd"
  "/Od /MT /Gd"
)

call_forms=(
  $'#define THUNK (*(HANDLE (WINAPI **)(LPSECURITY_ATTRIBUTES,SIZE_T,LPTHREAD_START_ROUTINE,LPVOID,DWORD,LPDWORD))0x10024050)\nresult = THUNK(NULL,0,srv_GameLoop,serverInitParams,THREAD_CREATE_RUN_IMMEDIATELY,(LPDWORD)&serverInitParams);'
  $'#define THUNK ((HANDLE (WINAPI *)(LPSECURITY_ATTRIBUTES,SIZE_T,LPTHREAD_START_ROUTINE,LPVOID,DWORD,LPDWORD))0x10024050)\nresult = THUNK(NULL,0,srv_GameLoop,serverInitParams,THREAD_CREATE_RUN_IMMEDIATELY,(LPDWORD)&serverInitParams);'
  $'typedef HANDLE (WINAPI *PCT)(LPSECURITY_ATTRIBUTES,SIZE_T,LPTHREAD_START_ROUTINE,LPVOID,DWORD,LPDWORD);\nPCT p=(PCT)*(DWORD*)0x10024050;\nresult = p(NULL,0,srv_GameLoop,serverInitParams,THREAD_CREATE_RUN_IMMEDIATELY,(LPDWORD)&serverInitParams);'
  $'typedef HANDLE (WINAPI *PCT)(LPSECURITY_ATTRIBUTES,SIZE_T,LPTHREAD_START_ROUTINE,LPVOID,DWORD,LPDWORD);\nresult = ((PCT)(*(DWORD*)0x10024050))(NULL,0,srv_GameLoop,serverInitParams,THREAD_CREATE_RUN_IMMEDIATELY,(LPDWORD)&serverInitParams);'
)

store_forms=(
  $'#define HGS (*(HANDLE*)0x11764094)\nHGS = result;'
  $'#define HGS (*(volatile HANDLE*)0x11764094)\nHGS = result;'
  '{ HANDLE *h=(HANDLE*)0x11764094; *h=result; }'
)

ret_forms=(
  'return result != NULL;'
  '{ BOOL ok=(result!=NULL); return ok; }'
  '{ BOOL ok=FALSE; if(result) ok=TRUE; return ok; }'
)

printf "diff\ttext_size\tflags\tvariant\n" > "$OUT"

vid=0
for cf in "${call_forms[@]}"; do
  for sf in "${store_forms[@]}"; do
    for rf in "${ret_forms[@]}"; do
      vname="v$(printf "%04d" "$vid")"
      ((vid+=1))
      cat > "$VAR_DIR/$vname.c" <<EOF
#include <windows.h>

#define srv_GameLoop ((LPTHREAD_START_ROUTINE)0x100093a0)
#define THREAD_CREATE_RUN_IMMEDIATELY 0

BOOL __cdecl Init(LPVOID serverInitParams)
{
    HANDLE result;
    $cf
    $sf
    $rf
}
EOF
    done
  done
done

for src in "$VAR_DIR"/*.c; do
  bname="$(basename "$src")"
  relsrc="${src#$ROOT/}"
  for fl in "${flags_list[@]}"; do
    set +e
    wine "$CL" /nologo /c $fl /I"$INC" /Fo"$OBJ" "$relsrc" >/dev/null 2>&1
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
    dd if="$BIN" of="$WORK/_winh48.bin" bs=1 count=48 2>/dev/null
    cmp -l "$WORK/_winh48.bin" "$ORIG" > "$WORK/_winhcmp.txt" 2>/dev/null || true
    if [[ -s "$WORK/_winhcmp.txt" ]]; then
      diffc=$(wc -l < "$WORK/_winhcmp.txt")
    else
      diffc=0
    fi
    printf "%s\t%s\t%s\t%s\n" "$diffc" "$tsize" "$fl" "$bname" >> "$OUT"
  done
done

{ head -1 "$OUT"; tail -n +2 "$OUT" | sort -t$'\t' -n -k1,1 -k2,2 | head -200; } > "$BEST"

echo "Wrote: $OUT"
echo "Top:   $BEST"
