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

**Only `B` matters.** `rebrew build postlink`'s data fixer overwrites the built
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
PYTHONPATH=$PWD/.scratch/rebrew-stable/src rebrew build layout --data-gap 0x4600
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

`rebrew build postlink` refuses to run unless the built bytes between the IAT and
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
* Historical interpretation, superseded by section73: the IAT slot order
  was described as hash-driven and not forceable with `/include`, so
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
| `/OPT:NOREF` | keeps every COMDAT of every linked object. Needed: our reversed `.text` is not all referenced, and `/OPT:REF` gutted it (`0x22256 -> 0x100c6`). |
| `/OPT:REF` (current, with `layout/server.dll/game-includes.rsp`) | drops unreferenced COMDATs: `.rdata 0x3041 -> 0x2f81` (raw `0x4000 -> 0x3000`!), `.data 0x1743498 -> 0x1742614`, and `.text` down to `0x100c6`. Not usable as-is, but it proves the surplus is unreferenced COMDATs. |
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

* **`rebrew build layout` is not output-stable.** Two of the files it rewrites
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

Offline census after the library-ordering repair: the reference and saved
native baseline each contain 44 blocks totaling 7404 bytes, with 3499
HIGHLOW entries and 27 ABS alignment entries. Their remaining virtual
extents are entirely zero: 59016 bytes in the reference versus 43908 in
the saved native file. Thus the 15108-byte gap is reservation beyond the
live block payload. This is a measurement of the saved baseline, not a
freshly rebuilt deliverable. Evidence:
`.scratch/repaired-native-config/relocation-census.json`.

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

## 30. Order every source readonly COMDAT to interleave the real compiler pools

A literal-only `/ORDER` moves the pools before ordinary zlib readonly data
(section 24). The data-only `selectany` declarations in C-shapes section 214
make every preceding source readonly owner eligible for the same native order.
No code helpers become public; the empty `tr_static_init` remains private,
so section 26's extra ICF fold is not introduced.

The existing `layout/server.dll/common-data-order.txt` now starts with the
75 readonly symbols in reference-address order, followed by its unchanged
COMMON data order. Its historical filename describes only the latter part.
For native x86 `/ORDER`, remove one leading underscore from actual COFF names,
including `__real@...` pool names; LINK adds the C decoration itself.
The source definitions retain their natural alignment (C-shapes 214).
Unused real readonly owners need `/INCLUDE` under the existing `/OPT:REF`:
69 decorated symbol anchors are appended to the existing
`native-archive-includes.rsp`. These retain actual reference data; they do
not introduce padding or change the ordered stock CRT member anchors.

The clean diagnostic puts all 75 owners at their reference addresses, with
full contents equal. All bytes from `0x100241a0` through `0x10025fbf` match:
7712 bytes of zlib tables/strings, type tables, game definitions, real compiler
pools, pointer initializers and native alignment. In particular the pools
now land at their actual reference VAs:

| Pool | Native and reference VA |
|---|---|
| float 1000 | `0x10025680` |
| double zero | `0x10025698` |
| float 30 | `0x100256c4` |
| float 8 | `0x100257c4` |
| float 4 | `0x100257c8` |
| double one | `0x100257d8` |

The diagnostic preserves every one of the 598 mapped function bindings, the
complete raw code outside its identical 3140 HIGHLOW fields, all 100 import
identities, DLL order and named hints. The 23 displaced IAT slots remain.
Live relocations remain 3499 each; missing/extra sites improve 162 -> 151
outside code. Section extents are unchanged: `.text` VS `0x22846`, `.rdata`
VS `0x2e81`, `.data` deficit 3296, `.reloc` deficit 15108. The stock CRT
readonly lookup table now also lands at reference `0x10026008`, through the
correctly sized source readonly contributions; it is supplied by the stock
archive.

Diagnostic overlapping differences fall 29835 -> 28367 (1468 fewer), with
raw differences `.text` 4613 -> 4484, `.rdata` 3556 -> 2304,
`.reloc` 655 -> 568; `.data` remains 20732. The whole file remains 16384
bytes short and unequal. The promoted canonical build
reproduces these measurements; native timestamp/checksum fields stay in the whole-file
comparison as described in section 29.

Evidence: `.scratch/native-readonly-order/{link.py,ordered-argv.json,
ordered-link.log,ordered-audit.json,ordered-owners.json,ordered-values.json,
rejected-placement.txt}`. The values output checks the two original readonly
strings. The canonical readonly gate now requires every annotated game owner's exact VA
and all 7712 source readonly bytes, rather than accepting values at shifted
addresses. This change uses native compiler/linker output and adds no manual
padding, archive patches or object rewriting. C-shapes 214 records the
inherited, unresolved extra `border` dword; this byte match does not establish
its original ownership.

Canonical validation (2026-10-01): native `cmake --build build --target
server_dll -j4` succeeds. All 75 readonly owner bindings/values and all
7712 source readonly bytes pass. The full comparison is 28367 differing
bytes plus a 16384-byte length gap, as above. Verification remains 262/262
(22 EXACT, 240 RELOC), zero failures and no size divergences. Data improves
284 -> 320 matched; 277 mismatched, seven missing, four unchecked (608 total,
604 compared). `--raw-link` acknowledges the native link and permits managed data-status writes. Build-check
covers 191 current objects with zero drift. Lint: zero errors, 52 warnings,
4121 files passed. The seven game/CRT zero/one operands keep their shared
providers and now their exact reference target addresses.

Canonical SHA-256:
`3663890b7aeb9c033325c590d599c4e24eb6a2be7d9cffab37c7c3ea36a812f1`;
stored/computed checksum `0x43d21`, `e_lfanew` `0xf0`, Rich counts unchanged.
The diagnostic/canonical raw `.text`, `.data`, `.reloc` sections are identical;
readonly differences between those two native links are only the actual
export timestamp bytes at RVAs `0x26e34/35`. Strict independent whole-file
verification and the CLI whole-binary check still fail on the unresolved
file/data/layout differences; 262 matched functions are not whole-file
identity. Coverage is regenerated from the completed verification.
Canonical evidence: `.scratch/native-readonly-order/{canonical-build.log,
canonical-audit.json,canonical-owners.json,canonical-readonly.txt,
canonical-pool-users.json,canonical-build-check.json,canonical-lint.json,
canonical-full-verify.json,canonical-objective.txt,canonical-coverage.json,
canonical-vs-diagnostic.json}`.

## 31. Request stock CRT data members before their deferred dependencies place them late

With section 30's native readonly order in place, actual matched-code COFF
operands identify the remaining CRT contributions. Most readonly CRT data is
already at its reference addresses. Two late members explain the remaining
constant/string interleaving; their bytes are supplied by stock SP5 LIBCMT,
not by local CRT definitions.

`timeset.obj` has a 61-byte ordinary readonly section, flags `0x40300040`.
`___dnames` is at offset zero; `___mnames` at offset 24. The reference base
is `0x10026418`, but the previous native base was `0x100264a0`. Its separate
148-byte initialized `.data` section contains the timezone defaults and
names. This member has no code to retain or reorder.

`strftime.obj` owns the C-locale readonly string COMDATs and initialized
`___lc_time_c` table. The native build already selects the member for data;
its formatting function bodies are discarded under the existing `/OPT:REF`.
Its first readonly string, `H:mm:ss`, previously landed at `0x100264e0`
instead of reference `0x100264c8`. The `a_cmp.obj` 24-byte exception table
was before these strings, at `0x10026488` instead of `0x100265f0`.

Add two decorated data anchors to the existing native library-retention list:

```text
/INCLUDE:_calloc
/INCLUDE:___dnames
...
/INCLUDE:_$I10_OUTPUT
/INCLUDE:___lc_time_c
```

These request the actual data members at the appropriate stage of the native
archive selection order. No object/archive contents, source definitions,
compiler flags or code anchors are changed. Unlike section 14's COMMON
controls, these directives affect where newly selected library data members
contribute their sections. They are not a general replacement for `/ORDER`.

Three controls use the same canonical objects and stock libraries:

| New data anchors | Full function bindings preserved | Raw `.rdata` differences | Raw `.data` differences | Overlapping file differences |
|---|---|---:|---:|---:|
| neither (section 30 checkpoint) | yes | 2304 | 20732 | 28367 |
| only `___dnames` | yes | 2134 | 20737 | 28188 |
| only `___lc_time_c` | yes | 1727 | 20779 | 27850 |
| both, promoted | yes | 1274 | 20748 | 27342 |

With both anchors, **every one of the 9320 readonly bytes from
`0x100241a0` through `0x10026607` matches the reference**. This extends the
7712-byte source match by all 1608 subsequent stock CRT readonly bytes.
It includes the stock exception tables, lookup table, fdiv literals, runtime
messages, month/day abbreviations, error-number spellings and C-locale
strings. The import descriptor group now begins at reference `0x10026608`.
The `a_str` exception table, user32 procedure-name strings, `x10fout` strings
and `a_cmp` exception table all regain their reference positions.

The selected stock archive remains unchanged (SHA-256
`28b9f04962378ec4668072f37d7fd2835cd6cacc17b40cf22002c57bd8e76714`).
The source and library selection counts remain 191 objects and 124 members.
All 598 mapped function bindings and all 3140 actual code HIGHLOW sites remain
unchanged. Full raw code has zero differences outside those sites. Import
identities/count (100), DLL order and named hints remain correct; 23 IAT
slots are still displaced. Live relocations remain 3499 each; missing/extra
sites improve 151 -> 128 outside code.

Moving complete stock data members also moves their writable data.
`__timezone` now lands at `0x10033cf0`, reference `0x10033f80`;
`___lc_time_c` lands at `0x10033ee0`, reference `0x10034260`.
Their writable placement remains unfinished. `.data` raw differences rise
by 16, while the total file diff falls by 1025. Natural input alignment raises
native `.data` VS `0x173f8bc` -> `0x173f8dc`, reducing its deficit
3296 -> 3264; no definition size or padding is added. This observation does
not identify a missing 32-byte owner. `.text` VS `0x22846`, `.rdata` VS
`0x2e81` and `.reloc` VS `0xc870` remain unchanged. The file remains
16384 bytes short, with the `.reloc` VirtualSize deficit still 15108.
Raw `.text` differences fall 4484 -> 4471 inside pointer slots; `.reloc`
raw differences change 568 -> 570.

The readonly checker now checks the full 9320-byte source/stock CRT span,
as well as all 54 annotated game values at their exact VAs. The prior native
DLL passes all 54 game values and fails this new span guard:
`Source and stock CRT readonly span differs`. The inherited `border` dword
ownership caveat in C-shapes 214 still applies; native byte equality does not
resolve that separate provenance question.

Evidence: `.scratch/native-bss-owners/{data_anchors.py,data-anchors-audit.json,
*-includes.rsp,*-argv.json,*-link.log,both-full-audit.json,
before-data-anchors-audit.json,before-data-anchors-operands.json,
rejected-crt-readonly-order.txt}`. The current `audit.json`/`operands.json`
revalidate section binding against the promoted native link; they preserve the
three game BSS composition conflicts from section 27. No new Rebrew tooling
defect was encountered in these controls.

Canonical validation (2026-10-01): native build succeeds; 262/262 functions
pass (22 EXACT, 240 RELOC), no size divergences. Data improves 320 -> 348
matched, with 249 mismatched, seven missing, four unchecked (608 total,
604 compared). `--raw-link` acknowledges the native link and permits managed data-status writes. The full
readonly run and all seven shared game/CRT zero/one operands pass. Build-check
covers 191 current objects with zero drift; lint zero errors, 52 warnings,
4121 files passed. Coverage is regenerated after verification. Full CLI and
independent whole-file checks remain unsuccessful, as expected from the
actual remaining bytes and length gap.

Canonical SHA-256:
`1f1f4cddf579267b2e9bc30ff2b6a4e87a83a8e3f55d00876d9b6d0cfd0364b3`;
stored/computed checksum `0x450a8`, `e_lfanew` `0xf0`, Rich counts unchanged.
Its measurements equal the promoted diagnostic: 27342 overlapping differences,
16384 bytes short. Diagnostic and canonical raw `.text`, `.data`, `.reloc`
are identical. Their readonly differences are restricted to the actual
export timestamp field, as in section 29. Canonical evidence:
`.scratch/native-bss-owners/{canonical-build.log,canonical-audit.json,
canonical-readonly.txt,canonical-pool-users.json,canonical-build-check.json,
canonical-lint.json,canonical-full-verify.json,canonical-objective.txt,
canonical-coverage.json,canonical-vs-diagnostic.json}`.

## 32. Restore real writable owners before removing their duplicated literals

C-shapes 215–216 establish two separate writable-data issues through actual
COFF references: the missing shared VFS mode string, and duplicated alchemy
strings whose live compiler pools already exist. Keep source code order and
stock archive selection unchanged. Insert the existing 25-byte alchemy header
as a data-only source immediately before `ahm_ExAllocAlchemist.c`; the linker
supplies its trailing alignment naturally. Replace the four unused named
string definitions with extern inventory labels and keep the actual later
alchemy tables in their original code owner. Add the existing `"rb"` string
as the opening VFS data definition and make its three readers share it.

The two repairs interact with native input alignment. Before either change,
VFS data starts at `0x1002944c`, four bytes before its reference magic values,
and the office tables start at `0x10029ae8`, eight bytes before reference
`0x10029af0`. Adding the real three-byte mode and its natural alignment
restores the VFS values and triggers the office contribution's native
alignment, correcting the subsequent eight-byte displacement.

The alchemy header previously followed the live string pools and began at
`0x1002a1a8`, 184 bytes past reference `0x1002a0f0`. Simply moving the
existing header before those pools and removing the duplicated arrays leaves
its new start at `0x1002a0e8`: still eight bytes early without the preceding
VFS/office repair. Separate controls expose this interaction:

| Native source control | Raw `.text` diff | Raw `.rdata` diff | Raw `.data` diff | Raw `.reloc` diff | Overlapping file diff |
|---|---:|---:|---:|---:|---:|
| Previous canonical | 4471 | 1274 | 20748 | 570 | 27342 |
| Alchemy header and duplicate removal only | 3433 | 1274 | 21172 | 418 | 26576 |
| VFS mode and three readers only | 4353 | 1274 | 20151 | 567 | 26624 |
| Both, promoted | 2777 | 1274 | 1851 | 159 | 6340 |

Every control preserves all 598 mapped function bindings, all 3140 actual
code HIGHLOW sites and zero raw-code differences outside those sites.
The successful combined link retains all 9320 source/stock CRT readonly bytes
and all 54 annotated readonly game values at their exact addresses. No code
helper visibility, compiler flags, library body, library selection directives
or readonly ordering is changed by this repair.

With both changes, the mode, two magic DWORDs, VFS path and message match
all 85 bytes at `0x1002944c`; all three code operands target the same
reference mode owner. The alchemy floats and tag now match at
`0x1002a0f0`, `0x1002a0f4` and `0x1002a0f8`; the two complete tables match
at `0x1002a1cc` (7812 bytes) and `0x1002c050` (928 bytes).
The entire 16872-byte initialized span from `0x1002a0f0` through
`0x1002e2d7` matches, including the compiler literal pools and natural
alignment. None of the four duplicated public array symbols, or the former
anonymous mode pool, remains defined in the MAP.

The combined native `.data` VS changes `0x173f8dc` -> `0x173f81c`,
shrinking by 192 bytes after the unused string copies are removed.
The deficit to reference VS `0x174059c` becomes 3456 bytes; a smaller numerical
deficit was not evidence of better ownership. The live relocation count
remains 3499 in both files, with missing/extra sites improving 128 -> 80,
all outside code. The VFS-only control has 130 missing/extra sites; it is
not enough to restore the later complete data run. The same 100 import
identities, DLL order and named hints remain intact, with 23 displaced IAT
slots. Raw `.text`/`.rdata` extents remain exact; `.reloc` VS remains
`0xc870` against reference `0x10374`. The file is still 16384 bytes short
and unequal; headers, writable CRT/BSS ownership, imports and relocation
extent remain unfinished.

Evidence: `.scratch/native-mutable-owners/{link.py,link-controls.json,
*-objects.rsp,*-argv.json,*-link.log,*-audit.json,combined-values.json,
combined-readonly.txt}`. Each link uses canonical native objects with the
listed whole-object substitutions and unchanged stock libraries; no object,
archive or linked bytes are patched. The diagnostic LNK4070 warning describes
its alternate output filename versus the original DEF export name; the
canonical output name remains `server.dll`. No duplicate-definition warning
is suppressed. Managed string-size corrections are documented in C-shapes 215.

Canonical validation (2026-10-01): the production CMake build reproduces the
combined control. A VFS block comment beginning `DATA: SERVER` was being
recognized as a second annotation once the actual mode owner acquired its
marker; replace the comment heading with ordinary prose. This is an
annotation correction, with no generated-code change. Final lint has zero
errors, 52 warnings and 4122 files passed. Build-check includes 192 objects,
zero drift. Verification passes 262/262 functions (22 EXACT, 240 RELOC),
zero failures and no size divergences. Full data verification improves
348 -> 526 matched, with 71 mismatched, seven missing and four unchecked
(608 total, 604 compared), using the corrected complete string sizes.
Verification explicitly uses `--raw-link` and writes the measured data
verdicts through the managed CLI. Coverage is regenerated after verification.

Canonical SHA-256:
`9c0a21fa77e41b170fd0d2d4fcdf6c1f4c7a2fdb869173ac946aee81ea9ecce4`;
stored/computed checksum `0x4d849`, `e_lfanew` `0xf0`.
Rich's game compiler input count becomes 192 because the existing three
header definitions now have a separate real data object; it was previously
191. The unchanged stock archive contributes the same 124 selected members.
The storage audit still identifies the three conflicting game BSS section
compositions from section 27; no BSS placeholder is removed or extended.
The canonical overlapping difference count is 6340, with the same 16384-byte
length gap and false whole-file identity. CLI and independent whole-file
checks correctly remain unsuccessful. Diagnostic/canonical raw `.text`,
`.data` and `.reloc` match; readonly differences are only the actual export
timestamp field. Final canonical evidence:
`.scratch/native-mutable-owners/{canonical-final-build.log,
canonical-audit.json,canonical-values.json,canonical-readonly.txt,
canonical-final-verify.json,canonical-final-lint.json,
canonical-final-build-check.json,canonical-final-coverage.json,
storage-audit.py,audit.json,operands.json,check_values.py}`.

## 33. Keep the shared zlib version characters before their existing pointer

C-shapes 217's native C spelling fixes the remaining source-library version
run without changing object order. The former four-byte ordinary pointer
followed by a six-byte compiler string becomes one 12-byte ordinary data
contribution containing the real character array, natural alignment and
existing pointer. All literal readers share that real array, so there is no
second string pool.

The diagnostic preserves all 598 mapped function bindings and 3140 actual
code HIGHLOW sites, with zero raw-code differences outside those sites.
All 9320 readonly source/stock CRT bytes and 54 annotated game values still
match, as do section 32's complete 85-byte VFS and 16872-byte game data runs.
All 12 version-run bytes and its four code operands now equal the reference.
The total overlapping difference count falls 6340 -> 6323: raw `.text`
2777 -> 2773, `.data` 1851 -> 1839, `.reloc` 159 -> 158; `.rdata` remains
1274. Timestamp/checksum bytes remain part of the strict file comparison.
The live relocation count stays 3499 each; missing/extra sites improve
80 -> 79, all outside code. This is placement of one existing pointer,
not an added relocation or manufactured extent.

All native section VirtualSizes and raw lengths remain unchanged. The
`.data` VS deficit remains 3456, `.reloc` VS deficit 15108, file length gap
16384. Import identities/count/DLL order/named hints remain correct, with
23 displaced IAT slots. Stock SP5 archive bytes, CRT code, selected members
and retention directives remain unchanged. The whole-file objective remains
incomplete. Evidence: `.scratch/native-version-owner/{link.py,
version-objects.rsp,version-argv.json,version-link.log,version-audit.json,
version-values.json,check_game_readonly.stdout,check_values.stdout}`.

Canonical native build (2026-10-01) reproduces the diagnostic's 6323
overlapping differences and unchanged 16384-byte length gap. SHA-256:
`f463550ae0eb7165186cd09252cf56c4196d1c0bcc42356019b51a947a7e9534`;
stored/computed checksum `0x4d29f`, `e_lfanew` `0xf0`, Rich input counts
unchanged from section 32. The build has 192 source objects and 124 selected
stock CRT members; build-check finds zero drift. Lint: zero errors, 52
warnings, 4122 files passed. Complete readonly, version-run and game writable
checks pass. The three prior BSS composition conflicts remain. The diagnostic
and canonical raw `.text`, `.data`, `.reloc` sections are identical; their
readonly difference is restricted to actual export timestamp bytes at
RVAs `0x26e34/35`. The independent strict whole-file check still fails,
with no normalization or reference change. Canonical evidence is in
`.scratch/native-version-owner/{canonical-build.log,canonical-audit.json,
canonical-values.json,canonical-game-writable.json,canonical-readonly.txt,
canonical-build-check.json,canonical-lint.json,canonical-vs-diagnostic.json,
canonical-objective.txt,storage-audit.py,audit.json,operands.json}`.

Final function verification is 262/262 (22 EXACT, 240 RELOC), zero failures
and no size divergences. Data now has 527 matched, 70 mismatched, seven
missing and four unchecked (608 total, 604 compared), one more full symbol
matched than section 32. `--raw-link` explicitly permits managed data-status
writes. All seven shared game/CRT zero/one operands remain correct.
CLI whole-binary verification exits unsuccessful because whole-file equality
and the remaining layouts are still false; the function results are all
successful. Coverage is regenerated after this completed verification.
Evidence: `canonical-full-verify.json`, `canonical-coverage.json` and
`canonical-pool-users.stdout` in the same experiment directory.

## 34. Retention order can place existing stock CRT data without adding code

Plain SP5 native LINK controls on section 33's 192 source objects and
unchanged stock archives. Insert data `/INCLUDE` anchors immediately after
the existing `__except_handler3` anchor; retain the canonical `/OPT:REF`,
COMMON/readonly ORDER and all other flags. `cmiscdat.obj`'s existing
24-byte `__cfltcvt_tab` belongs at `0x10033bb0`. Data anchors affect stock
selection/contribution order even when those data symbols are already live.

| Added anchors, in sequence | Overlapping differences | Unmasked raw-code changes | Mapped functions | Missing/extra live sites |
|---|---:|---:|---:|---:|
| None, section 33 canonical | 6323 | 0 | 598 | 79 each |
| `__cfltcvt_tab` | 6977 | 0 | 598 | 74 each |
| `__cfltcvt_tab`, `__pctype`, `___mb_cur_max` | 6236 | 0 | 598 | 76 each |
| Same sequence with `___init_dummy` between table and ctype | 6050 | **434** | **599** | 62 each |

The three-anchor candidate fixes all 24 table bytes and all nine actual
code operands into that table. Its `__pctype`/`___mb_cur_max` bindings
are `0x10033bc8/0x10033dd4`, still 268 bytes before reference
`0x10033cd4/0x10033ee0`: the intervening private locale cache contribution
is misplaced, not absent. All 267 bytes of that untouched stock contribution
occur uniquely at `0x10034110` in this control, against `0x10033bc8` in
the reference. C-shapes section 220 explains why its member has no MAP owner.

The three-anchor candidate preserves the complete 9320-byte readonly run,
all 54 readonly game values, the complete VFS/game/version writable runs,
all 598 function bindings, and the identical set of 3140 code HIGHLOW sites.
It keeps all 100 import identities, DLL order and named hints; 23 IAT slots
remain displaced. Native `.data` VS `0x173f81c` and `.reloc` VS `0xc870`
remain unchanged, against reference `0x174059c/0x10374`. Both files retain
3499 live HIGHLOW entries. Raw `.text`/`.rdata`/`.data`/`.reloc` differences
are 2748/1274/1817/118, versus 2773/1274/1839/158 in the baseline.
The file remains 16384 bytes short and unequal. The single-table control
instead grows `.data` VS naturally by 32 and worsens many later operands;
fewer displaced relocation sites alone is insufficient.

**Reject the dummy-code control** despite its lower aggregate count. It
retains `___init_dummy` at `0x1001e8b4`, moves later code, changes actual
code HIGHLOW positions and fails the full-code audit. This dummy is stock
code, but it is not present at that position in the reference. Stock archive
bytes are never patched to remove it.

Further native controls, all unpromoted:

| Input/retention control | Overlapping differences | Result |
|---|---:|---|
| Untouched extracted `setlocal.obj` directly before LIBCMT | 6788 | Private data enters source-input order too early; 90 displaced sites |
| Same object directly after LIBCMT | 6788 | Same wrong data placement and 90 displaced sites |
| Baseline `/VERBOSE:LIB` | 6323 | Library paths only; no loaded-member trace |
| Discarded selectany dummy pointer, object last | 6336 | No placement repair |
| Same dependency object first | 6335 | No placement repair |
| Dependency object with the three data anchors | 6236 | Same outcome as three anchors alone; helper adds nothing |

The direct-object and dependency controls retain 598 function bindings,
3140 code HIGHLOW sites and zero unmasked code changes. They do not
justify introducing dead source tables, artificial storage or a special
CRT build. The candidate requires only the three native data anchors;
section 36 records canonical promotion and final verification.

Evidence: `.scratch/native-crt-data-order/{probe.py,controls.json,
cmisc-full-value.json,setlocal-full-value.json,*-argv.json,*-includes.rsp,
*-link.log,*-audit.json,*-values.json,whole-object-controls.json,
dependency-controls.json}` and `.scratch/native-early-bss/full-gates.json`.
Each diagnostic is an ordinary LINK output; no object, archive, linked byte
or reference is modified. Alternate output names retain the documented
diagnostic LNK4070 warning; the production output remains `server.dll`.

## 35. Early BSS ordering fixes known owners but shifts the remaining allocation

C-shapes section 218 tests 12 selectany zero definitions in seven whole
source objects, plus the existing empty-string COMDAT in ORDER. This tests
real storage; it adds no padding declaration, larger array or synthetic owner.
Every native link preserves the same code and readonly guarantees as section
34, including the complete VFS/game/version writable runs.

| BSS control | Overlapping differences | Raw `.text` | Raw `.data` | Raw `.reloc` | Native `.data` VS |
|---|---:|---:|---:|---:|---|
| Attributes only, original ORDER | 6323 | 2773 | 1839 | 158 | `0x173f81c` |
| Early 13-owner ORDER group | 6693 | 3151 | 1831 | 158 | `0x173f83c` |
| Early group plus section 34's three CRT anchors | 6606 | 3126 | 1809 | 118 | `0x173f83c` |

Both ordered controls have 13 exact MAP bindings spanning
`0x10034610..0x10034643`, all 81 code operands into that run exact, and
the two zutil initializer targets at `0x100294dc/0x100294f8` exact.
All 12 complete code sections retain their original 5008-byte code shape.
The `.rdata` difference count remains 1274. Live entries remain 3499 each,
with missing/extra sites 79 for the early group and 76 with the CRT anchors;
all are outside code. The whole-file length gap remains 16384 bytes.

The measured 32-byte VirtualSize increase is native alignment after owner
movement, not an added 32-byte declaration. Moving a small owner to its
correct address can worsen hundreds of later address bytes when the rest
of allocation remains unresolved. Neither ordered BSS control is promoted;
production BSS and its source ordering remain as in section 33.

The first existing ordered COMMON is **`g_sequence_counter`**, reference
`0x10035408`, followed by `g_dynamic_count` at `0x1003540c`. It is not
the CRT stream count. Original-order native bindings are
`0x10034610/0x10034614`. The early correct 52-byte run does not establish
the owners between its end and `0x10035408`. Likewise the reference region
between `g_save_extra_field`'s 32 bytes at `0x10035478` and the game clock
at `0x10035880` contains independently anchored ordinary stock CRT BSS;
it cannot be repaired by extending the save field. Three prior mixed game
BSS compositions also remain unresolved. Keep those evidence boundaries
when continuing native allocation work.

Evidence: `.scratch/native-early-bss/{checks.json,shapes.json,link.py,
controls.json,check_values.py,full-gates.json,*.order,*-argv.json,
*-audit.json,*-check_values.stdout}`. The independent value checker
requires symbol and operand bindings as well as zero values. C-shapes
section 219 documents why suffixing BSS alone does not solve this ordering.

## 36. Canonical promotion of the three stock-data anchors

Canonical native rebuild (2026-10-01) changes only
`layout/server.dll/native-archive-includes.rsp`: append the three anchors
from section 34 immediately after `__except_handler3`. No BSS experiment,
extracted library object or dependency helper enters production. CMake
regenerates its normal flags and relinks unchanged source objects with
untouched stock libraries. The canonical build emits no duplicate-symbol
warning and keeps the original output/export filename.

The canonical file has **6235 overlapping differing bytes**, down 88 from
section 33's 6323. The diagnostic had 6236; its raw `.text`, `.data` and
`.reloc` are identical to canonical, and its readonly differences are only
the actual export timestamp bytes at RVAs `0x26e34/0x26e35`. Native
timestamps and checksum remain in the strict comparison. Do not attribute
the one-byte diagnostic/canonical count difference to another layout repair.

Canonical SHA-256:
`845bb9458d04004ef295893c7faf1ff6bef1ebc8d529c1980979e74845136d1e`.
Stored/computed checksum is `0x4db00`, `e_lfanew` is `0xf0`, and Rich
input counts are unchanged. All 598 function bindings and 3140 actual code
HIGHLOW sites remain identical to the established native code baseline,
with zero unmasked raw-code changes. All 24 stock conversion-table bytes
at `0x10033bb0` and its nine code operands match. All 9320 readonly bytes,
54 readonly game values, the complete 85-byte VFS run, 16872-byte game
writable run, 12-byte zlib version owner and seven shared zero/one code
operands pass their independent checks.

Function verification: **262/262**, 22 EXACT and 240 RELOC, no failures
or size divergences. Data verification remains 527 matched, 70 mismatched,
seven missing and four unchecked (608 total, 604 compared). The managed
CLI writes these measured verdicts using `--raw-link`; coverage regenerates
after completed verification. Lint: zero errors, 52 warnings, 4122 passed.
Native build-check: 192 objects, zero drift, current object dependencies.

The updated storage audit includes the complete unique initializer of hidden
`setlocal.obj`: 124 MAP-visible stock members plus that additional member,
at least 125 physical stock inputs. It does not infer the private 12-byte
BSS base from zeros. All 3132 COFF-anchored code operand sites are inspected;
the eight previously listed unanchored actual code sites remain explicit.
The three mixed game BSS composition conflicts are unchanged. This corrects
the scratch census's MAP-only assumption; it establishes no new deficit in
Rebrew's archive indexing or CLI, so no speculative tool feature is added.

Remaining strict failures are unchanged in scope: `.data` VirtualSize
deficit 3456 bytes, `.reloc` VirtualSize deficit 15108, 76 missing/extra
live relocation sites outside code, 23 displaced IAT slots and header
differences. The native file is 270336 bytes versus reference 286720:
**16384 bytes short, whole-file equality false**. Both the CLI whole-binary
gate and the independent objective check exit unsuccessful; the active
whole-file goal remains incomplete. The configured reference remains
unchanged while its provenance question is pending.

Evidence: `.scratch/native-crt-data-order/{canonical-build.log,
canonical-audit.py,canonical-audit.json,canonical-full-verify.json,
canonical-lint.json,canonical-build-check.json,canonical-gates.json,
canonical-readonly.txt,canonical-game-writable.json,canonical-version.json,
canonical-pool-users.stdout,check_table.py,canonical-cmisc-table.json,
canonical-vs-diagnostic.json,canonical-objective.txt,canonical-coverage.json,
storage-audit.py,audit.json,operands.json}`. All new measured source and
linker patterns, including rejected controls, are recorded in C-shapes
218–220 and linker-layout 34–36.

## 37. Ordinary stock data cannot be placed with native ORDER

C-shapes section 221's two whole-project controls rule out ORDER as a
placement mechanism for the ordinary initialized conversion, ctype and
locale data. Correctly decorated public names produce native LNK4065;
the private locale-cache name produces LNK4037. LINK ignores every added
entry. Raw code, initialized data and relocation sections remain entirely
identical to section 36's canonical build, including all operand values;
only the current native export timestamp differs in readonly bytes.
Geometry, function bindings, imports and remaining strict failures are
unchanged. No new native source or link directive is promoted.

This extends the earlier ordinary-BSS observation to initialized-data
contributions. COMMON and COMDAT ORDER results cannot be applied to an
ordinary section merely because one of its public symbols appears in MAP.
The hidden 267-byte locale cache still needs correct input/contribution
selection order. Evidence: `.scratch/native-ordinary-data-order/`;
`versus-canonical.json` compares every raw byte in all four sections.

## 38. A native LIB-generated EXP keeps its own export timestamp through LINK

Section 29 observes equal COFF/export timestamps under the canonical
single-LINK `/DEF` recipe. They can be produced independently using a
different, entirely native two-stage recipe. Plain SP5 LIB 6.00.8447 accepts
the project's unchanged DEF directly:

```text
rebrew-cmake-lib /nologo /MACHINE:IX86 /DEF:<src/server.def> /OUT:<scratch/server.lib>
```

It emits both the import library and `server.exp`. The untouched native
EXP contains `.edata` (81 bytes, flags `0x40000040`), `.debug$S`
(143 bytes, `0x42100040`) and `.drectve` (22 bytes, `0xa00`). Its export
directory timestamp is `0x6abe6ef8`. Link the canonical native inputs,
remove only `/DEF` and diagnostic `/PDB`, and add this complete EXP file.
The resulting COFF timestamp is `0x6abe6f2e`, while the final export
timestamp remains **`0x6abe6ef8`**. LINK preserves the EXP's export stamp
and computes its own PE COFF stamp; it does not rewrite the input EXP.
SHA-256 of that unchanged input:
`8f930730d47b0e4675869c5a25caf9097df2af54bf8a75ea3658be516097614f`.

The diagnostic retains all 598 function bindings, identical 3140 code
HIGHLOW sites, zero unmasked code changes, unchanged section geometry,
3499 live relocation entries and 76 displaced sites outside code.
It keeps the same 100 imports/DLL order/hints and 23 displaced IAT slots.
Raw section difference counts remain 2748/1274/1817/118; overlapping file
differences are 6236 with the unchanged 16384-byte length gap. Rich input
counts also remain unchanged. The alternate DLL filename causes the same
diagnostic LNK4070 `/OUT:server.dll` warning documented previously.

This establishes that unequal native COFF/export timestamps are possible.
It does not contradict the separately measured 285 header-byte differences
between the configured reference and matching distribution copies, and does
not solve their missing Rich header or debug-stripped bit. Neither this
current-time EXP nor a source timestamp constant is promoted. A subsequent
clock experiment tests whether both desired stamps can be generated
reproducibly by the native tools, without editing input or output bytes.

Harness correction: unquoted `/?` was expanded by the host shell and made
LIB try to open `Z:\\`; quoted `/?` prints its native usage successfully
(native help exit status 76). This was not a CMake bridge path defect.

Evidence: `.scratch/native-export-exp/{lib.log,server.exp,server.lib,
link.py,explicit-exp-argv.json,explicit-exp-link.log,
explicit-exp-audit.json,control.json}`. All LIB/LINK executions use Docker
and the unchanged stock SP5 tools. The production build remains section 36.

## 39. Native clock control needs both ELF clock ABIs; frozen LIB and LINK repeat exactly

The first clock controls used Debian libfaketime 0.9.10-2.1 in a derived
SP5 image, keeping Wine 8.0 and every native tool/archive byte unchanged.
Both preloads (`libfaketimeMT.so.1`, then `libfaketime.so.1`) stalled before
LIB executed. The MT run had one 32-bit Wine process, zero CPU activity,
`futex_wait`, and no child tool output; it was terminated. The non-MT run
hit its explicit 45-second limit and the existing bridge killed its named
container. A frozen 64-bit `/bin/date` alone was insufficient evidence.
No result from either stalled LIB invocation was accepted.

The upstream [32-bit time64 issue](https://github.com/wolfcw/libfaketime/issues/418)
made an ABI mismatch a plausible explanation, not a proven local root cause.
Pinned upstream **0.9.13**, commit
`86b37fde2fed7336ea2d0c17928e3015a55d9b4a`, supplies the necessary
[clock wrappers](https://github.com/wolfcw/libfaketime/blob/86b37fde2fed7336ea2d0c17928e3015a55d9b4a/src/libfaketime.c).
Its complete downloaded source archive has SHA-256
`d98aa7beeb21344b3612f60cbfe08196541a2ef25525b3774b11871493a4726e`.
Build the normal library twice, `gcc` and `gcc -m32`. The loader expands
literal `$LIB` separately for the 64-bit Wine launcher and 32-bit Wine.
Keep wall time fixed, monotonic time and file metadata real:

```text
TZ=UTC
LD_PRELOAD=/usr/$LIB/faketime/libfaketime.so.1
FAKETIME_FMT=%s
FAKETIME=<decimal seconds>
FAKETIME_DONT_FAKE_MONOTONIC=1
NO_FAKE_STAT=1
```

The normal and `-DFAKE_STATELESS` 0.9.13 controls both pass 32-bit Linux
programs using time32 and time64: `clock_gettime`, `gettimeofday`, and
`time` report **1071482016**, while monotonic time advances. Both native
LIB controls then finish and produce export timestamp **`0x3fdd84a0`**.
The normal build suffices; the stateless variant is not needed in production.
Different scratch output names explain the distinct EXP hashes.

Using the normal native EXP unchanged, two full-project LINK runs at
**1771046057** both emit COFF timestamp **`0x699004a9`**, preserve export
stamp **`0x3fdd84a0`**, and produce identical full-file SHA-256:
`b80c45a32235a45be89f34c58b4d94a0819b355d3d7b015c0fe45e2026994904`.
Input EXP SHA-256 stays
`604f49dca75701d7ededa9684cbd8f1cc06cb77c8e0ddc6475d019e815921176`.
LINK computes its own valid checksum, stored/computed **`0x46428`**.
There is no binary or archive edit between phases.

The full native audit preserves all 598 function bindings, identical 3140
code HIGHLOW sites, zero unmasked raw-code changes, all section geometry,
100 import identities/hints/DLL order and the existing 23 displaced IAT
slots. Live relocations remain 3499 each, with 76 missing/extra sites outside
code. Raw differences are 2748 `.text`, **1270** `.rdata`, 1817 `.data`,
118 `.reloc`; the four export-stamp bytes now match. The diagnostic has
**6232 overlapping differences** and the unchanged **16384-byte** length
gap. Whole-file equality remains false. Clock control solves timestamps;
it supplies no missing data owner, section extent or Rich-header provenance.

Native CL/LINK/LIB and LIBCMT hashes agree between stock and derived images:
`1bf99f206271ecdbd13da2829192ea2c02e2a44c740b8d72935d5d9cb753b156`,
`9672e578fdfaa43bdb8e9c16071682988665cb90bba2904bf02f6a5576d8ffbc`,
`0a7105543f85cc4f78b7aa7bc0a4b4b3c90f410ed2706af643dececde6232ce3`,
`28b9f04962378ec4668072f37d7fd2835cd6cacc17b40cf22002c57bd8e76714`.

Evidence: `.scratch/native-export-exp/{clock-mt.py,clock-mt.stdout,
clock.py,clock.stdout,frozen-hang-maps.txt,frozen-hang-processes.txt,
Dockerfile.clock-v13,clock-v13-build.log,clock-api.c,clock-v13.py,
clock-v13-controls.json,clock-v13-link.py,clock-v13-link-controls.json,
clock-v13-audit.json,clock-stock-hashes.txt,clock-v13-stock-hashes.txt}`.
All probe processes are terminal. Production integration uses the standard
SOURCE_DATE_EPOCH knob and a native two-phase CMake recipe; its final
checks are recorded separately below.

## 40. Canonical native timestamp recipe and base-dependency repair

Promoted the proven two-stage recipe through the normal build. CMake reads
both stamps from the unchanged configured reference using
`scripts/native_timestamps.py`; it never changes the reference. Native LIB
creates `build/native-export/server.exp` from the existing DEF at epoch
1071482016. Native LINK consumes that whole EXP, at epoch 1771046057,
instead of generating a new export directory through `/DEF`. The canonical
output name remains `server.dll`, with no alternate-name LNK4070 or
duplicate-symbol warning. No source object, archive, EXP or final DLL is
patched. The existing three stock data anchors and all source shapes remain.

The missing native build-clock support is fixed in sibling Rebrew:
`config.source_date_epoch` validates the standard environment variable,
`cmake_tc` routes dated CL/LIB/LINK invocations through the image clock,
and `toolchain.run_toolchain` forwards it to the normal local backend.
Both object-cache schema 7 and verification configuration hash include it.
The sibling toolchains base supplies the pinned 0.9.13 libraries and a small
clock helper. Wine clocks support 0..2147483647 seconds; unsupported values
or missing libraries fail before the native tool. Normal undated invocations
keep their existing runner path. Complete upstream source and GPLv2 COPYING
ship with the clock libraries; compiler/archive hashes remain unchanged.

A second real tooling deficit was exposed by this integration: generated
Dockerfiles declare `ARG BASE_IMAGE=rebrew/base:1.0` then
`FROM ${BASE_IMAGE}`. `rebrew toolchain build` previously read that variable
literally, skipped its local base dependency, and could use a stale base or
fail on a clean daemon. The CLI now resolves declared ARG defaults before
the first FROM, and builds the corresponding base directory. It also fixes
the previous hardcoded `base/` directory for `rebrew/base-noble:1.0`.
Two behavioral tests execute the build command with recorded builders and
require the correct base before the profile. No general Dockerfile parser
or new build configuration is introduced.

Canonical **SHA-256** is
`b80c45a32235a45be89f34c58b4d94a0819b355d3d7b015c0fe45e2026994904`,
identical to both prior clocked full-link controls. **6232 overlapping
file differences**, down three from section 36's canonical 6235;
**16384 bytes short**, 270336 versus 286720. COFF stamp `0x699004a9`
and export stamp `0x3fdd84a0` both match. Native stored/computed checksum
is `0x46428`, `e_lfanew` stays `0xf0`. Timestamp and checksum bytes remain
inside the strict comparison; they are not masked out of these counts.

Regenerating the EXP with the normal `rebrew-cmake-lib` command produces
exactly the same input bytes, SHA-256
`8b880bae9a4d8220fe229f3e074a296ae67dbf2bef2e5ebb5598d330496c5d15`.
Executing CMake's actual `cmake_link_script` again produces exactly the same
entire DLL. Both phases finish successfully; this is an executed native
repeat, not an unchanged-target/no-op build. The EXP's 136-byte `.debug$S` differs from the scratch control's 157-byte
section, which records its other output path. Both full 81-byte `.edata` and
22-byte `.drectve` sections, flags and COFF stamps agree; see
`exp-path-control.json`. The current non-debug link emits the same full DLL.

All 598 function bindings and 3140 actual code HIGHLOW sites remain fixed,
with zero raw-code differences outside those fields. Section sizes, Rich
input counts, 100 import identities/hints/DLL order, 23 displaced IAT slots,
3499 live relocations and 76 missing/extra sites outside code are unchanged.
Full readonly 9320 bytes/54 game values, VFS 85 bytes, game writable 16872
bytes, version 12 bytes, seven shared zero/one operands, stock conversion
table 24 bytes and all nine of its code operands pass separate executable
checks. All native compiler and stock archive hashes match their pre-clock
values.

Function verification is **262/262**, 22 EXACT and 240 RELOC, zero failures
or size divergences. Data remains 527 matched, 70 mismatched, seven missing
and four unchecked. Lint: zero errors, 52 warnings, 4122 passed. Native
build-check: 192 source objects, no flag drift, current dependencies.
Relevant Rebrew tests: **651 passed**; Ruff, mypy and cycle/layering checks
pass. Toolchain contracts: **29 passed**; wrapper harness ALL-PASS,
ShellCheck clean. Configuration tracks the reference path, and EXP generation
tracks the reference, reader, config and DEF. A dependency-aware native rebuild
emits exactly the same full-file hash. Coverage regenerates after completed
verification. CLI whole-binary and
independent whole-file checks still exit 1: `.data` VirtualSize deficit
3456, `.reloc` deficit 15108, displaced non-code fixups/IAT slots and
remaining headers prevent equality. The whole-file goal remains active
and incomplete; the configured reference/provenance choice stays pending.
The inherited twentieth `border` DWORD remains an unresolved original owner.

Evidence: `.scratch/native-export-exp/{canonical-clock-build.log,canonical-clock-dependencies-build.log,
exp-path-control.json,canonical-clock-audit.py,canonical-clock-audit.json,
canonical-clock-verify.json,canonical-clock-lint.json,
canonical-clock-build-check.json,canonical-clock-gates.json,
canonical-clock-repeat.json,canonical-clock-repeat-lib.log,
canonical-clock-repeat-link.log,canonical-clock-stock-hashes.txt,
canonical-clock-objective.txt,canonical-clock-coverage.json,
base-clock-final2-build.log,toolchain-clock-final-build.log,
rebrew-clock-complete-tests.txt,rebrew-clock-ruff.txt,
rebrew-clock-mypy.txt,rebrew-clock-build-mypy.txt,
rebrew-clock-boundaries.txt,clock-wrapper-tests.txt,
clock-shellcheck.txt,clock-toolchain-contracts.txt}`. Every measured new
source/linker pattern, including failed controls and harness corrections,
is documented in C-shapes 221–222 and linker-layout 37–40.

## 41. Five true late COMMON owners fit the existing connection/allocator interval

The existing nine connection slots occupy `0x1585584` bytes. At the
reference base `0x101deb00` their end is exactly `0x11764084`, the first
late server scalar. The reference order is max_players, tick_rate,
chain_id_start, players_synced, thread_handle, at offsets 0/4/8/12/16.
The current ordinary source BSS groups could not express that geometry:
server.c grouped the thread handle beside an early handler flag, and
ServerMainThread.c grouped players_synced immediately after tick_rate.

C-shapes 224 proves the five existing declarations can become COMMON with
all 2624 CODE bytes and 184 named fixups unchanged. Native ORDER inserts
their names after g_connections and before g_alloc_root. The resulting
five native bindings at `0x11762e84..94` have the exact relative offsets
and fit the existing interval before the allocator at `0x11762ea0`.
Both the connection and allocator bindings remain fixed. These addresses
are still `0x1200` before reference; missing earlier composition remains
unresolved. No array is enlarged and no alignment gap is materialized.

| Native control | Overlapping differences | Raw `.text` differences | `.data` VS |
|---|---:|---:|---|
| Previous canonical | 6232 | 2748 | `0x173f81c` |
| Thread COMMON only | 6232 | 2748 | `0x173f81c` |
| Main-thread fields and chain COMMON | 6202 | 2718 | `0x173f81c` |
| All five COMMON, reference order | 6198 | 2714 | `0x173f81c` |

All controls preserve 598 function bindings, zero unmasked raw-code
changes, 3140 identical code HIGHLOW sites, 3499 live HIGHLOW entries,
100 import identities/DLL order/hints, and the complete readonly,
VFS/game/version/stock-table value gates. The 23 displaced IAT slots and
76 missing/extra non-code relocation sites remain. Other raw differences
remain `.rdata` 1270, `.data` 1817, `.reloc` 118. Across the combined
link, 245 actual code operands change: 21 name the five moved fields;
the remainder reflect native ordinary-BSS movement. The byte-distance
changes are 38 improved fields, four worsened, 203 unchanged. None of the
four worsened CRT operands was an exact reference address before the
change. Full compiler contributions and live-code relocation topology
stay protected; the smaller total alone is not the ownership proof.

Canonical CMake rebuild reproduces the entire combined DLL, SHA-256
`1b773c6500f289990bf2638008dc162f4f6179479dc37ccb2ee7dd6873b89c9d`.
Native stored/computed checksum is `0x51f23`; both previously fixed native
COFF/export timestamps still match. All section extents remain unchanged.
The file is still **16384 bytes short**, 270336 versus 286720, with
**6198 overlapping differences**. `.data` VS deficit 3456 and `.reloc`
VS deficit 15108 remain. CLI whole-binary and independent strict file
checks correctly fail; the whole-file goal remains active/incomplete.

Canonical verification: **262/262**, 22 EXACT/240 RELOC, no failures or
size divergences. Stored data: **528 matched, 70 mismatched, seven missing,
three unchecked** (608 total/605 compared). Zero data values do not prove
the five globals' absolute bindings; their exact native/reference deltas
are checked independently. Full readonly 9320 bytes/54 values, VFS 85
bytes, game writable 16872 bytes, version 12 bytes, seven shared pool
operands, conversion table 24 bytes/nine operands all pass. All three
targets retain zero lint errors/warnings; native build-check reports
192 source objects and zero flag drift.

The fresh storage audit inspects 3132 actual COFF-anchored code sites,
192 source objects and 125 stock members (124 MAP-visible plus the
full-content-validated private setlocal.obj). The generated native EXP
is a separate linker input, not a C source object; the audit excludes it
from that source count. Only gm_Open.c's ordinary BSS remains internally
inconsistent. Hidden locale placement and the original early-BSS region
remain unresolved. No prior rejected early-BSS control is promoted here.

Desktop IDA export cross-check: it declares `dword_10035408` initialized
to 1204388073, but that VA is in the configured reference's virtual zero
tail beyond `.data`'s raw end at `0x10035000`. That weak exported initializer
is not evidence for native initial bytes. Its two-DWORD grouping at
`0x10034670` likewise does not establish a second live stream-pool field:
the matched allocator accesses the head through its first pointer only.
The unproved `0x10034674` owner is not created or appended to the pool.

Evidence: `.scratch/native-late-bss/{probe.py,controls.json,checks.json,
shapes.json,changed-operands.json,canonical-late-bindings.json,
canonical-clock-audit.json,canonical-build.log,canonical-verify.json,
canonical-lint.json,canonical-build-check.json,canonical-gates.json,
canonical-objective.txt,storage-audit.py,audit.json,operands.json,
ida-bss-control.json}` and the thread/main-chain/combined native link logs.

## 42. Native ORDER restores the stock CRT COMMON tail's relative geometry

The actual stock COMMON definitions and matched CODE/validated initializer
operands identify 28 live globals after the game's log-file handle. Sorting
these proven reference bindings and appending their names to the existing
native ORDER file reproduces their complete relative layout. This operates
on stock LIBCMT; no CRT function/data definition, extracted-object edit,
archive edit or extra retention directive is introduced.

Only MAP-visible `<common>` symbols with one unambiguous reference binding
and exclusively stock COMMON definitions qualify. __FPinit is deliberately
excluded: despite an archive's COMMON declaration, its live native definition
is initialized data at the already-correct 0x100317d8. The eight-symbol
allocator ownership repair is the separate source change in C-shapes 226.

The 28 native stock bindings now all have exactly **-0x1200** displacement,
matching the preceding game's COMMON displacement. This fixes their relative
order and natural alignment, not their absolute addresses. Examples:

| COFF symbol | Bytes | Reference VA | New native VA |
|---|---:|---|---|
| ___mbcodepage | 4 | 0x11766208 | 0x11765008 |
| ___mbulinfo | 12 | 0x11766210 | 0x11765010 |
| __mbcasemap | 256 | 0x11766220 | 0x11765020 |
| __mbctype | 257 | 0x11766320 | 0x11765120 |
| ___setlc_active | 4 | 0x11766428 | 0x11765228 |
| ___pioinfo | 256 | 0x11766460 | 0x11765260 |
| __bufin | 4096 | 0x11766580 | 0x11765380 |
| ___onexitbegin | 4 | 0x11767598 | 0x11766398 |

The complete 28-symbol ownership/size/operand-vote list is in symbols.json;
bindings.json records every old/new/reference VA. Common sizes are sizes,
not section offsets. Native ORDER removes one x86 decoration underscore,
as established earlier. No missing symbol is retained just to enlarge a
section. Both full 256-byte tables, the 257-byte table and 4096-byte buffer
are existing stock storage, not new declarations or manual padding.

| Native control | Overlapping differences | Raw `.text` | Raw `.data` | `.data` VS |
|---|---:|---:|---:|---|
| Prior canonical | 6198 | 2714 | 1817 | 0x173f81c |
| Allocator block ownership alone | 6198 | 2714 | 1817 | 0x173f81c |
| Stock COMMON order alone | 5991 | 2509 | 1815 | 0x173f7fc |
| Combined, promoted | 5991 | 2509 | 1815 | 0x173f7fc |

The ordinary BSS contributions now follow the ordered tail. Their movement
does not fix their earlier reference placement. Native alignment shrinks
.data VirtualSize by 32 bytes, increasing its remaining deficit to **3488**;
no source storage is deleted to obtain that change. Raw `.rdata` differences
remain 1270; raw `.reloc` differences remain 118. Whole-file length remains
**270336 versus 286720**, 16384 bytes short. Across the canonical change,
478 actual CODE operands move: 222 improve in byte distance, 17 worsen,
239 have the same distance, net **205 fewer CODE differing bytes**. No
previously exact CODE operand loses its reference binding. The other two
bytes of aggregate improvement are in initialized data; a lower score alone
is not the evidence for the stock COMMON layout.

Canonical CMake produces the same entire DLL as the combined diagnostic,
SHA-256 **45a27ccdc52cb4460b539ae1eeeb59c1e8875b48f09b458db531a87f6b87bffb**.
Stored/computed checksum is 0x50276. Native COFF/export timestamps still
match 0x699004a9 and 0x3fdd84a0. All 598 function bindings, 3140 identical
CODE HIGHLOW sites, zero unmasked raw-code differences, and 3499 live
relocations each remain protected. Missing/extra non-CODE sites remain 76
each. All 100 import identities, DLL order and hints remain; 23 IAT slots
are still displaced. No duplicate-symbol or linker warning is emitted.

Verification: **262/262**, 22 EXACT/240 RELOC, zero function failures or
size divergences. Data: **529 matched, 69 mismatched, seven missing, three
unchecked**, 608 total/605 compared. Complete readonly 9320 bytes/54 game
values, VFS 85 bytes, game writable 16872 bytes, version 12 bytes, seven
shared pool operands and conversion table 24 bytes/nine operands pass.
All three targets still lint with 4122 passed/zero errors/zero warnings;
build-check has 192 objects/zero drift. CLI whole-binary and independent
strict objective checks both correctly exit 1. Coverage is regenerated
after terminal verification. The whole-file objective remains incomplete.

Fresh source/stock audit covers 192 C objects, 125 physical stock members
and 3132 COFF-anchored CODE sites. The allocator's eight anchors now agree
on one reference base. gm_Open's remaining 12-byte group has two implied
bases, so its unproved pool-to-count word is still not created. The early
0x10034684..0x10035408 owner, ordinary CRT BSS placement, private setlocal
initializer, import slots and relocation/header geometry remain work.
For ordinary stock BSS alignment, decode the actual COFF alignment field:
0xc0400080 denotes **eight-byte** alignment (time/mlock/tzset/gmtime), not
sixteen. Their reference bases such as 0x10035538 satisfy that requirement.

Evidence: `.scratch/native-crt-common-order/{probe.py,symbols.json,
bindings.json,link.argv.json,link.log,changed-operands.json,
changed-summary.json,canonical-code.json,canonical-clock-audit.json,
canonical-build.log,canonical-verify.json,canonical-lint.json,
canonical-build-check.json,canonical-gates.json,canonical-objective.txt,
canonical-coverage.json,storage-audit.py,audit.json,operands.json}`;
allocator ownership controls and rejected six-field controls are documented
in C-shapes 225–226. No new Rebrew tooling deficit was exposed by these
controls; existing fixes and concurrent sibling edits are preserved.

## 43. One stock COMMON root restores the full 1140-byte CRT initialized prefix

C-shapes 227's three native COMMON-root controls all produce the same DLL.
Promote only **/INCLUDE:___setlc_active** immediately after __cfltcvt_tab in
native-archive-includes.rsp. The original stock member is selected earlier;
its unused code remains discarded. The canonical CMake recipe, stock
archives, native EXP and compiler/source inputs otherwise stay unchanged.
There is no local CRT definition or postlink operation for this placement.

The full initialized run **0x10033ba0..0x10034013**, 1140 bytes, now equals
the configured reference byte for byte, including all live pointer fields
and the linker's natural alignment gaps. Its ordinary stock contributions:

| Member | Section bytes | Reference and native base |
|---|---:|---|
| exsup.obj | 16 | 0x10033ba0 |
| cmiscdat.obj | 24 | 0x10033bb0 |
| setlocal.obj private initializer | 267 | 0x10033bc8 |
| ctype.obj | 522 | 0x10033cd4 |
| nlsdata1.obj | 12 | 0x10033ee0 |
| crt0msg.obj private _rterrs | 144 | 0x10033ef0 |
| timeset.obj writable data | 148 | 0x10033f80 |

The direct complete-run checker masks nothing, verifies its writable .data
extent and rejects the previous canonical native DLL. Individual unique
stock initializer/COFF proofs agree with those bases. The private locale
initializer still has no public MAP owner; full content, not a nearest
public label, establishes its location. Ordinary section flags determine
the intervening alignment, including crt0msg's eight-byte alignment after
nlsdata1 ends at 0x10033eec. No four-byte gap declaration is added there.

| Canonical metric | Before root | After root |
|---|---:|---:|
| Overlapping file differences | 5991 | **5320** |
| Raw .text differences | 2509 | 2343 |
| Raw .rdata differences | 1270 | 1270 |
| Raw .data differences | 1815 | 1323 |
| Raw .reloc differences | 118 | 106 |
| Missing/extra live non-CODE sites | 76 each | 55 each |
| .data VirtualSize | 0x173f7fc | 0x173f800 |

The four-byte VS increase is native alignment, not additional source
storage. The remaining .data VS deficit is **3484**. .reloc stays 0xc870
versus reference0x10374, still15108 short. The native file remains
**270336 versus286720**, **16384 bytes short**. The overall reduction is
671 differing bytes;166 are CODE,492 initialized data,12 relocation bytes,
one header byte. No previously exact CODE operand loses its reference
binding; the seven worsened CODE operands were already misplaced. Each
stock COMMON tail binding remains -0x1200, so this does not solve earlier
BSS ownership or the stock ordinary-BSS interleaving.

Canonical native DLL SHA-256
**27d2ff2ab733cdf24957b17719ba561c55d582b2923e14e28fa1bfc29c476c71**
equals every COMMON-root diagnostic's entire file. Native checksum stored
and computed are0x4c4a9; COFF/export stamps remain0x699004a9/0x3fdd84a0.
All598 function bindings and3140 CODE HIGHLOW sites remain unchanged,
with zero unmasked raw-code differences. Both images have3499 live
relocations. All100 imports, DLL order/hints remain;23 IAT slots still
displaced. No linker or duplicate-symbol warning is emitted.

Canonical verify: **262/262**,22EXACT/240RELOC, zero failures or size
divergences. Data **530 matched,68 mismatched,7missing,3unchecked**,
608total605compared. Complete readonly9320B/54values, VFS85B, game
writable16872B, version12B, seven shared pool operands, conversion
table24B/nine operands and the new complete stock prefix1140B all pass.
All three targets lint4122passed/0errors/0warnings; build-check192objects
and zero drift. Whole-binary and independent strict objective checks
correctly exit1; whole-file identity is incomplete. Coverage is regenerated
after terminal verify. Zero-data verdicts still do not prove absolute VAs.

Fresh storage audit retains192Cobjects and125 physical stock members,
3132 COFF-anchored CODE sites, and one gm_Open BSS conflict. The allocator
block and remaining pool-word limits from section42 still apply. The next
misplaced initialized contributions include day/calendar tables, winxfltr,
intrncvt, mbctype, locale-time and lconv. C-shapes228 rejects three initial
data-root controls: a data-symbol request can move already-live CODE, and
a correct single data owner cannot excuse13304 unmasked CODE differences.
The early BSS region, IAT/relocation/header geometry and border's twentieth
DWORD provenance remain unresolved. Configured reference is unchanged.

Evidence: `.scratch/native-locale-common-anchors/{probe.py,controls.json,
changed-operands.json,changed-summary.json,check_prefix.py,
rejected-old-prefix.txt,canonical-build.log,canonical-clock-audit.json,
canonical-verify.json,canonical-lint.json,canonical-build-check.json,
canonical-gates.json,canonical-objective.txt,canonical-coverage.json,
storage-audit.py,audit.json,operands.json}`; the three COMMON-root outputs
and the rejected later-data controls. No new Rebrew implementation defect
was exposed; existing sibling tooling fixes and concurrent edits stay intact.

## 44. Direct stock import objects are not a substitute for this archive selection

Four native controls pass complete, untouched stock WinSock members directly
as inputs, after the normal object list. Each tests reference ordinal order
and its reverse. No library, member, reference or linked file is patched.

| Direct member format | LINK result | Parsed imports | Moved existing functions | Overlapping differences |
|---|---|---:|---:|---:|
| VC6 short, reference order | LNK1213 | No output | N/A | N/A |
| VC6 short, reverse order | LNK1213 | No output | N/A | N/A |
| VC5 full COFF, reference order | Exit0, LNK4089 | 84 | 6 | 13169 |
| VC5 full COFF, reverse order | Exit0, LNK4089 | 84 | 0 | 13162 |

The short-object diagnostic is `unexpected import object encountered`.
The full-COFF controls warn that all references to WS2_32.dll and several
direct input paths were discarded by /OPT:REF. Their output has no WinSock
import descriptor and loses all 16 WinSock imports, despite retaining the
normal stock archives. Its .rdata VS shrinks from0x2e81 to0x2df1. A successful
LINK exit and unchanged function positions in the reverse control cannot
excuse a missing DLL. These controls are rejected, not promoted or repaired
by suppressing warnings. The observations apply to these direct inputs;
they are not a claim about every possible full-COFF import configuration.

Stock archive hashes are unchanged: VC6 WS2_32
`dbe9de991aea6662d8857da13e572729b5379377be8e13bdd86e57a51354988e`,
VC5 WS2_32 `4f7725f9dbfc7bdcc5b087851948319ba9ab85c980a0b8a58068cee714e3e48f`.
Every extracted complete member is compared with its original archive bytes;
the ordinal/name-type distinction is checked before selecting records.

Two other controls remove all16 WinSock retention pragmas, or only the seven
whose function roots already occur in native-archive-includes.rsp. Both
produce the entire canonical DLL byte-for-byte. The present seeds therefore
do not provide a WinSock slot-order control. Actual C object symbol-order
recon finds seven direct function references in broadcast.c.obj and14 import
pointer references in server2.c.obj. Eliminated C address expressions cannot
change their order (C-shapes229–230). No production seed/no-op edit is made.

The canonical artifact remains SHA256
`27d2ff2ab733cdf24957b17719ba561c55d582b2923e14e28fa1bfc29c476c71`,
**5320 overlapping differences and16384 bytes short**. Fresh three-target
lint has4122passed/0errors/0warnings each. The strict file objective remains
incomplete. No new Rebrew defect is implied by native LINK rejecting these
inputs or by its successful-but-incomplete import result.

Correction to C-shapes228: winxfltr.obj has two CODE COMDATs of318/58 bytes,
both flags0x60101020. Neither function name appears in the canonical or
exception-table-control MAP; a full-contribution search, masking only their
COFF relocation fields, finds neither body in either DLL or the reference.
That data root reorders other live CODE; the earlier description that its
own CODE was live was too strong. The exact dependency responsible is still
unresolved, so do not infer it from the constant598 function-label count.

Evidence: `.scratch/native-import-inputs/{probe.py,controls.json,
filter-discarded-code.json,canonical-lint.json}`, short/direct and full/direct
member files, exact argv, link logs, MAPs and DLLs;
`.scratch/native-import-seeds/{probe.py,controls.json,ws2-symbol-order.json}`;
`.scratch/native-import-symbols/{probe.py,controls.json}`.

## 45. MAP-visible archive members are a lower bound on actual loaded members

Native LINK6 `/VERBOSE:LIB` prints library searches at this checkpoint;
plain `/VERBOSE` also prints the actual found symbol, referencing object,
loaded member, discarded COMDATs and pass-two object list. Both diagnostic
links preserve the **entire canonical DLL byte-for-byte**. The full trace
therefore describes the same build, not a different debug-layout control.

The trace loads **138 unique LIBCMT members**. The prior storage audit's
125 members were124 MAP-visible owners plus the completely validated
private setlocal initializer. That was an inspected subset, not a complete
physical-member census. Thirteen further loaded members lack that prior
MAP/content anchor: a_loc, chr, getqloc, initcoll, initctyp, inithelp,
initmon, initnum, mbsdup, w_loc, w_str, winsig and xtoa.

Nine of those contain **100 bytes of private ordinary BSS**: a_loc4,
getqloc36, initctyp8, inithelp8, initmon4, initnum12, w_loc4, w_str4 and
winsig20. Their sections all have flags0xc0300080. The other four have
no ordinary writable contribution. Loading is not proof of a retained
section's absolute address; none of these nine sections has an established
native/reference binding in this audit. Do not allocate replacement storage
or use zero-byte searches to invent their positions. In particular, these
members are already selected, so forcing their CODE to obtain a supposedly
missing library member is the wrong next action.

The corrected audit inspects all138 loaded members and still accounts
**3132 of3140 CODE HIGHLOW sites**,192 source objects, eight unanchored
thunk/unwind sites,21 absolute-zero __except_list fields, and one game
section-binding conflict. The13 extra members add no anchored CODE sites.
Only setlocal is reported as an additional member validated by complete
initializer content; the13 trace-selected members are reported separately.
Earlier references to125 physical members should be read as that prior
inspected subset. No new native bytes are introduced by correcting the audit.

The full trace also explicitly discards both winxfltr CODE COMDATs, supporting
the correction in section44. It records all16 WinSock member selections;
their extraction sequence differs from the emitted IAT sequence. This rules
out equating archive load order with IAT order, without asserting a particular
hash or sorting algorithm. Further work must use the actual symbol and member
trace alongside initialized-data/BSS ownership, not the redundant seed order.

Evidence: `.scratch/native-import-seeds/{storage-audit.py,storage-audit.log,
audit.json,operands.json,loaded-member-audit.json,ws2-extraction-order.json}`
and verbose/verbose-all native argv, link logs, DLLs, MAPs and SHA audits.


## 46. Bind the native CMake drivers together; compiler-cache changes can remove objects

A project-local Rebrew installation does not repair hooks previously cached
from a global installation. Native EXP generation also bypassed the selected
archiver by invoking bare `rebrew-cmake-lib` at build time. The generated
Rebrew toolchain now resolves CL on PATH at configuration and binds LINK/LIB
to that same installation directory; the project's EXP rule uses CMAKE_AR.
A real CMake script test confirms the three absolute paths survive a later
PATH change and a missing CL produces a clear configuration error. The lookup
preserves the project's CMake3.15 minimum.

Changing CMAKE_C_COMPILER in the live cache caused CMake to reset compiler
state and remove CMakeFiles, including192 existing native objects, before
trying the compiler again. The retry then failed under restricted cache and
Docker access. The DLL/MAP/EXP were preserved, but restoring CMakeCache did
not recover the removed COFF files. Recovery used a separate forced-toolchain
configuration, verified unchanged flags/input order/link arguments, and then
regenerated the empty canonical state. Future driver changes should first be
validated in a separate build directory. This is configuration evidence, not
a new native-link or compiler codegen result.

The same failure exposed a Rebrew cleanup defect: the compile/link/lib try
block included response rewriting and cache-lock acquisition, so a failure
before subprocess.run attempted to kill a nonexistent container and warned
that it could still be running. Cleanup now surrounds only subprocess.run,
excludes spawn OSErrors and finishes while the prefix lock is held. Existing
timeout cleanup still passes; response, lock and spawn failure controls make
no kill call. All44 focused CMake tests and Ruff checks pass.

No rebuilt DLL is claimed. The saved DLL remains entire-file SHA256
27d2ff2ab733cdf24957b17719ba561c55d582b2923e14e28fa1bfc29c476c71;
canonical native objects are currently absent and build-check correctly fails.
Evidence: `.scratch/native-project-hooks/`; upstream-source patch against
9123ca68: `docs/rebrew-patches/cmake-drivers.patch`. The project-local wheel
contains the patch; the read-only sibling checkout remains unchanged.

## 47. Native COFF debug output exposes private stock CRT storage

The saved native diagnostic adds `/DEBUG /DEBUGTYPE:COFF /PDB:NONE /OPT:ICF`
to the normal LINK invocation, redirecting its outputs into scratch. It uses
the actual 192 compiler objects, unchanged stock archives and native EXP;
no object, archive or output bytes are rewritten. This control ran before
the later library-marker ordering regression described in entry 48. It is
diagnostic output, not a production candidate.

LIEF reads 2005 symbols from the resulting PE COFF table, including 80 private
writable symbols (storage class STATIC, section 3). These 80 include both
initialized data and BSS. In this LINK output, symbol values are image RVAs:
add the image base, not the section RVA. The COFF debug payload starts at file
offset 270336, and PointerToSymbolTable is 270368. LIEF's generic debug
payload accessor is empty here, but `PE.Binary.symbols` reads the table;
another COFF parser is unnecessary.

All 598 function bindings remain unchanged. All 572 previously anchored
writable symbol bindings agree with the diagnostic, with zero failures.
The diagnostic also supplies unique bases for nine stock ordinary-BSS
contributions whose private names were absent from the ordinary MAP:

| Stock member | Bytes | Native diagnostic base |
| --- | ---: | --- |
| initnum.obj | 12 | 0x11766770 |
| initmon.obj | 4 | 0x1176677c |
| initctyp.obj | 8 | 0x11766780 |
| getqloc.obj | 36 | 0x117667ac |
| winsig.obj | 20 | 0x117667d4 |
| inithelp.obj | 8 | 0x117667e8 |
| w_str.obj | 4 | 0x117667f4 |
| w_loc.obj | 4 | 0x117667f8 |
| a_loc.obj | 4 | 0x117667fc |

These total 100 bytes. Each private symbol offset was checked against the
saved diagnostic's symbol table. These addresses describe this native link;
they do not establish the corresponding addresses in the original binary.
The ordinary CRT contributions still follow the large game COMMON storage.

Debug output changes layout: `.rdata` VirtualSize grows from 0x2e81 to
0x2ed1, and the later CRT readonly lookup strings move by 0x58. `.text` and
`.data` VirtualSizes and every section RVA remain unchanged. Debug directories
contain COFF, MISC and FPO records; the diagnostic SHA256 is
`a8de60f21aa41df77885dcda2aec5159cb63beeb88af7bdecaae291b0e42e00f`.
Do not promote this control or infer original storage geometry from its
private-symbol addresses alone. Evidence: `.scratch/native-coff-debug/`
(`audit.json`, `binding-validation.json`, `hidden-bss.json`, `argv.json`).

## 48. Library attribution must preserve a source's target link position

Changing two zlib server markers from FUNCTION to LIBRARY exposed a Rebrew
ordering defect. `file_va` recognized only FUNCTION. `check_header.c` lost
its only recognized server VA and moved from object index 11 to index 190;
`gzread.c` used its unrelated GOLDTL FUNCTION VA 0x45f380 and moved from
index 13 to index 1. Their C bodies and all 192 per-source flag mappings
were unchanged. The regenerated native DLL grew `.text` by 16 bytes and
had 149199 overlapping byte differences against the reference, versus 5320
before the reorder; both files are 16384 bytes short.

Fixed the shared helper directly in the sibling Rebrew source: it now uses
`parse_c_file_multi` and `FUNCTION_MARKERS`, including FUNCTION, LIBRARY and
STUB while excluding data markers. Target scoping and the existing fallback
for old module names are preserved. This repairs order-sources, link-order
and recommend together. The regression checks a target-scoped LIBRARY
stacked with a foreign FUNCTION, C89 STUB markers and excluded DATA markers.
The 102 focused source-order/link/CMake tests pass, as do Ruff checks.

The project's older installed reader also rejected these valid LIBRARY
markers with E015. Installed the existing sibling lint fix alongside the
ordering repair; its 229 lint tests pass. The project uses a pinned local
wheel, avoiding unrelated concurrent edits in the sibling checkout.
SHA256: `5e19f07c3e7a89d43c99d9cfdb87f7c0543e9975e0b15d3d29e7afa935e28fe6`.
The reproducible additional patch is
`docs/rebrew-patches/library-source-order.patch`; the earlier CMake driver
repair remains included. CMake now invokes the selected project Rebrew
for order-sources and final verification as well as source selection/flags.

The bare global CLI also found W033 because its packaged workflow template
was newer than the pinned project's copy. Included that existing template
update in the wheel and used `rebrew init --refresh-agents` to refresh the
single differing generated skill file. The scaffold check reports zero
drift, and both the project CLI and bare `rebrew lint --all-targets --json`
report zero errors and warnings for all three targets.

An isolated `cmake -P` check executes the project's actual source selection
and ordering block without compiler/linker commands. It reproduces all 192
source inputs in the previous canonical order exactly, including the two
library positions. Final lint for each of three targets is 4122 passed,
zero errors and zero warnings. Evidence: `.scratch/no-docker-source-order/`
and `.scratch/native-access-restored/` (`source-order-tests.log`,
`library-lint-tests.log`, `no-docker-final-lint.json`).

No Docker invocation or native rebuild was performed during this repair.
The current `build/server.dll` remains the regressed native output, SHA256
`074b59125fbfa2466dee844dda7d72f416c43f6cf3937f2f186c13515b05d5d0`.
The earlier native DLL and all 192 original objects are saved under
`.scratch/native-access-restored/`. A fresh configure/build must regenerate
the response file and relink before claiming restored binary agreement.
Do not replace the deliverable with the saved DLL or edit generated ordering
files by hand. This entry documents a tooling/layout defect; no new C codegen
shape was measured.

Follow-up configuration recovery: normal `cmake -S . -B build` with the
existing project compiler cache successfully regenerates the actual build
files without invoking Docker or a compiler/linker. Its full 193-input
response file, including the native EXP, now exactly equals the saved
canonical order. All 192 existing compiler-object SHA256 values and the
compiler-state file are preserved. The DLL itself remains unchanged at the
regressed SHA256 above. Build-check correctly reports STALE OBJECTS after
the tooling/configuration refresh, so a real rebuild is still required;
configuration success does not prove binary agreement. Evidence:
`.scratch/repaired-native-config/{configure.log,audit.json,objects-before.json,
build-check.json}`. The prior statement that the response file still needs
regeneration describes the checkpoint before this follow-up.

Native recovery completed after Docker access was rechecked successfully.
The full 192-object CMake rebuild reproduces the saved baseline DLL exactly,
SHA256 `27d2ff2ab733cdf24957b17719ba561c55d582b2923e14e28fa1bfc29c476c71`.
The ordering regression is resolved in actual toolchain output, not by
restoring a saved DLL. Fresh verification passes all262 functions, including
two library checks, with zero size divergences; data has530 matched,
68 mismatched, seven missing and three unchecked. Build-check checks192
objects with zero drift; all three targets lint cleanly. Whole-file identity
remains false:5320 overlapping differences and16384 missing bytes.
Evidence: `.scratch/repaired-native-config/native-*`.

## 49. A shorter COMMON order lets ordinary CRT BSS precede unordered game storage

The control keeps all75 readonly entries and the24 early game COMMON entries
through g_save_extra_field, removing later game and stock COMMON names from
the scratch ORDER file. It links the unchanged192 real C objects, stock
archives and native EXP. It changes no source, object or archive bytes.

Ordinary CRT BSS now precedes unordered bulk game COMMON storage. Examples
derived from matched CODE or validated initializer operands:

| Owner | Reference base | Control base | Displacement |
| --- | --- | --- | ---: |
| time.obj,24B | 0x10035498 | 0x10034708 | -3472 |
| crt0dat.obj,68B | 0x100354b0 | 0x10034720 | -3472 |
| mlock.obj,96B | 0x10035538 | 0x100347a8 | -3472 |
| stdargv.obj,260B | 0x100355d8 | 0x10034820 | -3512 |
| gmtime.obj,36B | 0x100357a8 | 0x100349f0 | -3512 |
| lconv.obj,1B | 0x10035864 | 0x10034ad8 | -3468 |

The actual g_stream_pool/count move from the late game tail to0x100346b4/b8,
against reference0x10034670/78. g_sequence_counter remains0x10034610 against
reference0x10035408. These are actual new placements, not proofs of missing
owners in the intervening span. Default COMMON allocation scrambles the
bulk game's reference order: g_current_year moves to0x117632e0 and
g_slot_table to0x1166d360. All28 stock tail COMMONs nevertheless have the
same -3488 displacement in this control; __FPinit remains initialized data
at its correct address.

All598 function bindings,3140 CODE HIGHLOW sites and every non-fixup CODE
byte are unchanged. All four complete readonly/game-writable/version/
conversion-table guards pass.1197 CODE operands move, with zero lost or
gained exact operands. The entire file worsens from5320 to6634 differing
overlapping bytes, with the same16384-byte length gap. Raw differences:
text3667/rdata1270/data1312/reloc106. Data VS0x173f7fc is3488 bytes short,
four bytes worse than the canonical extent. Reloc VS remains0xc870.

This control is not promoted. SHA256:
`280ebf50d7dd7a3f2d3c0b8c43f0af9ec265b3410e13098e83fdb455d7376d9a`.
Evidence: `.scratch/native-partial-common-order/{probe.py,early-only.order,
argv.json,audit.json,bindings.json,crt-ordinary-bss.json,
changed-operands.json,gates.json}`. An initial diagnostic-script error
treated two complete-content initializer records as CODE operands; corrected
the analysis to select the3132 CODE records. It was not a native link error.

## 50. COMMON input ownership controls allocation without adding storage

Eight scalar controls separate ordinary BSS from COMMON allocation. Every
variant has exactly36 bytes of data VirtualSize: one4-byte explicit-zero
anchor, then eight4-byte tentative globals. The names below have prefix g_;
the anchor precedes them in every map.

| Input variant | COMMON allocation order |
| --- | --- |
| left,right | omega,gamma,delta,mu,beta,alpha,zeta,rho |
| right,left | beta,alpha,zeta,rho,omega,gamma,delta,mu |
| one combined object | beta,omega,gamma,alpha,zeta,delta,mu,rho |
| combined, declarations reversed | beta,omega,gamma,alpha,zeta,delta,mu,rho |

The single-object map order reverses the measured COFF symbol-table order
(C-shapes231). The two-object maps reverse the input groups. Two further
controls compile one scalar per object, in reverse desired physical order,
with definitions identical to the existing COMMONs. Prefixing these objects
before left/right yields the desired zeta,alpha,rho,beta,omega,gamma,mu,delta
order. Appending them leaves the original left/right order. The equal-size
COMMON definitions coalesce: every output still has36 bytes, with no linker
warning. This demonstrates ownership/allocation behavior in these cases,
not a reason to introduce duplicate definitions into production.

A server diagnostic applies the same prefix control to39 existing late game
COMMONs. Their declarations come from the shared tree-sitter parser, using
the actual defining source and compiler object's COMMON size. Every newly
compiled C object is checked to contain exactly its existing symbol with
the same size and no CODE or initialized-data contribution. The early99-entry
ORDER file from49 leaves these globals unordered. Original game objects and
stock archives are unchanged; equal-size definitions coalesce.

All39 late game COMMONs now follow their requested reference order after
ordinary CRT BSS. The first four clock globals have -3480 displacement;
the other35 have -3488. Data VS remains0x173f7fc, exactly equal to the
early-only control: no storage extent is added by the duplicate declarations.
Every100 import identity, IAT slot and named hint equals the canonical build.
All598 functions,3140 CODE HIGHLOW sites, non-fixup CODE bytes and the four
complete data/value guards remain protected. There are1197 changed CODE
operands versus canonical, with zero lost or gained exact operands.

The diagnostic improves the early-only file from6634 to5648 differences,
but remains worse than canonical5320. Raw differences are
text2681/rdata1270/data1312/reloc106; file length remains16384 bytes short.
SHA256 `887275ee51a794d24776c7dcfd393714b662a426625668da97e926017dd34c2b`.
It is not promoted. A production ownership repair would need to move the
existing definitions and preserve sizes, then prove complete byte agreement;
retaining extra COMMON definitions solely to influence allocation is not
such a repair. Missing original storage and the clock-to-array alignment
remain unresolved.

Evidence: `.scratch/native-common-allocation/` and
`.scratch/native-common-owner-control/{declarations.json,probe.py,argv.json,
audit.json,bindings.json,changed-operands.json,gates.json}`, all actual C
sources/compiler objects and native compile/link logs. No object/archive
patching, fake padding, enlarged array or CRT reconstruction was used.

## 51. Related binaries confirm the border-adjacent word, without proving its owner

Searching the complete 19-entry zlib border sequence finds it at these
addresses. Each first hit is followed by bytes00 00 ff ff and the inflate
copyright string:

| Binary | border VA | Next four bytes |
| --- | --- | --- |
| server.dll | 0x10024650 | 00 00 ff ff |
| Europa1400Gold.exe | 0x005ec140 | 00 00 ff ff |
| Europa1400Gold_TL.exe | 0x00663388 | 00 00 ff ff |

The TL binary also has a second copy at0x0066b4b8, followed immediately by
the string "invalid bit length repeat" rather than that word/copyright pair.
These are byte-sequence observations; the second copy's library ownership
is not established by this search.

The Desktop IDA export guesses dword_10024650[32]. Its initializer absorbs
the 19 genuine indices, the adjacent word, and all46 copyright bytes rounded
to12 further DWORDs. That guessed extent is not source-table evidence.
The server's two live relocation targets into the 19-entry span both address
its base; none addresses the adjacent word. The stock source indexes only
entries0..18. These facts leave the original owner/meaning of the word
unresolved. Its recurrence in related binaries does not authorize increasing
the source array merely to reproduce it.

C-shapes232's 19-entry control emits a76-byte four-aligned border COMDAT.
With the otherwise unchanged192-input native recipe, inflate_copyright moves
from0x100246a0 to0x1002469c; 16 subsequent readonly owners also move -4,
through g_file_extension_names. The next eight-aligned contribution restores
later geometry naturally. No replacement word or alignment object is added.

All598 function positions,3140 CODE HIGHLOW sites and non-fixup CODE bytes
remain unchanged.26 CODE operands change and all26 lose previously exact
bindings. Relative to canonical, raw text/data/rdata differ by26/5/885 bytes;
raw reloc is unchanged. Every section VirtualSize and file length stays the
same. The full readonly guard fails while the three other value guards pass.
The control has6236 overlapping differences and the unchanged16384-byte
length gap, SHA256
`97f8f203f888438d573f54477cab31086b5a5ade3d52a1dca38d26dc9cd25438`.
It is not promoted. Production remains the5320-difference canonical build;
the inherited extra initializer remains an explicit provenance limitation.

Evidence: `.scratch/native-infblock-tail/`, including related-tables.json,
the full-source/native-object check and complete native link/map/audit logs.
The configured reference, production sources, stock archives and canonical
objects are unchanged. No new Rebrew implementation deficit was exposed.

## 52. Dead-code removal changes live relocations without changing this reservation

Four SP5 native LINK-only controls retain genuine stock KERNEL32 imports,
requesting either function thunks or IAT symbols for GetLastError and
GetTickCount. They use /DLL /NOENTRY /NODEFAULTLIB /OPT:REF and frozen
SOURCE_DATE_EPOCH1771046057. No source table, fabricated fixup or edited
archive is supplied.

| Requested roots | Imports | Live HIGHLOW | Directory bytes | .reloc VS |
| --- | ---: | ---: | ---: | ---: |
| One function thunk | 1 | 1 | 12 | 12 |
| Two function thunks | 2 | 2 | 12 | 24 |
| One IAT symbol | 1 | 0 | 8 | 12 |
| Two IAT symbols | 2 | 0 | 8 | 14 |

Thus neither live HIGHLOW count nor import count alone determines reservation.
The IAT-only controls retain a relocation directory despite having no live
HIGHLOW entry. Their links report expected LNK4001/LNK4068 because no C
object or explicit machine option is supplied; the stock inputs select x86.
These diagnostic warnings do not occur in the production build.

A server control, before C-shapes233's placeholder cleanup, changes only
/OPT:REF to /OPT:NOREF and adds /VERBOSE.
It links the same192 C objects, native EXP and unchanged stock archives.
The loaded CRT-member set remains exactly138: no addition or removal.
Live HIGHLOW count rises3499 ->4246 and the directory grows7404 ->8924B,
but **.reloc VirtualSize remains exactly0xc870 (51312B)**. No warning is
emitted. This directly establishes that enabling these discarded contributions
does not supply the missing15108-byte reservation under this recipe.

The control has201 additional function MAP labels and109 imports instead
of100. .text VS grows141382 ->158080, .rdata11905 ->13969,
.data24377344 ->24380428. These relative section sizes do not indicate
correct absolute placement: earlier section growth also changes later RVAs.
The initialized .data extent grows0xd610 ->0xddd8 (+1992B), and its
combined BSS span grows0x17321f0 ->0x1732634 (+1092B). New COMMONs include
the three unreferenced source placeholders from C-shapes233 and three4B
stock fields: ___alternate_form, ___no_lead_zeros and ___sbh_initialized.
Their declared sizes total1039B; the remaining53B span change is not
attributed here. This is not proof of original missing BSS owners.

The /OPT:NOREF control is rejected: it adds code and imports absent from the
reference and does not fix relocation reservation. SHA256
`4ef9ccdf1425ff1b910151f91f8af1e1d3b5e3135a78778681e2cf0d0c7984f2`.
The read-only input census covers193 direct inputs (including EXP) plus138
CRT members:4167 DIR32,513 DIR32NB and2453 REL32 records. It excludes
synthetic short-import contributions and is not a general extent formula.
Do not multiply counts into a purported missing source table.

Evidence: `.scratch/native-reloc-input-census/{probe.py,controls.json,
input-census.json}` and `no-ref/{argv.json,link.log,audit.json,
new-symbols.json}`, all native DLLs and MAPs. Production /OPT:REF and its
5320-difference output are unchanged by these controls.

## 53. Resolve ordinal names from stock imports before changing call bindings

The older inline layout in rebrew-project.toml mislabeled three WinSock
ordinal slots. The actual stock WS2_32 short-import records establish:

| Ordinal | Reference IAT VA | Correct API | Stale inline name |
| --- | --- | --- | --- |
| 111 | 0x10024170 | WSAGetLastError | WSACleanup |
| 115 | 0x10024178 | WSAStartup | WSAGetLastError |
| 116 | 0x1002417c | WSACleanup | WSAStartup |

All236 audited direct import CODE operands bind to the same API identity
in the reference and canonical DLL, including these slots. Source calls
and retention seeds already use the correct names. The canonical layout
package records the raw ordinals correctly, and current Rebrew gen-layout's
resolver table is already repaired. This is stale project metadata, not a
new resolver implementation bug or a reason to rename correct C calls.

Correct only the three inline labels using Rebrew's locked project-TOML
reader/writer. Exact text and parsed-document checks prove every other config
field is unchanged. A native CMake rebuild regenerates EXP and relinks,
preserving all192 C objects and the entire canonical DLL byte for byte.
The23 displaced IAT slots remain a placement problem. No import identity,
ordinal, hint, source call or raw layout byte is changed by this repair.

Evidence: `.scratch/native-import-identity-audit/{direct-code-bindings.json,
stock-winsock-ordinals.json,config-repair.json,project-before.toml,
objects-before.json,canonical-repair-audit.json,native-build.log,
native-verify.json,native-build-check.json}`. Full verification remains
262/262, including two library checks; whole-file identity remains false.

## 54. CRC ownership now names the actual readonly library table

C-shapes233 removes three unreferenced COMMON placeholders and relocates
the CRC annotation to its real initialized zlib owner. The updated shared
declaration and managed fields name crc_table with const unsigned long[256]
and explicit1024B extent. Every metadata write uses rebrew data set; the previous
verdict is invalidated before fresh raw-link verification. The table contents
and library implementation are unchanged.

Independent owner checks require the MAP's actual _crc_table at0x100241a0,
all1024 reference bytes, a readonly PE section, and absence of the three
removed placeholder symbols. All pass on the native rebuilt artifact. An
image-content verdict alone did not establish that the old zero-filled
g_crc_table declaration supplied those readonly bytes; the owner check now
uses the correct symbol.

The complete rebuilt DLL remains canonical SHA256
`27d2ff2ab733cdf24957b17719ba561c55d582b2923e14e28fa1bfc29c476c71`,
270336B,5320 differing overlapping bytes and16384B short. Fresh verification
passes262/262,22EXACT/240RELOC, including two library checks, with zero
size divergences. Data remains530 matched,68 mismatched, seven missing and
three unchecked (608total). The renamed1024B CRC entry is VERIFIED with
new definition/input evidence. Build-check checks192 objects with zero drift.
All three targets lint4122passed with zero errors and warnings.
Whole-file verification and the independent objective gate correctly exit1.

These repairs remove unsupported declarations and stale labels; they do not
recover the original early BSS span, relocation reservation or header recipe.
The inherited border word's provenance remains unresolved. No padding,
enlarged array, CRT reconstruction, object/archive patch or postlink operation
is added. Evidence: `.scratch/native-crc-owner/canonical-*` and the native
full-source control. The whole-file goal remains incomplete.

## 55. Empty aligned data inputs explain the timezone displacement

The previous canonical link has timeset's complete148-byte initializer at
reference0x10033f80, ending0x10034014. tzset's28-byte initializer requests
eight-byte alignment, but starts at0x10034020 instead of0x10034018. Native
C-only controls correctly align148 to152. The stock ulldiv/ullrem assembly
members instead contain empty `.data` sections requesting16-byte alignment;
C-shapes234 proves their placement effect with an untouched whole member.

Move the existing `/INCLUDE:___dnames` root from after calloc to after
`__aullrem`. It supplies the same code-free timeset member after these empty
sections. This restores all28 tzset bytes and its actual operand binding
at0x10034018, while preserving all9320 readonly bytes and the full1140-byte
CRT initialized prefix. There is no new data definition, member or padding.

Four native controls use the same192 C objects, native EXP and stock archives:

| Roots changed after moving timeset | File differences | Raw CODE/data/reloc differences | Displaced HIGHLOW sites outside CODE |
|---|---:|---|---:|
| Timeset only | 5287 | 2326/1307/106 | 55 |
| Also days after tzset | 5118 | 2299/1189/82 | 47 |
| Also lconv after the C-locale time root | 4618 | 2324/640/106 | 54 |
| Days and lconv | 5110 | 2299/1181/82 | 36 |

All four retain598 function bindings,3140 CODE HIGHLOW sites, zero CODE
differences outside those fields,100 import identities/DLL order/hints,
23 displaced IAT slots, unchanged section extents and all five full-value
guards. Raw readonly differences remain1270. All still have3499 live
HIGHLOW entries and a16384-byte file-length gap. These counts are complete
native-link measurements, not normalized-object comparisons.

Promote **timeset plus lconv**. The added `/INCLUDE:___lconv_c` immediately
after `___lc_time_c` loads the existing60-byte code-free lconv contribution
before the existing700-byte constpow contribution. Every700 constpow byte
now matches at reference0x10034350; its two CODE operands also become exact.
Across58 changed CODE operands,19 become exact and zero previously exact
operands are lost. The lconv contribution itself remains at0x10034220,
against reference0x10034310: its placement is still incomplete.

The days controls place its104 bytes correctly at0x10034034, but the combined
control moves constpow to0x10034348, losing the complete power-table match.
It is not promoted despite fewer displaced relocation sites. Production
days remains incorrectly placed at0x10034260; the exception table remains
at0x100342c8 against0x100340a0. These bindings are explicit unresolved work.

The actual CMake rebuild reproduces the accepted native control exactly,
SHA256 `de01cc4e2bba67bd23e31719d3b797feb2fd9dfa13ead6c9eb338e93f8e93fbb`,
270336B and4618 overlapping differences, down702 from5320. All192 compiler
object hashes are unchanged. Data VirtualSize remains0x173f800 (3484 short),
reloc VirtualSize0xc870 (15108 short), and the configured reference is
unchanged. Stored/computed checksum is0x443ff; e_lfanew remains0xf0.
Whole-file equality remains false. No library, object or output byte is
patched; this is native archive selection through two existing data owners.

Evidence: `.scratch/native-ordinary-data-alignment/`, including server.py,
the four native output/argv/log/audit/gates directories, table-bindings.json,
lconv/changed-code-operands.json, lconv/operand-summary.json,
objects-before.json and canonical-build.log.

Final canonical checks:262/262 function checks pass (22EXACT/240RELOC,
including two library checks), with zero failures/size divergences. Reversing
progress remains260/339; the two library checks are excluded. Full data
verification remains530 matched,68 mismatched, seven missing and three
unchecked. Build-check checks192 objects with zero drift. Every target lints
4122 passed with zero errors and warnings. Whole-binary verification and the
independent objective gate correctly exit1. Coverage is regenerated after
verification completes. Status reports92.6% file agreement and99.4% accounted
text; its reusable function-proof timestamps remain unchanged because the
compiler inputs are unchanged. Evidence: canonical-* in the same directory.

## 56. Complete stock data matching must validate pointer identities

A read-only scan of the unchanged stock archive examines42 ordinary
initialized contributions of at least16 bytes that have a nonzero fixed
byte outside relocation fields. Sparse full initializers are included:
setlocal's267-byte cache with only three 'C' bytes must not be discarded
by a high fixed-byte threshold. All qualifying currently selected
contributions have a reference match. The selected-member set comes from
the measured138-input native trace, not the124 MAP-visible owners.

The only unselected candidate is syserr.obj's180-byte pointer table:
44 DIR32 fields and one nonzero fixed byte. Masking its pointers produces
eight apparent reference matches, including unrelated game tables and
the readonly border region. **All eight are rejected**: each has zero of
the required44 HIGHLOW sites and zero complete matches for the actual
pointed-to stock strings. Matching the remaining fixed bytes alone would
incorrectly attribute library ownership. No extra member is linked.

This scan excludes all-zero blocks, short scalars, COMDAT data and BSS;
it cannot establish the original discarded CODE, unknown BSS owners or
the ten additional compiler-8047 C inputs suggested by Rich records.
Only two of the archive's40 empty tcmap aliases target already-live code;
their one/two-alias controls were already measured in20. Counts alone
do not justify choosing additional inputs. Evidence:
`.scratch/native-original-data-census/{scan.py,sections.json,summary.json,
candidate-checks.json}`. No new Rebrew implementation defect is established
by these bounded scans; prior shared tooling repairs remain in place.

## 57. Removing an unsupported duplicate root restores CRT data and all relocation sites

Starting from55's4618-difference native build, add __lpdays and __XcptActTab
immediately after ___tzset. All later initialized CRT tables regain their
reference positions, but96 CODE labels move. C-shapes235 establishes the
cause from complete stock bodies and native verbose folding messages:
the retained private _strncnt copy changes from a_cmp to a_map, even though
the total ICF savings stay86 bytes. The public strdup/mbsdup pair's survivor
changes too. Both inputs are still selected; the member set remains138.

Five public data roots for the same winxfltr member (XcptActTab, First_FPE_Indx,
Num_FPE, XcptActTabCount and XcptActTabSize) all produce19955 file differences,
96 moved functions and13304 unmasked CODE differences. Moving the lconv root
after strcmpi/allmul/crtCompareStringA/the final floating-point root, moving
the exception root after gmtime/strtol, changing the single late tcmap alias
and adding the other already-live alias do not repair it. Duplicating the
crtCompareStringA root earlier moves67 functions and is also rejected.
Swapping strdup/mbsdup roots has the same19955-difference regression.
No rejected root/alias ordering is part of production.

The current source and actual selected-object fixups never reference
__mbsdup. Only its explicit root selects mbsdup.obj; the verbose trace has
no caller for that symbol. Its complete43-byte function and all three named
fixups equal strdup's. Remove that root while keeping the two real table
roots. Native ICF now keeps the reference private helper and produces3900
file differences. Baseline-without-mbsdup alone gives4620 differences and
unchanged CODE: the useful repair is the coupled table/duplicate-input change.

The original fixed598-label audit fails on this accepted control because
one unused alias disappears. The specific ownership check requires **only**
__mbsdup to be absent, verifies its old VA equals retained __strdup at
0x10023812, compares all43 actual bytes against the reference and checks all
remaining597 bindings. It also scans every relocation section of192 C
objects plus137 actually loaded CRT members for that alias: zero references.
No executable function body is missing or moved. Never approve this outcome
from a smaller function count alone.

Complete native guards establish:

- Same3140 CODE HIGHLOW sites and zero CODE differences outside those fields.
- **All3499 live HIGHLOW sites equal**, with zero missing/extra anywhere.
- All53248 emitted relocation-section raw bytes equal the reference prefix;
  its full live7404-byte directory matches. The larger reference extent still
  has16384 additional raw zero bytes; this does not prove an input owner.
- All five readonly/game-writable/version/conversion/prefix guards pass.
- Complete timezone28B,days104B,exception136B,conversion48B,mbctype248B and
  power700B contributions match at reference34018/34034/340a0/34130/34160/34350.
- The C-locale table and lconv contribution now bind to34260 and34310;
  lconv's pointers to its BSS null byte still differ.
- All100 import identities,DLL order and named hints remain correct;
  23 IAT slots remain displaced.

The actual CMake relink equals the accepted control exactly, SHA256
`7bcdaa633a46c5506d70ad06abc6dda52568d14a51a96b2f17550e0c11679c95`,
270336B,3900 overlapping differences and16384B short. This improves718 bytes
over55. Every192 compiler-object hash stays unchanged. Raw text/rdata/data/
reloc differences are2288/1270/62/0. **Every one of the62 differing data
bytes lies in17 known HIGHLOW pointer fields**, all targeting BSS: the zutil
empty string, stdio buffer, four lock owners and lconv null byte. All other
initialized-data bytes match. These BSS targets still need correct placement.

Native section extents remain text0x22846,rdata0x2e81,data0x173f800 and
reloc0xc870. Data is3484 virtual bytes short; relocation reservation is15108
virtual bytes short. Stored/computed checksum is0x4ad54 and e_lfanew0xe0.
The Rich compiler-8047 count becomes113; the reference's124 still does not
identify missing owners. The configured reference is unchanged and whole-file
identity remains false. No padding, new storage, CRT implementation,
object/archive editing or postlink operation is introduced.

The separate /OPT:ICF=1 experiment exits93 with native LNK1117 (unsupported
option syntax). That is a measured LINK6 limitation, not a Rebrew driver
failure. The probe stops there; ICF=10, VC5-import and runtime-library-position
controls in its later list were **not executed** and are unnecessary for the
accepted repair. Do not describe them as negative results.

Fresh verification passes262/262 (22EXACT/240RELOC, including two library
checks) with zero failures/size divergences. Data remains530 matched,
68 mismatched, seven missing and three unchecked. Build-check checks192
objects with zero drift; all three targets lint4122 passed with zero errors
and warnings. Whole-binary and independent objective checks correctly exit1.
The storage audit is regenerated against the actual137-member trace; stale
138-member censuses must not be reused as current membership evidence.
No new shared Rebrew implementation defect is established in these controls.

Evidence: `.scratch/native-crt-exception-root/`, particularly controls.json,
ordering-controls.json,folding-controls.json,accepted-checks.json,
canonical-ownership-audit.json,canonical-*,storage-audit.py/audit.json and
the unchanged native argv,logs,DLLs and MAPs. Next work is genuine BSS
ownership/order, IAT slots, reserved relocation extent and native headers.

## 58. IAT placement and the hint/name pool have separate orders

The reference's first KERNEL32 IAT entry is GetLocalTime, but its first
hint/name record at RVA0x2680c is WriteConsoleA. The existing gen-layout
retention source requests imports in IAT order. That restores many IAT
slots while forcing a different physical hint/name pool. Neither order is
an adequate substitute for the other. All controls below use native LINK
and unchanged stock libraries; no synthesized import storage is added.

Eleven small links isolate the input-context effect. Six WinSock-only
controls use forward/reverse IAT roots, forward/reverse function roots,
and the two mixed root sequences. With sixteen IAT roots alone, emitted
ordinals follow the requested reference sequence:
`1,13,19,16,10,111,22,115,116,23,21,8,9,2,20,3`.
Adding the81 KERNEL32 IAT roots still preserves that WinSock sequence.
Adding the two USER32 and one WINMM roots changes the emitted WinSock
sequence to `19,16,10,111,22,115,13,23,21,8,9,2,20,3,1,116`, despite
unchanged WinSock requests and archive. Function-root order also changes
which seven thunks survive and their ordering. Archive lookup order alone
therefore does not predict emitted IAT order. These controls do **not**
establish LINK's internal sorting algorithm.

Fourteen full-DLL controls start from57's canonical3900-difference build:

| Control | Overlap differences | Displaced IAT entries | Moved function labels | Unmasked CODE differences |
|---|---:|---:|---:|---:|
| Remove seven late KERNEL32 IAT seeds | 3895 | 24 | 0 | 0 |
| All WinSock IAT roots first, ORDER adler32 then seven thunks | 142900 | 24 | 596 | 113815 |
| Root WS2_32 descriptor | 3900 | 23 | 0 | 0 |
| Root WINMM descriptor | 3900 | 23 | 0 | 0 |
| Root all four descriptors | 4414 | 23 | 0 | 0 |
| Remove seven WinSock function roots | 3910 | 24 | 6 | 7 |
| Remove those roots and all WinSock IAT seeds | 3900 | 23 | 0 | 0 |
| Remove every import seed | 3054 | 69 | 0 | 0 |
| First nine direct WinSock IAT roots first | 3903 | 24 | 0 | 0 |
| Those nine roots in reverse | 3903 | 24 | 0 | 0 |
| No seeds, WINMM before CRT | 3054 | 69 | 0 | 0 |
| No seeds, another unchanged KERNEL32 archive after CRT | 3828 | 71 | 0 | 0 |
| Existing seeds, WINMM before CRT | 3900 | 23 | 0 | 0 |
| Existing seeds, another unchanged KERNEL32 archive after CRT | 3906 | 25 | 0 | 0 |

Every control keeps100 import identities, DLL descriptor order and all
named hints. Every control except the large ORDER regression keeps all
3499 live relocation sites. Native ORDER accepts the thunk function names
without warnings, but places them at0x10001130 instead of0x1001a160 and
moves almost all code; acceptance is not a placement proof. The separate
IAT-symbol ORDER failures in11 still apply.

Removing every seed is informative but unpromoted. It restores75 of84
hint/name RVAs, versus27 currently, and changes readonly differences from
1270 to308. Its remaining nine displaced name records are GetLastError,
HeapReAlloc,GetCommandLineA,GetVersion,EnterCriticalSection,
LeaveCriticalSection,GetStringTypeA,GetStringTypeW and GetCPInfo.
The first six form one rotation; the last three form another. Native
verbose references attribute the first rotation to CRT member selection
(including realloc and the GetLastError callers); the latter involves
mbctype/a_cmp/initctyp versus a_str/w_str. Do not change correct API calls
or stock bodies to match these ordering differences.

The per-group readonly byte comparison is:

| Native group | Current differing bytes | No-seed differing bytes |
|---|---:|---:|
| IAT, .idata$5 | 123 | 83 |
| Descriptors, .idata$2 | 8 | 0 |
| Null descriptor, .idata$3 | 0 | 0 |
| Lookup table, .idata$4 | 123 | 83 |
| Hint/name pool, .idata$6 | 1016 | 142 |

The lower raw count hides operand regressions: no-seed gains five exact
HIGHLOW operand values and loses115, increasing raw CODE differences from
2288 to2404. Data remains62 and emitted relocation raw bytes remain exact.
Removing only late kernel seeds loses one exact operand; moving an extra
kernel search after CRT loses six with seeds, or105 without them. The
coupled WinSock root/seed deletion trades one exact operand for another.
None is a repair that preserves the established bindings.

Rooting WS2_32's descriptor and moving WINMM before CRT with existing seeds
each produce the entire canonical DLL unchanged. Rooting WINMM's descriptor
changes27 bytes versus canonical, relocating the DLL string versus its name
record without fixing a slot. Rooting all descriptors changes1635 bytes
versus canonical. Do not infer a no-op from an unchanged total diff count.

No control is promoted. Canonical SHA256 remains
`7bcdaa633a46c5506d70ad06abc6dda52568d14a51a96b2f17550e0c11679c95`;
the3900-difference/16384B-short objective remains incomplete. No new shared
Rebrew implementation defect is established. Evidence:
`.scratch/native-import-selection/{probe.py,full.py,all-toy-audit.json,all-full-audit.json}`
and each native argv/log/DLL/MAP. The controls' replacement C objects contain
only directives/debug information and no relocations or executable/storage
contributions. All canonical compiler inputs and archives are untouched.

## 59. Place the actual callback without shifting the other COMMON owners

The early reference callback pointer is0x10034610, while the previous native
link places its explicitly initialized ordinary-BSS owner at0x1176641c.
Changing only this actual declaration to a tentative four-byte COMMON and
inserting it before the existing sequence counter reaches the reference
callback but shifts bulk allocations32 bytes. A selectany declaration yields
the same complete control DLL. Both controls have4820 differences versus3900
before, six gained exact operands and no lost exact operands. Neither is
promoted. Removing the other18 ordinary placeholders' initializers still
leaves4820 differences and loses32 bytes of allocated extent; also unpromoted.

The accepted change replaces the sequence counter's early ORDER entry with
the callback, then places the counter immediately after the existing entity
pointer. Its actual four-byte COMMON fits the existing28-byte alignment
interval before `g_relationship_matrix_secondary`. No replacement storage
or array enlargement is introduced. Only two mapped symbols move: callback
to0x10034610, sequence counter from0x10034610 to0x1014c6c4. The counter's
reference is still0x10035408. All other symbols, including all597 function
labels, retain their addresses. All six callback operands become exact; all
five counter operands bind to its actual new owner, and no formerly exact
HIGHLOW operand is lost. Thirty-nine CODE bytes change only inside those
eleven fields; `.rdata`, `.data` and emitted `.reloc` raw bytes are unchanged.

The actual CMake build recompiles only `link_stubs.c.obj`; the other191 C
objects retain their hashes. Its native output equals the accepted scratch
LINK output exactly: SHA256
`77f7fec33f3ed91a525e9f1896d9df1da1f65c0505c8ef15c734dcc2ec3c7bfa`,
270336B,3881 overlapping differences,16384B short. Raw section differences
are2269/1270/62/0 for text/readonly/data/relocations. All3499 live HIGHLOW
sites equal the reference globally, all53248 emitted relocation bytes equal
its prefix, and no CODE difference exists outside3140 HIGHLOW fields.
Imports retain100 identities, hints and DLL order, with23 IAT displacements.
The unchanged stock CRT archive supplies the same137 selected members and
124 MAP-visible members. The fresh storage census uses all192 C objects and
the actual77f verbose native trace;3132 CODE fields have COFF attribution,
with eight synthetic import sites separately accounted for. Complete game
readonly, mutable data, version, CRT pointer-table and locale-prefix guards
all pass. No stock object/archive/reference or linked byte is edited.

Section VirtualSizes remain text0x22846, readonly0x2e81, data0x173f800,
relocations0xc870. Data is3484 virtual bytes short; relocations are15108
virtual bytes short. Native `/RELEASE` checksum stored/computed is0x4edbb;
e_lfanew remains0xe0. The configured reference remains unchanged. This is
native operand-placement progress, not full-file identity.

Full forced verification at07:01:45 UTC reports262/262 byte matches
(22EXACT/240RELOC, including two library checks), zero failures or size
divergences. Reversing progress excludes those two checks:260/339.
Data comparison reports530 matched,68 mismatched,7 missing,3 unchecked.
Build-check reports192 objects/zero drift; all three targets lint4122
passed/zero errors/zero warnings. Whole-binary and independent file gates
correctly fail the incomplete goal.

That forced run exposed a shared Rebrew deficit: `status` continued to show
the cache's04:27 timestamp as stale. The generic atomic writer correctly
preserves mtime for identical bytes, but status uses cache mtime as the full
verification instant. Repeated full runs serialize identical verdict rows
and therefore never refresh it. Fix `save_verify_cache` directly in the
sibling Rebrew source: under its existing write lock, touch the successfully
published cache after an unfiltered run, then invalidate its memo. Filtered
runs do not refresh identical preserved rows. Keep generic atomic-write
idempotence and the cache schema unchanged. A two-case regression reproduces
the failure before the fix and passes after it;216 incremental/status tests,
Ruff checks/format and cache-module mypy pass. The global CLI reads that
editable source. The project fix is also packaged with the prior driver and
source-order repairs in the pinned9123ca68 wheel, rather than synchronizing
the unrelated concurrent sibling changes. Reproducible patch:
`docs/rebrew-patches/verify-cache-freshness.patch`.

Evidence: `.scratch/native-panic-owner/`, including accepted ownership and
member audits, full verification, native build logs, value guards, tooling
regression logs and wheel build/install evidence. Goal remains active.

With the installed fix, the unfiltered full-scope07:20:23 UTC verification
again reports262/262. Project `status` now reports07:21:04 UTC,stale=false,
92.9% file agreement and99.4% accounted text. Coverage is regenerated for
all three targets; fresh all-target lint and192-object build-check pass.
Wheel SHA256 is
`9724e9b3ef9b11ae6cd2f49741e4228cdfafec76dea5bf9f1b045286d25259df`.
Its only changed package file is verify_cache.py; RECORD and WHEEL generator
metadata also change. The two pinned regression cases pass. The bare global
CLI's concurrently edited comparison logic has a different compiler/cache
identity, so it rejects this pinned run's cache and does not display its
verification summary. That is separate from the repaired timestamp defect;
the project `.venv/bin/rebrew` and native build remain authoritative.

## 60. Three native logging COMMONs fit when earlier real counters move

Promote only three C89 tentative definitions and their actual native ORDER
entries: `g_crash_callback`, `g_log_mode_flags`, `g_crash_dump_all_frames`.
Their four/four/one-byte owners reach reference0x10034614/18/1c after the
already-exact panic pointer. Move the existing four-byte dynamic count and
two family counters after the existing sequence counter in the entity-pointer
alignment interval. That interval now retains12 bytes of native alignment.
The three relocated game counters remain unmatched; no owner is enlarged,
duplicated or replaced. No stock archive, object, reference or linked byte
is edited, and the18 ordinary support placeholders stay unchanged.

An independent logging-only control reaches the same three reference
bindings but moves the aligned32-byte save field and every large array32
bytes. It yields4745 differences despite20 gained/zero lost exact operands;
unpromoted. The coupled counter ORDER change restores all89 other previous
COMMON bindings and every large-array address. All597 function labels and
3499 live HIGHLOW sites retain their addresses. Every CODE byte outside the
3140 HIGHLOW fields remains exact. All20 logging fields are exact, and every
previously exact field stays exact. Three COMMON counters move; three new
logging COMMONs move out of ordinary BSS;67 ordinary symbols move12 or16
bytes earlier through native allocation/alignment. C-shapes237 records the
measured alignment boundary and actual storage sizes.

Actual CMake recompiles exactly three source objects;189 retain their hashes.
The before-manifest is derived from the previously validated192-object
manifest with the unchanged support-object hash refreshed; the linker rsp's
193rd input is native EXP, not another compiler object. Complete object
contribution checks cover executable and initialized data, section sizes/
flags and named fixups. Native CMake output equals the accepted scratch LINK
output exactly: SHA256
`dbcc3e33da342162a00608e0d2d1d9f25166848e780b7866c3c615d99cf03b92`,
270336B,3816 overlapping differences (65 fewer),16384B short. Text differences
fall2269->2203; readonly/data/relocation differences remain1270/62/0.
Readonly and relocation raw bytes are unchanged. The16 changed initialized
data bytes lie wholly in existing HIGHLOW pointer fields; no fixed data
value changes. The complete five value guards pass. All53248 emitted
relocation bytes still equal the reference prefix.

The same137 unchanged stock CRT members are selected,124 MAP-visible.
Fresh dbcc COFF census uses192 C objects and that native member trace,
attributing3132 of3140 CODE fixups with the eight synthetic import sites
separate. Callback/mode/byte have3/15/2 exact native/reference votes and
single COMMON definitions of4/4/1 bytes. Imports retain100 identities,
hints and descriptor order, with23 displaced IAT entries; the entire readonly
section is unchanged. Native checksum stored/computed is0x428d0; e_lfanew0xe0.
Text/readonly/reloc VirtualSizes remain0x22846/0x2e81/0xc870. Data VirtualSize
becomes0x173f7f0,3500 short; reloc virtual reservation is still15108 short.
These missing extents and native headers/import placement remain real work.

Fresh full-scope verification07:39:32 UTC reports262/262
(22EXACT/240RELOC including two library checks),zero failures/size divergences.
Data530matched/68mismatched/7missing/3unchecked. Project status07:40:18 UTC
is current (stale=false),92.9% file agreement,266520/286720B;
99.4% accounted text,260/339 progress. Stored data accounting remains
498verified/12drift/3unchecked,27020/66664 verified bytes,36713 conflicting
verified bytes. Build-check192objects/zero drift; all three targets lint4122
passed/zero errors/zero warnings; coverage regenerated for all three.
Whole-binary and independent objective gates correctly fail full identity.

Native trace control: `/VERBOSE:LIB` reports library searches but zero
`Loaded LIBCMT.lib(...)` lines in this link. `/VERBOSE` reports all137, and
both produce identical native bytes. Use the complete trace for ownership,
not the restricted output. No shared Rebrew caller of either flag is found;
this is a scratch-control repair, not a new Rebrew implementation defect.
Trace SHA256
`d16aa10eda58b3b2ccd9e9aba78c463e5c039d69d26dd7c0b155c61271924313`.
Prior direct cache/CMake/source-order fixes are preserved. Evidence:
`.scratch/native-log-common/{canonical-*,member-audit.json,accepted-checks.json,
accepted-gates.json,audit.json,operands.json}` and common-gap native artifacts.
Goal active/incomplete; keep the configured reference unchanged.

## 61. Bound omitted stock storage before adding library inputs

A fresh read-only census parses all638 COFF objects in the unchanged SP5
LIBCMT archive and uses the actual137-member dbcc selection. Seventy-five
members have BSS or COMMON. The35 unselected storage owners have1720 bytes
of ordinary BSS and48 bytes of COMMON, with no COMDAT BSS. Every unselected
COMMON is four bytes. Their BSS section flags request a total maximum103
bytes of individual alignment slack. Including at most three alignment
bytes per four-byte COMMON gives1907 bytes of their own contributions.
This is below both the3460-byte early unanchored span and3500-byte current
data VirtualSize deficit. Twelve already-selected CRT BSS sections lack
reference anchors:152 bytes plus36 alignment slack. Adding those gives2095.

This bound concerns these storage contributions and their recorded section
alignment. It excludes initialized-data inputs and layout shifts of storage
already present; it is not a bound on every possible final linked extent.
It does not establish which unselected members belonged to the original or
permit selecting all35 solely to fill a gap. The known late4104-byte file
COMMON contribution already has actual owners/bindings; it is not missing
storage to reuse in the early gap. Ordinary startup/thread/locale/cache
definitions remain subject to their actual call/data references.

The archive contains598 x86 objects plus40 unspecified-machine tcmap COFF
weak-alias objects, and three archive metadata members. All40 alias objects
are explicitly parsed: their section byte/fixup counts and COMMON storage
are zero. They are not directive-only objects; they contain empty `.text`
and class105 weak externals with fallback symbol indices. Their two fallback
targets already live in this DLL are covered by earlier alias controls.
Zero storage does not mean a native link no-op (see20's alignment control),
but these aliases cannot supply the missing BSS owner. Evidence includes
`weak-aliases.json`; the census does not silently skip non-x86 members.

The unchanged distribution copy is rechecked against the configured
reference: all four section contents/extents/RVAs/raw offsets remain exact.
Only its headers provide the original Rich provenance. Stock counts include
37 compiler8966 inputs versus192 native,124 compiler8047 versus113 native,
and six librarian7291 versusone native. The stripped configured header has
no Rich entries. These counts still do not identify original storage owners
or authorize changing the configured reference. The selected archive and
reference hashes remain unchanged.

A separate native control moves39 real late-game COMMON definitions into
one existing early input, replacing all previous definitions with externs.
There are no duplicate providers or additional compiler objects, and all
nine replacement objects preserve complete CODE/initialized data and named
fixups. It uses only the early ORDER prefix through the actual save field.
Native allocation reverses the provider's COFF table rather than following
the requested reference order. All597 function positions,3499 live sites,
fixed CODE bytes, all imports/readonly/relocation bytes and five complete
value guards are protected; no exact operand is gained or lost.

Control SHA256
`d46cbe45a0a7246b8fe3ff129f9da8cd416741ffe449dfa3a3959795d6e66a3b`,
270336B,5226 differences,16384B short. Text/readonly/data/relocation
differences3643/1270/32/0. Data VS0x173f81c is44 bytes larger through
alignment, despite identical declaration extents; still3456 short.
The complete source move makes the earlier50 experiment reviewable as real
ownership, but this layout is rejected. Do not promote the control or claim
its lower data-only count as progress toward the deliverable. C-shapes238
records provider counts and the actual order.

Canonical native output remainsdbcc/3816/16384B short. Its last262/262 proof
still applies to the unchanged DLL and compiler/source inputs. All three
targets retain clean lint;192-object build-check and direct file/hash guards
pass. No canonical rebuild or full verification is needed for scratch/docs
changes. No new Rebrew implementation deficit is found; preserve the prior
direct fixes and pinned wheel. Next work remains genuine game storage/input
composition and explicit ordering with ordinary CRT BSS, plus imports,
relocation reservation and native header provenance. Whole goal incomplete.

Evidence: `.scratch/native-missing-bss-census/{scan.py,storage.json,summary.json,
selected-unanchored-bss.json}`; `.scratch/native-common-single-owner/` including
native nine-source/COFF comparisons, allocation audit, five guards and
canonical validation. No stock member/archive/object/reference is edited.

## 62. Compiler debug records alone leave the small reservation control unchanged

The plain, `/Z7`, `/Zi`, and `/Zd` SP5 objects from C-shapes239 retain the
same runtime contributions while their compiler debug records differ.
Native LINK receives no `/DEBUG`. All four complete DLLs are identical,
with three live HIGHLOW entries, a 24-byte directory, 26-byte `.reloc`
VirtualSize, and no debug directory. SHA256
`9e70690c8077ca0289a802237f87297113c917dc10e556a93290d3879e5109ad`.

This rules out a compiler debug-record effect in this particular input;
it is not a full-server control. Do not enable the coupled CMake debug
option and attribute its linker changes solely to compiler `/Z7`.
The saved four-control generation had already completed. A separate
read-only recheck validates all native bytes and runtime COFF contributions;
this continuation invokes neither Docker nor a toolchain wrapper.

Evidence: `.scratch/native-debug-reservation/{probe.py,audit.json,recheck.py}`
and the four complete native object/DLL/argv/log sets. Canonical server
inputs and its dbcc DLL remain unchanged.

## 63. A fixup-and-page bound fits the saved reservation controls

A fresh read-only census uses the actual current 193 direct inputs,
including one native EXP, and all 137 selected unchanged stock CRT members.
It finds 4,167 DIR32, 512 DIR32NB, and 2,450 REL32 records. The complete
current native library trace also records 109 selected import members:
90 KERNEL32, two USER32, sixteen WS2_32, and one WINMM. Import descriptors,
the shared null descriptor, and DLL null-thunk members are excluded from
that count. The live DLL retains only 100 imports.

Define `N` as all input DIR32 records plus the potential synthetic import
thunk fixups, including discarded inputs. Define `P` as the sum of
`ceil(VirtualSize / 4096)` across emitted sections other than `.reloc`.
Every measured DLL has 4096-byte section alignment. The empirical model is:

```text
reserved bytes = min(12 * N, 2 * N + 10 * P)
```

This exactly fits all 23 saved PE files, representing fifteen distinct
`(N, P)` pairs. Four of the files are byte-identical debug controls; this
is not a claim of 23 independent experiments. Representative measurements:

| Saved control | N | P | Measured .reloc VS |
| --- | ---: | ---: | ---: |
| One rooted import thunk | 1 | 2 | 12 |
| Two rooted IAT symbols | 2 | 1 | 14 |
| Three-fixup C input | 3 | 2 | 26 |
| Sixteen rooted IAT symbols | 16 | 1 | 42 |
| Sixteen rooted import thunks | 16 | 2 | 52 |
| 100 rooted IAT symbols | 100 | 1 | 210 |
| Historical discarded 1,000-pointer control | 1,001 | 3 | 2,032 |
| Current native server | 4,276 | 5,990 | 51,312 |
| Historical server `/OPT:NOREF` | 4,276 | 5,996 | 51,312 |

The current server count comes from fresh COFF and loaded-member evidence,
not from dividing its reservation by twelve. The older NOREF control uses
its own historical input census and retained import table. In the large
server, the model selects the `12 * N` bound. In the smaller controls it
can select the page bound. This explains the earlier numerical coincidence
and the small-control counterexamples within one model. It also accounts
for an unchanged reservation when NOREF changes live sites but preserves
potential fixups and stays in the same capped branch.

This remains an empirical fit, not a proved general LINK algorithm. In
particular, these saved files do not independently vary virtual BSS pages
while holding potential fixups fixed through the proposed transition.
That is the next discriminating native control. Do not treat the model as
a managed metadata rule, or manufacture dead pointers or BSS to obtain an
extent. Existing diagnostic pointer tables are historical scratch evidence
only; none is added to production.

If this model also applies to the original reference, its 66,420-byte
reservation would imply 5,535 potential fixups, 1,259 more than the current
input set. This conditional inference does not identify their owners,
prove an original discarded table, or recover the original link inputs.
The model concerns section VirtualSize, not the reference's directory-size
field, native headers, live-site values, or whole-file identity.

No production C, layout, archive, object, reference, or shared Rebrew code
changes. The independent project objective checker had a misleading
diagnostic: failed data/relocation extent checks printed the reference
extent. Its one-line correction now prints the measured build extent
(`0x173f7f0` and `0xc870`). Pass/fail and raw identity logic are unchanged.
Its existing input regression passes; the canonical failure output is
checked for the actual extents and the unchanged 3,816/16,384-byte deltas.
This standalone checker has no shared Rebrew implementation caller, so
there is no corresponding library fix to make.

Evidence: `.scratch/native-reloc-reservation-audit/{audit.py,audit.json,
inputs.json,lint-all.json,build-check.json,objective.json}`. The read-only
audit records every current input hash, complete loaded import names, all
23 PE hashes, potential-count provenance, page counts, and model results.
Fresh all-target lint remains zero errors/warnings; native object checks
remain clean. Whole-file goal is still incomplete.

## 64. A native page-boundary experiment supports the reservation cap

The seven complete C89 controls in C-shapes240 preserve all runtime object
contributions and their three DIR32 records while varying one live COMMON
array. Native links retain the indexed function and use the same frozen
epoch, `/DLL /NOENTRY /NODEFAULTLIB /INCREMENTAL:NO /OPT:REF` recipe.
All have three live HIGHLOW entries and a 24-byte directory.

| Array extent | Data VS | Non-reloc pages P | Reloc VS | Model |
| --- | ---: | ---: | ---: | ---: |
| 1 | 9 | 2 | 26 | 26 |
| 4000 | 4032 | 2 | 26 | 26 |
| 4064 | 4096 | 2 | 26 | 26 |
| 4065 | 4097 | 3 | 36 | 36 |
| 4096 | 4128 | 3 | 36 | 36 |
| 8192 | 8224 | 4 | 36 | 36 |
| 32768 | 32800 | 10 | 36 | 36 |

This is the independent page variation missing from63: a single-byte
COMMON extent change crosses the page boundary, changes reservation by10,
and leaves code, initialized data, potential fixups and live fixups fixed.
Further pages do not grow reservation after the proposed `12*N` cap.
The measured controls support `min(12*N, 2*N+10*P)` causally, within this
recipe. They do not prove a general algorithm for every architecture,
section alignment, incremental/debug mode, absolute symbol, or discarded
storage contribution, nor establish original reference input composition.

Docker responds normally (29.8.1); project wrappers successfully compile
and link every control. The earlier offline continuation did not probe
access and does not establish a current Docker failure. No production
array, archive, object or reference is modified for this experiment.
Evidence: `.scratch/native-reloc-pages/`, including complete seven native
artifact sets and `audit.json`. The before/after canonical hash is equal.

## 65. Promote allocator ownership with actual fields in existing alignment intervals

The earlier13-owner selectany controls in35 tested a different ownership
shape and were rejected. This control uses the eight current real allocator
definitions in their existing owner translation unit, converting only
explicit zeros to tentative COMMONs. Complete runtime COFF contributions
remain identical. The four previously promoted logging owners stay exact.
Zutil's existing empty literal is explicitly ordered; no literal is invented.

The allocator-only control correctly binds the eight fields and empty
literal, but shifts the save/bulk arrays64 bytes and worsens3816->4531.
The coupled control uses nine real unchanged game fields to occupy36
bytes of existing native alignment:28 after manufacturer types and eight
after the human-family counter. It preserves every other protected COMMON,
all bulk/clock/save/logging bindings,597 function positions,3499 live
HIGHLOW sites, and all non-fixup CODE bytes. All five complete data/value
guards pass. The displaced fields themselves remain unmatched; their real
definitions, types, sizes and code references are retained.

Promoted production changes: eight removed scalar initializers in
`m_alloc.c`, the existing empty COMDAT plus eight allocator ORDER entries,
and nine existing game-field ORDER moves. No new source object, duplicate
provider, enlarged array, modified CRT archive/object, fake BSS or postlink
operation. All stock CRT members are linked unchanged.

Current native `build/server.dll` SHA256
`bff0b0fdc5e4ec0f2def61d6222e38f02013e808e45142b08329415454c50a26`,
270336 bytes,3647 overlapping differences,16384 bytes short. Native CMake
equals the complete validated candidate. The captured193-input manifest
shows one changed source object,191 unchanged inputs including native EXP,
and no input-set change. Code/readonly/data/reloc differences2042/1270/54/0,
improving161 CODE bytes and eight data bytes. Fifty-five allocator operands
and two zutil initializer fields become exact; no previous exact field is
lost. All53248 relocation raw bytes remain the exact reference prefix.

Data VS0x173f7d0 is32 bytes smaller through actual BSS removal/allocation,
now3532 short. Reloc VS0xc870 remains15108 short. Stored/computed checksum
0x47cd2; e_lfanew0xe0. Readonly bytes and every import identity/hint/slot
remain unchanged;23 IAT slots are still displaced. A fresh complete native
verbose trace selects exactly the same137 stock CRT members and produces
the same DLL. Current storage audit covers192 C objects and137 CRT members.

Fresh full verification2026-10-02 09:23:28 UTC:262/262 passed,
22EXACT/240RELOC including two library checks,zero failures or size
divergences. Data531matched/67mismatched/7missing/3unchecked. Status
09:24:04 UTC is current (stale=false):93.0% file agreement,
266689/286720 bytes,260/339 reversing progress,99.4% accounted text.
Stored data remains498verified/12drift/3unchecked,27020/66664 verified
bytes and36713 conflicting verified bytes; distinct from raw comparison.
All three targets lint4122passed/zero errors/zero warnings. Native build
check192objects/zero drift; coverage regenerated for all three targets.
Whole-binary and independent strict objective correctly fail full identity.

Evidence: `.scratch/native-allocator-common/{probe.py,validate.py,audit.json,
shapes.json,accepted-checks.json,gates.json,canonical-ownership-audit.json,
canonical-verify.json,canonical-status.json,canonical-lint-all.json,
canonical-coverage.json,canonical-objective.txt}`, captured before artifacts,
native common-gap verbose trace, and `storage/{audit.json,operands.json}`.
Prior direct Rebrew cache/CMake/source-order fixes and the pinned wheel
remain intact; no new shared implementation defect is found. Goal incomplete.

## 66. A measured server flag fits beside the clock run without moving other COMMONs

The pool/count/counter owner control is rejected: four complete native
objects preserve all runtime contributions and twelve total BSS bytes,
but the three separate four-byte owners only rearrange displaced ordinary
BSS. Whole-file differences remain3647; no exact operand gain/loss. The
original pool's guessed eight-byte IDA extent is not proved by its observed
one-word root contract. C-shapes242 documents the full callee evidence.

Promote only the actual server-stop flag's tentative definition in its
existing `server.c` owner and its ORDER entry before the four clock fields.
The flag binds at10034680; clock year/hour/mid/tail bind at34684/34688/3468c/
34690, preserving the0/4/8/12 cross-field access geometry. The sixteen-byte
clock run ends before the unchanged slot table346a0. Ninety-nine other
COMMON bindings stay fixed. Seven flag fields become exact with no lost
exact field;28 removed CODE byte differences versus26 added coincident
clock-byte differences gives a two-byte whole-file improvement.

Current native `build/server.dll` SHA256
`9642a1dc31004e7effc7383de6ac9b471c83fe2c475f03916ef3db70e4fa3e8f`,
270336 bytes,3645 overlapping differences,16384 bytes short. Raw text/rdata/
data/reloc differences2040/1270/54/0. Data VS0x173f7c8 is3540 bytes short;
reloc VS0xc870 is15108 short. Stored/computed checksum0x4c5a0. All597
function bindings,3499 live HIGHLOW sites and non-fixup CODE bytes stay
fixed. Readonly and all53248 emitted relocation bytes are unchanged;
relocation bytes remain an exact reference prefix. All import identities,
hints and slots are unchanged;23 slots remain displaced. All five complete
data/value guards pass.

Actual CMake output equals the validated native candidate. The193-input
manifest has one changed C object,191 unchanged C objects and unchanged
native EXP:192 other direct inputs. Earlier wording that said191 other
direct inputs including EXP conflated the C-object and direct-input counts.
No new object/provider/storage, enlarged array, padding, patched stock
object/archive/reference or postlink operation. A fresh full native verbose
link reproduces the canonical DLL and selects the same137 stock CRT
members, with no duplicate-symbol warnings. CRT remains stock-linked.

Full verification before the tooling correction,2026-10-02 10:00:17 UTC:
262/262 passed,22EXACT/240RELOC including two library checks,zero failures
or size divergences. All three targets lint4122passed/zero warnings/errors;
build-check192objects/zero drift. Whole-file equality remains false.

That run also exposes a shared Rebrew accounting defect: configuration
already declares `raw_link = "build/server.dll"`, but an explicit `--built`
of that same image bypasses acknowledgement and suppresses managed data
verdicts. Fix directly in sibling Rebrew's shared verify callback: select
the configured default when needed, then acknowledge equal resolved paths.
Other paths still require the explicit flag, including files with identical
bytes. Six existing-test variants fail two cases before the fix and pass
after it;116 verify CLI/watch/text tests, Ruff and targeted mypy pass.
Configuration documentation and changelog are updated. The project wheel
changes only `rebrew/verify.py` and RECORD; previous package repairs remain.
Current post-fix verdict/status metrics are recorded in HANDOFF.

Evidence: `.scratch/native-vfs-storage-owners/{audit.json,accepted-checks.json,
gates.json,canonical-ownership-audit.json,canonical-verify.json,
canonical-verify-raw.json,raw-link-tooling-audit.json}`, before manifest,
both complete native controls and `canonical-verbose/{argv.json,link.log,
audit.json}`. Reproducible shared patch:
`docs/rebrew-patches/raw-link-acknowledgement.patch`. The strict goal stays
active/incomplete.

## 67. BSS section suffixes do not solve the early-CRT and late-COMMON boundary

C-shapes243 varies one real64-byte declaration in a bounded native toy,
keeping all three DWORD definitions, one full code object and four fixups
fixed. Default COMMON has24 bytes of native alignment; ordinary BSS avoids
that alignment. Suffixed `.bss$G`/`.bss$0` place the default late COMMON
before the game array. Unsuffixed `.bss` and default explicit zero put it
after the game array. This distinction matters: the reference has ordinary
CRT storage before bulk game storage, and stock CRT COMMONs after it.

Naming an uninitialized contribution `.data` or `.data$...` instead emits
LNK4078 and two same-named data sections at different RVAs. Neither matches
the configured reference's single data section. Changing the suffix's sort
character does not fix the root/attribute conflict in these tested cases.
No section recipe is promoted. The toy's extra virtual page increases
relocation reservation10 bytes, with unchanged fixup count/sites; storage
extents, native alignment and section-page geometry are distinct measures.

The final eight-control audit validates actual virtual BSS ranges, complete
fixed CODE, four live sites, and before/after canonical hashes. The initial
unsupported timestamp option and raw-BSS-read assertion are corrected;
the only final warnings are the expected attribute findings. No Rebrew
implementation defect is established by those harness/native diagnostics.
Evidence: `.scratch/native-bss-group-order/`. Current canonical9642/3645/
16384B short is unchanged.

## 68. Sole game providers in native archives expose two separate ordering constraints

The39 actual game definitions can be removed from their eight owners and
provided once by native C/LIB output without changing any complete runtime
reader object. Unlike50's duplicate-provider diagnostic, these controls
have no duplicate COMMONs. Their types and total24316040 logical bytes stay
fixed; neither stock archive nor any compiler object is edited.

One explicit-zero ordinary-BSS provider has12 internal alignment bytes.
Its complete native link preserves597 function positions,3499 live sites,
all non-fixup CODE bytes, every import identity/hint/slot, readonly and
relocation bytes, and all five complete value guards. It selects the same
137 stock CRT members and emits no linker warning. But game alignment and
placement change: clock at10034ab0, slot table10034ac0. File differences
worsen3645->4269, rawtext/rdata/data/reloc2688/1270/30/0. Data VS0x173f71c
is3712 short,172 smaller than canonical. SHA256
`b17dc949d7146b6dd32349ba1920198095639d58c6fd91ec3fac56d236385c1b`.
Do not promote it merely because data-only differences improve.

Thirty-nine sole COMMON providers retain native COMMON alignment. Native
LIB archives with opposite physical member orders preserve identical COFF
payloads. Unrooted links have identical entire DLLs despite this reversal.
Reference-order INCLUDE roots reverse the game sequence and violate clock
geometry. Reversed roots recover the game sequence. In these four cases,
game allocation reverses the measured native member load order; do not
infer the linker's general internal selection algorithm.

| Archive control | File differences | Data VS | Raw text/data differences |
| --- | ---: | --- | --- |
| Reference physical member order, unrooted | 5073 | 0x173f7e8 | 3488 / 34 |
| Reversed physical member order, unrooted | 5073 | 0x173f7e8 | 3488 / 34 |
| Reference-order roots | 5865 | 0x173f7f0 | 4280 / 34 |
| Reversed roots, archive after LIBCMT | 3911 | 0x173f808 | 2326 / 34 |

The reversed-root archive case restores the39-field sequence but places
stock `_bufin` at10034e60 rather than reference11766580. Its existing4096
bytes precede the game block: the35 bulk fields move1536 bytes beyond their
reference positions, while four clocks move1532. This existing real buffer
cannot be treated as replacement storage for the unknown early span.

Five further native links reuse the already validated provider objects:

| Provider input position, reversed roots | File differences | Data VS | Raw text/data |
| --- | ---: | --- | --- |
| Archive immediately before LIBCMT | 4113 | 0x173f7fc | 2532 / 30 |
| Archive before direct objects | 4113 | 0x173f7fc | 2532 / 30 |
| Archive after all libraries | 3911 | 0x173f808 | 2326 / 34 |
| Direct39 objects before original objects | 4113 | 0x173f7fc | 2532 / 30 |
| Direct39 objects after all libraries | 4191 | 0x173f7fc | 2610 / 30 |

The first, second and fourth are identical entire DLLs, SHA256
`1665535e9cf458ebe7d78b2e57d9c3a541d7debdcfc8ed23fcbe1815cf746e14`.
They keep the39-field game sequence and stock buffer after the game block,
but the slot table10034b00 remains3488 bytes too early. The late archive
equals the earlier3911 control. Late direct objects give different bytes
despite identical final VS; clock/slot are34ab0/34ac0. These are bounded
native input-position results, not interchangeable general rules.

All five input-position links preserve597 function positions,3499 sites,
fixed CODE/data bytes, all imports, readonly/relocation bytes and all five
complete value guards; clock geometry holds. All select the same137 stock
members, without linker warnings. The unrooted archive has those checks
too; its reversed-member counterpart has identical bytes. Reference roots
are rejected specifically at the clock check before the five guards.
Every control remains16384 bytes short. No control beats canonical3645;
none is promoted. The unexplained original storage and alignment remain
unresolved, rather than authorizing extra arrays, providers or padding.

Evidence: `.scratch/native-game-data-archive/`, complete C/COFF/nativeLIB/
DLL/MAP/argv/log sets, shape proofs, full validators and root/input-order
audits. Canonical source, compiler inputs, stock libraries and DLL are
unchanged. No new shared Rebrew implementation deficit is exposed.

## 69. Native header controls retain Rich data; BREPRO changes the timestamp

Five fresh LINK 6.00.8447 controls reuse two unchanged native objects with
48 CODE bytes and four fixups. They run through the configured Docker
wrapper with `/DLL /NOENTRY /NODEFAULTLIB /INCREMENTAL:NO /OPT:REF /RELEASE`
and frozen `SOURCE_DATE_EPOCH=1771046057`. All native links exit 0 and all
stored checksums equal independently computed checksums.

| Additional option | Measured result |
| --- | --- |
| None | Rich present, e_lfanew 0xb0, COFF characteristics 0x210e |
| `/BREPRO` | Same header geometry and Rich; timestamp 0xffffffff |
| `/DEBUGTYPE:FIXUP` | Entire DLL identical to the default control |
| `/DEBUG /DEBUGTYPE:FIXUP /PDB:NONE` | LNK4075 ignores FIXUP; adds a 56-byte debug directory |
| `/HDRSIZE:0x80` | Entire DLL identical to the default control |

All five retain Rich, e_lfanew 0xb0, characteristics 0x210e and 4,096-byte
SizeOfHeaders. Other than BREPRO, timestamps remain 1771046057. Debug mode
adds a virtual section page and changes relocation VS 28->38; fixup count
remains four. None produces the configured reference's Rich-free header
and 0x230e characteristics. These small controls establish only their
measured behavior, not impossibility for every native input recipe.

The image search found no separate DOS-stub file. Its LINK.EXE contains a `nostub`
string in the EDITBIN option table; that does not establish a LINK option.
EDITBIN is not invoked. Native `LINK /?` prints its help and exits 76;
inspection does not establish a wrapper/path-translation defect.

Default SHA256 3fc6c637397c84fcdadfcf36e6c0f9ff31675b8b11168231bb3031540cdd5234;
BREPRO a5a2b1fd7a65f766aeb4d31040810a15f3b3aad4901f8b620017c3474463978b;
debug d209fb95d0510958799b8f4f5d3ad11a8af8814ead74ea65652cd45994bd80dc.
Evidence: `.scratch/native-header-recipe/{probe.py,audit.json,link-help.txt}`
and all five native DLL/MAP/argv/log sets. No full-server recipe is promoted;
canonical 9642/3,645 differing bytes/16,384B short remains unchanged.

## 70. Layout freshness must hash the actual saved PE headers

The native default and BREPRO DLLs have different timestamps/checksums but
the old Rebrew `layout_fingerprint` returns the same 530c89cd...ae1fc hash.
It hashes only section names/VA/size/raw-size and image base, despite its
docstring promising headers. Consequently `check_layout_freshness` labels
a package recorded against default as fresh against BREPRO. Whole-file
comparison already rejects those DLLs correctly; that gate is unchanged.

Fix the shared function directly in sibling Rebrew using existing
`pe_headers.pe_layout`: include bytes from file start through the complete
section table, exactly the header extent saved by `layout_meta.extract_layout`.
This covers DOS/Rich bytes, COFF/optional fields, raw pointers, attributes
and section order. Section contents remain excluded. No new header parser,
CLI option or compatibility hash is introduced. Existing generated hashes
become stale and require regeneration; an absent legacy stamp still reports
unknown. The canonical layout has no stamp and is not silently stamped or
regenerated over its customized source inputs.

One parametrized regression checks DOS bytes, timestamp, section raw pointer,
attributes and CODE contents for PE32 and PE32+. Before:8failed/2passed;
after: all 10 pass. The 86 focused binary-gate/gen-layout/layout tests, Ruff
check/format and targeted mypy pass. Native-pair reproduction changes from
fresh/fresh to fresh/stale; neither native DLL is edited.

Patch: `docs/rebrew-patches/layout-header-fingerprint.patch`, applied to
the pinned 9123ca68 source after the existing fixes. Installed wheel
`build/tooling-wheels/layout-header-fingerprint/rebrew-2.19.0-py3-none-any.whl`,
SHA256 b452a58fcf5b44d830409e4c4b3574a52d7c69ab191d0545de957a574b78048b.
Only `rebrew/binary_gate.py` and RECORD differ from the preceding e8c40 wheel.
Evidence: `.scratch/native-header-recipe/fingerprint_audit.py`,
`fingerprint-{before,after}.json`, regression logs and `wheel-audit.json`.
This is a comparison/freshness repair, with no new native file-byte gain.

## 71. SP5's normal PE path always builds Rich; ROM bypass changes the format

Trace the unchanged image's LINK.EXE, SHA256
`9672e578fdfaa43bdb8e9c16071682988665cb90bba2904bf02f6a5576d8ffbc`,
with read-only Rizin and Capstone. There is no plaintext `DanS` or CODE
`Rich` immediate because the signature constants are stored encoded:

| LINK VA | Stored DWORD | XOR with 0xaa559966 |
| --- | --- | --- |
| 0x4693b0 | 0xf93bf822 | 0x536e6144, `DanS` |
| 0x4693b4 | 0xc236f034 | 0x68636952, `Rich` |

The builder at 0x43fdd0 counts unique compiler identifiers in loaded inputs
and constructs the key from the actual DOS-stub bytes and identifier counts.
The default stub is the existing 128-byte array at 0x406eec; its stored
length is at 0x406f6c. For this template the rotated-byte sum plus its length
is 0x884f3421. Add each compiler identifier rotated by its count, using x86
32-bit rotation and wraparound. The resulting key matches native and stock
files exactly; it does not depend on the COFF output timestamp.

After counting `N` distinct identifiers, the builder allocates and returns:

```
extra_header_bytes = 32 + 8 * (N + ((key >> 5) % 3))
e_lfanew = input_DOS_stub_bytes + extra_header_bytes
```

The native encoded Rich structure occupies `24 + 8*N` bytes; the remaining
`8 + 8*((key >> 5)%3)` bytes are native zero tail bytes. This explains header
size changes without guessing extra object counts or supplying manual padding.
The audit checks the entire existing stub, encoded structure and zero tail.

| Existing file | Key | N | Key-derived slots | Extra bytes | e_lfanew |
| --- | --- | ---: | ---: | ---: | --- |
| Current native server | 0x2e6cd894 | 8 | 0 | 96 | 0xe0 |
| All five header toy controls | 0x8877c039 | 1 | 1 | 48 | 0xb0 |
| Matching stock distribution server | 0xc3b8ddfa | 8 | 1 | 104 | 0xe8 |

These are seven complete checked images. The stock file has SHA256
3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1.
The configured reference has the same default stub, with e_lfanew 0x80,
followed immediately by PE headers. It has no Rich block. Its earlier
285-byte header-only difference from matching distribution copies remains
established; all four raw sections still agree with those copies.

The ordinary PE build path at 0x445806 invokes the builder, adds its result
to the stub length, and later writes the stub and Rich buffer and stores the
new e_lfanew at file offset0x3c. The bypass is the ROM flag at context+0x147,
set by the `/ROM` option at 0x4493ce. The PE header callback at 0x45c180 also
uses this flag to omit the DOS/PE prefix. Thus removing compiler tags or
changing a stub does not turn this valid ordinary PE path into Rich-free PE
output. No executable, object, archive or reference is patched.

The exact pointer/length handoff is also checked: the builder receives the
address of `[esp+0x24]` at 0x445810, and its returned length is saved at
`[esp+0x14]` at 0x445822. The ordinary path loads that pointer at 0x445c6a
and that length at 0x445c9a before writing. This uses actual instruction
operands; preliminary Rizin stack-variable names were inconsistent across
the long function and are not used to establish the handoff.

One new native `/ROM /DLL` control reuses the two unchanged toy objects.
LINK exits 0 without warnings and emits 1,536 bytes, SHA256
603bf1e84772e45c8e2d9c09065a87e550e7678ef08a9c238953dff038b9d7f0.
The file begins `4c 01 02 00` (COFF machine/section count), has no MZ prefix
and is not parsed as a PE. A successful native link therefore does not
resolve the configured server's header mismatch. This bypass is rejected.

The BREPRO handler at 0x4471a4 sets global byte 0x480f6c. The x86 PE path at
0x445834 tests it and substitutes timestamp 0xffffffff for `time()`, confirming
69's observed behavior. A PowerPC-only user of that flag was inspected too;
it is not a Rich writer. Indirect format callbacks required explicit local
Rizin `af` before disassembly; this is not an established Rebrew defect.

Evidence: `.scratch/native-header-writer/{trace.py,audit.py,audit.json,
rom_probe.py}`, six complete relevant disassemblies, xref JSON, native ROM
DLL/MAP/argv/log/audit and seven-image algorithm checks. The traces locate
the actual builder and emitter; filenames from preliminary traversal are
not evidence of their function roles. The known normal SP5 PE path cannot
produce the configured Rich-free header while retaining the required format.
Canonical output remains unchanged at 3,645 differences and 16,384B short;
reference selection remains unchanged pending the earlier user clarification.

## 72. Natural import selection improves the complete file despite more IAT displacement

Reassess58's no-seed control against the current3645-difference baseline.
The objective is complete file equality. Preserving each already exact IAT
operand at the cost of846 other differing bytes is not a requirement of
that objective. The measured natural-import control is therefore promoted,
with the losses recorded explicitly.

Delete the directive-only `crt_imports.c` and its CMake keep/prefix entries.
All100 imports are retained by actual references and unchanged stock
libraries. No runtime function body, source signature, data owner, library,
link option, reference or executable is patched. The scratch native link
and terminal CMake output must agree exactly; no postlink step is involved.

| Measurement | Before | Natural references |
| --- | ---: | ---: |
| Overlapping differing bytes | 3645 | 2799 |
| File agreement, including missing tail | 93.0% | 93.3% |
| Raw `.text` differences | 2040 | 2156 |
| Raw `.rdata` differences | 1270 | 308 |
| Raw `.data` differences | 54 | 54 |
| Raw emitted `.reloc` differences | 0 | 0 |
| Displaced IAT slots | 23 | 69 |
| Function MAP bindings | 597 | 597 |
| Live HIGHLOW sites | 3499 | 3499 |

Every changed HIGHLOW value is checked against the old IAT identity and
its new slot:155 fields retarget, all to the same imported API. Every
other HIGHLOW value stays identical. Five fields become exact and115 lose
exact values. All non-import public bindings, including every game/CRT
storage owner, stay fixed. All CODE differences are inside reference
HIGHLOW fields; every readonly change lies in one of the five native
`.idata` groups. The five complete data/value guards pass. All137 selected
stock CRT members are unchanged, with no native linker warning.

The comment-only intermediate DLL SHA256 is
5c7a050b8bbbd0abbe357caafadaab6ba69da049fc857146f7110ce37101177a.
Removing its empty input gives SHA256
f3b3faa4176605cba1e47a99f67d7ce79d4701258d769c709d78f046b397e87c.
Those two files differ only in65 header bytes, have the same2799 overlap
differences and remain16384B short. The final native checksum is0x423f7.
Data VS remains0x173f7c8 (3540B short), relocation VS0xc870 (15108B short),
and e_lfanew0xe0. All53248 emitted relocation bytes remain the exact
reference prefix. The reference, stock archive and required format stay
unchanged; whole-file equality remains false.

The initial CMake build with the comment-only source recompiles just that
object and preserves the other192 direct-input hashes. The final removal
changes the global flags/source list and triggers native recompilation;
do not carry that hash-preservation claim into the terminal recipe.
C-shape246 documents this and the one-count Rich change. No new shared
Rebrew implementation deficit is established by E001 for the empty source.

Evidence: `.scratch/native-import-natural/` complete before/input manifest,
C/COFF shapes, two complete native links, full semantic import audit,
five guards, CMake logs, verification/lint/build-check/coverage/status and
independent objective reports. Reproduce the semantic comparison with
`audit.py` and `no-empty-object/audit.py`; they use the captured before DLL.

Terminal validation: native CMake equals the no-empty-object candidate
exactly. All191 retained C objects were recompiled; their hashes change,
and the native export object's hash remains unchanged. Build-check checks
191 objects with zero drift. Fresh final verify at2026-10-02T12:17:11 UTC
passes262/262 (22EXACT/240RELOC, including two library checks), with zero
failures or size divergences. Raw data compares534 matched,64 mismatched,
seven missing and three unchecked; the managed target summary remains
499verified/11drift/3unchecked. All three targets lint4121 passed with zero
warnings/errors. Three coverage documents are regenerated after terminal
verification. Whole-binary and independent objective correctly exit1.
Every check uses the same configured reference and raw native DLL.


## 73. Import contributions are sorted through the tool runtime's qsort

Read-only tracing of the unchanged SP5 LINK.EXE establishes a concrete
ordering step. Its SHA256 is
9672e578fdfaa43bdb8e9c16071682988665cb90bba2904bf02f6a5576d8ffbc.
The layout pass at0x442020 selects `.idata$4`/`.idata$5` groups and calls
0x40f580 at0x4422a9. That helper gathers contribution pointers, then calls
the imported `MSVCRT.dll!qsort` at0x40f5d6 with element size4 and comparator
0x40f630. The comparator follows contribution+0x18 to the module, then
module+4 to its filename. Equal strings return0: there is no symbol-name
secondary comparison in this function. The following helper at0x40f680
regroups adjacent entries with equal module filenames.

This supersedes section4's blanket hash-order claim. Equal-key ordering can
depend on the runtime's sorting implementation and the input list. Wine8.0's
[MSVCRT implementation](https://raw.githubusercontent.com/wine-mirror/wine/wine-8.0/dlls/msvcrt/misc.c)
explicitly describes remaining comparison-order differences from Microsoft.
The trace and runtime controls establish a real runtime dependency; they do
not prove qsort is its only cause, nor completely recover `.idata$6` ordering.
Use actual instruction operands rather than Rizin's inconsistent stack labels.

Six saved native `/INCLUDE` controls reuse the natural-import2799 baseline:

| Additional roots | Differing bytes | Displaced IAT slots | Result |
| --- | ---: | ---: | --- |
| `__imp__GetLocalTime@4` | 3528 | 95 | Worse; complete semantic checks pass |
| `__imp__WriteConsoleA@20` | 2799 | 69 | Entire DLL unchanged |
| `__imp__GetLastError@0` | 3546 | 96 | Worse; complete semantic checks pass |
| `__imp__GetCPInfo@8` | 4113 | 95 | Worse; complete semantic checks pass |
| All16 WinSock IAT roots in reference order | 2808 | — | Six thunk function bindings move; rejected |
| The same16 roots reversed | 2806 | 71 | Worse; complete semantic checks pass |

These are concrete rejected recipes, not evidence that `/INCLUDE` can never
influence ordering. All preserve the100 import identities, DLL order and hints
and issue no native linker warnings. None is promoted.

Two isolated full-link controls instead install whole, unchanged Microsoft
runtime DLLs in copied Wine prefixes, leaving the canonical prefix untouched:

| Tool runtime | Version | SHA256 |
| --- | --- | --- |
| Local original VC6 DLL | 6.0.8168.0 | fb6260b07c05bdbcb6928156da514be5b6b69f095b335692ba46c561d85bd5f8 |
| Official VC6 redistributable DLL | 6.0.8797.0 | 887eb5ce93edb7192ca3e9220f07f9ca0f94db02af5862ebcbdfcb852db99fd1 |

The saved loader trace identifies LINK's process loading native MSVCRT, not
merely Wine's startup processes. Both controls emit the identical270336-byte
DLL, SHA256 d337d847b8a75319ae4de07faf0e9a15127dcc3305ded312914032c7d119a4ea:

| Measurement | Canonical Wine runtime | Microsoft runtime control |
| --- | ---: | ---: |
| Overlapping differing bytes | 2799 | 2775 |
| Raw `.text` differences | 2156 | 2138 |
| Raw `.rdata` differences | 308 | 302 |
| Raw `.data` differences | 54 | 54 |
| Raw emitted `.reloc` differences | 0 | 0 |
| Displaced IAT slots | 69 | 59 |

All597 function MAP bindings,3499 live HIGHLOW sites, storage bindings and
nonfixup raw CODE bytes stay fixed. All162 changed fixup values still point to
the same API identities. Thirty-four complete fixup fields become exact and
five lose exact values. The same137 stock LIBCMT members are selected, with
zero linker warnings; all five data/value guards pass. The53248-byte emitted
relocation prefix remains reference-identical. The16384-byte missing tail,
`.data` VS0x173f7c8 and `.reloc` VS0xc870 remain unchanged. The native checksum
is0x51f9a. Complete file agreement is93.31787109375%; equality is false.

The new opt-in `msvc-6.0-sp5-crt` recipe pins
[Microsoft's VC6 redistributable](https://download.microsoft.com/download/vc60pro/Update/2/W9XNT4/EN-US/VC6RedistSetup_deu.exe)
to SHA256 c2eb91d9c4448d50e46a32fecbcc3b418706d002beab9b5f4981de552098cee7,
extracts and verifies the complete DLL, and installs it beside unchanged tools
with `WINEDLLOVERRIDES=msvcrt=n,b`. No target archive is modified. Its saved
image build succeeds with SHA256
5a62502de66853510cce040080a16ca0065f0277065ed7154a581c37cfc44f3a.
The manifest, generated Dockerfile/wrapper and catalog provenance live in the
sibling toolchains checkout. An existing project TOML overlay registers the
experimental profile; no Rebrew implementation change or wheel replacement
is necessary. Default CL/LINK and the canonical DLL remain unchanged.

The later Docker restriction prevents the remaining image smoke compile and
canonical CMake link. Do not report this scratch gain as a promoted build or
claim fresh function verification. All159 offline Rebrew toolchain/CMake tests
and16 catalog/generation tests pass. The project overlay resolves through the
installed pinned wheel. No canonical staging or fabricated smoke golden.

Evidence: `.scratch/native-import-incremental/` six complete recipes/results;
`.scratch/native-import-writer/` full comparator/layout traces, both runtime
links, compiler controls, image build, runtime archive and extracted DLL;
`native-redist/offline-audit.log` repeats the full saved-file semantic audit
without invoking Docker. The canonical reference and all192 direct input
hashes remain fixed during this restricted pass.


## 74. Smoke bootstrap needs a recipe, not an assumed golden

The experimental runtime overlay exposes a real Rebrew deficit before any
Docker execution: `toolchain smoke --print-goldens` directly indexes
`_SMOKE_GOLDEN[tool]`, raising `KeyError` for a registered overlay profile.
The sibling update helper has the same unchecked lookup. Both paths also
accept an existing object without requiring a zero container exit status.
A failed command must not supply byte-reproducibility evidence.

Fix these paths directly in sibling Rebrew's `toolchain_cli.py`. Add the
explicit `--fixture` option for a named profile with `--print-goldens` only.
It borrows the fixed source, flags and timestamp mask from a known recipe,
then reports the new profile's measured object hash. It neither compares
against nor stores the fixture profile's expected hash. Missing recipes
produce an infrastructure result instead of a traceback; the update helper
returns no hash. Missing runners and nonzero exits also fail as infrastructure.
Remove any previous output before each attempt. Existing default golden
comparisons and the two-run update stability check retain their contracts.

The future native measurement command is:

```sh
REBREW_TOOLCHAIN_OVERLAY_DIR="$PWD/cmake/toolchain-overlays" \
  .venv/bin/rebrew toolchain smoke msvc-6.0-sp5-crt \
  --fixture msvc-6.0-sp5 --print-goldens --json
```

This command is documented, not executed under the Docker restriction.
A genuine measurement still needs two native runs before registering a golden.

Six initial new regression cases fail before the fix; the four existing smoke
checks pass. After the fix, expanded failure checks and the complete focused
suite pass167 tests. The runner is mocked for these checks: they verify recipe
selection, actual target image, masking, missing fixture handling, prohibition
on borrowed comparison goldens, missing executables and nonzero exits with an
object present. Ruff check/format and targeted mypy pass.

Patch: `docs/rebrew-patches/smoke-profile-bootstrap.patch`, including source
and regression tests. Apply to the pinned9123ca68 source, build using its
pinned setuptools80.10.2, and install noneditable without dependency changes.
Installed wheel `build/tooling-wheels/smoke-profile-bootstrap/rebrew-2.19.0-py3-none-any.whl`
has SHA256 01e4e8bd4c33eecdfbd2c72b40e6efe9c0b0ee9e0fc08f21ab41047422e49bc3.
Compared with b452a58, only `rebrew/toolchain_cli.py` and RECORD differ.

The first package audit catches a no-op Git patch in the nested source tree:
its wheel payload remains identical to b452a58. Apply the reviewed patch with
filesystem `patch`, then rebuild and check the payload before delivery. The
corrected wheel's installed command passes the mocked measurement assertion;
the actual missing-fixture invocation returns a controlled JSON result with
exit2 before any Docker call. No smoke golden is fabricated.

No source/body, stock library, reference, CMake linker recipe or canonical DLL
changes. The production artifact remains f3b3faa4...e87c at2799 overlapping
differences and16384B short. No fresh native verification is claimed. The saved
Microsoft-runtime candidate remains unpromoted pending real image measurement
and canonical linking. All-target lint still passes4121 checks without warnings.
Evidence: `.scratch/native-import-writer/smoke-{fixture-before,fixture-after,
all-tests,wheel-build}.log`, wheel audit, installed assertions/help,
controlled-error JSON and installed lint report.

## 75. Native Microsoft runtime and WinSock roots are now production inputs

The user clarified that Docker should run. The earlier avoidance condition
was a misunderstanding, now superseded. Docker29.8.1 is accessible; actual
image smoke compilation and canonical CMake linking complete successfully.
Keep the configured reference and stock archives unchanged.

Two real smoke runs through `msvc-6.0-sp5-crt`, using section74's explicit
recipe fixture, produce the same masked object hash:
`547b88f827c13e9273f46b1a72415002289fac62d0f65dc0ef9289dbc5a3e546`.
This also equals the measured plain-SP5 golden. CL, LINK and LIBCMT hashes in
the new image equal the plain-SP5 inputs. A loader trace identifies LINK's
process loading the native app-directory MSVCRT; Wine startup processes
loading builtin MSVCRT do not contradict this. LINK's help invocation exits76
after displaying help, whereas the actual complete links exit0.

Promote the runtime for LINK only. CMake's existing `RULE_LAUNCH_LINK` supplies
`REBREW_TOOLCHAIN_OVERLAY_DIR`, and the existing bridge consumes
`/REBREW_TOOLCHAIN:msvc-6.0-sp5-crt`. CL stays on plain SP5. The canonical
270336-byte DLL first reproduces section73's saved d337d847...a4ea output
exactly, reducing overlapping differences2799->2775. All192 direct inputs
(191 C objects plus the native EXP) retain their complete hashes; no source
object recompiles. No new profile registry or default compiler change.

Repeat section73's six import-root controls under this changed tool runtime:

| Additional roots | Differing bytes | Displaced IAT slots | Result |
| --- | ---: | ---: | --- |
| GetLocalTime | 3493 | 81 | Semantic checks pass; worse |
| WriteConsoleA | 2775 | 59 | Entire DLL unchanged |
| GetLastError | 3510 | 81 | Semantic checks pass; worse |
| GetCPInfo | 4078 | 81 | Semantic checks pass; worse |
| All16 WinSock IAT roots in reference order | 2815 | — | Function bindings move; rejected |
| The same16 roots reversed | 2748 | 51 | Semantic checks pass; promoted |

The reversed WinSock roots precede the existing public thunk/CRT anchors in
`native-archive-includes.rsp`. They are genuine existing import identities,
not a new C translation unit or synthetic archive. All16 WinSock IAT slots
now equal the reference. Eleven complete HIGHLOW fields become exact and
none loses an exact value. The response-file candidate equals the inline
control; an actual CMake LINK-only build equals that complete candidate.
All192 direct input hashes remain fixed. This result supersedes the old Wine
runtime's rejected reversed-root control; root order depends on runtime too.

Four complete81-root KERNEL32 controls (reference IAT/name order and both
reversals) move281 function bindings and worsen the file to41722–42350
differences. Explicitly rooting `__imp__RtlUnwind@16` brings its real thunk
from0x10023840 to0x1001a160, disturbing subsequent thunk/function alignment.
Exclude that root while keeping the natural stock CRT reference: all four
80-root controls then pass the complete semantic audit, but remain worse:

| KERNEL32 roots without RtlUnwind | Differences | Displaced IAT slots |
| --- | ---: | ---: |
| Reference IAT order | 3656 | 27 |
| Reversed IAT order | 4436 | 98 |
| Reference hint/name order | 3817 | 71 |
| Reversed hint/name order | 4429 | 98 |

Fewer displaced IAT slots alone is insufficient: the first control worsens
readonly bytes286->1270. None of these KERNEL32 controls enters production.

Current canonical SHA256:
`715ae25d1882f26d7c994975c2018c613ecf1ce4e6fdf64c813eb0ed545d0158`.
There are2748 overlapping differing bytes,16384 missing bytes, and
267588/286720 identical file bytes (93.3272879464%). Raw
`.text/.rdata/.data/.reloc` differences are2127/286/54/0. All597 function
bindings,3499 HIGHLOW sites, non-import public/storage bindings, and every
nonfixup raw CODE byte remain fixed. All100 imports/hints/DLL order remain
correct;51 KERNEL32 IAT slots remain displaced. The same137 stock CRT members
are selected, with no linker warnings. All five value guards pass. The53248
emitted relocation bytes equal the reference prefix. Native checksum0x50bb2
is valid; `.data` VS0x173f7c8 and `.reloc` VS0xc870 remain short3540/15108B.

A residual operand census finds1262 differing non-IAT HIGHLOW fields, all
targeting `.data`;917 have reference-minus-native target delta0x1200.
For example the actual log buffer is11764f00 versus reference11766100.
Its proven260-byte extent is unchanged. A shared displacement establishes
placement error, not permission to enlarge an array or invent missing storage.

Fresh verification at2026-10-02T14:38:05.904787+00:00 passes262/262 functions
(22 EXACT/240 RELOC, including two library checks), with no size divergences.
Raw data comparison is550 matched/48 mismatched/seven missing/three not
comparable. Stored target data accounting is499 verified/11 drift/three
unchecked; these are different populations. All-target lint passes4121 checks
per target without warnings/errors; build-check covers191 objects with zero
flag drift. All three coverage documents are regenerated; status is not stale.
Whole-binary and independent whole-file checks correctly fail. Neither these
promotions nor Docker access resolves the established Rich-free-reference
header conflict, original missing storage, or relocation reservation extent.

Evidence: `.scratch/native-import-writer/native-image-proof.json`, both
`smoke-native-*.json`, `native-image/` full audit/loader trace/canonical build;
`.scratch/native-import-runtime-roots/` six controls, immutable before files,
response-file reproduction, CMake log, promotion, and final verify/status/lint/
coverage/build-check/objective reports; `.scratch/native-kernel-runtime-roots/`
and `.scratch/native-kernel-runtime-roots-no-unwind/` complete controls/audits.

## 76. SP5's reservation path caps fixup space independently of missing BSS

Reference-choice statements in this checkpoint are superseded by section77.
The reservation/emitter instruction evidence remains valid.

Read the unchanged LINK.EXE with SHA2569672e578...ffbc. This adds primary
instruction evidence to sections63–64's empirical model; no compiler/linker
execution or production edit is needed for this analysis.

The normal PE layout path at0x440ede reads context+0xd0, doubles it, and
stores that initial reservation in the `.reloc` section record. Context+0xd0
is the PE relocation directory's Size field: COFF Machine is at context+0x30
and the optional header starts at+0x44. Before emission, this directory field
temporarily holds the potential-fixup counter. At0x4391d4 it receives the
accumulated object counter as well as the existing synthetic counter.

At0x440ee9–0x440f1a, the path computes page span from page-aligned BaseOfCode
(context+0x58) to the current `.reloc` start, clamps that page count to the
potential counter, and adds ten bytes per clamped page. For this path:

```text
reservation = 2*N + 10*min(N, ceil((reloc_start - floor(BaseOfCode/4096)*4096)/4096))
```

This is a contiguous image-span bound, not a general sum of per-section
pages. The earlier control set's page sums agree with that span. Other mode
branches exist: context+0x13e can add section-dependent space, and0x440f40
checks additional globals before an incremental-space extension. Do not
generalize this bounded path to arbitrary link modes or architectures.

A fresh census of the current192 direct inputs and137 actually loaded stock
CRT members finds4167 DIR32,512 DIR32NB and2450 REL32 records. The saved
validated native trace contains109 loaded import members. Thus the same
independently counted potential total is4276. Its page span is5990, above
that counter, giving exactly12*4276 =51312 reserved bytes. Correcting the
3540-byte BSS deficit can increase the span; it cannot increase this already
capped reservation while these input fixups and mode remain unchanged.
This rules out BSS padding as a relocation repair as well as forbidding it.

Under the same normal path, the original66420-byte reservation requires5535
potential fixups,1259 more than the current input set. This does not name
their owners or authorize discarded pointer tables. Genuine original input
composition or evidence of a different link mode is still required.

Current production census update, 2026-10-03: after genuine source grouping
and the two accepted scalar ORDER changes, all 127 direct inputs and 137
freshly traced stock CRT members still have 4167 DIR32, 512 DIR32NB and
2450 REL32 records. The 109 loaded import members leave potential count
4276 and page span 5990, exactly reproducing 51312 reserved bytes. The
additional 1259 potential fixups implied by the reference remain unattributed.
This fresh input proof explains why the 3604-byte data-size deficit cannot
be used to predict a reservation repair. Complete per-object census and
unchanged-input/definition barrier: `native-current-input-evidence/`.

At0x442f76–0x442f85 the emitter overwrites context+0xd0 with the actual bytes
used: output cursor minus relocation start. Section VirtualSize remains the
reservation. The untouched stock reference confirms this distinction:

| Artifact | `.reloc` VS | Relocation directory Size | PE offset | Rich |
| --- | ---: | ---: | ---: | --- |
| Current native build | 51312 | 7404 | 0xe0 | Present |
| Untouched stock server.dll | 66420 | 7404 | 0xe8 | Present |
| Configured original/Server/server.dll | 66420 | 66420 | 0x80 | Absent |

The two references have identical section layouts and every raw section byte,
but285 header-byte differences. Both native and untouched stock Rich records
contain product4/build8447/count1, corroborating the same linker build. The
configured file has also changed the relocation directory Size to include
the unused reservation. This is an additional precise header discrepancy,
not missing live relocation records: both references have the same3499 sites.

Section71 proves this stock build's normal PE path always constructs Rich;
its bypass produces ROM/COFF rather than the required PE. Consequently the
configured Rich-free header cannot be emitted by that normal stock toolchain
under the existing no-patching/no-postlink constraints. A reference choice
is requested: retain the untouched stock binary as the native-output target,
or keep the configured artifact and resolve this incompatible header
requirement explicitly. Do not silently replace it or weaken equality.
Selecting stock alone would not finish the remaining storage, input-fixup,
import, timestamp or compiler-record work.

Runnable evidence: `.scratch/native-reloc-writer/audit.py` and `audit.json`
record exact instruction bytes/operands, all current input counts, all three
PE hashes, span sizes and Rich records, plus fresh raw-section identity and
285-byte header-difference assertions. The canonical DLL/reference/stock
archive hashes stay fixed. No smoke or function recheck is reported as new
progress, and no production byte gain is claimed for this analysis.


## 77. Untouched GOG reference restores the native header contract

The user selected the untouched distribution reference. The GOG installer
`setup_the_guild_gold_2.0.0.5.exe` supplies `app/Server/server.dll`, 286720 bytes,
SHA256 `3cc2ce9049e41ab6d0eea042df4966fbf57e5e27c67fb923e81709d2683609d1`.
Direct extraction proves it byte-identical to the Steam copy and the configured
`original/Server/server.dll`, which remains mode0444. README records provenance
and the checksum command; the GOG-labelled directory itself is a Redump symlink.
Do not use that directory label as distribution evidence.

This resolves the earlier Rich-free-reference conflict. The old modified
reference is preserved at `.scratch/reference-before-stock/`; no comparison
against it is the current objective. Its four raw sections agree with stock,
but its285 changed header bytes included removal of Rich and replacement of
relocation directory Size7404 by section reservation66420.

Reconfigure the existing native timestamp launcher against stock and remove
`/RELEASE`: stock stores checksum0 and the default native linker emits0.
The resulting native build has SHA256
`0f9429af4659fc7be4cd37361730acb7e45742753107b03cab91dbb40a6fd01a`,
270336 bytes,2736 overlapping differences,16384 bytes short. Its timestamp is
0x3fdd84a0,checksum0; raw section differences remain2127/286/54/0. All192 direct
input hashes stay fixed and no C recompiles in this rebaseline. Changing the
reference is not counted as a code gain.

Refresh the extracted layout through existing public Rebrew APIs, without
restoring generated C scaffolding: only `header.hex` and `layout.fingerprint`
change. New fingerprint
`91c52bf83e1a44d2d2fa17bb2c156b81d4c6fa94cefdf721938dc52296f2a199`
is fresh. Combined verification passes262/262 functions, zero size divergences;
data550matched/48mismatched/7missing/3not_comparable. Whole-binary verification
correctly exits1; all-target lint has zero warnings/errors. The whole-file goal
remains incomplete. Original storage/input composition,51 KERNEL32 IAT slots,
relocation reservation and compiler records still differ.

Evidence: `.scratch/native-stock-reference/` terminal rebaseline, layout refresh,
verification, lint, coverage/status and build-check reports;
`.scratch/gog-reference-verification/verification.json` direct installer check.
Section76's potential-fixup bound remains applicable to the same raw inputs;
stock selection does not infer1259 missing fixup owners or authorize padding.

## 78. A real source cohort changes Rich counts without changing runtime bytes

Six contiguous Error-module fragments all use `/O2 /Gd`. Their shared prototypes
must first agree; C-shape249 records byte-preserving int-to-byte parameter
handling and genuine SDK declarations. A complete six-source compile preserves
all eleven function sizes, every nonfixup code byte and typed relocation
positions/kinds. It compiles without warnings.

The full native link nevertheless fails the whole-file improvement gate.
MSVC6 moves the four automatic string COMDATs after the explicit initialized
globals in the combined unit. Eighteen public/literal bindings move; data
mismatches rise54→916 and text mismatches2127→2209. Complete differences are
3678 versus2736; size remains270336. All192 production inputs stay fixed for
this control. Function-local matching alone is insufficient to promote it.

The smaller contiguous cohort, `ErrorModule.c`, the SDK-correct initializer,
and `ErrorModule2.c`, preserves the preceding literal owners. Eight functions
compile together without warnings. Its native DLL has SHA256
`f5ea7643c440cbd3ca01355f58d5880113bf9646ccd6b618bde6b6ec77413fda`:
2735 differences,16384 bytes short. Every runtime section equals the baseline,
all597 function bindings and3499 live HIGHLOW sites stay fixed, all100 import
identities/hints/slots and other public symbols retain their bindings, the
same137 stock CRT members supply runtime code, and five data/value guards pass.
There are no linker warnings when the scratch DLL retains the `server.dll`
basename. A differently named scratch output produced the expected LNK4070
EXP `/OUT` mismatch; that control-path warning was removed by using the proper
basename, without altering the native EXP.

The C compiler Rich record changes191→189 for product10/build8966. This is an
actual reduction in native compiler inputs, not a synthetic Rich edit. The key
changes0x2e67c711→0xee63f9ee; both PE offsets remain0xe0 under section71's
key-derived reservation formula. Only one additional header byte agrees with
stock. The original count37 and original key0xc3b8ddfa are still unmatched.
Do not infer completion from that small header gain.

Source promotion concatenates the three fragments into `ErrorHandlers.c`,
preserving all33 FUNCTION/DATA/GLOBAL markers across all targets and original
function order. The dispatch int-formal/local-byte form is promoted separately.
Canonical CMake recompilation and final verification are required before
reporting this candidate as the production DLL. An initial complete rebuild
stops around74% with Docker/containerd ENOSPC; no candidate DLL is copied over
production and no equality assertion is weakened.

Evidence: `.scratch/native-error-tu/` compile/native-link argv and logs,
`group-functions.json`, `quick-audit.json`, `tail-audit.json`, `tail-gates.json`,
`rich-cohort.json`, `marker-preservation.json` and source snapshots. Final
production validation is recorded in the latest HANDOFF checkpoint.


## 79. Restoring literal ownership removes the full-cohort layout regression

C-shape250 replaces the fragment-created blobs/message arrays by their exact
live string literals. A single native Error object supplies the same data pool
at the same addresses as the six previous fragments. All eleven complete
function sizes/nonfixup bytes/typed relocation topology stay fixed.

After ordinary native LINK, `.text`, `.rdata`, `.data` and `.reloc` are all
byte-identical to the accepted2735-difference baseline. The full Error pool
matches reference bytes; all597 function bindings,3499 live HIGHLOW sites,
100 import identities/hints/slots, surviving public bindings,137 selected
stock CRT members and five value guards pass. Fourteen artificial data aliases
are replaced by44 actual live-literal symbols, with no new or unused storage.
The original data byte extents remain real and unchanged. Native compile and
link controls have zero warnings.

The candidate SHA256 is
`c805c9c5aec84c522f27931d98980bd236755e81b97f755dd58f6bda1187b1a9`,
270336 bytes,2734 differences,16384 bytes short. C compiler Rich count is186
rather than189 (and191 before any Error consolidation), key0x4662de1a. This
native source-input change saves one more header byte; it does not repair
storage extents,51 displaced KERNEL32 slots or original compiler/library counts.

Promote the measured body to `Units/Error/Error.c`, retaining all function
markers across targets. Delete its three remaining fragments and their
obsolete source-only data-alias markers; keep the real globals and managed
byte-region metadata. The normal canonical build and verification, not copying
the candidate DLL, determine acceptance. See the latest HANDOFF for terminal
production validation; older ENOSPC/intermediate checkpoints remain historical.

Evidence `.scratch/native-error-tu/literal-cohort/` functions/audit/gates,
native argv/logs, literal-binding-changes.json, source-promotion.json and
production build/verification/lint reports. All producer/object/reference
bytes are emitted or read normally; no binary patch or postlink action occurs.


Section79 terminal acceptance: the ordinary production CMake build completes
successfully and emits the exact measured c805c9c5...7b1a9 candidate. Final
verification passes262/262 with no failures or size divergences; all three
targets lint with zero warnings/errors; build-check covers186 objects with
zero drift; all three coverage documents are regenerated. The earlier disk
capacity failure is resolved. Whole-binary identity remains false. Full
terminal reports are in `.scratch/native-error-tu/literal-cohort/final-*`
and `production-lint.json`.

## 80. An extra native producer record can improve header bytes and regress code

The original compiler8047 count differs by eleven from the137 selected stock
CRT members' native contribution. Testing zlib as a possible owner is a
hypothesis, not an attribution. C-shapes251 compiles all twelve actual zlib
inputs under unchanged native VC6 RTM; eleven runtime objects match SP5,
while `inflate_blocks` reverses two independent load pairs (eight bytes).

Keep all187 production inputs unchanged and link controls replacing only
these real compiler outputs. No empty input, object edit or metadata patch:

| Native replacement | SHA256 | Overlapping differences | PE offset | C producer records |
|---|---|---:|---:|---|
| None, production | c805c9c5aec84c522f27931d98980bd236755e81b97f755dd58f6bda1187b1a9 | 2734 | e0 | 8966:186; 8047:113 |
| All12 RTM zlib objects | edc4a6414c46bca5c25bff60f869899bb5bed6eff45485b6cc9c5c8134579362 | 2583 | e8 | 8966:174; 8168:12; 8047:113 |
| Eleven exact RTM objects | 1aad92adca1a8e88a5adab07cf05d08f5eab1f7fbdefa58b6979705acd1fc2e1 | 2776 | f8 | 8966:175; 8168:11; 8047:113 |

Both links complete with no native warnings. The twelve-object control's
lower difference count and correct PE offset do not outweigh eight newly
incorrect instruction bytes and an extra producer record absent from stock.
The eleven-object control preserves all runtime section bytes, all597
function MAP bindings,3499 live sites,100 import identities/hints/slots,
all surviving public/storage bindings,137 unchanged stock CRT members and
five value guards, but worsens the header and adds the unsupported producer.
Neither control is promoted. The original stock record is build8047:124;
this experiment definitively supplies8168 and therefore rejects the proposed
zlib producer explanation for this compiler profile. It does not prove which
original discarded inputs supplied the additional8047 records.

All three DLLs remain270336 bytes,16384 short. All relocation bytes and
section extents remain fixed. Evidence `.scratch/native-zlib-producer/`
link_controls.py, before-inputs.json, controls-comparison.json and complete
all-base/exact-eleven argv,logs,results; exact-eleven/audit.json and gates.json.
The real production DLL and all187 input hashes are checked unchanged after
both links. No new Rebrew deficit is exposed by this bounded experiment.


## 81. Directory grouping is not original TU ownership or cross-target layout proof

C-shapes252 measures two complete native command cohorts. The all69-directory
control changes35 function bindings despite every function's object code being
correct: `cm_RouteCommand` is actually from `lobbycommands.c`, as its live
source-path literal shows. Its272-byte contribution moves before the intervening
34 functions. Candidate07245cb205b933db9bdbfe2f9c71b453df4cc6a6e00fe7240531867bc651fc94
has24417 differing bytes; it is rejected.

Excluding that handler produces the genuine68-function server command.c control,
SHA2563cae84437bf1c5319bd89ab6f79f00424eca63581ce056361784b17d5526339f.
All four runtime sections equal production exactly, including full relocation
operands. All597 function bindings,3499 live sites,100 import identities/hints/
slots,surviving public symbols,137 selected unchanged CRT members and five value
guards pass; native compile and LINK have no warnings. Extents remain unchanged,
270336 bytes and16384 bytes short. C producer count119 replaces186; keyb162ba9f
and PEf0 produce2735 differences rather than2734. This is authentic input
consolidation evidence, not a claimed byte-match gain or whole-file recovery.

The shared-source validation rejects production adoption: nine unique GOLDTL
source-order warnings W030 arise under every target lint result. The source had
been tentatively assembled with all114 annotations preserved, but is restored
completely before acceptance. No native candidate is copied to production; the
canonical DLL remains c805c9c5...7b1a9. Restored source hashes equal all68 captured
snapshots, all-target lint is again zero-warning, and CMake is reconfigured back
to186 C inputs plus native EXP. Do not silence a warning merely because the
server control matches. A source cohort shared by three targets must satisfy
all their source-order checks, or remain split.

A renewed native build initially fails at8% with real Docker Btrfs metadata
ENOSPC. The failed log is preserved; this is not a permission denial or compiler
miscompile. A bounded empty-chunk release completes successfully and relocates
zero chunks, so it is not credited with recovering capacity. Docker's container
health check subsequently succeeds; the restored normal production target is
retried with one compiler at a time, without raising resource limits. Final
terminal restoration validation is recorded in HANDOFF.

Evidence `.scratch/native-command-tu/`: all-69/ complete object/DLL/MAP/logs,
functions.json, quick-audit.json, audit.json, gates.json, source snapshots,
source-promotion-rejected.json, restored-lint.json, restoration-check.json,
failed production-build.log and restored configure/build reports. No production
source, extra input, compiler override, padding or postlink change is retained
from these command controls. No new Rebrew implementation deficit is established.


## 82. Real compatible source grouping predicts and restores the native PE offset

Use section81's measured68-function code while splitting at the nine shared
order conflicts; the greedy contiguous grouping needs eight actual source
parts, including one unchanged singleton. All eight native SP5 controls retain
all68 complete function shapes and typed symbolic relocation bindings.
C-shapes253 records the source and shared-target validation.

The measured section71 formula predicts the header before LINK. Replace
compiler product10/build8966 count186 by126 while retaining the other seven
producer records. The rotated producer-sum key changes4662de1a→ae653e4f;
128+32+8*(8+((key>>5)%3)) gives PE offsete8, equal to stock. This prediction
uses actual live source-input counts. It neither adds an artificial producer
nor edits Rich/header bytes. Native LINK then independently confirms count126,
keyae653e4f and PEe8 exactly.

The candidate is f12b99461f19ae44e29e44390865d2917ed7633241f1d206eb83e74fe446c6d7,
270336 bytes,2563 overlapping differences,16384 bytes short. It removes171
header differences from the c805c9c5 baseline. All four runtime sections are
byte-identical to that baseline, including complete HIGHLOW operands and
relocation bytes. Every597 function MAP binding,3499 live sites,100 import
identities/hints/slots,surviving public/data bindings,137 unchanged selected
CRT members and all five value guards pass. No complete fixup field gains or
loses exactness. All native compiler/link controls have zero warnings.

Source preparation preserves all114 original markers: seven restored cohorts
carry110 and the retained singleton four. All-target lint4056/4056 is clean;
CMake configures127 direct inputs (126 C plus native EXP) and build-check
reports zero flag drift. Build-check validates recipes, not object presence:
seven new production objects are still missing and must be compiled normally.
The last262/262 production verification is correctly stale after this source
change. Do not label the candidate as the production build or its171-byte gain
as a completed production promotion.

The root capacity issue cleared, allowing the successful bounded scratch link.
The current managed execution profile subsequently denies connection to
`/var/run/docker.sock`, confirmed by read-only `docker info`. Native production
rebuild and fresh verification therefore await Docker-accessible execution.
Do not raise limits, use host Wine, copy candidate objects/DLLs into build or
claim complete-file identity. The canonical DLL stays c805c9c5...7b1a9 and the
read-only stock reference stays3cc2ce90...09d1. All control objects/canonical
hashes are checked unchanged around the terminal native LINK.

Evidence `.scratch/native-command-tu/compatible/`: link-argv/result/log,
before-inputs.json, quick-audit.json, audit.json, gates.json, final-lint-summary,
source/order/token checks, production-configure/build-check/status/readiness.
The next required check is the ordinary CMake target, followed by full function,
data/whole-binary verification and coverage regeneration.

Current producer identity clarification: the final normal production
ff81a459 image still has key ae653e4f, while the untouched reference has
c3b8ddfa. Matching PE offset e8 does not make their Rich ledgers equal.
Product10/build8966 is 126 in production and 37 in the reference; product1/
build0 is 109/126, product10/build8047 is 113/124, and product12/build7291 is
1/6. The other four counts agree. The 126-source-input control above restores
the PE offset through the measured native formula; it does not claim original
TU composition or discarded-input provenance. Fresh read-only ledger and
section evidence is `native-early-game-counters/remaining-comparison.json`.

Production validation update, 2026-10-03 01:11 UTC: the host monitor's canceled
duplicate Make invocation explicitly deleted the shared graveyard object
`gv_ExtendProductionTime.c.obj`. The earlier host build then failed LNK1181
for that same path, despite an intact source, compile rule and prerequisite.
The failed LINK removed the production DLL. This is build contention;
do not change the source list or copy a control object to conceal it.
Thirteen concurrent source/header changes were recorded, so a future native
result needs fresh source/import/layout evidence. All-target offline lint
now passes 4052 checks per target, zero errors/warnings. Preserve the complete
control evidence; normal native production acceptance remains pending.
Terminal logs and receipt: `compatible/concurrent-build-failure/`.

Repair update, 2026-10-03 01:19 UTC: a single native CMake build completes
with source/config/layout hashes unchanged. Production DLL 8e02205d...5f0858
is present, 2563 differences and 16384 bytes short: 171 fewer differences
than the previous production build. Other ownership edits make the production
hash differ from the original control. Complete nonfixup code, 597 function
positions, 3499 live HIGHLOW sites, 100 import identities and five value guards
pass. This is a successful native build with incomplete whole-file identity;
fresh function verification has not completed. The full CLI verify's 60-second
timeout emits no report and is not a pass.


## 83. Placement checks must use the active target and native LINK positions

The repaired production MAP places `_g_log_level_table` at 0x10027078,
exactly the SERVER metadata address. `rebrew build check-data-placement` instead reports
expected 0x00677918 and actual 0x10027046. Two independent root mistakes
explain the false finding. `data_layout.data_symbols` reads every target into
one name map; the later GOLDTL record overwrites SERVER's address. Then
`verify_placement` sums unlinked object `.data` contributions to predict
placement, rather than observing the native LINK result. This does not model
the final COMDAT selection and section ordering.

Do not change correctly placed source storage to satisfy this report, or
interpret all 88 reported misplacements as native layout regressions. Filter
metadata to the configured target and derive actual positions from the linked
image/native MAP. Missing or discarded object symbols must remain explicit;
unlinked COFF presence alone is not proof that a symbol survives LINK.

The reproduction is confirmed in both installed and sibling source at
`data_layout.py:277` and `verify_placement.py:98`. A direct root fix remains
pending because the sibling is outside this session's writable roots and
approval requests are disabled. No installed tool or managed verdict was
patched to hide the finding.

Evidence `compatible/concurrent-build-failure/placement-tool-deficit.json`,
`production-placement-cli.json`, native production MAP and the SERVER/GOLDTL
metadata records. Public Rebrew whole-binary/data APIs separately complete
under unchanged input hashes: whole identity false, 569 data matches,
48 mismatches, seven missing and two not comparable. Native production
still needs fresh source-compilation verification; the full CLI's 60-second
timeout is not a completed gate.


## 84. Merging stock BSS into data materializes an incompatible native section

The reference places ordinary CRT storage before the bulk game COMMONs and
stock CRT COMMONs after them. Current bulk and late COMMON bindings remain
0x1200 too early; ordinary CRT bindings occupy the late tail. Previous native
section-suffix and sole-provider controls in sections 67–68 did not recover
both constraints. Do not repeat them or invent storage for the unowned span.

One new bounded control changes only the native LINK directive
`/MERGE:.bss=.data`. It tests whether the existing stock ordinary BSS can
participate earlier in native data layout without replacing a library or
changing any object. All 127 current direct inputs, stock archives, source,
configuration, ORDER/INCLUDE responses, production DLL and read-only GOG
reference are hash-guarded. Native output DLL/MAP/LIB stay in scratch.

The host executes this control through the stock Docker-backed wrapper.
LINK exits zero with every guarded input unchanged, but emits LNK4078:
multiple `.data` sections have different attributes, C0000080. The candidate
is 24,592,384 bytes rather than the reference's 286,720. It has 39,270
overlapping differences and 24,305,664 extra bytes: 24,344,934 total unmatched
bytes against the production baseline's 18,947.

All 597 function positions and import identities/hints/slots survive, and
complete nonfixup text remains identical. The live HIGHLOW site set changes,
however. Only the readonly value guard passes; mutable/VFS, version,
conversion-table and locale-prefix guards fail. The candidate is rejected.
Do not silence the section-attribute warning or copy these outputs into
production. The native merge result does not establish a missing storage
owner and supplies no reason to enlarge any game allocation.

Prepared host command:

```sh
.venv/bin/python .scratch/native-bss-merge/probe.py --execute
```

The default invocation prepares argv and input hashes without native
execution. The host invocation bounds LINK at 60 seconds and terminates only
its own process group on timeout. This session does not run Docker. The
measured host control leaves production and the read-only reference intact.

Evidence `.scratch/native-bss-merge/probe.py`, `prepared-inputs.json` and
`merge-bss-data/{argv.json,result.json,audit.json,guards.json,link.log}`.
Candidate SHA256 is
35876f19d1db30c866594ba9f3ca22cbd0b4c031c56746c2d6a9480ca9691fd4.
Baseline remains production 8e02205d...5f0858, 2563 differing bytes plus
16384 missing; reference remains 3cc2ce90, mode 0444.


## 85. Removing an array alignment gap can lose correct address bindings

The host executes exactly one scratch save-loader compile and one native
stock link. All 4259 guarded inputs remain unchanged; both native calls exit
zero. The array's logical extent remains 32 bytes and its zero-filled value
is checked completely. C-shapes 255 records the object-level storage change.

The candidate is 000644a87ff9112a49ad79ca838a27d17146609fb57adb133371b0f759cd99f4,
270336 bytes, 2570 overlapping differences and 16384 bytes short. Total
unmatched bytes rise from 18947 to 18954. Function/import/live-site/nonfixup
checks and all five value guards pass, with no warnings. These semantic
checks do not turn a worse native file comparison into a successful repair.

The array and neighboring handler/clock move eight bytes earlier; the bulk
slot table and earlier two save-header DWORDs stay fixed. Seven formerly
exact HIGHLOW fields for the handler lose exactness, with no exact fields
gained. Reject promotion and preserve the existing tentative definition.
The control disproves this isolated COMDAT repair, not the known 32-byte
array extent or every possible genuine storage-owner arrangement.

Evidence `.scratch/native-save-array-comdat/{probe.py,prepared-inputs.json,
compile-argv.json,link-argv.json,compile.log,link.log,result.json,
object-shape.json,audit.json,changed-fixups.json,guards.json}`. Production
8e02205d...5f0858 and read-only reference 3cc2ce90...09d1 remain intact.


## 86. Two real query pointers fill a native alignment interval without moving bulk storage

`gm_NextEntityQueryMatch.c` defines the genuine four-byte query filter and
cursor pointers; their reference bases are 0x10035464/68. They precede the
entity-table end pointer and save-header DWORDs at 0x1003546c/70/74, followed
by the 32-byte save array at 0x10035478. The existing ORDER instead places
both query pointers after a large dispatch table, at 0x1014c6d4/d8. Fifteen
complete HIGHLOW fields target those two pointers and differ in three bytes.

Move only those two ORDER names immediately before `g_entity_table_end`.
They use the existing eight-byte alignment interval before the save array;
removing their old slots enlarges the natural interval before the next large
relationship array. No new definition, weak COMDAT, array enlargement,
padding, library change, compiler call or object edit occurs. Predict a
15-byte file improvement before LINK, with exactly five changed public
bindings and no change to the save array, handler, clock or bulk allocations.

The bounded stock native control independently confirms every prediction:

| Existing owner | Previous native base | Control base |
| --- | --- | --- |
| query filter pointer | 0x1014c6d4 | 0x1003464c |
| query cursor pointer | 0x1014c6d8 | 0x10034650 |
| entity-table end pointer | 0x1003464c | 0x10034654 |
| first save-header DWORD | 0x10034650 | 0x10034658 |
| second save-header DWORD | 0x10034654 | 0x1003465c |

All other public bindings and all 597 function bindings remain unchanged.
The 33 changed fixups remain bound to their real owners; no complete exact
field is gained or lost. Imports/hints/slots, live HIGHLOW sites, complete
nonfixup code and all five full value guards pass without warnings. All
4256 guarded inputs remain unchanged during LINK. The native verbose trace
selects 137 stock CRT members.

The accepted control SHA256 is
fcc658ee78c9ab03a43f0b5e55ce62e60d18d2ddc6568630213495c74485d526,
270336 bytes, 2548 overlapping differences and 16384 bytes short. Total
unmatched bytes decrease from 18947 to 18932. Complete-file identity remains
false; these five absolute bindings still differ from their reference bases.
Public Rebrew comparison APIs preserve export/import/relocation/resource/
image-base/layout gates, with file/section gates false. Data remains 569
matched, 48 mismatched, seven missing and two not comparable. These read-only
checks write no managed verdict and do not replace source compilation.

The production ORDER file now equals the control's ORDER. The only changed
prepared input is that source layout file. Normal native production build
and fresh verification remain required; no scratch output is copied into
production. Evidence `.scratch/native-query-pointer-order/`: probe and
prediction, native argv/log/DLL/MAP, audit and complete fixups, guards,
selected CRT members, public API reports, promotion-ready.json and the
production-before-inputs.json snapshot. This session does not run Docker.

Production acceptance update: the host runs exactly one normal
`cmake --build build --target server_dll --parallel 1`, exit zero in
4.05 seconds with every guarded input unchanged. Native production equals
the accepted fcc658ee control byte for byte: 2548 differences and 16384 bytes
short. Read-only public binary/data APIs repeat the control's gates and
569/48/7/2 counts. The reference remains SHA256 3cc2ce90...09d1, mode 0444.
No scratch DLL or object enters production. Durable native build, hash and
API receipts are `native-query-pointer-order/production/`. Fresh compiled
function verification remains pending; this measured native production gain
does not establish complete-file identity.

Focused validation update: the host executes the prepared ordinary CLI
tests for all 19 functions containing the 33 changed fields. All 19 pass
RELOC with equal complete annotation/object sizes and match_count equal to
total, no timeout or input change, in 12.17 seconds. Production/reference/
metadata remain unchanged. This validates the changed-reference scope;
it is not a new full verification of all source or complete-file identity.
Receipt and per-function results: `native-query-pointer-order/focused/`.


## 87. Genuine early counters can use existing alignment without moving large arrays

The native clock ends with a two-byte field at 0x10034690; the following
slot table starts at 0x100346a0. Move three existing four-byte game COMMONs
from their late positions to this naturally aligned interval. The counters
retain their sole real providers and types. No compiler/object/library change,
extra definition, enlarged array or explicit padding occurs.

Their old slots precede the large dispatch table. The remaining four scalars
shift twelve bytes earlier, with natural alignment retaining the dispatch
table and every larger/late allocation. Predict all seven changed public
bindings and the 18-byte improvement before LINK; derive the byte gain from
complete reference/native fields, rather than numeric address distance.

| Existing owner | Previous native base | Control base |
| --- | --- | --- |
| citizen count | 0x10138684 | 0x10034694 |
| active-player count | 0x10138688 | 0x10034698 |
| saved-dynasty field | 0x1013868c | 0x1003469c |
| dynasty name | 0x10138690 | 0x10138684 |
| dynasty scan count | 0x10138694 | 0x10138688 |
| query limit | 0x10138698 | 0x1013868c |
| query count | 0x1013869c | 0x10138690 |

The initial prediction catches a numeric coincidence: a table-minus-four
field currently equals the query counter's address. Native COFF proves its
separate table owner/addend, and the corrected prediction leaves it fixed.
C-shapes 256 records this compiler addressing form. Do not change the source
or metadata to make a numeric-address guess fit.

The bounded stock host LINK confirms exactly seven moved public bindings,
44 changed fields with complete owner/reference proof, and 18 fewer bytes.
Every other public binding, all 597 functions, live HIGHLOW sites, import
slots/hints, complete nonfixup code and five full value guards remain fixed;
no exact field is lost and no warning or guarded input change occurs.

Candidate SHA256 is
ff81a459a20dbdbbf3bebe76128ec8bdd80b80bd59bf238cc2db936f12941935,
270336 bytes, 2530 overlapping differences and 16384 bytes short. Total
unmatched bytes decrease from 18932 to 18914. All seven absolute bindings
still differ from their reference positions; the complete original relative
layout remains unresolved. This is a measured native byte improvement,
not complete-file identity or recovery of the unknown earlier storage owner.

Public Rebrew comparison APIs preserve structural gates, with file/section
gates false and data counts 569/48/7/2. They write no managed verdict. The
production ORDER now equals the accepted control and is the only changed
prepared input. One normal native CMake relink remains required; production
still has the fcc658ee hash until it completes. No scratch artifact enters
production. Evidence `.scratch/native-early-game-counters/`: probe/prediction,
native argv/log/DLL/MAP, audit/guards/fields, public API reports and
production-before-inputs.json/promotion-ready.json. This session does not
run Docker.

Production acceptance update: one normal host CMake build exits zero in
1.27 seconds with unchanged guarded inputs and produces the exact accepted
ff81a459 control. Production has 2530 differences and 16384 bytes short;
no scratch output or binary transformation is used. Public Rebrew API
structural gates and data 569/48/7/2 repeat on production. Reference SHA256
and mode 0444 remain unchanged. Durable host receipts are
`native-early-game-counters/production/`.

Full source verification update: seven ordinary full CLI directory scopes
partition all 262 candidates and pass with unchanged guarded inputs and
technical metadata definitions. An ordinary unscoped CLI verification then
uses those fresh valid results and repeats the data/whole-binary gates in
49.68 seconds. All 262 pass: 22 EXACT, 240 RELOC, including two library
checks, zero failures or size divergences. Its exit one correctly reports
the remaining complete-file/section disagreement. Managed verdicts are
written by the CLI, and final status has stale=false. Receipts and reports
are `native-early-game-counters/verify-scopes/`; the earlier invalidated
tool-change epoch is preserved separately and is not counted as accepted.

### 5a. `/OPT:REF` with game-function anchors (2026-10-06)

`/OPT:REF` alone gutted the game code because the reversed functions are reached by address, not by symbol.
`layout/server.dll/game-includes.rsp` anchors each of the 260 SERVER game symbols with `/INCLUDE:` in VA
order (`scripts/gen_game_includes.py` writes it from `rebrew-functions.toml`; re-run after a row change).
Measured on the raw link: `.text` VirtualSize 141392 against the reference's 141382, all 260 game functions
and all 56 compiled library functions at their reference VAs. The stock library region sits 6 bytes late
because `/include:__imp__RtlUnwind@16` in `src/crt_region/crt_imports.c` pulls the KERNEL32 import member
first, and its `_RtlUnwind@16` thunk (reference VA `0x10023840`) lands before the WS2_32 thunks; the 6 bytes
then cascade into 16-byte alignment steps.

Two source facts the order depends on, both measured:

- Emission order is source order. The `__LINE__` values the code passes to `LogMessageInternal` rise with
  the VA inside `spiel.c`, and a function body placed above its `// FUNCTION` marker moved its COMDAT.
- A callee defined earlier in the same translation unit changes the caller's code. `gm_Open` lost `ebx` (859
  bytes against the reference's 861) when `gm_InitObjektHersteller` was defined above it; calling it through a
  function pointer restores the reference bytes. Per-function `#pragma optimize` (`gm_AllocGebaeude`,
  `gm_CalculateProductionValue`, `ProcessSendData`) and the cumulative `#pragma intrinsic` lines belong at
  the function that introduced them, not in the shared preamble.

### 5b. Import slots, `.rdata`, and what is left (2026-10-06)

- **IAT order.** `layout/server.dll/import-includes.rsp` (written by `scripts/gen_import_includes.py`;
  `src/crt_region/crt_imports.c` supplies only the `@N` decoration and is not linked) forces the game's
  KERNEL32 imports and the other DLLs in the reference's hint/name order; section 5d gives the load-order
  model and what is left of the slot order. `AllocConsole` had no import at all before (`/include` in an
  object directive was ignored), so the code called `FreeConsole`'s slot; Error.c now calls the APIs by name.
- **`.rdata`.** `src/crt_region/rdata_restore.c` is no longer linked. Its blob repeated the C objects of
  `readonly_strings.c`, `type_adjustments.c` and `game_float_constants.c` (3272 bytes) and the CRT strings that
  the linked LIBCMT objects supply. `.rdata` is 11905 bytes long, the reference's, and equal except 8 bytes of
  CRT literal order near `0x100260b3` and the import descriptors that follow the IAT order above.
- **Constants.** One representation per value. A constant that code reads through a float operand in a double
  expression, or whose use changes scheduling, is a named `selectany const` object (anchored in
  `game-includes.rsp`); doubles that the CRT shares (`1000.0`, `0.0`) are compiler literals so their
  `__real@8@...` COMDATs fold with LIBCMT's. Reading by absolute address (`*(float*) 0x100256b4`) stays where the
  symbol form changed the schedule. Rewriting every constant as a literal was tried and rejected: three
  functions need a float memory operand there. `/ALTERNATENAME` is ignored by this LINK.
- **Not done.** `.data`: `src/crt_region/data_restore.c` is a 0x9a00-byte copy of reference `.data` that sits
  where LIBCMT's own `.data` now links, so LIBCMT's data is 0x9a00 bytes late and 1438 `.text` operands still
  miss their target (fixed in 5c and 5d). Raw link `.text` is the reference's size and every
  differing byte (4406) is inside a reference relocation dword: 1438 `.data`, 51 IAT, 16 `.rdata` operands.

### 5c. Locale data, import thunks, and the BSS model (2026-10-06)

- **Locale stubs removed.** `link_stubs.c` no longer defines `___setlc_active`, `___unguarded_readlc_active`,
  `___lc_handle`, `___lc_codepage`, `___lc_collate_cp`, `___crtGetLocaleInfoA/W` or `___get_qualified_locale`.
  The linker now pulls `setlocal.obj`, `nlsdata2.obj` and the locale objects from LIBCMT. `/OPT:REF` drops their
  code (all COMDAT), so no NLS import appears, and `setlocal.obj`'s plain 0x10b-byte `.data` section supplies the
  268 bytes the reference has between the `__cfltcvt_tab` pointers and `_ctype`. Raw `.text` is now equal to the
  reference outside relocation operands (0 differing bytes outside reloc dwords).
- **`rdata_fold.c` removed.** It existed to fold LIBCMT's zero-length literals out of a restored `.rdata`;
  with the real members linked its two `.data$zz` literals only displaced COMMON by 16 bytes.
- **Import slot recipe.** `gen_import_includes.py` now reads the reference's import table directly. WS2_32 is left
  out of `import-includes.rsp`: its members carry the thunks the game calls, so the thunk includes at the top of
  `native-archive-includes.rsp` load them in the reference's thunk order (`closesocket` .. `socket`, 0x1001a160).
  USER32's pair is `MessageBoxA`, `GetWindowTextA` (the old pragma order had them swapped). Measured facts:
  an include loads its member once and the first load fixes both the thunk position and the slot; `/ORDER`
  moves thunks (they are COMDAT) but lists first, so it cannot place them mid-`.text` while static zlib
  functions cannot be listed (LNK4037); in an isolated probe the includes' order is the slot order, in the full
  link the WS2_32 slots are permuted by the import sort (section 73), so the 9 WS2_32 members that have no
  thunk (`accept`, `listen`, `send`, `recv`, `ioctlsocket`, `WSAGetLastError`, `shutdown`, `WSAStartup`,
  `WSACleanup`) are still out of order.
- **BSS model (measured).** LINK lays `.bss` out as: COMMON symbols listed in `/ORDER`, then every plain
  `.bss` section in load order (command-line objects first, then archive members as they load), then
  unlisted COMMON, then `.bss$*` sections by name. Explicit zero definitions are plain `.bss`; arrays are
  4-byte aligned, scalars naturally aligned. The reference is: game `.bss`, LIBCMT's plain `.bss`, then the
  rest of the game's data, then LIBCMT's COMMON. Section 5d gives the reconstruction.
- **`Error.c` pool.** Every string from 0x100270f8 to 0x10027488 is a literal at its use, as in the original:
  VC6 emits them in creation order after the TU's named data, and crt0msg's `"\r\n"` folds into Error.c's
  (the CRT's own copy used to sit in `.rdata` and move every later CRT string by 4).

### 5d. Generated BSS, data-only TUs and what is left (2026-10-06)

- **Generated BSS.** `scripts/gen_bss_layout.py` writes `src/bss_layout/bss_head.c`, `bss_head2.c` and
  `bss_late.c` from `rebrew-data.toml`: one explicit zero definition per reference row in its declared type,
  in VA order, with `g_gap_<va>` pads where the rows name nothing (alignment, or a variable nobody has named).
  A row that overlaps the next ends where the next starts, so a large object is covered by the symbols that
  follow it. `bss_head.c` and `bss_head2.c` are command-line objects ordered around zutil.obj, whose empty
  string `""` is a 1-byte `.bss` COMDAT the reference has at 0x10034620. `bss_late.c` is the static library
  `bss_late`, linked after LIBCMT, so LINK loads it after the CRT members and its `.bss` follows theirs. The
  head ends at the last game variable: a 24-byte LIBCMT static block (time.obj) precedes crt0dat in both
  images. The game TUs declare these names `extern`. Re-run the generator after a data row changes.
- **Measured results.** `.data` VirtualSize equals the reference; `rebrew verify --data` with the link map
  reports 334 symbols EXACT and none DISPLACED.
- **Data-only `spiel_data.c` is original structure.** Defining its globals inside `spiel.c` makes VC6 widen
  `gm_NextEntityQueryMatch`'s word load of `g_query_filter_type` to a dword: code generation runs after the
  whole TU is parsed, so a definition anywhere in the TU changes it. The original therefore did not define
  them in spiel.c. `spiel3.c` and `spiel_gm_DispatchCall.c` held no code and are gone.
- **Literal-sensitive `gm_AllocSpieler`.** Its five strings and the 1.0 in `spiel.c` are literals, as in the
  reference (the 1.0 folds into LIBCMT's `__real@8@3fff8000000000000000`, ordered in
  `common-data-order.txt`). Changing either alone swaps two reload blocks at the function tail; both together
  match.
- **Base relocations.** Every absolute address the reference relocates must be a symbol in the source.
  `scripts/symbolize_addresses.py` rewrites `(T*) 0xVA` casts (also `&row + offset`); loops need both ends
  named (`p < (int) sym + extent`), with the original's signed or unsigned compare: naming only the start
  changes the strength-reduced loop. Float constants in `.rdata` are the users' `__real@4` literal pools
  (ahm_ExAllocAlchemist at 0x100256a0..c8, gv_ExAllocGraveyardWorker's 1000/8/4), placed by
  `common-data-order.txt`; `g_download_state` is one struct (`WHOLE` in the generator), and that store order
  is what fixes `srv_LoadBuf`. Missing sites went from 473 to 0. The last two needed a spelling
  change besides the name: `ahm_ExAllocAlchemist` writes the slot's 0xffff through `g_slot_table` so
  the named `g_citizen_count` read can replace the literal, and `gm_InitObjektHersteller` stores
  `((int*) g_minimum_manufacturer)[ent_idx]` (the `(int) g_minimum_manufacturer + ent_idx * 4` form
  changes `gm_Open`'s register use).
- **TU boundaries from the literal pools.** VC6 emits a TU's string literals after its plain `.data`, so
  plain data after another object's literals starts the next TU. On that evidence `g_alchemy_random_table`
  through `g_chain_handler_table` and `gm_GetFieldByType` are command.c's, `plt_TableLookup` with its pair
  table is its own TU (`plant_pairs.c`, opening an 8-aligned block), and the strings of aemter, alchemistry,
  plant, broadcast and vfs are literals at their uses. Objects link in file-name order (Units, then the
  server, then the add-on files, alphabetically), and both client builds name the network unit
  `D:\develop\units\net\net.c`, so the data-only winsock string TU is `Units/net/net.c`. In the map, every game object's `.data` is now plain data followed by `??_C@`
  literals. `rebrew source rehome` re-points a moved function's row.
- **`gm_Open` depends on the TU's declarations.** Adding or removing a file-scope declaration, even an
  unused one in an included header (`game_data.h`), or a new line before it, changes its code; block-scope
  `extern`s inside the using function do not.
- **`.reloc` VirtualSize is LINK's reservation**, `12 * N` for N input DIR32 records (section 76). Restoring
  relocations raised it from 49296 to 51288 bytes; 5f has the current reservation.
- **Load order of the late CRT members and the imports (2026-10-07).** The original link had no include list
  past the code members it needed: `setlocal.obj` pulled getqloc, initnum, initctyp and initmon (code
  discarded, `.bss` kept), and initctyp pulled `a_str.obj`. The include list therefore stops after
  `_strpbrk` (its entries after `_toupper` are in `bss_head2.c`, 5f) and LIBCMT's own references load the rest, which places those members' `.bss` before
  `a_str` and `GetCPInfo` before `GetStringTypeA` as in the reference: `.data` is byte-identical. A late
  alias object aligns `_RtlUnwind@16` (section 20); it is now OLDNAMES' `mkdir` alias (5e), not `chr.obj`.
  The imports load in the reference's hint/name order: `scripts/gen_import_includes.py` forces only the 28
  KERNEL32 imports of the first library pass (the game's), then USER32, WS2_32 (reversed) and WINMM; the CRT's
  imports and RtlUnwind follow naturally. Every DLL's hint/name order then equals the reference's except
  `GetLastError` (load index 42 against 37; no loaded member between `toupper.obj` and `realloc.obj`
  references it). Raw `.rdata` differs in 242 bytes (was 1768).
- **Left:** `GetLastError` now loads at index 37 and the hint/name order is exact (5f); the IAT slot order and
  the `.reloc` reservation remain (5e explains them, 5f has the current numbers).

### 5e. The server was linked from source files shared with the client (2026-10-07)

The game's source files (`spiel.c`, `aemter.c`, `net.c`, ...) were compiled into the clients and the server.
`/O2` implies `/Gy`, so the server's `/OPT:REF` discarded every function the server never calls: the TL
client's `aemter.c` holds about 19 KB of code, the server's 2.9 KB. The discarded functions still shaped the
server image, and the remaining differences are their fingerprints. The general rules are in rebrew's
`rebrew-data-analysis` skill, `references/link-fingerprints.md`. Section 5f has the reconstructed code and the
current measurements.

- **Rich header.** The reference's `@comp.id` counts: game C objects (10/8966) 37, LIBCMT C members (10/8047)
  124, weak-alias objects (12/7291) 6, import members (1/0) 126, descriptors and null thunks (19/8034) 9, asm
  members (14/7299) 22. Before any reconstruction (main at f829a810) this build had 36, 113, 1, 109, 9 and 22:
  the original linked more LIBCMT C members, alias objects and import functions, and no extra DLL.
- **IAT order.** LINK sorts the `.idata$4`/`.idata$5` contributions with MSVCRT 6.0.8797's `qsort` (middle
  pivot, no median-of-three, selection sort for runs of 8 or fewer, leftmost maximum), comparing only the
  module file name. The array is every loaded import member in `/VERBOSE` load order, dropped ones included,
  plus each DLL's null thunk; each null thunk then moves to the end of its DLL's run. A Python port of this
  predicts this build's IAT exactly for all four DLLs over every relink measured. The bytes fix only the
  array, not which functions loaded the dropped members.
- **A fully dropped DLL leaves its name.** LINK keeps the DLL name string when all its imports are dropped
  (ADVAPI32 and WINSPOOL probes added `ADVAPI32.dll`/`WINSPOOL.DRV` to the import area); the reference has none,
  so the extra imports come from KERNEL32, USER32, WS2_32 and WINMM.
- **`.reloc` reservation.** DIR32 records in discarded functions and discarded data COMDATs count, REL32 do
  not: a discarded function with 1261 absolute stores gives exactly the reference's 66420, `SizeOfImage` and
  file size, with no other byte changed. All 3499 relocation sites are present (`rebrew binary relocs`).
- **Load position.** A discarded CRT reference loads its member where it is first referenced, so the CRT
  anchors after `_toupper` are read from `bss_head2.c` instead of the command line (5f).
- **Shown, not adopted.** A synthetic discarded TU (placeholder API calls and CRT references) reproduces
  `.text`, `.rdata`, `.data` and the Rich header byte for byte. It proves the model but invents code, so
  the build instead reconstructs the real client-only functions in the shared files (5f). Discarded code must
  still link, because LINK resolves references before it discards, so only functions whose callees and globals
  exist in the server belong in the server build.
- **Weak-alias objects and old names.** Rich product 12 build 7291 marks LIBCMT's 40 `tcmap` members and all
  230 `OLDNAMES.LIB` members, the alias objects that map a POSIX name (`mkdir`, `getcwd`, `stricmp`, `itoa`,
  ...) to the underscore function. No LIBCMT member references a `__tcs` name, and the TL client calls no
  `_mbs*` function from game code, so the reference's six are old-name references (or `_tcs` calls in
  server-only code, which no binary preserves). Because OLDNAMES is searched after LIBCMT, an old-name
  reference loads its LIBCMT member one pass later than the underscore name would: `vfs_MakeDirs` calls
  `mkdir`, and `CreateDirectoryA` now loads after every CRT import (load index 130), where the exact IAT
  solution (5f) puts one dropped import. Any such alias loaded late gives `_RtlUnwind@16` the alignment that
  `MSVCRT.LIB(chr.obj)` used to provide, so `bss_late` now compiles `-MT` like the DLL (`-MD` named MSVCRT as
  a default library, which resolved late CRT references to MSVCRT.dll imports) and no `__tcschr` include
  remains.

### 5f. Reconstructed client code in the shared files: status (2026-10-08)

Every function below is ported from Europa1400Gold_TL.exe (TL), written against server symbols, and called by
no server function, so `/OPT:REF` discards it. None has a row in `rebrew-functions.toml` (no server VA).

- **`Units/net/net.c`.** The client's TCP connection functions (TL 0x4208a0..0x421347, nine functions). They
  load seven WS2_32 members the server lacks (`inet_ntoa`, `gethostbyname`, `gethostname`, `getsockopt`,
  `select`, `connect`, `inet_addr`) and add 170 DIR32 records. Their client state has no proven server
  allocation and is `selectany`. Not added: the client's broadcast open (TL 0x402220), whose `GetLastError`
  call would load that import in the game's KERNEL32 pass (load index 28; the reference has 37), and the rest
  of the client browser (TL 0x402320..0x402604), which adds `recvfrom` and `fprintf.obj` with no measured
  support.
- **`vfs.c` is the client's vfs TU, with its directory tree.** The TL client's `.data` holds one literal pool
  from `0x679e60` to `0x67a0d4`: the gzip magic words (plain data, read by `vfs_ReadData`/`vfs_OpenStream`),
  then literals in creation order from `vfs:IGetSubDir` (0x42e5a0) through `%i vfs_file(s) were left open!`
  (0x4310f0). The directory tree, the `.BIN` file search, `vfs:Open`, `CloseVfsStream`, `vfs_ReadData`,
  `vfs_OpenStream` and `vfs_init` (0x431070) are one TU, the server's `vfs.c`; its `.BIN5`..`.BIN` table is
  `g_file_extension_names`. Built, in the client's order before `CloseVfsStream`: the whole tree, TL
  0x42e4d0..0x42fe60 (26 functions: name compares, `vfs_GetSubDir`, `vfs_FindFile` (`bsearch`),
  `vfs_AddFile`, `vfs_FinishFiles` (`qsort`), path lookups, the file search `vfs_ScanDir` (0x42f6d0), the
  archive scan `vfs_ScanArchive`, `vfs_MakeDirs` and `vfs_RemoveFile` (`remove`, `memmove`)); after
  `vfs_OpenStream`: `vfs_init` (`getcwd`). Compiled from `vfs.c`, every one matches the TL client in all
  common bytes (`rebrew test -t Europa1400Gold_TL.exe`) except `vfs_AddFile`, whose two array moves use the
  aligned-copy asm of `vfs_ReadData` and allocate registers differently (1477 bytes against 1472); a
  `memcpy` there would load `memcpy.obj`, an assembler member, early.
- **vfs.c's file API (round 18).** The rest of the client TU is built too, in its order: `vfs_Tfopen`
  (0x42ff50, the `vfs:Open`/`vfs_Tfopen` messages) after `vfs_RemoveFile`; `vfs_fgetc`, `vfs_fgets`,
  `vfs_fwrite`, `vfs_fseek` and `vfs_ftell` (0x430870..0x430c50) after `vfs_ReadData`; `vfs_ForEachFile`
  (0x430f70) after `vfs_OpenStream`; `vfs_exit` (0x4310f0, `%i vfs_file(s) were left open!`) after
  `vfs_init`. `vfs_Tfopen` opens loose and new files through `gzopen`, which only links now that gzio.c is
  stock; its storage is the stream pool and count, the tree root and `g_file_extension_names`. `vfs_exit`
  walks and frees the pools through m_alloc.c's client pool helpers (TL 0x41e350..0x41e4d0, after
  `m_pool_free`: next, first, free-all, clear, info, stats), and m_alloc.c gains the client's
  `m_is_tracked` (0x41dd90, `g_array_count`/`g_array_ptr`). Under the TL client's code generator
  (Processor Pack, `rebrew test -t Europa1400Gold_TL.exe --no-promote`) every one matches the client in all
  common bytes except `vfs_Tfopen` (register and frame layout; 22 DIR32 like the client) and
  `m_pool_next` (register choice, no fixups). No CRT member or import is added (all already load). 40
  more DIR32 records.
- **The tree's references.** The file search calls `FindFirstFileA`, `FindNextFileA`, `FindClose`,
  `FileTimeToLocalFileTime` and `FileTimeToSystemTime` directly, so they load in the game's library pass
  after Error.c's imports, as the exact IAT solution needs; `import-includes.rsp` now forces only Error.c's
  twenty KERNEL32 imports (an `/INCLUDE` would keep a dropped import), and server.c's eight load in their
  hint/name order on their own. The name compares call `stricmp`, `mkdir` and `getcwd` by their old names, so
  OLDNAMES resolves them: `stricmp.obj` keeps the late position `getqloc.obj` gives it (the reason the
  previous round ruled the tree out), and `mkdir.obj` and `getcwd.obj` load after LIBCMT's first pass.
  `vfs.c`'s first-pass group is now `toupper`, `strupr`, `bsearch`, `qsort`, `findfile`, `unlink`,
  `memmove`.
- **Tree storage.** The client keeps its tree root and pending-item pool at 0x6b7fdc and 0x6b7fe0, below the
  stream pool (0x6b7fe4), flag (0x6b7fe8) and stream count (0x6b7fec). The server has the same three at
  0x10034670..0x10034678 and two dwords below them that no relocation in the reference addresses, so they
  are `g_vfs_root` (0x10034668) and `g_vfs_item_pool` (0x1003466c). The flag is set for case-insensitive
  compares (`stricmp`) and clear for upper-casing names before plain compares, despite its name.
- **minizip is its own TU (`Units/vfs/unzip.c`).** The server's `unzClose`, `unzReadCurrentFile` and
  `unzCloseCurrentFile` (formerly `vfs_DestroyEntity`, `vfs_ReadCompressed`, `vfs_CleanupObject`) compile
  from zlib 1.1.3's stock `contrib/minizip/unzip.c` to the reference bytes, and every other stock function
  matches the TL client, which keeps the unit apart from vfs.c (0x4645a0..0x4657d0). The server's readonly
  data holds the unit's ` unzip 0.15a Copyright 1998 Gilles Vollant ` right before vfs.c's `.BIN` table. The
  vendored file lists its changes: the 0.15a copyright string (selectany, ordered as before), the client's
  `unzGetFilePos`/`unzGoToFilePos` (TL 0x465750, 0x465790) appended, SIZE comments. It links between
  `trees.c` and `vfs.c` and leaves every function VA unchanged; Rich counts one more game C object.
- **zlib is stock 1.1.3, whole files (round 18).** The vendored files had every function the server does not
  call removed (`#if 0`, "not present in original DLL"), which `/OPT:REF` drops anyway, `gzio.c` was replaced
  by a decompiled copy (`Units/vfs/gz_stream.c`, `vfs_GetByte` for `get_byte` and so on), and `trees.c` was
  split into `trees.c` and `trees2.c`. Compiled whole, stock `gzio.c` gives the server's eight gzio functions
  byte for byte, and one stock `trees.c` gives the server's function order: VC6 emits a static function
  after the first function that references it (`get_byte` after `check_header`, `putLong` after
  `gzclose`, `build_tree` after `_tr_flush_block`). The discarded public gzio functions load exactly the
  four LIBCMT members the Rich header was short, in the first library pass and with no new import or data
  byte: `fprintf.obj` (gz_open's header), `fdopen.obj` (gzdopen; `zutil.h` maps `fdopen` to `_fdopen` for
  MSC), `vsprintf.obj` (gzprintf) and `rewind.obj` (gzrewind). `gzsetparams` needs `deflateParams`, so
  `deflate.c` must be whole as well. The four bytes `border[]` carried after its 19 entries are
  `inflateSync`'s `mark[4] = {0, 0, 0xff, 0xff}`, a static whose plain `.rdata` follows `infblock.obj`'s:
  `border` is stock again and `mark` is a selectany object ordered after it, anchored by
  `game-includes.rsp` (`gen_game_includes.py` ZLIB_ANCHORS; a `/include` directive in `inflate.obj` itself
  does not keep it, `/VERBOSE` reports it discarded). `compress.c` and `uncompr.c` stay out: they would be
  two more game C objects. The restored code adds 30 DIR32 records; Rich now counts 124 LIBCMT C members
  and 37 game C objects, both equal to the reference.
- **Late CRT anchors.** Object references load after the whole command-line include list, so the anchors from
  `_memmove` to `_strpbrk` are in `late-archive-includes.txt`, which `scripts/gen_bss_layout.py` writes into
  `bss_head2.c` as `#pragma comment(linker, "/include:...")`. LINK reads `bss_head2.obj` after `vfs.obj`; the
  vfs group above already loads `memmove.obj`, and `findfile.obj` puts `GetLastError` at the reference's load
  index 37. A directive in `vfs.c` itself would not work: LINK takes an object's directives before its
  symbols.
- **spiel.c's unit conversions and price formatting (round 18).** TL 0x50b710, 0x50b750, 0x50b780 and
  0x50b7a0, before `gm_QueryEntitySum`, divide or multiply an amount by an item's units per trade unit,
  `g_spiel_space_fill[id - 61]` (16 dwords of 32 for item ids 61..76). The client addresses that table as
  0x6995bc, 61 dwords below it: spiel's `.data` maps to the server's at +0xf997808 up to the client's
  extra 6-byte record at 0x6995d8 and at +0xf9977fc from the table on (`.scratch/measure/align_bytes.py`),
  the table's bytes are identical, and no other code in either image reads it. The item id is the first
  word of `g_entity_slot_table`'s record, as in `gm_QueryEntitySum`. TL 0x50bb50 (`gm_GetSeasonPrice`)
  reads `g_slot_array`'s 0x2a90-byte season tables like `gm_FindSlotById` (client 0x85ab90 is server
  0x1009b770, the offset `g_entity_slot_table` has) and falls back to `gm_CalculateProductionValue`.
  TL 0x50bc10 (`gm_FormatPrice`) groups thousands with dots through `itoa`: the client's only `_itoa`
  call in a server TU. `xtoa.obj` already loads for `getqloc.obj`, so the old name adds the fifth alias
  object and nothing else. All six match the client in all common bytes under its code generator except
  `gm_FormatPrice` (one x87 load scheduled before a string scan). 16 more DIR32 records.
- **Random helpers are their own object (`game/zufall.c`).** Both clients hold `gm_RandomMod`, a range helper
  (`gm_RandomMod(2n + 1) - n`), `gm_RandomFloat01`, `gm_RandomQuadratic`, a squared `gm_RandomFloat01` (TL
  0x42e4a0), `srv_SeedRandomWithTime` and `srv_SeedRandom` contiguously (TL 0x42e410..0x42e4c5), after a trace
  unit (`tr_*`, 0x42dfb0..) and apart from spiel.c's client span. The server's five sit after spiel.c's last
  function, so the object links last; no path string names it. The range and squared helpers are discarded
  code. The trace unit is not in the server: its initialized pointers to `"*bRaIn DeaD%&"` and
  `"%aRscH Ab :-)"` would keep those strings, and the server has neither.
- **No timer unit.** The clients' `tb_*` multimedia-timer unit (TL 0x42dcd0..0x42df70) is not built. Its
  five dropped WINMM imports (`timeSetEvent`, `timeBeginPeriod`, `timeGetDevCaps`, `timeKillEvent`,
  `timeEndPeriod`) cannot coexist with net.c's seven dropped WS2_32 imports. The IAT permutation depends only
  on the DLL-key sequence of the contribution array, so the model can be inverted per split (below): with the
  reference's 26 dropped imports (Rich: 126 import members, 100 live), an exact IAT needs w + m = 5 or 7
  dropped WS2_32 and WINMM imports, also with 1 to 3 dropped USER32 imports; 7 + 5 has no solution. net.c's
  TCP functions sit in the TU whose winsock strings the server keeps; the timer unit had no path evidence,
  and its storage was offsets into the unnamed `g_gap_10035a10`. Without it Rich counts 37 game C objects like
  the reference (three of them are the generated BSS objects).
- **Game TUs.** 148 function definitions, each placed after the server function that precedes it in the
  client: `aemter.c` (TL 0x4e8a80..0x4ec810) and `server.c` (0x4e73c0..0x4e7c70) office and stat-dump helpers;
  `friedhof_logic.c` slot helpers (0x4f1790..0x4f1890, 0x4f1a10, 0x4f3800, 0x4f3e60); `plant.c` record lookups
  (0x4bcc20, 0x4bcc50); `sim.c` family, age and directory helpers (0x4ff860, 0x4fffb0, 0x500240, 0x500480,
  0x500660); `alchemistry_logic.c` recipe, avatar and trait helpers (0x4ec8a0..0x4ece30, 0x4eceb0,
  0x4eefe0..0x4ef0d0, 0x4f0eb0, 0x4f0f60, 0x4f0ff0..0x4f1290, 0x4f13a0, 0x4f1450, 0x4f14c0); 76 `spiel.c`
  definitions (game-clock, query, store and ranking helpers, four building-upgrade counters, and the item and
  building type lookups by name, TL 0x501490 and 0x504eb0, which call `strcmpi` by its old name); and
  `loadsave.c`'s relationship-matrix loader (0x524610). 0x500660 calls
  `_findfirst`/`_findnext`/`_findclose`, the same `findfile.obj` as `vfs_MakeDirs`. 0x500480's scan cursor
  (TL 0x773d64) is the last dword of the server's unnamed 0x10035410 block, below `g_next_family_index` as in
  the client. Not ported: client copies of server functions (amt_FindEntity27, amt_ClearEntityLinks,
  AssignProductionSlot, cm_GetBuildingStatCount, and the spiel functions that are server functions:
  `gm_InitObjektHersteller`, `gm_ObjectsAvailble`, `gm_ff_Objekt`, `gm_SubObjekt`, `gm_SubObjectNoKill`,
  `gm_FindNextFilteredEntity`, `gm_MapEntityStatRange`, `gm_LookupEntityRecordById`, `gm_EntitySetField`);
  plant's box cache 0x4bd1e0, which calls `_stricmp` and `_strnicmp` (an underscore-name game reference loads
  those members in the first library pass, ahead of where the reference has them; the old names do not, see
  5e); functions whose storage has no server allocation (aemter 0x4e98d0, alchemistry's card deck and
  player prototype, sim 0x5007f0..0x500a20, most client-only loaders) and functions reaching them (spiel
  0x502780, friedhof 0x4f1a40); and TL 0x522e30, the client's `ls_LoadEntities`.
- **ICF survivor.** LINK folds the identical `_strncnt` COMDATs of `a_cmp.obj` and `a_map.obj`; the reference
  keeps `a_cmp.obj`'s. LINK 6.00.8447 decides it with MSVCRT `qsort`: COMDAT resolution (0x4627e0) appends
  every executable COMDAT it keeps as a definition to one array, in resolution order (command-line objects,
  then archive members in load order), before `/OPT:REF` and including code it later discards; 0x433690
  sorts the array by section size, then relocation count (comparator 0x4337f0), and 0x433fd0 folds each
  identical later section into the first one of its run. The two `_strncnt` copies have equal keys, so the
  unstable sort decides from every executable COMDAT's size and relocation count. Adding or removing discarded
  code, or loading a member in another pass, can flip it. `.scratch/measure/icf_predict.py VERBOSE_LOG
  BUILD_DIR` rebuilds the array and predicted the survivor in 42 of 42 native links (31 `a_cmp`, 11 `a_map`).
- **IAT inversion.** The import sort compares only the DLL file name, so the IAT permutation depends only on
  the array's DLL-key sequence: KERNEL32 x (28 + h), its null thunk, USER32 x 2, null, WS2_32 x (16 + w),
  null, WINMM x (1 + m), null, KERNEL32 x (53 + t), where h counts dropped KERNEL32 imports of the game's
  first library pass and t those of the CRT pass. Per split, CP-SAT picks which positions are dropped so that
  every DLL's live imports, named in hint/name (load) order, land in the reference's slots
  (`.scratch/measure/iat_cpsat.py`; `iat_gaps.py` enumerates placements, `iat_nearest.py` finds the one
  nearest a given gap vector, `iat_hyp.py` checks a named array). With h + w + m + t = 26 the exact splits
  are (h, w + m, t) = (3, 5, 18), (5, 5, 16), (5, 7, 14) and (7, 5, 14). None has h = 0: the original's game
  objects referenced KERNEL32 functions that `/OPT:REF` dropped.
- **An exact IAT from real client code.** One named array reproduces all 100 reference slots with the
  model (`iat_hyp.py`): round 16's array without the timer's five WINMM imports, with the vfs file search's
  five KERNEL32 imports (`FindFirstFileA`, `FindNextFileA`, `FindClose`, `FileTimeToLocalFileTime`,
  `FileTimeToSystemTime`, TL 0x42f6d0 calls them directly) after `FreeConsole` (vfs.c links between Error.c
  and server.c), `DeleteFileA` after `GetLastError` (`remove` in TL 0x42fe60 loads `unlink.obj` with
  `findfile.obj`), and four imports after `SetEnvironmentVariableA` (`getcwd.obj`'s `GetCurrentDirectoryA`,
  `GetFullPathNameA`, `GetDriveTypeA` and `mkdir.obj`'s `CreateDirectoryA`, loaded through OLDNAMES aliases
  after LIBCMT's first pass). That is (h, w, m, t) = (5, 7, 0, 14); the placements around it are not unique.
  The tree port above builds exactly this array, and the native link's IAT equals the reference's.
- **The building-site box cache (round 18).** plant.c's client TU continues after `plt_SetPlantMap` with the
  3D vegetation loader, the box cache and the `rd_` building-site helpers; their literals (`!bk_`, `bk_`,
  `rd_GetBKSize(): Unbekannter Bauplatz '%s'`) sit in plant.c's client literal pool. The cache is the
  server's `g_aux_entity_count`/`g_aux_entity_buffer`: `ls_LoadBuildingEntityState` (server 0x100128f0,
  client 0x522510) reads a count and `realloc`s the buffer to count * 0x60 bytes, then reads 0x40 + 0x10 +
  0x10 bytes per record, exactly the client's box records (name, low and high corner) at 0x10058e0 and
  0x10058e4 (`.scratch/measure/anchors2.py` pairs the two loaders' operands). `rd_AddBKBox` (TL 0x4bd1e0)
  calls `strnicmp` and `strcmpi`: the client's only `_strnicmp` caller in a server TU, and `strnicmp.obj`
  already loads for `getqloc.obj`, so the old name adds the sixth alias object and nothing else. It needs
  only `realloc` and a call through the 3D object's interface. 34 DIR32 records. Its neighbours call engine
  code the server lacks; `rd_GetBKSize` (0x4bdf40) is built with the placeholders (below).
- **Savegame writers (round 18).** The client saves; the server only loads. Each writer mirrors a server
  loader field by field and calls `vfs_fwrite`, which is only linkable now: `ls_SaveObjects`,
  `ls_SaveDynamicEntities` and `ls_SaveRelationships` (TL 0x51ebc0, 0x51f170, 0x520860, before
  `ls_ReadVfsDataChecked`), `gv_fio_SaveGraveyardData` (0x4f3900, before `ls_LoadGraveyardData`) and
  `ahm_fio_SaveAhmInfo` (0x4eed10, before `ahm_AllocAhmInfo`). Their storage is the loaders'
  (`g_query_base`, `g_entity_base`, both relationship matrices, the graveyard slot and the alchemist record).
  `vfs_fwrite` returns `unsigned int` like `fwrite`: the client tests its result with `ja`/`jbe`. spiel.c
  also gains `gm_SlotKindIsOneOf` (0x506ee0, variadic, `g_slot_table`). All match the client in all common
  bytes under its code generator.
- **The server's log macro (round 18).** The server build expands the game's log macro to
  `LogMessageInternal(file, line, message, level)`; the clients compile it to nothing. Server
  `amt_fio_LoadAemter` logs every failed field ("Can't load id", ...), client 0x4ec520 has no such call;
  server `ahm_ExAllocAlchemist` logs three errors, client 0x4ee290 none. A formatted message survives in the
  client as an unused `sprintf` into a local buffer (client `amt_fio_SaveAemter` 0x4ec410, `rd_GetBKSize`,
  `vfs_Tfopen`, `vfs_init`); a literal message leaves no trace. So a client-only function's server copy can
  hold `LogMessageInternal` calls, two DIR32 records for each literal message and one for each formatted
  one, that no binary records. The ports carry the client's code only. This bounds what any reconstruction
  from the clients can prove: the exact `.reloc` reservation needs the server's log calls in discarded code,
  which no image shows. A dangling `sprintf` is not proof of a log call either: the live server
  `gm_KillSpieler` (0x10017fb0) formats two messages into a local buffer and logs neither.
- **Placeholder log calls (round 19).** A stopgap, requested until real code is found: 211
  `LogMessageInternal(path, __LINE__, message, 1)` calls, each marked `/* placeholder: inferred server log
  call, see msvc6-link-layout 5f */`, in discarded client-only functions. They supply 404 of the 412 missing
  DIR32 records; `amt_fio_SaveAemter` (TL 0x4ec410, before `amt_fio_LoadAemter`, without log calls) and
  `rd_GetBKSize` (TL 0x4bdf40, after `rd_AddBKBox`), ported in the same change, supply 8. `path` is the
  TU's `__FILE__` string as its live calls spell it; the line argument is the placeholder's own line, since
  the server's is unknown. The set, `.scratch/measure/placeholder_spec.tsv` (applied to a clean tree by
  `apply_placeholders.py`), has five tiers, strongest first:
  - 14 formatted: the client builds a message into a local buffer and drops it (`vfs_AddFile`,
    `vfs_Tfopen`, `vfs_init`, `rd_GetBKSize`, `nt_Connect` x2, `nt_Recv` x3, `srv_FormatStatDumpBegin`/`End`,
    `ahm_fio_LoadAvatars` x3); the call logs that buffer.
  - 53 guard failures: invalid argument, open/read/write failure, overflow, as server `amt_fio_LoadAemter`,
    `gm_SubObjekt` and `ahm_ExAllocAlchemist` log theirs (`ahm_fio_SaveAhmInfo` and `ahm_fio_LoadAvatars`
    per field, `nt_Connect`'s socket setup, `vfs_fwrite`, `vfs_MakeDirs`, spiel lookups).
  - 19 not-found fall-throughs of lookups, as `plt_SetPlantMap` logs before its final return.
  - 106 entry traces and 19 exit traces (`"<function>(): enter"`/`"exit"`, as `gm_Open` logs), with no
    evidence beyond the macro's use in sibling functions: they fill the count. The exit traces sit in the 19
    longest functions.

  Each call costs one DIR32 for the path and one for a literal message (none for a buffer); in
  `gv_HasGravediggerRoom`, `vfs_MakeDirs` and `vfs_Tfopen` the compiler shares one `push path; call` tail
  between two calls, 4 records fewer (`.scratch/measure/log_relocs.py` counts calls and path records per
  function). Message literals are `??_C@` COMDATs in `.data`; referenced only from discarded functions they
  are discarded too, and no `.data` byte changes. The path literal is different, because the TU's live calls
  keep it, and VC6 emits a literal's COMDAT with the first function that references it. Measured: a call in
  `ls_SaveObjects` moved loadsave.c's path literal ahead of `ls:tmp`, `AHM_INFO` and `f3g:PlantMap` (122
  `.data` bytes); calls in `amt_fio_SaveAemter`, directly before `amt_fio_LoadAemter`, reordered
  `amt_fio_LoadAemter`'s own literals (229 bytes). `.scratch/measure/log_sites.py VERBOSE_LOG BUILD_DIR MAP`
  lists the discarded functions where no kept literal of the object lies between the function and the path
  literal; only those carry placeholders, and the build confirms each set. That excludes loadsave.c's
  savers, aemter's office helpers before `amt_fio_LoadAemter`, the alchemistry recipe helpers, friedhof's
  slot helpers, plant's record lookups and spiel's game-clock helpers. Under that emission rule the reference
  also shows that the server's loadsave.c had no log call in any function before `ls_ID2Ptr`. Stock zlib and
  minizip, and `zufall.c`, which has no path string, get none. The final set keeps `a_cmp.obj`'s
  `_strncnt` (the two ports alone flip it to `a_map.obj`, as in round 18). Replace a placeholder when the
  server's real code for that function is known, then re-tune the rest to the count.
- **Ruled out (round 18).** The four -1 dwords the client's command.c keeps between `g_game_speed_index` and
  the dispatch table (TL 0x68a9d0..0x68a9dc) sit inside plain `.data`, which LINK never discards, and the
  server has none: they and the helpers reading them (TL 0x4c4dc0, 0x4c76c0, 0x4c7870, 0x4cc590) are not in
  the server's source. The client's command.c functions that the portability scan reports (TL 0x4cb6f0,
  0x4cc2b0, 0x4cd750, 0x4cd7a0) are entries 57, 64, 92 and 93 of the client's dispatch table: client
  versions of server handlers, not extra functions. Error.c's `GILDE_SEASON`/`GILDE_DISASTER`/`GILDE_DAYTIME`
  registration (TL 0x41db30) calls a client debug-variable unit and its three dwords are absent from the
  server's Error.c storage; TL 0x41ca10 (nearest palette colour) belongs to a client graphics unit. sim's name
  table (client 0x773d3c..0x773d44, read by 0x5007f0..0x500a20) is defined in a client-only TU before
  sim.c. Address brackets between equal-offset anchors are not proof by
  themselves: aemter's TL 0x4e98d0 brackets onto `g_module_path`, which the server uses.
- **Game `.bss` layout (round 19).** Measured with this toolchain (`.scratch/r19/alchemy-bss/` probes, CL
  12.00.8966 and LINK 6.00.8447): LINK places every object's ordinary `.bss` section in object order, each at
  its section alignment, then all COMMON symbols after the last `.bss` contribution (the CRT's included):
  objects in reverse input order, each object's COMMONs in reverse symbol-table order, 32-byte alignment for
  COMMONs of 32 bytes or more. Inside one object's `.bss`, CL puts the uninitialized statics first, in an
  order that ignores declaration and use order (three orders of the same eight statics gave one
  layout), then the `= 0` definitions in definition order. The section is 8-aligned when it holds a
  `double` or an array of 0x170-byte structs, 4-aligned for `int`, `short` and `char` arrays. The server's
  early `.bss` (0x10034610..0x10035497) is this ordinary-section run: Error.c, m_alloc.c and vfs.c have the
  same internal layout as in the TL client (anchor offsets 0xf97d6c8, 0xf97d6c0, 0xf97c68c), and the run
  follows the server's object order.
- **The alchemistry state is not the clients' (round 19).** `g_gap_10034684` (0x10034684..0x10035407, 3460
  bytes, no server reference) lies between server.c's `g_handler_started` and `g_sequence_counter`
  (server loadsave.c reads 4 bytes into it and falls back to 1000000; TL 0x521920 does the same with
  0x773d38). By the layout above it holds the `.bss` of every object between them in link order, which
  includes `alchemistry_logic.obj` and the next object. In the client these are two objects: the
  avatar-table unit's plain `.data` (TL 0x68e020..0x68fea0, 7808 bytes) starts after alchemistry's literal
  `ahm_AllocAhmInfo` and equals server 0x1002a1d0..0x1002c050. Their statics are TL 0x772f78..0x772fe7
  (112 bytes: a 0x60-byte block that TL 0x4edd30 reads field by field, then four dwords) and
  0x772fe8..0x773d37 (3408 bytes: a 14-byte copy of the game clock, 56 x 8 bytes, 8 x 0x170 records), ending
  at `g_sequence_counter` (0x773d38); Europa1400Gold.exe has the same sizes at 0x6f0dc8..0x6f1b87. With both
  sections 8-aligned they would need 0x10034688..0x10035447, 64 bytes past `g_sequence_counter`, so the
  server compiled different storage. Its plain data differs too, and LINK never discards plain `.data`:
  both clients' alchemistry `.data` starts with {1, 3, 7, 11, 13, 17, 19, 21} (TL 0x68dec0, GOLD 0x60f190),
  read by the deck shuffle TL 0x4ecaa0; the server holds those 32 bytes nowhere, and its alchemistry `.data`
  starts with 1.0f and 0.5f (0x1002a0f0, `g_alchemy_one`/`g_alchemy_half`), which no server code reads and
  neither client has there. From `g_sequence_counter` to `g_next_family_index` the clients have 48 bytes
  (TL 0x773d38..0x773d68, GOLD 0x6f1b88..0x6f1bb8), the server 36. So the server's alchemistry sources
  differ from both clients' in data and storage, and no image records the server's layout. A 0x168-byte
  record or a 48-entry array would each fill the gap exactly if no other object has `.bss` there, but no byte
  selects either, so the deck, player-prototype and alchemist-table code (TL 0x4ec9e0..0x4ecc20,
  0x4ed240, 0x4ed800, 0x4edce0..0x4ee080, 0x4ef2e0, 0x4ef770, 0x4efc50..0x4efd70, 0x4f0960, 0x4f09c0,
  0x4f0c90, 0x4f0da0, 0x4f0e40) is not
  ported. Round 18's reason was a mispairing: the server's `ahm_LookupEntityInTable` is TL 0x4ce590 in the
  client's command.c span and reads the same 10 x 0x5c table (TL 0x68b400, bytes equal to server
  0x1002c050); TL 0x4efd30 is a different lookup over the 0x170-byte records.
- **Measured** (native link of the committed tree against `original/Server/server.dll`; `.scratch/measure`
  scripts: section byte compare, IAT and hint/name compare per DLL, Rich records, link map, ICF predictor):

  | | main f829a810 | round 16 fcfdd827 | round 17 477dc53e | round 18 bd322c10 | now (placeholders) | reference |
  |---|---|---|---|---|---|---|
  | functions at reference VA | 260 | 260 | 260 | 260 | 260 | 260 |
  | `rebrew verify` | not re-run | 316/316 | 316/316 | 316/316 | 316/316 | |
  | `.text` differing bytes | 138 | 146 (all IAT operands) | 0 | 0 | 0 | 0 |
  | `.rdata` differing bytes | 242 | 122 | 0 | 0 | 0 | 0 |
  | `.data` differing bytes | 0 | 0 | 0 | 0 | 0 | 0 |
  | hint/name order diffs | 6 (KERNEL32) | 0 | 0 | 0 | 0 | 0 |
  | IAT slots off the reference | 53 of 100 | 37 of 100 | 0 of 100 | 0 of 100 | 0 of 100 | 0 |
  | Rich game C / LIBCMT C / alias / imports | 36 / 113 / 1 / 109 | 38 / 116 / 1 / 127 | 38 / 120 / 4 / 126 | 37 / 124 / 6 / 126 | 37 / 124 / 6 / 126 | 37 / 124 / 6 / 126 |
  | `.reloc` VirtualSize | 51312 | 59928 | 59868 | 61476 | 66420 | 66420 |
  | header bytes differing (`cmp`, first 0x400) | | | 269 | 6 | 0 | |
  | file size | | | 8192 short | 4096 short | 286720 | 286720 |

  `rebrew binary relocs` reports all 3499 sites and no extra one. With the placeholder log calls the linked
  `server.dll` is byte-identical to the reference (`cmp`).
- **Left:** 404 of the 5535 DIR32 records come from placeholder log calls, not recovered code. Their real
  sources are discarded server code: client-only functions whose storage is not yet mapped (aemter's office
  counters, the loadsave writers that read unmapped tables, spiel's BAD set), the log calls the server's
  discarded functions made, which no binary shows (see the log macro above), and server code that differs
  from the clients' (the alchemistry state above). Each recovered function displaces placeholders and needs
  the set re-tuned to 66420 with `_strncnt` kept.
