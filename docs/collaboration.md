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

## Live Ghidra analysis

[Ghidra MCP](https://github.com/bethington/ghidra-mcp) can provide live
pseudocode, callers/callees, cross-references and data-flow queries while we
reconstruct C. BinSync carries reviewed names and types into the analysis;
Rebrew compilation and raw-image checks still establish byte agreement.

Exporting a state directory alone does not update Ghidra. Use the Ghidra
BinSync integration to consume it, or implement and test an explicit headless
relay. Keep one state repository per exact reference binary. This project
currently configures only the server state; the clients need their own program
paths and state directories.

Pin compatible Ghidra, plugin and bridge versions. Preserve the developers'
names: pass `strict_mode = false` where the endpoint supports it, and verify
the effective policy before allowing writes. The tested headless 6.0.0 server
does not load the project's naming-policy file automatically. Rebrew 5.2.0's
structural backends are ReVa and `ghidra-cli`; bethington's server is a separate
analysis connection, not a drop-in replacement for either backend. Begin with
read-only queries, review incoming fields through BinSync, and re-test affected
C after accepting names or types. This guide does not register a client connection.

A local 2026-10-19 trial used the stable MCP 6.0.0/Ghidra 12.1.2 pair and
REA 6.7.0 against the exact TL reference. After supplying the reviewed entry,
both returned the 216-byte body at `0x4b6f00`. Their pseudocode omitted its x87
calculation; native instructions and existing operand proof remained necessary.
REA creates a separate temporary database; reuse the persistent MCP project for
repeated queries. Full results and version hashes are in ignored
`.scratch/ghidra-mcp-trial/` and `.scratch/rea-trial/`.

Keep Ghidra databases under a path such as `build/ghidra`: Ghidra rejects
dot-prefixed project path elements. Preview BinSync types before importing; this
trial exposed partial layouts and conflicting private type names, so it did not
apply a bulk type import. The existing server state repository was preserved.

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
repository stays valid. Command shapes above match Rebrew 5.2.0 help. No state
repository was changed and no synchronization was started while writing this
guide.
