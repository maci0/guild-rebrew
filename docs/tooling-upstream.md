# Project tooling and upstream Rebrew

The October 2026 audit inventories all 46 scripts present before migration and
checks their callers, test coverage and corresponding upstream commands.
The cleanup leaves nine project-specific scripts and retires 37; old experiments
remain available in git history, with no retained build/test caller into that graph. Archived
`.scratch` contains 2,953 Python/shell files; its inventory and representative
recent reconstruction, native-object proof and vendor experiments were inspected,
not replayed. These files contain evidence for particular binaries, not a second
source of general Rebrew features.

The reusable missing feature was pristine-plus-patches source vendoring. It now
lives in `rebrew library vendor MANIFEST...`, with check as the default and explicit
`--sync` to regenerate. CMake passes our two manifests and retains all vendor-file
configure dependencies. The local implementation and tests were removed; upstream
owns the reproduction and failure tests. See [vendoring](vendoring.md).

The other safe deletion was `symbolize_addresses.py`: `rebrew source symbolize`
already provides its behavior, using the configured target, link map, managed data
identities and a C parser. Its upstream tests already cover skipping a definition
rather than a call site and keeping spans correct after preceding rewrites. The
local duplicate and its weaker brace-parser test were removed.

| Scripts before migration | Decision |
| --- | --- |
| `vendor.py` | Move upstream; migrate CMake, manifests, docs and tests. |
| `symbolize_addresses.py` | Delete duplicate; use `rebrew source symbolize`. |
| `reloc_set_check.py`, `data_placement.py`, `derive_link_order.py` | Use the upstream placement and ordering diagnostics in `rebrew binary relocs`, `rebrew build check-data-placement`, `rebrew build link-order` and `rebrew build order-sources`. Their historical reports also contain project-specific bands and split-link assumptions. Retire the duplicate diagnostics and old split-link reports. |
| `catalog_functions.py`, `whathas.py`, `update_state_table.py` | Retire the now-unused coverage adapter. Keep `whathas.py` and `update_state_table.py` for project notebook searches/rendering; upstream owns coverage APIs. |
| `gate.sh`, `verify_objective.py`, `wine_load_check.sh`, `native_timestamps.py` | Project acceptance criteria, independent raw-file cross-check and build/load harness. Upstream has whole-binary verification and binary information; our two exports, native linker clock and server-specific assertions belong here. Keep the independent check independent. |
| `gen_bss_layout.py`, `gen_game_includes.py`, `gen_import_includes.py` | Emit this server's explicitly recovered storage and ordered link anchors. Generic source ordering, import diagnostics and BSS tools already exist upstream; selected game constants and unresolved layout owners are not generic policy. |
| `map_libcmt.py`, `locate_sections.py`, `locate_common.py`, `import_thunk_census.py`, `ref_include_set.py`, `climb_link_order.py`, `split_audit.py` | Historical stock-library/template and linker-composition experiments. Upstream already inventories/matches archives, checks imports and reports placement. Masked prefix hits are not operand-supported identities or proof of the selected provider; do not promote this older matching policy. |
| `split_coff.py`, `flatten_comdat.py`, `resolve_static_labels.py`, `split_blob.py`, `make_split_rsp.py`, `split_link.sh`, `linktest.sh` | Historical split-link experiment, not the current stock-library reconstruction. Retire the entire experiment graph; the current build links stock libraries. |
| `absolute_symbols.py`, `emit_absolute_obj.py`, `emit_base_relative.py`, `emit_commons.py`, `emit_crt_data.py`, `emit_data_sections.py`, `emit_data_symbols.py`, `emit_defs.py`, `emit_idata.py`, `emit_thunks.py`, `apply_data_emit.py`, `apply_section_emit.py`, `data_emit_manifest.py` | Historical emitters coupled to the split-link experiment. Copied CRT data, promoted private labels and replacement import tables are not evidence of original source ownership. Retire these emitters rather than upstream the workarounds. |
| `check_crt_messages.py`, `check_crt_storage.py`, `check_game_readonly.py`, `check_zero_literals.py` | Assertions for exact project symbols and experiment outputs. Retire these checks; generic data verification and archive-owner accounting already exist upstream. |

Recent ad hoc proofs already use public Rebrew compilation, COFF parsing,
`apply_coff_relocations`, strict relocation comparison and locked metadata writers.
Their remaining values are target VAs, complete object extents, literal contents,
compiler profiles, negative controls and preserved-input receipts. Those are the
facts each reconstruction must establish; moving the facts into Rebrew would hide
rather than generalize them. Use the APIs and `rebrew build round-trip` for reusable
mechanics, and keep binary-specific proof controls with the reconstruction evidence.

The gate now consumes upstream lint/verification JSON and runs function, data,
text and whole-file checks in one report. Its duplicate PE import parser and
obsolete postlink API probe are removed. The independent objective verifier
remains a separate acceptance check.

The nine retained scripts are `gate.sh`, `verify_objective.py`,
`wine_load_check.sh`, `native_timestamps.py`, `gen_bss_layout.py`,
`gen_game_includes.py`, `gen_import_includes.py`, `whathas.py` and
`update_state_table.py`. They encode project acceptance, an independent verifier,
reference-clock/build adapters, evidenced storage/anchor choices and notebook
formats. They are not alternative generic Rebrew CLIs.

Upstream [PR #18](https://github.com/maci0/rebrew/pull/18) also updates the packaged
AGENTS template and workflow/data skills. The new tool-selection reference routes
common operations to existing commands and public APIs, distinguishes legitimate
binary-specific scratch proofs from missing reusable capabilities, and requires
caller migration and duplicate removal when work moves upstream. Generated copies
here are refreshed with `rebrew init --refresh-agents`; the naming rules below the
project-rules marker are preserved. Archived scratch proof receipts stay intact.
