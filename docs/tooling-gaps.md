# Rebrew tooling gaps pending upstream submission

The upstream checkout (`/home/maci/Desktop/Projects/relumea/repos/rebrew`) is
writable from this session, so fixes and features land there with tests. The
entries below either wait for a released wheel or describe the remaining
reviewed-writer gaps. Commands that need an unreleased fix run through the
development checkout:

```
uv run --project /home/maci/Desktop/Projects/relumea/repos/rebrew rebrew ...
```

## `source import-related` conditional definition is fixed upstream, unreleased

A shared source file that defines a function inside a target `#if` block made
the copy path raise `ValueError` and abort the whole batch, even with
`--dry-run`. The per-candidate call now catches that error, records an `error`
row naming the candidate, and continues. Regression test:
`tests/test_cross_import.py::TestCLI::test_conditional_donor_reports_row_and_continues`.
Fixed on the development checkout 2026-10-23, not in the 5.4.0 wheel.

## LIBRARY-over-FUNCTION writer is implemented upstream, unreleased

`rebrew library adopt` records a unique stock-archive match over an existing
FUNCTION or STUB row: it re-runs the project archive match, requires one unique
symbol/member candidate, refuses vendored-object matches, writes `kind =
LIBRARY` with the archive family's declaration header, keeps the old claim in
`binding_history`, and guards apply with the preview digest. Batch conversions
use `change_source_bindings_batch` so one metadata write carries many reviewed
changes. Tests: `tests/test_library_adopt.py`,
`tests/test_source_binding.py::TestBatchBindingChanges`.

Fixed on the development checkout 2026-10-24, not in the 5.4.0 wheel. Run it
through `uv run --project /home/maci/Desktop/Projects/relumea/repos/rebrew`.

## `binary repair-extents --merge` is implemented upstream, unreleased

Inventory splits that cut one routine at an internal branch target are now
reversible with `binary repair-extents --merge 0xHEAD=0xTAIL` (repeatable, in
order for chained arms). The head extent grows to the tail's end, the tail row
is removed with its extent history preserved under the head, and the preview
digest binds the ordered merge list. Tests:
`tests/test_inventory_repair.py` (`TestInventoryMerge`, `TestMergeCli`).

Fixed on the development checkout 2026-10-23, not in the 5.4.0 wheel. Remaining
work in this class: a reviewed bulk manifest (which split arms are real function
starts) and the LIBRARY writer below.

## `data layout fill` writes target pads into the shared server BSS file

`rebrew data layout fill --target Europa1400Gold.exe` reports init/BSS pads and
writes them into `src/bss_layout/bss_late.c`, the static library the server
links after the CRT. Filling a client target therefore edits the server's BSS
layout. Proposed capability: per-target BSS source files, or an
`--output-source` option, and a refusal when a target's pads would land in
another target's file.
