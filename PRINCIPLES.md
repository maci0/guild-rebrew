# Rebrew Design Principles

The rules every tool in the Rebrew suite is held to.

## 1. Idempotency First
Every tool in the Rebrew suite (`rebrew coverage catalog`, `rebrew verify`, `rebrew init`, etc.) must be safely repeatable. Running a command twice should not yield a different outcome than running it once. There must be no destructive side-effects when re-running workflows, ensuring that humans and AI agents can safely retry operations.

## 2. Config-Driven Execution
Global and project-specific settings live in `rebrew-project.toml`. Tools must rely on this central configuration rather than requiring complex, manual CLI path arguments. This creates a unified entry point and guarantees that any agent or contributor is working with the exact same context (paths, compiler flags, target binaries).

## 3. Composability and Modularity
Rebrew exposes small, single-purpose tools as subcommands of one installed `rebrew` CLI. Complex workflows chain `rebrew <command>` invocations, which suits AI orchestration and custom batch scripts. Do not add duplicate `rebrew-<command>` executables. Four external build hooks keep separate names because CMake and objdiff invoke them directly.

## 4. Verdict Fidelity (No Silent Status Loss)
Whether driven by a human or an AI agent, the system must **never** silently lose a function's record. The byte comparison stays the only source of a verdict, and any change it produces is written, improvements and regressions alike (`RELOC` -> `NEAR_MATCHING` and `PROVEN` -> `NEAR_MATCHING` are both recorded). Three verdicts are refused: a status parked as `SKIP`, a `STUB` displaced by a placeholder size verdict, and a tooling failure verdict written over an earned status. `PROVEN` records semantic equivalence rather than a byte match, so the next byte verdict replaces it.

## 5. Byte-Identical Ground Truth
"Close enough" is not the goal. The ultimate source of truth is the compiler output. Cosmetic changes (renaming variables, adding comments) are only accepted if `rebrew test` verifies that the resulting `.obj` bytes remain completely identical to the existing matched baseline.

## 6. Safe by Default (Shadow Workspaces)
To prevent corruption of known-good decompilation (`EXACT` / `RELOC` states), experimental generation and compilation must occur in isolated staging areas. Changes are promoted to the main source tree only after passing the byte-matching gates and regression suites.

## 7. The Snowball Effect (Iterative Enrichment)
Success breeds success. Every reversed function immediately enriches the context available to the ecosystem. Tools and agents process the easiest functions first (smallest functions, library matches, single-block leaves), continuously expanding the semantic database. This makes subsequent, harder functions easier to reverse.

## 8. Bi-Directional Synchronization
Local decompilation workflows and reverse-engineering platforms (like Ghidra) must complement each other. Shared native fields (names, signatures, comments, locals, globals, and types) flow through BinSync state. Local STATUS, compiler flags, blockers, and verification evidence remain Rebrew-owned. A binary-scoped shared baseline distinguishes incoming changes from conflicting edits; previews and failures never advance it. Missing remote fields require explicit deletion resolution.

## 9. RAG over Hallucination
AI models infer semantics, but they cannot guess absolute Virtual Addresses (VAs), structure offsets, or proprietary calling conventions. Ground generated code in retrieved evidence: reference binary/disassembly, canonical source and metadata, and derived context/coverage documents. Retrieve addresses, types, and calling conventions from their authoritative source rather than guessing them. Coverage documents are a regenerable view, not the owner of those facts.

## 10. AI as a Baseline, Not a Finisher
The LLM's role is to generate a semantically correct structural baseline. It shouldn't be relied upon to perfectly guess register allocation optimizations or minute instruction jitter. Once the LLM achieves a `NEAR_MATCHING` state with a small byte delta, deterministic programmatic tools (like the Genetic Algorithm) take over to brute-force the remaining permutations.

## 11. Tiered Context Budgets
Context windows are finite and expensive. When injecting RAG context for a target function, a strict priority budget must be enforced. Critical definitions (directly referenced struct types and called function signatures) take precedence over "nice-to-have" context (like the raw assembly of distant caller algorithms).

## 12. Explicit Typing and Code Clarity
Relying on implicit language features introduces hidden codegen discrepancies. Code implementation should favor maximum explicitness to ensure reliable, deterministic output:
- Explicit precision: Always use `__cdecl`, `__stdcall`, and exact variable sizes (`unsigned char` over `char`) matching the original binary.
- Avoid expression tricks: Prefer clear, explicit control flow (`if/return`) over size-optimized but complex expressions (like `(x != -1) - 1`).

## 13. Predictable C89 Structural Conformity
When dealing with older compilers (like MSVC6), code must map directly to compiler idiosyncrasies:
- Variable declarations must stay grouped at the top of a block.
- Logic structure (`if/else` flow, loop choice) dictates the machine code generation directly, requiring rigid adherence over modern "clean code" stylistic preferences.

## 14. Continuous Linting and Validation
Run `rebrew lint` after source/metadata changes and `rebrew test` / `rebrew verify` after changes to compilation inputs. Identity is a `MODULE.0xVA` row (`file` plus a kind). An unmigrated file may still carry an inline marker; do not restore markers to pure-C migrated files, and do not write new ones. STATUS, SIZE, CFLAGS, and other volatile fields are metadata-owned. `// SOURCE: naked` stays source-owned. See the annotation and metadata references for the exact field rules.

## 15. Full-Binary Scope (Beyond `.text`)
A faithful decompilation requires coverage of the *entire* binary, not just executable code. The `.data`, `.rdata`, and `.bss` sections contain globals, dispatch tables, vtables, string tables, and const arrays that are equally critical for correctness. Tools must inventory and cross-reference data-section artifacts (`rebrew data list`), detect dispatch tables / vtables by scanning for contiguous function-pointer arrays, and flag type conflicts across files. Report file agreement, accounted `.text`, and initialized-data verdict bytes with their own denominators. Data buckets must be disjoint even for overlapping symbols. `.bss` has no file-backed bytes; show its symbol/virtual-layout progress separately.

## 16. Automated Near-Miss Promotion
Many `NEAR_MATCHING` functions differ from the target by only a handful of bytes: an operand swap, branch inversion, or register allocation jitter. The system must be able to batch-process these near-miss cases unattended (`rebrew match batch --near-miss --threshold N`), sorted by byte delta so the easiest wins come first. Trivial NEAR_MATCHING→RELOC promotions then happen without a person, who works only on the functions that need one.

## 17. Source / Metadata Separation
Volatile metadata lives in `rebrew-functions.toml` and `rebrew-data.toml` at `cfg.metadata_dir`, shared across targets. CLI writers preserve stable `(module, VA)` identity and validate against the shared schemas. Never manually edit these managed stores or write STATUS in C. SIZE and CFLAGS are metadata-owned. `rebrew source migrate-markers` moves function identity into `rebrew-functions.toml` and data identity into `rebrew-data.toml`, and leaves pure C. New writers do the same. External field origins and verification inputs/measurement time are durable canonical facts, separate from ordinary edit stamps and regenerable coverage/cache files.

## Atomicity

Source-file rewrites (`rebrew lint --fix`, `rebrew skeleton`, `rebrew source rename`,
…) use atomic file replacement (`atomic_write_text`). Tool-owned metadata
(`rebrew-functions.toml`, `rebrew-data.toml`, BinSync state TOML) uses
`atomic_write_locked` (chmod writable, atomic replace, then mode 0444), so a
crash never leaves a torn file and casual hand-edits fail with Permission
denied. Atomicity is per file/store; a multi-file sync is not one transaction.
Identical writes preserve content and timestamps to avoid watch-loop churn.
