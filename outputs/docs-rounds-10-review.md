# Internal review: `docs/*` (round 1 of 10)

Pre-trust critique of the guild-rebrew documentation corpus. Not a publication decision. Question: would these files mislead an agent reversing `server.dll` against MSVC 6.0 SP6?

**Trust rule for this round.** Treat `scripts/gate.sh` defaults and `docs/TODO.md` continuation notes (from the Round-896 heading) as the live floor. Treat frozen session maps, present-tense cookbook headings after `docs/TODO.md` ~L19110, and early allocator “Practical recipe” / “fenced-naked” bodies as archive unless a later section or `src/rebrew-functions.toml` confirms them.

External literature APIs (arXiv, OpenAlex, Europe PMC, Hugging Face, AlphaXiv): **N/A / blocked**. This is a local empirical cookbook, not a paper.

---

## Summary Assessment

**Revision priority: high for agent-facing headers and indexes; low for the measured mechanisms.**

The corpus is a real lab notebook: VA-keyed, full of negative results, and unusually honest about object-score lies. The scientific core (linked residue over `match_count` / `aligned`; CFLAGS are per-file; PROVEN is not a byte match; `volatile` has a direction; some encodings are not reachable from C) is supported by named functions, probe counts, and gate tables.

What fails pre-trust is *navigation and supersession*. An agent told to “read the docs” hits, in order: a 1.4 MB `TODO.md` whose “CURRENT STATE” header is 465 rounds stale; a 158-section shapes file with four reused section numbers; an allocator cookbook whose probe recipe and “8168 will not reproduce” findings describe a compiler the tree no longer uses. Those faults do not falsify the later measurements. They will waste rounds, land worse links, and reopen closed functions.

Fix the keys first (current numbers, unique section IDs, “do not retry” banners, toml as status source of truth). Do not rewrite the lab notes.

**Headline numbers to use (verified this round unless marked):**

| Quantity | Live value | Source |
|---|---|---|
| verify `passed` | 281/283 | `scripts/gate.sh` `BASELINE`; TODO continuation |
| byte-matched (EXACT+RELOC) | 264 | `BYTE_BASELINE`; shapes §93 |
| `.text` residue | 8,634 | `RESIDUE_BASELINE`; TODO L82/L345 |
| raw-link `.data` divergence | 21,836 | `DATA_BASELINE` |
| imports | 100 | PE parse of `original/Server/server.dll`; AGENTS.md |
| reference `.text` VirtualSize | `0x22846` | PE parse; `docs/general-knowledge.md` |
| reference file size | `0x46000` | PE parse; `docs/msvc6-link-layout.md` |
| exports | `Init` `0x10009320`, `Exit` `0x10009350` | PE parse; general-knowledge |

`scripts/gate.sh` *comments* still say residue 8636 (round 516) and `.data` 22,266 (round 519). Values at L78/L85 are the ones the gate actually uses.

---

## Strengths

1. **Linked residue is the adjudicator.** `docs/measure-traps.md` §1–§2, `docs/msvc6-c-shapes.md` §19/§79/§94/§118, allocator Finding 59, and AGENTS.md all converge on: object `match_count` / `aligned` / `matched-reloc` can point the wrong way; one candidate, one rebuild, one number; `scripts/linktest.sh` is the ruler. This is the corpus’s main contribution and it is evidenced (hoist that rose `aligned` 662→665 while linked residue +42).

2. **Negative results are kept.** Flag sweeps, GA stagnation, declaration-order inertness on named sites, eight return spellings that still fold epilogues, six-site memset-prelude conversion costing +108,180 residue. Walls §6b’s gate table (round 889) is a model of “exhausted, not abandoned.”

3. **Self-correction exists.** Shapes §52 supersedes §50’s “no lever” on the 16-bit zero-extend; §94 corrects a header CFLAGS sweep; §98/§99 catch a measuring-script vs postlink drift; §101 corrects §100’s whole-TU `.data` plan; allocator Finding 59 has an amendment (even if filed under Finding 61).

4. **Reference PE geometry is exact.** `docs/msvc6-link-layout.md` §1 table and `docs/general-knowledge.md` match a parse of `original/Server/server.dll` this round (sections, VirtualSizes, raw sizes, file size, image base, 100 imports, Init/Exit VAs).

5. **Agent-process traps are short and true.** `docs/workflow-traps.md`: no probe files in `src/` (CMake GLOB), no `git add -A`, no measure-while-write, `lib-match` not FLIRT (9/68), inverted-`volatile` brief vs shapes §52.

6. **Semantic honesty.** Shapes §110 and `docs/behavioral-verdicts.md` both record the shipped `gm_AllocSpieler` slot[9] bug and the unlandable correct spelling. Walls §6b marks the asm-prelude judgement as judgement.

7. **Lookup tool exists.** `scripts/whathas.py` indexes the VA-keyed docs, which is the right index for a 35k-line corpus. AGENTS.md already tells agents to run it before probing.

---

## Critical Issues

These undermine validity of *guidance an agent will act on*, not of the underlying measurements.

### C1. `docs/TODO.md` “CURRENT STATE” is not current
**Confidence: 1.0**

`docs/TODO.md:3–5` labels itself “kept current” and freezes **rounds 254–431 (2026-09-14; residue 9,209 → 8,666)**. Continuation notes at L50 start at **Round-896** and repeatedly measure residue **8,634**, verify **281/283**, byte-matched **264**, `.data` **21,836**. Next `##` after CURRENT STATE is ~L19110: the H2 swallows ~19k lines of newest-first diary.

The frozen map also overclaims inside its own window: “14 landed wins” lists 11; “no spelling change has ever landed” is a 254–431 snapshot, not tree law; “data tools N/A” is false after the data pass; CrashDump is counted as a live bug while labelled FIXED.

**Why it matters.** Agent who stops at L48 works to residue 8,666, skips `DATA_BASELINE`, and treats order-only / no-spelling as standing law.

**Fix.** Collapse L3–L48 to a 20-line dashboard that copies `gate.sh` defaults and points at the latest continuation heading. Demote L5–L48 to “Session map, rounds 254–431 (archive).” Put a TOC of the last ~20 rounds at the top.

### C2. AGENTS.md still states a `.text` shortfall the docs already retracted
**Confidence: 0.95**

AGENTS.md:196–197: `` `93ecf29` … linked 0x1edc2 — 0x3a84 short, which is the state the tree is in today. See `docs/TODO.md`, "`.text` link shortfall". ``

Shapes §98 L3887 already: that AGENTS line is stale; at *that* writing the split-link **overshot** `0x22ac8` vs `0x22846`. TODO continuation / Round-888 reports built VirtualSize **exact `0x22846`** with residue 8,634. This round’s `.scratch/server.dll.prelayout` has `.text` VSize **`0x221f6`** (short by `0x650`) — a third era.

Three “today” numbers, two still written as current. README.md:83 is a fourth (verify 278/280, 330 byte-exact).

**Why it matters.** Agent may try to “recover 0x3a84 of `.text`” that is not the live problem, or chase the archived shortfall essay TODO still advertises in README.

**Fix.** Replace AGENTS “today” paragraph with: compare built `.text` VirtualSize to `0x22846`; if short, code is missing; if over, postlink trims. Cite `gate.sh` residue, not a commit hash. Demote TODO’s shortfall `##` to past tense. Update README counts from `gate.sh`.

### C3. `docs/msvc6-c-shapes.md` reuses section numbers 16, 34, 35, 36
**Confidence: 1.0**

| N | First | Second |
|---|---|---|
| 16 | L579 call skeleton | L727 `match_count` positional (restates §19) |
| 34 | L1208 RELOC hides wrong global | L1394 SIB base/index |
| 35 | L1238 row multiply vs offset | L1419 PROVEN lost by STUB |
| 36 | L1274 outer-call argument form | L1437 false RELOC (overlaps first §34) |

Integers 1–158 are all present (no gaps). Order anomaly: §117 L5036 then §116 L5107.

Cross-refs poison this: L1188 “section 16” for match_count realignment hits the *first* 16. “Sections 34 and 36” is ambiguous (wrong-symbol vs SIB / outer-call). AGENTS.md “sections 19, 116, 118” for rulers: 116 is the CrashDump hoist; the worked `match_count` vs `aligned` vs +42 link is 118.

**Why it matters.** The file’s contract is “look the address up; sections are the catalogue.” Duplicate IDs make `see §16` a random draw.

**Fix.** Renumber the second 16 as a pointer to §19 (or delete it). Merge the two RELOC-wrong-symbol sections. Give SIB and PROVEN-lost-by-STUB new numbers. Add a 20-line index: N → one-line rule + one VA.

### C4. Allocator methodology and “Practical recipe” describe a different compiler and a steerability the walls doc retracts
**Confidence: 0.9**

`docs/msvc6-allocator.md:6` image `rebrew/msvc:6.0-win32`. L20–26 recipe: `cd build; cp /tmp/probeNN.c _v.c; /home/maci/.local/bin/rebrew-cmake-cl ...`. `_v.c` appears only here. Findings 24–36: “MSVC6 8168 will not reproduce.” L881 distinguishes 8168 vs SP6 8804; later findings ignore it. Complements `rebrew/docs/codegen/msvc/msvc-6.md`, **not in this workspace**.

L211–228 “Practical recipe” presents flag `dl`/`bl`, post-loop `return 0` merge, and `-1` form as general matching C. That is `gm_ff_Objekt` (0x10016460). `docs/codegen-walls.md` §1: register allocation and scheduling are not steerable from C. Later Findings 52–65 agree (homes unsteerable; `volatile` is per-variable). Toml: `["SERVER.0x10016460"] status = "RELOC"`.

Sampled stale “fenced-naked / blocked” vs toml RELOC: `m_pool_free` 0x10006e30, `sim_PriorityUpdate` 0x10015400 (the *earlier* H2 at L524 already says CONVERTED RELOC 83/83; Finding 26 still reads open), `sim_StartEntityQueryByType` 0x10015460.

**Why it matters.** Agent compiles with the wrong image, hardcoded path, and `_v.c`; or re-attacks closed RELOC functions; or spends a round on “first-tested flag is `dl`” as GRA law.

**Fix.** Banner at top: Findings 1–8e and the recipe are `gm_ff_Objekt` lab notes; current GRA policy is walls §1 + Findings 52–65; status = toml. Replace the recipe with `scripts/probe_function.py` + `scripts/linktest.sh`. Spell the docker tag `rebrew/msvc:6.0-sp6-win32`. Quote or vendor `msvc-6.md`.

### C5. Early shapes `volatile` / object-score wins vs later “aligned win, link loss”
**Confidence: 0.95**

Shapes §8c/§22/§30 teach `volatile` as a pin that closes match_count. §52: the 16-bit idiom is selected by the qualifier; *removing* it yields the reference `xor`/`mov`. §94: three-for-three (four-for-four) `volatile` raises `aligned` and **loses at link** (`m_AllocTracked` +40, `gm_AllocSpieler` +2, `gm_FindNextFilteredEntity` +51 body). Workflow-traps: an inverted brief wasted 14 probes.

§58 L2247: “`/Oa` and `/Ow` are load-bearing on `gm_AllocSpieler`.” §94 L3669–L3671: “`/Ow` is load-bearing … **`/Oa` is entirely inert**.” §49 L1984 still points forward to §58 as the supersession.

**Why it matters.** Agent who reads the first 30 sections sprinkles `volatile` and `/Oa`, then ships a worse link. This is the exact class of mistake the later docs exist to prevent.

**Fix.** Banner on §8a/§8c/§22/§30: object-only; default expect link loss (§94); qualifier direction is §52. One sentence in §58: “`/Oa` inert; `/Ow` load-bearing. §49 `/Oa-` row and this paragraph superseded by §94.”

---

## Major Issues

### M1. Shapes how-to-probe is not the measured pipeline
**Confidence: 0.9** — `docs/msvc6-c-shapes.md:16–28`

Isolated `.scratch` + `rebrew-cmake-cl /nologo /c /MT /O2 /Gd probe.c` is a *mechanism* probe. `scripts/probe_function.py` compiles the real file with includes, `-DREBREW_ALLOW_NAKED`, WIN32 defines, and metadata cflags; CMake can pin a file to sp5-pp (`measure-traps` §5: verify reports a compile that does not ship). L12 `rebrew diff <VA>` — CLI is `rebrew diff <file>`. L605 `.scratch/seg.py` does not exist. L683 `rebrew/src/rebrew/core/matching.py:488` is not in this repo.

**Fix.** How-to-probe: `python3 scripts/whathas.py 0xVA` → `python3 scripts/probe_function.py` → `bash scripts/linktest.sh <file.c>`. Label isolated `.c` as not link-valid.

### M2. `docs/msvc6-link-layout.md` “built (now)” row is stale
**Confidence: 0.95** — L301–303 vs parse this round

Doc: built-now file `0x3e000`, `.rdata` raw `0x4000`, `.reloc` raw `0x8000`. Current `.scratch/server.dll.prelayout`: file **`0x3d000`**, `.rdata` raw **`0x3000`**, `.reloc` raw `0x8000`, `.text` VSize **`0x221f6`**. Reference table is still exact.

Prefix surplus `0x1c8` (L173–176) **not re-diffed this round** — needs evidence.

**Fix.** Re-run §7 recipes; replace “now” with a dated dump. Keep the three linker rules; they still hold on the reference.

### M3. Allocator Findings 9–11 missing; Finding 8* disordered; ~48 unnumbered H2s
**Confidence: 1.0** — `docs/msvc6-allocator.md`

Sequence: 1–7, 8b, 8d, 8c, 8, 8e, then a jump to 12. No 8a. No 9–11 (zero mentions). Per-function notes L430–1657 sit between 8e and 12 and later reappear as numbered findings with different status.

**Fix.** Do not invent 9–11. Insert a jump note. Promote or delete the unnumbered H2s. Status line on each: toml value + date.

### M4. `docs/behavioral-verdicts.md` overclaims coverage; residue column frozen
**Confidence: 0.85**

L3: “Every function carrying linked `.text` residue has an explicit behavioral verdict as of rounds 288–297.” Table is 19 named carriers. Score 19/19 is internally consistent. Per-function residue (Spieler 2861, CrashDump 1597) is a snapshot; later TODO cites Spieler 2,685 / 2,824. Method (ignore GRA walls; hunt constants/offsets/args) is sound and unreplicated this round — the *verdicts themselves* are **needs evidence** for anyone who did not do those instruction reviews.

**Fix.** Title as “19 largest residue carriers, rounds 288–297.” Drop per-function residue or mark “as of round N.” Keep the two live Spieler bugs; they are independently documented in shapes §110.

### M5. `docs/general-knowledge.md` cites a heading that does not exist
**Confidence: 1.0** — L21 “codegen-walls §needle-2”

Intended target is walls §7 item 2 (“What would actually move the needle”), which is **CLOSED** (SP6 confirmed, flag axis flat, three sp5-pp pins, do not re-open). The general-knowledge bullet still says per-file flag variance is “suspected but unattested.”

**Fix.** Point at walls §7.2. Replace “unattested” with “swept; three file pins remain.”

### M6. Shapes §32 / §35 / §93 split the PROVEN rule; early closures still look like wins
**Confidence: 0.85**

Together they match AGENTS.md: PROVEN is not a byte match; `passed` folds it (264+17=281); a STUB overlay is a real regression; chase `delta` not percentage. An agent who reads only §32 will edit PROVEN for match_count. Early sections still report match_count jumps as closures without a link number.

**Fix.** Merge into one boxed rule at the top of shapes. Demote early scores to “object-only.”

### M7. Present-tense cookbook in `docs/TODO.md` after L19110
**Confidence: 0.9**

Headings such as “`.text` link shortfall,” “The CMake `.text` shortfall is substitution,” “The IAT is in slot order now” read as live. They are 2026-09-11..13 lab notes. README still advertises “Open work and the `.text` link shortfall.”

**Fix.** Prefix those `##` with “Archive (round N).” Point README at the continuation notes, not the shortfall essay.

### M8. Shipped semantic / encoding trades are easy to “fix”
**Confidence: 0.9** — shapes §110, §80; verdicts row `gm_AllocSpieler`

Correct `slot[9] = (char)arg8` measured +393 linked. xor-xor vs xor-then-or is a known dishonest encoding that paid −12. Correctness-seeking agent will revert both.

**Fix.** Already stated in §110. Lead the function file header with `WARNING: do not correct; see shapes §110`. Repeat in the CURRENT STATE dashboard.

---

## Minor Issues

### m1. Evidence-thin numbered shapes entries
**Confidence: 0.8** — §6, §8 (no VA), §10 (AssignProductionSlot, no VA), §18, second §16, §55 (“candidate's VA was not recorded”)

Cookbook contract is “each with a verified call site.” Thin entries get over-applied (loop shape as universal; §8 is 4 lines).

### m2. Walls §1 “declaration / statement order inert” vs shapes §9 / §33 / §84
**Confidence: 0.85**

Not a true contradiction if scoped: walls named CrashDump / CheckInventory / ExSell slot transposition; shapes named first-use and sink-definition on other functions. Without a banner, agents pick one law.

**Fix.** Walls §1: “homes and equal-count slot transpositions. Statement/definition order remains a lever for *which value* is computed where (§84).”

### m3. Finding 59’s REL32-call amendment lives under Finding 61
**Confidence: 1.0** — allocator L3112+

`measure-traps.md` §3 already cites “Finding 59 and its amendment.” Agent who stops at 59 over-attributes DIR32.

### m4. Finding 52 truncated VA `0x128f0`
**Confidence: 1.0**

Real `0x100128f0`. `whathas.py` on the short form misses it.

### m5. Naming-conventions RevEng reproduction is gated
**Confidence: 0.8** — `docs/naming_conventions.md:401–409`

Hardcoded analysis id `1468081` + `$REVENG_API_KEY`. Fallback (`rebrew asm` + string push) is described. Attested-name table claims disassembly confirmation — **needs evidence** per row; method is sound.

Merged tree section is labelled speculative. Keep.

### m6. Shapes §158 ends mid-data-pass; residue cited 8,636
**Confidence: 0.8**

Live gate 8,634. “Next miss” CrashDump COMDATs may still be live; the number is not.

### m7. `docs/msvc6-c-shapes.md` §8 loop-shape has no VA
**Confidence: 0.75**

§57 later bounds when loop shape is a lever. §8 still reads as step-zero for every function. Walls §2 (epilogue merge) is the actual wall for “reference keeps N rets.”

### m8. Workflow-traps L40–42 vs verdicts CrashDump
**Confidence: 0.7**

Same incident (AnalyzeInstruction arg-swap), consistent if read together. One-line cross-link would save a reread.

### m9. `IAT size 0x1a0` vs “100 imports”
**Confidence: 0.9** — not a bug

104 dwords = 100 imports + 4 DLL-terminating zeros. Link-layout §3 already writes “100 imports * 4, padded.” Fine if an agent does not divide and expect 104 APIs.

### m10. Duplicate PROVEN essays (§32 and §93)
**Confidence: 0.8**

Content agrees. Cost is length. Merge.

---

## Nits

- `docs/TODO.md` two “start here” sentences (L3 vs L50). L50 is the real one.
- Allocator Finding 8\* order is 8b, 8d, 8c, 8, 8e.
- Shapes §117 before §116.
- `auxillary` in naming_conventions is original `__FILE__` spelling — do not “fix.”
- gate.sh header comment “three checks” vs four checks in the body.
- Caveman/ponytail: do not add a fourth codegen doc. Index the three plus traps/walls.

---

## Inline Annotations

Tied to document sections. Format: `file:§ or L — issue`.

### `docs/TODO.md`
- **L3–L5** — C1. “kept current” / residue 8,666 / rounds 254–431. Archive it.
- **L13–14** — “no spelling change has ever landed.” Window-scoped; not tree law.
- **L43** — “data tools N/A.” False.
- **L45–46** — verdicts 19/19 true as of 297; CrashDump is not a live bug.
- **L50** — actual current start. Promote.
- **L82 / L345** — live floor 8,634 / 281 / 264 / 21,836. Dashboard material.
- **~L19110+** — M7. Present-tense archive. Demote.

### `docs/msvc6-c-shapes.md`
- **How to probe L16–28** — M1. Not the ship path.
- **§8 L226** — m1/m7. No VA; walls §2 is the epilogue wall.
- **§12 L449** — still true; AGENTS.md cites it correctly.
- **§16 L579 vs L727** — C3. Two different rules, one number.
- **§19 L680** — keep; this is the positional-score warning AGENTS wants.
- **§32 / §35 L1419 / §93** — M6. Merge PROVEN rule.
- **§34 L1208 vs L1394; §36 L1274 vs L1437** — C3.
- **§49 L1984 vs §58 L2247 vs §94 L3669** — C5. `/Oa` load-bearing then inert.
- **§52** — keep as the `volatile` direction law; banner the earlier volatile sections to it.
- **§58** — C5.
- **§94** — keep as the link-vs-aligned law; this is what early volatile sections lack.
- **§98 L3887** — C2. Already called AGENTS 0x3a84 stale; AGENTS never absorbed it. Overshoot `0x22ac8` is itself no longer “now.”
- **§110** — M8. Keep; surface it.
- **§116 / §117 / §118** — C3 order; 118 is the worked linktest example.
- **§139 / §142 / §150 / §158** — M6/m6. Headline residues 8652 / 8636 / 8633 are historical.

### `docs/msvc6-allocator.md`
- **L6, L20–26** — C4. Wrong image tag, hardcoded path, `_v.c`.
- **L10** — missing `msvc-6.md`. Completeness.
- **L211–228** — C4. Recipe overclaims steerability.
- **Findings 1–8e** — `gm_ff_Objekt` lab. Toml RELOC.
- **Gap after 8e** — M3. No 9–11.
- **Findings 24–36 “8168 will not reproduce”** — C4. Project is SP6 8804.
- **Finding 25/26/27 vs H2 L524 / toml** — C4. Status drift.
- **Finding 52 `0x128f0`** — m4.
- **Finding 59 vs amendment under 61** — m3.
- **Findings 52–65** — keep as current GRA policy.

### `docs/codegen-walls.md`
- **§1** — keep as default for *homes*; add pointer to shapes §84 for definition order (m2).
- **§2 / shapes §74** — consistent epilogue-merge wall.
- **§3 / shapes §52** — consistent `volatile` direction.
- **§6 / §6b** — keep; gate table is the constraint cost.
- **§7.2** — closed needle. general-knowledge still cites “§needle-2” (M5).
- **§8** — measured floor of the constraint set; do not reopen without new evidence.

### `docs/measure-traps.md`
- **§1–§3** — keep. Ceiling table (`cm_ExProdObjekt` / `cm_ProcessCommandQueue` at `matched-reloc` ceiling) is the object-score kill shot.
- **§4 L53** — Spieler 2,861 is verdicts-era; mechanism (“residue is distance from first divergence”) still holds.
- **§5 toolchain pin** — keep; this is why isolated `/O2 /Gd` probes lie.
- **§6 / 6b–6f** — recent and aligned with TODO continuation.
- **§9 cmake --build deletes server.dll** — keep; independently in TODO L350–355.
- **§10** — keep as the “how to check a claim” section.

### `docs/msvc6-link-layout.md`
- **§1 table** — verified against the reference PE. Keep.
- **§3 prefix surplus 0x1c8** — needs evidence (not re-diffed).
- **§6 postlink overwrite table** — still the right contract (`.data` blit makes “`.data` differing 0x0” a tautology — TODO later notes this).
- **L301–303 “built (now)”** — M2. Stale.
- **§7 recipes** — keep; they are how to refresh the stale row.

### `docs/behavioral-verdicts.md`
- **L3 “every function”** — M4.
- **Spieler row** — consistent with shapes §110. Keep.
- **CrashDump “fixed at +0”** — consistent; TODO frozen map garbles it.
- **Score 19/19** — snapshot, not a live residue dashboard.

### `docs/naming_conventions.md`
- **Source tree / `__FILE__`** — method is right (debug strings). Speculative merged tree is labelled.
- **Attested names + RevEng** — m5. Gated reproduce; local confirm path exists.
- **Calling convention `__cdecl`** — matches AGENTS.md.

### `docs/workflow-traps.md`
- Keep as-is after adding a pointer at L3 to measure-traps §1 and walls §6b.
- L21–23 inverted-volatile brief: the existence proof that C5 is not hypothetical.

### `docs/general-knowledge.md`
- Image base, exports, 100 imports, `.text` 0x22846, zlib path — verified.
- **L21 §needle-2** — M5.
- Per-file flags “unattested” — stale vs walls §7.2.

### `AGENTS.md` / `README.md` / `scripts/gate.sh` (not in `docs/*` but agents read them first)
- AGENTS “0x3a84 short … today” — C2.
- README 278/280 and 330 byte-exact — C2.
- gate.sh comments 8636 / 22266 vs values 8634 / 21836 — stale comments, live values OK.

---

## Claims flagged as needing evidence

| Claim | Where | Status this round |
|---|---|---|
| 19 instruction-level behavioral verdicts | `behavioral-verdicts.md` | Method stated; reviews not re-done. Treat as unreplicated. Spieler bug independently evidenced in shapes §110. |
| Prefix surplus `0x1c8` still present | link-layout §3 | **Needs evidence.** Prelayout `.rdata` raw is now `0x3000`, so the surplus story may have moved. |
| Attested-name table, every row pushes the literal | naming_conventions | Method described; rows not re-disassembled. |
| Finding 59 HIGHLOW counts (SMT 128 vs 56) | allocator L3040–3047 | Not re-counted. Mechanism agrees with measure-traps §3. |
| sp5-pp “3 pins, 16 of 16 unpinned worse” | walls §7.2 | Not re-run. Do not reopen without a new sweep. |
| `matched-reloc` already at ceiling for ExProd / PCQ | measure-traps §3 table | Not re-scored. |
| Current split-link `.text` VirtualSize | AGENTS / TODO / shapes §98 | **Conflicting “today” values.** This round’s prelayout is `0x221f6`. Re-measure with `scripts/section_geometry.py` before citing any of them. |
| `rebrew/src/rebrew/core/matching.py:488` | shapes §19 | Path not in this repo. Mechanism (positional compare, reloc mask) is consistent with tool behavior described elsewhere. |

---

## Methodology / confounds / design / reproducibility / completeness

**Claims vs evidence.** Strongest where a VA, a probe count, and a link delta co-occur (walls §6b, shapes §94/§110/§118, measure-traps §3/§6). Weakest where a heading is a universal law with one function or none (§8, allocator recipe, TODO “no spelling change”).

**Confounds.** The corpus itself names the main ones: positional `match_count`, one-sided REL32, COMDAT padding vs real body, CMake pin ignored by `rebrew test`, measuring while agents write, `cmake --build` destroying split state, postlink blit making non-`.text` diffs tautological. That is good science. The confound that remains *in the docs* is supersession: later measurements do not invalidate earlier headings.

**Experimental design.** No formal baselines/ablations in the paper sense. Informal design is actually good: one variable per probe, negative results kept, constraint cost measured through `gate.sh`. Missing: a single current scoreboard (residue, byte-matched, `.text` VSize, `.data`, imports) at the front of every long file.

**Reproducibility.** Positive: `whathas.py`, `linktest.sh`, `section_geometry.py`, sizeof compiler checks, PE recipes. Negative: allocator `/home/maci/.local/bin` + `/tmp/probeNN.c`; missing `msvc-6.md` / `matching.py` / `seg.py`; RevEng analysis 1468081; TODO 24k lines with two start-here lines.

**Writing / completeness.** Related work is implicit (MSVC 6.0 CL 12.00, LIBCMT, zlib 1.1.3). Limitations are often present but filed 80 sections after the overclaim. Indexability is the completeness failure: `whathas.py` is the index and is not mentioned in TODO’s header or shapes’ how-to-probe.

**Agent-safety.** Highest-ROI edits are banners and unique IDs, not more prose.

---

## Blocked checks

- arXiv / OpenAlex / Europe PMC / Hugging Face / AlphaXiv: N/A.
- Full `scripts/gate.sh` / docker compile matrix: not run.
- RevEng.AI dump: no key used.
- Prefix-byte re-diff, HIGHLOW recount, attested-name re-disassembly: not run.
- Exhaustive toml-vs-allocator status audit: sampled three VAs (all RELOC as the subagent claimed); remaining listed VAs unverified.
- Isolated `probe.c` compile from the shapes recipe: not executed.
- `whathas.py` behavior on duplicate section numbers: not executed (likely first-heading wins).

---

## Suggested first edits (priority)

1. Dashboard: 20 lines at the top of `docs/TODO.md` copied from `gate.sh` + “start at the latest Round-N heading.” Archive L5–L48.
2. AGENTS.md / README.md “today” numbers: replace with `gate.sh` + “measure VirtualSize, do not cite 0x3a84.”
3. Renumber/merge shapes 16, 34, 35, 36. Banner volatile §§ → §52/§94. Fix `/Oa` in §58.
4. Allocator top banner: recipe deprecated; image SP6; status = toml; Findings 1–8e are one function.
5. Re-run link-layout §7; replace “built (now).”
6. general-knowledge: drop `§needle-2`; point at walls §7.2.

Do not rewrite the lab notes. Do not add a fourth cookbook. The measurements hold; the keys do not.
