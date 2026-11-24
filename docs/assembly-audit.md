# Assembly audit

[AGENTS.md](../AGENTS.md#assembly-and-linker-gaps) owns assembly policy.
`rebrew source document-assembly` records reviewed evidence for each definition
and target. `rebrew test` and `rebrew verify` earn byte verdicts separately.
Whole-function assembly remains separate from C recovery.

## What qualifies

Positive native evidence can support original assembly at a specific site.
Actual alignment bytes can support padding. A failed C search, byte match,
blocker or `REBREW_ALLOW_NAKED` define establishes neither.

Review source/context freshness and each target independently. Gold evidence does
not exempt GoldTL. Matching source hashes confirm unchanged source text. They
do not validate a receipt's reasoning or other inputs.

## Find outstanding work

```sh
uv run --frozen rebrew todo --category naked-reconstruction --all-targets --json
uv run --frozen rebrew lint --all-targets --json
```

The todo category reports byte-matched definitions still marked `source = "naked"`.
Each target defaults to at most 20 items; increase `--limit` to review more.
Lint E023 uses a heuristic to flag whole-function naked assembly dumps; reviewed
assembly and minor padding are exempt. A clean lint run does not establish native
assembly evidence. Use both lists without maintaining a separate count here.

## Compilation and retention

Separate compilation, selected link inputs, archive extraction and retained
contributions. A gap proves none of them. Comparison-client `/OPT:NOREF` retains
selected contributions but does not establish original linker behavior.
[Link layout](msvc6-link-layout.md) owns placement and discard analysis.

Acceptance requires complete native bodies, operands, literals and the relevant
raw-image checks.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
