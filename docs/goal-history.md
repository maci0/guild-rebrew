# Research history

Historical evidence is separate from [current work](TODO.md). Old scores, flags,
release states and running-job instructions do not describe the current tree.
[Provenance](provenance.md) remains the append-only decision ledger.

## Milestones

| Period | Research outcome |
| --- | --- |
| September 2026 | Server recovery and early codegen/layout experiments; later postlink claims were withdrawn. |
| October 2026 | Raw server identity, shared client recovery, native contracts, library attribution and source-organization reviews. |
| November 2026 | [1.10.0 source checkpoint](releases/1.10.0.md), reviewed client corrections and fleet shutdown. |

Detailed goal-by-goal chronology is archived. Resume from the
[handoff](HANDOFF.md), not a historical "next" instruction.

## Full notebooks

| Archive | Contents |
| --- | --- |
| [2026-10-16 notebooks](archive/2026-10-16-notebooks.tar.xz) | 24 documents from the first cleanup |
| [2026-10-18 documentation](archive/2026-10-18-documentation.tar.xz) | 28 documents before the earlier documentation cleanup |
| [2026-10-18 module guides](archive/2026-10-18-module-readmes.tar.xz) | Three source/Miles guides |
| [2026-11-05 documentation](archive/2026-11-05-documentation.tar.xz) | Pre-cleanup guides, notebooks, work queue, handoffs and obsolete status graphics |

Read without extracting over the working tree:

```sh
tar -tf docs/archive/2026-11-05-documentation.tar.xz
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/msvc6-c-shapes.md | less
```

Live technical pages retain old section anchors and searchable hex-value indexes.
`rebrew source findings` searches those Markdown pages and provenance; detailed
controls and corrections are in the corresponding archived member.

## Local receipts

The November release cleanup moved local research to
`../guild-rebrew-archive/2026-11-05/`. Former `.scratch/` paths resolve under
`scratch/`, and former `.rebrew/` state under `rebrew-state/`. The directory is
local-only, not part of a source release. Pre-cleanup moving maps are retained
inside that archive. Do not restore a candidate over current source without review.

Record a new result once in its owning reference or receipt. Do not append another
full status report, work queue or procedure to the notebooks.

## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

The [November 5 archive](archive/2026-11-05-documentation.tar.xz) preserves the full
`docs/goal-history.md` notebook, including corrections and receipt paths. Entries below locate
historical claims, not current instructions or verdicts. Hex values include
code/data addresses and constants.

```sh
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/goal-history.md | less
```

| Historical section | Referenced hex values |
| --- | --- |
| <a id="goal-history"></a>Goal history | - |
| Milestones | - |
| <a id="recent-milestones"></a>Recent milestones | `0x4364f0` |
| Full notebooks | - |

</details>
