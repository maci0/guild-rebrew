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
- **Cost:** uncached input, output and cached input tokens of the lane's whole session, priced as
  above. Sources: Codex rollouts, Claude Code transcripts, OpenCode's session totals, and
  Antigravity's conversation databases (`gen_metadata`, protobuf field 1.4, decoded without a
  published schema; 7 of 9 turns the agent host recorded for lanes 80 and 81 equal runs of
  generations exactly). The agent host's own per-turn log is not used: it drops interrupted turns.
  Claude cache writes are priced as uncached input.
- **Value:** API-equivalent dollars per `RELOC`/`EXACT`. Lower is better.

## Known limits

- 30 functions per model separates large differences only; a gap of one or two matches is noise.
- Opus's draw holds fewer `NEAR_MATCHING` rows (4 of 30, against about 8 for the others), which
  makes its sample harder.
- Every row was tried before by earlier matching rounds, so all models work leftovers. Absolute
  rates are lower than on fresh rows; the comparison between models is what the round measures.
- Usage limits can park a model before it finishes; its rate then covers fewer rows.

## Ladder (provisional)

Which model to try first on a function, and when to hand it on. Trying rungs in order of successes
per dollar costs least per match when failures at one rung say little about the next; that
independence is assumed, not measured. Snapshot of round 1 at 07:20 UTC on 2026-11-25, before
batch r5b90; costs include work whose keeps were not committed yet.

| Model | Rows tried | `RELOC`/`EXACT` | Dollars per row | Matches per dollar |
| --- | ---: | ---: | ---: | ---: |
| Claude Opus 5.5 | 24 | 4 | 0.98 | 0.17 |
| Claude Sonnet 5.5 | 30 | 1 | 0.25 | 0.13 |
| GPT 6.2 Sol | 30 | 1 | 0.40 | 0.08 |
| Gemini 4 neon | 30 | 2 | 1.12 | 0.06 |
| Gemini 4 argon | 20 | 1 | 1.08 | 0.05 |
| Gemini 4 hydrogen | 30 | 1 | 0.89 | 0.04 |
| GPT 6.1 Terra | 30 | 0 | 0.21 | 0 |
| MiniMax M3.1 flash | 30 | 0 | 0.04 | 0 |
| GPT 6 Luna, Claude Haiku 5.5, DeepSeek v4.1 flash | 90 | 0 | 0.02 | 0 |

Rungs to test:

1. **No model:** `rebrew cross-import` from a matched twin, flag sweeps and Rebrew's genetic search.
2. **A model at about 2 cents per row.** None of the four cheapest matched one of 120 hard rows. At
   that price a 1% success rate would already beat every row of the table, and 0 of 120 does not
   rule out 2%.
3. **A middle rung:** Sonnet, Sol or a Gemini model.
4. **Opus**, for rows the others failed.

Handover rules:

- After two or three trials without a rise in aligned pairs, hand the row on with its trials and
  notes. The next model reads them and repeats none.
- A model does not retry a row it already failed.
- A held-back keep (one that lowers a stored status) counts as a failure, and the row moves on.
- Prices here are API-equivalent. Subscription limits also decide the rung: a model whose quota is
  scarce is kept for rows that need it.

Not settled: the order rests on one to four matches per model, all on rows earlier rounds had
tried. Round 2 measures first attempts, drawn from the Gold functions that have no source yet
(2,110 of 4,768 inventory entries on 2026-11-25). In earlier work Gemini 4 hydrogen's committed
`RELOC`/`EXACT` results came mostly from first bodies: 18 of 27 started from `STUB` or no verdict.

## Results

Round 1 is running. This section gets each model's rows finished, `RELOC`/`EXACT`, success rate,
API-equivalent cost and cost per match when it ends.
