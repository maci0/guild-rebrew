# Reconstruction handoff — 2026-11-05

Release follow-up: the accepted working-tree changes are included in the 1.10.0 source checkpoint. Historical local paths below resolve under the sibling archive directory `../guild-rebrew-archive/2026-11-05/`: `.scratch/` is preserved as `scratch/`, and former `.rebrew/` state is preserved as `rebrew-state/`. This local research archive is not part of the public source release. See [release notes](releases/1.10.0.md) for validation and remaining limits.

The fleet is stopped at the user's request. All 40 retained workers were terminated and archived, another 1,024 historical sessions were archived, and supervision heartbeat `e18752d8` was deleted. No restart or further compiler work is scheduled. Historical closed sessions and native evidence are preserved.

## Working tree and cleanup

All work already shares the current `main` working tree. There is one branch and one worktree, with no separate branch changes to merge. The 125 existing tracked modifications were preserved; nothing was committed, pushed, reset, or discarded. Managed metadata was not repaired or rolled back during cleanup.

Loose untracked files and directories were moved to `.scratch/microfleet/cleanup-2026-11-05/loose/`, preserving their original relative paths. `moves.json` records each relocation. In particular, untracked `src/Develop/DieGildeAddOn/game/GOLDTL.cand1_00558d10.c` is quarantined there rather than adopted or left in build discovery. The archive includes the pre-cleanup tracked patch and status. Existing evidence under `.scratch/` remains in place.

## Recent changes retained in production

These changes have native evidence and recorded changed-TU measurements. The measurements establish compilation and byte verdicts, not semantic proof or the cause of remaining differences. All rows below remain SIZE_MISMATCH.

| Native VA | Retained change | Receipt under `.scratch/microfleet/` | Match / total |
|---|---|---|---|
| 004b4650 | Return 0 for the 25 non-check in-range kinds; keep conditional increment and return 1 for the five check kinds | `worker-02/integrate-004b4650-defaults/receipt.json` | 102 / 112 |
| 00515e10 | Pass the first strstr result as a null-test boolean rather than its pointer value | `worker-01/verify-00515e10-bn/test-after.json` | 27 / 252 |
| 005a6e90 | Correct the early return and forward the normal tail callee's result | `worker-14/integrate-005a6e90-returns/test-after.json` | 28 / 816 |
| 004721e0 | Correct both record byte strides from 108 to 0x3cc | `worker-18/integrate-004721e0-stride/test-after.json` | 7 / 111 |
| 004fb390 | Change the gate to ordered equality, matching TEST AH,0x44 / JP parity | `worker-20/integrate-004fb390-equality/receipt.json` | 21 / 389 |
| 00547770 | Correct command threshold to cnt[5]<1 and reset v inside each iteration | `worker-11/integrate-00547770-integers/test-after.json` | 757 / 5595 |

Earlier accepted changes, including 004f89b0, 00573e10, 004c8de0, 004d1970 and 00524b50, remain in the working tree and append-only provenance ledger. This handoff does not supersede their bounded evidence or claim whole-body byte agreement.

## Unfinished work preserved for review

No unresolved candidate was copied wholesale into production during shutdown.

- **004cdda0:** `buf+4` differs from native `buf`; owner review also found a final a2/a3 destination disagreement. Caller contract remains unresolved. See `worker-09/review-004cdda0-owner/OWNER-REVIEW.md` under `.scratch/microfleet/` and the peer review under `worker-36/review-004cdda0-buffer-peer/`.
- **005cff20:** native holder construction can execute with shown=0 and *a2!=0; the source shown wrapper is suspect. Holder/shadow slots, read-before-write state and tail behavior remain separate HOLDs. See `worker-19/review-005cff20-owner/review.md` and `.scratch/review-005cff20-shown-path/`.
- **00515e10:** the boolean fix is integrated and measured. Copying the terminating NUL and the success-path return reaching definition remain unresolved; do not fold them into an equivalent-expression cleanup.
- **005a6e90:** only the two return hunks were adopted. Larger candidates contain incorrect mode/compare-slot and loop assumptions. Use `worker-14/review-005a6e90-owner/` before further edits.
- **00547770:** integer fixes are integrated; FP threshold and intermediate precision claims remain separate. See `worker-11/review-00547770-integer-owner/` and the earlier FP reviews.
- **00524b50:** header-dependent read sizes were integrated. Global counter/failure-state changes remain held, including transitive mutation questions. See `worker-10/review-00524b50-transitive-state/`.
- **005e5a50:** callee 00533a60 writes two output IDs subsequently consumed by gates; scratch candidates still require whole-body review. See `worker-09/review-005e5a50-533a60-alias/FINAL-review.md`.

Paths beginning `worker-` in this section are relative to `.scratch/microfleet/`. Other historical candidates and reservations remain documented in `current-supervision-facts.json` and worker manifests; their old permissions are superseded by the STOPPED marker and explicit shutdown record.

## Proposals that must not be revived as fixes

Latest independent corrections reject the following earlier claims:

- 00504bd0 category remap: production matches all 256 byte inputs; the alleged differences used byte-1 as byte. See `worker-20/review-00504bd0-categories/`.
- 004fdfe0 substring base+0x14: held pushes resolve the argument to base itself. See `worker-20/withdraw-004fdfe0-substring/`.
- 005b00f0 sign and x/y swaps: the full x87 stack trace agrees with production. See `worker-22/review-005b00f0-x87-peer/`.
- 004fb2c0 long-long return: the shared __ftol helper's EDX:EAX output does not establish the source return width. Keep the existing type pending a caller contract.
- 004b33c0 array-to-scalar: a single in-bounds dword use does not prove a semantic defect or original scalar declaration.
- 005b6300 a24-to-a1c, 00414ab0 ordered min/max swap, 005dc270 argument swap, 0045d0d0 a5/a6 swap, and 004aa0c0 q.c deletion: withdrawn or rejected by corrected frame/flags/CFG evidence. Preserve the current reviewed source.

## Verification limits and metadata provenance

No reconstruction tests were run for shutdown cleanup. Existing source changes are uncommitted and have not received a fresh whole-project verification.

Some earlier sessions exceeded their compiler reservations: owner03 performed redundant variants/reruns, and owner02 produced a redundant `receipt-rerun.json`. These are not additional accepted progress. A reported unlocked alchemistry TU test had no attributable receipt; a test-writer promotion of 004ee790 to RELOC is recorded at 2026-11-05T00:42:36Z, but available evidence cannot attribute it to that session. See `worker-08/review-004ee790-test-impact/review.md`. No speculative metadata rollback was performed.

Any resumed work requires a new explicit request, current source review and canonical identity checks. Preserve C89, whole-TU flags, locked metadata writers and append-only provenance. Compiler/diff work uses `.scratch/microfleet/compiler.lock`; provenance appends use `.scratch/microfleet/provenance.lock`.
