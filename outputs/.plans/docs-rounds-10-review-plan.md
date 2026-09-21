# Review plan: `docs/*` (round 1 of 10)

Pre-trust critique of the guild-rebrew documentation corpus. Not a publication decision. Goal: find claims that would mislead an agent reversing `server.dll` / `Europa1400Gold_TL.exe` against MSVC 6.0 SP6.

## Corpus

| File | ~size | Role |
|---|---|---|
| `docs/msvc6-c-shapes.md` | 394 KB / 7335 L | Empirical C shapes that close byte mismatches |
| `docs/msvc6-allocator.md` | 191 KB / 3240 L | Register allocation cookbook |
| `docs/TODO.md` | 1.4 MB | Live work log + open items |
| `docs/measure-traps.md` | 31 KB | Measurement pitfalls (object vs link) |
| `docs/naming_conventions.md` | 23 KB | Symbol / file naming |
| `docs/msvc6-link-layout.md` | 18 KB | Link / layout / postlink |
| `docs/codegen-walls.md` | 15 KB | Known unmatchable codegen |
| `docs/workflow-traps.md` | 4 KB | Process traps |
| `docs/behavioral-verdicts.md` | 3 KB | Residue-function behavioral review |
| `docs/general-knowledge.md` | 1.5 KB | Misc facts |

External APIs (arXiv, OpenAlex, Europe PMC, Hugging Face, AlphaXiv): not applicable. This is a local empirical compiler cookbook, not a paper. Mark those checks **blocked / N/A**.

## Method

1. Inventory headers, TOC, status claims, numeric baselines, VA citations.
2. Sample every numbered section in the three codegen docs; full-read the six small docs.
3. Adversarial checks:
   - Claim vs evidence (cited VA, probe, round, `linktest.sh` delta).
   - Internal contradictions (same VA, two rules; object-score vs link-score).
   - Stale numbers vs `AGENTS.md`, `scripts/gate.sh`, `rebrew-project.toml`, current `src/rebrew-functions.toml`.
   - Missing limitations / scope (CFLAGS per-file, PROVEN vs EXACT, FLIRT vs lib-match).
   - Reproducibility (can a later agent rerun the cited probe).
4. Fan-out: researcher on c-shapes + allocator; reviewer on traps/walls/verdicts/TODO contradictions; verifier on numeric baselines and VA lookups via `scripts/whathas.py` and grep.
5. Write evidence notes, then one final review with severity-graded findings.

## Evaluation axes

- Claims vs evidence
- Methodology soundness / confounds (object `match_count` vs linked residue)
- Experimental design (baselines, ablations, negative results)
- Reproducibility
- Writing clarity / completeness (limitations, related work, indexability)
- Agent-safety: instructions that would waste a round or land a worse link

## Deliverables

- `outputs/.plans/docs-rounds-10-review-plan.md` (this file)
- `outputs/.drafts/docs-rounds-10-review-evidence.md`
- `outputs/docs-rounds-10-review.md` (exactly one final review)

## Out of scope this round

- Re-running the full MSVC docker compile matrix.
- Rewriting the docs.
- Judging game-logic correctness except where a doc claims a behavioral verdict.
