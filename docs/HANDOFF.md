# Unfinished reconstruction reviews

[Current work](TODO.md) owns status and priorities. This page indexes archived
source review questions. Recheck current source and native evidence before
treating a question as unresolved.

| GoldTL VA | Review question | Receipt under the archived `scratch/microfleet/` |
| --- | --- | --- |
| 0x004cdda0 | The receipt maps the passed buffer to buf and the final write to arg2. Recheck the caller contract before adoption. | `worker-09/review-004cdda0-owner/OWNER-REVIEW.md` |
| 0x005cff20 | Native holder construction can run with shown=0 and *a2!=0. Keep holder/shadow slots, read-before-write state and tail behavior separate. | `worker-19/review-005cff20-owner/review.md` |
| 0x00515e10 | Check terminating-NUL copy and caller return use. A 2026-11-13 void-return correction is recorded in provenance; recheck that contract before adopting older candidates. | `worker-07/review-00515e10-bn-owner/` |
| 0x005a6e90 | Review mode, comparison-slot and loop assumptions before adopting a candidate. | `worker-14/review-005a6e90-owner/` |
| 0x00547770 | Review FP threshold and intermediate precision separately from integer operations. | `worker-11/review-00547770-integer-owner/` |
| 0x00524b50 | Review global counter/failure state and transitive mutation. | `worker-10/review-00524b50-transitive-state/` |
| 0x005e5a50 | Callee 0x00533a60 writes two IDs used by later gates. Scratch candidates still need whole-body review. | `worker-09/review-005e5a50-533a60-alias/FINAL-review.md` |

Receipt paths are relative to
`../guild-rebrew-archive/2026-11-05/scratch/microfleet/` from the checkout root.
See [local receipts](goal-history.md#local-receipts) for archive access.
[Provenance](provenance.md) retains earlier decisions and superseded candidates.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
