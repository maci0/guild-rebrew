# Research history

Old scores, flags, release states and running-job instructions describe the
tree at the time they were written. [Current work](TODO.md) has the latest
documented snapshot and next actions. [Provenance](provenance.md) is the
append-only decision ledger.

<a id="full-notebooks"></a>

## Full notebooks

| Archive | Contents |
| --- | --- |
| [2026-10-16 notebooks](archive/2026-10-16-notebooks.tar.xz) | 24 documents from the first cleanup |
| [2026-10-18 documentation](archive/2026-10-18-documentation.tar.xz) | 28 documents from before the 2026-10-18 cleanup |
| [2026-10-18 module guides](archive/2026-10-18-module-readmes.tar.xz) | Three source and Miles guides |
| [2026-11-05 documentation](archive/2026-11-05-documentation.tar.xz) | Guides, notebooks, work queue, handoffs and status graphics as of November 5 |

Section and finding numbers in source comments and vendor patches refer to
the corresponding `docs/<name>.md` member in the November 5 documentation archive,
even when an older comment omits the `archived` qualifier. Comments covered by reviewed source provenance
are retained verbatim. Read their compiler-search claims as results of the recorded
probes, under the limits in [negative results](codegen-walls.md).

Read a member without extracting it over the working tree:

```sh
tar -tf docs/archive/2026-11-05-documentation.tar.xz
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/msvc6-c-shapes.md | less
```

<a id="local-receipts"></a>

## Local receipts

Research receipts are under `../guild-rebrew-archive/2026-11-05/`, relative to
the checkout root. Former `.scratch/` paths are under `scratch/` there, and
former `.rebrew/` state is under `rebrew-state/`. The directory is local only.
Review a candidate before restoring it over current source.

Record a new result once, in the reference or receipt that owns it.
