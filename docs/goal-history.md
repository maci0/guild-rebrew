# Research history

The notebooks record the sources, flags and measurements at the time of each
experiment. See [current work](TODO.md) for the latest snapshot and
[provenance](provenance.md) for decisions.

## Full notebooks

| Archive | Contents |
| --- | --- |
| [2026-10-16 notebooks](archive/2026-10-16-notebooks.tar.xz) | 24 documents from the first cleanup |
| [2026-10-18 documentation](archive/2026-10-18-documentation.tar.xz) | 28 documents from before the 2026-10-18 cleanup |
| [2026-10-18 module guides](archive/2026-10-18-module-readmes.tar.xz) | Three source and Miles guides |
| [2026-11-05 documentation](archive/2026-11-05-documentation.tar.xz) | Guides, notebooks, work queue, handoffs and status graphics |

Section and finding numbers in source comments and vendor patches refer to the
matching `docs/<name>.md` member of the 2026-11-05 archive, even when an older
comment omits the `archived` qualifier. Comments covered by reviewed source
provenance stay verbatim. Read their compiler-search claims as results of the
recorded probes, under the limits in [negative results](codegen-walls.md).

Read a member without extracting it over the working tree:

```sh
tar -tf docs/archive/2026-11-05-documentation.tar.xz
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/msvc6-c-shapes.md | less
```

## Local receipts

Research receipts for the 1.13.0 round (2026-11-14) are under
`../guild-rebrew-archive/2026-11-14/`, relative to the checkout root. Former
`.scratch/` paths are under `scratch/` there. This directory is local to the checkout host.

The 2026-11-05 and 2026-11-13 receipt archives were deleted on 2026-11-14.
Provenance preserves the recorded results. Review any recovered candidate before
applying it to current source.

Record a new result once, in the reference or receipt that owns it.
