# Rejected Miles import-library candidate

`references/mss-6.0/mss32.lib` is a local audit input. Neither client selects it
in `rebrew-project.toml`; both select the [6.1c archive](../mss-6.1c/README.md).

| Property | Value |
| --- | --- |
| Local source, relative to the checkout root | `../openmiles/references/MSS-6.0/mss32.lib` |
| Bytes | 238,328 |
| SHA-256 | `dadb9a3e8db1f0359cafda6ffed71565237549f53e9e62a24265b26a8e36e78d` |

The local copy matches that source. The archived
`text-accounting-20261016/all-miles-library-fingerprints.json` records all 51
GoldTL import names present and zero matching import hints for this hash.
The directory label alone does not establish the SDK version.

That receipt is under `../guild-rebrew-archive/2026-11-05/scratch/`, relative
to the checkout root. See [receipt locations](../../docs/goal-history.md#local-receipts).
