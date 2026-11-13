# Assembly audit

[AGENTS.md](../AGENTS.md#assembly-and-linker-gaps) owns assembly policy. Metadata
records each reviewed definition/target receipt and byte verdict through
`rebrew source document-assembly`. Whole-function assembly is separate from C recovery.

## What qualifies

Positive native evidence can support original assembly at a specific site.
Actual alignment bytes can support padding. A failed C search, byte match,
blocker or `REBREW_ALLOW_NAKED` define establishes neither.

Review source/context freshness and each target independently. Gold evidence does
not exempt GoldTL. Matching source hashes confirm unchanged source text. They
do not validate a receipt's reasoning or other inputs.

## Find outstanding work

```sh
uv run rebrew todo --category naked-reconstruction --target Europa1400Gold.exe --json
uv run rebrew lint --all-targets --json
```

The todo category reports byte-matched definitions still marked `source = "naked"`.
Lint E023 flags unsupported whole-function assembly dumps. Documented assembly
and minor padding are exempt. These are different lists. Do not maintain another
count here.

## Compilation and retention

Separate compilation, selected link inputs, archive extraction and retained
contributions. A gap proves none of them. Comparison-client /OPT:NOREF retains
selected contributions but does not establish original linker behavior.
[Link layout](msvc6-link-layout.md) owns placement and discard analysis.

Acceptance requires complete native bodies, operands, literals and the relevant
raw-image checks.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
