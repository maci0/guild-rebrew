# Evidence notes — `docs/*` review (round 1 of 10)

Pre-trust critique. Local empirical compiler / reverse-engineering cookbook. Not a paper.

External APIs (arXiv, OpenAlex, Europe PMC, Hugging Face Hub, AlphaXiv): **N/A / blocked**. No paper ID. No citation graph. No gated dataset.

## Corpus inventory (2026-09-18 worktree)

| File | Lines | Role |
|---|---:|---|
| `docs/TODO.md` | 24672 | Live log + archived cookbook. Dual "start here". |
| `docs/msvc6-c-shapes.md` | 7335 | C shapes that closed byte mismatches. §§1–158. |
| `docs/msvc6-allocator.md` | 3240 | GRA / slot findings. Findings 1–65 with gaps. |
| `docs/measure-traps.md` | 445 | Object vs link measurement failure modes. |
| `docs/naming_conventions.md` | 511 | Original 4HEAD naming, source tree, attested names. |
| `docs/msvc6-link-layout.md` | 371 | PE / LINK / postlink outside `.text`. |
| `docs/codegen-walls.md` | 231 | Exhausted-spelling walls. |
| `docs/workflow-traps.md` | 60 | Agent / process traps. |
| `docs/behavioral-verdicts.md` | 39 | Residue-function semantic review, rounds 288–297. |
| `docs/general-knowledge.md` | 31 | Original project / build / domain bullets. |

## Live baselines (trust these over frozen headers)

From `scripts/gate.sh` defaults:

- `BASELINE=281` (EXACT+RELOC+PROVEN)
- `BYTE_BASELINE=264`
- `RESIDUE_BASELINE=8634` (comment still says 8636 as of round 516)
- `DATA_BASELINE=21836` (comment still says 22266 as of round 519)

From `docs/TODO.md` continuation (round 896, L82–83, L345):

- residue **8,634**, raw-link `.data` **21,836**, verify **281/283**, byte-matched **264**, imports **100**

From `original/Server/server.dll` (parsed this round):

- file size `0x46000` (286720) — matches `docs/msvc6-link-layout.md` and `docs/general-knowledge.md`
- ImageBase `0x10000000`, SectionAlignment = FileAlignment = `0x1000`, SizeOfHeaders `0x1000`
- `.text` VA `0x1000` VSize `0x22846` raw `0x23000`
- `.rdata` VA `0x24000` VSize `0x2e81` raw `0x3000`
- `.data` VA `0x27000` VSize `0x174059c` raw `0xe000`
- `.reloc` VA `0x1768000` VSize `0x10374` raw `0x11000`
- Exports: `Init` VA `0x10009320`, `Exit` VA `0x10009350`
- Imports: 100 across KERNEL32 (81), USER32 (2), WS2_32 (16), WINMM (1)
- IAT size `0x1a0` = 104 dwords = 100 imports + 4 null terminators (one per DLL)

From `.scratch/server.dll.prelayout` (this round, **not** the link-layout "now" row):

- file size `0x3d000` (doc claims built-now `0x3e000`)
- `.text` VSize `0x221f6` (short of `0x22846` by `0x650`)
- `.rdata` raw `0x3000` (doc's "now" row still has `.rdata` raw `0x4000`)
- `.reloc` raw `0x8000`

`scripts/linktest.sh`, `scripts/whathas.py`, `scripts/ndiff.py`, `scripts/cdiff.py`, `scripts/gaptrace.py`, `scripts/reallen2.py`, `references/zlib-1.1.3` all exist.

## `docs/TODO.md`

- Header L3: "CURRENT STATE (kept current; read this before the history below)".
- L5 session map frozen at **rounds 254–431 (2026-09-14; residue 9,209 → 8,666)**.
- L50 continuation: "start here"; first entry **Round-896**.
- Whole-file round mentions: min 17, max **896**, n=1590.
- Next `##` after CURRENT STATE is L19110. CURRENT STATE swallows ~19k lines of newest-first diary.
- L13–14: "Every one is a statement/definition ORDER change; no spelling change has ever landed" — scoped to that 254–431 window if read charitably; continuation and later data-pass sections contradict it as a standing law.
- L45: "verdicts 19/19"; L46 CrashDump listed among "2 live bugs" while labelled FIXED.
- L43: "data tools N/A" in the frozen map; DATA_BASELINE exists.
- Present-tense cookbook after L19110 (e.g. `.text` link shortfall) never demoted.
- AGENTS.md:196 still: "`93ecf29` … linked 0x1edc2 — 0x3a84 short, which is the state the tree is in today. See `docs/TODO.md`, "`.text` link shortfall`"."
- shapes §98 L3887 already: "AGENTS.md's `.text` link shortfall … 0x3a84 short is stale" and at that time claimed **overshoot** `0x22ac8`. Current prelayout is **short** `0x221f6`. Three eras, three numbers, two still written as "today".

## `docs/msvc6-c-shapes.md`

Numbered `## N.` headings: 162 headings, unique 1–158, **no missing integers**.

Duplicates (same number, different titles):

| N | First | Second |
|---|---|---|
| 16 | L579 call skeleton | L727 `match_count` positional (also restates §19 L680) |
| 34 | L1208 RELOC hides wrong global | L1394 SIB base/index |
| 35 | L1238 row multiply vs offset | L1419 PROVEN lost by STUB |
| 36 | L1274 outer call argument form | L1437 false RELOC (overlaps §34) |

Order anomaly: §117 L5036 then §116 L5107.

Thematic duplicates: §32 and §93 both "PROVEN is not a byte match".

AGENTS.md cited sections 12, 19, 116, 118, 127 exist and match the cited topics (CFLAGS per-file; positional `match_count`; CrashDump hoist; hoist scope; ServerMainThread silent no-op). Lookup by number is still hazardous because of the duplicates.

Probe recipe (L21–24) uses `rebrew-cmake-cl` on PATH in `.scratch/` — matches current toolchain wrappers better than the allocator recipe.

Cite `rebrew/src/rebrew/core/matching.py:488` — not in this repo. Exists under sibling checkouts (`/home/maci/Desktop/rebrew-go/...`, cache). Completeness hole, not a false mechanism.

§110 documents the shipped `gm_AllocSpieler` slot[9] semantic bug with bytes and linked cost (+393). Consistent with `behavioral-verdicts.md` and TODO.

§158 ends mid-data-pass ("Next miss" CrashDump COMDATs). Residue cited there as 8,636; live gate is 8,634.

## `docs/msvc6-allocator.md`

Finding headings: 1–7, then 8b, 8d, 8c, 8, 8e. **No 8a. No Findings 9, 10, 11.** Then 12–65. ~48 unnumbered per-function H2s between 8e and 12.

Methodology L20–26: `cd build; cp /tmp/probeNN.c _v.c; /home/maci/.local/bin/rebrew-cmake-cl ...`. `_v.c` unique to this file. Image tag L6: `rebrew/msvc:6.0-win32`. Project default: `rebrew/msvc:6.0-sp6-win32`. Findings 24–36 repeatedly "MSVC6 8168 will not reproduce". L881 does distinguish 8168 vs 8804; later findings ignore that.

Complements `rebrew/docs/codegen/msvc/msvc-6.md` — **not in this workspace**.

Practical recipe L211–228 generalizes `gm_ff_Objekt` GRA (flag `dl`/`bl`, post-loop `return 0` merge). Contradicts `codegen-walls.md` §1 and later Findings 52–65 (homes unsteerable).

Stale status vs `src/rebrew-functions.toml` (sampled):

| VA | Later finding / early note | toml |
|---|---|---|
| 0x10006e30 `m_pool_free` | Finding 25 fenced-naked (allocator audit) | RELOC |
| 0x10015400 `sim_PriorityUpdate` | Finding 26 fenced-naked; H2 L524 already CONVERTED RELOC 83/83 | RELOC |
| 0x10015460 `sim_StartEntityQueryByType` | Finding 27 / H2 blocked | RELOC |
| 0x10016460 `gm_ff_Objekt` | intro target, Findings 1–6 as open GRA | RELOC |

Finding 59 exists at L3035 and agrees with measure-traps §3. REL32-call amendment sits under Finding 61 (L3112+).

Finding 52 truncated VA `0x128f0` for `ls_LoadBuildingEntityState` (real `0x100128f0`).

## `docs/codegen-walls.md`

Strongest "do not retry" document. Exhaustion claimed with named functions, flag lists, and a gate measurement for the asm-prelude constraint (round 889: residue 8,634 → 116,814).

§7 item 2 "needle" is the closed SP6/flag search. `docs/general-knowledge.md` L21 cites **`codegen-walls §needle-2`** — that heading does not exist. Intended target is §7 item 2.

§1 "declaration order is inert" / "statement order is inert" is scoped to named probes; shapes §9 / §33 / §84 still treat order as a lever. Walls later qualify "almost no influence". Agents who read only one file will over- or under-steer.

## `docs/measure-traps.md`

Best methodology doc. Rule "only the linked residue decides" + "one candidate, one rebuild" + relocation ceiling table.

§4 still uses `gm_AllocSpieler` residue **2,861** (verdicts-era). Continuation L267: SMT 367 residue; Spieler later cited 2,685 / 2,824. Frozen example, mechanism still valid.

§6 / 6b–6f are recent (rounds 866–880, 895) and match continuation notes.

§10 "How to check any claim" exists — good reproducibility section.

`cmake --build` alone deleting `server.dll` / split state (round 889, walls + TODO L350–355) is recorded in §9.

## `docs/msvc6-link-layout.md`

Reference PE table: **byte-verified** this round against `original/Server/server.dll`.

Recipes in §7 are runnable (`scripts/section_geometry.py`, prelayout copy story).

Stale "built (now)" arithmetic L301–303: claims `.rdata` raw `0x4000`, file `0x3e000`. Current prelayout: `.rdata` raw `0x3000`, file `0x3d000`, `.text` VSize `0x221f6`.

Prefix surplus `0x1c8` (L173–176) not re-measured this round — **unverified / possibly stale**. Mark needs evidence.

Import count 100: verified.

## `docs/behavioral-verdicts.md`

19 rows, score 19/19, rounds 288–297. Method stated (instruction-level, ignore GRA walls).

Claim L3 "Every function carrying linked `.text` residue" is stronger than the table (19 named carriers as of that era). Per-function residue column is frozen (Spieler 2861, CrashDump 1597) and no longer matches later TODO figures.

"2 live bugs" vs CrashDump "fixed at +0": the TODO frozen map garbles this; the verdicts file itself is internally consistent (Spieler 2 live; CrashDump fixed).

## `docs/naming_conventions.md`

Attested-name table claims verification against disassembly, and records RevEng false attributions. Good.

Reproduction path: RevEng.AI `GET /v2/analyses/1468081/...` + `$REVENG_API_KEY`. Hardcoded analysis id. **Blocked** without that key. Fallback (strings in the binary + `rebrew asm`) is described.

"Merged Source Tree (speculative)" is labelled speculative. `auxillary` spelling preserved from `__FILE__` — good.

Calling convention table (`__cdecl` for game) matches AGENTS.md.

## `docs/workflow-traps.md`

Short, high-ROI. glob `_` exclude, no `git add -A`, no measure-while-write, lib-match vs FLIRT 9/68, inverted-volatile brief (shapes §52).

L40–42 CrashDump `AnalyzeInstruction` arg-swap "deliberate cost of 1 linked byte" vs verdicts "bug 1 verified fixed" — same incident, consistent.

## `docs/general-knowledge.md`

Reference facts (image base, exports, 100 imports, `.text` 0x22846, zlib 1.1.3 path) verified.

Broken cross-ref `codegen-walls §needle-2`.

"/O2 /Gd default … per-file variance suspected but unattested" is itself stale: walls §7 item 2 **CLOSED** the flag/SP search; three sp5-pp pins exist (`measure-traps` §5, CMake pin).

## Confounds / method

Object rulers (`match_count`, `aligned`, `matched-reloc`) vs linked residue: documented repeatedly (shapes §19/§16/§96, measure-traps §1, allocator Finding 59, AGENTS.md). This is the corpus's main scientific contribution. The remaining failure is **not repeating the rule in the files agents open first** (TODO session map, README, allocator recipe).

PROVEN vs EXACT: shapes §32/§93 and gate.sh BYTE_BASELINE agree. README still "330 byte-exact, verify 278/280".

## Reproducibility

Positive: VA keys, `whathas.py`, `linktest.sh`, gate.sh, isolated probe recipe in shapes, PE parse recipes in link-layout, sizeof compiler check in measure-traps §6.

Negative: allocator hardcoded `/home/maci/.local/bin` + `_v.c`; `matching.py:488` and `msvc-6.md` outside repo; RevEng analysis 1468081; probe corpus cited as `/tmp/probe26.c`; TODO 1.4 MB with two start-here lines.

## Checks blocked this round

- AlphaXiv / arXiv / OpenAlex / Europe PMC / Hugging Face: N/A.
- Re-running the MSVC docker compile matrix / full `gate.sh`: not run (pre-trust doc review, not a rebuild).
- RevEng.AI string dump: no `REVENG_API_KEY` used.
- Prefix surplus `0x1c8` and current `.rdata` prefix bytes: not re-diffed.
- Exhaustive toml-vs-allocator status audit: sampled, not complete (subagent listed more VAs; three sampled RELOC confirmations above).
- c-shapes subagent: did not return before write; numbering and sampled sections done lead-side.
