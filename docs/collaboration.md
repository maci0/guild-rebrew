# Git and BinSync

The project repository contains C, headers, configuration, layouts, native evidence and
managed metadata. Use a narrow branch/worktree and agree on source, header and
layout ownership before parallel edits. Use separate build directories or one
linker writer; metadata locks protect neither source edits nor links. Submit
affected-target checks with changes. Rebrew writers own metadata edits.

BinSync is optional analysis exchange. It carries reviewed names, prototypes,
comments, locals, globals and types. It does not import STATUS, compiler flags or
byte-match claims, and does not replace source review.

## State repositories

Use one state Git repository per exact reference binary. Give each
analyst and bridge its own BinSync username and branch. Use separate checkouts
for live clients with different users; do not switch branches under another client.

This project keeps three ignored state repositories, one per current reference
binary, each set by `binsync_state_dir` in `rebrew-project.toml`:

| Target | State directory |
|---|---|
| `server.dll` | `binsync/` |
| `Europa1400Gold_TL.exe` | `binsync-goldtl/` |
| `Europa1400Gold.exe` | `binsync-gold/` |

`binsync-2026-09-22/` is the archived September state. It is bound to a binary that
is none of the three current ones and holds the user's own annotations: preserve it,
never initialize, push or prune over it. Preserve the three current repositories
too rather than initializing over them. Names and source similarity do not
establish a compatible state repository.

## Review an exchange

```sh
uv run --frozen --extra binsync rebrew binsync summary binsync --target server.dll --json
uv run --frozen --extra binsync rebrew binsync diff binsync --target server.dll --json
uv run --frozen --extra binsync rebrew binsync pull binsync --target server.dll --user REBREW_USER --no-git --dry-run --json
uv run --frozen --extra binsync rebrew binsync push binsync --target server.dll --user REBREW_USER --dry-run --json
```

For a client, use its state directory and target in place of `binsync` and `server.dll`. Replace `REBREW_USER` with Rebrew's own writer username. It must differ from
the live bridge's username: pull excludes Rebrew's user branch, and push writes
that branch. Keep the same writer identity for the exchange; do not infer it
from the state author in `binsync/metadata.toml`. Resolve binary,
state-health and field conflicts first. `diff` exits 1 for differences. `--no-git`
uses already-fetched peer state. A preview with `--no-git` cannot review unseen
remote changes. After reviewing a preview, omit `--dry-run` only
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

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
