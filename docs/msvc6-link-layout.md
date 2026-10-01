# MSVC 6.0 LINK / PE layout: what decides the bytes outside `.text`

`rebrew test` and `docs/msvc6-c-shapes.md` cover function code generation.
This companion records native storage, alignment, imports, and PE layout.
New findings name their compiler/linker profile and saved evidence; distinguish
the observed bytes from explanations still under investigation.

**Current objective:** ordinary toolchain output must match the entire reference
file. The canonical artifact is `build/server.dll`, built with plain MSVC 6.0
SP5 and unchanged stock libraries, without postlink rewriting or manual padding.
Sections 1–8 describe the earlier postlink pipeline and its historical numbers;
their padding recipes and permissions do not apply to the current objective.
Sections 9 onward record native-build findings. The reference remains
`original/Server/server.dll`. Section 18 records that this configured copy
has altered headers relative to matching local distribution copies; their
four section contents are identical. Do not infer compiler provenance from
the configured copy's missing Rich header.

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

### The split link's tail blob, and what the raw-link `.data` figure measures

`scripts/split_link.sh` drops `data_restore.c` and appends
`data_restore_split.obj` last: a blob holding the reference's `.data` from
offset `S` (where the link places it) up to where the `.data$zz` group starts.
`.data$zz` holds `crt_region/rdata_fold.c`'s two literals; the linker sorts it
after every plain `.data` contribution, so the blob is sized
`GAP = 0xe000 - S - align4(.data$zz)` and both end at `0xe000`. The blob's
bytes sit on the reference's own and add nothing to the gate's raw-link
`.data` count. `S` moves whenever a game TU's `.data` changes size, so the
script reads `S` and the `.data$zz` size from `build/split_poc.map` after
linking and, if `GAP` was stale, re-emits the blob and relinks. A hand-set
`GAP` that went stale by `0x58` cost 6,187 bytes and pushed `.data` raw to
`0xf000`. When the reference bytes the blob would copy are all zero, msvc6
puts the array in `.bss`: the section then ends at `S` and the raw size still
rounds to `0xe000`.

Raw-link `.data` differing is **0** of `0xe000` (gate `DATA_BASELINE`).
`scripts/emit_crt_data.py` links the library sections below, in this order,
after every other `.data` contribution and before the gap blob.
`g_data_restore_gap` therefore starts at `0xd30c`, past the old tail
`0xd274`. A blob that starts earlier is copying reference `.data` the link
did not emit; `postlink_residual.py` flags that, and `gate.sh` fails on it.

`___lc_time_curr` (4 bytes at `0xd258`) points at `___lc_time_c` (the
`0xac` C-locale time table at `0xd260`, ALIGN_8, so the 4 bytes at `0xd25c`
are the linker's pad). The table's day and month slots relocate to the
string COMDATs already resident in the `.rdata` blob; those names are
absolute symbols, because leaving them undefined pulls `strftime.obj` and
its `.text`. `intrncvt` is raised from ALIGN_8 to ALIGN_16 so it lands at
`0xd130` instead of `0xd128`. `charmax` is not a separate contribution: its
4 bytes are the tail of `crt0msg`. `lconv` (`0xd310`) and `constpow`
(`0xd350`) stay inside the tail blob. `link_stubs.c` still keeps the BSS
definitions (`__pctype` is not among them; `ctype.obj` emits it) that stop
the archive from contributing a second copy.

Matching each LIBCMT archive member's `.data` (relocation slots masked)
against the reference gives the order: `exsup` `0xcba0`, `cmiscdat` `0xcbb0`,
`setlocal` `0xcbc8`, `ctype` `0xccd4`, `nlsdata1` `0xcee0`, `crt0msg`
`0xcef0`, `charmax` `0xcf78`, `timeset` `0xcf80`, `tzset` `0xd018`, `days`
`0xd034`, `winxfltr` `0xd0a0`, `intrncvt` `0xd130`, `mbctype` `0xd160`,
`___lc_time_curr` `0xd258`, `___lc_time_c` `0xd260`, `lconv` `0xd310`,
`constpow` `0xd350`. `link_stubs.c`'s `.rdata` constants
(`g_float_const_*`, `g_dbl_const_*`) keep their values so the raw link
computes correctly; the reference holds those bytes in `.rdata`.

How msvc6 lays out a TU's `.data`, as used to close the game gaps:

* Named initialised globals first, in definition order, then the string
  literal COMDATs. A function's literals are emitted in **reverse** order of
  first use in its code, functions in source order, so turning named string
  arrays and raw `(char*) 0x1002....` addresses back into literals reproduces
  the reference order, and a literal several split files share (a `__FILE__`
  path) folds to the first object's copy.
* A **struct** object gives the whole section 8-byte alignment and is itself
  8-aligned; arrays of scalars (including 2-D) only 4. Four zero bytes in the
  reference between two TUs' data (`0x10029aec`, `0x1002d874`, `0x1002dd44`)
  mean the second TU's section starts with, or holds, a struct object.
* A named array is not neutral: `gm_AllocSpieler`'s SpID format as a literal
  swaps two stack loads (3681/3689), and `gm_Open` with the spiel.c path as a
  literal instead of a raw address falls to 859/861. Both keep their old form;
  `rebrew test` each file after the conversion.
* So is a header line: dropping one unused `extern` from `rebrew_globals.h`
  took `gm_Open` (which includes it) to 859/861 again. Keep declarations a
  file sees unless `rebrew verify --full` holds.
* A split TU's named globals would land after the literals of the files linked
  before it: `spiel.c`'s named block therefore lives in the data-only
  `game/spiel_data.c`, ordered by `--first-va` (CMakeLists.txt).

**A local array initialised from a string literal emits that literal as a
`.data` COMDAT** (`char szSep[] = "---\r\n";`). If a data blob already carries
the same bytes, the link holds them twice and every later symbol shifts.
`CrashDumpUnhandledExceptionFilter.c` hit this (every symbol from `0x1002733c` on moved `+0x20`,
raw-link `.data` 22,684 to 27,620): its blob now ends at `0x100272f8`, the two
literals follow as that file's COMDATs, and `EmitCrashModuleLine.c` (the next
object) defines the rest from `0x10027318`.

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

**Current state:** `scripts/split_blob.py` now places the members' string
COMDATs at their reference offsets inside the blob instead (longest first, so
a short string takes a match the longer sections leave free), and
`rdata_fold.c` folds only the all-zero pair (`"\0"`, `L"\0"`) that matches
every zero run; its literals sit in `.data$zz` (section 2). The rest of this
subsection records how folding was established.

`crt_region/rdata_fold.c` did exactly that for the six objects' strings and
carried no `.text` at all: the literals go to `.data` (referenced literals do
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

## 9. Explicit zero initialization and tentative definitions choose different native storage

Plain MSVC 6.0 SP5 emits these distinct COFF forms:

| C89 definition | COFF storage |
|---|---|
| `int plain;` | External COMMON, size four, no defining section |
| `extern int declared; int declared;` | Same external COMMON form |
| `int array[4];` | External COMMON, size sixteen |
| `int initialized = 0;` | External symbol defined in ordinary `.bss` |
| `int initialized_array[4] = {0};` | External symbol defined in ordinary `.bss` |
| `static int private_value;` | Static symbol defined in ordinary `.bss` |
| `volatile int volatile_value;` | External COMMON; volatile alone does not choose `.bss` |

Therefore zero-valued definitions that look interchangeable in C can change
native allocation order and alignment. Reversing tentative declarations or
changing which of two arrays is referenced did not reorder the tested COMMON
arrays. A diagnostic with explicit zero initialization gave ordinary section
allocation controlled by the owning object instead. The native linker also
accepts COMMON data symbols in `/ORDER`; the large game COMMON arrays acquire
the measured 32-byte boundaries naturally. `__declspec(align(32))` fails with
C1600 in this compiler and is not a substitute.

The tracked `layout/server.dll/common-data-order.txt` reproduces the proven
game ordering. It does not solve the remaining 3296-byte `.data` extent gap.
Explicit-zero controls for smaller globals moved CRT storage but worsened the
raw comparison; they were not promoted. Recover the actual owner before
changing storage or inserting a definition merely to fill a gap.

Evidence: `.scratch/native-bss-shapes.c` and `.json`, `.scratch/common-order/`,
and the native COMMON ordering controls recorded in `docs/HANDOFF.md`.

## 10. Removing one float literal can change owner positions without shrinking VirtualSize

The successful alchemist product rewrite (`msvc6-c-shapes.md` §203) removes
one compiler-generated four-byte 0.33 float. Before it, the two readonly string
owners were 20 bytes late and the recovered arrays/record arrays were 24 bytes
late. After it, all six owners are **16 bytes late**, and their values still
match at their actual native addresses. Native alignment changed along with
the removed literal. Total `.rdata` VirtualSize stayed `0x2ea1`, 32 bytes
larger than the reference's `0x2e81`.

At that checkpoint, four compiler-generated floats remain before those owners: alchemist's 30,
and graveyard's 1000, 8, and 4. Named readonly owners already hold those values,
but replacing the literal reads changes instructions (§204). A value match,
an object RELOC match, an owner-address match, and a section-extent match are
separate checks. Do not predict file progress by subtracting literal sizes.
Section 23 subsequently removes their duplicate named definitions by
changing the other readers to literals; the compiler pools are retained.

The copied readonly restore blob is gone. `rdata_restore.c` now owns only the
actual 44-byte unzip copyright and 41-byte packed extension strings; typed
game tables and the unchanged CRT provide their own contributions. Copied
alignment bytes were removed rather than replaced with manual padding.
Evidence: `.scratch/native-float-scheduling/canonical-product-audit.json` and
`.scratch/native-symbol-operands/canonical-audit.json`.

## 11. Import member format does not by itself determine IAT slots or final thunk alignment

Four native controls used unchanged VC5 stock import libraries with the
canonical 190 objects and SP5 LINK. VC5's import members are full COFF; the
canonical VC6 archives use short import records. No archive was patched.

| Libraries changed to VC5 | Import identities | Different IAT slots | Different named hints | Moved mapped functions | Raw differing bytes |
|---|---:|---:|---:|---:|---:|
| KERNEL32 | 100 | 23 | 80 | 95 | 47221 |
| WS2_32 | 100 | 23 | 0 | 0 | 31511 |
| KERNEL32 and WS2_32 | 100 | 23 | 80 | 95 | 47225 |
| All four DLL libraries | 100 | 23 | 83 | 0 | 31484 |

Every control retains the four DLLs in reference order. None fixes the IAT
slots. Changing all four has a slightly lower raw byte count than the
canonical 31493 but breaks 83 named hints, so it is not a correct improvement.
Full COFF import members alone also do not restore the final unwind thunk's
reference alignment. These controls were rejected and the canonical stock
SP5 libraries retained. Check identities, hints, slots, and code positions
after each link-input change; no one count represents the entire import table.

Evidence: `.scratch/native-legacy-imports/{stock-format,stock-members,audit}.json`
and the successful per-control link logs. The stock-members manifest records
archive/member hashes checked after linking. Native `/ORDER` on IAT symbols
was separately rejected with LNK4065; `/INCLUDE` retains an input without
guaranteeing its reference slot (`.scratch/native-import-slots/`).

## 12. Live base relocations and the linker's relocation-section reservation are separate

The reference has 3499 live base relocations. Its relocation directory and
section extent include a large zero tail beyond the actual relocation blocks.
Native VC6 controls show that a discarded selectany table of 1000 pointers
can increase the reserved extent by about 2020 bytes without adding live
relocations. This establishes that discarded inputs can affect reservation;
it does not identify the original discarded inputs or justify manufacturing
a dead pointer table to enlarge the file.

At the current checkpoint, native live-count parity is restored (3499), but
164 sites are missing and 164 extra: 145 in data, 18 in readonly data, and the
final unwind code operand. Native `.reloc` VirtualSize is `0xc870` against
reference `0x10374`, a 15108-byte difference. Correcting eight live operands
also changed the section reservation, so a live-fixup count is not an extent
formula. Recover genuine input composition and placement; padding and copied
relocation bytes do not meet the native-output objective.

Evidence: the selectany control in `docs/HANDOFF.md`'s command-table relocation
checkpoint and `.scratch/native-symbol-operands/canonical-audit.json`.
The latter checkpoint still has 31493 overlapping differing bytes and a
16384-byte length gap. All 262 function checks pass; whole-file identity is
false.

## 13. Selectany readonly scalars change storage and retention without folding these literals

Plain SP5 `/O2 /Gd` accepts `__declspec(selectany) const float name = value;`
for the existing 30/1000/8/4 owners. The four ordinary `.rdata` definitions
become separate four-byte `.rdata` COMDATs: their section characteristics
change from `0x40400040` to `0x40301040`, including the alignment change from
eight to four. This changes placement even when the initializer bytes agree.

Six native controls keep the canonical 190 objects and stock libraries,
substituting only the diagnostic readonly object where stated:

| Control | `.text` VS | `.rdata` VS | Raw differing bytes | Readonly check |
|---|---|---|---:|---|
| Ordinary definitions, explicit `/OPT:ICF` | `0x22844` | `0x2ea1` | 31493 | 52 pass |
| Four selectany definitions, default optimization | `0x22844` | `0x2e91` | 30421 | Two owners missing |
| Four selectany definitions, explicit `/OPT:ICF` | `0x22844` | `0x2e91` | 30421 | Two owners missing |
| Four selectany definitions, `/OPT:NOICF` | `0x2289e` | `0x2e91` | 46212 | Two owners missing |
| Four selectany definitions, force the two unused owners with `/INCLUDE` | `0x22844` | `0x2ea1` | 30451 | 52 pass |
| Same retained definitions, explicit `/OPT:ICF` | `0x22844` | `0x2ea1` | 30451 | 52 pass |

Under `/OPT:REF`, unreferenced `g_graveyard_const_a` and `_b` disappear.
This is removal, not folding with the literal reads. With both retained,
the named owners sit at `0x10025fc0..0x10025fcc`, while the four compiler
literal symbols remain at `0x100252e8..0x100252f4`. Explicit ICF does not
coalesce these pairs. All named values pass at their actual locations, but
their placements differ substantially from the reference. The section
retains its 32-byte excess. The interval array happens to reach its reference
address; that isolated win does not establish the intended ownership/layout.

ICF is already effective in the canonical link: adding `/OPT:ICF` changes none
of the measured extents or positions, while disabling it adds 90 bytes of
code and moves 95 mapped functions. The other five controls keep all 597
mapped function positions. No control was promoted: the hypothesis was
literal folding, and all four compiler literals remain separate.

Evidence: `.scratch/native-readonly-comdat/four-selectany.c`, its native COFF
object and compile log, `objects.rsp`, the six DLL/map/link-log pairs, and
`audit.json`. The canonical production definitions and linker flags are
unchanged. These results apply to the tested four scalar pairs, not every
possible COMDAT selection or folding mechanism.

## 14. COMMON retention directives do not substitute for native allocation ordering

Ten controls keep the canonical objects and archives, remove `/ORDER`, and
vary `/INCLUDE` directives for the already-linked COMMON symbols. The order
file is derived from reference addresses where known; unknown CRT symbols
retain their measured native order. The input list and exact argv are saved.

Without `/ORDER`, `g_slot_table` moves to `0x1166d3a0`, `g_connections` to
`0x100e7100`, and `g_current_year` to `0x11763334`; CRT `___lc_handle` moves
ahead of the large arrays to `0x10034a6c`. The game arrays have the wrong
relative order. Forcing game COMMON names first in either forward or reverse
order does not change those allocations. Appending all COMMON names in
either order also leaves the allocations unchanged. Thus these retention
spellings do not reproduce `/ORDER`'s game-data order.

| Control | Link result | Raw differing bytes | Moved mapped functions |
|---|---|---:|---:|
| No `/ORDER`, no new retention directives | Pass | 31918 | 0 |
| Game COMMON directives first, forward or reverse | Pass | 31918 | 0 |
| All COMMON directives last, forward or reverse | Pass | 31893 | 0 |
| All COMMON directives first, reverse | Pass | 70623 | 274 |
| All COMMON directives first, forward | Duplicate CRT startup definitions; unresolved `_main` | — | — |
| Forward directives with `/DLL` and `/ENTRY` moved first | Same failure | — | — |
| Forward directives with DLL startup `/INCLUDE` added first | Same failure | — | — |
| Forward directives with only `__acmdln` removed | Pass | 70679 | 274 |

The archive inspection identifies the unsafe retention anchor: both
`crt0.obj` and `dllcrt0.obj` declare `__acmdln` as a four-byte COMMON.
Forcing it early can pull executable startup into a DLL. Removing that
anchor resolves the failure; retaining the resulting link still disrupts
code layout. This is an archive-member selection finding, not evidence for
changing DLL startup code or silencing duplicates with `/FORCE:MULTIPLE`.
None of these controls was promoted.

The reference has no HIGHLOW relocation whose stored pointer targets the
suspected `0x10034684..0x10035408` gap. That does not identify its owner or
exclude indirect/indexed accesses. The supplementary linear disassembly
stops after 47320 of 141382 bytes and is explicitly recorded as incomplete;
it cannot establish that the whole text section has no accesses.

Evidence: `.scratch/native-common-includes/{probe.py,input-order.json,audit.json,
startup-common-members.json,gap-xrefs.json}` and per-control argv/link logs.
Both extracted startup objects are unchanged archive members. The canonical
`/ORDER` recipe and production definitions remain unchanged.

## 15. SP5 and SP6 use the same LINK; Win98 optimization changes file alignment

Both installed profiles report LINK **6.00.8447**, and their `LINK.EXE` files
have identical SHA-256:

```
9672e578fdfaa43bdb8e9c16071682988665cb90bba2904bf02f6a5576d8ffbc
```

Linking the canonical 190 objects with the SP6 profile while keeping all five
required import/CRT archives pinned to the unchanged SP5 files reproduces
the canonical 31493 raw differences, 16384-byte length gap, and section
extents. A service-pack switch here is not a different linker. Earlier SP6
CRT code differences came from input libraries, not this executable.

Native `/LINK50COMPAT` and explicit `/OPT:WIN98` leave extents, all 597 mapped
function positions, import identities/hints/slots, and the final unwind thunk
unchanged. The thunk stays at `0x1002383e`, reference `0x10023840`.
`/OPT:NOWIN98` also leaves virtual extents and code positions unchanged but
changes FileAlignment from `0x1000` to `0x200`: the file becomes 24576 bytes
short, with 200286 overlapping differences. It does not repair the two-byte
code alignment; it changes raw section packing.

Evidence: `.scratch/native-link-versions/{sp6-argv.json,sp6-audit.json,
flag-audit.json}` and the corresponding native link logs. Canonical flags
and libraries remain unchanged.

## 16. A native DOS-stub control can hide failure from an overlap-only byte count

The configured reference has `e_lfanew=0x80`, no Rich header, checksum `0x4d328`,
and COFF characteristics `0x230e` (debug-stripped bit present). The canonical
plain SP5 LINK baseline before adding `/RELEASE` has `e_lfanew=0xd8`, a Rich header, checksum zero, and
characteristics `0x210e`. Both report linker version 6.0, subsystem 4.0 and
FileAlignment `0x1000`. These header differences remain part of the objective;
function or section-content matches do not resolve them. The reference's
provenance cannot be established from these fields alone; see section 18's
subsequent comparison with local distribution copies.

**Do not use a complete PE as a DOS stub.** In the native `/STUB` control,
passing the unchanged reference DLL succeeds but embeds the entire reference
before a new PE header. The result has only three differing bytes over the
reference's file length, yet grows to 557056 bytes, moves all 597 mapped
functions, and puts its actual PE header at `0x46060`. It also has a Rich
header. This is a rejected diagnostic, not a matching build. Equality of
length and comparison of the active PE image are necessary alongside raw
overlapping-byte counts.

Native `/RELEASE` computes a nonzero checksum but leaves the other measured
header fields unchanged; its checksum cannot stand in for the reference's
while the image bytes differ. `/DEBUGTYPE:COFF` without `/DEBUG` changes
neither the Rich header nor the debug-stripped bit. These diagnostic links
edited no reference/output bytes. `/RELEASE` was subsequently promoted for
the configured reference's valid-checksum requirement (section 17).

This probe exposed a Rebrew path-translation defect: `/STUB:/absolute/path`
fell through the generic filename case, converting the *entire option* to
`Z:\\STUB:...`. The shared CMake linker translator now recognizes `/STUB:`
and converts only its path, including in response files. Relative paths,
case variants and a path containing spaces have regressions. All 36 CMake
bridge tests, Ruff check/format and mypy pass.

Evidence: `.scratch/native-header-controls/{audit.json,*-argv.json,*-link.log}`;
fix in sibling Rebrew's `src/rebrew/cmake_tc.py`, `tests/test_cmake_tc.py`,
and `CHANGELOG.md`. This pre-`/RELEASE` checkpoint was 16384 bytes short with
31493 overlapping differences. Whole-file identity was false.

## 17. `/RELEASE` computes the checksum from the native output

Plain MSVC 6 SP5 LINK 6.00.8447 accepts `/RELEASE` and writes a checksum that
equals LIEF's independent computation over the emitted file. The configured
reference also has a valid checksum (`0x4d328`), so this flag was added to
the canonical CMake target. No checksum constant or reference bytes are
copied. The actual value changes with the native file bytes, including its
link timestamp.

The resulting canonical DLL has 31496 overlapping differences and a
16384-byte length gap. All 262 reversed functions pass (22 EXACT, 240 RELOC),
without size divergences; all 597 mapped function positions are unchanged.
All 100 import identities and DLL order agree, with 23 displaced IAT slots
and no differing named-import hints. Both files contain 3499 live base
relocations; 164 remain displaced. The 52 readonly checks pass and the
190-object build has no flag drift. Whole-file identity remains false.

Evidence: `.scratch/native-header-controls/canonical-release-*`. This flag
is appropriate to the configured reference, **not the matching local stock
copies**, whose stored checksum is zero (section 18). Reference selection
must determine whether to keep it.

## 18. The configured reference has altered headers; local stock copies recover Rich records

The Steam English international, DVD English UK, and earlier local
reconstruction originals have identical SHA-256:

```
3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1
```

The configured `original/Server/server.dll` instead has SHA-256:

```
c7ac331f44292657c1fa613608ffd84c9d8ee778e3e7696c7782b37dd6d40ee5
```

Both are 286720 bytes. **All raw bytes, virtual sizes, RVAs and raw offsets
of `.text`, `.rdata`, `.data` and `.reloc` agree exactly.** The 285 differing
file bytes are confined to the headers. The configured copy has
`e_lfanew=0x80`, no Rich header, timestamp `0x699004a9`, checksum `0x4d328`,
and characteristics `0x230e`. The matching stock copies have
`e_lfanew=0xe8`, a Rich header, timestamp `0x3fdd84a0`, checksum zero, and
characteristics `0x210e`. This establishes alteration relative to the local
distribution copies; it does not identify who changed the file or how.
No reference file was modified during the investigation.

The stock Rich entries provide useful input-composition evidence:

| product id | build id | stock count | native count at this checkpoint |
|---|---:|---:|---:|
| 4 | 8447 | 1 | 1 |
| 10 | 8966 | 37 | 190 |
| 1 | 0 | 126 | 109 |
| 19 | 8034 | 9 | 9 |
| 10 | 8047 | 124 | 114 |
| 14 | 7299 | 22 | 22 |
| 11 | 8047 | 1 | 1 |
| 12 | 7291 | 6 | absent |

The linker build record agrees with the installed LINK 6.00.8447. The
different object counts expose input composition that still needs recovery;
they do not, by themselves, identify missing symbols or permit invented
storage. Header size is also affected by the number of Rich entries.
Historical claims that SERVER provides no Rich provenance apply only to
the altered configured copy, not these matching stock copies.

The installed plain RTM and SP5 images contain byte-identical stock
KERNEL32, USER32, WS2_32 and WINMM import archives. Selecting RTM for those
four archives therefore does not test a different member composition or IAT
order. The SHA-256 values are recorded in
`.scratch/native-reference-provenance/import-library-hashes.json`.

Evidence: `.scratch/native-reference-provenance/audit.json`, which records
both exact paths, hashes, section comparisons, header fields and Rich
entries. Reference selection was raised with the user; the configured
reference remains unchanged pending their answer. Code/data comparisons
remain useful against either copy because the sections are identical.

## 19. Identical memory-copy members need call-reference evidence to bind names

Plain SP5's unmodified `LIBCMT.LIB` supplies identical `memcpy.obj` and
`memmove.obj` `.text` sections: 821 bytes, 46 relocations, SHA-256
`cc84e3d1b41ff741cc25e7ca08cfe87c1d023d80828570c8517c822fea5675b0`.
Neither FLIRT names nor full-body equality establish which reference VA
belongs to which public symbol. `lib-match` returns both candidates.

The outgoing relocations in genuine stock callers resolve the binding:
`fwrite_lk`, `fread_lk`, four `realloc` sites and
`crtGetEnvironmentStringsA` reference `memcpy` at `0x1001eab0`;
`sbh_free_block`, `shift` and `fptostr` reference `memmove` at `0x1001b200`.
These ten linked calls had wrong REL32 fields with the previous anchor order.
Swapping the two existing `/INCLUDE` lines in
`layout/server.dll/native-archive-includes.rsp` corrects them. The stock
bodies and every other existing mapped function position stay unchanged.
The stable library identity headers were corrected to the same names.

Together with the game flush-call correction in C-shapes section 209, this
leaves only the final thunk's two-byte alignment discrepancy in the
HIGHLOW-normalized raw `.text` comparison. No CRT code was reversed or
edited; LINK continues to supply it from the stock archive. Evidence:
`.scratch/native-data-layout-audit/mem-{first,second}-libmatch.json`,
`memory-section-hashes.json`, `unmasked-text-instructions.json`,
`correct-memory-callers.json`, and `correct-memory-anchors-audit.json`.

## 20. Retaining a stock empty alias member changes native final-thunk alignment

With plain SP5 LINK 6.00.8447, `/OPT:REF /INCREMENTAL:NO /RELEASE`, and
the corrected memory bindings, appending
`/INCLUDE:__tcschr` to the archive anchor response file retains stock
`build\intel\st_obj\tcmap\chr.obj`. Its machine is zero, its `.text` is
empty, its `@comp.id` is product 12/build 7291, and its weak alias forwards
to already-linked `__mbschr`. This genuine stock member changes LINK's final
alignment: three native `CC` bytes precede `_RtlUnwind@16` instead of one.
The thunk moves from `0x1002383e` to the reference's `0x10023840`; `.text`
VirtualSize becomes the reference's `0x22846`. No padding object, output
edit or patched library is used.

Four native controls distinguish retention from ordering:

| stock alias anchors | `.text` VS | unwind VA | other existing functions moved | alias Rich count |
|---|---:|---:|---:|---:|
| `__tcschr` last | `0x22846` | `0x10023840` | 0 | 1 |
| `__tcsnicoll` last | `0x22846` | `0x10023840` | 0 | 1 |
| both last | `0x22846` | `0x10023840` | 0 | 2 |
| both first | `0x22854` | `0x1002384e` | 273 | 2 |

The early control is rejected: 274 total functions move, including unwind.
All late controls keep the 100 import identities, DLL order, 23 displaced
IAT slots, equal named-import hints, and data/readonly extents. The minimal
single-`__tcschr` late control is canonical. Its new alias map label shares
the target's address, bringing mapped labels to 598. This proves a native
alignment effect from a real stock input; it does not prove the exact
alias name present in the original. The pristine reference Rich header has
six product-12/build-7291 inputs, and their exact identities remain unknown.
The canonical count is now one, versus section 18's earlier absent record.

The complete raw `.text` sections are both 143360 bytes and have precisely
the same 3140 HIGHLOW sites. Masking only those sites yields zero differing
bytes. Raw `.text` still differs at 4644 bytes inside pointer slots. The
canonical file has 31473 overlapping differences and remains 16384 bytes
short; data, IAT placement, readonly ownership, relocation reservation and
headers remain unresolved. Both files contain 3499 live relocations, with
163 displaced outside code. The current native Rich header puts
`e_lfanew` at `0xe0`, rather than the configured reference's `0x80` or the
pristine reference's `0xe8`. Full-file identity remains false.

Evidence: `.scratch/native-data-layout-audit/alias-retention.py`,
`alias-retention-audit.json`, `crt-aliases.json`, `canonical-alias-build.log`,
and `canonical-alias-audit.json`. C-shapes section 210 describes the matching
tool's omission of these alias names and its fix.

## 21. Other stock CRT builds do not supply the missing BSS storage

Compare the unmodified RTM, SP5 and SP6 `LIBCMT.LIB` archives against the
124 CRT member names selected in the current native map. Raw archive/member
hash changes include timestamps and compiler records, so they are not code
or storage differences by themselves. Compare ordinary BSS section sizes/
flags, COMMON symbol sizes, and code with only actual COFF fixups masked.

| archive versus SP5 | selected members with BSS/COMMON differences | members with normalized code differences | actual reference bodies that fail the eligible comparison |
|---|---:|---:|---:|
| RTM | 2 | 8 | 19 of 293 |
| SP6 | 0 | 6 | 5 of 293 |

RTM changes storage only in selected `heapinit.obj` and `sbheap.obj`.
Their declared ordinary BSS/COMMON storage is 16 bytes smaller in total,
not the missing 3296 bytes; this is a symbol-size sum, not a native extent
prediction. The same members change required heap code. Examples of failing
RTM bodies are `_free`, `_realloc`, `_calloc` and the old small-block heap
helpers. SP6's selected BSS/COMMON shapes are identical to SP5, but actual
`__dosmaperr`, `__output`, `___old_sbh_resize_block`, `__NMSG_WRITE` and
`__setmbcp` bodies do not match the reference. Neither archive was substituted
in the canonical link, and no CRT code was reimplemented.

All 302 directly comparable SP5 mapped bodies match reference fixed bytes.
Nine are intentionally excluded from the library-origin verdict by
`lib-match`'s minimum-length/fixed-fraction guards. Counting those guarded
cases as alternative-archive failures would overstate the result; the table
uses only the 293 eligible bodies. Whole-member differences can also occur
in discarded helpers, so the direct reference-body check matters.

Archive SHA-256 values and all member/body results are in
`.scratch/native-crt-storage-builds/{compare.py,comparison.json,comparison.log}`.
This rules out these installed alternative CRT builds as a repair for the
storage gap; it does not identify the actual missing owner or original input
composition.

## 22. Tested native export and assembler aliases do not provide the required data binding

Before the successful C rewrite in section 23, alias controls tested whether
two source names could share the real compiler float pool without editing
objects or stock libraries. No generated diagnostic alias was added to the
canonical link.

SP5 LIB 6.00.8447 `/DEF` with an export alias and a native C data object
produces an import library and export object, not a zero-code weak alias
member. Four further controls used decorated export names, reversed aliases,
and `/LINK50COMPAT`; their generated members contain import descriptors/
thunks and no weak alias records. These outputs are not suitable for an
internal float-storage binding.

The installed MinGW 16.2.0 assembler, run only inside its Docker image,
accepts `.weak _probe_alias` plus `.set _probe_alias, _probe_target`.
It emits empty `.text`/`.data`/`.bss` sections and a weak external with
`SEARCH_NOLIBRARY` characteristic 1. A native SP5 LINK data-only control
with a real strong target and real C pointer reader still fails with
LNK2001 for `_probe_alias`. The tested `.weakref` spelling emits no external
alias and also fails linking; `.weakext` is an unknown pseudo-op for this
assembler target. These results concern the particular forms tested, not
all possible alias-generation tools or formats. The stock tcmap
`SEARCH_ALIAS` characteristic-3 members in section 20 are different.

Evidence: `.scratch/native-crt-storage-builds/alias-{target,use}.c`,
`alias-native.s`, `alias-native.obj`, `alias-binding-link.log`,
`export_alias_probe.py`, `native-lib-export-alias-controls.json`,
`native-assembler-alias-controls.json` and the corresponding native logs.
The final successful change uses ordinary C literals and deletes duplicate
definitions; none of these alias experiments is required by it.

## 23. Removing duplicate named floats shrinks readonly storage without changing code

The literal rewrites in C-shapes section 211 make all four existing
30/1000/8/4 named float definitions unused. Their removal leaves the actual
compiler literal COMDATs, with no manufactured bytes or linker aliases.
The native read-only checker checks their four actual pool symbols and
rejects a duplicate named definition; all 52 scalar/array values pass.

The canonical CMake build still uses 190 objects, plain SP5 and stock
libraries, with zero flag drift. Full verification passes 262/262
(22 EXACT, 240 RELOC) without size divergences. The entire 143360-byte raw
`.text` remains equal after masking only the same 3140 actual HIGHLOW sites.
Raw `.text` differences fall from 4644 to 4613, and raw `.rdata` differences
from 5161 to 3888. All 598 mapped labels, 100 import identities and DLL order
remain unchanged; 23 IAT slots still differ and named hints agree.

`.rdata` VirtualSize is now `0x2e91`, versus reference `0x2e81`: the excess
halves from 32 to 16 bytes. Other extents remain `.data -3296` and
`.reloc -15108`. Both files still have 3499 live relocations; displaced
sites fall from 163 to 156, restoring seven reference sites. The raw data
report improves from 261 to 279 matches, with 318 mismatches, seven missing
and four unchecked entries (608 total, 604 compared). Lint has zero errors
and 52 warnings. Values at native symbol locations are checked separately
from fixed-reference-VA data placement.

The raw canonical file has 30088 overlapping differences and remains 16384
bytes short (270336 versus 286720). Its SHA-256 at this checkpoint is
`5c238b10224df5f0247e624014315e134f002f6f4df86a179eb8e184a2e6139e`.
Stored checksum `0x497ed` equals the native computation, and `e_lfanew`
remains `0xe0`. File/header equality is still false, and the configured
reference has not been modified.

Evidence: `.scratch/native-crt-storage-builds/canonical-literals-*`,
`literal-callers-audit.json` and `literal-links-audit.json`. CMake produces
the DLL directly; only source definitions/readers and the readonly checker's
explicit symbol mapping changed. No postlink or library patch is involved.

## 24. Pure readonly object order restores strings; `/ORDER` moves literal COMDATs to the front

Plain SP5, unchanged 190 CMake objects and stock libraries, native
`/OPT:REF /INCREMENTAL:NO /RELEASE`: placing `rdata_restore.c.obj` before
`ahm_ExAllocAlchemist.c.obj` puts `unz_copyright` at `0x100252e8` and
`g_file_extension_names` at `0x10025314`, exactly their reference addresses.
Both strings previously sat 16 bytes late. No source bytes, function object
order, compiler flags or stock archive changed. This input order is promoted
in CMake. It identifies a sufficient placement, not the original source TU.

| native control | raw `.rdata` differences | strings at reference VAs | literal 30 VA | result |
|---|---:|---|---|---|
| section 23 baseline | 3888 | no | `0x100252e8` | prior canonical |
| strings before first literal owner | 3798 | yes | `0x10025340` | promoted |
| constants before first literal owner | 5044 | no | `0x10025f58` | rejected |
| strings and constants before first literal owner | 4391 | yes | `0x10025fb0` | rejected |
| `/ORDER` with actual `__real@4@...` names | 3888 | no | `0x100252e8` | ignored names |
| `/ORDER` with one leading underscore removed | 6229 | no | `0x100241a4` | rejected |

All five controls pass the 52 readonly-value checks and retain every mapped
function address, all code HIGHLOW sites, zero unmasked raw `.text`
differences, all 100 import identities, DLL order, 23 IAT displacements and
matching named hints. All section extents remain unchanged; `.rdata` is still
16 bytes too large. The successful strings control reduces its raw mismatch
by 90 bytes, with 29998 overlapping file differences at the diagnostic
timestamp and the unchanged 16384-byte length gap. The compiler literals
remain displaced. A correct string position alone does not establish the
rest of the readonly layout.

LINK adds the x86 C leading underscore to each `/ORDER` name. Supplying the
actual `__real@4@...` pool symbol therefore seeks nonexistent
`___real@4@...` and gives LNK4037. Removing one underscore is accepted,
but moves those four COMDATs to the start of the `.rdata` contribution group,
before the ordinary zlib readonly contributions. Their new addresses are
`0x100241a0..0x100241ac`. It does not interleave them among ordinary named
constants. Live fixup counts remain 3499 each, but displaced sites increase
from 156 to 166 in that control. This is a measured ordering limitation,
not a missing-symbol or weak-alias problem.

Evidence: `.scratch/native-readonly-placement/{probe.py,audit.json,*-argv.json,*-link.log}`.
Each probe changes only native LINK inputs and writes a separate diagnostic
DLL. No object, library, reference or completed DLL is edited.

The ordinary canonical CMake build confirms 29998 overlapping differences,
the unchanged 16384-byte length gap, and SHA-256
`de5ad7bfd784c2858ed357799d1f5d790f4d66b4b6531b002ab924f6fa2b98be`.
Both complete strings also pass readonly/value checks at their fixed reference
VAs (44 and 41 bytes). Verification passes 262/262, 22 EXACT and 240 RELOC,
with no size divergences. Data improves by two further entries to 281 matched,
316 mismatched, seven missing and four unchecked (608 total, 604 compared).
Build-check covers 190 objects with zero drift; lint has zero errors and
52 warnings. Stored/computed checksum is `0x50376`; full-file equality is
still false. Coverage is regenerated from this verification. Evidence:
`.scratch/native-readonly-placement/canonical-strings-*`.

## 25. Shared game/CRT double pools remove the remaining readonly extent surplus

Plain SP5, stock archives, `/OPT:REF /INCREMENTAL:NO /RELEASE`: the two
double-literal reader rewrites in C-shapes section 212 let LINK share the
game's zero/one pools with stock `cvt.obj` and `testfdiv.obj`. Removing their
two named double definitions eliminates duplicate ownership. The original
CRT code operands point to the game-region constants; the previous native
link's separate CRT doubles did not reproduce that relationship.

Both native link controls below retain all existing mapped function
positions, zero unmasked raw `.text` differences, the same code HIGHLOW
sites, all 100 imports/DLL order, 23 IAT displacements and equal named hints.
All 52 readonly values pass, checking the actual compiler-pool providers.

| native input control | `.rdata` VS | raw `.rdata` differences | overlapping file differences |
|---|---:|---:|---:|
| previous canonical | `0x2e91` | 3798 | 29998 |
| shared doubles, constant object last | `0x2e81` | 4746 | 31057 |
| also restore named 1000 / change only its reader | `0x2e81` | 4947 | 31257 |
| shared doubles, constants before 30 owner | `0x2e81` | 4641 | 30958 |
| shared doubles, constants before zero owner | `0x2e81` | 4790 | 31102 |
| shared doubles, constants before one owner | `0x2e81` | 3918 | 30208 |
| named 1000 variant, constants before 30 owner | `0x2e81` | 4455 | 30765 |
| named 1000 variant, constants before zero owner | `0x2e81` | 4719 | 30963 |
| named 1000 variant, constants before one owner | `0x2e81` | 3982 | 30271 |

The minimal shared-double variant with the constant object before
`gm_AllocSpieler.c.obj` is promoted. Its section VirtualSize equals the
reference's `0x2e81`, and all other section extents stay unchanged. This is
a storage-ownership and geometry repair, not a claim of readonly byte
identity: the total diff rises 210 bytes while placement remains unfinished.
Live relocation counts stay 3499 each, with 162 displaced sites rather than
156. The file remains 16384 bytes short. The successful individual named
1000 spelling is kept diagnostic; it improves neither the selected layout
nor its remaining sharing requirements.

Coarse object movement cannot place each pool within the contiguous ordinary
constant definitions. The reference interleaves constants and pools; a
matching VirtualSize alone is insufficient. No extra storage, synthetic
padding, stock-library alteration or postlink fix is added. Evidence:
`.scratch/native-pool-ownership/{pool-users.json,readers-audit.json,
links-audit.json,placements.py,placements-audit.json,*-argv.json,*-link.log}`.

Canonical verification passes 262/262 (22 EXACT, 240 RELOC), with no size
divergences. All 598 mapped labels retain their positions/bindings; full
raw `.text` has zero unmasked differences and the same 3140 HIGHLOW sites.
All 52 readonly values and both fixed-position strings pass. The pool audit
checks all seven game/CRT zero/one operands share their intended providers.
Data has 278 matches, 319 mismatches, seven missing and four unchecked
(608 total, 604 compared), versus the previous 281/316. Build-check covers
190 objects with zero drift; lint reports zero errors and 52 warnings.
All 100 import identities/DLL order agree, 23 IAT slots differ, hints agree.

At this checkpoint the native SHA-256 is
`1be041ceda5bd8a0db4dfd46570d4a158b55a8e377b1defce95d368e1c647de4`;
its stored/computed checksum is `0x49782`. Whole-file identity remains
false. Raw section differences are `.text 4622`, `.rdata 3918`,
`.data 20732`, `.reloc 655`; extents remaining are `.data -3296` and
`.reloc -15108`. Native zero/one locations are still `0x10025348` and
`0x10025fc0`, not their reference VAs. Evidence:
`.scratch/native-pool-ownership/canonical-shared-*`; coverage regenerated
after verification. No rejected zlib/order input is part of this build.

## 26. Publishing an empty private helper changes native ICF despite identical object bodies

The 190 canonical source objects contain 316 CODE COMDATs. An `/ORDER` file
covering their 316 mapped functions can resolve the 295 public symbols;
the 21 private zlib symbols produce LNK4037 and move to the unordered tail.
That direct ordering control moves function positions and is rejected.
All x86 names use the one-leading-underscore removal measured in section 24.

A diagnostic makes only those 21 functions public in `deflate.c`, `inftrees.c`
and `trees.c`, retaining private data declarations and the existing
`/O2 /Gd /MT` compile settings. All 32 measured bodies in the three objects
retain their full section sizes, flags, fixup positions and fixed bytes.
LINK now resolves all 316 ordered function names without private-symbol
warnings, but the resulting image is still wrong: 538 mapped labels move,
raw `.text` has 102167 differences outside the reference HIGHLOW slots and
different native HIGHLOW sites,
and its VirtualSize shrinks from `0x22846` to `0x22836`.

The cause is observed in the map and object bytes: the previously private
`tr_static_init` is a one-byte `ret` plus 15 compiler NOPs. Once public,
LINK folds it into `gm_NoopRet2`. The map points its label to
`0x10016660` in that game's object instead of the original `0x10006f30`.
Native ICF savings increase from 43 to 59 bytes, removing exactly that
16-byte contribution. `/INCLUDE:_tr_static_init`, and separately retaining
both it and `_gm_NoopRet2`, do not prevent the fold. These flags control
retention here; they do not preserve a distinct address under ICF.

This shows why equal normalized object bodies are insufficient to approve
a linkage change. Visibility can change LINK's folding eligibility and
therefore every subsequent position. No zlib linkage changes, code-order
file or retention control is promoted, and no CRT code is reimplemented.
Evidence: `.scratch/native-pool-ownership/{external_zlib.py,
zlib-body-controls.json,text-order-baseline-audit.json,
external-zlib-baseline-audit.json,external-zlib-include-*-argv.json}` and
the corresponding native MAP/link logs.

## 27. COFF operand identity detects storage blocks that cannot be placed contiguously

The native image and reference have identical raw `.text` bytes outside the
same 3140 actual HIGHLOW sites. Use the live object section's mapped code base
and its DIR32 relocation record to identify the operand's **symbol and
addend**. For a defined symbol, the implied storage-section base is:

```
(linked_operand - COFF_addend - symbol_section_offset) modulo 2^32
```

For an undefined or COMMON symbol, omit the section offset. A COMMON symbol's
COFF value is its allocation size, not an address offset. Require owner-scoped
MAP anchors; private names such as `LeadUp1` occur in multiple archive members.
This is an audit of the actual objects, not a nearest-address symbol guess.

The unsigned arithmetic matters: stock `output.obj` references its
`___lookuptable` with both addends zero and `0xffffffe0` (-32). They imply the
same native base `0x10026010` and reference base `0x10026008`. Treating the
second addend as an unbounded positive Python integer invents a conflicting
negative base. Also, 21 stock CRT DIR32 fields name absolute `__except_list`
with value/addend zero. They are not PE HIGHLOW sites and must not be rebased.

The current audit reads 191 native source objects and 124 selected members of
the unchanged SP5 archive, SHA-256
`28b9f04962378ec4668072f37d7fd2835cd6cacc17b40cf22002c57bd8e76714`.
It accounts for 3132 of the 3140 code HIGHLOW sites. The eight others are the
seven import-thunk operands at `0x1001a162..0x1001a186` (stride six) and the
final unwind thunk at `0x10023842`; import archives are outside this audit.
It also checks 19 initialized data sections at their inferred bases, masking
only actual COFF relocation fields before following their initializer pointers.
Eighteen are stock CRT sections; one is the actual `z_errmsg` table.

Three current game BSS sections produce conflicting implied reference bases:

| Current object | Concrete conflict | Consequence |
|---|---|---|
| `server.c.obj` | `g_handler_started` offset zero targets `0x10034680`; `g_thread_handle` offset four targets `0x11764094` | The two definitions cannot remain a single eight-byte reference block. |
| `ServerMainThread.c.obj` | max/tick offsets zero/four target `0x11764084/88`, but players-synced offset eight targets `0x11764090` | A four-byte owner at `0x1176408c` lies between them; whole-object movement cannot supply it. |
| `gm_Open.c.obj` | six scalars imply bases `0x10034624`, `0x10034638`, `0x10034664`, `0x10034668` | Its current 24-byte section does not reproduce the original field spacing. |

The readonly constants section also has conflicting bases because literal
pools interleave the reference's named definitions. Section 28 fixes its
early type-table prefix without moving code; the remaining scalar/table
section still has five distinct implied bases. These contradictions establish
that whole-object movement is insufficient. They do **not** by themselves
recover the original translation units or prove the extents of unreferenced
game storage. The 465 inferred section candidates include pooled contributions;
they are not 465 independently proven original owners.

Initializer pointers recover storage absent from direct code references.
The stock `mlock.obj` 192-byte initialized table, reference `0x10031aac`,
identifies its unchanged 96-byte BSS block at `0x10035538`. Its four actual
critical-section targets are `0x10035538`, `0x10035550`, `0x10035568`,
`0x10035580`. The native block is `0x117651e0`; no CRT storage is reconstructed.
The 60-byte stock `lconv.obj` initializer has exactly one full fixed-byte
match in reference `.data`, at `0x10034310`. Its nine null-string pointers
all target the one-byte BSS owner `0x10035864`, native `0x1176550c`.
Section 213 of the C-shapes companion separately records the generated
empty-string BSS owner at `0x10034620`.

These identify actual small owners and constraints; they do not identify an
owner for the unreferenced `0x10034684..0x10035408` gap or solve the 3296-byte
VirtualSize deficit. No BSS padding, archive changes, source body changes or
metadata hand edits result from the audit. Evidence:
`.scratch/native-storage-bindings/{audit.py,audit.json,operands.json,
before-types-audit.json,before-types-operands.json}`. The script asserts native
code equality, map consistency, absolute-zero exclusions, the unique `lconv`
match and absence of conflicting stock-CRT storage bases.

## 28. A separate type-table C object restores 832 bytes without changing function order

The reference stores five named type-adjustment owners at
`0x10025340..0x10025680`, before every game literal pool. The previous single
`game_float_constants.c` object put those owners 32 bytes late while keeping
many later constants correctly positioned. Moving the entire object earlier
was already rejected in sections 24–25; those controls moved later data too.

Separate only the five existing C definitions, unchanged, into
`src/Develop/DieGildeAddOn/game/type_adjustments.c`. Keep the other definitions
and compiler-pool inventory labels in `game_float_constants.c`. With the same
plain-SP5 `/O2 /Gd /MT` settings, the new object emits one 832-byte `.rdata`
section, flags `0x40400040`, zero relocations, **identical to every reference
byte in that span**. Its alignment comes from the compiler. No bytes or
alignment arrays are supplied manually.

Place this pure data object between the existing readonly string owner and
`ahm_ExAllocAlchemist.c.obj`, the first float-literal provider. Keep the later
constants object before `gm_AllocSpieler.c.obj`, as in section 25. The native
diagnostic preserves all 598 function labels and bindings, all code HIGHLOW
sites and all section extents. CMake promotes precisely this input order.

| Owner | Reference and new native VA | Bytes |
|---|---|---:|
| `g_type_adjustments` | `0x10025340` | 600 |
| `g_type_adjustments_count` | `0x10025598` | 4 |
| `g_type_adjustments_secondary` | `0x100255a0` | 200 |
| `g_type_adjustments_secondary_count` | `0x10025668` | 4 |
| `g_type_multipliers` | `0x1002566c` | 20 |

The remaining four bytes in the 832-byte contribution are native alignment
before the second table. The existing readonly checker now reads both source
files, checks the two full record arrays as well as the previous 52 values,
and requires all five type-owner addresses to equal their reference VAs.
All 54 values pass. A previously passing native value-only snapshot is rejected
by the new placement guard: `Misplaced type table: g_type_adjustments`.

The promoted canonical build has **29835 overlapping differences**, down
373 from 30208. Readonly raw differences fall 3918 -> 3556; raw code
differences inside pointer slots fall 4622 -> 4613. It remains 16384 bytes
short. `.text` VS `0x22846` and `.rdata` VS `0x2e81` still match;
`.data -3296` and `.reloc -15108` remain. No other raw section diff changes.
Literal order still differs: the native 30/zero/1000/8/4 pools are
`0x10025680/688/690/694/698`, while their reference VAs are
`0x100256c4/698/680/7c4/7c8`. Keeping the same providers and code-object order
therefore still requires more than splitting the ordinary constant data.
The double-one pool remains late at `0x10025fc0`, reference `0x100257d8`.

Verification: 262/262 (22 EXACT, 240 RELOC), no size divergences;
data 284 matched, 313 mismatched, seven missing, four unchecked (608 total).
Raw-link status write suppression is retained. Build-check covers 191 current
objects with zero drift. Lint: zero errors, 52 warnings, 4121 files passed.
All 100 import identities, DLL order and hints remain correct; 23 IAT slots
still differ. Both images have 3499 live relocations with 162 missing/extra
sites outside code. Full raw `.text` still has zero differences after masking
only the identical 3140 actual HIGHLOW slots. Both readonly strings and all
seven game/CRT zero/one operands retain their required sharing.

Native SHA-256 at this checkpoint:
`c24adf7d12a9b18ac65a1c94ec6ff632567692b843b006ce94bef1e706e9744e`;
checksum stored/computed `0x4203b`. The extra compiler object also changes
the Rich compiler record count 190 -> 191 and observed `e_lfanew` `0xe0` ->
`0xf0`. Other Rich record counts are unchanged. This observation does not
isolate a rule connecting source count alone to header alignment. The header
remains part of the unfinished whole-file objective.

Evidence: `.scratch/native-storage-bindings/{split_types.py,
split-types-audit.json,split-types-argv.json,split-types-link.log,
canonical-types-*,rejected-type-placement.txt}`. Diagnostic and canonical
raw-link checks agree on section/code/import results. The independent whole
file gate still fails, as expected; no postlink edits or library patches are used.

## 29. Native LINK also writes its timestamp inside the readonly export directory

The section comparison between section 28's diagnostic and canonical links
finds identical geometry and raw `.text`, `.data`, `.reloc` bytes. Their
`.rdata` bytes differ only at RVAs `0x26e34` and `0x26e35`. These lie in the
actual export directory's four-byte timestamp field (directory RVA `0x26e30`,
field offset four); every other readonly byte agrees. This is not a remaining
constant-owner discrepancy between those two links.

Under the unchanged native SP5 link flags, the diagnostic COFF and export
timestamps both equal `0x6abe3d64`; the canonical pair both equal
`0x6abe3e26`. Header/checksum bytes consequently differ too. The independent
whole-file gate still includes all these differences. Only the diagnostic
reproducibility comparison identifies this specific timestamp field; it does
not normalize the actual build or the reference.

The configured reference has different values in those two fields: COFF
`0x699004a9`, export `0x3fdd84a0`. This supplements section 18's evidence of
altered headers. Matching only a native header timestamp would therefore not
match the reference's export-directory timestamp under the measured recipe.
Reference selection remains unchanged; no timestamp/header patch is made.

Evidence: `.scratch/native-storage-bindings/canonical-vs-diagnostic.json`,
which checks every raw section byte, requires differences to be contained in
the actual export timestamp field and checks both native COFF/export pairs.
