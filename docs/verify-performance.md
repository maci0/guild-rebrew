# Verification and caches

Use the smallest check that covers the claim. [Measurement](measure-traps.md)
explains verdict limits; [build instructions](build.md) cover raw images.

| Need | Command | Compiler work |
| --- | --- | --- |
| Existing image data | `uv run --frozen rebrew verify --data` | None unless functions are requested |
| Existing image structure | `uv run --frozen rebrew verify --whole-binary` | None unless functions are requested |
| Function placement and linked EXACT | `uv run --frozen rebrew verify --text --raw-link` | Function checks and linked-image comparison |
| Function bodies | `uv run --frozen rebrew verify` | Cached or fresh compilation/comparison |
| Functions and data | `uv run --frozen rebrew verify --functions --data` | Both pipelines |
| Recheck every selected function | `uv run --frozen rebrew verify --no-cache` | Rechecks verdicts; may reuse objects |

Select `--target` and `--built` for the image under review, and keep its matching
map beside it or pass `--link-map`. The project defaults to GoldTL. `--text`,
source scopes, `--context` and `--fix-sizes` also request function checks, even
with image checks selected. Inspect `functions_checked` in JSON to confirm scope.

Use `--dry-run` to preview without writes. `--no-promote` prevents function-metadata
updates but still saves the report and cache. `--raw-link` acknowledges unmodified
linker output; a path matching the target's configured `raw_link` also supplies
that acknowledgement. Linked EXACT requires matching bytes and placement.

## Cache layers

Compiler image/helper caches, compiled-object caches, verdict caches and CMake
object trees have different inputs and lifetimes. A warm object still needs
extraction/comparison. A valid verdict hit can avoid both. Known-binding policy
still applies to cached results.

CMake objects are not interchangeable with test objects: flags, defines and
compiler-visible paths can differ. Header or generated-input changes may rebuild
more than the edited source. Do not retime generated files to suppress that work.

The configured `unshare` backend runs inside pinned toolchain image filesystems.
Docker prepares those images; there is no host compiler fallback. See the
[build prerequisites](build.md#prerequisites) for backend requirements.

## Diagnose a slow check

Separate time waiting for compiler/metadata locks from actual compilation. Record
cache state and host load before comparing timings. A timeout gives no verdict;
confirm the process/lock state before retrying.

Clear disposable compiled objects with `uv run --frozen rebrew cache clear --force`. Preserve
verification baselines and research receipts when cleaning local state.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
