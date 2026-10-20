# Project tooling and upstream Rebrew

Run the project CLI through `uv run rebrew <command>`; use its commands and
public APIs before adding a helper. For tooling development, fix reusable bugs
with regression tests in a [Rebrew checkout](https://github.com/maci0/rebrew) and
record feature gaps in its `docs/IDEAS-GUILD.md`. A tooling checkout is not required
to use the installed package. Native evidence stays here; [AGENTS.md](../AGENTS.md)
owns project rules.

## Retained scripts

| Script | Project-specific purpose |
| --- | --- |
| `gate.sh` | Server build, function/data/image and load acceptance |
| `verify_objective.py` | Independent complete raw-file equality check |
| `wine_load_check.sh` | Load server DLL and resolve `Init`/`Exit`; does not call them |
| `gen_bss_layout.py` | Measured server allocation/layout recipe |
| `gen_import_includes.py` | Measured native import-retention/order recipe |
| `progress_svg.py` | README progress bars and function map from `rebrew status --json` |
| [`stubs/linked_manifest.py`](../stubs/linked_manifest.py) | Client scaffold attribution from successful link maps |

The BSS recipe's overlapping views are reconstruction assumptions, not permission
for duplicate allocations or inferred CRT ownership. It reads the managed data
store through Rebrew; the scaffold manifest uses Rebrew's MSVC map parser.

## Replacements for retired helpers

| Old operation | Current tool |
| --- | --- |
| Vendor pristine-plus-patches reproduction (`vendor.py`) | `rebrew library vendor MANIFEST...`; check by default, regenerate with `--apply` |
| Address lookup (`whathas.py`) | `rebrew source findings 0x<VA> --json` |
| Address casts (`symbolize_addresses.py`) | `rebrew source symbolize FILE --dry-run` |
| Inventories/coverage adapters | `rebrew status`, `todo`, `coverage catalog`; views read canonical inputs |
| Relocation-set checks | `rebrew binary relocs --json` |
| Data placement | `rebrew build check-data-placement --json` |
| Source/link ordering | `rebrew build order-sources`, `link-order`, `anchors` |
| Library/template scans | `rebrew library inspect`, `match`, `scan-signatures` |
| Reference header/export timestamps | `rebrew binary pe --target server.dll --json` |
| Function probes and comparisons | `rebrew test`, `diff`, `diagnose probe`, `build round-trip` |
| Gate text scraping (`update_state_table.py`) | Gate JSON reports and `rebrew status`; the old TODO table is a historical checkpoint |
| Duplicate scaffold recipe (`stubs/recipe.txt`) | [Client build and regeneration instructions](../stubs/README.md) |

Split-link, copied CRT data, absolute-symbol and replacement-import emitters are
retired. Their historical receipts do not authorize recreating that pipeline.
The separate source store is retired as well. Format 3 `rebrew-functions.toml`
holds `source.definitions` and `source.files`, and `rebrew-data.toml` remains
format 2. Masked template hits do not establish native operand identity or a
selected provider. For composition outside the CLI, reuse public compile, COFF,
relocation and locked metadata APIs; keep target-specific controls in
`.scratch/`. `rebrew test --linked` still expects a Docker linked shell, and
the configured unshare backend refuses it. See
[runner limits](verify-performance.md#runner-and-caches).

Regenerate server game anchors with:

```sh
uv run rebrew build anchors --target server.dll \
  --data-source src/Develop/DieGildeAddOn/game/game_float_constants.c \
  --data-prefix _ --symbol _mark --output layout/server.dll/game-includes.rsp
```

The October consolidation reproduced the previous 251 function/34 data anchors.
CMake reads reference timestamps through Rebrew; the gate consumes structured
lint/verification results. Its independent objective verifier remains separate.
Project-level `compiler.execution_backend` also selects the CMake driver runtime.
See [runner/cache guidance](verify-performance.md) for runtime and cache behavior.
Old `--full` transcripts are historical.

## Upstream receipts

- [PR18](https://github.com/maci0/rebrew/pull/18): vendor checks, tool-selection
  guidance and packaged skills/template. Refresh generated guidance through
  `rebrew init --refresh-agents`, preserving local project rules.
- [PR24](https://github.com/maci0/rebrew/pull/24): rename planning includes bound
  library sources outside `reversed_dir` and other-target provider collisions.
- [PR25](https://github.com/maci0/rebrew/pull/25): exported K&R names use the shared
  parser, retaining typedef/member guards.

The [historical archive](goal-history.md#full-notebooks) holds the full retired
script inventory and migration audit. Its intermediate script counts are obsolete.

## Import-table API extraction (2026-10-20)

The remaining script audit found one reusable omission: the import API discarded
PE hint/name RVAs, so `gen_import_includes.py` repeated LIEF's import traversal.
Upstream commit `dea5295c`, published in [Rebrew 5.4.0](https://github.com/maci0/rebrew/releases/tag/v5.4.0), exposes
nullable `hint_name_rva` through `formats.import_table.parse_imports` and
`binary imports list --json`. Physical name-table position does not establish
linker load order; the server recipe and ordinal spellings remain project policy.

Guild now pins the published 5.4.0 wheel and its import recipe uses that API.
Before/after comparisons preserve all 39 lines and 1,205 bytes of the tracked
response file. The read-only replay and original migration patch remain in
`.scratch/rebrew-import-hint-name-rva-migration/` as local evidence.
All six release CI jobs passed, and the exact package artifact passed local
manifest verification and clean-venv smoke installation. BSS layout, independent
objective checks, Wine load acceptance and README graphics retain
their project-specific scope; no native build was rerun for this migration.
