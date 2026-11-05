# Workflow checks

[AGENTS.md](../AGENTS.md) owns project rules. This checklist covers mistakes that
repeatedly invalidated otherwise plausible work.

## Before editing

- Read the source, current binding and address-keyed findings before starting a
  new probe. Resolve the exact target/VA rather than borrowing a similar name.
- Establish exclusive file/definition ownership for parallel work. Review shared
  callers, types, storage and build contexts before assigning separate edits.
- Check the library provider and complete native extent before treating a row as
  missing game code. A signature miss is inconclusive.
- Use the installed CLI and public APIs before writing a duplicate helper.

## During a probe

Keep the baseline and each candidate receipt separate. Record failed commands;
a later successful run does not make the first one pass. Check actual exit codes
and full diagnostics instead of counting familiar error strings.

Observe the live process handle when waiting. A missing notification, old lock file
or opaque error is not proof that work stopped. Do not launch duplicate workers
or compiler jobs to work around an unverified wait.

## Before accepting a change

Inspect every affected target and caller, generated build inputs and linker
anchors. A source rename can leave stale build state or explicit retention symbols.
Review managed-store changes through their owning writers; read-only file mode is
intentional, not permission to bypass locks.

Rebuild the artifact that decides the claim. Check its freshness and full length.
A green object score does not clear link, data, load or source-fidelity failures.
[Measurement](measure-traps.md) owns those distinctions.

## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

Original notebook: `docs/workflow-traps.md` in the [documentation archive](goal-history.md#full-notebooks).

| Historical section | Referenced hex values |
| --- | --- |
| <a id="workflow-traps"></a>Workflow traps | - |
| <a id="index"></a>Index | - |
| <a id="1-agent-concurrency"></a>1. Agent concurrency | - |
| <a id="2-scope-constraints-that-closed-options"></a>2. Scope constraints that closed options | - |
| <a id="3-errors-made-during-this-work-kept-on-the-record"></a>3. Errors made during this work, kept on the record | - |
| <a id="3b-a-declaration-is-not-a-definition-sweep-for-undefined-extern-operands-round-924"></a>3b. A declaration is not a definition: sweep for undefined `extern` operands (round 924) | `0x10031004` |
| <a id="3c-rebrew-data-lists-type-conflict-list-is-a-signal-not-a-work-queue-round-925"></a>3c. `rebrew data list`'s type-conflict list is a signal, not a work queue (round 925) | `0x10030b84` |
| <a id="4-an-objective-criterion-with-no-check-will-silently-stay-unverified-round-934"></a>4. An objective criterion with no check will silently stay unverified (round 934) | - |
| <a id="5-rebrew-library-match-without---allow-is-not-a-finding-round-947"></a>5. `rebrew library match` without `--allow` is not a finding (round 947) | - |
| <a id="6-a-header-records-a-true-observation-about-a-compilation-that-no-longer-exists-rounds-940-955-957"></a>6. A header records a true observation about a compilation that no longer exists (rounds 940, 955-957) | - |
| <a id="7-a-sweep-that-rewrites-a-tracked-file-must-be-killable-and-self-restoring-round-966"></a>7. A sweep that rewrites a tracked file must be killable and self-restoring (round 966) | - |
| <a id="8-probe-history-lives-in-two-places-whathaspy-indexes-only-one-round-978"></a>8. Probe history lives in TWO places; `whathas.py` indexes only one (round 978) | `0x1000bebc` |
| <a id="9-the-round-978-rule-was-written-and-then-broken-in-the-same-session-round-979"></a>9. The round-978 rule was written and then broken in the same session (round 979) | `0x101deac0` |
| <a id="10-four-wasted-rounds-share-one-cause-no-opening-step-forced-the-lookup-round-981"></a>10. Four wasted rounds share one cause: no opening step forced the lookup (round 981) | - |
| <a id="11-a-stale-in-source-note-can-describe-a-state-the-source-no-longer-has-round-982"></a>11. A stale in-source note can describe a state the source no longer has (round 982) | - |
| <a id="12-32-dangling-extern-array-declarations-are-latent-hazards-all-7-with-scalar-stubs-are-currently-inert-round-983"></a>12. 32 dangling `extern` array declarations are latent hazards; all 7 with scalar stubs are currently inert (round 983) | - |
| <a id="13-cl-fas-writes-its-listing-to-the-cwd-not-next-to-fo-round-984"></a>13. `cl /FAs` writes its listing to the CWD, not next to `/Fo` (round 984) | - |
| <a id="14-a-headers-bankable-once-n-bytes-are-recovered-can-itself-be-stale-round-986"></a>14. A header's "bankable once N bytes are recovered" can itself be stale (round 986) | - |
| <a id="15-rebrew-test---json-persists-state-including-a-per-function-toolchain-pin-round-997"></a>15. `rebrew test --json` PERSISTS state: including a per-function toolchain pin (round 997) | - |
| <a id="16-a-headers-unused-slack-figure-was-correct-the-check-that-disproved-it-was-tautological-rounds-998-1017-1018"></a>16. A header's "unused slack" figure was CORRECT: the check that "disproved" it was tautological (rounds 998, 1017, 1018) | - |
| <a id="17-a-stale-inventory-is-not-a-coverage-gap-check-the-annotations-before-claiming-missing-functions-rounds-1021-1024-corrected-round-1037"></a>17. A stale inventory is not a coverage gap: check the annotations before claiming missing functions (rounds 1021-1024, corrected round 1037) | - |
| <a id="19-rebrew-todos-20-items-are-2-real-carriers-and-18-false-positives-verified-again-rounds-955-1038"></a>19. `rebrew todo`'s 20 items are 2 real carriers and 18 false positives: verified again (rounds 955, 1038) | `0x10024000`, `0x10024044` |
| <a id="20-build-is-gitignored-so-a-hand-edited-buildmake-is-invisible-to-every-check-round-1051"></a>20. `build/` is gitignored, so a hand-edited `build.make` is invisible to every check (round 1051) | - |
| <a id="21-a-misleading-error-message-is-a-defect-postlinks-rdata-prefix-check-named-one-cause-and-hid-the-measurement-round-1053"></a>21. A misleading error message is a defect: postlink's `.rdata` prefix check named one cause and hid the measurement (round 1053) | - |
| <a id="22-inserting-a-for--else-mid-body-dedents-the-rest-of-the-loop-and-no-other-check-sees-it-round-1055"></a>22. Inserting a `for ... else` mid-body dedents the rest of the loop, and no other check sees it (round 1055) | - |
| <a id="23-a-read-only-metadata-file-is-rebrews-write-lock-not-a-bug-the-cli-is-meant-to-write-it-round-1060-corrected-round-1061"></a>23. A read-only metadata file is rebrew's WRITE-LOCK, not a bug: the CLI is meant to write it (round 1060, corrected round 1061) | - |
| <a id="24-some-source-experiments-need-a-full-object-rebuild-to-recover-from-and-linktestsh-cannot-tell-you-round-1064"></a>24. Some source experiments need a full object rebuild to recover from, and `linktest.sh` cannot tell you (round 1064) | - |
| <a id="25-rebrew-source-rename-leaves-the-cmake-tree-stale-and-both-guards-miss-it-round-1080"></a><a id="26-cmake---build-build---target-final-needed-two-passes-after-a-clean-configure-and-reported-a-fake-residue-of-86676-round-1102"></a>25. `rebrew source rename` leaves the CMake tree stale, and both guards miss it (round 1080) | - |
| <a id="26-the-retired-final-target-hid-a-failed-first-build-round-1102"></a>26. The retired `final` target hid a failed first build (round 1102) | - |
| <a id="27-the-goldtl-client-statically-links-d3dx8-run-lib-match-against-d3dx8lib-not-just-libcmt-round-1143"></a>27. The GOLDTL client statically links D3DX8: run `lib-match` against `d3dx8.lib`, not just LIBCMT (round 1143) | `0x0045fa70`, `0x00460a40`, `0x005e0000`, `0x0064ffff` |
| <a id="28-pin-both-the-cmake-toolchain-and-the-verification-target-2026-10-15"></a>28. Pin both the CMake toolchain and the verification target (2026-10-15) | - |
| <a id="same-target-names-need-reviewed-reference-ownership-2026-10-16"></a>Same-target names need reviewed reference ownership (2026-10-16) | `0x005012b0`, `0x005392a0` |
| <a id="run-contract-audits-after-metadata-writes-finish-2026-10-16"></a>Run contract audits after metadata writes finish (2026-10-16) | - |

</details>
