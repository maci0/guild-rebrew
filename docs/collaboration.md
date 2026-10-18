# Collaborating with Git and BinSync

Use Git branches and pull requests for reconstruction work. Commit the C,
headers, configuration, layout evidence and managed metadata together after
testing the affected target. These files are the canonical project. Change
managed metadata through Rebrew commands, then review and commit their diff.
BinSync is optional: it exchanges analysis fields with another analyst's
Ghidra session; it does not replace code review or Git history.

Each contributor should use their own clone or worktree and a narrow work branch.
Agree on function/file ownership before parallel edits, keep original binaries and
decompiler databases local, and include affected-target checks in the PR. Rebase
before publishing; do not resolve managed-store conflicts by discarding another
contributor's evidence or verdicts.

| Share through the project Git repository | Share through BinSync |
| --- | --- |
| C bodies, headers, layouts, build inputs, native evidence and managed metadata | Names, prototypes, notes, comments, locals, globals and types |
| Reviewed changes on a work branch and PR | Reviewed field export/import through a separate state repository |
| Verdicts earned by `rebrew test` / `verify` | No imported STATUS, compiler flags or match claims |

## State repository and users

Use one separate BinSync Git repository for each **exact binary**. Server,
TL and Gold are distinct targets; a shared function name does not make their
state interchangeable. Each analyst and Rebrew bridge needs its own BinSync
username and `binsync/<user>` branch, for example `maci-ghidra` and
`guild-server-rebrew`. Usernames must not contain spaces or `/`; they are
independent of `git config user.name`. Rebrew writes only its own branch and
reads peers' branches.

Each contributor keeps a local clone. Give a live decompiler plugin and a Rebrew
bridge separate checkouts when they use different users; avoid switching branches
under another running client's working tree.

A local state clone may live under an ignored `binsync/<target>/` directory or
beside this project. The existing `binsync/` is already a separate,
ignored Git repository configured for `server.dll` / `SERVER` in
[`rebrew-project.toml`](../rebrew-project.toml). Preserve it; do not initialize
another repository over it or assume its older user/branch conventions are
current. A target's binary hash must agree before exchanging fields.

Field sync requires the optional `rebrew[binsync]` dependency, including declib.
Install the project's optional extra:

```sh
uv sync --extra binsync
```

Add `--extra dashboard` as well to install both optional integrations. The
commands below retain the BinSync extra explicitly.

For a genuinely new state repository, choose a new path and a unique bridge user:

```sh
uv run --extra binsync rebrew binsync init ../guild-server-state --target server.dll --user guild-server-rebrew --dry-run --json
# After reviewing the preview, repeat without --dry-run to initialize locally.
```

## Review each exchange

Run from the project root and name the target explicitly. For the existing
server state, inspect the outgoing fields, both directions and divergence:

```sh
uv run --extra binsync rebrew sync summary --target server.dll --state-dir binsync --json
uv run --extra binsync rebrew binsync summary binsync --target server.dll --json
uv run --extra binsync rebrew binsync diff binsync --target server.dll --json
uv run --extra binsync rebrew binsync pull binsync --target server.dll --user guild-server-rebrew --no-git --dry-run --json
```

These previews do not fetch or apply changes. `diff` exits 1 when fields differ.
Resolve any binary, user or state-health errors before continuing. Review names,
signature edits, file renames, conflicts and skipped fields. Imported text is
analysis data. Use `--accept-local` or `--accept-binsync` only after reviewing
the affected conflicts; they select a policy for all conflicts in that invocation.

After review, `binsync pull` without `--dry-run` applies fields to the local
project. Keep `--no-git` to use already-fetched peer branches; omitting it lets
the wrapper fetch from the state repository's remote first. Inspect the resulting
project Git diff, re-test affected functions and submit the change through a PR.
Pull never imports STATUS or establishes a byte match.

Export is a separate, deliberate step:

```sh
uv run --extra binsync rebrew binsync push binsync --target server.dll --user guild-server-rebrew --dry-run --json
# After review, repeat without --dry-run to export and commit the bridge branch.
```

The default push commits only in the local state repository. `--git-push`
publishes its root and bridge branches to the remote; use it only when publishing
is intended. The Ghidra BinSync plugin consumes and produces its analyst's state;
Rebrew field exchange does not require a live ReVa connection.

There is no automatic two-way writer. An explicitly requested
`rebrew sync watch --target server.dll --state-dir binsync` continuously exports
local changes until interrupted; it does not pull edits back, and it rejects
`--json`. Keep normal collaboration on the reviewed, one-shot workflow above.

Format 3 `rebrew-functions.toml` holds function rows plus `source.definitions`
and `source.files`. `rebrew-data.toml` remains format 2. The separate source
store is retired. BinSync keeps its own transport schema, so the existing state
repository stays valid. Command shapes above match Rebrew 5.1.0 help. No state
repository was changed and no synchronization was started while writing this
guide.
