# Workflow checks

[AGENTS.md](../AGENTS.md) owns project rules. This checklist covers mistakes that
repeatedly invalidated otherwise plausible work.

## Before editing

- Read the source, current binding and address-keyed findings before starting a
  new probe. Resolve the exact target/VA rather than borrowing a similar name.
- Establish exclusive file/definition ownership for parallel work. Review shared
  callers, types, storage and build contexts before assigning separate edits.
- Check the library provider and complete native extent before treating a row as
  missing game code. A signature miss is inconclusive.
- Use the installed CLI and public APIs before writing a duplicate helper.

## During a probe

Keep the baseline and each candidate receipt separate. Record failed commands;
a later successful run does not make the first one pass. Check actual exit codes
and full diagnostics instead of counting familiar error strings.

Observe the live process handle when waiting. A missing notification, old lock file
or opaque error is not proof that work stopped. Do not launch duplicate workers
or compiler jobs to work around an unverified wait.

## Before accepting a change

Inspect every affected target and caller, generated build inputs and linker
anchors. A source rename can leave stale build state or explicit retention symbols.
Review managed-store changes through their owning writers; read-only file mode is
intentional, not permission to bypass locks.

Rebuild the artifact that decides the claim. Check its freshness and full length.
A green object score does not clear link, data, load or source-fidelity failures.
[Measurement](measure-traps.md) owns those distinctions.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
