# General knowledge: facts about the original game, build, project

Grows with findings. One fact, one bullet, evidence pointer. Anything that
is not C spelling, allocator, wall, trap, or session history lives here:
original build environment, project organization, game-domain facts,
toolchain observations. Naming evidence stays in `naming_conventions.md`;
this file holds the rest.

## Original project

- Developer: 4HEAD Studios (German). Verbs English, game nouns German.
- Original root: `D:\Develop\` (case varies). Game logic: `DieGildeAddOn\`
  (server build) / `DieGildeAddOnVc\` (client T&L build). Shared engine:
  `Units\`. Server entry: `DieGildeAddOnServer\server.c`.
- Evidence: `__FILE__` debug strings + PDB refs in shipped binaries. See
  `naming_conventions.md` source-tree section (canonical file map).

## Original build

- **Europa1400Gold_TL.exe was linked with `/DEBUG`, so `/OPT:NOREF`; Europa1400Gold.exe and the server use
  `/OPT:REF`.** TL carries a PDB path and keeps 298 game-range functions nothing references; Gold has no
  PDB path and 3 such functions, the server none. A TL TU is the client's whole compile of that file
  (`docs/msvc6-link-layout.md` 5f, round 19; `.scratch/measure/unref.py`).
- Compiler: MSVC6. Flags: `/O2 /Gd` default project-wide. Per-file variance
  was swept (codegen-walls §7 item 2, CLOSED): SP6 confirmed **for
  `server.dll`**, flag axis flat, three `sp5-pp` file pins remain. Do not
  re-open *for the server*.
- **The two clients are `msvc-6.0-sp5-pp`, not sp6** (round 1290). The client
  `.text` uses the NaN-safe float comparison `fnstsw ax; test ah,5; jp`, which
  no other available toolchain emits (`sp0`-`sp6` all emit `test ah,1; je`;
  `/O1 /Ox /Op /Za /Gf /G6` flat). Census of that 2-byte-later idiom:
  `Europa1400Gold.exe` 724, `Europa1400Gold_TL.exe` 809, `server.dll` **0**.
  Expressed as a per-target profile in `rebrew-project.toml`
  (`[targets.X] compiler = { profile = "msvc-6.0-sp5-pp" }`): GOLDTL
  `verify --full` 115 -> 121 byte-matched (6 functions straight to RELOC 100%),
  GOLD 208 -> 213, server unchanged at 281.
- **Shared files diverge in *data*, not only in code.** `cm_GetBuildingStatCount` has client
  stat literals 0x10/0x18/0x20 (`+0x10`/`+8`) against the server's 0xc/0x12/0x18 (`+4`/`+2`), and
  `DispatchLogOutput`'s level table has **12** severity bits (1..0x800) in the client against **3**
  (1,2,8) in the server, with client log names `_error.log`, `_ai.log`, `_sim.log`, `_dbg.log`,
  `_script.log`, `_cutscene.log`, `_meister.log`, `_d3.log`, `_stats.log`, `_msx.log`,
  `___tracker.log`, `_meister2.log` (32 bytes each at GOLDTL 0x677948) against the server's
  `__server.log`, `gilde_server.log`, `__dbg.log`. A shared marker therefore does **not** imply a
  shared body: measure each marker before assuming (round 1291).
- **The original source used string literals for allocation tags, not addresses.** `m_AllocTracked`
  tags like `"gv_AllocGraveyardField"`, `"gv_Alloc:_all_graves"`, `"gv_Alloc:_all_zombies"` appear
  verbatim in both binaries at each binary's own `.rdata`; a `(const char*) 0x1002d474` cast only
  matches the binary whose address it names. 200 such casts remain in the tree (round 1292).
- **Not every tracked VA is the right one.** Two GOLDTL markers pointed at VAs where the body scores
  ~9-40% while the same source scores 94-99% elsewhere: `gv_AllocGraveyardField` `0x45e520` ->
  `0x4f1d20` (round 1291), `gm_StartFilteredEntitySearch` `0x502cd0` -> `0x503fe0` (round 1292). A bad
  VA also poisons every caller's REL32 validation, so a "wrong-callee" mismatch is often a wrong
  *catalogue* entry, not wrong C. Test a suspect file at both VAs before editing its body.
- **A shared file can annotate one global once per target.** Two
  `// GLOBAL: <marker> 0xVA` blocks each followed by the same declaration let one C body reference a
  symbol whose address differs per binary; the compiler emits a relocation instead of a baked immediate
  and both targets match. Used for `g_14cc360` (GOLDTL 0x14cc360 / GOLD 0xf8aae0), `g_10058a0`
  (0x10058a0 / 0xf812a0) and `g_10069a0` (0x10069a0 / 0xf82320) in round 1294.
- **Library code sits wherever the linker put it.** The T&L client's statically linked d3dx8.lib
  occupies `0x5e0000-0x64ffff` (~907 bodies) and is declared in `rebrew-project.toml` as
  `external_ranges`; the other static libs (CTLFW32, LUA50, MSS32, LIBCMT) have no contiguous band:
  their VAs are the `// LIBRARY:` rows in `src/library_*.h` (CTLFW32 253, LUA50 59, MSS32 2, D3DX8 910
  markers). Tools that enumerate "work left" must skip both. Evidence: round 1293.
- **The client duplicates functions; one name can sit at two VAs.** `gv_Free3Fields` exists at
  `0x45b790` (frees `[slot+0x24]`/`[slot+0x28]`) and `0x4f2290` (frees `[slot+0x1c]`/`[slot+0x20]`):
  different bodies, and both are called. `0x45e520` (an 832-byte function the shared allocator source
  does not match) has **no callers at all**; `gm_LookupEntityRecordById` sits at `0x4cef30` while
  `cm_ChkEntityLookup` calls the untracked `0x4f48e0`.
- **LIBCMT objects are library metadata, not project TUs.** GOLDTL `__initterm`
  (`0x64e761`) and `_munlock` (`0x45ee00`) are `library_goldtl_libcmt.h` rows.
  Do not rebuild them under the game profile. An old SP6 pin on `__initterm`
  described the CRT object, not the GOLDTL toolchain.
- Image base `0x10000000`. Exports: `Init` (0x10009320), `Exit`
  (0x10009350). Imports: exactly 100, inside `.rdata`/`.data` (no `.idata`).
- `.text` VirtualSize `0x22846`. CRT: LIBCMT static. Compression: zlib
  1.1.3 vendored (`references/zlib-1.1.3`).


## Toolchain observations (verified with commands; round 938)

- **Nine MSVC6 images are available locally**, and they are *not* nine distinct
  generators: `msvc-6.0`, `-sp1` … `-sp5` and `-win9x` compile a shared row to
  **byte-identical objects** (measured round 502: 1149/2057, obj 2056 on
  `cm_ExSellObjekt`). So a service-pack sweep has only three real stops: the
  base group, `-sp5-pp`, and `-sp6`. Evidence: `docs/TODO.md` round 502.
- **`rebrew toolchain detect` is a hint, not a verdict.** On
  `original/Server/server.dll` it returns `"confidence": "high"` while its own
  `version_hint` says the compiler "may be MSVC 4.x/5.0", and one of its own
  evidence lines reports **5 pre-6.0 constant-hoist sites**. It cannot separate
  SP0-SP6 within the family. Do not cite it alone as proof of a service pack.
  Evidence: run it; the output contradicts the `confidence` field.
- Detector evidence it does report, all reproducible: 142 `rep movs/stos`,
  94 `push ebp; mov ebp,esp` prologues, 30 `int3` pad runs, 16 `mov edi,edi`
  2-byte nops, both wrapper styles (4 push-`[mem]`, 3 load-first),
  which is the machine-readable form of the project-wide "per-file flags
  vary" finding. Evidence: `rebrew toolchain detect original/Server/server.dll --json`.
- **`-sp5-pp` is a per-file pin, not a project setting, and it is worth 4
  bytes net.** Three files carry it (`spiel_dumpD.c`, `ahm_ExAllocAlchemist.c`,
  `ls_LoadBuildingEntityState.c`); 16 of 16 unpinned rows are *worse* under it,
  with `ServerMainThread` 2075 -> 1224 matched. Evidence: rounds 502/842,
  `docs/codegen-walls.md` §196.

## Deliverable mechanics

- **The shipped `build/server.dll` is not what the linker produces.**
  `rebrew build postlink` writes `.data`, `.rdata`, `.reloc` and the headers from the
  layout package. Shipped: all four `differing 0x0`; **raw link: `.data`
  21,481, `.rdata` 1,268, `.reloc` 7,107, headers 267** = 30,123 bytes the
  fixers overwrite. `.text` is the only section the build must get right.
  Evidence: `scripts/postlink_residual.py --write build/server.dll`.
- The deliverable is **286,720 bytes**, the reference's exact size, with
  **8,628 differing bytes, all inside `.text`**. Evidence: `scripts/gate.sh`.
- **Independently re-verified by direct byte comparison** (round 951), without the layout package,
  the fixer, or `rebrew`: file sizes equal, **8,628** differing, `.text` 8,628 and
  `.rdata` / `.data` / `.reloc` / headers **0 / 0 / 0 / 0**. Two methods, one answer.

## Game domain

- Two-phase command architecture: `cm_Chk*` validate, `cm_Ex*` execute.
- Seasons: `GM_WINTER/SPRING/SUMMER/AUTUMN`. Sim events: `HE_SIM_*`.
- (Add findings here with evidence: string VA, function VA, or doc pointer.)

## The `command_c` discovery boundaries are an INVENTORY artefact, not a coverage gap

`rebrew verify --full` reports "13 function(s) have annotation SIZE differing from the binary-derived
size". Twelve are `command_c/*.c` with `binary_size > annotation_size`. Rounds 1021-1024 read this as a
coverage gap and reported 51, then 10, "missing sibling functions" hidden inside over-wide discovery
symbols. **That conclusion was wrong**, and this entry replaces it.

**Every function inside those spans is already implemented, annotated, and byte-identical.** Measured: for
each of the 12 spans, every annotated VA inside it, with its length to the next annotated VA and its
residue in the shipped file:

| annotated functions inside the 12 spans | 25 |
|---|---|
| byte-identical (residue 0) | **24** |
| with residue | 1: `cm_ExSellObjekt` (`0x1000d930`, 966 bytes) |

Total residue inside all twelve spans: **966 bytes**, all of it `cm_ExSellObjekt`: a carrier already in the
residue table. Nothing is missing.

**The ten VAs rounds 1022-1024 named as "missing" are all present in the tree:**

| VA | file |
|---|---|
| `0x1000d340` | `cm_RejectCommand.c` |
| `0x1000d730` | `cm_ExFree.c` |
| `0x1000d930` | `cm_ExSellObjekt.c` |
| `0x1000e750` | `cm_ExAllocObjekt.c` |
| `0x1000f480` | `cm_ExSetWohnsitz.c` |
| `0x10010080` | `cm_ExSimCommand.c` |
| `0x1000e9c0`, `0x1000f590`, `0x1000fad0`, `0x10010140` | also annotated |

**The real artefact is that `function_structure.json` is stale, not that code is missing.** It holds 543
entries against 283 annotated functions: a *coarser* partition than the annotations. `0x1000d8a0` is one
2008-byte entry in the inventory, while the tree annotates **two** functions inside it:
`cm_ExTransferCurrencyNoKill` at `0x1000d8a0` (144 bytes, byte-identical) and `cm_ExSellObjekt` at
`0x1000d930`. The inventory entry's size is the gap to the *next inventory entry*, so it overlaps functions
the annotations already separate.

**Consequence for the earlier rounds.** `rebrew verify`'s denominator (283) counts annotations, which is the
right population. Nothing was ever unreachable via `rebrew skeleton`; the ten VAs simply had annotations
already. The "694 raw-link capability bytes" of round 1022 are real as a *measurement* (those bytes differ in
the raw link) but they are **not** un-implemented code, and closing them is not a coverage task: it is the
same codegen work as any other carrier, and `cm_ExSellObjekt`'s 966 bytes are already the subject of a
documented wall.

Evidence: enumeration of every annotated VA inside each span, with per-function residue measured against
`original/Server/server.dll` and `build/server.dll`; `grep` of `FUNCTION: SERVER` across `src/server.dll`;
`rebrew binary asm show` at each VA.

## The build is bit-reproducible from scratch, and the correct clean recipe is `--target final`

Verified round 1039: a **full clean rebuild reproduces the shipped `server.dll` byte-for-byte.**

```
cmake --build build --clean-first          # fails at POST_BUILD postlink BY DESIGN (see below)
cmake --build build --target final         # the deliverable; split_link.sh + postlink
cmp <pre-clean server.dll> build/server.dll   -> identical
md5sum                                        -> 3febd2c4ca080a3749c12d4bf7452fbe (both)
```

Residue after the clean rebuild: **8628** (`0x21b4`), unchanged.

**The `--clean-first` failure is expected and is not a broken tree** (measure-traps §17). It fails at the
POST_BUILD step with:

```
error: postlink failed: built .text is not position-aligned with the reference;
only 4847/7463 layout-map entries validate (64.9%, minimum 90%).
.text VirtualSize built 0x221f6 vs reference 0x22846.
```

That message describes the **plain CMake link** (`0x221f6`), which is not the deliverable. The deliverable is
`--target final`, which runs `scripts/split_link.sh` (per-reference-offset composition, LIBCMT placed as
stock objects) and then `postlink_residual.py`. `rebrew build postlink` in the POST_BUILD step refuses a
non-position-aligned `.text`, and the plain CMake link is exactly that: by design.

**Why this is worth recording.** Two properties follow, and both matter for trusting every number this
project reports:

- **The 8628 baseline is not an artefact of stale objects.** A clean rebuild from source produces the same
  bytes, so the residue is a property of the sources, not of the incremental build state.
- **The tree is reproducible by a fresh clone.** No gitignored intermediate is load-bearing for the
  deliverable (the five stock LIBCMT archives in `.scratch/libcmt/` are extracted from the toolchain images
  as `split_link.sh`'s header documents, and are the only external inputs).

Evidence: `cmake --build build --clean-first` then `--target final`; `cmp` and `md5sum` against the
pre-clean artefact; `postlink_residual.py --write build/server.dll`.

## Done-criteria status, verified independently (round 1043)

The objective lists five done criteria. Verified each from outside the project's own tooling this round, so
the status is a measurement rather than a summary of the gate.

| criterion | status | evidence |
|---|---|---|
| `.text` VirtualSize exactly `0x22846` | **MET** | independent PE parse (`scripts/verify_objective.py`, shares no code with project tooling) |
| residue at or below `RESIDUE_BASELINE` | **MET** | 8628 = baseline; all 8628 differing bytes inside `.text`, 0 elsewhere |
| `rebrew verify --full` at or above `BASELINE` | **MET** | 281/283 passed, 264 byte-matched, `BASELINE=281` held |
| import table exactly 100 | **MET** | 100 imported symbols across 4 DLLs, identical to the reference |
| Wine load + exports (Init, Exit) resolve | **MET** | `wine_load_check.sh`: `LoadLibraryA` succeeds, both `GetProcAddress` calls resolve |
| **all functions EXACT, zero drift** | **NOT MET** | 31 EXACT + 233 RELOC = 264 byte-matched of 283; 2 failed, 17 PROVEN (not byte matches) |
| **residue at zero** | **NOT MET** | 8628 |

**Independent structural confirmation** (`scripts/verify_objective.py`, an independent PE parser):

```
file size equals reference                286720 bytes
.text / .rdata / .data / .reloc VirtualSize equal reference
import DLL list identical                 4 DLLs
imported SYMBOL count == 100              (reference 100)
export names + VAs identical              Exit, Init
all differing bytes inside .text          8628 of 8628
non-.text bytes identical
no exported entry point lies in the residue
export Exit body identical (0x40 bytes)
export Init body identical (0x40 bytes)
```

**Function-level:** `rebrew test --all` reports 283 total, **0 compile errors, 0 missing files**, 31 exact,
233 reloc, 17 proven, 264 byte-matched.

**Where the objective stands.** Every structural criterion and the load criterion are met. The two
unmet criteria are the same quantity: the 8,628-byte residue on 18 carriers, which is the C-only floor
this session has characterised from six independent angles (per-carrier class map, fault reproduction,
displacement profiles, operand completeness, work-queue emptiness, per-function independence) and which no
lever found in rounds 1025-1042 moves.

## Faking the original `D:\` build path through wine is possible, and unnecessary (round 1054)

**The question.** The game was built from `D:\Develop\...`, the reconstruction lives in a Linux checkout, and
`__FILE__` under wine expands to a POSIX path mapped as `Z:\home\...`. Can the original path be faked?

**Yes, and it is a two-line change.** Verified by experiment:

```
$ mkdir -p .scratch/Ddrive/Develop/DieGildeAddOnServer
$ ln -s $PWD/.scratch/Ddrive ~/.cache/rebrew-msvc-6.0-sp6-wineprefix/dosdevices/d:
$ rebrew-cmake-cl /nologo /c /O2 /Gd /MT /Foout.obj "D:\Develop\DieGildeAddOnServer\server.c"
$ strings out.obj | grep server.c
D:\Develop\DieGildeAddOnServer\server.c
```

`__FILE__` then expands **byte-identically** to the reference's string. The mechanism, from
`rebrew/cmake_tc.py`: the wineprefix is a host directory mounted into the container
(`-v {prefix}:{prefix}`), and wine reads its drives from `{prefix}/dosdevices/`. A fresh prefix has only
`c:` and `z:`; adding a `d:` symlink there creates the drive. The target must live **inside a directory the
container already mounts** (the project root or the wineprefix) because `_docker_run` mounts only those
two; a `d:` pointing at `/tmp` fails with `C1083` even though the symlink is correct.

**But it is unnecessary, and here is the measurement.** `__FILE__` is used **nowhere** in this tree:
`grep -rn "__FILE__" src/server.dll` finds exactly one hit, and it is in a comment. Every `D:\Develop\...`
string is a **hand-written literal** passed to `LogMessageInternal`, escaped in the source:

```c
LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x5df, "LOBBY mode", 1);
```

All **14** `D:\Develop\...`-shaped strings in the reference are **already present in the shipped file**:
verified by scanning both images, and all 11 distinct literals are written out in the sources.

**So the path axis is already closed by construction, not by luck.** The reconstruction reproduces these
strings by typing them, which is what the original source did too (the original called
`LogMessageInternal("D:\\Develop\\...", ...)` with a literal, not `__FILE__`; if it had used `__FILE__`, the
strings would carry the SDK's own layout, and `/FC` would have been required).

**When this WOULD matter.** If a round ever converts one of these literals to `__FILE__` (for instance while
tidying, or because a decompiler emitted `__FILE__` for a path argument) the build would silently start
emitting `Z:\home\maci\...` instead of `D:\Develop\...`, breaking strings that currently match, and the
failure would appear only in `.rdata`. The `d:` mapping above is the fix if that ever happens. Recorded so
the technique is available and the reason it is currently unused is explicit.

**Corollary for `__FILE__`-bearing code generally:** under wine, `__FILE__` reflects the path spelled on the
`cl` command line. CMake passes an **absolute** POSIX path, so without `/FC` a `__FILE__` would still be the
absolute path (wine maps it to `Z:`), not a relative one. Any TU that needs a specific `__FILE__` string must
either take the `D:`-drive route above or pass a relative path, and neither is currently needed.

## The data sections are complete, and `rebrew todo` was reporting 123 phantoms (round 1078)

The exact section layout, which every data question resolves against. All four section headers are
**byte-identical** between `original/Server/server.dll` and the built `build/server.dll`:

| section | VirtualAddress | VirtualSize | SizeOfRawData | file bytes cover |
|---|---|---|---|---|
| `.text` | `0x00001000` | `0x00022846` | `0x00023000` | RVA `0x1000`..`0x24000` |
| `.rdata` | `0x00024000` | `0x00002e81` | `0x00003000` | RVA `0x24000`..`0x27000` (the IAT is its head) |
| `.data` | `0x00027000` | `0x0174059c` | `0x0000e000` | RVA `0x27000`..`0x35000` |
| `.reloc` | `0x01768000` | `0x00010374` | `0x00011000` | its `rawptr` is `0x35000` |

Two consequences that are easy to get wrong:

- **There is no `.idata` section**, despite 84 metadata entries claiming `section = ".idata"`. The import
  address table lives at the head of `.rdata` (`DataDirectory[12]` = RVA `0x24000`, size `416`).
- **`.data`'s virtual tail begins at VA `0x10035000`** (`vaddr + rawsize`). Everything from there to
  `0x1176759c` (`.bss` in ordinary terms) has no file bytes in either image and is zero-filled by the
  loader. `section_symbol_bytes` skips it deliberately (`# zero-fill tail (BSS): no file bytes to read`), so
  `rebrew verify --data` cannot compare those symbols and never marks them VERIFIED.

**Data state: 329 metadata symbols, 0 differences from the reference.** 122 are `VERIFIED` by
`verify --data`; the other 207 are `UNCHECKED` and un-clearable, but were checked independently by direct
byte comparison: 84 import slots (all dwords identical), 111 in the zero-fill tail, 5 with file bytes
(identical), 7 sizeless. The 18 `__imp__` items and the 123 `start-data` items that `rebrew todo` used to
list were artefacts of that gap; both lanes are now empty and only the 2 known `.text` carriers remain.

**`rebrew verify --data` now prints its denominator** (fixed round 1079, rebrew commit `3f7cefea`). The
summary reads `data: 122 matched, 0 mismatched, 0 missing (122 of 329 symbols compared, 37%)` and names why
the other 207 are not comparable, and `--json` carries `total`/`compared`/`not_comparable`/`coverage`. Before
that fix the coverage figure was absent entirely and had to be reconstructed by calling
`section_symbol_bytes` on both images and counting `ref_sizes`; see `docs/measure-traps.md` §51 for why a
zero in a diff-shaped result is never a statement about the whole tree.

## Section-by-section parity: the shipped file is byte-identical outside `.text`, BY COPYING, NOT BY COMPILING (round 1089, corrected round 1092)

**Read the raw-link column before drawing any conclusion from this.** The zeros below are produced by
`rebrew build postlink` writing those sections from the layout package (`layout/server.dll/*.hex`), which holds the
reference's own bytes. They are **not** evidence that the compiler and linker reproduce them. Round 936
recorded this correctly; the round-1089 version of this entry did not, and is corrected here.

| section | shipped deliverable | **raw link (real compile + link), pre-fixer** |
|---|---|---|
| `.text` | differing 8,628 | differing **14,347** |
| `.rdata` | differing 0 | differing **1,268** |
| `.data` | differing 0 | differing **21,481** |
| `.reloc` | differing 0 | differing **7,103** |

"A zero here is a tautology, not a match", and `rebrew verify --data` says so itself, in its own output:
*"server.dll's .data is byte-identical to the reference. If the build postlinks by copying that section, these
results are tautological: point --built at the raw link instead."*

The measurements below are still true **of the shipped artifact**, and that is the artifact the objective
names. They simply cannot be evidence about codegen. For the shipped deliverable:

| section | SizeOfRawData | differing bytes | SHA-256 (ref = built) |
|---|---|---|---|
| `.text` | `0x23000` | **8,628** | differs |
| `.rdata` | `0x3000` | **0** | `8046aaa446c8…` |
| `.data` | `0xe000` | **0** | `e1f56d0d50af…` |
| `.reloc` | `0x11000` | **0** | `d8cf33e18c1a…` |

File size is 286,720 bytes in both, and all four section headers are byte-identical. The whole-file SHA-256
still differs, and the difference is **exactly** the `.text` residue: nothing else in the image contributes.

**`rebrew verify --data`'s 37% coverage is the maximum, not a shortfall.** Its report reads
"122 of 329 symbols compared". The 207 it does not compare decompose as: **73** symbols declared `.data` that
sit past `rawsize` `0xe000` in the virtual tail (`0x10035000`+), **84** import slots, **50** `.bss`. Measured
directly: **none of the 73 is inside the file-backed region** `0x10027000`..`0x10035000`. The 122 compared are
85 `.data` + 37 `.rdata`, which is every symbol that has file bytes in either image to compare against. There
is no additional coverage to be had: the remainder is symbols the file format does not carry.

**What this means for the done-criteria.** "Every data byte matching" is satisfied and independently verified.
"`.text` VirtualSize exactly `0x22846`" is satisfied (`0x22846` in both). "Import table exactly 100" is
satisfied. "residue at zero" and "all functions EXACT" are the two clauses that are not, and they are the same
clause: the 8,628 bytes above.

## Finding code we already reversed in another target: `rebrew source import-related`

The three targets share one source tree and one codebase, so most of the work
is already done somewhere else.  The question "is this GOLDTL function already
reversed in GOLD or in SERVER, and in which file?" is answered by
`cross-import` in **report mode** (round 1378):

```
rebrew source import-related --from server.dll --target Europa1400Gold_TL.exe \
    --dry-run --candidates-only --json
```

`--from` is the SOURCE (searched for already-matched code: EXACT/RELOC/PROVEN),
the target option is the DESTINATION (searched for not-yet-matched work).
Matching is structural (mnemonic histogram + call/branch counts + size) over
the **target bytes**, so no compilation is needed for the search.  Every result
row names `dst_va`, `src_va`, `score`, `src_status`, `src_file` (the file that
already holds the code) and `dst_file`; `--candidates-only` hides the thousands
of "no match" rows and reports the count as `skipped_count`.

Measured on the 2024 trees (round 1378): SERVER -> GOLDTL 68 candidates,
GOLD -> GOLDTL 6, GOLDTL -> GOLD 118.  Default thresholds are `--min-score 95`
and `--min-gap 5`.

Importing is `--shared`: it stacks the destination marker onto the body that is
already in the file (ADR-010, one body, one marker per target) and then
compiles + verifies against the destination binary, promoting STATUS only on a
real match, reverting otherwise.

Read the score as "same structure", **not** "same bytes":

- The two clients (GOLD, GOLDTL) share the `msvc-6.0-sp5-pp` profile, so a
  shared body can verify byte-exact (`--from GOLDTL --target GOLD` round 1378
  imported GOLD 0x421ed0 from GOLDTL 0x41d4d0, EXACT).
- SERVER was built with the sp6 profile, so SERVER twins routinely compile to
  9-135 differing bytes under the client profile even at score 100.  The import
  is then reverted, not forced.
- `--min-score 95` is a *recall* threshold: several 95-99 candidates are not
  twins at all.  Always let the verify decide; never trust the score.

Never use the copy path (no `--shared`) in this project: the destination path
is the source file itself, and a whole-file copy would delete the co-resident
functions.  `cross-import` refuses that case with `TARGET_CONFLICT` and tells
you to use `--shared` (round 1378 fix).

## The three binaries: one compiler version, two code generators (round 1379, definitive)

Earlier notes said "clients sp5-pp, server sp6".  Measured properly, the
distinction is **not a compiler version** and not a service pack: all three
binaries were built with the same compiler product and version
(**MSVC 6.0, cl.exe 12.00.8804**) and differ only in the **code generator**
(c2.dll):

| binary | compiler version | code generator | `Rich` record | pp-only `test ah,X` sites |
|--------|------------------|----------------|---------------|---------------------------|
| SERVER | cl 12.00.8804 | stock VC6 c2 | stock copy: comp_id `0x000a2306`, count 37; configured copy: stripped | **0** |
| GOLDTL | cl 12.00.8804 | **Processor Pack** c2 13.00.9044 | comp_id `0x00302354`, count 154 | 1011 |
| GOLD | cl 12.00.8804 | **Processor Pack** c2 13.00.9044 | comp_id `0x00302354`, count 157 | 841 |

Three independent measurements, all agreeing:

1. **Compiler fingerprint (`@comp.id`).** The Processor Pack image
   (`rebrew/msvc:6.0-sp5-pp-win32`) stamps every object with
   `@comp.id = 3154772 = 0x00302354`: product `0x0030`, build `2354` = 9044,
   i.e. c2.dll 13.00.9044.0.  Nine VC6 code generators are registered
   (`6.0`, `sp1`-`sp6`, `win9x`, `sp5-pp`) and each stamps a different
   `@comp.id`; only `sp5-pp` uses product `0x0030`.  Both clients' Rich headers
   carry exactly that record (counts 154/157 objects). Matching local stock
   SERVER copies carry product 10/build 8966, count 37. The configured project
   copy has altered headers, including a removed Rich record and minimal
   0x80 DOS stub; its four section contents are identical to the stock copies.
   See `msvc6-link-layout.md` section 18 for hashes, paths and all records.
   Do not trust `diec`'s "compiler 13.00.9178" line for these clients: that
   value comes from a non-compiler Rich entry (a statically linked SDK/MSS32
   object); the compiler record is the `0x0030`/9044 one.

2. **Code-generator fingerprint.** Compiling one fixed source (float and
   double `==`, `!=`, `<`, `<=`, `>`, `>=`, branch and int-returning forms)
   with `/Od`, `/O1`, `/O2`, `/Ox`, `/Os`, `/O2 /Op`, `/O2 /Oa`, `/O2 /Ot`,
   `/O2 /Oy-`:
   - `sp5-pp` emits `test ah,0x44` (+ `jp`) and `test ah,0x05`, and **never**
     `test ah,0x40`, under all nine flag sets.
   - All eight plain VC6 code generators emit `test ah,0x40` + `test ah,0x01`
     + `test ah,0x41`, and **never** `0x44`/`0x05`, under all nine flag sets.
   The idiom is therefore a code-generator signature, not a flag artefact.
   **The `test ah,X` only counts as a compare idiom when `fnstsw ax` precedes
   it** (`df e0 f6 c4 XX`): a bare `f6 c4 40` is usually the integer
   strength-reduction `test eax,0x4000` -> `test ah,0x40`, which both
   generators emit.  Counting properly, in the shipped `.text`:

   | binary | fnstsw+0x44 | fnstsw+0x05 | fnstsw+0x40 | fnstsw+0x01 |
   |--------|-------------|-------------|-------------|-------------|
   | SERVER | 0 | 0 | 0 | 10 (game fns) |
   | GOLDTL | 200 | 801 | 0 | 22 (**all** 22 inside the D3DX8 static-lib band `0x5e0000-0x64ffff`) |
   | GOLD | 115 | 719 | 0 | 0 |

   So the clients' game code carries 1001 / 834 pp-idiom compares and not one
   plain one; the server is the mirror image; the server's own plain compares
   (`fnstsw+0x01`) sit in the very functions the reproduction matrix below
   shows compile correctly only under the plain generator.  GOLDTL's 22 plain
   sites are Microsoft-built D3DX8 objects, not game source.

3. **Byte-reproduction matrix** (same file, same CFLAGS, only `--toolchain`
   varies; all four rows are matched functions that contain an FP compare):

   | function | sp5-pp | sp6 | sp5 |
   |----------|--------|-----|-----|
   | GOLDTL `0x0042e470` `gm_RandomQuadratic` | **RELOC** | NEAR_MATCHING | NEAR_MATCHING |
   | GOLDTL `0x004b4f00` | **RELOC** | NEAR_MATCHING | NEAR_MATCHING |
   | SERVER `0x1000c3c0` `alchemistry_logic2` | SIZE_MISMATCH | **RELOC** | **RELOC** |
   | SERVER `0x100100a0` `cm_ExModifyStat` | NEAR_MATCHING | **RELOC** | **RELOC** |

   Client bytes are reproduced **only** by the Processor Pack generator; server
   bytes **only** by the plain generators.

   This does NOT mean every client function needs the pp generator: a 14-file
   sweep of matched GOLDTL functions (round 1379b) gives 11/14 byte-identical
   under all three generators (no FP compare to rewrite), 3/14 pp-only
   (`0x459940`, `0x4fffb0`, `0x492990`), and **0/14 plain-only**.  Five client
   functions now tested where the generator matters, all pp-only; no
   counterexample exists in either direction.

### Game code only (round 1379c)

D3DX8, LIBCMT and the other Microsoft-built objects were compiled with
Microsoft's own settings, so they say nothing about the game's build and are
excluded.  Restricted to game code (inventory functions, no library mark, no
`external_ranges` band), the compare-idiom census is:

| binary | game-code pp compares (`fnstsw+0x44/0x05`) | game-code plain compares (`fnstsw+0x40/0x01`) |
|--------|--------------------------------------------|-----------------------------------------------|
| SERVER | **0** | 9 x `0x01` (+6 x `0x41`, a value both generators emit) |
| GOLDTL | 723 (113 + 610) | **0** |
| GOLD | 693 (97 + 596) | **0** |

The two zeroes do not depend on my library classifier: `fnstsw ax; test
ah,0x40` occurs **nowhere** in either client, and all 22 of GOLDTL's
`fnstsw+0x01` sites lie inside the D3DX8 band.  The server's pp count is zero
across its whole `.text`, game code included.

The sweep of 14 matched GOLDTL functions (all game code, none carries a
`LIBRARY:` row) is the same story: 11 reproduce under all three generators,
3 reproduce only under the Processor Pack (`0x459940`, `0x4fffb0`, `0x492990`),
0 only under the plain ones.

The Rich-header `comp.id 0x00302354` count is a *build-level* record: it
aggregates every object in the link, game and library alike, so it alone would
not prove the game TUs are pp.  The proof for game code is the reproduction
matrix plus the game-code census above.

Consequences:

- The SERVER↔client body overlap cannot be byte-identical wherever the changed
  generator touches the code (x87 compare idiom and the scheduling it drags
  along). `rebrew source import-related --from server.dll` therefore reverts even at
  score 100: that is the tool being honest, not a match-quality bug.
- GOLD and GOLDTL share the generator, so GOLDTL→GOLD marker moves do verify
  (round 1378: GOLD `0x421ed0` from GOLDTL `0x41d4d0`, EXACT).
- Plain VC6 SP5 and SP6 output is byte-identical for the functions measured
  here, so the server cannot be pinned to a specific service pack: only to
  "a plain, non-Processor-Pack VC6 code generator".  The three per-file
  `sp5-pp` pins in `CMakeLists.txt` are marginal partial-match wins (834 vs
  828 bytes, 824 vs 820), not evidence of a pp-built server.

### Does the Processor Pack work for the SERVER target? (round 1379e)

Partly: per file, never as the target profile.

Same file, same flags, only `--toolchain` varies, 12 matched server functions
(the 5 that carry a plain x87 compare plus 7 ordinary ones):

| result | count | functions |
|--------|-------|-----------|
| byte-identical under sp5-pp AND sp6 | 9 | `cm_ExSetAttribute`, `cm_ExModifyHealth`, `cm_DispatchProduction`, `cm_ChkEntityLookup`, `InitializeLogAndErrorHandler`, `cm_ExSetWohnsitz`, `cm_ExCreateGeb`, `cm_ChainAssignId`, `cm_ChkSellObjekt` |
| pp **breaks** it | 3 | `ahm_ClampFloatValue` 0x1000c3c0, `cm_ExModifyStat` 0x100100a0, `sim_FindAndMatchParents` 0x100151e0 |
| pp-only (pp matches, plain does not) | 0 | - |

The rule is exact: the three that break each contain the plain idiom
(`fnstsw ax; test ah,0x01`: 2, 3 and 2 sites) **inside the compared
function's own span**, and every function whose span contains none is
generator-insensitive.  `cm_ExSetAttribute` 0x1000e8d0 has three such sites
*after* its end and stays byte-identical under pp: the earlier inventory
attribution had folded them into it.

Conclusion (round 1379f): the server build is **single-toolchain**: one plain
VC6 profile for every TU.  The three `msvc-6.0-sp5-pp` pins that used to sit in
`CMakeLists.txt` are gone.  They were bought with partial-match scores on
functions nobody has matched yet (171/346 vs 162/346, 834 vs 828, 824 vs 820),
i.e. a wrong-compiler coincidence, and they contradict the binary's own
fingerprint.  Removing them costs nothing measurable: with all three objects
force-rebuilt under sp6, `rebrew verify --full` is 281 passed / 264
byte-matched, gate residue 11735, raw-link `.data` 22749 and imports 100:
identical to the pinned build.  `scripts/gate.sh` now fails if a pin of the
other generator family appears, and `rebrew toolchain detect` refuses the pack
profile for the server target.

## Using the two clients as a reference for the remaining server work (round 1380)

Where server.dll stands: 283 annotated functions, 264 byte-matched (31 EXACT,
233 RELOC), 17 PROVEN, 1 NEAR (`ServerMainThread@4`), 1 STUB
(`gm_AllocSpieler`), and the link is 0x620 bytes short of the reference
`.text` (residue 11735).  `rebrew todo` now lists exactly two function items
once library and other-target rows are filtered out of it.

What the clients can and cannot give:

1. **They do not carry the server's missing C.** `cross-import --from
   GOLDTL --target server.dll` finds 0 candidates above score 95 (1 at score
   83): for every server carrier the client twin is itself unmatched, so there
   is no verified client body to stack.  Six carriers do have a same-named
   client marker (below); none of those client bodies is byte-matched either.
2. **Same-named client twins are not always the same function.** Compiling
   the shared body under BOTH profiles gives the same object size for
   `ahm_ExAllocAlchemist` (1002/1002), yet the two references differ by 86
   bytes (server 1002, GOLDTL 1088) and there is no x87-compare delta to
   explain it.  The TL client's copy of that function is built from different
   source.  Compare reference sizes before trusting any twin:

   | function | server VA | server ref | GOLDTL VA | GOLDTL ref | our obj sp6 / pp |
   |----------|-----------|-----------|-----------|------------|------------------|
   | `cm_ExProdObjekt` | 0x1000e140 | 993 | 0x4c35f0 | 960 | 993 / 991 |
   | `vfs_ReadCompressed` | 0x10008a90 | 492 | 0x465350 | 496 | 492 / 492 |
   | `vfs_OpenStream` | 0x10009020 | 667 | 0x430cb0 | 704 | 701 / 685 |
   | `ahm_ExAllocAlchemist` | 0x1000bdf0 | 1002 | 0x4ee290 | 1088 | 1002 / 1002 |
   | `gm_AllocGebaeude` | 0x100174d0 | 1088 | 0x5974e0 | 1113 | 1078 / 1074 |
   | `gv_ExAllocGraveyardWorker` | 0x10011bf0 | 1040 | 0x4f3310 | 992 | 1040 / 1000 |

   Three of the six pairs differ by more than the profile change can move the
   same body, so they are divergent source, not divergent codegen.
3. **The profiler that still pays is the server's own bytes plus the
   documented levers.** Every one of the 19 carriers has a `docs/msvc6-*.md`
   entry with the shapes already spent; the first divergence census is the
   fastest triage:

   ```
   python3 scripts/first_divergence.py        # per carrier: first differing byte
   python3 scripts/whathas.py 0x<VA>          # what is already recorded there
   rebrew diff 0x<VA> --target server.dll     # structural vs reloc-only (`~~`)
   ```

   The closest carrier, `gm_CalculateProductionValue` (0x10019720), is down to
   **2 structural diffs** in 396 bytes: the reference orders `fxch st(1)`
   before an independent `cmp byte ptr [esi], 0x17`, our build after it: a
   scheduler tie-break on already-correct C, and the file records six
   reassociations that were tried and are worse.

4. **Two tool bugs were hiding the real worklist** (fixed this round):
   `rebrew todo` offered the `// LIBRARY:` rows in `library_msvc.h` as
   "improve-match" items (11 of the top 20) and listed 20 GOLDTL data symbols
   in the server's todo because one metadata file serves the unified tree.

- Gold and TL rand have different CRT threading variants: native GOLD0x5de784 whole-body matches stock msvc-6.0-sp5-pp LIBC.LIB `_rand`, build\intel\st_obj\rand.obj; native global seed slot0x62e108. LIBCMT whole-body probe misses. TL0x64d3f8 is already identified as LIBCMT `_rand`. Code origin is established; this does not by itself prove an entire runtime selection or linked provider without native link-map evidence. Receipts .scratch/goal-crt-retirement/{gold-rand-libc-library,gold-rand-library,gold-rand-native-asm}.json. Never recreate or patch either runtime body.

- DirectInput device correspondence is evidenced by identical complete GUIDs and native CreateDevice outputs: TL GUID66cc50/GUID_SysMouse (6f1d2b60-d5a0-11cf-bfc7-444553540000) equals unique Gold5eee60; TL pointer14ce8a0 maps to Gold1467360, acquired by Gold410710. TL GUID66cc40/GUID_SysKeyboard (6f1d2b61-d5a0-11cf-bfc7-444553540000) equals unique Gold5eee50; TL pointer14ce90c maps to Gold14673cc, acquired by Gold410740. Gold410770 uses DirectInputCreateA/version700, whereas TL411820 uses DirectInput8Create/version800; root interfaces must remain distinct. Evidence .scratch/goal-forward-ret/input-guid-cross-build.json and gold-input-init-asm.json. The compiler-image DINPUT.H confirms both GUID names and Acquire/Unacquire methods; receipt native-sdk-input-evidence.txt. No storage/type/header changes made from this read-only finding.

- Keyboard buffered-event ABI differs between clients: TL4124b0 calls vtable GetDeviceData(+0x28) with cbObjectData0x14 and a0x18 local frame; unique Gold4112e0 counterpart calls the same device method with cbObjectData0x10 and a0x14 frame. Gold device pointer14673cc matches the GUID-proven keyboard slot. This is a real DirectInput8/7 event-record difference, so an unchanged20-byte event import would alter Gold API behavior. Native receipts .scratch/goal-input-drain/gold-loop-candidates.json, gold-native.json, and .scratch/goal-input-types/drain-native.json.

- TL420b70 clears 0x6a0 bytes at14cbcc0; existing shared updater TL420ba0/Gold424810 bounds the byte index below0x6a and updates four-int rows, choosing columns0/1 or2/3. These independent accesses corroborate106 rows of16 bytes (1696 accessed bytes), not a storage owner. Native clear has one Gold37-byte counterpart4247e0 with table1460b00 and counters633178/633174/633180/63317c. Library probes negative; source reorganization pending. Evidence .scratch/goal-getter-extents/next-{native,counterpart,library,gold-library}.json and src/GOLDTL.fcn_00420ba0.c.

- Client packet statistics columns0/1 track received packets/bytes and2/3 sent packets/bytes: TL4210a0 loads native recv IAT662384 intoESI (calls4210ed/42114a), then calls updater420ba0 with flag1 at421262; send routine421290 passesflag0 at421328. The updater selects0/1 fortrue,2/3 forfalse. Field names remain reconstructed; native semantics are corroborated. Evidence .scratch/goal-net-stats/{packet-directions,update-call-context}.json.

- Native TL4737e0/Gold476c80 count six12-byte rows over72 accessedbytes, checking each firstword against-1. Corresponding table views TL1011980..10119c8 andGoldf8ab80..f8abc8 are positive whole-body matches after masking only start/end operands. Remaining row-word semantics, full backing allocation, subsystem and storage owner are unresolved. Evidence .scratch/goal-vfs-casefold/next-4737e0-native.json andnext-counterparts.json.

- Full native extents identify TL66080a as stock MT _strupr (308bytes, LIBCMT strupr.obj) andGold5eaad6 as stock ST _strupr (158bytes, LIBC strupr.obj). The competing strlwr bodies have7 and4 fixed-byte mismatches. Earlier library-match32-byte prefix candidates and legacy catalog __strlwr labels did not establish the exact member. Evidence .scratch/goal-vfs-casefold/full-runtime-attribution.json, pinned public index_library/match_bytes over stock archives previously validated byCLI.

- Dummy-object loader TL5a3580 invokes native _strupr at66080a (call5a35c2) before formatting dummy_%s; its existing C incorrectly calls _strlwr. Complete stock308-byte attribution distinguishes uppercase from lowercase. Source correction is staged in .scratch/goal-upper-call/candidate.c, not yet applied while VFS repairgate runs. Evidence .scratch/goal-vfs-casefold/other-case-caller-native.json andfull-runtime-attribution.json.

- TL40eca0 and Gold40dd90 have the same complete21-byte wrapper after masking only the call operand, but their native callees differ: TL450a00 is a38-byte counter/callback body and does not read the stack argument; Gold453890 begins with counters and reads byte[esp+4] before branching into a longer body. Same wrapper bytes do not establish unchanged callee semantics or justify importing the38-byte TL callee into Gold. TL source already has a char-width wrapper prototype; Gold scratch byte-width correction matches its21-byte native caller independently. Evidence .scratch/goal-small-extents/next-{gold-40dd90-tl-candidates,gold-453890-native,tl-450a00-native}.json.

- TL67bbdc/Gold5fcc78 form an accessed12-byte, three-float view. Shared updater native operands independently establish member offsets0/4/8; former scalar globals67bbe0/67bbe4 (Gold5fcc7c/5fcc80) are interior aliases. Existing header now supplies inferred VECTOR3 with x/y/z and canonical extern declarations; this names the shared layout, not an original SDK/game type or complete allocation. Another user g_6b86c4 has unresolved semantics, so the shared type is not renamed RGB. TL450b20 passes the first triple as ambient RGB to the material setter. The primary [Wine D3D8 interface header](https://raw.githubusercontent.com/wine-mirror/wine/master/include/d3d8.h) places SetMaterial at vtable index42/offset0xa8, matching native ff91a8000000 at450c5c. Microsoft [D3DMATERIAL8](https://learn.microsoft.com/en-us/previous-versions/ms886288(v=msdn.10)) describes the material colors. Configured SDK8 probe failed C1083 missingd3d8.h; no SDK layout assertion passed. Complete backing extent and storage owners remain unresolved. Receipts .scratch/goal-material-colors/{method-binding,field-alias-bindings,alias-metadata-preview}.json.

- Native literal audits found placeholder strings in TL C bodies despite zero common-prefix differences: TL401470 emits `array count mismatch`, while its native operand points to675058 `bio_rd_array_debug: Tried to load invalid array-sizes...`; TL40cba0 emits `invalid object`, while native675da8 contains `WalkToDummyRotate(): invalid character or dummy`. Masked relocation agreement does not establish literal equality. These bodies require real literal recovery before strict promotion; original-name/source-path evidence must be checked against the native string push. Evidence `.scratch/goal-small-client-helpers/placeholder-string-evidence.json`.

- TL entity-query table pointer: canonical `g_entity_ptr` binds to native `0x0090e094` (four-byte word in `.data` zero-filled virtual tail). Complete native users `gm_SearchStruct` (`0x00504100`, 39 bytes) and `gm_SearchTable67` (`0x00504e70`, 62 bytes), plus existing matched reset/cleanup users, agree. Allocation witness at `0x005010b2-0x005010dc` passes `f3_gm:lpGebaeudeINST`, allocates `0xa900` bytes (256 records of stride `0xa9`), stores the result in that word and zeroes the buffer. This identifies the logical pointer; its native standalone owner or containing allocation remains unresolved. The managed row is declaration-only, with no backing or native link-symbol claim and no new C definition. Evidence: `.scratch/goal-tl-query-bindings/allocation-witness.json`, `extent-audit.json`, `users.json`. Gold independently compiled shared search/reset/cleanup bodies agree on `0x00889f74`; native allocation at `0x004fe5e2-0x004fe60c` passes the same complete label at `0x0061aa00`, allocates/zeroes `0xa900` bytes, and stores/loads that four-byte `.data` virtual-tail word. Gold storage owner/backing remain unresolved. Gold evidence: `.scratch/goal-gold-query-bindings/{extent-audit,allocation-witness,users}.json`.

- TL building-prototype table pointer: canonical `g_entity_type_table` binds native `0x00868050`, a four-byte `.data` virtual-tail word. Native initialization at `0x0050108a-0x005010a3` allocates `0xca78` bytes (88 records, stride `0x24d`) with complete label `f3_gm:lpGebaeudePROT` at `0x00699748`. All aligned canonical users agree; 20-user catalog comparisons preserve compiled bytes and scores. Logical identity is verified; native storage owner/backing remains unresolved. Declaration-only metadata allocates no storage. Evidence: `.scratch/goal-tl-prototype-bindings/{allocation-witness,users,binding-effects,extent-audit}.json`.

- Animation callback TL406410 / GOLD405870 follows the same pointer chain (`obj+0x34`, then `+0x1cc`) but reads its blocking word at TL+0x390 versus GOLD+0x84. The complete 248-byte bodies otherwise agree after nine validated relocations. `REBREW_GOLD` is an inferred build selector, not an attested original macro; it selects only this shared source's `ANIMATION_BLOCK_OFFSET`. The logical member name and full containing layout remain unresolved. Omitting the selector reproduces exactly the two displacement-byte differences at offsets47/48 with no invalid relocations. Evidence `.scratch/goal20/padded-callback-{differences,without-selector}.json` and fresh dual-target callback tests.


- TL CharacterClearSitting406560 uses the existing seat at character+0x74
  after a conditional call to402aa0, whose complete native body is a single RET.
  It obtains the animation name from seat+0x68 and passes model+0xf4 first,
  name second, to435500; the model pointer is at entity+0x1ec. It clears the
  seat pointer and sitting bit0x10, preserving the other flag bits. Four other
  source users already treat402aa0 as void. The corrected C stops treating its
  stale EAX as a replacement seat and restores the native argument order.
  Original helper name/TU context and complete entity/seat types remain unknown.
  Evidence: `.scratch/goal20/clear-sitting-{original-current,noop-original,
  behavior,call-audit}.json`.

- TL initializer4a1130 registers the native action name `Buergerrecht`
  (literal67edf8) with type0x19, starter499a50 and run499ad0. The starter is
  a125-byte four-argument handler with3 trailing layout NOPs, not the130-byte
  `ahm_ProcessEntityChain` dispatcher at4c4d30. Its threshold uses the native
  float pools66417c (0.44f) and664340 (16000.0f). This proves the action
  association, not an original C function name or source unit. Evidence:
  `.scratch/goal20/citizenship-registration.json` and `ahm-chain-original.json`.

- GOLD independently registers `Buergerrecht` at initializer4a16f0 with
  name600190 and starter49a010. Its125-byte starter shares the recovered TL C
  body; the global byte is6f1bc5, query helper509ee0, and float pools5ecef0/
  5ed0a8. Managed existing globals/callee aliases map these targets; no new
  storage is defined. Resolving all four COFF operands reproduces each native
  body, and both complete float payloads match. This is stronger body evidence
  than masked relocation agreement but does not establish a raw client link.
  Evidence `.scratch/goal20/citizenship-{starter-audit,gold-audit}.json`.
