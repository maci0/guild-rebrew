# Documentation

<a id="reading-order"></a>

## Build and contribute

| Task | Guide |
| --- | --- |
| Verify the server against its reference | [Server build and gate](build.md) |
| Link and compare the clients | [Client comparison builds](../stubs/README.md) |
| Choose work and see current measurements | [Current work](TODO.md) |
| Read project rules and completion criteria | [AGENTS.md](../AGENTS.md), [objective](../goal.md) |
| Exchange native analysis | [Git and BinSync](collaboration.md) |
| Choose a CLI command or report a tooling gap | [Rebrew tooling](tooling-upstream.md) |
| Measure changes and handle caches | [Workflow](workflow-traps.md), [comparison results](measure-traps.md), [verification performance](verify-performance.md) |
| Prepare SDKs or regenerate vendor sources | [DirectX](directx-inputs.md), [Miles 6.1c](../references/mss-6.1c/README.md), [vendoring](vendoring.md) |

<a id="reference-map"></a>

## Technical reference

| Topic | Reference |
| --- | --- |
| Source locations and shared definitions | [Source layout](source-layout.md) |
| Names and original spellings | [Naming conventions](naming_conventions.md), [name ledger](name-ledger.tsv) |
| Global storage and placement | [Data ownership](data-ownership.md) |
| Target compiler and runtime evidence | [Build facts](general-knowledge.md) |
| MSVC6 code generation | [C shapes](msvc6-c-shapes.md), [register allocation](msvc6-allocator.md), [search results](codegen-walls.md) |
| Linked image layout | [Link layout](msvc6-link-layout.md) |
| Original and reconstructed assembly | [Assembly audit](assembly-audit.md) |
| Game systems and formats | [Game reference](game-compendium.md), [community research](community-research.md) |
| Rebrew design | [Design principles](../PRINCIPLES.md) |

<a id="evidence-lookup"></a><a id="keep-it-short"></a>

## Evidence and history

- Search by virtual address with `uv run --frozen rebrew source findings 0x00499950 --json`. Use the address under review and check that the evidence applies to your target.
- See [unfinished reviews](HANDOFF.md) for source questions and the [provenance ledger](provenance.md) for recorded decisions.
- Find archived notebooks and local receipts in [research history](goal-history.md). Historical claims describe the inputs at the time.
- Model benchmark: [guild-bench](guild-bench.md).
- Source checkpoints: [1.20.0](releases/1.20.0.md), [1.19.0](releases/1.19.0.md), [1.18.0](releases/1.18.0.md), [1.17.0](releases/1.17.0.md), [1.16.0](releases/1.16.0.md), [1.15.0](releases/1.15.0.md), [1.14.0](releases/1.14.0.md), [1.13.0](releases/1.13.0.md), [1.12.0](releases/1.12.0.md), [1.11.0](releases/1.11.0.md), [1.10.0](releases/1.10.0.md).

Add new results to the page that covers their topic. Keep attachments in
`docs/assets/` and local Obsidian settings in `.obsidian/` outside Git.

`rebrew init --refresh-agents` refreshes the generated part of
[AGENTS.md](../AGENTS.md), [PRINCIPLES.md](../PRINCIPLES.md) and the installed
skills in `.agents/skills/`. Put local rules below the AGENTS marker and follow
the [skill override instructions](../AGENTS.md#agent-skills).
