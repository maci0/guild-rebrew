# Miles 6.1c build dependency

Both clients select the SDK archive at `references/mss-6.1c/mss32.lib`.
It is a reproducible build input, not proof of the exact archive used by the
original linker.

## Install

Download the [pinned archive](https://raw.githubusercontent.com/ProjectDreamland/area51/dfaa140222e8918c47b844af15dd10150b05a9a9/xCore/3rdParty/Miles6/lib/win/Mss32.lib)
without modification and save it at the path above. The binary stays ignored.

| Property | Value |
| --- | --- |
| Source | ProjectDreamland/area51, commit `dfaa140222e8918c47b844af15dd10150b05a9a9` |
| Git blob | `79105dce07956c70a0e6bc4156236f3e91a36bea` |
| Bytes | 253,742 |
| SHA-256 | `34882ed6295c6d7937a505ccab6f32b50a47433856431565ef49860d6bd45f9d` |

## Verify

```sh
sha256sum references/mss-6.1c/mss32.lib
```

`cmake/verify-mss32.cmake` checks that hash during configuration and before each
client link. CMake also checks that each client selects this archive. Missing,
changed or substituted archives fail; do not generate a replacement import library.

## Evidence

The saved snapshot header identifies 6.1c. The archived `link-probe.json` records
51 GoldTL and 31 Gold MSS32 imports with matching names and hints. These isolated
probes do not establish a complete client image. The [6.0 candidate](../mss-6.0/README.md)
supplied the names but failed every hint check.

Local receipts are under
`../guild-rebrew-archive/2026-11-05/scratch/goal83-miles-candidates/`, relative to
the checkout root. `source-pin.json` records the commit and blob above;
`downloads.json` records the archive hash and size. `area51-mss.h` contains the
version label. See [receipt locations](../../docs/goal-history.md#local-receipts).

Historical analysis and receipt paths are preserved as
`references/mss-6.1c/README.md` in the
[documentation archive](../../docs/goal-history.md#full-notebooks). Reference game
hashes belong in the [build guide](../../docs/build.md#reference-inputs).
