<a id="goal-one-faithful-source-tree-three-byte-identical-binaries"></a>

# Reconstruction objective

Recover the shared C source the original developers most likely used and
reproduce every byte of `server.dll`, `Europa1400Gold_TL.exe` and
`Europa1400Gold.exe` with the original toolchains.

## Priorities

1. Preserve the server and recover source that affects its link, including discarded contributions.
2. Recover GoldTL.
3. Validate the shared tree against Gold and recover Gold-specific code.

<a id="done-when"></a>

## Acceptance criteria

- Each raw toolchain output matches the entire reference, including code, data,
  headers, imports, exports, resources and relocations.
- Game functions use faithful C or evidenced original assembly. Each earns
  object `EXACT` or verified linked `EXACT`. Record library origin and the
  selected provider separately.
- Verify data bytes, placement, operand bindings and storage owners.
- The server passes its [gate](docs/build.md#run-the-server-gate), including Wine
  resolution of `Init` and `Exit`, 100 imports and `.text` VirtualSize `0x22846`.
  Each client passes equivalent checks against its own reference.
- Shared declarations, types and definitions agree across targets. All-target lint
  passes without findings. Remove invented padding, placeholder calls, fabricated
  logs, drifting copies and postlink repairs.

<a id="continue"></a><a id="working-rules"></a>

Report raw-file agreement, accounted code bytes, game C recovery and data
verification separately. The current task queue and measurements are in
[current work](docs/TODO.md). See the [project rules](AGENTS.md) for implementation
and verification requirements.
