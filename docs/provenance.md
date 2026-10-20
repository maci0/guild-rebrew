# Provenance ledger

Append-only record of changes to the reconstruction deliverables. Each entry
names the date, the change, the reason, the evidence, who asked or decided, and
how the result was verified. Reversals are new entries.

## 2026-10-20

### Reconstructed function bodies (GOLDTL)

- Change: hundreds of `src/GOLDTL*.c` bodies rebuilt or corrected through the
  staffed reconstruction workflow; status transitions written only by
  `rebrew test`/`rebrew verify`.
- Why: reach byte-identical coverage of `Europa1400Gold_TL.exe` (session goal).
- Evidence: per-function `rebrew test --json` verdicts, `.scratch/recycle2/results/`,
  `.scratch/wave*/results/`, `.scratch/round5/results/` reports; promoted rows
  listed in the session log.
- Decided by: user goal; each body reviewed against `rebrew diff` and asm.
- Verified: `rebrew test` match counts; RELOC promotions re-measured after every
  extent repair; no STATUS hand-written.

### Reviewed extent repairs (inventory only)

- Change: `rebrew binary repair-extents` batches applying reviewed native body
  boundaries and merged-row splits (trailing NOP removal, added entries).
- Why: stored SIZE padded to next entry blocked RELOC for complete bodies.
- Evidence: `.scratch/wave2/extent-specs.tsv` (each spec lists its ret/NOP/pad
  evidence), `--dry-run` digests, advisory notices from agents.
- Decided by: session Lead after agent evidence review.
- Verified: digest-guarded apply; rows re-measured with `rebrew test --va --size`;
  refused cases (`overlaps next inventory start`) recorded in
  `.scratch/wave2/EXTENT-QUEUE.md`.

### Compiler-behaviour decisions

- Change: `.scratch/wave2/DECISIONS.md` updated with proven codegen rules and
  walls (framed tail jmps, PP shrink-wrapped saves, frame sizing, `extern`
  literal forms, duplicated-call merge, allocate probes).
- Why: stop agents repeating dead ends and make levers reusable.
- Evidence: probe sources under `.scratch/recycle2/agents/*/`, compiled with the
  locked `msvc-6.0-sp5-pp` profile; per-rule replay commands in the file.
- Decided by: session Lead.
- Verified: probes recompile and reproduce source-target byte shapes.

### Tooling gaps recorded for upstream

- Change: IDEAS entries drafted in `.scratch/wave2/DECISIONS.md` because the
  upstream checkout is mounted read-only in this session: extent-retire
  capability, `build driver` profile handling, `source binding` ambiguity with
  stacked anchors.
- Why: these gaps block reviewed work (interior-row retirement, PP probes).
- Evidence: concrete rows and commands named in each entry.
- Decided by: session Lead.
- Verified: every gap reproduced with the named commands.

### Row-level body corrections (recycle2 refine waves, 2026-10-20)

- Change: targeted C-shape corrections closing remaining byte deltas on partial
  bodies, e.g. `0x4d3c60` (ratio arm polarity plus `cnt` band block; 477 -> 516
  of 560, now NEAR_MATCHING), `0x4f1ad0` (reload instead of cached pointer; 161
  -> 225 of 592), `0x4fcc20` (live handle deref, scaled `0x24d` base; 59 -> 342
  of 376), `0x500a40`, `0x550be0`, `0x4cfca0`, `0x5bdfc0` (the last three now
  RELOC).
- Why: close near-miss rows to RELOC and raise partial coverage.
- Evidence: per-row `rebrew test --json` before/after counts in
  `.scratch/recycle2/results/`; decisions and levers in
  `.scratch/wave2/DECISIONS.md`.
- Decided by: session Lead (agents propose, Lead reviews promotions).
- Verified: every change re-measured with `rebrew test`; promotions recorded only
  by the comparison tools, never hand-written.

### 0x572a50 promoted to RELOC (820/820)

- Change: `gm_RandomMod` callee declared `unsigned short` instead of `int`, so
  the call site emits native `mov cx,ax`; reviewed extent repair
  `0x572a50`=820 (switch table inside, 12 NOP pad removed).
- Why: byte-identical body was blocked only by the callee return-width codegen.
- Evidence: `rebrew test --va 0x572a50 --size 820 --json` returned
  `status RELOC, match_count 820, total 820, mismatches 0`.
- Decided by: recycle2 group-105 finding, Lead applied the extent repair.
- Verified: full-body test with the repaired extent, 23 reloc bindings validated.

### ADDRESS-comment binding repairs (2026-10-20)

- Change: removed a duplicated GOLD anchor above `extern int g_6b7fac` in
  `src/GOLDTL.fcn_0040bd80.c`; moved 14 misplaced ADDRESS comments that sat above
  `extern` declarations onto their function definitions; created reviewed data
  rows `g_6b7fd0`/`g_6b7fd4`/`g_6b7fd8` (0x6b7fd0 family) and `g_6b8014`;
  renamed the GOLD row at 0x6b7fac to `g_6b7fac_gold` so the TL name is unique.
- Why: resolver built name-to-VA across targets, so duplicated or misplaced
  anchors produced AMBIGUOUS_VA and no RELOC was possible for affected operands.
- Evidence: PE sections confirm 0x6b7fd0/0x6b8014 live in .data
  (base 0x400000, .data RVA 0x275000); native relocation values equal those VAs;
  audit found exactly 14 misplaced anchors via a script over src/**/*.c.
- Decided by: session Lead after group-104/111/115 findings.
- Verified: `0x415d70` RELOC 739/739, `0x4133e0` RELOC 158/158, `0x42e0e0`
  RELOC 59/59 at its 59-byte extent, `0x42e120` RELOC 86/86.

### Interior inventory row retirement (2026-10-20)

- Change: removed seven reviewed interior inventory rows that an earlier
  discovery split out of multi-entry bodies: 0x4b023b; 0x55b5a2, 0x55b866,
  0x55b8b4, 0x55b8e4, 0x55b914; 0x51f0ce. Each is a `je` target strictly inside
  a single body, has no metadata row, and blocked the parent extent repair.
  Applied with `.scratch/wave2/retire_inventory_rows.py`, then resized the
  parents through `rebrew binary repair-extents` with a reviewed digest.
- Why: `repair-extents` cannot retire interior rows, so byte-exact bodies
  (0x4b0220 at 438, 0x55b3e0 at 2115, 0x51ecf0 at 1145) could not be measured.
- Evidence: inventory entries and metadata absence checked per row; parent
  boundary evidence in `.scratch/recycle2/results/group-128.md`; script refuses
  children that have metadata rows. Backup kept at
  `db/inventory-Europa1400Gold_TL.exe.json.pre-retire`.
- Decided by: session Lead, after group-128 reported the tooling gap.
- Verified: parents resized with digest-guarded repair; verdicts re-measured with
  `rebrew test --va --size`.

### Retirement promotions (2026-10-20)

- Change: `0x4b0220` RELOC 438/438, `0x55b3e0` RELOC 2115/2115 after the
  interior-row retirement and parent resizes above.
- Why: both bodies were byte-exact but unmeasurable at their merged extents.
- Evidence: `rebrew test --va ... --size ... --json` reports the two verdicts
  with full match counts and 15 / many VALIDATED relocations.
- Decided by: session Lead.
- Verified: digest-guarded repair then per-row comparison; store verdicts written
  only by `rebrew test --force-status`.

### Rewrite wave and extent repairs (2026-10-20, later)

- Change: rebuilt wrong-body SIZE_MISMATCH functions from native disassembly in
  rotating groups (151-173); promoted `0x532bd0` RELOC 791/791, `0x5da820` RELOC
  770/770, `0x555d30` RELOC 984/984; promoted `0x64d1df` EXACT 56/56 and
  `0x4eb260`/`0x4eb320` RELOC 188/188; applied reviewed extent repairs and
  interior-row retirements described above.
- Why: close byte coverage; bodies proven wrong by earlier waves needed
  reconstruction, not gap fixes.
- Evidence: per-group reports under `.scratch/recycle2/results/`, native
  disassembly dumps under `.scratch/recycle2/agents/group-*/`, and the extent
  specs in `.scratch/wave2/extent-specs.tsv`.
- Decided by: session Lead; agents propose bodies, Lead applies metadata changes.
- Verified: every promotion re-measured by `rebrew test --force-status`; statuses
  written only by the comparison tools.

### Restored clobbered source file (2026-10-20)

- Change: `src/GOLDTL.fcn_004055a0.c` was restored from HEAD after another
  writer replaced its body with `fcn_004cf000`, which duplicated the 0x4cf000
  ADDRESS anchor and broke the project-wide scan.
- Why: every `rebrew test` failed with an address-anchor conflict.
- Evidence: `git show HEAD:src/GOLDTL.fcn_004055a0.c`; clobbered copy at
  `.scratch/wave2/004055a0.clobbered.c`; row re-measured RELOC 248/248 after
  restore with `rebrew test --no-promote`.
- Decided by: session Lead (unblock).
- Verified: comparison tool scan succeeds project-wide again.

### README statistics and graphics refresh (2026-10-20)

- Change: refreshed `README.md`, `docs/progress.svg` and
  `docs/function-map.svg`. C matches are 251/251 server, 3,752/5,042 GoldTL
  and 2,469/4,592 Gold; 26 Gold whole-function assembly matches stay separate.
  Added the remaining verdict categories and source gaps, and distinguished
  the existing server file's equality from current-source verification.
- Why: replace the earlier snapshot with current stored results without
  treating partial implementations or inventory changes as match gains.
- Evidence: `rebrew status --all-targets --json`, saved locally as
  `.scratch/readme-2026-10-20/latest/status.json`; graphics rendered by the
  existing `scripts/progress_svg.py`, including its map/count reconciliation.
- Decision owner: user requested the latest README data and statistics.
- Verification: README totals reconcile with the saved status report; both
  SVGs parse as XML; local README links, fragments and fences pass, and
  `git diff --check` passes for the changed deliverables. No compilation,
  metadata writes, fresh function verification or full gate was run.

### README progress metrics distinguished (2026-10-20)

- Change: made virtual `.text` accounting the README's primary percentage,
  alongside C function counts and same-offset raw-file agreement. Renamed the
  function graphic's heading and subtitle in `scripts/progress_svg.py` so its
  percentages cannot be read as byte coverage; regenerated `docs/progress.svg`.
- Why: 74.4% of GoldTL functions matched does not mean 74.4% of its code bytes
  are accounted for. The same snapshot reports 47.3% code accounting and 1.2%
  raw-file agreement; Gold reports 22.9%, 53.7% and 1.1% respectively.
- Evidence: `.scratch/readme-2026-10-20/latest/status.json`, confirmed by a
  subsequent read-only GoldTL status query. No new verification was claimed.
- Decision owner: user requested correction of the confusing percentages and
  a Git commit.
- Verification: README figures reconcile with the saved JSON, both SVGs parse,
  local links/fences and staged whitespace checks pass. Rendering changes are
  labels only; no compiler, metadata or raw-link changes are included.

### Three progress bars per target (2026-10-20)

- Change: updated the README graphic and renderer to show separate bars for
  virtual `.text` accounting, C function matches and raw-file agreement at
  original offsets. Updated README alternative text and renderer tests; the
  address-ordered function map remains unchanged.
- Why: make the three denominators visible and prevent the function-count
  percentage from being mistaken for byte coverage or whole-file completion.
- Evidence: the same `.scratch/readme-2026-10-20/latest/status.json` snapshot
  used by the README table; rendered preview `latest/three-metrics.png` beside
  it. No new source-recovery or verification result is claimed.
- Decision owner: user requested the graphics update and Git push.
- Verification: six focused renderer tests pass, including independent bar
  widths, assembly/PROVEN exclusion, absent-image N/A and invalid counts.
  Ruff formatting/lint, SVG XML parsing, rendered visual inspection and
  staged whitespace checks pass. No compiler or full reconstruction gate ran.

### Full reconstruction working-tree checkpoint (2026-10-20)

- Change: committed the accumulated client C implementations, shared GUI text
  creator and caller repairs, declarations, inventory and managed metadata
  updates, project rules, trackers and handoff notes. Existing partial and
  nonmatching bodies remain explicitly unfinished. Removed trailing whitespace
  from one blank line in `src/GOLDTL.fcn_00441400.c` without changing line count.
- Why: preserve all current project work in Git at the user's request; this
  checkpoint is not a successful build or whole-image verification claim.
- Evidence: prior per-function receipts indexed in this ledger and
  `docs/TODO.md`; commit-time reports under
  `.scratch/commit-everything-2026-10-20/`. Four empty root artifacts and a
  compiler-generated `t5.asm` listing were preserved there rather than tracked.
- Decision owner: user explicitly requested committing everything and pushing.
- Verification: whitespace check passes. Full read-only lint returned one E013
  duplicate-VA error and 24 warnings per target during ongoing source edits;
  the duplicate's focused recheck subsequently had zero errors and two
  warnings per target. The complete lint was not repeated, and no full
  build, function re-verification or raw-link gate ran for this checkpoint.

### GOLD naked-asm conversion and lint repair (2026-10-20, evening)

- Change: converted all 36 GOLD rows that claimed RELOC/EXACT from whole-function
  `__declspec(naked)` + `__asm` into plain C89 (groups 190-195), using an
  instruction-shape twin search over the GOLDTL inventory and translating the
  twin's source. Registered the retired mis-bound
  `spiel_c/GOLDTL.gm_ChangePlayerIdentityImpl.c` as a support file, and removed
  the duplicate `0x62b5d0` ADDRESS anchor (prototype moved to a header).
- Why: project rules allow asm only for 1-2 padding bytes; lint E023 failed the
  gate for 36 GOLD rows. The E001/E013 errors blocked the same gate.
- Evidence: `.scratch/recycle2/results/group-190..195.md`; `.scratch/wave2/lint4.json`
  reports `total 7252, errors 0, warnings 23`; per-row verdicts written by
  `rebrew test --force-status`.
- Decided by: session Lead. Where conversion lost bytes to a documented wall, the
  honest C body and reduced verdict were kept (see DECISIONS).
- Verified: full `rebrew lint` errors 0; converted rows re-measured
  (group-194 kept 6/6 RELOC; group-195 kept 4 RELOC + 1 EXACT).

### README graphic freshness and cache versions (2026-10-20)

- Change: regenerated both README SVGs from a fresh status snapshot, added
  visible minute-level UTC timestamps to the existing renderer and content-hash
  versions to both image URLs, and refreshed Gold's unfinished-work counts.
- Why: readers reported old graphics. Published raw README/SVG hashes matched
  the local committed files, so a server-side content mismatch was not observed;
  changing image URLs avoids reusing the previous browser image-cache key.
- Evidence: raw GitHub responses and `.scratch/readme-refresh/status.json`;
  headline percentages are unchanged. No stale-browser cache was directly
  reproduced, and no new build or source-verification result is claimed.
- Decision owner: user reported stale GitHub README graphics; publishing the
  refresh follows the user's existing commit/push instruction.
- Verification: renderer tests, SVG XML and image-URL hash checks, visual preview
  and whitespace checks; remote content checked after publication. Project
  reconstruction changes are outside this documentation refresh.

### Immutable README image references (2026-10-20)

- Change: pinned both README SVG image URLs to graphics commit `9a72da61`.
  Local SVGs remain in `docs/`; subsequent refreshes must update the image ref.
- Why: immediately after publication, raw GitHub `main` URLs returned older
  bytes even with content-version query parameters. Commit-addressed URLs
  returned the exact new files, so immutable refs supersede the query-only fix.
- Evidence: SHA-256 comparisons of local, branch-addressed and commit-addressed
  README/SVG responses; GitHub's rendered README already used the new query
  URLs while those raw image responses remained older. Response cache lifetime
  was 300 seconds. This establishes an observed stale branch response, without
  identifying whether an intermediary or origin maintained that cached copy.
- Decision owner: user reported old graphs; preserve the requested current view.
- Verification: both commit-addressed image responses equal the local SVGs;
  README asset URLs resolve and staged whitespace checks pass. No build ran.

### Import-table API extraction and prepared caller migration (2026-10-20)

- Change: implemented nullable PE `hint_name_rva` in the existing upstream
  import-table API and JSON output, with parser/consumer regressions and CLI
  documentation; recorded the gap in upstream `docs/IDEAS-GUILD.md`. Added the
  release prerequisite and audit disposition to `docs/tooling-upstream.md`.
- Why: Guild's import recipe needs physical hint/name positions, but the public
  API discarded them and forced duplicate LIEF traversal. Its measured server
  ordering rules remain local; no generic linker policy was inferred.
- Evidence: upstream local commit `dea5295c`, branch
  `feature/import-hint-name-rva`, isolated at
  `.scratch/rebrew-import-hint-name-rva`. Prepared caller patch and read-only
  parity replay live in `.scratch/rebrew-import-hint-name-rva-migration`.
  Original and migrated recipes both reproduce all 39 lines / 1,205 bytes of
  `layout/server.dll/import-includes.rsp`, SHA-256
  `994f6ee54779552cb809b13b70051f2e87f84a73d1527cd36f6e6a0ff8f00b5f`.
- Decision owner: user requested the script audit, delegated implementation and
  upstream migration. Preserve the supported pinned package environment: the
  caller patch remains unapplied until a release containing the field is
  installed. The working script, dependency pins and native inputs are unchanged.
- Verification: 515 distinct upstream focused/consumer/CLI/package tests pass;
  both PE widths preserve physical hint/name positions independently of IAT
  order, and ordinal/ELF/NE imports carry null. Ruff, touched-file formatting,
  mypy (401 modules), cycles/layering and commit hooks pass. Patch apply-check
  and read-only parity replay pass. Full upstream suite and native builds were
  not run; no metadata writes, package upgrades or publication occurred.

### Rebrew 5.4.0 publication and Guild import-API migration (2026-10-20)

- Change: published the verified distribution assets for Rebrew 5.4.0 at
  upstream tag commit `79896b0d`, containing import API commit `dea5295c`.
  Guild's manifest/lock and installed venv now use that public wheel for prove
  and optional BinSync, retaining Recoverage's scoped dependency exclusion.
  Applied the prepared import-recipe migration and refreshed current tooling
  instructions, README installation version, handoff and queue guidance.
- Why: user explicitly authorized publication and a release; remove Guild's
  duplicate import-table traversal only once the public dependency supports it.
- Evidence: https://github.com/maci0/rebrew/releases/tag/v5.4.0 and all six green
  CI jobs at https://github.com/maci0/rebrew/actions/runs/39406501806.
  Exact CI package artifacts, verification logs, before/after package lists and
  read-only recipe replays are under `.scratch/rebrew-release-5.4.0-logs/` and
  `.scratch/release-asset-verification-79896b0d/`.
- Decision owner: user authorized the release, migration and publishing.
- Verification: CI wheel/sdist manifest validation and clean-venv smoke pass;
  uploaded assets are the verified CI files plus SHA256SUMS. Guild `uv lock
  --check`, `uv pip check`, prove/BinSync/Recoverage imports and 22 selected
  project tests pass. Only installed Rebrew changed, from 5.2.0 to 5.4.0.
  The migrated response is still all 39 lines / 1,205 bytes with SHA-256
  `994f6ee54779552cb809b13b70051f2e87f84a73d1527cd36f6e6a0ff8f00b5f`.
- Test-fixture correction: the project gate already requires explicit
  `functions_checked: true`; its old positive fixture omitted the field.
  Updated that fixture and added missing/false controls without weakening the
  production gate. No game source, managed metadata, layout bytes or raw
  binaries were changed by this migration, and no native rebuild ran.
- Validation limits: an initial parallel local push-hook run had one native
  fixture failure that passed alone. Later local full runs were invalidated
  when an overlapping release process removed their temporary worktree;
  they are not claimed as passing. Final release acceptance uses the complete
  successful CI run for the published commit and exact artifact checks.

### Retire obsolete helpers and reuse canonical readers (2026-10-20)

- Change: removed `scripts/update_state_table.py` and its best-effort gate hook;
  removed duplicate `stubs/recipe.txt` in favor of `stubs/README.md`. The TODO
  table retains every measured value and is explicitly a historical checkpoint.
  Updated the retained-helper inventory, including the README graphics renderer.
- Why: user requested cleanup after the upstream script migration. Scraping old
  gate terminal phrases into the tracker could replace measurements with unknown
  values; the gate already saves structured reports. The duplicate recipe still
  carried obsolete invocation flags.
- Change: retained the measured BSS and scaffold recipes, replacing their local
  TOML/map parsing with Rebrew's `load_data_metadata` and `parse_link_map` APIs.
  BSS input now includes managed fragments and respects the configured metadata
  backend; target filtering and allocation/order policy remain local.
- Decision owner: user requested removal of old ad hoc scripts. Keep live native
  build/acceptance recipes and historical scratch evidence.
- Evidence: read-only before/after replays in
  `.scratch/script-cleanup-2026-10-20/`, including `parity.json`. All three BSS
  recipe outputs agree, as do complete Gold and GoldTL manifest JSON documents
  from the existing link maps (2,890 and 2,960 scaffold symbols respectively).
- Verification: 24 selected tests and 3 subtests pass; new regressions cover
  fragmented metadata and both project-object and archive-member map origins.
  Ruff, shell syntax and scoped whitespace checks pass. No BSS source,
  scaffold manifest, managed metadata or native binary was regenerated. No
  native build or full gate ran; unrelated reconstruction edits remain separate.

### README and chart snapshot refresh (2026-10-21)

- Change: refreshed the README metric and remaining-work tables, progress bars
  and address-ordered function map from one `rebrew status --all-targets --json`
  snapshot. Updated the refresh recipe to reuse one report, with commit-pinned
  published image URLs to avoid stale branch-cache responses.
- Why: user requested the latest README data and charts. Keep code-byte
  accounting, C function counts and raw-file agreement separate; exclude
  whole-function assembly and PROVEN from matched C totals.
- Evidence: `.scratch/readme-refresh-2026-10-21/status.json`, captured at
  2026-10-20 17:51 UTC (2026-10-21 Singapore time), SHA-256
  `48bc6d4fb96c4bb9aab96e9f044726ed9b448d2c346ffd4da13feeeb1a8bd921`.
  GoldTL: 3,771/5,053 C matches (74.6%), 1,192,240/2,491,370 accounted code
  bytes (47.8%); Gold: 2,469/4,592 C matches (53.7%), 22.9% code accounting;
  server: 251/251 C matches and 100.0% code accounting. Existing raw-file
  agreement remains 100.0% server, 1.2% GoldTL and 1.1% Gold.
- Decision owner: user requested the refresh and previously authorized pushing
  README and graphic updates. Preserve concurrent reconstruction edits.
- Verification: six graphic tests pass; both SVGs parse as XML and use the same
  timestamp. Function-map game/library/assembly/C totals agree with the status
  report; README values reconcile to that report. No source, inventory,
  metadata or raw binary changed in this refresh. No native build or fresh
  verification ran; the snapshot includes current stored working-tree verdicts.
