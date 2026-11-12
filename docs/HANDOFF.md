# Unfinished reconstruction reviews

[Current work](TODO.md) owns status and priorities. This page indexes archived
source review questions. Recheck current source and native evidence before
treating a question as unresolved.

| GoldTL VA | Review question | Receipt under the archived `scratch/microfleet/` |
| --- | --- | --- |
| 0x004cdda0 | The receipt maps the passed buffer to buf and the final write to arg2. Recheck the caller contract before adoption. | `worker-09/review-004cdda0-owner/OWNER-REVIEW.md` |
| 0x005cff20 | Native holder construction can run with shown=0 and *a2!=0. Keep holder/shadow slots, read-before-write state and tail behavior separate. | `worker-19/review-005cff20-owner/review.md` |
| 0x00515e10 | Check terminating-NUL copy and success-path return definition. | `worker-07/review-00515e10-bn-owner/` |
| 0x005a6e90 | Review mode, comparison-slot and loop assumptions before adopting a candidate. | `worker-14/review-005a6e90-owner/` |
| 0x00547770 | Review FP threshold and intermediate precision separately from integer operations. | `worker-11/review-00547770-integer-owner/` |
| 0x00524b50 | Review global counter/failure state and transitive mutation. | `worker-10/review-00524b50-transitive-state/` |
| 0x005e5a50 | Callee 0x00533a60 writes two IDs used by later gates. Scratch candidates still need whole-body review. | `worker-09/review-005e5a50-533a60-alias/FINAL-review.md` |

Resolve these paths through [local receipts](goal-history.md#local-receipts).
[Provenance](provenance.md) retains earlier decisions and superseded candidates.

## Archived techniques

Original notebook: `docs/HANDOFF.md` in the [documentation archive](goal-history.md#full-notebooks).

- Handoff
- Resume (2026-11-01): Gold TL byte match
- Kept (`0x00613478`, `0x006ad80c`)
- Restored this pass (score did not rise) (`0x0041b510`, `0x00436a00`, `0x00471e30`, `0x00472680`, `0x004b64b0`, `0x004c6090`, `0x004c6940`, `0x004eea30`, `0x004f2ee0`, `0x00509120`, `0x00536b10`, `0x005473a0`, `0x0057c7b0`, `0x0057de80`, `0x005aceb0`)
- Next (`0x004f88d0`, `0x00613478`)
- Prepared helper work (historical, 2026-10-19) (`0x00469890`, `0x0046b520`, `0x0046c9e0`, `0x0046ea00`, `0x0046f650`, `0x004730d0`)
