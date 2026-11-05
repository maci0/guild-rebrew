# Assembly audit

[AGENTS.md](../AGENTS.md#assembly-and-linker-gaps) owns assembly policy. Metadata
records each reviewed definition/target receipt and byte verdict through
`rebrew source document-assembly`. Whole-function assembly is separate from C recovery.

## What qualifies

Positive native evidence can support original assembly at a specific site.
Actual alignment bytes can support padding. A failed C search, byte match,
blocker or `REBREW_ALLOW_NAKED` define establishes neither.

Native INT3 assertion branches support an assembly-statement inference. The
repeated fill/copy family has a bounded likelihood argument from register
invariance and operand homing across contexts, including literal-count spills.
That is not proof of C impossibility, authorship or an original macro name.

Review source/context freshness and each target independently. Gold evidence does
not exempt GoldTL. Matching source hashes confirm unchanged source text. They do not validate a
receipt's reasoning or other inputs.

## Find outstanding work

```sh
uv run rebrew todo --category naked-reconstruction --target Europa1400Gold.exe --json
uv run rebrew lint --all-targets --json
```

The todo category selects metadata `source = "naked"`; lint E023 detects whole-function
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

Original notebook: `docs/assembly-audit.md` in the [documentation archive](goal-history.md#full-notebooks).

| Historical section | Referenced hex values |
| --- | --- |
| <a id="recovery-checkpoint"></a>Recovery checkpoint | `0x0042c200`, `0x0042c340`, `0x004364f0`, `0x0044f680`, `0x0044f860`, `0x0045dad0`, `0x00465c80`, `0x0046c250`, `0x004c0210`, `0x004c2480`, `0x004c24c0`, `0x004ce130`, `0x004fe1e0`, `0x005a89a0` |
| What qualifies | `0x004023b2` |
| <a id="goal88-remaining-list-snapshot"></a>Goal88 remaining-list snapshot | - |
| <a id="replays-and-limits"></a>Replays and limits | `0x00575900`, `0x00575930` |

</details>
