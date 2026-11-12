# Research history

Historical evidence is separate from [current work](TODO.md). Old scores, flags,
release states and running-job instructions do not describe the current tree.
[Provenance](provenance.md) remains the append-only decision ledger.

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

Live technical pages index archived techniques and addresses.
`.venv/bin/rebrew source findings` searches project evidence; detailed controls
and corrections are in the corresponding archived member.

## Local receipts

Local research receipts are under `../guild-rebrew-archive/2026-11-05/`.
Former `.scratch/` paths resolve under `scratch/`, and former `.rebrew/` state
under `rebrew-state/`. This directory is local-only. Do not restore a candidate
over current source without review.

Record a new result once in its owning reference or receipt. Do not append another
full status report, work queue or procedure to the notebooks.

## Archived techniques

Original notebook: `docs/goal-history.md` in the [documentation archive](goal-history.md#full-notebooks).

- Goal history
- Recent milestones (`0x004364f0`)
