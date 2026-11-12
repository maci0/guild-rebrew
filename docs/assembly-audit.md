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
.venv/bin/rebrew todo --category naked-reconstruction --target Europa1400Gold.exe --json
.venv/bin/rebrew lint --all-targets --json
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

## Archived techniques

Original notebook: `docs/assembly-audit.md` in the [documentation archive](goal-history.md#full-notebooks).

- Recovery checkpoint (`0x0042c200`, `0x0042c340`, `0x004364f0`, `0x0044f680`, `0x0044f860`, `0x0045dad0`, `0x00465c80`, `0x0046c250`, `0x004c0210`, `0x004c2480`, `0x004c24c0`, `0x004ce130`, `0x004fe1e0`, `0x005a89a0`)
- What qualifies (`0x004023b2`)
- Goal88 remaining-list snapshot
- Replays and limits (`0x00575900`, `0x00575930`)
