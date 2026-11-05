# Current work

## Verified checkpoint, 2026-11-05

[Release 1.10.0](releases/1.10.0.md) records the latest validation. Its server build
matches the complete 286,720-byte reference: 316 function checks, 652 data checks,
structural checks and Wine load/export resolution passed.

The full gate still fails on five lint warnings and 28 GoldTL D3DX library-screening
findings. Both clients remain incomplete. The release compiled all 123 changed C
translation units, but did not establish a new complete client image or gameplay
result. Older client link counts and image scores are historical.

Build trees and caches were cleared after validation. Local receipts and preserved
images are outside the checkout at `../guild-rebrew-archive/2026-11-05/`. Historical
`.scratch/` paths resolve under that archive's `scratch/` directory. Rebuild before
claiming a current image result. [Build instructions](build.md) and
[client instructions](../stubs/README.md) describe how.

## Next actions

1. Review the five lint warnings: three STUB rows lack blocker explanations,
   `amt.office_slot:SERVER` has stale type evidence, and generated instructions
   differ from the installed template. Rebind or refresh only after review.
2. Resolve the 28 D3DX screening findings with complete native/operand/provider
   evidence. Do not count library bodies as game recovery or suppress the gate.
3. Resume the bounded source questions in the [reconstruction handoff](HANDOFF.md):
   004cdda0 argument/base selection, 005cff20 holder gating, 00515e10 terminator and
   return flow, 005a6e90 frame slots, 00547770 FP threshold, 00524b50 failure state,
   and 005e5a50 callee output use. Recheck current source before adopting a candidate.
4. Rebuild each client and record fresh link, placement, data and whole-file checks.
   Repair actual provider/ownership failures before interpreting layout scores.
5. Recover remaining C bodies and reconcile shared declarations/types across all
   targets. Preserve the server after each shared change.

No subagent fleet, heartbeat or background reconstruction job remains active.
The prior reservations and permissions are closed.

## Choose work from canonical inputs

```sh
uv run rebrew todo --target Europa1400Gold_TL.exe --json
uv run rebrew source findings 0x<VA> --json
uv run rebrew lint --all-targets --json
```

[goal.md](../goal.md) defines completion. [AGENTS.md](../AGENTS.md) owns project
rules. [Goal history](goal-history.md) locates older checkpoints and notebooks.

## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

The [November 5 archive](archive/2026-11-05-documentation.tar.xz) preserves the full
`docs/TODO.md` notebook, including corrections and receipt paths. Entries below locate
historical claims, not current instructions or verdicts. Hex values include
code/data addresses and constants.

```sh
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/TODO.md | less
```

| Historical section | Referenced hex values |
| --- | --- |
| Current work | - |
| <a id="working-checkpoint-update-2026-11-01-1515-utc"></a>Working checkpoint update (2026-11-01 15:15 UTC) | `0x50E170` |
| <a id="working-checkpoint-2026-11-01"></a>Working checkpoint (2026-11-01) | - |
| <a id="source-and-provider-changes"></a>Source and provider changes | `0x402b80`, `0x40ed40`, `0x40f1c0`, `0x40fb80`, `0x4124b0`, `0x4127a0`, `0x4131e0`, `0x413d10`, `0x41b510`, `0x420bf0`, `0x420d20`, `0x420db0`, `0x427280`, `0x436a00`, `0x437bc0`, `0x440670`, `0x441400`, `0x445ec0`, `0x44c6f0`, `0x44d7e0`, `0x450e90`, `0x45bfb0`, `0x465c60`, `0x471e30`, `0x472680`, `0x473610`, `0x4763e0`, `0x479660`, `0x47c1f0`, `0x48ddd0`, `0x48eba0`, `0x48f4f0`, `0x4903c0`, `0x490c10`, `0x491570`, `0x491680`, `0x4918a0`, `0x493be0`, `0x495180`, `0x499950`, `0x49a880`, `0x4a0bb0`, `0x4a70c0`, `0x4b64b0`, `0x4c3800`, `0x4c39c0`, `0x4c6090`, `0x4c6940`, `0x4c6e20`, `0x4c75f0`, `0x4c7c50`, `0x4cd090`, `0x4ce210`, `0x4d3c60`, `0x4dc3a0`, `0x4e3020`, `0x4e7340`, `0x4ea350`, `0x4ee290`, `0x4eea30`, `0x4f0a30`, `0x4f2ee0`, `0x4f4440`, `0x4f88d0`, `0x502450`, `0x5024e0`, `0x503e80`, `0x506ab0`, `0x507130`, `0x509120`, `0x509570`, `0x50b840`, `0x50dfd0`, `0x50e170`, `0x513d40`, `0x524fc0`, `0x536b10`, `0x53fa80`, `0x5435e0`, `0x5448e0`, `0x545780`, `0x5473a0`, `0x55a0b0`, `0x565ab0`, `0x571140`, `0x57a3d0`, `0x57c7b0`, `0x57d0d0`, `0x57de80`, `0x57e880`, `0x57f9a0`, `0x580e20`, `0x5816f0`, `0x589d00`, `0x58bfd0`, `0x58e220`, `0x593360`, `0x59dcf0`, `0x5aa480`, `0x5aceb0`, `0x5b44b0`, `0x5bf9e0`, `0x5ce800`, `0x5de9a0`, `0x5e53b0`, `0x5e6840`, `0x605233`, `0x613478`, `0x67bbdc`, `0x67bbe0`, `0x68bfb8`, `0x6b5c84`, `0x77492c`, `0x1007ce0` |
| <a id="tooling-and-validation"></a>Tooling and validation | `0x4bd1e0`, `0x57a3d0`, `0x605233`, `0x64d399` |
| Next actions | `0x420db0`, `0x48ddd0`, `0x4903c0`, `0x495180`, `0x4cd090`, `0x5024e0`, `0x57a3d0`, `0x593360`, `0x5e53b0` |
| <a id="historical-work-records"></a><a id="status-snapshot-2026-10-21-1202-utc"></a>Historical work records | - |
| <a id="status-snapshot-2026-10-24-session-round-7"></a>Status snapshot (2026-10-24 session round 7) | `0x414fb0`, `0x41bb70`, `0x41ebca`, `0x00479330`, `0x47a320`, `0x4bfe00`, `0x4c9e20`, `0x4f0f60`, `0x4f18d0`, `0x50e170`, `0x5294c4`, `0x52f7b0`, `0x532ef0`, `0x005d3d90`, `0x5d6c50`, `0x5d6ea0`, `0x60ff98`, `0x62a1ee`, `0x64d228`, `0x64d3f8`, `0x64d41a`, `0x650000`, `0x660075` |
| <a id="status-snapshot-2026-10-24-session-round-6"></a><a id="live-state-2026-10-22-round-107"></a>Status snapshot (2026-10-24 session round 6) | `0x40d9a0`, `0x00479330`, `0x4bfe00`, `0x4f0f60`, `0x52f7b0`, `0x532ef0`, `0x64d228`, `0x64d3f8`, `0x64d41a` |
| <a id="historical-state-2026-10-22-round-107"></a>Historical state (2026-10-22, round 107) | `0x004012b0`, `0x00401380`, `0x00402540`, `0x00402ab0`, `0x402d00`, `0x00403ab0`, `0x403ab0`, `0x404c20`, `0x405610`, `0x00406560`, `0x407390`, `0x004076b0`, `0x4076b0`, `0x408320`, `0x0040cda0`, `0x0040d8d0`, `0x0040eac0`, `0x40ed40`, `0x40f9d0`, `0x40fb80`, `0x00411b00`, `0x00411c10`, `0x412b10`, `0x412f10`, `0x00413030`, `0x413480`, `0x413e00`, `0x00415150`, `0x415510`, `0x00417710`, `0x00417840`, `0x00418e90`, `0x418e90`, `0x0041a25c`, `0x0041a8c3`, `0x41a8d0`, `0x0041e050`, `0x41e050`, `0x0041e0a0`, `0x41e0a0`, `0x0041e670`, `0x0041ebca`, `0x004207c0`, `0x00423670`, `0x004284d0`, `0x00429670`, `0x00429e90`, `0x0042ada0`, `0x0042b410`, `0x0042bd30`, `0x42bd30`, `0x42bd5f`, `0x0042bd60`, `0x42bd60`, `0x42bd8f`, `0x0042ee50`, `0x0042f620`, `0x00435810`, `0x00435870`, `0x00436070`, `0x436070`, `0x00437060`, `0x43a720`, `0x0043b600`, `0x0043b6e0`, `0x0043bb70`, `0x0043d7c0`, `0x0043deb0`, `0x0043e090`, `0x0043e180`, `0x43e1b0`, `0x00440280`, `0x440280`, `0x00441ab0`, `0x00441ea0`, `0x00442210`, `0x4488e0`, `0x00449630`, `0x449630`, `0x0044964d`, `0x44964d`, `0x44b340`, `0x0044f010`, `0x0044f760`, `0x44f760`, `0x0044f7e0`, `0x004506e0`, `0x454460`, `0x004556d0`, `0x455d30`, `0x45c380`, `0x45c554`, `0x0045cd50`, `0x0045f640`, `0x0045fb40`, `0x0045fd70`, `0x00461690`, `0x4616c0`, `0x00463740`, `0x465e60`, `0x4675e0`, `0x00467790`, `0x00468c60`, `0x0046cfc0`, `0x0046e980`, `0x004734c0`, `0x00473610`, `0x00474e5d`, `0x00475840`, `0x00476ef0`, `0x00478bc0`, `0x0047c3c0`, `0x0047cda0`, `0x47ce20`, `0x0047ce50`, `0x00490b80`, `0x494740`, `0x00496060`, `0x496480`, `0x0049ab50`, `0x49ab50`, `0x0049b110`, `0x0049ee20`, `0x0049f5c0`, `0x0049fb80`, `0x4a0bb0`, `0x004a16f0`, `0x004a5340`, `0x004a8f20`, `0x004ab2c0`, `0x4ab2c0`, `0x004ab3e0`, `0x4ab3e0`, `0x004ad0a0`, `0x004ad1c0`, `0x4b64b0`, `0x004bc640`, `0x004bcc20`, `0x004c3800`, `0x4c3800`, `0x004c38eb`, `0x004c4268`, `0x004c70fa`, `0x4cb5d0`, `0x004ccf10`, `0x004cd4c0`, `0x004cd5e0`, `0x4cd5e0`, `0x4cda90`, `0x4cdb10`, `0x4cdb90`, `0x004ce040`, `0x004ce200`, `0x004cf000`, `0x4d0963`, `0x4d099d`, `0x004d16da`, `0x004d7000`, `0x4d7f70`, `0x4d8e20`, `0x4dada0`, `0x4dae90`, `0x004e5770`, `0x4e5770`, `0x004e6d80`, `0x004e6e20`, `0x004eaea0`, `0x004eb180`, `0x004ece60`, `0x004f0430`, `0x4f0f60`, `0x004f2540`, `0x004f3700`, `0x4f3780`, `0x4f8730`, `0x4f8800`, `0x4f9300`, `0x004fdcf0`, `0x00501190`, `0x501190`, `0x509570`, `0x0050c550`, `0x0050f910`, `0x510b40`, `0x00511630`, `0x005117c0`, `0x51463d`, `0x00519a30`, `0x0051c8a0`, `0x00520f50`, `0x00526660`, `0x0052668b`, `0x00526b37`, `0x005283d0`, `0x0052d970`, `0x0052e080`, `0x0052f2f0`, `0x0052fb00`, `0x00536b8e`, `0x00537e40`, `0x00537fe0`, `0x538060`, `0x0053db90`, `0x00541240`, `0x5435d0`, `0x0054f3b0`, `0x54fd0a`, `0x55c700`, `0x570960`, `0x570ad7`, `0x570def`, `0x570e5b`, `0x570e8b`, `0x570ebb`, `0x570eeb`, `0x570f75`, `0x571020`, `0x00577e50`, `0x00577f90`, `0x00578440`, `0x00578760`, `0x00580420`, `0x00580d50`, `0x00582490`, `0x005847e0`, `0x0058ac10`, `0x0058f6a0`, `0x58f6a0`, `0x0058fa20`, `0x005975e0`, `0x005a4060`, `0x005a6e90`, `0x5a6e90`, `0x005a8a90`, `0x005a8e50`, `0x005b104c`, `0x005b22d0`, `0x005b46e0`, `0x5bc820`, `0x005bd2e0`, `0x005bd340`, `0x005be320`, `0x5c86b0`, `0x6310e4`, `0x6f25b8`, `0x770b80`, `0x774970`, `0x7f4ca0`, `0xb83654`, `0x00f83654`, `0x100184ff`, `0x10018506`, `0x10031484`, `0x100314bb` |
| <a id="delegated-reconstruction-waves-2026-10-19"></a>Delegated reconstruction waves, 2026-10-19 | `0x0042f4d0`, `0x445760`, `0x45a3a0`, `0x45a7f9`, `0x4aa240`, `0x4d1ad0`, `0x004e8c00`, `0x512b40`, `0x524fc0`, `0x5252d0`, `0x5294c4`, `0x546720`, `0x5e0000`, `0x64ffff` |
| <a id="paused-checkpoint-2026-10-19"></a><a id="current-integration"></a>Paused checkpoint, 2026-10-19 | - |
| <a id="historical-integration"></a>Historical integration | `0x40cfb0`, `0x418030`, `0x4195f0`, `0x423a50`, `0x424720`, `0x46b2b0`, `0x46e700`, `0x46fac0`, `0x472380`, `0x473640`, `0x475be0`, `0x475ca0`, `0x4790d0`, `0x4c6a50`, `0x4c6a60`, `0x4cfe70`, `0x4d0ec0`, `0x4d6170`, `0x4eabe0`, `0x4ec960`, `0x551010`, `0x552730`, `0x55a820`, `0x55af10`, `0x586bd0`, `0x5bcb10` |
| <a id="goldtl-data-audit-2026-10-19"></a>GoldTL data audit, 2026-10-19 | - |
| <a id="verified-checkpoint"></a>Verified checkpoint | `0x4364f0` |
| <a id="next-actions-1"></a>Next actions | - |
| <a id="commands"></a><a id="current-state"></a>Commands | - |
| <a id="historical-state"></a>Historical state | - |
| <a id="evidence-and-handoff"></a>Evidence and handoff | - |
| <a id="pending-metadata-write-retire-split-artifact-row-0x0041ebca"></a>Pending metadata write: retire split-artifact row 0x0041ebca | `0x41e680` |
| <a id="whole-binary-checkpoint-round-8"></a>Whole-binary checkpoint (round 8) | - |
| <a id="matching-lever-g5-and-g6-for-msvc-scheduler-tie-breaks"></a>Matching lever: /G5 and /G6 for MSVC scheduler tie-breaks | `0x490c10`, `0x615e12`, `0x62ade8` |
| <a id="do-not-run-test---all-while-teammates-are-editing"></a>Do not run `test --all` while teammates are editing | - |
| <a id="per-row-cflags-clearing-needs-remove_field-and-a-cli-gap"></a>Per-row cflags: clearing needs remove_field, and a CLI gap | - |
| <a id="per-row-cflags-and-multi-function-translation-units"></a>Per-row CFLAGS and multi-function translation units | - |
| <a id="tl-link-blocker-d3d8lib-direct3dcreate8-import"></a>TL link blocker: `d3d8.lib` (Direct3DCreate8 import) | - |
| <a id="tl-link-scaffolds-comparison-build-only"></a>TL link scaffolds (comparison build only) | `0x5e0000`, `0x64ffff` |
| <a id="tl-stub-floor-five-size-exact-codegen-walls"></a>TL STUB floor: five size-exact codegen walls | `0x404dc0`, `0x4c9e20`, `0x558220`, `0x57d0d0`, `0x5a0ad0`, `0x7f4ca4`, `0x7f4e24` |
| <a id="round-18-block-layout-wall-probed-further"></a>Round 18: block-layout wall probed further | `0x4c9e20`, `0x4c9e8e`, `0x4c9ed7` |
| <a id="tl-stub-bodies-zero"></a>TL stub bodies: zero | `0x5eb108`, `0x62ce8f` |
| <a id="tl-link-convergence"></a>TL link convergence | - |
| <a id="tl-comparison-image-links-round-20"></a>TL comparison image links (round 20) | - |
| <a id="round-21-import-table-parity"></a>Round 21: import-table parity | - |
| <a id="round-22-the-two-added-imports-are-a-library-version-mismatch"></a>Round 22: the two added imports are a library-version mismatch | `0x5e0000`, `0x64ffff` |
| <a id="round-24-scan-integrity-cleanup-for-retired-and-library-converted-rows"></a>Round 24: scan-integrity cleanup for retired and library-converted rows | - |
| <a id="round-24-no_source-decomposed-from-the-status-code-path"></a>Round 24: NO_SOURCE decomposed from the status code path | `0x650000` |
| <a id="round-24-band-range-is-an-approximation-per-row-library-identity-is-the-truth"></a>Round 24: band range is an approximation, per-row library identity is the truth | `0x5e0000`, `0x5e5a50`, `0x5e5ea0`, `0x5e9da0`, `0x5eaad0`, `0x64ffff` |
| <a id="round-24-two-data-losses-repaired-one-still-open"></a>Round 24: two data losses repaired, one still open | - |
| <a id="round-25-no_source-258---50-stub-2-justified"></a>Round 25: NO_SOURCE 258 -> 50, STUB 2 justified | `0x5e0090`, `0x5e0140`, `0x5e7e30`, `0x654e25` |
| <a id="round-25-0x5e0090-is-game-code-not-band-library"></a>Round 25: 0x5e0090 is game code, not band library | `0x5e0000`, `0x5e0090`, `0x64ffff`, `0x65f220` |
| <a id="round-26-full-d3dx8-member-inclusion-is-not-viable-with-this-archive"></a>Round 26: full D3DX8 member inclusion is not viable with this archive | - |
| <a id="round-26-backend-split-for-this-sandbox"></a>Round 26: backend split for this sandbox | - |
| <a id="round-27-quick-win-wave-started"></a>Round 27: quick-win wave started | `0x004042b0`, `0x00418b40`, `0x00469890`, `0x00473610`, `0x0047d240`, `0x004cffe0`, `0x0050be50`, `0x0051e070` |
| <a id="round-27-wave-composition-and-the-postlink-question"></a>Round 27: wave composition and the postlink question | - |
| <a id="round-28-library-pull-in-experiment-reverted-deliverable-restored"></a>Round 28: library pull-in experiment reverted, deliverable restored | - |
| <a id="round-29-derived-spans-for-zero-size-library-rows"></a>Round 29: derived spans for zero-SIZE library rows | - |
| <a id="round-30-d3dx8-member-inclusion-solved-text-gap-268-kb---32-kb"></a>Round 30: D3DX8 member inclusion solved, .text gap 268 KB -> 32 KB | - |
| <a id="round-31-data-virtual-size-back-to-reference-member-list-persisted"></a>Round 31: .data virtual size back to reference, member list persisted | - |
| <a id="round-32-member-filter-settled-header-layout-blocker-found"></a>Round 32: member filter settled, header-layout blocker found | - |
| <a id="round-33-d3dx8-provider-hunt"></a>Round 33: D3DX8 provider hunt | - |
| <a id="round-34-matching-d3dx8-provider-found-header-layout-fixed"></a>Round 34: matching D3DX8 provider found, header layout fixed | - |
| <a id="round-35-sdk81-archive-wired-member-set-still-approximate"></a>Round 35: SDK8.1 archive wired, member set still approximate | - |
| <a id="round-36-d3dx8-provider-cannot-be-identified-byte-identity-blocked"></a>Round 36: D3DX8 provider cannot be identified; byte identity blocked | `0x5e6d72` |
| <a id="round-37-provider-confirmed-in-toolchain-images-member-set-re-derived"></a>Round 37: provider confirmed in toolchain images, member set re-derived | - |
| <a id="round-38-no_function-driven-down-remaining-bytes-need-completed-bodies"></a>Round 38: NO_FUNCTION driven down, remaining bytes need completed bodies | - |
| <a id="round-38b-near-match-batches-running-no_function-accounting-settled"></a>Round 38b: near-match batches running, NO_FUNCTION accounting settled | `0x41b820`, `0x465840`, `0x4c70fa`, `0x550770` |
| <a id="round-39-no_function-accounting-fix-upstream-two-agents-on-the-remainder"></a>Round 39: NO_FUNCTION accounting fix upstream, two agents on the remainder | `0x4f1860` |
| <a id="round-40-no_function-reached-zero-no_source-is-the-remaining-counter"></a>Round 40: NO_FUNCTION reached zero; NO_SOURCE is the remaining counter | - |
| <a id="round-41-no_function-0-and-no_source-0-measured"></a>Round 41: NO_FUNCTION 0 and NO_SOURCE 0 measured | `0x4f1840`, `0x4f1850`, `0x4f1860`, `0x650000`, `0x660ace` |
| <a id="round-42-zero-counters-hold-proven-restored-data-owner-added"></a>Round 42: zero counters hold; PROVEN restored; data owner added | `0x404dc0`, `0x41adc0`, `0x4c9e20`, `0x558220`, `0x57d0d0`, `0x5a0ad0`, `0x675318` |
| <a id="round-43-ga-finds-no-source-expressible-lever-ga-pragma-anchor-bug-fixed"></a>Round 43: GA finds no source-expressible lever; GA pragma anchor bug fixed | `0x473610`, `0x490c10`, `0x4b64b0`, `0x4c3800`, `0x4c6e20`, `0x50b840`, `0x536b10` |
| <a id="round-44-new-lanes-dispatched-tiny-band-functions-closest-near-import-split"></a>Round 44: new lanes dispatched (tiny band functions, closest NEAR, import split) | `0x40fb80`, `0x47c1f0`, `0x495180`, `0x4ce210`, `0x5eaad0`, `0x5eb307`, `0x5ec8bf`, `0x5edcfa`, `0x5ef2e0`, `0x5f022d`, `0x5f0e27`, `0x6052b9`, `0x60ffc0` |
| <a id="round-45-no_function-0-under-the-pinned-cli-ten-parallel-reconstruction-agents"></a>Round 45: NO_FUNCTION 0 under the pinned CLI, ten parallel reconstruction agents | `0x444ff0`, `0x5f0e46` |
| <a id="round-49-counters-reconciled-after-the-boundary-merges"></a>Round 49: counters reconciled after the boundary merges | - |
| <a id="gap-to-byte-identity"></a>Gap to byte identity | `0x261000`, `0x26D000`, `0x5E0000`, `0x66FFFF` |

</details>
