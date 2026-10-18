# Project principles

[AGENTS.md](../AGENTS.md) owns project rules and the skills describe procedures.
[PRINCIPLES.md](../PRINCIPLES.md) owns the shared tool-design principles.

For this reconstruction:

- Require faithful C and complete raw-file identity for all three targets.
- Preserve the server while recovering shared client definitions and contracts.
- Separate code agreement, source fidelity, library origin, selected providers,
  data ownership and placement. Evidence for one does not establish the others.
- Keep one home per fact: objective in [goal.md](../goal.md), current work in
  [TODO.md](TODO.md), measurements in their technical reference, and identity,
  verdicts and source definitions in the managed stores. `rebrew-functions.toml`
  is format 3 and holds `source.definitions` and `source.files`.
  `rebrew-data.toml` remains format 2. The separate source store is retired.
- Retain reproducible evidence when correcting a conclusion; remove obsolete
  instructions from the live path and link the correction.
