# Tooling

Use `uv run --frozen rebrew <command>` and its public APIs before adding a helper.
`pyproject.toml` and `uv.lock` specify package pins. A sibling tooling checkout is not
needed for normal reconstruction.

## Choose an existing command

| Need | Command group |
| --- | --- |
| Address-keyed research | `source findings` |
| Work selection and accounting | `todo`, `status`, `coverage catalog` |
| Symbolize data accesses | `source symbolize --dry-run` |
| Rename/rebind a definition | `source rename`, `source binding` |
| Inspect native code and references | `binary asm show`, `binary xrefs` |
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
| `scripts/verify_objective.py` | Independent server file equality and PE checks |
| `scripts/wine_load_check.sh` | Load the server DLL and resolve Init/Exit |
| `scripts/gen_import_includes.py` | Native import retention/order recipe |
| `scripts/progress_svg.py` | Graphics from a canonical status report |
| `scripts/gen_library_headers.py` | Rewrite `src/library_*.h` as lists of their LIBRARY rows; run after `library adopt` or `source rehome` |
| `stubs/linked_manifest.py` | Scaffold attribution from a successful link map |

Layout generators do not establish original storage owners.
`scripts/gen_text_lead.py` is disabled by default and is not a reconstruction
procedure. The BSS and data-lead generators were removed on 2026-11-12; their
outputs (`src/bss_layout/*.c`) remain committed. Recreating those generators
would risk reassigning ADDRESS bindings and splitting complete objects. Retired
split-link, copied-CRT and replacement-import emitters are not build alternatives.

## Open gaps

Record missing capabilities in the upstream checkout's `docs/IDEAS-GUILD.md`,
with the problem, proposed capability and replay evidence. Tooling bugs require
an upstream fix, regression test and passing suite before reconstruction resumes;
a local workaround or backlog entry does not close them. See
[upstream rules](../AGENTS.md#upstream-rebrew) for the checkout path.

Before using `data layout fill`, check installed help and preview the selected
target's writes. Review proposed source paths and storage ownership before applying.

The managed support-purpose descriptions mark `src/crt_region/amsg_exit.c` and
`src/crt_region/data_restore.c` as historical experiments excluded from the
current server build.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
