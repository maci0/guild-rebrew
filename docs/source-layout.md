# Source layout

Use one shared tree under `src/Develop/`, following attested `D:\Develop` paths.
Label inferred placement. A byte match does not establish the original TU.

Paths in this table are relative to `src/Develop/`.

| Location | Role |
| --- | --- |
| `DieGildeAddOn/game/` | Game units such as spiel, sim and aemter |
| `DieGildeAddOn/command/` | Command and lobby units |
| `DieGildeAddOn/auxillary/` | Plant subsystem; retain the attested spelling |
| `DieGildeAddOn/loadsave/` | Save/load code |
| `DieGildeAddOnServer/` | Server entry and shared declarations |
| `Units/` | Error, allocation, VFS, network, audio and renderer units |
| `Unassigned/` | Bodies whose original module/TU remains unresolved |
| `DieGildeAddOn/unknown/` | Existing unresolved placement; review alongside `Unassigned/` before moving it |

Reconstructed filenames and private headers may be inferred even when the parent
unit is attested. Native paths, diagnostics, counterparts and dependencies provide
placement evidence; automatic address clustering alone does not.

## Move, merge or split

Use `rebrew source organize review` to inspect all-target providers, native order,
compiler context and storage instances. Preserve baselines, includes, declaration
order and flags. Update managed identities through Rebrew writers. Recheck
complete objects and operand bindings, then compare preserved and rebuilt raw
images with `rebrew source organize check`.

Do not split a native sequence merely because recovered definitions currently
live in different files. A shared file may contain target-specific definitions;
the same symbol spelling can also name independent functions.

[Data ownership](data-ownership.md) covers storage and declarations. Keep types
in the owning subsystem header or private source and bind stable IDs through
`rebrew types bind`. Use `Units/d3/d3_object.h` for current D3 layouts.

Use `rebrew source units --json` for native path witnesses. Current definition
bindings belong in managed function metadata; merge receipts belong in
[provenance](provenance.md).

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
