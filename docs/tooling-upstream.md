# Tooling

Use `uv run rebrew <command>` and its public APIs before adding a helper.
`pyproject.toml` and `uv.lock` own package pins. A sibling tooling checkout is not
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
| `scripts/gen_bss_layout.py` | Measured server allocation/layout recipe |
| `scripts/gen_import_includes.py` | Native import retention/order recipe |
| `scripts/gen_data_lead.py`, `scripts/gen_text_lead.py` | Existing measured link-layout generators |
| `scripts/progress_svg.py` | Graphics from a canonical status report |
| `stubs/linked_manifest.py` | Scaffold attribution from a successful link map |

Layout generators do not establish original storage owners. Retired split-link,
copied-CRT and replacement-import emitters are not build alternatives.

## Open gaps

Reusable issues belong in the upstream checkout's `docs/IDEAS-GUILD.md`, with
replay evidence. Do not treat an old local "unreleased" label as current release
state; the archived repair reports below describe their own package versions.

The earlier `data layout fill` audit wrote client pads into shared server BSS
source. Installed help still has no output-source selector. This documentation
pass checked help only, not the write behavior. Preview the exact target/files
and review ownership before using it; do not infer permission to emit storage.

## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

The [November 5 archive](archive/2026-11-05-documentation.tar.xz) preserves the full
`docs/tooling-upstream.md` notebook, including corrections and receipt paths. Entries below locate
historical claims, not current instructions or verdicts. Hex values include
code/data addresses and constants.

```sh
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/tooling-upstream.md | less
```

| Historical section | Referenced hex values |
| --- | --- |
| <a id="project-tooling-and-upstream-rebrew"></a>Project tooling and upstream Rebrew | - |
| <a id="retained-scripts"></a>Retained scripts | - |
| <a id="replacements-for-retired-helpers"></a>Replacements for retired helpers | - |
| <a id="upstream-receipts"></a>Upstream receipts | - |
| <a id="import-table-api-extraction-2026-10-20"></a>Import-table API extraction (2026-10-20) | - |

</details>
