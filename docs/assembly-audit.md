# Assembly audit

[AGENTS.md](../AGENTS.md#assembly-and-linker-gaps) owns assembly policy. Metadata
records each reviewed definition/target receipt and byte verdict through
`rebrew source document-assembly`. Whole-function assembly is separate from C recovery.

## What qualifies

Positive native evidence can support original assembly at a specific site.
Actual alignment bytes can support padding. A failed C search, byte match,
blocker or REBREW_ALLOW_NAKED define establishes neither.

Native INT3 assertion branches support an assembly-statement inference. The
repeated fill/copy family has a bounded likelihood argument from register
invariance and operand homing across contexts, including literal-count spills.
That is not proof of C impossibility, authorship or an original macro name.

Review source/context freshness and each target independently. Gold evidence does
not exempt GoldTL. A matching source hash does not independently prove every
sentence in a provenance receipt.

## Find outstanding work

```sh
uv run rebrew todo --category naked-reconstruction --target Europa1400Gold.exe --json
uv run rebrew lint --all-targets --json
```

The todo category selects metadata source=naked; lint E023 detects whole-function
naked C definitions. They are different lists. Do not maintain another count here.

## Compilation and retention

Separate compilation, selected link inputs, archive extraction and retained
contributions. A gap proves none of them. Comparison-client /OPT:NOREF retains
selected contributions but does not establish original linker behavior.
[Link layout](msvc6-link-layout.md) owns placement and discard analysis.

Historical C recoveries, assertion/fill receipts and corrected partial extents
are indexed below. Current acceptance still requires complete native bodies,
operands, literals and the relevant raw-image checks.

## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

The [November 5 archive](archive/2026-11-05-documentation.tar.xz) preserves the full
`docs/assembly-audit.md` notebook, including corrections and receipt paths. Entries below locate
historical claims, not current instructions or verdicts. Hex values include
code/data addresses and constants.

```sh
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/assembly-audit.md | less
```

| Historical section | Referenced hex values |
| --- | --- |
| Assembly audit | - |
| <a id="recovery-checkpoint"></a>Recovery checkpoint | `0x42c200`, `0x42c340`, `0x4364f0`, `0x44f680`, `0x44f860`, `0x45dad0`, `0x465c80`, `0x46c250`, `0x4c0210`, `0x4c2480`, `0x4c24c0`, `0x4ce130`, `0x4fe1e0`, `0x5a89a0` |
| What qualifies | `0x4023b2` |
| Compilation and retention | - |
| <a id="goal88-remaining-list-snapshot"></a>Goal88 remaining-list snapshot | - |
| <a id="replays-and-limits"></a>Replays and limits | `0x575900`, `0x575930` |

</details>
