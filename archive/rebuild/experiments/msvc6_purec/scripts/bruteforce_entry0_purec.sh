#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../../../../" && pwd)"
CL="$ROOT/tools/MSVC600/VC98/Bin/CL.EXE"
WORK="$ROOT/rebuild/experiments/msvc6_purec/entry0"
VAR_DIR="$WORK/variants"
OBJ="_bf.obj"
BIN="_bf.bin"
SRC="_bf.c"
OUT="bruteforce_entry0.tsv"
BEST="bruteforce_entry0_best.tsv"
ORIG="entry0_original_157.bin"

mkdir -p "$VAR_DIR"

if [[ ! -f "$WORK/$ORIG" ]]; then
  dd if="$ROOT/original/Server/server.dll" of="$WORK/$ORIG" bs=1 skip=$((0x1B9D4)) count=157 2>/dev/null
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
)

pad_sizes=(0 4 8 12 16 20 24 28 32)

if [[ -n "${PAD_SIZES:-}" ]]; then
  IFS=',' read -r -a pad_sizes <<< "$PAD_SIZES"
fi

max_variants="${MAX_VARIANTS:-0}"
stop_variants=0

custom_forms=(
  'custom=(dllmain_fn)G_CUSTOM_HANDLER; if(custom){ if(!custom(h,r,p)) return 0; }'
  'custom=(dllmain_fn)G_CUSTOM_HANDLER; if(custom) { if(!custom(h,r,p)) return 0; }'
)

call_init_forms=(
  'if(!sub_1001B8FB(h,r,p)) return 0;'
)

call_09310_forms=(
  'fdwReason=sub_10009310(h,r,p);'
)

reason_tail_forms=(
  'if(r==1){ if(fdwReason!=0) goto done; fdwReason=sub_1001B8FB(h,fdwReason,p); }'
)

detach_forms=(
  'if(r==0){ if(G_TERMINATION_FLAG==0) return 0; }'
  'if(r==0){ if(G_TERMINATION_FLAG==0) goto ret0; }'
)

thread_forms=(
  'if(r==0 || r==3){ if(!sub_1001B8FB(h,r,p)) fdwReason &= 0; }'
  'if(r==0 || r==3){ if(sub_1001B8FB(h,r,p)==0) fdwReason &= 0; }'
)

custom_tail_forms=(
  'if(fdwReason!=0){ custom=(dllmain_fn)G_CUSTOM_HANDLER; if(custom){ fdwReason=custom(h,r,p);} }'
  'if(fdwReason){ custom=(dllmain_fn)G_CUSTOM_HANDLER; if(custom){ fdwReason=custom(h,r,p);} }'
)

printf "diff\ttext_size\tflags\tvariant\n" > "$WORK/$OUT"

vid=0
for pad1 in "${pad_sizes[@]}"; do
  for pad2 in "${pad_sizes[@]}"; do
    for cf in "${custom_forms[@]}"; do
      for ci in "${call_init_forms[@]}"; do
        for c93 in "${call_09310_forms[@]}"; do
          for rt in "${reason_tail_forms[@]}"; do
            for df in "${detach_forms[@]}"; do
              for tf in "${thread_forms[@]}"; do
                for ct in "${custom_tail_forms[@]}"; do
                  vname="v$(printf "%04d" "$vid")"
                  ((vid+=1))
                  if [[ $max_variants -gt 0 && $vid -gt $max_variants ]]; then
                    stop_variants=1
                    break
                  fi
                  cat > "$VAR_DIR/$vname.c" <<EOF
#ifdef _MSC_VER
#include <windows.h>
#else
typedef int BOOL;
typedef void *LPVOID;
typedef void *HINSTANCE;
typedef unsigned long DWORD;
#ifndef __stdcall
#define __stdcall
#endif
#ifndef __declspec
#define __declspec(x)
#endif
#endif

typedef BOOL (__stdcall *dllmain_fn)(HINSTANCE, DWORD, LPVOID);

#define G_TERMINATION_FLAG (*(DWORD *)0x100354FC)
#define G_CUSTOM_HANDLER (*(DWORD *)0x11767588)

#define PAD1_SIZE $pad1
#define PAD2_SIZE $pad2

#ifdef _MSC_VER
#pragma optimize("y", off)
#pragma auto_inline(off)
#endif

static BOOL __stdcall sub_1001B8FB(HINSTANCE h, DWORD r, LPVOID p) {
  volatile unsigned char pad[PAD1_SIZE ? PAD1_SIZE : 1];
  return ((dllmain_fn)0x1001B8FB)(h,r,p);
}

static BOOL __stdcall sub_10009310(HINSTANCE h, DWORD r, LPVOID p) {
  volatile unsigned char pad[PAD2_SIZE ? PAD2_SIZE : 1];
  return ((dllmain_fn)0x10009310)(h,r,p);
}

#ifdef _MSC_VER
#pragma auto_inline(on)
#endif

// FUNCTION: SERVER 0x1001B9D4
BOOL __stdcall entry0(HINSTANCE hinst, DWORD fdwReason, LPVOID reserved) {
  register dllmain_fn custom;
  register DWORD reason = fdwReason;
  register HINSTANCE h=hinst;
  register DWORD r=reason;
  register LPVOID p=reserved;
  $df
  if(r!=0){
    if(r==1 || r==2){
      $cf
      $ci
    }
  }
  $c93
  $rt
  $tf
  $ct
 done:
  return fdwReason;
 ret0:
  return 0;
}

#ifdef _MSC_VER
#pragma optimize("", on)
#endif
EOF
                done
                if [[ $stop_variants -eq 1 ]]; then break; fi
              done
              if [[ $stop_variants -eq 1 ]]; then break; fi
            done
            if [[ $stop_variants -eq 1 ]]; then break; fi
          done
          if [[ $stop_variants -eq 1 ]]; then break; fi
        done
        if [[ $stop_variants -eq 1 ]]; then break; fi
      done
      if [[ $stop_variants -eq 1 ]]; then break; fi
    done
    if [[ $stop_variants -eq 1 ]]; then break; fi
  done
  if [[ $stop_variants -eq 1 ]]; then break; fi
 done

cd "$ROOT"

for src in "$VAR_DIR"/*.c; do
  bname="$(basename "$src")"
  relsrc="${src#$ROOT/}"
  for fl in "${flags_list[@]}"; do
    set +e
    wine "$CL" /nologo /c $fl /I"$ROOT/tools/MSVC600/VC98/Include" /Fo"$WORK/$OBJ" "$relsrc" >/dev/null 2>&1
    rc=$?
    set -e
    if [[ $rc -ne 0 ]]; then
      printf "9999\t0\t%s\t%s\n" "$fl" "$bname" >> "$WORK/$OUT"
      continue
    fi
    if ! objcopy -O binary --only-section=.text "$WORK/$OBJ" "$WORK/$BIN" >/dev/null 2>&1; then
      printf "9998\t0\t%s\t%s\n" "$fl" "$bname" >> "$WORK/$OUT"
      continue
    fi
    tsize=$(stat -c%s "$WORK/$BIN" 2>/dev/null || echo 0)
    if [[ "$tsize" -lt 157 ]]; then
      diffc=$((157 - tsize + 1000))
      printf "%s\t%s\t%s\t%s\n" "$diffc" "$tsize" "$fl" "$bname" >> "$WORK/$OUT"
      continue
    fi
    dd if="$WORK/$BIN" of="$WORK/_bf157.bin" bs=1 count=157 2>/dev/null
    cmp -l "$WORK/_bf157.bin" "$WORK/$ORIG" > "$WORK/_bfcmp.txt" 2>/dev/null || true
    if [[ -s "$WORK/_bfcmp.txt" ]]; then
      diffc=$(wc -l < "$WORK/_bfcmp.txt")
    else
      diffc=0
    fi
    printf "%s\t%s\t%s\t%s\n" "$diffc" "$tsize" "$fl" "$bname" >> "$WORK/$OUT"
  done
done

{ head -1 "$WORK/$OUT"; tail -n +2 "$WORK/$OUT" | sort -t$'\t' -n -k1,1 -k2,2 | head -200; } > "$WORK/$BEST"

echo "Wrote: $WORK/$OUT"
echo "Top:   $WORK/$BEST"
