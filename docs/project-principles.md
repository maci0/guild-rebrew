# Rebrew principles

Project rules and exact commands live in [AGENTS.md](AGENTS.md) and the shipped
skills. These principles explain the intended tool behavior.

1. **Repeatable operations.** Re-running a workflow must be safe; configured inputs
   determine its result. Settings belong in `rebrew-project.toml`.
2. **One CLI.** Compose `rebrew <command>` operations. CMake and objdiff call
   `rebrew build driver` and `rebrew build objdiff-driver`.
3. **Honest verdicts.** Record measured improvements and regressions. Preserve
   earned verdicts on tooling failure and respect SKIP. PROVEN is semantic
   evidence; the next byte comparison replaces it.
4. **Native evidence.** Retrieve addresses, types, extents, calling conventions
   and names from reference bytes and canonical metadata. Coverage is a view.
5. **Preserve known matches.** Probe in scratch; verify affected definitions,
   callers and target contexts before adopting source/header/compiler changes.
6. **One owner.** Canonical source or a selected library member supplies storage.
   Declarations, aliases, spans and imports are different relationships.
7. **C89 fidelity.** Use evidenced widths, conventions and control flow. Keep
   declarations at block top and test emitted bytes after source changes.
8. **Separate synchronization from verification.** BinSync carries native fields;
   Rebrew owns statuses, flags, blockers and comparison evidence. Preview or
   failed sync must not advance its baseline.
9. **Use the existing tools.** Check CLI help and public APIs before adding a
   helper. Put reusable repairs upstream with regression tests.
10. **Report only what was checked.** Object matches, linked matches, whole-file
    identity and bounded semantic checks establish different claims. Never hide
    a failing gate or promote a verdict through prose.
