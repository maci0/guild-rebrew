# Rebrew design principles

## 1. Idempotency First

Repeating a command with unchanged inputs must be safe. Identical writes preserve
content and timestamps; retries must not destroy evidence.

## 2. Config-Driven Execution

Resolve project inputs from `rebrew-project.toml`. CLI overrides must remain
explicit and reproducible.

## 3. Composability and Modularity

Expose focused operations through `rebrew <command>`. CMake and objdiff use
`rebrew build driver` and `rebrew build objdiff-driver`; do not add duplicate
`rebrew-*` executables.

## 4. Verdict Fidelity (No Silent Status Loss)

Record measured improvements and regressions. Respect SKIP and preserve earned
verdicts on tooling failure. PROVEN is semantic evidence, replaced by the next
byte verdict. Placeholder-size results must not erase an existing STUB.

## 5. Byte-Identical Ground Truth

Use complete reference/object/raw-image comparisons for the corresponding claim.
A score, rename or comment edit earns no verdict; reverify changed inputs.

## 6. Safe by Default (Shadow Workspaces)

Probe in scratch, preserve known matches, and verify every affected target before
adopting a source, declaration or compiler change.

## 7. The Snowball Effect (Iterative Enrichment)

Start with well-supported, tractable work. Feed verified names, types, calls and
library identities back into the canonical catalog.

## 8. Bi-Directional Synchronization

BinSync carries native names, signatures, comments, locals, globals and types.
Rebrew owns statuses, flags, blockers and verification. Preview/failure must not
advance a shared baseline; remote deletions require explicit resolution.

## 9. RAG over Hallucination

Retrieve addresses, offsets, conventions and ownership from native evidence and
canonical inputs. Derived coverage and declarations are not evidence owners.

## 10. AI as a Baseline, Not a Finisher

Use generated code as a hypothesis. Native review, compiler comparisons and
bounded matching tools decide whether it holds.

## 11. Tiered Context Budgets

Prioritize referenced types, callee contracts and direct native evidence over
distant context. Retrieve more when a concrete question requires it.

## 12. Explicit Typing and Code Clarity

State evidenced calling conventions, widths and precision. Prefer clear control
flow, preserving compiler-sensitive forms where measurements require them.

## 13. Predictable C89 Structural Conformity

Follow the selected compiler's language constraints. For C89, declare locals at
block top; verify emitted code after changing control flow or declarations.

## 14. Continuous Linting and Validation

Lint source/store edits and compare changed compile inputs. ADDRESS anchors bind
the next declaration; identity and state belong in format-2 managed metadata.

## 15. Full-Binary Scope (Beyond `.text`)

Check code, data, virtual layout, headers, imports, exports, resources and
relocations. Report file agreement, accounted text and stored data verdicts
separately. Count overlapping data once; BSS has no file-backed payload.

## 16. Automated Near-Miss Promotion

Use bounded, delta-ordered matching for eligible near misses. Promote only from
actual comparison results, never the search budget or a proposed source shape.

## 17. Source / Metadata Separation

Locked writers own function/data/source/type stores. Registration preserves
existing evidence; edit stamps, external origins, verification and caches remain
separate. Never hand-edit managed stores or put STATUS in C.

## Atomicity

Source rewrites use atomic replacement. Managed stores use locked atomic writes
and return to mode `0444`. Atomicity is per file/store, not a multi-file transaction.
