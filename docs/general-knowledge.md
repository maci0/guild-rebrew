# General knowledge — facts about the original game, build, project

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
  `external_ranges`; the other static libs (CTLFW32, LUA50, MSS32, LIBCMT) have no contiguous band —
  their VAs are the `// LIBRARY:` rows in `src/library_*.h` (CTLFW32 253, LUA50 59, MSS32 2, D3DX8 910
  markers). Tools that enumerate "work left" must skip both. Evidence: round 1293.
- **The client duplicates functions; one name can sit at two VAs.** `gv_Free3Fields` exists at
  `0x45b790` (frees `[slot+0x24]`/`[slot+0x28]`) and `0x4f2290` (frees `[slot+0x1c]`/`[slot+0x20]`) —
  different bodies, and both are called. `0x45e520` (an 832-byte function the shared allocator source
  does not match) has **no callers at all**; `gm_LookupEntityRecordById` sits at `0x4cef30` while
  `cm_ChkEntityLookup` calls the untracked `0x4f48e0`.
- **CRT copies of LIBCMT keep the compiler that built LIBCMT, not the game's.**
  `src/Develop/crt_region/initterm.c` (GOLDTL `0x64e761`) is EXACT only under
  `msvc-6.0-sp6` and is pinned there per-file. Expect more crt_region pins;
  check them before "fixing" a CRT-region mismatch under the target profile.
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
  2-byte nops, both wrapper styles (4 push-`[mem]`, 3 load-first) —
  which is the machine-readable form of the project-wide "per-file flags
  vary" finding. Evidence: `rebrew toolchain detect original/Server/server.dll --json`.
- **`-sp5-pp` is a per-file pin, not a project setting, and it is worth 4
  bytes net.** Three files carry it (`spiel_dumpD.c`, `ahm_ExAllocAlchemist.c`,
  `ls_LoadBuildingEntityState.c`); 16 of 16 unpinned rows are *worse* under it,
  with `ServerMainThread` 2075 -> 1224 matched. Evidence: rounds 502/842,
  `docs/codegen-walls.md` §196.

## Deliverable mechanics

- **The shipped `build/server.dll` is not what the linker produces.**
  `rebrew postlink` writes `.data`, `.rdata`, `.reloc` and the headers from the
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

**Every function inside those spans is already implemented, annotated, and byte-identical.** Measured — for
each of the 12 spans, every annotated VA inside it, with its length to the next annotated VA and its
residue in the shipped file:

| annotated functions inside the 12 spans | 25 |
|---|---|
| byte-identical (residue 0) | **24** |
| with residue | 1 — `cm_ExSellObjekt` (`0x1000d930`, 966 bytes) |

Total residue inside all twelve spans: **966 bytes**, all of it `cm_ExSellObjekt` — a carrier already in the
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
entries against 283 annotated functions — a *coarser* partition than the annotations. `0x1000d8a0` is one
2008-byte entry in the inventory, while the tree annotates **two** functions inside it:
`cm_ExTransferCurrencyNoKill` at `0x1000d8a0` (144 bytes, byte-identical) and `cm_ExSellObjekt` at
`0x1000d930`. The inventory entry's size is the gap to the *next inventory entry*, so it overlaps functions
the annotations already separate.

**Consequence for the earlier rounds.** `rebrew verify`'s denominator (283) counts annotations, which is the
right population. Nothing was ever unreachable via `rebrew skeleton`; the ten VAs simply had annotations
already. The "694 raw-link capability bytes" of round 1022 are real as a *measurement* (those bytes differ in
the raw link) but they are **not** un-implemented code, and closing them is not a coverage task — it is the
same codegen work as any other carrier, and `cm_ExSellObjekt`'s 966 bytes are already the subject of a
documented wall.

Evidence: enumeration of every annotated VA inside each span, with per-function residue measured against
`original/Server/server.dll` and `build/server.dll`; `grep` of `FUNCTION: SERVER` across `src/server.dll`;
`rebrew asm` at each VA.

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
error: postlink failed: built .text is not position-aligned with the reference —
only 4847/7463 layout-map entries validate (64.9%, minimum 90%).
.text VirtualSize built 0x221f6 vs reference 0x22846.
```

That message describes the **plain CMake link** (`0x221f6`), which is not the deliverable. The deliverable is
`--target final`, which runs `scripts/split_link.sh` (per-reference-offset composition, LIBCMT placed as
stock objects) and then `postlink_residual.py`. `rebrew postlink` in the POST_BUILD step refuses a
non-position-aligned `.text`, and the plain CMake link is exactly that — by design.

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

## Faking the original `D:\` build path through wine is possible — and unnecessary (round 1054)

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
container already mounts** — the project root or the wineprefix — because `_docker_run` mounts only those
two; a `d:` pointing at `/tmp` fails with `C1083` even though the symlink is correct.

**But it is unnecessary, and here is the measurement.** `__FILE__` is used **nowhere** in this tree —
`grep -rn "__FILE__" src/server.dll` finds exactly one hit, and it is in a comment. Every `D:\Develop\...`
string is a **hand-written literal** passed to `LogMessageInternal`, escaped in the source:

```c
LogMessageInternal("D:\\Develop\\DieGildeAddOnServer\\server.c", 0x5df, "LOBBY mode", 1);
```

All **14** `D:\Develop\...`-shaped strings in the reference are **already present in the shipped file** —
verified by scanning both images — and all 11 distinct literals are written out in the sources.

**So the path axis is already closed by construction, not by luck.** The reconstruction reproduces these
strings by typing them, which is what the original source did too (the original called
`LogMessageInternal("D:\\Develop\\...", ...)` with a literal, not `__FILE__` — if it had used `__FILE__`, the
strings would carry the SDK's own layout, and `/FC` would have been required).

**When this WOULD matter.** If a round ever converts one of these literals to `__FILE__` — for instance while
tidying, or because a decompiler emitted `__FILE__` for a path argument — the build would silently start
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
  `0x1176759c` — `.bss` in ordinary terms — has no file bytes in either image and is zero-filled by the
  loader. `section_symbol_bytes` skips it deliberately (`# zero-fill tail (BSS): no file bytes to read`), so
  `rebrew verify --data` cannot compare those symbols and never marks them VERIFIED.

**Data state: 329 metadata symbols, 0 differences from the reference.** 122 are `VERIFIED` by
`verify --data`; the other 207 are `UNCHECKED` and un-clearable, but were checked independently by direct
byte comparison — 84 import slots (all dwords identical), 111 in the zero-fill tail, 5 with file bytes
(identical), 7 sizeless. The 18 `__imp__` items and the 123 `start-data` items that `rebrew todo` used to
list were artefacts of that gap; both lanes are now empty and only the 2 known `.text` carriers remain.

**`rebrew verify --data` now prints its denominator** (fixed round 1079, rebrew commit `3f7cefea`). The
summary reads `data: 122 matched, 0 mismatched, 0 missing (122 of 329 symbols compared, 37%)` and names why
the other 207 are not comparable, and `--json` carries `total`/`compared`/`not_comparable`/`coverage`. Before
that fix the coverage figure was absent entirely and had to be reconstructed by calling
`section_symbol_bytes` on both images and counting `ref_sizes`; see `docs/measure-traps.md` §51 for why a
zero in a diff-shaped result is never a statement about the whole tree.

## Section-by-section parity: the shipped file is byte-identical outside `.text` — BY COPYING, NOT BY COMPILING (round 1089, corrected round 1092)

**Read the raw-link column before drawing any conclusion from this.** The zeros below are produced by
`rebrew postlink` writing those sections from the layout package (`layout/server.dll/*.hex`), which holds the
reference's own bytes. They are **not** evidence that the compiler and linker reproduce them. Round 936
recorded this correctly; the round-1089 version of this entry did not, and is corrected here.

| section | shipped deliverable | **raw link (real compile + link), pre-fixer** |
|---|---|---|
| `.text` | differing 8,628 | differing **14,347** |
| `.rdata` | differing 0 | differing **1,268** |
| `.data` | differing 0 | differing **21,481** |
| `.reloc` | differing 0 | differing **7,103** |

"A zero here is a tautology, not a match" — and `rebrew verify --data` says so itself, in its own output:
*"server.dll's .data is byte-identical to the reference. If the build postlinks by copying that section, these
results are tautological — point --built at the raw link instead."*

The measurements below are still true **of the shipped artifact**, and that is the artifact the objective
names. They simply cannot be evidence about codegen. For the shipped deliverable:

| section | SizeOfRawData | differing bytes | SHA-256 (ref = built) |
|---|---|---|---|
| `.text` | `0x23000` | **8,628** | differs |
| `.rdata` | `0x3000` | **0** | `8046aaa446c8…` |
| `.data` | `0xe000` | **0** | `e1f56d0d50af…` |
| `.reloc` | `0x11000` | **0** | `d8cf33e18c1a…` |

File size is 286,720 bytes in both, and all four section headers are byte-identical. The whole-file SHA-256
still differs, and the difference is **exactly** the `.text` residue — nothing else in the image contributes.

**`rebrew verify --data`'s 37% coverage is the maximum, not a shortfall.** Its report reads
"122 of 329 symbols compared". The 207 it does not compare decompose as: **73** symbols declared `.data` that
sit past `rawsize` `0xe000` in the virtual tail (`0x10035000`+), **84** import slots, **50** `.bss`. Measured
directly: **none of the 73 is inside the file-backed region** `0x10027000`..`0x10035000`. The 122 compared are
85 `.data` + 37 `.rdata`, which is every symbol that has file bytes in either image to compare against. There
is no additional coverage to be had — the remainder is symbols the file format does not carry.

**What this means for the done-criteria.** "Every data byte matching" is satisfied and independently verified.
"`.text` VirtualSize exactly `0x22846`" is satisfied (`0x22846` in both). "Import table exactly 100" is
satisfied. "residue at zero" and "all functions EXACT" are the two clauses that are not, and they are the same
clause: the 8,628 bytes above.

## Finding code we already reversed in another target: `rebrew cross-import`

The three targets share one source tree and one codebase, so most of the work
is already done somewhere else.  The question "is this GOLDTL function already
reversed in GOLD or in SERVER, and in which file?" is answered by
`cross-import` in **report mode** (round 1378):

```
rebrew cross-import --from server.dll --target Europa1400Gold_TL.exe \
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
binaries were built with the same compiler product and version —
**MSVC 6.0, cl.exe 12.00.8804** — and differ only in the **code generator**
(c2.dll):

| binary | compiler version | code generator | `Rich` record | pp-only `test ah,X` sites |
|--------|------------------|----------------|---------------|---------------------------|
| SERVER | cl 12.00.8804 | stock VC6 c2 | **none** (no Rich header) | **0** |
| GOLDTL | cl 12.00.8804 | **Processor Pack** c2 13.00.9044 | comp_id `0x00302354`, count 154 | 1011 |
| GOLD | cl 12.00.8804 | **Processor Pack** c2 13.00.9044 | comp_id `0x00302354`, count 157 | 841 |

Three independent measurements, all agreeing:

1. **Compiler fingerprint (`@comp.id`).** The Processor Pack image
   (`rebrew/msvc:6.0-sp5-pp-win32`) stamps every object with
   `@comp.id = 3154772 = 0x00302354` — product `0x0030`, build `2354` = 9044,
   i.e. c2.dll 13.00.9044.0.  Nine VC6 code generators are registered
   (`6.0`, `sp1`-`sp6`, `win9x`, `sp5-pp`) and each stamps a different
   `@comp.id`; only `sp5-pp` uses product `0x0030`.  Both clients' Rich headers
   carry exactly that record (counts 154/157 objects); SERVER's file has no
   Rich header at all (minimal 0x80 DOS stub), so nothing is recorded there.
   Do not trust `diec`'s "compiler 13.00.9178" line for these clients: that
   value comes from a non-compiler Rich entry (a statically linked SDK/MSS32
   object); the compiler record is the `0x0030`/9044 one.

2. **Code-generator fingerprint.** Compiling one fixed source (float and
   double `==`, `!=`, `<`, `<=`, `>`, `>=`, branch and int-returning forms)
   with `/Od`, `/O1`, `/O2`, `/Ox`, `/Os`, `/O2 /Op`, `/O2 /Oa`, `/O2 /Ot`,
   `/O2 /Oy-`:
   - `sp5-pp` emits `test ah,0x44` (+ `jp`) and `test ah,0x05`, and **never**
     `test ah,0x40` — under all nine flag sets.
   - All eight plain VC6 code generators emit `test ah,0x40` + `test ah,0x01`
     + `test ah,0x41`, and **never** `0x44`/`0x05` — under all nine flag sets.
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

The sweep of 14 matched GOLDTL functions (all game code — none carries a
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
  along). `rebrew cross-import --from server.dll` therefore reverts even at
  score 100 — that is the tool being honest, not a match-quality bug.
- GOLD and GOLDTL share the generator, so GOLDTL→GOLD marker moves do verify
  (round 1378: GOLD `0x421ed0` from GOLDTL `0x41d4d0`, EXACT).
- Plain VC6 SP5 and SP6 output is byte-identical for the functions measured
  here, so the server cannot be pinned to a specific service pack — only to
  "a plain, non-Processor-Pack VC6 code generator".  The three per-file
  `sp5-pp` pins in `CMakeLists.txt` are marginal partial-match wins (834 vs
  828 bytes, 824 vs 820), not evidence of a pp-built server.

### Does the Processor Pack work for the SERVER target? (round 1379e)

Partly — per file, never as the target profile.

Same file, same flags, only `--toolchain` varies, 12 matched server functions
(the 5 that carry a plain x87 compare plus 7 ordinary ones):

| result | count | functions |
|--------|-------|-----------|
| byte-identical under sp5-pp AND sp6 | 9 | `cm_ExSetAttribute`, `cm_ExModifyHealth`, `cm_DispatchProduction`, `cm_ChkEntityLookup`, `InitializeLogAndErrorHandler`, `cm_ExSetWohnsitz`, `cm_ExCreateGeb`, `cm_ChainAssignId`, `cm_ChkSellObjekt` |
| pp **breaks** it | 3 | `ahm_ClampFloatValue` 0x1000c3c0, `cm_ExModifyStat` 0x100100a0, `sim_FindAndMatchParents` 0x100151e0 |
| pp-only (pp matches, plain does not) | 0 | — |

The rule is exact: the three that break each contain the plain idiom
(`fnstsw ax; test ah,0x01` — 2, 3 and 2 sites) **inside the compared
function's own span**, and every function whose span contains none is
generator-insensitive.  `cm_ExSetAttribute` 0x1000e8d0 has three such sites
*after* its end and stays byte-identical under pp — the earlier inventory
attribution had folded them into it.

Conclusion (round 1379f): the server build is **single-toolchain** — one plain
VC6 profile for every TU.  The three `msvc-6.0-sp5-pp` pins that used to sit in
`CMakeLists.txt` are gone.  They were bought with partial-match scores on
functions nobody has matched yet (171/346 vs 162/346, 834 vs 828, 824 vs 820),
i.e. a wrong-compiler coincidence, and they contradict the binary's own
fingerprint.  Removing them costs nothing measurable: with all three objects
force-rebuilt under sp6, `rebrew verify --full` is 281 passed / 264
byte-matched, gate residue 11735, raw-link `.data` 22749 and imports 100 —
identical to the pinned build.  `scripts/gate.sh` now fails if a pin of the
other generator family appears, and `rebrew toolchain detect` refuses the pack
profile for the server target.
