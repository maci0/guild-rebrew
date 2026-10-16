# Original build and native facts

Technical evidence, not current progress. Query current metadata and use
[TODO.md](TODO.md) for continuation. Names belong in the
[naming ledger](naming_conventions.md); source/codegen/layout findings have
separate references in the [documentation map](README.md).

## Original project

4HEAD Studios used `D:\Develop\`: `DieGildeAddOn` game logic,
`DieGildeAddOnVc` client build, `DieGildeAddOnServer\server.c` entry and
shared `Units`. Embedded paths and diagnostic prefixes attest names; game nouns
are German and most verbs English.

## Original build

| Property | Server | TL | Gold |
| --- | --- | --- | --- |
| Configured code generator | Plain VC6 SP5 | SP5 Processor Pack | SP5 Processor Pack |
| Runtime | `/MT`, LIBCMT | `/MT`, LIBCMT | `/ML`, LIBC |
| Original retention evidence | `/OPT:REF` | `/DEBUG`, `/OPT:NOREF`, PDB path | `/OPT:REF` |

Default game optimization is `/O2 /Gd`; effective inputs live in configuration.
TL keeps 298 unreferenced game-range bodies in the measured census, Gold three,
server none. Source sharing does not imply identical code/data: client building
stat offsets and the 12-level logging table differ from server's three levels.
Use literal allocation tags, per-target managed data bindings and actual native
callee destinations. Same-named functions and same-shaped wrappers can differ.

The D3DX8 static band in TL is `0x5e0000..0x64ffff`; other libraries are not
necessarily contiguous. Library attribution is separate from game/compiler and
selected-provider evidence. Server exports `Init` at `0x10009320` and `Exit` at
`0x10009350`, image base `0x10000000`, 100 imports, `.text` VS `0x22846`.

## Toolchain observations (verified with commands; round 938)

Detector confidence alone cannot identify a service pack. Old SP6 claims and
three per-file Processor Pack pins were superseded by round 1379 below. Plain
SP5/SP6 produced the same tested bodies; current server policy is one plain
profile. Stock library objects have independent compiler provenance.

## Deliverable mechanics

Historical postlink builds copied non-text bytes from the reference; their green
section checks did not establish raw-file identity. That pipeline is retired.
Current acceptance compares ordinary `build/server.dll` against the complete
reference; [goal.md](../goal.md) defines completion.

## Game domain

Commands separate `cm_Chk*` validation from `cm_Ex*` execution. Other game facts
and the distinction between native and community evidence are in the
[compendium](game-compendium.md). Working constant names are not automatically
attested original identifiers.

## The `command_c` discovery boundaries are an INVENTORY artefact, not a coverage gap

Rounds 1021–1024 misread coarse inventory spans as missing source. All 25 bound
functions within the twelve investigated spans already existed; 24 had no
shipped residue. The remaining 966 bytes belonged to known `cm_ExSellObjekt`
`0x1000d930`. The old `0x1000d8a0` 2,008-byte inventory entry swallowed its
separate 144-byte predecessor and that body. Check existing bindings and native
boundaries before claiming missing work. Full VA/file census is archived.

## The build is bit-reproducible from scratch, and the correct clean recipe is `--target final`

Historical round 1039 reproduced the then-postlinked image and its 8,628-byte
text residue after a clean build. The heading names a retired split-link recipe;
it is not a current build instruction. Use the current server gate.

## Done-criteria status, verified independently (round 1043)

The historical structural/load checks passed while text residue and unmatched
functions remained. Their success did not establish completion or raw identity.
The full old table is archived; do not reuse its counts.

## Faking the original `D:\` build path through wine is possible, and unnecessary (round 1054)

The compiler command-line path controls `__FILE__` under Wine. The measured tree
used explicit original-path diagnostic literals, so a new drive mapping was not
needed. Preserve literal bytes; changing a log path to `__FILE__` can introduce
`Z:\home\…` text. The old host-prefix mapping example is historical; compilation
still runs only through configured Docker tooling.

## The data sections are complete, and `rebrew todo` was reporting 123 phantoms (round 1078)

Historical postlinked measurements, not current data completion. Server has no
`.idata`: IAT is at `.rdata` head (RVA `0x24000`, 416 bytes). The `.data` virtual
tail begins at `0x10035000` and ends `0x1176759c`; loader zero-fill has no reference
file payload. A comparison denominator must distinguish file bytes, imports,
zero-fill and unknown extents. See [data ownership](data-ownership.md).

## Section-by-section parity: the shipped file is byte-identical outside `.text`, BY COPYING, NOT BY COMPILING (round 1089, corrected round 1092)

The earlier completion claim was retracted: postlink supplied those equal bytes.
Always compare the raw toolchain output and complete file lengths. An initialized
byte comparison does not establish source ownership or virtual storage extent.

## Finding code we already reversed in another target: `rebrew source import-related`

```sh
uv run --frozen rebrew source import-related --from server.dll --target Europa1400Gold_TL.exe --dry-run --candidates-only --json
```

Structural scores propose counterparts; destination compilation and complete
operand/literal checks decide adoption. Use shared-definition imports in this
unified tree, preserving co-resident bodies. The server/client generator
boundary and genuine source differences can defeat a score-100 candidate.
Current CLI help owns options and write behavior.

## The three binaries: one compiler version, two code generators (round 1379, definitive)

The investigation identifies VC6 `cl.exe` 12.00.8804 with plain versus Processor
Pack `c2.dll` 13.00.9044. Client Rich records carry `@comp.id = 0x00302354`
(counts 154/157); the measured stock server record is `0x000a2306`, count 37.
The contemporary configured server copy had altered headers; later untouched
reference provenance is recorded in [README.md](../README.md). Do not infer
compiler provenance from a stripped header or another SDK object's Rich entry.

Across nine optimization settings, Processor Pack emits x87 `fnstsw ax; test
ah,0x44/0x05`; plain VC6 uses `0x40/0x01/0x41`. Count only tests preceded by
`fnstsw ax`, excluding integer strength reductions. Complete reproduction and
game-only censuses establish the distinction; Rich alone aggregates libraries.

### Game code only (round 1379c)

| Census | Server | TL | Gold |
| --- | ---: | ---: | ---: |
| PP compare forms | 0 | 723 | 693 |
| Plain `0x40/0x01` forms | 9 | 0 | 0 |

TL's 22 whole-image plain `0x01` sites lie in D3DX8. Of fourteen tested TL game
functions, eleven matched under all three generators and three only under PP
(`0x459940`, `0x4fffb0`, `0x492990`); none was plain-only.

### Does the Processor Pack work for the SERVER target? (round 1379e)

Nine of twelve tested server bodies were generator-insensitive. PP broke
`0x1000c3c0`, `0x100100a0` and `0x100151e0`, each containing plain x87 compares;
none was PP-only. The old partial-score PP pins were removed. This supports one
plain server generator, without proving a specific service pack from those bodies.

## Using the two clients as a reference for the remaining server work (round 1380)

Measure reference bodies and destination calls before treating names as twins.
Six investigated pairs differed beyond code-generator effects. Matched client
source can help recover logic, but cannot supply a server byte/provider claim.
The old residue counts and retired probe commands remain in the archive.

## Native findings

The entries below preserve address-specific observations and receipts. Pending
or applied statements describe their recorded checkpoint; consult current
source/metadata before acting on them.

- Gold and TL rand have different CRT threading variants: native GOLD0x5de784 whole-body matches stock msvc-6.0-sp5-pp LIBC.LIB `_rand`, build\intel\st_obj\rand.obj; native global seed slot0x62e108. LIBCMT whole-body probe misses. TL0x64d3f8 is already identified as LIBCMT `_rand`. Code origin is established; this does not by itself prove an entire runtime selection or linked provider without native link-map evidence. Receipts .scratch/goal-crt-retirement/{gold-rand-libc-library,gold-rand-library,gold-rand-native-asm}.json. Never recreate or patch either runtime body.

- DirectInput device correspondence is evidenced by identical complete GUIDs and native CreateDevice outputs: TL GUID66cc50/GUID_SysMouse (6f1d2b60-d5a0-11cf-bfc7-444553540000) equals unique Gold5eee60; TL pointer14ce8a0 maps to Gold1467360, acquired by Gold410710. TL GUID66cc40/GUID_SysKeyboard (6f1d2b61-d5a0-11cf-bfc7-444553540000) equals unique Gold5eee50; TL pointer14ce90c maps to Gold14673cc, acquired by Gold410740. Gold410770 uses DirectInputCreateA/version700, whereas TL411820 uses DirectInput8Create/version800; root interfaces must remain distinct. Evidence .scratch/goal-forward-ret/input-guid-cross-build.json and gold-input-init-asm.json. The compiler-image DINPUT.H confirms both GUID names and Acquire/Unacquire methods; receipt native-sdk-input-evidence.txt. No storage/type/header changes made from this read-only finding.

- Keyboard buffered-event ABI differs between clients: TL4124b0 calls vtable GetDeviceData(+0x28) with cbObjectData0x14 and a0x18 local frame; unique Gold4112e0 counterpart calls the same device method with cbObjectData0x10 and a0x14 frame. Gold device pointer14673cc matches the GUID-proven keyboard slot. This is a real DirectInput8/7 event-record difference, so an unchanged20-byte event import would alter Gold API behavior. Native receipts .scratch/goal-input-drain/gold-loop-candidates.json, gold-native.json, and .scratch/goal-input-types/drain-native.json.

- TL420b70 clears 0x6a0 bytes at14cbcc0; existing shared updater TL420ba0/Gold424810 bounds the byte index below0x6a and updates four-int rows, choosing columns0/1 or2/3. These independent accesses corroborate106 rows of16 bytes (1696 accessed bytes), not a storage owner. Native clear has one Gold37-byte counterpart4247e0 with table1460b00 and counters633178/633174/633180/63317c. Library probes negative; source reorganization pending. Evidence .scratch/goal-getter-extents/next-{native,counterpart,library,gold-library}.json and src/GOLDTL.fcn_00420ba0.c.

- Client packet statistics columns0/1 track received packets/bytes and2/3 sent packets/bytes: TL4210a0 loads native recv IAT662384 intoESI (calls4210ed/42114a), then calls updater420ba0 with flag1 at421262; send routine421290 passesflag0 at421328. The updater selects0/1 fortrue,2/3 forfalse. Field names remain reconstructed; native semantics are corroborated. Evidence .scratch/goal-net-stats/{packet-directions,update-call-context}.json.

- Native TL4737e0/Gold476c80 count six12-byte rows over72 accessedbytes, checking each firstword against-1. Corresponding table views TL1011980..10119c8 andGoldf8ab80..f8abc8 are positive whole-body matches after masking only start/end operands. Remaining row-word semantics, full backing allocation, subsystem and storage owner are unresolved. Evidence .scratch/goal-vfs-casefold/next-4737e0-native.json andnext-counterparts.json.

- Full native extents identify TL66080a as stock MT _strupr (308bytes, LIBCMT strupr.obj) andGold5eaad6 as stock ST _strupr (158bytes, LIBC strupr.obj). The competing strlwr bodies have7 and4 fixed-byte mismatches. Earlier library-match32-byte prefix candidates and legacy catalog __strlwr labels did not establish the exact member. Evidence .scratch/goal-vfs-casefold/full-runtime-attribution.json, pinned public index_library/match_bytes over stock archives previously validated byCLI.

- Dummy-object loader TL5a3580 invokes native _strupr at66080a (call5a35c2) before formatting dummy_%s; its existing C incorrectly calls _strlwr. Complete stock308-byte attribution distinguishes uppercase from lowercase. Source correction is staged in .scratch/goal-upper-call/candidate.c, not yet applied while VFS repairgate runs. Evidence .scratch/goal-vfs-casefold/other-case-caller-native.json andfull-runtime-attribution.json.

- TL40eca0 and Gold40dd90 have the same complete21-byte wrapper after masking only the call operand, but their native callees differ: TL450a00 is a38-byte counter/callback body and does not read the stack argument; Gold453890 begins with counters and reads byte[esp+4] before branching into a longer body. Same wrapper bytes do not establish unchanged callee semantics or justify importing the38-byte TL callee into Gold. TL source already has a char-width wrapper prototype; Gold scratch byte-width correction matches its21-byte native caller independently. Evidence .scratch/goal-small-extents/next-{gold-40dd90-tl-candidates,gold-453890-native,tl-450a00-native}.json.

- TL67bbdc/Gold5fcc78 form an accessed12-byte, three-float view. Shared updater native operands independently establish member offsets0/4/8; former scalar globals67bbe0/67bbe4 (Gold5fcc7c/5fcc80) are interior aliases. Existing header now supplies inferred VECTOR3 with x/y/z and canonical extern declarations; this names the shared layout, not an original SDK/game type or complete allocation. Another user g_6b86c4 has unresolved semantics, so the shared type is not renamed RGB. TL450b20 passes the first triple as ambient RGB to the material setter. The primary [Wine D3D8 interface header](https://raw.githubusercontent.com/wine-mirror/wine/master/include/d3d8.h) places SetMaterial at vtable index42/offset0xa8, matching native ff91a8000000 at450c5c. Microsoft [D3DMATERIAL8](https://learn.microsoft.com/en-us/previous-versions/ms886288(v=msdn.10)) describes the material colors. Configured SDK8 probe failed C1083 missingd3d8.h; no SDK layout assertion passed. Complete backing extent and storage owners remain unresolved. Receipts .scratch/goal-material-colors/{method-binding,field-alias-bindings,alias-metadata-preview}.json.

- Native literal audits found placeholder strings in TL C bodies despite zero common-prefix differences: TL401470 emits `array count mismatch`, while its native operand points to675058 `bio_rd_array_debug: Tried to load invalid array-sizes...`; TL40cba0 emits `invalid object`, while native675da8 contains `WalkToDummyRotate(): invalid character or dummy`. Masked relocation agreement does not establish literal equality. These bodies require real literal recovery before strict promotion; original-name/source-path evidence must be checked against the native string push. Evidence `.scratch/goal-small-client-helpers/placeholder-string-evidence.json`.

- TL entity-query table pointer: canonical `g_entity_ptr` binds to native `0x0090e094` (four-byte word in `.data` zero-filled virtual tail). Complete native users `gm_SearchStruct` (`0x00504100`, 39 bytes) and `gm_SearchTable67` (`0x00504e70`, 62 bytes), plus existing matched reset/cleanup users, agree. Allocation witness at `0x005010b2-0x005010dc` passes `f3_gm:lpGebaeudeINST`, allocates `0xa900` bytes (256 records of stride `0xa9`), stores the result in that word and zeroes the buffer. This identifies the logical pointer; its native standalone owner or containing allocation remains unresolved. The managed row is declaration-only, with no backing or native link-symbol claim and no new C definition. Evidence: `.scratch/goal-tl-query-bindings/allocation-witness.json`, `extent-audit.json`, `users.json`. Gold independently compiled shared search/reset/cleanup bodies agree on `0x00889f74`; native allocation at `0x004fe5e2-0x004fe60c` passes the same complete label at `0x0061aa00`, allocates/zeroes `0xa900` bytes, and stores/loads that four-byte `.data` virtual-tail word. Gold storage owner/backing remain unresolved. Gold evidence: `.scratch/goal-gold-query-bindings/{extent-audit,allocation-witness,users}.json`.

- TL building-prototype table pointer: canonical `g_entity_type_table` binds native `0x00868050`, a four-byte `.data` virtual-tail word. Native initialization at `0x0050108a-0x005010a3` allocates `0xca78` bytes (88 records, stride `0x24d`) with complete label `f3_gm:lpGebaeudePROT` at `0x00699748`. All aligned canonical users agree; 20-user catalog comparisons preserve compiled bytes and scores. Logical identity is verified; native storage owner/backing remains unresolved. Declaration-only metadata allocates no storage. Evidence: `.scratch/goal-tl-prototype-bindings/{allocation-witness,users,binding-effects,extent-audit}.json`.

- Animation callback TL406410 / GOLD405870 follows the same pointer chain (`obj+0x34`, then `+0x1cc`) but reads its blocking word at TL+0x390 versus GOLD+0x84. The complete 248-byte bodies otherwise agree after nine validated relocations. `REBREW_GOLD` is an inferred build selector, not an attested original macro; it selects only this shared source's `ANIMATION_BLOCK_OFFSET`. The logical member name and full containing layout remain unresolved. Omitting the selector reproduces exactly the two displacement-byte differences at offsets47/48 with no invalid relocations. Evidence `.scratch/goal20/padded-callback-{differences,without-selector}.json` and fresh dual-target callback tests.


- TL CharacterClearSitting406560 uses the existing seat at character+0x74
  after a conditional call to402aa0, whose complete native body is a single RET.
  It obtains the animation name from seat+0x68 and passes model+0xf4 first,
  name second, to435500; the model pointer is at entity+0x1ec. It clears the
  seat pointer and sitting bit0x10, preserving the other flag bits. Four other
  source users already treat402aa0 as void. The corrected C stops treating its
  stale EAX as a replacement seat and restores the native argument order.
  Original helper name/TU context and complete entity/seat types remain unknown.
  Evidence: `.scratch/goal20/clear-sitting-{original-current,noop-original,
  behavior,call-audit}.json`.

- TL initializer4a1130 registers the native action name `Buergerrecht`
  (literal67edf8) with type0x19, starter499a50 and run499ad0. The starter is
  a125-byte four-argument handler with3 trailing layout NOPs, not the130-byte
  `ahm_ProcessEntityChain` dispatcher at4c4d30. Its threshold uses the native
  float pools66417c (0.44f) and664340 (16000.0f). This proves the action
  association, not an original C function name or source unit. Evidence:
  `.scratch/goal20/citizenship-registration.json` and `ahm-chain-original.json`.

- GOLD independently registers `Buergerrecht` at initializer4a16f0 with
  name600190 and starter49a010. Its125-byte starter shares the recovered TL C
  body; the global byte is6f1bc5, query helper509ee0, and float pools5ecef0/
  5ed0a8. Managed existing globals/callee aliases map these targets; no new
  storage is defined. Resolving all four COFF operands reproduces each native
  body, and both complete float payloads match. This is stronger body evidence
  than masked relocation agreement but does not establish a raw client link.
  Evidence `.scratch/goal20/citizenship-{starter-audit,gold-audit}.json`.

- Shared plant lookup SERVER10014ee0/TL4bcb80/GOLD4bc5a0 has a complete69-byte
  body followed by11 layout NOPs. Its three native table operands identify
  SERVER1002d878/TL6814a8/GOLD602840. The initialized table contains TANNE,
  BUCHE and EICHE plus a zero-id terminator: four70-byte records,280 bytes.
  All three complete payloads equal the single C definition (SHA256
  21d9adb5a8c9a11e3be5e349d24035e362575ab1d020d739099ae7cf3d40e3c1).
  Resolving every COFF operand reproduces all69 native code bytes; wrong+4
  table bindings reject. This proves each native table binding and full extent,
  not linked client placement. `plt_FindPlantInfo`/`plt_PlantInfo` are inferred
  names, and the meanings of f42/f43/f44 remain unresolved. Evidence:
  `.scratch/goal20/plant-lookup-audit.json`.

- The native filtered-entity iterator is TL503e80/GOLD501030, not
  `gm_AddObjekt` as the old TL identity claimed. The existing shared
  `gm_FindNextFilteredEntity` body in spiel.c compiles to all341 native bytes
  in both clients, followed by11 alignment NOPs; its SERVER body is346 bytes.
  A bounded traversal reaches every client instruction and the final return;
  the conservative linear extent reader stops at an internal jump after89
  bytes and cannot establish this function's complete extent. All20 COFF
  relocation sites resolve to the native addresses, and each wrong+4 global
  binding rejects. TL has all11 global names mapped; GOLD still lacks nine
  corresponding declaration bindings. These are code/operand proofs, not
  linked client data verification. Evidence:
  `.scratch/goal20/stat-shared-iterator-audit.json`.

- TL4e7600/GOLD4e5af0 append eight signed integer fields to a statistic buffer:
  six values at entity offsets190/194/198/19c/1a0/1a4, followed by the entity
  accumulation result and slot-wide accumulation result. The only direct
  caller in each image ignores the formatter's return. Plain C with the
  existing shared helpers reproduces all90 bytes and the complete25-byte
  format literal in both clients; wrong+4 controls reject all four operands.
  The slot helper TL50dac0/GOLD50a640 is already the shared124-byte
  `gm_WalkEntityChain(unsigned short)` body. The formatter pushes a partial
  AX load, and the helper compares SI then masks the index to16 bits before
  addressing its768-entry table. The numeric client helper duplicates that
  source; the later consolidation receipt below supersedes that duplicate.
  The formatter is now recovered in shared server.c as the inferred
  `srv_FormatStatTreasury`, RELOC90 in both clients. Its false TL `srv_Init`
  binding was corrected without changing the true server initializer.
  Evidence: `.scratch/goal20/stat-formatter-family-native.json`,
  `stat-formatter-c-probe.json`, `stat-formatter-behavior.json`.

- The numeric slot helper TL50dac0/GOLD50a640 now binds the existing
  `gm_WalkEntityChain(unsigned short)` implementation in spiel.c, shared with
  SERVER10019be0. Both client bodies match 124 bytes. All 52 referring files
  use the canonical prototype in reconstructed spiel.h, and the last
  unowned duplicate source is retired. Complete COFF comparison preserves
  all 82 caller groups and 108 function bodies; it also preserves both shared
  client translation units. This changes source ownership, not the matched
  function totals or client linked-data evidence. Evidence:
  `.scratch/goal20/stat-helper-replay.json` and
  `stat-helper-after-final-prototype/`.

- Full bounded control-flow traversal of the six statistic formatters in
  both clients establishes complete bodies of 159/179/68/87/90/147 bytes,
  followed only by alignment NOPs. The first and last bodies contain internal
  jumps; the conservative linear reader's earlier 19/57-byte results are
  partial extents. The attributes format literal contains six floating-point
  conversions, but the native call passes five float-to-double arguments,
  one int and one signed short. Preserve this original mismatch when
  reconstructing bytes; changing the int to a float would change the native
  call sequence. Both the native operands and every literal byte are compared.
  Evidence: `.scratch/goal20/stat-family-full-bounds.json` and
  `stat-attributes-skills-probe/receipt.json`.

- The remaining statistic formats are complete 37-byte identity, 13-byte
  four-string category, and 6-byte relationship literals in native .data in
  both clients. TL68d934's old .rdata annotation was wrong and is now repaired
  to a complete 13-byte .data compiler-literal row.
  The indexed table TL14a5c6c/GOLD143ab0c supplies the four `%s` arguments;
  its entries are pointer-sized, not an established integer array. It lies
  in the zero-filled virtual tail, so the shipped image does not provide its
  runtime strings or establish its full extent or storage owner. Do not
  allocate a replacement table from its extern-only declaration. Evidence:
  `.scratch/goal20/stat-remaining-data-evidence.json`.

- The fourth statistic formatter reads the entity's four office-role bytes
  at +0x166..+0x169 and formats their string-table entries. The fields' use in
  aemter.c establishes the office interpretation; the original formatter name
  and source placement are still inferred. One reconstructed aemter.h supplies
  the pointer declaration to the shared formatter and existing UI reader.
  Neither the header nor the two declaration-only alias rows defines storage
  or claims a complete table extent. LINK resolves even this discarded body's
  undefined table reference: compiling it into server.c failed with LNK2001.
  The recovered body now lives once in a client-only server_stats.c selected
  by the two client identities. That placement is inferred, and no replacement
  table or preprocessor guard is used to make the server link. Evidence:
  `.scratch/goal20/stat-offices-probe/receipt.json` and
  `stat-offices-recovery/receipt.json`, `stat-offices-server-gate.log` and
  `stat-offices-client-unit.json`.

- The current inferred name `gm_LookupEntityRecordById` is ambiguous across
  the reconstructed client tree. The shared server helper's complete 56-byte
  body searches 768 records and matches TL508e40/GOLD505df0 after resolving
  the ID field as slot-table +4. TL4cef30's separate body searches only 32
  records at9b4a40..9b8dc0. Its current inferred name does not make those
  different storage domains interchangeable. Reconcile native call destinations
  before renaming callers; the shared helper's missing client ID-field rows
  must describe interior views, not new allocations. Evidence:
  `.scratch/goal20/stat-record-lookup-probe/receipt.json` and
  `src/Develop/DieGildeAddOn/game/GOLDTL.spiel62.c`.

- TL's statistic dump begin/end routines at4e73c0/4e77e0 each contain one
  sprintf call and return after34 bytes, followed by14 alignment NOPs.
  Their complete54/52-byte literals match the reconstructed messages, but
  there are no native log calls supporting server.c's four placeholder calls.
  The year operand is TL7f4c00, the first four bytes of the existing packed
  calendar view. Its inferred shared scalar spelling `_g_current_year` now
  resolves through the view's recorded native link symbol without replacing
  its analysis label or allocating storage. A full Gold .text scan finds neither complete masked code pattern,
  and the Gold file contains neither delimiter literal. No Gold counterpart
  is established; applying the adjacent six-formatter VA shift is wrong
  (the guessed end address is an existing building-table initializer).
  The four placeholder calls are removed; both complete shared bodies verify
  as RELOC34, and the final unowned numeric duplicates are retired. The
  complete54/52-byte .data formats are compiler-literal rows, not new storage
  or linked-client data verdicts. Independent production-object comparisons
  validate every operand/literal byte and reject wrong bindings;79 surrounding
  bodies and typed operands remain unchanged across affected builds. The
  backing calendar allocation's full extent and owner remain unresolved.
  Evidence: `.scratch/goal20/stat-dump-delimiters-native.json`,
  `stat-delimiters-final-native.json`, `stat-delimiters-final-objects/` and
  `stat-delimiters-retirement.json`.

- Rebrew's shared relocation catalog must index a data row's exact native
  `link_symbol` as well as its analysis label within the selected target.
  Ignoring the native spelling forced valid field views/compiler literals to
  remain unknown to comparisons. Upstream080277bb fixes the common builder;
  four regressions fail before,97 focused tests, all18 hooks and the frozen
  full suite(11567passed/50skipped) pass. The project's three-target audit
  finds no native-spelling conflicts or catalog disagreements. Existing
  unknown-address policy is unchanged. Evidence:
  `.scratch/goal20/native-data-catalog-integration.json`.

- The native office queries contain no log calls. Slot queries copy two
  24-byte rows; affinity reads unsigned-byte rank at template+8 and a
  7x7 float matrix. TL extents121/124/193 and Gold121/193 are complete;
  no Gold council counterpart is established. Its neighboring Gold address
  is affinity, so a family-wide VA shift would bind the wrong function.
  All960 role-template and196 matrix initializer bytes equal the server's
  aemter.c data. Client rows remain declaration-only aliases, not new storage
  or linked verification. The slot declaration alone does not prove its full
  backing extent. Evidence: .scratch/goal20/office-query-integration-before/
  data-evidence.json and office-query-final-objects-refresh/{18,19}.json.

- A completely superseded multi-body source needs evidence for every body,
  owner and reference before deletion. The importer's intentional single-body
  restriction does not authorize deleting helpers or storage. This explicit
  query-unit edit separately checks both old bodies and all five target claims
  against native bytes, retains backups and leaves the automatic guard intact.
  The missing automation is recorded upstream as7ff37e19. Evidence:
  .scratch/goal20/office-query-duplicate-retirement/receipt.json.

- The first statistic formatter's invalid-class fallback points exactly240
  bytes beyond the guarded10x24 class-name view in both clients. Its neighbor
  is TL's Begin statistic delimiter, but Gold's first-formatter format string.
  Equal code does not imply equal neighboring string contents. The next shared
  source probe should preserve the table-relative address; the complete backing
  extent and original source expression are unproven. Do not introduce a
  common inline fallback literal or a new allocation. Evidence:
  .scratch/goal20/stat-identity-provider-evidence.json and
  stat-identity-fallback-view.json. All5 indexed name-pointer tables are in each
  client's zero-filled virtual tail; their complete extents/owners are unresolved.

- The first formatter now uses one shared `srv_FormatStatIdentity` body at
  TL4e73f0/Gold4e58e0: both complete159-byte native bodies, every operand and
  the37-byte format match, with wrong-address controls. The fallback retains
  the class-table+240 view. Gold's native year operand is770ae0, not770b60;
  a declaration-only four-byte `g_current_year` view binds it. Seven existing
  Gold target/flag groups have no current-year operand in their bound bodies.
  The broader legacy `g_7f4c00` users/catalog remain unchanged. No backing
  owner, full table extent, new storage or linked data verdict is inferred.
  All85 surrounding bodies/typed operands and21 affected client checks pass.
  Evidence: .scratch/goal20/stat-identity-shared-probe/receipt.json,
  stat-identity-final-objects/ and stat-identity-binding-before/receipt.json.

- Pool helpers TL41e440/41e490/41e4d0 have complete69/61/93-byte bodies,
  followed by11/3/3 NOPs. They contain no calls or relocations. Their existing
  shared m_alloc.c definitions now match every native byte after removal of
  three unsupported entry logs. Clear returns the sum of occupied slots and
  resets each block's used count and every slot's leading occupied word;
  it does not erase slot payloads. Info reports only the first block. Stats
  sums blocks/used/capacity and averages stride per block, not per slot.
  All33 surrounding bodies and typed operands remain unchanged across the
  server/TL/Gold compiler contexts. No header, caller or allocation changed.
  Evidence: .scratch/goal20/pool-clear-info-stats-objects/ and
  pool-clear-info-stats-recovery/receipt.json.

- The bounded pool iterator is131 bytes plus13 NOPs in both clients
  (TL41e350/Gold422ba0). First is39+9 (TL41e3e0/Gold422c30), and free-all
  is43+5 (TL41e410/Gold422c60). First/free-all have exactly one native call,
  to their iterator and tracked-free body respectively. The no-log shared
  first/free-all bodies reproduce every native byte and operand in both
  clients; their production consolidation remains pending. Gold's first
  stored48-byte span includes9 NOPs. The current no-log iterator compiles
  to136 bytes, with loop rotation/register differences; it is not matched.
  Nine C spellings, four targeted optimization controls, two state-type
  controls, two CPU controls and three induction controls are saved rejected
  evidence, not native-body or original-type claims. No asm or guessed
  storage binding was introduced. Evidence: .scratch/goal20/pool-shared-frontier-probe/
  and pool-next-{c-shapes,flag-controls,state-controls,induction-controls}/.
