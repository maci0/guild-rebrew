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
  was swept (codegen-walls §7 item 2, CLOSED): SP6 confirmed, flag axis
  flat, three `sp5-pp` file pins remain. Do not re-open.
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
