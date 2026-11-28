# German targets: decisions, assumptions and open questions

Working notes for the `de-targets` branch. Decisions marked **taken** follow from
[goal.md](../../goal.md), [AGENTS.md](../../AGENTS.md), the provenance ledger or the
agreed objective; each is reversible. **Open** items need an owner's answer.

## Objective (agreed with Lennard, maci not yet asked)

One faithful C89 source tree that reproduces, with the original toolchains and
nothing taken from the reference files at build time:

- English: `server.dll`, `Europa1400Gold_TL.exe`, `Europa1400Gold.exe` (maci's targets)
- German v2.06: `GildeGold_TL.exe` (D3D8) and `server.dll`; the German DX6 exe later

Readable names and types are part of the result. The non-byte-identical hybrid
reconstruction in Lennard's work is not extended; its names, types and
behavioural knowledge are ported into this tree.

## Taken

| # | Decision | Basis |
|---|---|---|
| D1 | German targets live in this tree as `GildeGold_TL.exe` (GOLDDE) and `server_de.dll` (SERVERDE); no source copies. | goal.md "one source tree", root-config comment "ported to #ifdef or stacked ADDRESS anchors" |
| D2 | A German twin is bound with a stacked `ADDRESS: GOLDDE/SERVERDE` anchor above the shared definition; rows only through Rebrew's locked writers. | AGENTS.md "Stack one address per target", "Never hand-edit stores" |
| D3 | Twin pairs come from the Ghidra export of Lennard's work, ranked exact body hash > normalized native body > link-order alignment (`gap`/`dup`). | measured: the alignment pairs that disagreed with native pairs were wrong (6/8 RELOC after rebinding) |
| D4 | Row SIZE comes from the English twin, not the coarser German inventory. | inventory extents differ for 124 of 232 sampled twins; the English size reproduced RELOC |
| D5 | Raw English string addresses passed as `(char *)`/`(void *)` become string literals when no other site names the address. | goal.md "faithful C"; VC6 without /GF emits the same relocated push |
| D6 | Raw English data addresses in non-matching German twins become named globals `g_<va>` only when every link that compiles the file already defines the name, and no English/Gold row of that definition is EXACT. | ledger precedent (2026-11-10/11: raw casts to existing `g_<va>` globals); AGENTS.md "zero new LNK2001/2019/2005"; gate "no stored status fell" |
| D7 | Wrong or unsupported German bindings are retired with `source binding retire` and a reason, never deleted silently. | AGENTS.md reviewed source claim changes |
| D8 | Non-matching German rows that lint flags carry a BLOCKER naming the measured difference; matching German twins of documented assembly carry GOLDDE evidence citing the English evidence. | lint W005/W020 rules; all-target lint must stay clean |
| D9 | German-only behaviour or constants will be expressed in the shared definition (`#if` on a German define) or in a German-only TU, never as a copy of a whole function. | goal.md "no drifting copies"; root-config comment |
| D11 | The German server target uses `msvc-6.0-sp5-pp`: `rebrew toolchain detect original/de/server.dll` finds 9 Processor-Pack x87 compares and 0 plain (the English server is plain), and with that profile the target reports `aligned`. | detect output; gate's code-generator check; goal.md "original toolchains" |
| D12 | Raw English data addresses in non-matching German twins may name new `g_<va>` globals; GoldTL placeholders come from `rebrew build symbol-stubs --log` (stubs/goldtl/symbol_stubs_de_twins.c). Never for code addresses or import slots; files whose English, Gold or German verdict falls are restored. Interior/end addresses use the base global the same function names (`scripts/symbolize_interior_addresses.py`). | naming-batch placeholder practice in the ledger; AGENTS.md import-slot ownership; maci unavailable, user asked to proceed Extended 2026-11-28 to bare integer literals (`scripts/symbolize_bare_addresses.py`): same scope and placeholders, an address within 0x4000 above another literal of the body is written as its offset, single-bit values stay numbers. |
| D10 | The German client target defines `REBREW_GOLDDE` (pattern of `REBREW_GOLD`/`REBREW_SERVER`). Version-dependent constants get a named macro in a small header, e.g. `d2_ELEMENT_CAPACITY` (768 German, 1024 English) in `Develop/Units/d2.v1/d2_capacity.h`; English code generation is unchanged because the expressions fold to the same constants. | existing target defines; naming_conventions.md `prefix_UPPER_SNAKE` |
| D13 | Two further pair sources and one inventory rule. (a) `map-en-de-callee.csv` (`scripts/de_callee_pairs.py`): code references zipped from German twins that measure EXACT/RELOC, ranked with the native pairs; kept only when every referencing twin agrees and the German address is not bound to another definition. (b) `map-en-de-gapmnem.csv` (`scripts/de_gap_align.py`): unpaired rows inside link-order gaps, capstone mnemonic similarity >= 0.9, ranked with gap/dup; look-alike siblings pair only as a whole cluster with equal counts, in link order. (c) The German inventory follows proven German functions (`scripts/de_inventory_plan.py`): EXACT/RELOC rows fix their extent; rows that ran into them are shrunk, missing starts admitted, code after the padding of a proven ret/jmp admitted as its own unnamed row. | (a) 2,482 of its first 2,548 pairs agreed with the older maps, none conflicted; (b) its first, greedy version paired two sibling functions wrongly, caught by `ch_RegisterScriptCommands` (the German registration table pushes the real addresses), hence the cluster rule; (c) measurement is the only evidence that fixes a German extent, the inherited inventory merges neighbours (D4). |
| D14 | The German server target defines `REBREW_SERVERDE` and force-includes `src/Develop/Units/Error/serverde_build.h` (`/FI` in its `base_cflags`). The header redirects `LogMessageInternal` to an empty `static __inline` stub, so calls and their literal arguments vanish while argument work with side effects (sprintf into a message buffer) stays. Code that differs otherwise is expressed in the shared definition: `#if defined(REBREW_SERVER) && !defined(REBREW_SERVERDE)` selects the client branch where the German server matches it (ahm_CheckFlag, m_alloc), `#if !defined(REBREW_SERVERDE)` drops a part the German build lacks (m_FreeTracked underflow check, the LogMessageInternal definition), and a loop spelling that gives the English bytes on the plain compiler and the German bytes on the Processor Pack one replaces the old one (DispatchLogOutput `for`). | The German server.dll contains none of the message literals the English server passes to LogMessageInternal (e.g. "Memory freed more than once", "gm_AddObjekt(): obj == ob_NULL", "not open crashdump"), nor its `Time:%8lu`/`Module` formats, but keeps sprintf formats such as "gm_AddObjekt(): Parent not found": logging compiled out, not removed by hand. A forced include changes no source line of the 18 files that log; ReportFatalError is not redirected because one header declares it variadic. |

## Assumptions

- A1: The unpacked Steam DE exe stands in for GOG DE `GildeGold_TL.exe`: all sections are
  byte-identical (`.text` SHA-256 `52877ae2...`), only the file container differs. Whole-file
  checks need the GOG file.
- A2: German twins with the same normalized body are the same original function; a RELOC match
  does not prove operand identities (reported separately, as for the English targets).
- A3: The German build is an older code version than the English one (EN exe 2004-01), not only
  a translation. German differences may therefore be code changes, not just strings.

## Open

| # | Question | Owner | Current handling |
|---|---|---|---|
| O1 | Does maci accept German targets and PRs here, or prefer a tracking repo? | maci | local branch only |
| O2 | Raw English addresses that are still numbers in C. (a) taken 2026-11-28 as D12 for German twins; the rest of (a) and (b) remain: pointer casts whose `g_<va>` name no link defines yet (about 400 sites): new placeholder globals in `stubs/` or proper data definitions first? (b) interior/end addresses in integer arithmetic, e.g. `(int) p < 0x14d0c20` (= `ch_CharacterSlots` + 0xc00) or `0x7f4ca0 + id * 0x21c`: these need the backing object and its extent (AGENTS.md "An interior address is a view"), but only 62 of 470 GOLDTL data rows record a size. About 250 German misses depend on (a) or (b). | maci | left as written |
| O3 | Tracked home for the EN->DE maps (`db/*` is git-ignored; placed in `docs/de/` for now). | maci | `docs/de/` |
| O4 | Licence/permission to publish inventories, maps and C taken from Lennard's work in this MIT repo. | user | done 2026-11-28: Lennard agrees to publishing in guild-rebrew. |
| O5 | ~~Name for the German define~~: taken as D10 (`REBREW_GOLDDE`). A German server define is not needed yet. | maci (review) | done |
| O6 | ~~Relinks~~: done. Server gate (raw link byte-identical), Gold and GoldTL clients link with 0 errors on this branch and on clean upstream. DirectX inputs: d3dx8.lib from the DirectX 8.1 SDK, the four XP SP1 archives from the Windows XP SP1 DDK (hashes match docs/directx-inputs.md). | done | ledger 2026-11-28 |
| O7 | Ten English RELOC rows bound through `_cm_ExProdObjekt` measure NEAR_MATCHING on clean upstream (stale stored status). | maci | reported only |
| O8 | Static or differently shaped zlib helpers cannot be bound (client 6, server 7: `deflateInit2_`, `destroy`, `inflateInit2_`, `inflate`, `inflate_trees_dynamic`, `zcalloc`, `zcfree`) with `library bind-source` (it needs an external symbol); how does the English target bind them? | us | done 2026-11-28: written as LIBRARY rows with the English identity shape through the locked writer; client 7 and server 6 verify EXACT/RELOC (provenance.md). zcfree has no map pair. |
| O9 | Lennard's work solved several German raw-address cases with hard-coded German addresses (`DE_ADDRESS_...` macros). These are not ported: they would need information from the reference at build time. | us | not ported |
| O10 | German server: `amt_ValidateAndAssignOffice` (aemter.c) and `gm_FreeObjectListRecursive` (spiel.c) match only with plain SP5, while the other German rows of those files match only with the Processor Pack. One TU cannot use two code generators, so the German original probably placed them in another TU. Needs the source-organization review (`rebrew source organize review`) before any per-TU pin. | maci / us | BLOCKER on both rows |
| O12 | German server bodies that differ from the English ones need German variants (D9, D14). Done 2026-11-28 for 21 (logging compiled out, client branches, m_FreeTracked, DispatchLogOutput, CrashDumpUnhandledExceptionFilter, sizes; m_PoolAlloc/m_ShutdownAllocator pair corrected); open: vfs_ReadData, vfs_OpenStream, ProcessSendData, amt_ValidateAndAssignOffice, ahm_ClampFloatValue, ahm_InitRandomEntity, cm_ExCreateGeb, gv_MoveSlotEntry (no inventory extent, W028), lb_ExPlayerlist, plt_SetPlantMap, gm_RemoveLinkedNodeById, gm_FreeObjectListRecursive, gm_KillSpieler, gm_GetEntityTableEntry, gm_ChangePlayerIdentityImpl. | us | partly done |
| O13 | Raw English addresses stay in definitions whose English row is EXACT, because naming them turns that row into RELOC (maci's ledger treats EXACT->RELOC as a review item). Measured 2026-11-28 with `--allow-exact` on the four rewrite scripts, then reverted: in 63 files without other falls, +59 German matches against 66 English rows EXACT->RELOC. The goal (no information from the original binaries in the source) favours naming them, and the linked image, not the per-function EXACT/RELOC label, is what has to stay identical; needs maci's or the user's call. | maci / user | open |
| O11 | Of the 294 German inventory entries without an English twin, many are not functions: tails and error paths of a preceding function (e.g. 0x40e5f4 starts with `pop edi; pop esi; ... add esp, 0x14; ret`; 0x40d79b-style entries use registers set by the caller code). They need `rebrew binary repair-extents --merge` after reviewing the containing function. The rest are mostly tail-call wrappers (`jmp m_FreeTracked`) and import thunks; genuinely German-only bodies are a minority. | us | partly done 2026-11-28: 33 fragment rows repaired (27 merged at proven English extents, 3 padding, 2 split, 3 continuation; provenance.md). Of the 309 unbound game-code rows left, 252 have no English pair in any map (147 KB, mostly functions with a prologue: German-only or changed beyond the matchers), 34 pair with English STUBs, the rest are zlib statics (O8) or English rows without a verdict. |
