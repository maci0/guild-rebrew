# guild-bench

A head-to-head of coding models on this project's real work: raising reconstructed client
functions to `RELOC` or `EXACT` through the same gate every change passes. It answers one
question: which model gives the most matched functions per dollar of API-equivalent tokens.

This page names models and agent tools by the user's decision (2026-11-25), as an exception to
the project's attribution rule. Status: **round 1 running**; results below are filled in when it
ends.

## Round 1 method

- **Sample.** One pool: every `SIZE_MISMATCH` and `NEAR_MATCHING` row from
  `rebrew todo --json` for both clients with a source file, one row per file (832 rows on
  2026-11-25). The pool is sorted, shuffled with seed `20261125`, and dealt round-robin, 15 rows
  per lane and two lanes per model, so each model gets 30 functions of the same random mix.
  Overall the first 300 rows hold 222 `SIZE_MISMATCH` and 78 `NEAR_MATCHING`. Opus joined
  later and got rows 300 to 329 of the same shuffle (26 and 4).
- **Work.** Each lane follows the project's matching rules: read the native code and the row's
  history, edit only its own file, measure each trial with `rebrew test --source-targets
  --no-promote`, keep a change only when aligned instruction pairs rise without lowering any
  target, and queue the kept file.
- **Gate.** Queued files are recorded in batches. A batch is committed only when both clients
  link, the server raw link stays byte-identical and lint reports 0 findings on all targets.
  A keep that lowers a stored status is held back and counts against the model.
- **Fixed conditions.** Bake-off lanes are never given more rows and never switch model; a lane
  that hits a usage limit parks, and its model is scored on the rows it finished.

| Lanes | Model | Route | API price, USD per 1M tokens (input / output / cached input) |
| --- | --- | --- | --- |
| 78, 79 | Claude Opus 5.5 | Claude Code | 4 / 20 / 0.2 |
| 80, 81 | Gemini 4 hydrogen | Antigravity | 1.5 / 7.5 / 0.075 |
| 82, 83 | Gemini 4 neon | Antigravity | 3 / 15 / 0.15 |
| 84, 85 | Gemini 4 argon | Antigravity | 2 / 10 / 0.1 |
| 86, 87 | DeepSeek v4.1 flash | OpenCode Go | 0.14 / 0.42 / 0.0042 |
| 88, 89 | MiniMax M3.1 flash | OpenCode Go | 0.075 / 0.3 / 0.0075 |
| 90, 91 | GPT 6.2 Sol | Codex | 2 / 10 / 0.1 |
| 92, 93 | Claude Sonnet 5.5 | Claude Code | 2 / 10 / 0.1 |
| 94, 95 | Claude Haiku 5.5 | Claude Code | 0.1 / 0.5 / 0.01 |
| 96, 97 | GPT 6.1 Terra | Codex | 1 / 5 / 0.05 |
| 98, 99 | GPT 6 Luna | Codex | 0.1 / 0.5 / 0.01 |

Prices are the models.dev API catalog on 2026-11-25. They price the tokens each run used, not
what the subscriptions billed.

## Scoring

- **Success:** functions that reach `RELOC` or `EXACT` in a committed batch, over the 30 rows.
  Rises to `NEAR_MATCHING` and held-back keeps are reported beside it.
- **Cost:** every turn's uncached input, output and cached input tokens, priced as above. Turn
  records come from the agent host's per-turn usage log; Codex runs use Codex's own session logs,
  because the host log records only a Codex agent's first turn.
- **Value:** API-equivalent dollars per `RELOC`/`EXACT`. Lower is better.

## Known limits

- 30 functions per model separates large differences only; a gap of one or two matches is noise.
- Opus's draw holds fewer `NEAR_MATCHING` rows (4 of 30, against about 8 for the others), which
  makes its sample harder.
- Every row was tried before by earlier matching rounds, so all models work leftovers. Absolute
  rates are lower than on fresh rows; the comparison between models is what the round measures.
- Usage limits can park a model before it finishes; its rate then covers fewer rows.

## Results

Round 1 is running. This section gets each model's rows finished, `RELOC`/`EXACT`, success rate,
API-equivalent cost and cost per match when it ends.
