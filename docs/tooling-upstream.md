# Tooling

Use `.venv/bin/rebrew <command>` and its public APIs before adding a helper.
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
| Check library origin/providers | `library inspect`, `match`, `review-native`, `adopt` |
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
procedure. The BSS and data-lead generators were retired on 2026-11-12: their
outputs (`src/bss_layout/*.c`) are committed and verified, and rerunning them
would reassign ADDRESS bindings and split complete objects. Retired split-link,
copied-CRT and replacement-import emitters are not build alternatives.

## Open gaps

Reusable issues belong in the upstream checkout's `docs/IDEAS-GUILD.md`, with
replay evidence. Check installed help and preview the selected target's writes
before using `data layout fill`. Review the proposed source paths and storage
ownership before applying the plan.

## Archived techniques

Original notebook: `docs/tooling-upstream.md` in the [documentation archive](goal-history.md#full-notebooks).

- Project tooling and upstream Rebrew
- Retained scripts
- Replacements for retired helpers
- Upstream receipts
- Import-table API extraction (2026-10-20)
