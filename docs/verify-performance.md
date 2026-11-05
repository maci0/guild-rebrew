# Verification and caches

Use the smallest check that covers the claim. [Measurement](measure-traps.md)
explains verdict limits; [build instructions](build.md) cover raw images.

| Need | Command | Compiler work |
| --- | --- | --- |
| Existing image data | `rebrew verify --data` | None unless functions are requested |
| Existing image structure | `rebrew verify --whole-binary` | None unless functions are requested |
| Function bodies | `rebrew verify` | Cached or fresh compilation/comparison |
| Functions and data | `rebrew verify --functions --data` | Both pipelines |
| Recheck every selected function | `rebrew verify --no-cache` | Rechecks verdicts; may reuse objects |

Select `--target` and `--built` for the image under review. `--text` and explicit
source scopes also request function checks. Inspect `functions_checked` in JSON;
a fast run need not have checked source. Use `--dry-run` when previewing writes.

## Cache layers

Compiler image/helper caches, compiled-object caches, verdict caches and CMake
object trees have different inputs and lifetimes. A warm object still needs
extraction/comparison. A valid verdict hit can avoid both. Known-binding policy
still applies to cached results.

CMake objects are not interchangeable with test objects: flags, defines and
compiler-visible paths can differ. Header or generated-input changes may rebuild
more than the edited source. Do not retime generated files to suppress that work.

The configured `unshare` backend runs inside pinned toolchain image filesystems.
Docker prepares those images; there is no host compiler fallback. Check current
help before using backend-specific features such as linked-shell comparison.

## Diagnose a slow check

Separate time waiting for compiler/metadata locks from actual compilation. Record
cache state and host load before comparing timings. A timeout gives no verdict;
confirm the process/lock state before retrying.

Clear disposable compiled objects with `rebrew cache clear --force`. Preserve
verification baselines and research receipts when cleaning local state. Historical
local timings and upstream repair measurements are indexed below, not benchmarks
for the current environment.

## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

Original notebook: `docs/verify-performance.md` in the [documentation archive](goal-history.md#full-notebooks).

- <a id="verification-and-runner-performance"></a>Verification and runner performance
- <a id="choose-the-check"></a>Choose the check
- <a id="causes-and-fixes"></a>Causes and fixes
- <a id="runner-and-caches"></a>Runner and caches
- <a id="imported-slots"></a>Imported slots
- <a id="replays"></a>Replays

</details>
