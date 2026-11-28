# German v2.06 target (GildeGold_TL.exe, module GOLDDE)

Reference: GOG DE `GildeGold_TL.exe` (D3D8 client, SHA-256 `cd40c06e...`), byte-identical in all sections to the
Steam DE `Europa1400Gold.exe` after SteamStub removal (`.text` SHA-256 `52877ae2...`). Place it at
`original/de/GildeGold_TL.exe`.

The German build shares `src/` with the English TL. German twins get a stacked `/* ADDRESS: GOLDDE 0x... */`
anchor above the shared definition; German-only differences belong in the same source (`#if`) or in their own
translation units, never in copies.

| File | Content |
|---|---|
| `map-en-de.csv` | EN TL -> DE function pairs by exact body hash |
| `map-en-de-aligned.csv` | pairs from link-order alignment between hash anchors (`method`) |
| `map-en-de-native.csv` | pairs from normalized native bodies (with hash and earlier DE measurement) |
| `map-en-de-sig.csv` | pairs from function signatures (lowest rank) |
| `map-server-en-de.csv`, `map-server-en-de-native.csv` | server pairs (hash/gap/dup and normalized native bodies) |
| `decisions.md` | decisions, assumptions and open questions for the German targets |
| `../../db/inventory-GildeGold_TL.exe.json` | German function inventory |

Maps and inventory come from Lennard's work on the German build (Ghidra export, used with permission).
`scripts/de_bind_twins.py` binds unbound twins; `rebrew test --all --target GildeGold_TL.exe` measures them.

Baseline 2026-11-27 (upstream a66112fe): 4,141 twins bound, 3,126 byte-identical (132 EXACT, 2,994 RELOC),
38.3 % of German `.text`. Of the English-matched twins 3,125 of 3,509 match; 364 NEAR_MATCHING and 20 STUB are
German-specific work. The 505 SIZE_MISMATCH are unfinished in English too.

## Moving the German work onto a new upstream main

Upstream (maci0/guild-rebrew) moves, merges and renames source files often, so a literal
`git rebase` of this branch conflicts in nearly every commit. The German work is replayed instead;
the previous branch state stays available as a ref (below: OLD, with BASE its merge base):

1. Branch from upstream main and `uv sync --frozen` (upstream pins rebrew).
2. Move the ignored SQLite replica aside (`rebrew-metadata.sqlite3*`, `.rebrew/metadata-journal.toml`,
   `.rebrew/metadata-replication.toml`); otherwise rebrew keeps reading the old branch's metadata.
   The first write re-initializes it from the TOML of the new branch.
3. Copy the files OLD added (`git diff --name-status BASE OLD`, status A) and apply OLD's hunks of
   `CMakeLists.txt`, `rebrew-project.toml` and `docs/provenance.md` (`git apply --3way`).
4. German rows: list OLD's GOLDDE/SERVERDE rows with the file of the current English row that has
   the same object symbol, then `scripts/de_replay_rows.py rows.json --apply` (anchors + rows through
   the locked writers; LIBRARY rows without anchors) and `scripts/de_dedupe_anchors.py --apply`.
5. Content edits: `scripts/de_port_edits.py BASE OLD files.txt --apply` ports every changed function
   whose upstream text still equals BASE's; it lists functions changed upstream and non-declaration
   top-level lines (includes, `#if` guards) for a manual merge.
6. Assembly evidence recorded for German modules (`source.definitions`): `document_assembly` again at
   the new locations; re-record English evidence made stale by German edits with upstream's current text.
7. Measure all five targets, compare German verdicts with OLD and English/Gold verdicts in changed
   files with upstream's stored ones; regenerate `stubs/goldtl/symbol_stubs_de_twins.c` from a GoldTL
   link log; relink both clients; `scripts/gate.sh`; `rebrew lint --all-targets`.
