# Rebrew tooling fixes and remaining gaps

Guild installs released Rebrew 6.9.0. Reusable repairs belong in the
[upstream checkout](https://github.com/maci0/rebrew), with regression tests;
native evidence stays here. A development checkout is an explicit tooling
opt-in, not a requirement for ordinary builds.

## Current unreleased repairs (2026-10-31)

- Library batch matching uses complete native extents instead of prefix retry.
  The replay's candidates still need operand, literal and provider review.
- Lint skips empty historical binding paths without weakening nonempty-history
  validation. The measured profile is in [current work](TODO.md).
- Stub generation preserves bare pointer-return declarations and refuses
  ambiguous conditional callable aliases unless an ABI-reviewed special exists.
- Single-function `test` honors explicit `--symbol` over the selected VA's symbol
  and supplied raw `--target-bin` bytes over the configured binary. Installed
  6.9.0 can silently ignore those overrides, so its corresponding wrong-window
  controls are invalid. The repaired development CLI rejects all four native
  controls; diagnostic overrides do not promote metadata.
- Source binding recognizes complete K&R bodies behind a conservative local
  storage macro, without changing assembly-provenance hashes or weakening
  duplicate-provider checks. This unblocks inspection of vendored minizip;
  it does not select that library as the native provider.
- Binding updates prepare once inside the writer lock. Renames without relevant
  provenance skip a second round-trip parse of the large function store;
  input, digest and concurrent-change checks remain.
- Library batch screening now reports unchecked functions and fails closed when
  an extent or native bytes are unavailable. The repaired D3DX screen has 28
  candidates and two unchecked entries, so the server gate is still open.
- Library adoption records a missing inventory size atomically with the source
  claim, including retired rows. It refuses conflicting positive sizes and
  detects inventory changes after review, including absent-to-present changes.
  This repairs the staged `fseek` restoration; strict callee proof is separate.

The latest upstream suite passes 13,436 tests, with 28 skipped. The private
v6.9.0 matcher/adoption port passes 13,350 tests, with 41 skipped. The separate
naming port's three binding/provenance repairs pass 13,359 tests, with 29 skipped.
That naming port was explicitly used for reviewed naming writes; ordinary Guild
commands still run released 6.9.0. Receipts:
`/tmp/rebrew-final-verification.txt`,
`.scratch/terra-goal-20261031/upstream-symbol-override/` and
`.scratch/naming-20261031-69/`, plus
`.scratch/goal-next-20261031/gate-screen/`. No new release is claimed.

### Mixed-context lookup rename

Gold and TL each have two distinct entity lookup tables. A source name is reused
across them, and a shared TU also contains unrelated server references. The
file-wide `source rename --reference-owner` option cannot safely express every
mixed context. Leaving a file untouched can also change its resolved callee
after other definitions are renamed, so bypassing the guard is insufficient.
The retained TL support helper's two current small-table calls need explicit
preservation even though its native identity is unresolved.

The upstream repair adds reviewed preserved-reference files and prospective
owners for retired identities. Neither option proves a native callee or activates
a provider. Guarded previews pin the source, metadata and target inputs; a
prospective owner must be rebound and verified before linking. Explicit
shared-definition renames now support the same digest guard without requiring
an ownership override. Conflicting selections and changed inputs still refuse.

The complete three-stage Guild rename passed an isolated replay before its
production application. The final upstream suite passes 13,447 tests (28 skipped);
the private v6.9.0 port passes 13,362 (40 skipped), with its absolute import path
recorded. Ruff and mypy pass. These fixes are not installed or released;
ordinary native builds still use Guild's released environment.
Caller evidence is in `.scratch/goal-next-20261031/gold-lookup-callers/`;
guarded previews, source comparisons and test logs are in
`.scratch/goal-lookup-split-20261031/`. The upstream gap and resolution remain
recorded in `docs/IDEAS-GUILD.md`. No native owner was invented for the support
helper.

The following sections retain the older issue anchors for existing links.
Their release state is corrected below; they are not all outstanding work.

<a id="source-import-related-conditional-definition-is-fixed-upstream-unreleased"></a>

## Conditional source imports (released)

A shared source file that defines a function inside a target `#if` block made
the copy path raise `ValueError` and abort the whole batch, even with
`--dry-run`. The per-candidate call now catches that error, records an `error`
row naming the candidate, and continues. Regression test:
`tests/test_cross_import.py::TestCLI::test_conditional_donor_reports_row_and_continues`.
The October 23 repair is present in installed 6.9.0; the old 5.4.0 limitation
is historical.

<a id="library-over-function-writer-is-implemented-upstream-unreleased"></a>

## Library adoption (released)

`rebrew library adopt` records a unique stock-archive match over an existing
FUNCTION or STUB row: it re-runs the project archive match, requires one unique
symbol/member candidate, refuses vendored-object matches, writes `kind = LIBRARY` with the archive family's declaration header, keeps the old claim in
`binding_history`, and guards apply with the preview digest. Batch conversions
use `change_source_bindings_batch` so one metadata write carries many reviewed
changes. Tests: `tests/test_library_adopt.py`,
`tests/test_source_binding.py::TestBatchBindingChanges`.

The adoption command is present in installed 6.9.0. Preview with
`uv run rebrew library adopt 0xVA --dry-run --json`; the current help defines
its evidence and digest requirements.

<a id="binary-repair-extents---merge-is-implemented-upstream-unreleased"></a>

## Inventory merges (released)

Inventory splits that cut one routine at an internal branch target are now
reversible with `binary repair-extents --merge 0xHEAD=0xTAIL` (repeatable, in
order for chained arms). The head extent grows to the tail's end, the tail row
is removed with its extent history preserved under the head, and the preview
digest binds the ordered merge list. Tests:
`tests/test_inventory_repair.py` (`TestInventoryMerge`, `TestMergeCli`).

The merge option is present in installed 6.9.0. Each repair still requires
reviewed native boundaries; the command does not decide whether an internal
branch target is a function entry.

## `data layout fill` writes target pads into the shared server BSS file

The earlier `rebrew data layout fill --target Europa1400Gold.exe` audit found
client pads written into `src/bss_layout/bss_late.c`, which the server links
after the CRT. That audit is not permission to emit new client storage. Current
6.9.0 help still offers no `--output-source`; the cross-target write behavior
was not retested in this documentation pass. The proposed repair is target-owned
output files and refusal to write a target's pads into another target's source.
