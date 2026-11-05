# Rebrew design principles

These principles describe tooling. [AGENTS.md](AGENTS.md) owns project rules.

- Repeating a command with unchanged inputs must preserve content, timestamps and
  evidence. Retries must be safe.
- Resolve inputs from `rebrew-project.toml`. Make overrides explicit and replayable.
- Use focused `rebrew` commands and public APIs rather than duplicate tools.
- Record measured improvements and regressions. Respect SKIP; tooling failure must
  not erase earned evidence. PROVEN remains a bounded semantic result.
- Match each claim to its artifact: object, raw linked image or complete file.
  Renames, comments and scores earn no verdict.
- Probe in scratch and verify every affected target before adopting a change.
- Recover names, types, calls and ownership from native evidence. Generated source
  is a hypothesis, not evidence.
- Keep analysis exchange separate from verdicts. BinSync carries reviewed analysis;
  Rebrew owns statuses, flags, blockers and verification. A preview or failure must
  not advance a sync baseline.
- Preserve evidenced calling conventions, widths, precision and compiler-sensitive
  forms. Follow the selected language constraints, including C89 declarations.
- Check code, data and the whole file. Account for overlapping bytes once; BSS has
  no file-backed payload.
- Promote near matches only from actual comparisons. Search effort proves nothing.
- Keep source separate from managed identity and state. Use locked atomic writers;
  registration, edit stamps, external origins and verification are distinct facts.

Atomic replacement protects one file or store at a time. It is not a multi-file
transaction. Managed stores return to mode `0444` after writes.

<!-- Section aliases retained for existing links. -->
<a id="1-idempotency-first"></a><a id="10-ai-as-a-baseline-not-a-finisher"></a><a id="11-tiered-context-budgets"></a><a id="12-explicit-typing-and-code-clarity"></a><a id="13-predictable-c89-structural-conformity"></a><a id="14-continuous-linting-and-validation"></a><a id="15-full-binary-scope-beyond-text"></a><a id="16-automated-near-miss-promotion"></a><a id="17-source--metadata-separation"></a><a id="2-config-driven-execution"></a><a id="3-composability-and-modularity"></a><a id="4-verdict-fidelity-no-silent-status-loss"></a><a id="5-byte-identical-ground-truth"></a><a id="6-safe-by-default-shadow-workspaces"></a><a id="7-the-snowball-effect-iterative-enrichment"></a><a id="8-bi-directional-synchronization"></a><a id="9-rag-over-hallucination"></a><a id="atomicity"></a>
