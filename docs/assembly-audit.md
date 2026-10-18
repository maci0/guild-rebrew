# Assembly audit

Assembly is allowed only for evidenced padding or positive evidence that the
original source very likely used it. A byte match, failed C search, blocker or
`REBREW_ALLOW_NAKED` define grants no exception. [AGENTS.md](../AGENTS.md) owns
that rule; metadata owns each definition/target receipt and current byte verdict.
Whole-function assembly verdicts do not count as C recovery.
Reviewed evidence is format-3 `[source.definitions]` / `[source.files]` in
`rebrew-functions.toml`. The separate source store is retired
(`rebrew-source.toml` is absent). Write receipts with
`rebrew source document-assembly`. Do not hand-edit the store.

## Recovery checkpoint

The initial audit found 57 active Gold whole-function naked reconstructions,
all present in that checkpoint's map. They were not padding or native discards.
At Goal110, 16 had become game C, one was corrected to an existing zlib provider,
and 40 remained unsupported. Later recovery work must update metadata, not this
historical denominator. The two live queries are different lists.
`todo --category naked-reconstruction` selects metadata `source = "naked"`.
Lint code E023 is a whole-function `__declspec(naked)` body. An older
goal-history lint total is that checkpoint only.

```sh
uv run rebrew todo --category naked-reconstruction --target Europa1400Gold.exe --json
uv run rebrew lint --all-targets --json
```

| Checkpoint | Recovered entries / correction | Receipt |
| --- | --- | --- |
| Goals86–88 | Six table searches `0x42c200`–`0x42c340`; record update `0x4fe1e0`, tail walk `0x4c0210`, record search `0x4ce130`, count/header readers `0x44f680`/`0x44f860` | `.scratch/goal86-{table-group,packed-store}/`, `goal87-{review,record-review}/`, `goal88-{save-counter,stream-header,stream-apply}/` |
| Goal90 | `0x465c80` is zlib `inflate_trees_fixed`, with the existing vendored provider; not game C credit | `.scratch/goal90-fixed-trees/` |
| Goals91/93 | Sound wrapper/control `0x4c24c0`/`0x4c2480` select shared client C | `.scratch/goal91-sound-wrapper/`, `goal93-shared-sound-control/` |
| Goal98 | Width setter `0x46c250`, native stride and low-word store checked | `.scratch/goal98-gui-width/` |
| Goal105 | Color initializer `0x45dad0`, 53 complete applied bytes | `.scratch/goal105-color-init/` |
| Goal110 | Getter `0x4364f0`, RELOC25/25 with DIR32 validated; Gold relinked | `.scratch/goal110-full-runs/getter-official.json` |

These replace already-accounted assembly; they add no accounted text. Complete
object/operand comparisons and rejecting controls support the recoveries, but
client native placement and whole-file identity remain unverified.

Additional C recovery outside the initial 57 includes Gold `0x5a89a0`: lookup
before wrapper in the shared TU preserves the native register assignment.
Standalone and callee-last controls fail. See `.scratch/goal89-tu-wrapper/`.
Fourteen empty guarded TL naked templates contained no reconstructed instructions.
Goal111 replaces that undefined fallthrough with ordinary comparison-only
`return 0` stubs; all 14 compile without C4716 but remain unmatched ABI/provider
work. No unique D3DX8/CRT archive member was established and no recovery credit
is earned. Receipt: `.scratch/goal111-empty-templates/result.json`.

## What qualifies

Padding must be alignment bytes at the actual site, separate from reachable
code. Scheduling NOPs inserted to steer the compiler do not qualify. None of
the initial 57 whole-function dumps was padding-only.

Native INT3 assertion branches are strong evidence for a VC6 assembly statement.
The repeated 26-byte fill/copy family instead carries a **likelihood inference**
from register invariance across native contexts and operand homing, including
spills/reloads of literal counts. Stock-library exclusions, byte matches and
failed searches corroborate those observations; they do not prove impossibility
in C, authorship or an original macro name.

Goal108 rechecked the existing definition hashes, both clients' 60-core registries
and the literal-count spill/reload in both building-table functions. Every tested
core rejected a one-byte site slide. The review corrected overstrong wording and
added target-scoped INT3/SaveBMP24/helper receipts. It ended with 58 receipts and
215 distinct fill/copy sites. Goal110 separately checked TL `0x4023b2` and added
that target's helper receipt, bringing the checkpoint to 59 receipts. A local
parameter rename preserved both target objects and refreshed Gold's receipt.

Receipts: `.scratch/goal108-assembly-provenance/` and
`.scratch/goal110-full-runs/hosts-native-tl.json`. Supporting analysis is in
[allocator findings](msvc6-allocator.md#the-prelude-is-hand-written-asm-not-a-compiler-expansion-2026-09-04)
and [walls §6b](codegen-walls.md#6b-the-inline-asm-zero-fillmemcpy-prelude-measured-cost-of-the-constraint).
No whole-function naked reconstruction receives a blanket exception.

A current source hash does not independently reprove every sentence in a receipt.
Evidence for Gold does not exempt TL. Recheck each target after source changes;
use `rebrew source document-assembly` for reviewed provenance.

## Compilation and retention

The comparison clients use `/OPT:NOREF` while WinMain is a stub. It retains
contributions from selected objects, not omitted TUs or every archive member.
Original Gold used `/OPT:REF`; compiled COMDATs could be discarded. Distinguish
compilation, selected link inputs, archive extraction and retained contributions.
A gap alone establishes none of them and supplies no permission to insert bytes.

Discarded code can still affect archive selection, import order or relocation
reservation. Establish that history with source strings, object/link evidence
and controlled links. Comparison omit lists and retired CRT files are current
build choices, not evidence of original linker discards. Reused Goal83 build
folders are not frozen historical baselines.

## Goal88 remaining-list snapshot

The former 46-row table, including subsequently recovered entries, is preserved
in the [October 18 archive](goal-history.md#full-notebooks). Use the live metadata
query above instead of duplicating it here.

## Replays and limits

The `0x575900` switch exposed a separate extent error: an old EXACT compared only
48 prefix bytes. Native cases and the nine-entry table occupy 196 bytes, followed
by 12 alignment NOPs. The old object measures 48/196; its assembly remains a work
item. `lua_version` at `0x575930` was an internal case block, not an established
library provider. Receipt: `.scratch/goal87-switch-review/`.

Initial inventory and independent reviews:
`.scratch/goal85-asm-audit/{inventory.json,inline-review.md,link-review.md}`.
The client builds remain comparison scaffolds; full C recovery, original discards
and gameplay are not validated by this audit.
