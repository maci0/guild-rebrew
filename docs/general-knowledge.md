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

- Compiler: MSVC6. Flags: `/O2 /Gd` default project-wide (per-file variance
  suspected but unattested — see codegen-walls §needle-2).
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
