# Goal: one faithful source tree, three byte-identical binaries

Reconstruct the shared C source tree the original developers most likely used,
and build `server.dll`, `Europa1400Gold_TL.exe` and `Europa1400Gold.exe` with
100% raw-file byte identity to their references. Both source fidelity and binary
identity are required. A matching binary assembled from fabricated source does
not complete this goal.

This is the durable objective for `goal-dd7dd2dd-8cde-4e14-a043-8674d4ec5631`.
If session goal state is lost, restore the objective from this file. Read
[AGENTS.md](AGENTS.md) for project rules and the relevant Rebrew skill before work.

## Priority and scope

1. Preserve and complete `server.dll`, including faithful reconstruction of
   discarded original source that affects link inputs and relocation reservations.
2. Reverse `Europa1400Gold_TL.exe` as the primary client workstream.
3. Validate `Europa1400Gold.exe` from the same source tree and verified related
   imports. Reverse unique Gold code when needed; do not reconstruct shared logic twice.

Keep one definition of shared game logic, with one managed identity per target.
Use target-specific code only where native evidence supports a difference.
Source placement and headers follow attested `__FILE__` paths, module conventions
and actual cross-TU use. Mark inferred names, layouts and organization explicitly.

## Completion criteria

All criteria must hold against current source, headers, compiler inputs and images:

- All three targets build reproducibly from the unified tree using their pinned
  toolchains. The raw linked files equal their references byte for byte, including
  headers, sections, imports, exports, resources and relocations. Postlink repairs
  cannot substitute for raw-link identity.
- Every reconstructed game function is EXACT in its object or verified as linked
  EXACT in the raw image. Library code/provider evidence is accounted separately.
  Every data byte and symbol placement is verified; unresolved owners stay explicit.
- The server passes `scripts/gate.sh`, including raw-file identity, linked EXACT,
  data/import placement and Wine load/export checks for `Init` and `Exit`.
  Its `.text` VirtualSize is `0x22846` and its import table matches all 100 entries.
- Both clients pass equivalent full-image checks against their own references.
  The current server gate alone does not establish client completion.
- Shared logic has no drifting duplicate bodies. Types, declarations, storage
  owners and native operands are reconciled across targets. No fabricated logs,
  placeholder calls, padding or fixups remain to manufacture agreement.
- All-target lint has zero errors and warnings, required checks pass, and the
  naming, native evidence and continuation documents are current.

Object RELOC, NEAR_MATCHING, PROVEN, bounded fixtures, coverage percentages and
historical green builds do not establish completion. Report file agreement,
accounted text, game reversing progress and stored data verification separately.

## Non-negotiable constraints

- C89 under MSVC6. No naked functions, `_emit` or inline assembly unless positive
  native evidence establishes original assembly at that site. A difficult match
  is insufficient evidence. Preserve reviewed assembly provenance where applicable.
- Run CL/LINK/LIB inside the configured Docker images: plain SP5 for the server,
  Processor Pack SP5 for both clients. Use the project's pinned environment;
  set `REBREW_DEBUG_INFO=OFF` for link checks. No host Wine/compiler fallback.
- Check library attribution before implementing a function. Reuse linked stock
  CRT and available library sources/providers; do not reimplement stock library
  code as game progress or patch third-party archives to force a match. Any
  evidenced original vendor changes must be pinned and reproducible.
- Preserve one storage owner per global and canonical subsystem declarations.
  Interior views, compiler literals, layout spans and imports are distinct facts.
  Never infer allocation ownership from an extern, address proximity or coverage row.
- Follow [naming_conventions.md](docs/naming_conventions.md). Attested spelling
  wins, including original errors. Use established module prefixes and record
  inferred names. Rename through `rebrew source rename`.
- Keep shared types in their owning headers; preserve byte-sensitive declaration
  order. Bind stable type IDs through `rebrew types bind`, separating C layout
  from evidenced allocation/stride extent. Resolve duplicate-symbol findings.
- Never hand-edit managed function, data, type or source-evidence stores. Use
  Rebrew CLI/locked APIs. Preserve unrelated changes and prior verified matches.
- Never weaken a gate, baseline, extent or binding policy to hide a regression.
  Do not restore invented logging calls or relocation reservations to recover bytes.

## Work loop

1. Read `rebrew todo --json` for the selected target and address-keyed findings
   before repeating experiments. Check existing CLI help/tools before writing helpers.
2. Check libraries, native bodies, callees and operands. Compare available
   decompiler seeds, including Kuna, against native evidence; then write real C.
3. Test/diff after source changes. Verify related imports against each destination
   before promotion. Use matching searches only after ordinary edits stall.
4. Reverify affected callers and all target contexts after shared-header, type,
   ownership or declaration changes. Known-binding checks remain enabled.
5. When matching measures disagree, compile an isolated raw native link and measure
   the complete image. Run `uv run --frozen scripts/gate.sh` before every commit. Client changes
   also require client-specific validation. Keep failed checks visible.
6. Read current coverage through `rebrew status` and the live coverage view.
   Use `rebrew coverage export` for an explicit offline snapshot; never maintain
   a second progress store. Record current evidence and concise next steps here.

Use the existing evidence homes: names in `docs/naming_conventions.md`; C shapes,
allocation and exhausted levers in their respective codegen documents; measurement
and process traps in `docs/measure-traps.md` and `docs/workflow-traps.md`; session
attempts and receipts in `docs/TODO.md`. Probes belong in ignored `.scratch/`.
Do not rerun exhausted probes without new evidence.

Fix Rebrew bugs in `/home/maci/Desktop/Projects/relumea/repos/rebrew` with a
reproducing regression test and a passing upstream suite before returning to
reversing. Record every missing capability immediately in that checkout's
`docs/IDEAS-GUILD.md` with the problem, proposed capability and replay evidence.
Keep binary-specific evidence in this project. Publishing and live sync require
explicit authorization; this file does not grant it.

## Current continuation — 2026-10-16

The full goal remains ACTIVE and incomplete. Goal68 admits and reconstructs one
shared object-universe mapping helper, TL515540 / Gold511df0, adding151/146
matched executable game bytes. Complete proofs validate all10operands and16
rejecting controls per target. Six bounded cases/client (24 native/compiled
executions) preserve signed cached values, allocator failure without mutation,
map→used→name write order and fresh object-type/map reload after the selected
initializer. The initializer/allocator services are modeled, not real execution.

Reviewed inventory repair splits each preceding496-byte interval into336+160.
Both old331-byte matches and historical reference hashes survive, with five
NOPs before the helper; its trailing9TL/14Gold NOPs remain separate. All six
helper-call edges across five existing caller contexts validate; Gold4fbd10
retains its existing SIZE_MISMATCH. The private d3.universe-view stable type
records only row strides3dcTL/3e0Gold and used byte+3d5, not string capacity,
complete allocation or storage ownership. game_data.h owns the compatible
prototype-table pointer declaration; no storage or initializer provider is added.
Helper name and source placement remain inferred.

The canonical gm_AllocGebaeude definition now agrees with command.c's narrow
unsigned-char / unsigned-short inputs. A separate full-width int count naturally
reuses the dead input argument slot under VC6. The previous C2443 narrowing
failure came from continuing to use a byte parameter as the assembly's DWORD
count; it did not establish wide semantic inputs. All1078 factory bytes,
49operand destinations,6literal uses and both internal tables agree, while all
127 old spiel.c contexts preserve complete code/fixups/literals, including11weak
bodies. All43private field declarations stay unchanged. The existing SERVER-only
original fill macro is retained and newly documented from independent cross-site
compiler controls; no new assembly, flags or client factory provider is claimed.

TL no-source remains1211 /1206802bytes because the admitted helper was previously
hidden rather than a separate no-source row. Newly matched game code is151TL /
146Gold; the factory repair adds zero matched bytes. TL accounted text is now
1123675/2491370 =45.1026945...%, displayed45.1%; libraries/padding are separate
from this new game-byte progress. Scope verification preserves all prior strong
matches. All6065 prior strong statuses retain their exact value; all prior weak
statuses are unchanged. All-target lint/data checks are clean; both client type
checks compile without findings. The fresh SERVER gate passes316/316 functions,
652/652data comparisons and all286720raw bytes, with matching imports/relocations/
layout and successful Wine load/exports. Client full links remain unverified.

The next package is cm_ExCreateGeb TL4cc820 /Gold4cbca0: a full838-byte scratch
match,44operands,eight literals,81rejecting controls per client. Factory signature
debt is closed, but placement-result/callback/iterator contracts, helper providers
and Gold twins still require reconciliation before adoption. A newly measured
placement callback598550 /58fc80 matches148bytes per client, separate from12NOPs;
case-insensitive bk_ acceptance followed by case-sensitive strstr is native
behavior. Keep that scratch result separate from STATUS until its callers/types
are integrated. Reports: .scratch/goal68/{factory-production,factory-review,
helper-proof,placement-contracts}.

Do not restart exhausted court/queue/office/camera/timer/runner or recent bounded
families without new evidence. OWN-before-OTHER query order, discarded server
inputs and the first cutscene command's allocator-zero read at address8 remain
required native behavior. AttachAnimLooped adds454bytes/client in Goal67;
Goal66 adds760/client. amt_ExecGebaeudeBauen remains543native/527compiled and
ls_LoadCharacter1915/1904 with strrchr last-underscore semantics and pointer debt.
CHARACTER allocation0x244 differs from Figure's0x228 accessed view and from D3.
Both clients' complete raw-file/data/provider/storage proofs and broader source
contracts remain open. Every completion criterion above still applies.

## History

[Archived checkpoints](docs/goal-history.md) preserve the previous goal file in
full. They are historical evidence, not current status or instructions. Keep this
file concise: replace the current continuation when it changes; write detailed
chronology to `docs/TODO.md` and evidence to its owning document.
