# Verification and runner performance

Current command behavior and execution settings. Timings below are dated local
observations, not cold-build benchmarks.

## Choose the check

| Need | Command | Compiler work |
| --- | --- | --- |
| Built data | `rebrew verify --data` | None unless functions are requested |
| Image structure | `rebrew verify --whole-binary` | None unless functions are requested |
| Function bodies | `rebrew verify` | Cached or fresh compilation/comparison |
| Combined data and functions | `rebrew verify --data --functions` | Function pipeline plus image check |
| Recheck every selected function | `rebrew verify --no-cache` | Skips the verification-result cache only |

Select the target and built image explicitly when needed. `--text` and explicit
source scopes also request function checking. JSON reports `functions_checked`.
A difference exits 1; a fast check is not necessarily a passing check.

## Causes and fixes

The old data-only path unconditionally ran function verification after the image
check. It scanned thousands of sources and recompiled or re-extracted objects.
Image-only checks now avoid that pipeline, leave function-result caches and the
function comparison baseline alone, and do not initialize a compiler runner.
On October 17, data dry-runs took 0.674s for Gold and 0.667s for TL; normal writes
took 1.764s/2.011s. Server data took 2.066s, with 652/652 matches.
Receipts: `.scratch/goal85-asm-audit/`.

Other repaired costs:

- **Known bindings disabled warm results.** Cached verdicts now require matching
  binary/compile inputs and unchanged resolution of every recorded operand.
  Missing evidence, changed addresses and gained/lost bindings force a miss;
  unchanged conflicts remain failures.
- **Relative path cache crossed projects.** Roots are made absolute before
  memoized symlink resolution, so changing cwd cannot reuse another project's
  metadata root.
- **Oversized compiler argv.** A 4,002-source cohort exceeded Wine's 32,767-character
  command-line limit and could fall back to individual launches. Oversized MSVC
  batches use a response file while retaining the readable first source required
  by the image wrapper. Pinned control objects agree with inline argv output.
- **Uninitialized Wine prefix.** Unshare now seeds Wine in the image cache before
  publishing it, waits for wineserver, and preserves extracted mtimes. Each run
  still uses private writable state. A private font cache removes repeated
  fontconfig errors. Receipts: `.scratch/goal110-full-runs/`.

## Runner and caches

`[compiler] execution_backend = "unshare"` governs verification and the CMake
CL/LINK/LIB driver. Server uses the pinned plain-SP5 image; clients use Processor
Pack. The runner uses those image filesystems and Wine, with no host compiler
fallback. Verification honors per-target compiler overrides. The CMake driver
has a profile pin but no Rebrew target identity, so it uses the project-level
backend; target-scoped CMake backend selection remains an upstream capability gap.

The image/helper cache, compiler-object cache, verification-result cache and
CMake object trees serve different purposes. A warm object avoids compilation
but still needs extraction/comparison; a valid result hit avoids both.
`verify --no-cache` rechecks every selected function but can reuse a matching
`.obj`. Backend identity separates Docker and unshare compile entries. Existing
CMake objects are not evidence that current compile inputs match.

`rebrew test --linked` is a separate padded-shell link. Rebrew 5.1.0 stops that
command when `execution_backend` is `unshare`, with
`execution_backend = unshare does not support linked comparison yet`.
`rebrew todo` can still print `rebrew test 0x<VA> --linked` for a RELOC row.
Ordinary object comparison, `verify --text --raw-link` on an existing image,
and CMake CL/LINK/LIB stay on the configured unshare runner.

Goal110 compared complete Gold `/ML` and TL `/MT` COFF objects using identical
argv and pinned time: Docker and unshare outputs were equal. The native probes
took 3.390s/2.513s versus Docker's 12.713s/18.796s under shared host load. This is
not a controlled whole-build speedup. Both subsequent full client passes linked;
compiler-warning cleanup and final-source rebuilds remain separate work.

## Imported slots

`__imp__EnterCriticalSection@4` and `__imp__LeaveCriticalSection@4` are already
import metadata and exist in both client images. KERNEL32 provides the functions;
the linker/loader owns their slots. They need no replacement C storage. The
placement view now includes DLL map records while static ownership excludes
them. Displaced slots remain a placement failure, even when import names agree.

## Replays

- Data-path, cache and import-slot fixes: `.scratch/goal85-asm-audit/`.
- CMake backend repair: `.scratch/goal109-unshare-runtime/REPORT.md`.
- Prefix isolation and equal objects: `.scratch/goal110-full-runs/seed-isolation.json`
  and `compile-equivalence.json`.
- Actual client/gate outputs: [current work](TODO.md).
