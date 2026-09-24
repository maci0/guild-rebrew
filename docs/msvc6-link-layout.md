# MSVC 6.0 LINK / PE layout: what decides the bytes outside `.text`

`rebrew test` and `docs/msvc6-c-shapes.md` own `.text`. Everything else
(section geometry, the import layer, `.data`/`.rdata` content, and what
`rebrew postlink` is allowed to overwrite) is decided by the linker and by
the layout package, and it is what this file records.

Every number here is measured, not inferred. The two binaries are
`original/Server/server.dll` (the reference) and the CMake build's
pre-postlink output (`.scratch/server.dll.prelayout`); reproduce any row with
the recipes in section 7.

## 1. Section geometry: three rules, and the arithmetic that follows

Both binaries: `SectionAlignment = FileAlignment = 0x1000`,
`SizeOfHeaders = 0x1000`.

| reference | RVA        | VirtualSize | raw     | file offset |
|-----------|------------|-------------|---------|-------------|
| `.text`   | `0x001000` | `0x022846`  | `0x23000` | `0x001000` |
| `.rdata`  | `0x024000` | `0x002e81`  | `0x03000` | `0x024000` |
| `.data`   | `0x027000` | `0x174059c` | `0x0e000` | `0x027000` |
| `.reloc`  | `0x1768000`| `0x010374`  | `0x11000` | `0x035000` |

file size `0x46000` (286720).

The rules the linker follows, each verified against both binaries:

1. **`raw = align_up(content_end, FileAlignment)`.** Not `VirtualSize`. The
   reference's `.data` `VirtualSize` is `0x174059c` (the whole section,
   `.bss` included) while its raw is `0xe000`; its last non-zero initialized
   byte is at section offset `0xd60b`, so the raw is the page-round of a
   content end that lies in `(0xd000, 0xe000]`.
2. **`RVA(n+1) = align_up(RVA(n) + VirtualSize(n), SectionAlignment)`.**
   `.rdata` ends at `0x24000 + 0x2e81 = 0x26e81`, so `.data` starts at
   `0x27000`: a whole `0x1000` early of where a raw-sized accounting would
   put it.
3. **`file_offset(n+1) = file_offset(n) + raw(n)`.** This is the rule that
   makes a surplus section fatal rather than cosmetic: one extra `0x1000` of
   `.rdata` raw moves `.data`, `.reloc` and the end of the file by `0x1000`.
   Byte-identical output therefore reduces to four exact raw sizes, and to
   the content that decides them.

The map file is the cheap way to read a section's *content* end: the linker
starts `.bss` where the initialized bytes stop.

```
0002:000001a0 00002630H .rdata     DATA      <- IAT is [0, 0x1a0)
0003:00000030 0000f4d0H .data      DATA      <- .CRT$XCA..XTZ are [0, 0x30)
0003:0000f500 01735598H .bss       DATA      <- .data content ends at 0xf500
```

So a section's content end is `bss_offset`, and the map's per-symbol offsets
are section-relative (add the section RVA for a VA).

## 2. `.data`: the gap blob, and the one number that matters

`crt_region/data_restore.c` is a single `unsigned char g_data_restore_gap[]`
whose bytes are a copy of the reference's `.data` raw. It is linked **first**
(after `crt_imports.c`), so in the linked image the section is laid out as

```
[0x00, 0x30)        .CRT$XCA .. .CRT$XTZ (10 sections, 0x30 bytes)
[0x30, 0x30+B)      g_data_restore_gap          (size B)
[0x30+B, ...)       every other TU's .data, .bss
```

**Only `B` matters.** `rebrew postlink`'s data fixer overwrites the built
`.data` wholesale with the layout package's `data.hex` (the reference's raw
bytes) and rewrites the header's raw size to `len(meta.data)`: the blob's
*content* never reaches the output. Its whole job is to make the section's
content end land in the band that rounds to the reference's raw size:

```
own      = content_end(without blob) - 0x30      # measured: 0x44d0
B        = 0xe000 - 0x30 - own                    # 0xe000 exactly
band     = (0xd000, 0xe000]                       # any value in it -> raw 0xe000
```

Measured:

```
data_restore.c header          content end (.bss)   .data raw
[0x3000:0xe000]  B = 0xb000    0xf500               0x10000   <- 0x2000 too big
[0x4600:0xe000]  B = 0x9a00    0xdf00               0x0e000   <- matches the reference
```

`B = 0x9a00` leaves `0x100` of headroom below `0xe000`, which is why it is
the chosen value rather than the exact `0x9b00`. The blob is regenerated with

```sh
PYTHONPATH=$PWD/.scratch/rebrew-stable/src rebrew gen-layout --data-gap 0x4600
```

where the argument is the **raw_start** (the reference `.data` offset the blob
starts at), so `B = reference_raw - raw_start`. Note that `--data-gap`'s help
text calls it `<raw-size>`; the code does `data[data_ro+raw_start : data_ro+data_raw]`.

Measured content inventory of `.data` in the CMake build (map section 3):
`0x30` CRT + `0x9a00` blob + `0x44d0` of TU data (game string literals
`??_C@...`, `link_stubs.c.obj`'s `g_<va>` scaffold globals, LIBCMT `.data`)
ends exactly at the reference's raw size. The map's `.bss` line is the
boundary: every symbol above `0xdf00` there is uninitialized, so the
surplus was blob + emitted literals, never an initialized global the layout
could not place.

### The prefix cannot be dodged by reordering: sections merge by name

The sub-sections of image section 2 are merged in **section-name order**, not
object order: the map always reads

```
0002:00000000 .idata$5   (IAT)
0002:000001a0 .rdata     (every `.rdata`-named contribution, in object order)
0002:000027d0 .idata$2   (import descriptors)
0002:00002820 .idata$3
0002:00002834 .idata$4
0002:000029d4 .idata$6   (hint/name records + DLL names)
0002:00002ff0 .edata
```

so no link-line change can put the import descriptors *before* the `.rdata`
contributions: the gate's `0x2468` bytes are exactly that `.rdata` group, and
satisfying it means making the group total `0x2468` **and** hold the
reference's bytes.  The same rule fixes the `.idata$N` order, which is why
postlink copies `bookkeeping.hex` (`0x828` bytes) over whatever sits at the
built import directory instead of trying to move it.

### Why `.data` is where the literals are

Under `/O2 /Gd /MT` (and unchanged by `/Gf`, `/Gy`, `/GA`, measured), msvc6
emits a **referenced string literal into `.data`**, as a `??_C@...` COMDAT,
not into `.rdata`.  A literal that nothing references is **not emitted at
all**: there is no unreferenced-literal section to restore.  Both facts show
up in the map: the game's `??_C@...` symbols all have section `0003`, and the
`runtime error` strings that a round-113 plan wanted to "re-emit from a TU"
were already inside `rdata_restore.c`'s blob precisely because no TU of ours
references them.

The consequence for planning: a missing `.rdata` string cannot be fixed by
writing the literal in a new C file: it will land in `.data` and shift every
literal after it.  Literal content belongs in the blob that covers the
reference's own bytes.

## 3. `.rdata` (map section 2): the prefix contract

Section 2 is the merged IAT + `.rdata` + import bookkeeping + export table:

```
[0x000, 0x1a0)   .idata$5   IAT (100 imports * 4, padded)
[0x1a0, 0x1a0+P) .rdata     P bytes
[        , +0x50).idata$2   import descriptors (4 DLLs + null)
[        , +0x14).idata$3
[        , +0x1a0).idata$4  OFT / name-pointer arrays
[        ,       ).idata$6  hint/name records + DLL names
[        , +0x51) .edata    export directory (Init, Exit)
```

`rebrew postlink` refuses to run unless the built bytes between the IAT and
the import directory are **exactly** the reference's:

```python
prefix_lo = rva_to_offset(iat_rva + iat_size)   # 0x24000 + 0x1a0
prefix_hi = rva_to_offset(import_rva)
if prefix_hi - prefix_lo != len(meta.prefix): raise ValueError(...)
if built[prefix_lo:prefix_hi] != meta.prefix:  raise ValueError(...)
```

`layout/server.dll/prefix.hex` is `0x2468` bytes: the reference's
`.rdata[0x1a0:0x2608)`, i.e. the whole `.rdata` proper up to the import
directory. Measured in the current build:

```
built prefix size  0x2630   (0x1a0 .. 0x27d0)
reference          0x2468   (0x1a0 .. 0x2608)
surplus            0x1c8
```

The surplus is one contiguous block **after** the `rdata_restore.c` blob
(`g_rdata_restore_252e8`, `0x1320` bytes at `0x12e8`, ending at `0x2608`
exactly like the reference). It is LIBCMT `.rdata` re-emitted by objects the
link pulls for their *code*, whose `.rdata` the blob already carries inside
its range:

```
0x2608  LIBCMT:testfdiv.obj   __real@8 reals + "IsProcessorFeaturePresent" + "KERNEL32"
0x2690  LIBCMT:x10fout.obj    "1#QNAN" "1#INF" "1#IND" "1#SNAN"
0x26b0  LIBCMT:output.obj     ___lookuptable, "(null)", wide "(null)"
0x2740  LIBCMT:timeset.obj    ___dnames, ___mnames
0x2780  LIBCMT:tzset.obj      "TZ"
0x2784  LIBCMT:a_map.obj      "SunMonTue..." , "JanFeb..."
0x27d0  __IMPORT_DESCRIPTOR_KERNEL32   <- import dir, 0x1c8 late
```

Two consequences worth keeping straight:

* The block is a **duplicate**, not extra data: the reference has the same
  bytes inside `[0x12e8, 0x2608)`: `"1#QNAN"` at `0x24a8`, `"(null)"` at
  `0x2074`, `"TZ"` at `0x2458`, `"Monday"` at `0x25c0` all match at the same
  offsets on both sides.
* Because the offset error is one contiguous block, every later sub-section
  keeps its internal size but moves `0x1c8` later, so `.edata` and the tail of
  the hint/name table land past where the reference has them.
  `crt0msg.obj`/`crtmbox.obj` were the first two members of this set and were
  removed in round 115 by supplying `_NMSG_WRITE`/`_crtMessageBoxA` locally
  (`0x33b1 -> 0x3041`); the six above are what is left.

Shrinking the blob by `0x1c8` instead of removing the objects does **not**
work: the block that would move up into `[0x2440, 0x2608)` is our own COMDAT
order (testfdiv reals first), which matches only 53 of 456 bytes of the
reference's window, and the prefix check compares bytes, not just length.

### Discarding the duplicates instead: COMDAT folding by symbol name

There is a third option, and it is the one that works: **the linker folds
COMDAT sections by symbol name, keeping the first definition it sees.**  msvc6
derives a string literal's `??_C@<length><hash>@<mangled-content>?$AA@` name
from the literal's contents, so an object that references *the same literals*
defines *the same COMDAT names*, and whatever the library emits for them is
discarded.

`crt_region/rdata_fold.c` does exactly that for the six objects' strings and
carries no `.text` at all: the literals go to `.data` (referenced literals do
not go to `.rdata`; see the section above), which costs nothing because
postlink overwrites `.data` wholesale.  Measured on the CMake build:

```
                     .rdata VS   .rdata raw   libc string COMDATs in the map
before                   0x3041       0x4000  8
with rdata_fold.c        0x2ff1       0x3000  0 (all folded)
```

`0x3000` is the reference's raw size, and it moves `.data` to file offset
`0x27000` and `.reloc` to `0x35000`: the reference's.  Two notes for extending
it to the rest of the block:

* A COMDAT folds against a definition of the same **name**, whatever the
  container.  `__lookuptable`/`__dnames`/`__mnames` fold against a one-byte
  `const` array each (COFF `___lookuptable` is C `__lookuptable`); the bytes do
  not have to be ours, because the reference's are already inside the blob and
  postlink rewrites the `.text` operands that point at them.
* A `.bss` (uninitialized) definition defines the symbol but does **not** fold
  the library's read-only COMDAT: measured, the library's copy stays in the
  map.  The definition has to be an initialized constant to be a COMDAT.
* **Not everything in the library is COMDAT.**  The string literals are
  (`??_C@…`, 11 of them folded here, worth `0x70` of `.rdata` VirtualSize), but
  `___lookuptable`, `___dnames` and `___mnames` are plain `.rdata` sections in
  LIBCMT: a definition of ours (even `__declspec(selectany)`, which does make
  it COMDAT) leaves *both* sections in the image, so the surplus grows by
  whatever we define.  Those `0x9c` bytes can only be removed by not linking
  the objects that carry them.  `__real@8@…` FP constants are COMDAT, but the
  compiler emits them only from an expression, and adding a `.text` function to
  get one defeats the purpose.

## 4. The import layer

* 100 imports across 4 DLLs (`KERNEL32`, `USER32`, `WS2_32`, `WINMM`), and
  the **set** must be identical: `_fix_imports` raises
  `import sets differ — refusing to copy bookkeeping` otherwise.
* The IAT slot order is hash-driven and not forceable with `/include`, so
  postlink copies `iat.hex` (`0x1a0` bytes) and `bookkeeping.hex` (`0x828`
  bytes: descriptors, OFT arrays, hint/name records, DLL names) over the
  built ones, and remaps `FF 15/25` operands in `.text` to the reference's
  slots.
* The hint/name table's **size depends on that order**, because records are
  padded to alignment: the same 28 names cost `0x61a` in our build and
  `0x624` in the reference. That is why postlink copies the whole
  bookkeeping block rather than trying to reorder ours, and why the built
  `.edata` can sit a few bytes earlier than the reference's.
* A missing or extra import is the cheapest possible signal that the link
  changed: compare the count (100) after any link change.

## 5. Linker flags measured

| flag | effect |
|------|--------|
| `/OPT:NOREF` (current) | keeps every COMDAT of every linked object. Needed: our reversed `.text` is not all referenced, and `/OPT:REF` gutted it (`0x22256 -> 0x100c6`). |
| `/OPT:REF` | drops unreferenced COMDATs: `.rdata 0x3041 -> 0x2f81` (raw `0x4000 -> 0x3000`!), `.data 0x1743498 -> 0x1742614`, and `.text` down to `0x100c6`. Not usable as-is, but it proves the surplus is unreferenced COMDATs. |
| `/FORCE:MULTIPLE` | silences `LNK4006`; the warning is a finding (see AGENTS.md), not noise. |
| `/INCLUDE:<sym>` | forces a LIBCMT object in for its *code* (`__ms_p5_mp_test_fdiv` is one of the eight here), and the object's `.data`/`.rdata` COMDATs come with it. |
| `/debug` | adds a `0x1c`-byte debug directory that shifts `.rdata`; `REBREW_DEBUG_INFO` must stay OFF. |

## 6. What postlink is allowed to overwrite (and what it is not)

| region | postlink behaviour |
|--------|--------------------|
| `.text` | trims to the reference's raw size, sets raw/VirtualSize, rewrites absolute data operands and E8/E9 targets from the sparse maps. Content is largely ours. |
| `.rdata` | **only** the IAT and import bookkeeping are copied. The rest must already match byte-for-byte: hence the prefix gate. |
| `.data` | overwritten wholesale with `data.hex` (`0xe000`), raw size set to the reference's. |
| `.reloc` | replaced with the reference's (grows to raw `0x11000`) at the **built** file's `.reloc` offset. |
| PE metadata | DOS stub, `e_lfanew`, TimeDateStamp, CheckSum, `.data` VirtualSize, `.reloc` VA, SizeOfImage. |

The practical reading: `.data`, `.reloc` and the import layer are already
solved *at the content level*; `.rdata`'s body and `.text`'s bytes are not.
Which is why the remaining raw-size work is worth doing: with `.rdata` raw at
`0x3000` and `.data` raw at `0xe000`, the built `.reloc` lands at file offset
`0x35000`, exactly the reference's, and the post-postlink file is `0x46000`
bytes, exactly the reference's size:

```
reference      0x1000 + 0x23000 + 0x3000 + 0xe000 + 0x11000 = 0x46000
built (now)    0x1000 + 0x23000 + 0x4000 + 0xe000 + 0x08000 = 0x3e000
built (target) 0x1000 + 0x23000 + 0x3000 + 0xe000 + 0x11000 = 0x46000
```

## 7. Measuring it (recipes)

A failed postlink **deletes** `server.dll`, but the POST_BUILD step copies the
honest link output to `.scratch/server.dll.prelayout` one command earlier.
`scripts/section_geometry.py` reads that file and prints the whole table
above, exiting non-zero when a raw size still differs from the reference:

```sh
python3 scripts/section_geometry.py                 # .scratch/server.dll.prelayout
python3 scripts/section_geometry.py build/x.dll     # or an explicit file
```

```sh
cmake --build build -j8
python3 - <<'PY'
import struct
d = open('.scratch/server.dll.prelayout','rb').read()
pe = struct.unpack_from('<I', d, 0x3c)[0]
n  = struct.unpack_from('<H', d, pe + 6)[0]
opt = pe + 24
for i in range(n):
    o = opt + struct.unpack_from('<H', d, pe + 20)[0] + i*40
    print(d[o:o+8].rstrip(b'\0').decode(),
          *[hex(x) for x in struct.unpack_from('<IIII', d, o+8)])   # vs, va, raw, ptr
PY
```

For a map (per-symbol objects, and the `.bss` content-end line), relink the
same objects with `/MAP`; the response file is already written for you:

```sh
cd build
sed -e 's#/out:server\.dll#/out:server_probe.dll#' \
    -e 's#/implib:server\.lib#/implib:server_probe.lib#' \
    -e 's#/pdb:[^ ]*#/pdb:server_probe.pdb#' \
    -e 's#/nologo#/nologo /MAP:server_probe.map#' \
    CMakeFiles/server_dll.dir/link.txt > /tmp/link_probe.txt
bash /tmp/link_probe.txt
```

The map's `Publics by Value` columns are
`section:offset name Rva+Base flags object`; library symbols have an empty
flags column, so parse the object as the last whitespace-separated field, not
by fixed column.

## 8. Traps

* **`rebrew gen-layout` is not output-stable.** Two of the files it rewrites
  (`crt_region/crt_imports.c`'s `/include:` order and the `layout` block in
  `rebrew-project.toml`) come out in set-iteration order, which changes
  between processes. Regenerating `data_restore.c` with `--data-gap` also
  churns those two; check `git status` and revert them unless the change is
  intended.
* **A `// DATA:` marker that is not in `src/rebrew-data.toml` is a lint
  warning (W016).** The gap blob's VA is a function of its size, so re-tuning
  it means moving the registry entry too (key, `section`, `name`, `type`).
* **`data_restore.c`/`rdata_restore.c` contents are scaffold.** Editing the
  bytes by hand cannot help (postlink overwrites `.data`; `.rdata`'s copy
  must line up with meta.prefix); the only knob is the blob's *length*.
* **Rebuild objects after touching `data_restore.c`.** Restores from
  `.scratch/padbak` have silently reverted this object before; always rerun
  `cmake --build` and re-read the map.
* **`.text` VirtualSize is the cheap link-health check**: the reference is
  `0x22846`. A built value below it means the link is not emitting code the
  reference contains, and no downstream section measurement is meaningful
  until that is understood.
