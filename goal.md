# Reconstruction objective

Recover the shared C source tree the original developers most likely used, then
reproduce every byte of `server.dll`, `Europa1400Gold_TL.exe` and
`Europa1400Gold.exe` with the original toolchains. Both source fidelity and raw-file
identity are required. The objective remains incomplete; [TODO.md](docs/TODO.md)
owns current work.

## Priorities

1. Preserve the server and recover source that affects linking, including discards.
2. Recover GoldTL.
3. Validate the shared tree against Gold and recover its unique code.

## Acceptance criteria

- All three raw toolchain outputs match their full references, including headers,
  code, data, imports, exports, resources and relocations.
- Game functions are faithful C, except evidenced original assembly, and earn
  object EXACT or verified linked EXACT. Library origin and selected providers
  remain separate from game progress.
- Data bytes, placements, operand bindings and storage owners are verified.
- The server passes `uv run bash scripts/gate.sh`, including Wine resolution of
  `Init` and `Exit`, its 100 imports and `.text` VirtualSize `0x22846`. Each client
  passes equivalent checks against its own reference.
- Shared declarations, types and definitions agree across targets. All-target lint
  has no errors or warnings. No invented padding, placeholder calls, fabricated
  logs, drifting copies or postlink repairs remain.

RELOC, PROVEN, fixtures, coverage percentages and historical builds do not prove
completion. Report file identity, code accounting, game C recovery and data checks
separately. [AGENTS.md](AGENTS.md) owns implementation rules; the
[documentation index](docs/README.md) routes supporting evidence.

<!-- Section aliases retained for existing links. -->
<a id="continue"></a><a id="done-when"></a><a id="goal-one-faithful-source-tree-three-byte-identical-binaries"></a><a id="working-rules"></a>
