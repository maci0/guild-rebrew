<a id="documentation"></a>

# Knowledge base

Start with a task below. Managed metadata holds current verdicts;
[current work](TODO.md) records a dated snapshot and priorities.
[Provenance](provenance.md) records decisions, and the
[archive](goal-history.md#full-notebooks) preserves earlier research.

<a id="reading-order"></a>

## Start and continue

| Need | Page |
| --- | --- |
| Project overview | [README](../README.md) |
| Completion criteria | [Objective](../goal.md) |
| Current status and next actions | [Current work](TODO.md) |
| Open source questions | [Handoff](HANDOFF.md) |
| Server build | [Build guide](build.md) |
| Client comparison builds | [Client guide](../stubs/README.md) |
| Implementation and metadata rules | [AGENTS.md](../AGENTS.md) |
| Tool design | [Principles](../PRINCIPLES.md) |
| Releases | [1.11.0](releases/1.11.0.md), [1.10.0](releases/1.10.0.md) |

## Workflows

| Topic | Page |
| --- | --- |
| Shared source and analysis | [Git and BinSync](collaboration.md) |
| CLI selection and upstream tooling | [Tooling](tooling-upstream.md) |
| Verification and caches | [Verification](verify-performance.md) |
| Vendor inputs and patches | [Vendoring](vendoring.md) |
| Client SDK dependencies | [DirectX](directx-inputs.md), [Miles 6.1c](../references/mss-6.1c/README.md) |
| Process mistakes | [Workflow checks](workflow-traps.md) |

<a id="reference-map"></a>

## Technical reference

A translation unit (TU) is a source file with its included headers. VA means
virtual address.

| Question | Page |
| --- | --- |
| Which names are attested or inferred? | [Naming](naming_conventions.md) |
| Which renames were made, and on what evidence? | [Name ledger](name-ledger.tsv) |
| Where does a definition belong? | [Source layout](source-layout.md) |
| Who allocates these bytes? | [Data ownership](data-ownership.md) |
| What compiler and runtime did each target use? | [Build facts](general-knowledge.md) |
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

[Research history](goal-history.md) lists the archived notebooks and the local
receipts. Topic pages link to their archived write-ups where available. An archived
claim is historical evidence; check current inputs before relying on it.

```sh
uv run rebrew source findings 0x00499950 --json
```

Replace the example VA with the address under review. Keep new notes in `docs/`
and attachments in `docs/assets/`; link to an existing topic before adding a
second explanation. To use Obsidian, open the repository root and keep
`.obsidian/` settings local.

`rebrew init --refresh-agents` rewrites [AGENTS.md](../AGENTS.md) above the
`rebrew: project rules` marker and all of [PRINCIPLES.md](../PRINCIPLES.md).
The refresh also rewrites and prunes generated `.agents/skills/` files. Keep
project-specific rules below the marker; see [skill overrides](../AGENTS.md#agent-skills)
for preserving skill customizations.
