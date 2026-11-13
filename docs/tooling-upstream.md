# Tooling

Use `uv run rebrew <command>` and its public APIs before adding a helper.
`pyproject.toml` and `uv.lock` specify package pins. A sibling tooling checkout is not
needed for normal reconstruction.

## Choose an existing command

| Need | Command group |
| --- | --- |
| Address-keyed research | `source findings` |
| Work selection and accounting | `todo`, `status`, `coverage catalog` |
| Symbolize data accesses | `source symbolize --dry-run` |
| Rename/rebind a definition | `source rename`, `source binding` |
| Inspect complete native code | `binary asm show`, `binary xrefs` |
| Review/repair native boundaries | `binary repair-extents --dry-run` |
| Compare function bytes | `test`, `diff`, `diagnose probe` |
| Check linked operands/placement | `binary relocs`, `build check-text-placement`, `build check-data-placement` |
| Organize source/link order | `source organize`, `build anchors`, `build link-order` |
| Check library origin/providers | `library inspect`, `library match`, `library review-native`, `library adopt` |
| Reproduce vendor sources | `library vendor` |

Read the command's help before composing flags. Preview guarded writes and use
the returned digest. [AGENTS.md](../AGENTS.md) owns metadata and upstream repair rules.

## Project-specific scripts

| Script | Purpose |
| --- | --- |
| `scripts/gate.sh` | Server acceptance checks |
| `scripts/verify_objective.py` | Independent raw-file equality check |
| `scripts/wine_load_check.sh` | Load the server DLL and resolve Init/Exit |
| `scripts/gen_import_includes.py` | Native import retention/order recipe |
| `scripts/progress_svg.py` | Graphics from a canonical status report |
| `stubs/linked_manifest.py` | Scaffold attribution from a successful link map |

Layout generators do not establish original storage owners.
`scripts/gen_text_lead.py` is disabled by default and is not a reconstruction
procedure. The BSS and data-lead generators were removed on 2026-11-12; their
outputs (`src/bss_layout/*.c`) remain committed. Recreating those generators
would risk reassigning ADDRESS bindings and splitting complete objects. Retired
split-link, copied-CRT and replacement-import emitters are not build alternatives.

## Open gaps

Reusable issues belong in the upstream checkout's `docs/IDEAS-GUILD.md`, with
replay evidence. Check installed help and preview the selected target's writes
before using `data layout fill`. Review the proposed source paths and storage
ownership before applying the plan.

The managed support-purpose descriptions for `src/crt_region/amsg_exit.c` and
`src/crt_region/data_restore.c` still describe retired link/postlink recipes.
Those recipes are retired, and the current server build excludes both files.
Correcting the labels through locked writers remains separate metadata work.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
