# Goal: one faithful source tree, three byte-identical binaries

Reconstruct the shared C source tree the original developers most likely used.
Build `server.dll`, `Europa1400Gold_TL.exe` and `Europa1400Gold.exe` with 100%
raw-file identity to their references. Source fidelity and binary identity are
both required.

The goal is **incomplete**. Current evidence and next actions live in
[TODO.md](docs/TODO.md).

## Priorities

1. Preserve and complete the server, including discarded source that affects linking.
2. Reverse the T&L client.
3. Validate Gold from the same tree; reconstruct its unique code where needed.

Share game definitions across targets. Use native evidence for differences,
original paths, names, types and storage; label inferences explicitly.

## Done when

- All three raw toolchain outputs reproduce their entire reference files,
  including headers, sections, imports, exports, resources and relocations.
- Every reconstructed game function is object EXACT or verified linked EXACT.
  Data bytes, placements, operands and storage owners are verified. Libraries
  and their selected providers are accounted separately from game progress.
- The server passes `uv run --frozen scripts/gate.sh`, including raw-file,
  function, data, import, layout and Wine load/export-resolution checks for
  `Init`/`Exit`. Its `.text`
  VirtualSize is `0x22846`; all 100 imports agree. Both clients pass equivalent
  checks against their own references.
- Shared definitions, types and declarations agree across targets; all-target
  lint has zero errors/warnings. No fabricated logs, placeholder calls, invented
  padding, postlink fixups or drifting duplicate bodies remain.

RELOC, NEAR_MATCHING, PROVEN, bounded fixtures, coverage percentages and old green
builds do not establish completion. Report file agreement, accounted `.text`,
game reversing and data verification separately.

## Working rules

[AGENTS.md](AGENTS.md) owns the project rules; load the relevant Rebrew skill.
Use C89 and the pinned toolchain image filesystems: plain SP5 for server,
Processor Pack SP5 for clients. The configured execution backend is unshare.
Keep `REBREW_DEBUG_INFO=OFF` for link checks.

Check libraries and address-keyed findings before implementation. Test affected
definitions and callers in every target after changing shared inputs. Preserve
known-binding checks, canonical storage owners and compiler-sensitive declaration
order. Assembly requires positive evidence of original assembly at that site.
Never hand-edit managed stores, patch stock archives, weaken gates or substitute
postlink repairs for raw-file identity.

Fix tooling bugs with regression tests in
`/home/maci/Desktop/Projects/relumea/repos/rebrew`; record missing capabilities in
its `docs/IDEAS-GUILD.md`. Keep native evidence here and probes in `.scratch/`.
Publishing and live sync require explicit authorization.

## Continue

[TODO.md](docs/TODO.md) owns the current checkpoint and next actions.
[Goal history](docs/goal-history.md) records milestones; the
[documentation map](docs/README.md) routes technical evidence. Replace current
state when it changes; do not append another copy of this objective.
