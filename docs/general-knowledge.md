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

## Discovery boundaries: 12 symbols in `command_c` are blocks of contiguous functions

`rebrew verify --full` reports "13 function(s) have annotation SIZE differing from the binary-derived
size". Twelve of them are `command_c/*.c`, all with `binary_size > annotation_size`, and the cause is not
codegen: **the discoverer merged a contiguous run of small command functions into one symbol.** Our source
implements the first function; the rest of the span is several sibling functions that have no VA of their
own and therefore never appear in `function_structure.json`.

Counted by scanning each span for `ret` (`0xc3`) bytes:

| VA | span | `ret`s | functions in span | ours |
|---|---|---|---|---|
| `0x10010260` | 176 | 9 | 9 | 144 B (first) |
| `0x1000f3b0` | 720 | 8 | 8 | 206 B |
| `0x100100a0` | 448 | 8 | 8 | 159 B |
| `0x1000d8a0` | 2208 | 6 | 6 | 142 B |
| `0x1000e690` | 320 | 6 | 6 | 191 B |
| `0x1000d6e0` | 272 | 5 | 5 | 78 B |
| `0x1000e8d0`, `0x1000eaa0`, `0x1000f980` | 464/352/432 | 4 | 4 each | 239/208/335 B |
| `0x1000cfe0`, `0x10010010` | 96/144 | 3 | 3 each | 64/110 B |
| `0x1000d330` | 32 | 2 | 2 | 14 B |

**50 extra reference functions** sit inside these 12 spans with no inventory entry. They are game code, not
library: they use `g_next_object_id` (`0x10030b6c`), `g_unknown_1de450` (`0x101de450`) and `g_item_def_table`,
and call game functions such as `0x10019cd0`, `0x100196c0`, `0x10019b80`.

**The extreme case is `cm_MarkAndReturn`** (`0x1000d330`): our 14-byte function is **EXACT**, and the
reference's remaining 18 bytes are `90 90 | b8 01 00 00 00 c3 | 90...` — a second complete function
(`mov eax,1; ret`) followed by padding. The 32-byte "binary size" is the gap to the next entry, not this
function's length. An `EXACT` status with a size divergence is therefore not a contradiction.

**Consequence for the objective.** `rebrew verify --full`'s denominator (283) counts discovery symbols, not
reference functions. Closing these 12 spans means implementing ~50 functions that no tool will hand out via
`rebrew skeleton`, because they have no VA in `function_structure.json`.

**They do cost residue — but only 694 of the raw link's 14,347 bytes.** Measured against the raw link
(`build/split_poc.dll`), not the shipped file:

| span | raw-link differing bytes |
|---|---|
| `0x1000d8a0` (2208 B) | 569 |
| `0x1000eaa0`, `0x1000e8d0`, `0x1000f980`, `0x1000e690` | 24, 21, 16, 15 |
| the other seven spans | 4-12 each, `0x10010010` zero |
| **total** | **694** |

The other 13,653 raw-link differences lie outside these spans — in the 19 carriers and in library
placement.

**Do not measure this on the shipped file.** `build/server.dll` reads **0** differing bytes across all
twelve spans, because postlink rewrites the `.text` data operands and `E8`/`E9` targets from the layout
package. The shipped file is the graded artefact and its number is correct for the objective, but it is
the wrong ruler for "does our build produce these bytes" — the same self-certification trap
`postlink_residual.py` documents for `.data`, in its `.text` form. Three artifacts, three answers for the
same bytes: `.scratch/server.dll.prelayout` 50,285 (plain CMake link), `build/split_poc.dll` 14,347
(split-set composition, LIBCMT placed as stock objects at reference offsets), `build/server.dll` 8,628
(after postlink's operand rewrite).

Evidence: `python3 -c` scan of the reference's `.text` for `0xc3` within each span; `rebrew verify --json`
`size_divergences`; `rebrew asm` at each sibling start; per-span byte compare of `original/Server/server.dll`
against `build/split_poc.dll` and `build/server.dll`.
