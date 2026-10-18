# Project tooling and upstream Rebrew

Use the pinned `rebrew <command>` CLI and public APIs before adding a helper.
Reusable bugs/features belong in
`/home/maci/Desktop/Projects/relumea/repos/rebrew`, with regression tests or an
entry in its `docs/IDEAS-GUILD.md`. Native addresses and acceptance criteria stay
here. Project rules are in [AGENTS.md](../AGENTS.md).

## Retained scripts

| Script | Project-specific purpose |
| --- | --- |
| `gate.sh` | Server build, function/data/image and load acceptance |
| `verify_objective.py` | Independent complete raw-file equality check |
| `wine_load_check.sh` | Load server DLL and resolve `Init`/`Exit`; does not call them |
| `gen_bss_layout.py` | Measured server allocation/layout recipe |
| `gen_import_includes.py` | Measured native import-retention/order recipe |
| `update_state_table.py` | Gate-generated `TODO.md` state block |

The BSS recipe's overlapping views are reconstruction assumptions, not permission
for duplicate allocations or inferred CRT ownership.

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

Split-link, copied CRT data, absolute-symbol and replacement-import emitters are
retired. Their historical receipts do not authorize recreating that pipeline.
Masked template hits do not establish native operand identity or a selected
provider. For composition outside the CLI, reuse public compile/COFF/relocation
and locked metadata APIs; keep target-specific controls in `.scratch/`.

Regenerate server game anchors with:

```sh
uv run --frozen rebrew build anchors --target server.dll \
  --data-source src/Develop/DieGildeAddOn/game/game_float_constants.c \
  --data-prefix _ --symbol _mark --output layout/server.dll/game-includes.rsp
```

The October consolidation reproduced the previous 251 function/34 data anchors.
CMake reads reference timestamps through Rebrew; the gate consumes structured
lint/verification results. Its independent objective verifier remains separate.
Project-level `compiler.execution_backend` also selects the CMake driver runtime;
[runner/cache guidance](verify-performance.md)
owns that behavior. `verify --no-cache` skips saved verification results and
still uses the compiler-object cache. Old `--full` transcripts are historical.

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
