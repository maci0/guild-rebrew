# Goal — 100% Byte-Identical server.dll, Europa1400Gold_TL.exe, AND Europa1400Gold.exe (in this order or priority) Recompilation with rebuilt original shared source structure.

Tracked as goal `goal-dd7dd2dd-8cde-4e14-a043-8674d4ec5631` (revision 11, 55/256 rounds).
This file is the durable copy: if the session goal state is ever lost, re-create it from here.

## Targets

- Reproduce server.dll (PE, x86-32, MSVC6) from C source with 100% byte-identical
  output: every function EXACT, every data byte matching, link producing reference
  .text VirtualSize 0x22846 with residue at or below RESIDUE_BASELINE and
  `rebrew verify --full` at or above its BASELINE.
- Reproduce Europa1400Gold_TL.exe (PE, x86-32, MSVC6) from C source with 100%
  byte-identical output: every function EXACT, every data byte matching.
- Onboard Europa1400Gold.exe as a third rebrew target (binary present at
  original/Europa1400Gold.exe): run the intake workflow (rebrew init target,
  lib-match sweep, skeleton, test loop) and reproduce it from C source with 100%
  byte-identical output: every function EXACT, every data byte matching.
- Rebuild the original shared source structure: one shared source tree serving all
  three targets, shared game logic lives once with per-build markers (one source
  file carries one marker per build), target-specific code stays in target-specific
  dirs, no duplicated shared sources drifting apart; placement follows module
  prefixes and __FILE__/string evidence, recorded in docs/TODO.md session notes.

## Multi-target rebrew shortcomings

Any shortcoming detected in rebrew for multi-target work — overlapping functions and
data at different VAs across targets (cross-target VA-keyed metadata collisions,
shared-source marker handling, per-target lint/verify/test isolation,
layout/postlink per-target state, tool-owned TOML interference between targets) —
gets fixed upstream in the rebrew checkout (precedent: layout rename compat,
merge-sweep, case-label registry, atomic writes, verify-cache guards), with its suite
green before returning to reversing; never work around a toolchain bug in game source.
Missing features go in the rebrew ideas file (docs/IDEAS-GUILD.md in the rebrew
checkout): pain, proposed feature, evidence pointer. Append on encounter, not at
session end.

## Hard constraints

C only (C89, MSVC6). No `//` comments in code bodies, no declarations-after-statements,
no `/GS`, no `__declspec(noinline)`. No asm. No naked, no _emit, no __asm. Allowed only
when certain the original game source used raw asm at the same site. Certain means
positive evidence (for example a code shape no MSVC6 C output can produce, or a
corroborating string/symbol), not a hunch from a hard match. Doubt means C. Convert
existing _emit dumps to proper C. Never reverse ZLIB or LIBCMT. Both link in as stock
libraries. Before touching any function, run `rebrew lib-match --stock-lib LIBCMT.LIB
--va 0x<VA>`. Anything matching is library code — skip it. Never patch a .lib. On
unwanted library pull-in, displace with a local symbol definition or remove the
reference (see CMakeLists.txt _CRT_REGION_KEEP pattern). REBREW_DEBUG_INFO=OFF for
every link check (/debug grows .rdata and breaks postlink layout).

## Toolchain (always use it)

- `rebrew todo --json` — pick highest-ROI item first.
- `rebrew lib-match` — library check before reversing (see above).
- `rebrew skeleton 0x<VA>` — new function skeletons.
- `rebrew test <file> --json` / `rebrew test --all --json` — compile + compare.
- `rebrew diff <file> --json` — byte diff; `rebrew match` / GA only after the
  test/diff loop stalls.
- `rebrew verify --json` / `--full` — bulk check; `rebrew lint --json` — annotation
  validity; `rebrew data --json` — globals inventory.
- Judge candidates with `scripts/linktest.sh <file.c`, not object scores:
  positional `match_count` and structural `aligned` routinely disagree with the link
  (one hoist: aligned 662 → 665, match 1004 → 947, link +42 worse). When rulers
  disagree, link and measure.
- Run `scripts/gate.sh` before every commit (lint, compile, verify baseline, residue
  baseline). Never lower `RESIDUE_BASELINE` or raise `BASELINE` except on a measured
  improvement.

## Continuous hygiene (lint, verify, test)

Byte match rots fast. Run checks constantly, not just before commits:
`rebrew lint --json` after every annotation edit. Zero warnings is the only acceptable
state. `rebrew test <file> --json` after every source edit; `rebrew test --all --json`
after any shared-header or cross-TU change. `rebrew verify --json` for single-file
confirmation; `rebrew verify --full` for whole-tree state; `rebrew verify --data`
after any data, struct, or header change. Never count PROVEN as byte-matched — it ranks
below RELOC and always carries a non-zero delta. Never hand-edit
src/rebrew-functions.toml or src/rebrew-data.toml. They are tool-owned.
`scripts/gate.sh` before every commit, no exceptions.

## Done criteria

- server.dll: `rebrew verify --full` all functions EXACT, zero drift, linked .text
  VirtualSize exactly 0x22846, import table exactly the reference 100 imports,
  residue at zero, `scripts/gate.sh` green, Wine load + exports (Init, Exit) resolve.
- Europa1400Gold_TL.exe: `rebrew verify --full` all functions EXACT, zero drift,
  `scripts/gate.sh` green.
- Europa1400Gold.exe: onboarded as rebrew target, `rebrew verify --full` all functions
  EXACT, zero drift, `scripts/gate.sh` green.
- Shared tree: all three targets build from the same shared sources with no duplicated
  game-logic files, gates green on all.
- Docs current: shapes, allocator, codegen-walls, measure-traps, naming,
  general-knowledge, TODO.
