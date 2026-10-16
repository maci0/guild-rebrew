# Documentation

Start with [the objective](../goal.md), then [current work](TODO.md).
[Goal history](goal-history.md) is a milestone index and full-log archive;
[AGENTS.md](../AGENTS.md) owns project rules.

## Reference map

| Question | Read |
| --- | --- |
| Which C shape changes the emitted bytes? | [C shapes](msvc6-c-shapes.md), indexed by symptom |
| Why these registers or stack slots? | [Allocator findings](msvc6-allocator.md) |
| Has this matching lever already failed? | [Codegen walls](codegen-walls.md) |
| What does this score or verdict establish? | [Measurement traps](measure-traps.md) |
| What controls sections, imports and relocation layout? | [Link layout](msvc6-link-layout.md) |
| Does this client function have server storage? | [Client-only sweep](client-only-sweep.md) |
| Who owns this global or interior view? | [Data ownership](data-ownership.md) |
| Where does this source/type belong? | [Source layout](source-layout.md) |
| What name is attested or inferred? | [Naming conventions](naming_conventions.md) |
| Which tool replaces an old script? | [Tooling](tooling-upstream.md) |
| How are vendor patches reproduced? | [Vendoring](vendoring.md) |
| What process mistakes should I avoid? | [Workflow traps](workflow-traps.md) |
| What principles guide project work? | [Project principles](project-principles.md); generated tool rules remain in [PRINCIPLES.md](../PRINCIPLES.md) |
| What is known about a residue function's behavior? | [Behavioral reviews](behavioral-verdicts.md), historical |
| What is known about the original build? | [Build facts](general-knowledge.md) |
| What are the game, network and asset conventions? | [Game compendium](game-compendium.md) |

## Evidence lookup

```sh
uv run --frozen rebrew source findings 0x<VA> --json
uv run --frozen rebrew source findings 0x<VA> --window 64 --json
```

These search live Markdown under `docs/`. For retired session logs, use the
[archive search commands](goal-history.md#full-notebooks). Historical figures are
measurements at their stated checkpoint. Query current metadata and run the gate
before reporting current status; old postlink success does not prove a raw link.

## Keep it short

- One home per fact: objective in `goal.md`, current work in `TODO.md`, milestones
  in `goal-history.md`, technical evidence in its reference. Link instead of copying.
- Findings retain target/VA, result, limits and receipt/replay. Omit running-job
  transcripts and repeated whole-project status reports.
- Keep existing section numbers and anchors: source comments cite them. Append
  new numbered findings without renumbering or reusing old numbers.
- Qualify client VAs with TL or Gold; server VAs start `0x100…`.
- Leave generated coverage, vendor documents and managed metadata to their owners.
