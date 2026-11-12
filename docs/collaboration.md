# Git and BinSync

The project repository contains C, headers, configuration, layouts, native evidence and
managed metadata. Use a narrow branch/worktree, agree on definition ownership,
and submit affected-target checks with changes. Rebrew writers own metadata edits.

BinSync is optional analysis exchange. It carries reviewed names, prototypes,
comments, locals, globals and types. It does not import STATUS, compiler flags or
byte-match claims, and does not replace source review.

## State repositories

Use one state Git repository per exact reference binary. Give each
analyst and bridge its own BinSync username and branch. Use separate checkouts
for live clients with different users; do not switch branches under another client.

This project's ignored `binsync/` repository is configured for the server. Preserve
it rather than initializing over it. Client states need their own binary bindings.
Names and source similarity do not establish a compatible state repository.

Install the optional dependencies with `uv sync --extra binsync`.
Retain required extras on later syncs.

## Review an exchange

```sh
.venv/bin/rebrew binsync summary binsync --target server.dll --json
.venv/bin/rebrew binsync diff binsync --target server.dll --json
.venv/bin/rebrew binsync pull binsync --target server.dll --user BRIDGE_USER --no-git --dry-run --json
.venv/bin/rebrew binsync push binsync --target server.dll --user BRIDGE_USER --dry-run --json
```

Replace `BRIDGE_USER` with the bridge's BinSync username.
Do not infer it from the state author in `binsync/metadata.toml`. Resolve binary,
state-health and field conflicts first. `diff` exits 1 for differences. `--no-git`
uses already-fetched peer state. After reviewing a preview, omit `--dry-run` only
for the intended apply/export. Re-test changed C contracts and inspect the Git diff.

Push commits to the local state repository by default; `--git-push` publishes it.
Starting a watch loop or live synchronization requires an explicit request.

## Decompiler connections

A state export alone does not update Ghidra. Its BinSync plugin must consume the
state. Live analysis may provide callers, xrefs and pseudocode, but native
instructions remain necessary; past pseudocode omitted real x87 work.

Match binary hashes and compatible tool versions. Begin read-only, preserve
attested names, and preview types before import. Partial layouts and conflicting
private names must not become bulk canonical types.

## Archived techniques

Original notebook: `docs/collaboration.md` in the [documentation archive](goal-history.md#full-notebooks).

- Collaborating with Git and BinSync
- Live Ghidra analysis (`0x004b6f00`)
- State repository and users
- Review each exchange
