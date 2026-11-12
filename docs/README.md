<a id="documentation"></a>

# Knowledge base

Use the topic owners below instead of copying their rules, status or findings.
Historical measurements belong in archives; current verdicts belong in managed
metadata.

<a id="reading-order"></a>

## Start and continue

| Need | Canonical page |
| --- | --- |
| Project overview | [Repository README](../README.md) |
| Completion criteria | [Objective](../goal.md) |
| Project rule owners | [Project principles](project-principles.md) |
| Current validation and priorities | [Current work](TODO.md) |
| Work and completion pointers | [Remaining work](remaining-work.md) |
| Unfinished source questions | [Handoff](HANDOFF.md) |
| Server setup/build | [Build guide](build.md) |
| Client comparison builds | [Client guide](../stubs/README.md) |
| Implementation and metadata rules | [AGENTS.md](../AGENTS.md) |
| Releases | [1.11.0](releases/1.11.0.md), [1.10.0](releases/1.10.0.md) |

## Workflows

For an Obsidian vault, open the repository root and start with this page.
Use relative Markdown links; keep `.obsidian/` settings local. Put new notes
in `docs/` and attachments in `docs/assets/`.

| Topic | Canonical page |
| --- | --- |
| Shared source and analysis | [Git and BinSync](collaboration.md) |
| CLI selection and upstream tooling | [Tooling](tooling-upstream.md) |
| Verification and caches | [Verification](verify-performance.md) |
| Vendor inputs and patches | [Vendoring](vendoring.md) |
| Process mistakes | [Workflow checks](workflow-traps.md) |
| Tool design | [Principles](../PRINCIPLES.md) |

<a id="reference-map"></a>

## Technical reference

A translation unit, or TU, is a source file with its included headers. VA means
virtual address.

| Question | Canonical page |
| --- | --- |
| Which names are attested or inferred? | [Naming](naming_conventions.md) |
| Which function renames were made, with their evidence? | [Name ledger](name-ledger.tsv) |
| Where does a definition belong? | [Source layout](source-layout.md) |
| Who allocates these bytes? | [Data ownership](data-ownership.md) |
| What compiler/runtime did each target use? | [Build facts](general-knowledge.md) |
| Which C expression changes the emitted code? | [C shapes](msvc6-c-shapes.md) |
| Why these registers or stack slots? | [Register allocation](msvc6-allocator.md) |
| What controls the linked image? | [Link layout](msvc6-link-layout.md) |
| What does a comparison prove? | [Measurement](measure-traps.md) |
| Has a probe family already failed? | [Negative results](codegen-walls.md) |
| Which assembly is evidenced? | [Assembly audit](assembly-audit.md) |
| What is known about the game and formats? | [Game reference](game-compendium.md) |
| Which external findings were reviewed? | [Community research](community-research.md) |

<a id="evidence-lookup"></a><a id="keep-it-short"></a>

## Research and history

[Goal history](goal-history.md) lists the notebooks and how to read them.
The [client/server sharing survey](client-only-sweep.md) and
[behavioral reviews](behavioral-verdicts.md) are historical research indexes.
Technical pages retain searchable address indexes and old section anchors where
needed. An index entry locates a historical claim; it does not validate that claim.

```sh
uv run rebrew source findings 0x<VA> --json
```

[Provenance](provenance.md) is an append-only decision ledger, not a procedure.
Generated instructions, managed stores and vendor documents stay with their owners.
