# Unfinished reconstruction reviews

[Current work](TODO.md) owns status and priorities. This page records source
questions that need native review before further edits.

| GoldTL VA | Open question | Evidence under the archived `scratch/microfleet/` |
| --- | --- | --- |
| 0x004cdda0 | Native passes buf rather than buf+4; the final a2/a3 destination and caller contract also need resolution. | `worker-09/review-004cdda0-owner/OWNER-REVIEW.md` |
| 0x005cff20 | Native holder construction can run with shown=0 and *a2!=0. Keep holder/shadow slots, read-before-write state and tail behavior separate. | `worker-19/review-005cff20-owner/review.md` |
| 0x00515e10 | Boolean argument fix is integrated. Terminating-NUL copy and success-path return definition remain open. | `worker-07/review-00515e10-bn-owner/` |
| 0x005a6e90 | Only two return hunks were accepted. Larger candidates have incorrect mode, comparison-slot and loop assumptions. | `worker-14/review-005a6e90-owner/` |
| 0x00547770 | Integer fixes are integrated; FP threshold and intermediate precision remain separate questions. | `worker-11/review-00547770-integer-owner/` |
| 0x00524b50 | Header-dependent read sizes are integrated. Global counter/failure state and transitive mutation remain unresolved. | `worker-10/review-00524b50-transitive-state/` |
| 0x005e5a50 | Callee 0x00533a60 writes two IDs used by later gates. Scratch candidates still need whole-body review. | `worker-09/review-005e5a50-533a60-alias/FINAL-review.md` |

The local archive is `../guild-rebrew-archive/2026-11-05/`; it is not a release
asset. [Provenance](provenance.md) and the [documentation archive](goal-history.md#full-notebooks)
retain earlier decisions and superseded candidates.

## Rejected proposals

Do not revive the 0x00504bd0 category remap, 0x004fdfe0 substring-base offset,
0x005b00f0 sign/x-y swaps, 0x004fb2c0 return-width inference, 0x004b33c0 scalar claim,
0x005b6300 member change, 0x00414ab0 ordered min/max swap, 0x005dc270 argument swap,
0x0045d0d0 argument swap or 0x004aa0c0 store deletion without new evidence.
Their corrected traces are in the archived worker reviews.

One alchemistry TU test-writer promotion has no attributable receipt. The
0x004ee790 native extent agrees with the earlier audit; no speculative metadata
rollback was made. See `worker-08/review-004ee790-test-impact/review.md`.

## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

Original notebook: `docs/HANDOFF.md` in the [documentation archive](goal-history.md#full-notebooks).

| Historical section | Referenced hex values |
| --- | --- |
| <a id="handoff"></a>Handoff | - |
| <a id="resume-2026-11-01--gold-tl-byte-match"></a>Resume (2026-11-01) — Gold TL byte match | - |
| <a id="kept"></a>Kept | `0x00613478`, `0x006ad80c` |
| <a id="restored-this-pass-score-did-not-rise"></a>Restored this pass (score did not rise) | `0x0041b510`, `0x00436a00`, `0x00471e30`, `0x00472680`, `0x004b64b0`, `0x004c6090`, `0x004c6940`, `0x004eea30`, `0x004f2ee0`, `0x00509120`, `0x00536b10`, `0x005473a0`, `0x0057c7b0`, `0x0057de80`, `0x005aceb0` |
| <a id="next"></a><a id="prepared-helper-work"></a>Next | `0x004f88d0`, `0x00613478` |
| <a id="prepared-helper-work-historical-2026-10-19"></a>Prepared helper work (historical, 2026-10-19) | `0x00469890`, `0x0046b520`, `0x0046c9e0`, `0x0046ea00`, `0x0046f650`, `0x004730d0` |

</details>
