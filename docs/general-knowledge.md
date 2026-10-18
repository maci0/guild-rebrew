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
`Z:\home\…` text. The old host-prefix mapping example is historical. Compilation uses
unshare and the pinned toolchain image filesystem; CMake and `verify` both
honor that backend.

## The data sections are complete, and `rebrew todo` was reporting 123 phantoms (round 1078)

Historical postlinked measurements, not current data completion. Server has no
`.idata`: IAT is at `.rdata` head (RVA `0x24000`, 416 bytes). The `.data` virtual
tail begins at `0x10035000` and ends `0x1176759c`; loader zero-fill has no reference
file payload. A comparison denominator must distinguish file bytes, imports,
zero-fill and unknown extents. See [data ownership](data-ownership.md).

## Section-by-section parity: the shipped file is byte-identical outside `.text`, BY COPYING, NOT BY COMPILING (round 1089, corrected round 1092)

The historical completion claim was retracted: postlink supplied those equal bytes.
Later raw server identity is independent evidence; it does not validate that pipeline.
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

Address-specific checkpoint evidence, not a work queue. Continuation is
[TODO.md](TODO.md). A placement below is what that receipt recorded; re-read
source and metadata before treating it as the live tree.

- Gold and TL `rand` use different CRT threading variants. Native Gold
  `0x5de784` matches stock msvc-6.0-sp5-pp `LIBC.LIB` `_rand`
  (`build\intel\st_obj\rand.obj`) over the whole body; the seed slot is
  `0x62e108`. A LIBCMT whole-body probe misses. TL `0x64d3f8` is LIBCMT
  `_rand`. That is code origin, not a whole runtime selection or the linked
  provider; the provider still needs the native link map. Do not recreate or
  patch either runtime body. Receipts:
  `.scratch/goal-crt-retirement/{gold-rand-libc-library,gold-rand-library,gold-rand-native-asm}.json`.

- DirectInput correspondence is identical complete GUIDs plus native
  `CreateDevice` outputs. TL `0x66cc50` / `GUID_SysMouse`
  (`6f1d2b60-d5a0-11cf-bfc7-444553540000`) equals unique Gold `0x5eee60`;
  TL pointer `0x14ce8a0` maps to Gold `0x1467360`, acquired by Gold `0x410710`.
  TL `0x66cc40` / `GUID_SysKeyboard`
  (`6f1d2b61-d5a0-11cf-bfc7-444553540000`) equals unique Gold `0x5eee50`;
  TL pointer `0x14ce90c` maps to Gold `0x14673cc`, acquired by Gold `0x410740`.
  Gold `0x410770` uses `DirectInputCreateA` / version 700; TL `0x411820` uses
  `DirectInput8Create` / version 800. The root interfaces stay distinct. The
  compiler-image `DINPUT.H` names both GUIDs and Acquire/Unacquire. The receipt
  changes no storage, type, or header. Evidence:
  `.scratch/goal-forward-ret/input-guid-cross-build.json`,
  `gold-input-init-asm.json`, `native-sdk-input-evidence.txt`.

- Keyboard buffered-event ABI differs. TL `0x4124b0` calls vtable
  `GetDeviceData` (+`0x28`) with `cbObjectData` `0x14` and a `0x18` frame.
  Unique Gold `0x4112e0` calls the same method with `cbObjectData` `0x10` and
  a `0x14` frame. Gold device pointer `0x14673cc` is the GUID-proven keyboard
  slot. This is a DirectInput 8 versus 7 record difference: importing the TL
  20-byte event unchanged would alter Gold API behavior. Receipts:
  `.scratch/goal-input-drain/gold-loop-candidates.json`, `gold-native.json`,
  `.scratch/goal-input-types/drain-native.json`.

- TL `0x420b70` clears `0x6a0` bytes at `0x14cbcc0`. Shared updater TL
  `0x420ba0` / Gold `0x424810` bounds the byte index below `0x6a` and updates
  four-int rows, columns 0/1 or 2/3. Those accesses corroborate 106 rows of
  16 bytes (1696 accessed bytes). They do not name a storage owner. The clear
  has one Gold 37-byte counterpart `0x4247e0`, table `0x1460b00`, counters
  `0x633178`, `0x633174`, `0x633180`, and `0x63317c`. Library probes were
  negative. Evidence:
  `.scratch/goal-getter-extents/next-{native,counterpart,library,gold-library}.json`,
  `src/GOLDTL.fcn_00420ba0.c`.

- Client packet-statistic columns 0/1 are received packets/bytes and 2/3 are
  sent packets/bytes. TL `0x4210a0` loads recv IAT `0x662384` into ESI (calls
  `0x4210ed` and `0x42114a`), then calls updater `0x420ba0` with flag 1 at
  `0x421262`. Send routine `0x421290` passes flag 0 at `0x421328`. The updater
  selects 0/1 for true and 2/3 for false. Field names are reconstructed; the
  direction split is corroborated. Evidence:
  `.scratch/goal-net-stats/{packet-directions,update-call-context}.json`.

- Native TL `0x4737e0` / Gold `0x476c80` count six 12-byte rows over 72
  accessed bytes and compare each first word with -1. Table views TL
  `0x1011980`..`0x10119c8` and Gold `0xf8ab80`..`0xf8abc8` match after masking
  only the start and end operands. Row-word semantics, the full backing
  allocation, the subsystem, and the storage owner were unresolved. Evidence:
  `.scratch/goal-vfs-casefold/next-4737e0-native.json`,
  `next-counterparts.json`.

- Full extents: TL `0x66080a` is stock MT `_strupr` (308 bytes, LIBCMT
  `strupr.obj`) and Gold `0x5eaad6` is stock ST `_strupr` (158 bytes, LIBC
  `strupr.obj`). The competing `strlwr` bodies have 7 and 4 fixed-byte
  mismatches. A 32-byte library-match prefix and the legacy catalog label
  `__strlwr` did not identify the member. Evidence:
  `.scratch/goal-vfs-casefold/full-runtime-attribution.json`, from pinned
  public `index_library` / `match_bytes` over stock archives the CLI had
  already accepted.

- Dummy-object loader TL `0x5a3580` calls native `_strupr` at `0x66080a`
  (call `0x5a35c2`) before formatting `dummy_%s`. The stock 308-byte member is
  uppercase. The Goal83 correction is in the dummy and town readers; both call
  `_strupr`. The older staged lowercase claim is superseded. Receipts:
  `.scratch/goal83-tl-casefold/`. Evidence:
  `.scratch/goal-vfs-casefold/other-case-caller-native.json`,
  `full-runtime-attribution.json`.

- TL `0x40eca0` and Gold `0x40dd90` are the same 21-byte wrapper after masking
  only the call operand, but the callees differ. TL `0x450a00` is a 38-byte
  counter/callback and does not read the stack argument. Gold `0x453890`
  starts with counters, reads `byte [esp+4]`, then enters a longer body. Equal
  wrapper bytes do not keep the callee's meaning, and they do not justify
  importing the 38-byte TL callee into Gold. The TL source has a char-width
  wrapper prototype. A Gold scratch byte-width correction matches its own
  21-byte caller. Evidence:
  `.scratch/goal-small-extents/next-{gold-40dd90-tl-candidates,gold-453890-native,tl-450a00-native}.json`.

- TL `0x67bbdc` / Gold `0x5fcc78` is an accessed 12-byte, three-float view.
  Shared updater operands put members at offsets 0/4/8. Former scalar globals
  `0x67bbe0` / `0x67bbe4` (Gold `0x5fcc7c` / `0x5fcc80`) are interior aliases.
  The checkpoint header supplies an inferred `VECTOR3` with `x`/`y`/`z` and
  canonical externs. That names the shared layout, not an original SDK or game
  type, and not the complete allocation. User `g_6b86c4` has unresolved
  semantics, so the shared type is not renamed `RGB`. TL `0x450b20` passes the
  first triple as ambient RGB to the material setter. The primary
  [Wine D3D8 interface header](https://raw.githubusercontent.com/wine-mirror/wine/master/include/d3d8.h)
  places `SetMaterial` at vtable index 42 / offset `0xa8`, matching native
  `ff 91 a8 00 00 00` at `0x450c5c`. Microsoft
  [D3DMATERIAL8](https://learn.microsoft.com/en-us/previous-versions/ms886288(v=msdn.10))
  describes the material colors. The configured SDK8 probe failed `C1083`
  (`d3d8.h` missing); no SDK layout assertion passed. Complete backing extent
  and storage owners were unresolved. Receipts:
  `.scratch/goal-material-colors/{method-binding,field-alias-bindings,alias-metadata-preview}.json`.

- Placeholder strings remain in TL C despite zero common-prefix differences.
  TL `0x401470` emits `array count mismatch`, while native `0x675058` is
  `bio_rd_array_debug: Tried to load invalid array-sizes...`. TL `0x40cba0`
  emits `invalid object`, while native `0x675da8` is
  `WalkToDummyRotate(): invalid character or dummy`. Masked relocation
  agreement is not literal equality. A strict promotion needs the native
  string, and any original name or source path has to match that push.
  Evidence: `.scratch/goal-small-client-helpers/placeholder-string-evidence.json`.

- TL entity-query table pointer: canonical `g_entity_ptr` binds to native `0x0090e094` (four-byte word in `.data` zero-filled virtual tail). Complete native users `gm_SearchStruct` (`0x00504100`, 39 bytes) and `gm_SearchTable67` (`0x00504e70`, 62 bytes), plus existing matched reset/cleanup users, agree. Allocation witness at `0x005010b2-0x005010dc` passes `f3_gm:lpGebaeudeINST`, allocates `0xa900` bytes (256 records of stride `0xa9`), stores the result in that word and zeroes the buffer. This identifies the logical pointer; its native standalone owner or containing allocation remains unresolved. The managed row is declaration-only, with no backing or native link-symbol claim and no new C definition. Evidence: `.scratch/goal-tl-query-bindings/allocation-witness.json`, `extent-audit.json`, `users.json`. Gold independently compiled shared search/reset/cleanup bodies agree on `0x00889f74`; native allocation at `0x004fe5e2-0x004fe60c` passes the same complete label at `0x0061aa00`, allocates/zeroes `0xa900` bytes, and stores/loads that four-byte `.data` virtual-tail word. Gold storage owner/backing remain unresolved. Gold evidence: `.scratch/goal-gold-query-bindings/{extent-audit,allocation-witness,users}.json`.

- TL building-prototype table pointer: canonical `g_entity_type_table` binds native `0x00868050`, a four-byte `.data` virtual-tail word. Native initialization at `0x0050108a-0x005010a3` allocates `0xca78` bytes (88 records, stride `0x24d`) with complete label `f3_gm:lpGebaeudePROT` at `0x00699748`. Aligned canonical users agree. The 20-user checkpoint comparisons preserved compiled bytes. Logical identity is verified; native storage owner and backing were unresolved. The declaration-only row allocates no storage. Evidence: `.scratch/goal-tl-prototype-bindings/{allocation-witness,users,binding-effects,extent-audit}.json`.

- Animation callback TL `0x406410` / Gold `0x405870` follows `obj+0x34`, then
  `+0x1cc`, but the blocking word is TL `+0x390` versus Gold `+0x84`. The
  248-byte bodies otherwise agree after nine validated relocations.
  `REBREW_GOLD` is an inferred build selector, not an attested macro; it
  selects only this shared source's `ANIMATION_BLOCK_OFFSET`. The member name
  and containing layout were unresolved. Omitting the selector reproduces the
  two displacement bytes at offsets 47 and 48 and no invalid relocation.
  Evidence: `.scratch/goal20/padded-callback-{differences,without-selector}.json`
  and the dual-target callback tests recorded with that receipt.

- TL `CharacterClearSitting` `0x406560` uses the seat at character `+0x74`
  after a conditional call to `0x402aa0`, whose native body is a single `RET`.
  The animation name is at seat `+0x68`. The call to `0x435500` passes
  model `+0xf4` first and the name second; the model pointer is at entity
  `+0x1ec`. It clears the seat pointer and sitting bit `0x10` and leaves the
  other flag bits. Four other source users treat `0x402aa0` as void. The
  corrected C does not treat the stale `EAX` as a replacement seat, and it
  restores the native argument order. The original helper name, TU, and
  complete entity/seat types were unknown. Evidence:
  `.scratch/goal20/clear-sitting-{original-current,noop-original,behavior,call-audit}.json`.

- TL initializer `0x4a1130` registers `Buergerrecht` (literal `0x67edf8`) with
  type `0x19`, starter `0x499a50`, and run `0x499ad0`. The starter is a
  125-byte four-argument handler with 3 trailing layout NOPs, not the 130-byte
  `ahm_ProcessEntityChain` dispatcher at `0x4c4d30`. Its threshold uses float
  pools `0x66417c` (`0.44f`) and `0x664340` (`16000.0f`). This is the action
  association, not an original C name or source unit. Evidence:
  `.scratch/goal20/citizenship-registration.json`, `ahm-chain-original.json`.

- Gold registers `Buergerrecht` at initializer `0x4a16f0`, name `0x600190`,
  starter `0x49a010`. Its 125-byte starter shares the recovered TL C body.
  The global byte is `0x6f1bc5`, the query helper is `0x509ee0`, and the float
  pools are `0x5ecef0` / `0x5ed0a8`. Existing global and callee aliases map
  these targets; the receipt defines no new storage. All four COFF operands
  reproduce each native body, and both float payloads match. That is stronger
  than masked relocation agreement and is not a raw client link. Evidence:
  `.scratch/goal20/citizenship-{starter-audit,gold-audit}.json`.

- Shared plant lookup server `0x10014ee0` / TL `0x4bcb80` / Gold `0x4bc5a0`
  is 69 bytes plus 11 layout NOPs. The table operands are server `0x1002d878`,
  TL `0x6814a8`, and Gold `0x602840`. The table is TANNE, BUCHE, EICHE, and a
  zero-id terminator: four 70-byte records, 280 bytes. All three payloads
  equal one C definition (SHA256
  `21d9adb5a8c9a11e3be5e349d24035e362575ab1d020d739099ae7cf3d40e3c1`).
  Every COFF operand reproduces the 69 code bytes; wrong `+4` table bindings
  reject. That proves each table binding and the full extent, not linked
  client placement. `plt_FindPlantInfo` / `plt_PlantInfo` are inferred, and
  `f42` / `f43` / `f44` were unresolved. Evidence:
  `.scratch/goal20/plant-lookup-audit.json`.

- The filtered-entity iterator is TL `0x503e80` / Gold `0x501030`, not
  `gm_AddObjekt` as the old TL identity claimed. Shared
  `gm_FindNextFilteredEntity` in `spiel.c` compiles to all 341 client bytes
  plus 11 alignment NOPs; the server body is 346 bytes. A bounded traversal
  reaches every client instruction and the final return. The linear extent
  reader stops at an internal jump after 89 bytes and does not establish the
  complete extent. All 20 COFF relocations resolve, and each wrong `+4`
  global binding rejects. At this checkpoint TL had all 11 global names
  mapped and Gold lacked nine declaration bindings. These are code and
  operand proofs, not linked client data verification. Evidence:
  `.scratch/goal20/stat-shared-iterator-audit.json`.

- TL `0x4e7600` / Gold `0x4e5af0` append eight signed integers to a statistic
  buffer: entity offsets `0x190`, `0x194`, `0x198`, `0x19c`, `0x1a0`, and
  `0x1a4`, then the entity accumulation and the slot-wide accumulation. The
  only direct caller in each image ignores the return. Plain C with the shared
  helpers reproduces all 90 bytes and the 25-byte format literal in both
  clients; wrong `+4` controls reject all four operands. Slot helper TL
  `0x50dac0` / Gold `0x50a640` is the shared 124-byte
  `gm_WalkEntityChain(unsigned short)` body. The formatter pushes a partial
  AX load. The helper compares SI, masks the index to 16 bits, and addresses
  a 768-entry table. A numeric client duplicate of that helper is superseded
  by the consolidation receipt below. The checkpoint recovered the formatter
  in shared `server.c` as inferred `srv_FormatStatTreasury`, RELOC 90 in both
  clients, and corrected a false TL `srv_Init` binding without changing the
  server initializer. Evidence:
  `.scratch/goal20/stat-formatter-family-native.json`,
  `stat-formatter-c-probe.json`, `stat-formatter-behavior.json`.

- The same slot helper, TL `0x50dac0` / Gold `0x50a640`, is the
  `gm_WalkEntityChain(unsigned short)` body in `spiel.c`, shared with server
  `0x10019be0`. Both client bodies match 124 bytes. All 52 referring files
  use the canonical prototype in reconstructed `spiel.h`, and the last unowned
  duplicate source was retired. COFF comparison preserved all 82 caller
  groups, 108 function bodies, and both shared client translation units.
  That changes source ownership, not matched-function totals or client
  linked-data evidence. Evidence: `.scratch/goal20/stat-helper-replay.json`,
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
  both clients. TL `0x68d934`'s old `.rdata` annotation was wrong; the
  checkpoint repaired it as a complete 13-byte `.data` compiler-literal row.
  The indexed table TL `0x14a5c6c` / Gold `0x143ab0c` supplies the four `%s` arguments;
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
  undefined table reference: compiling it into `server.c` failed with `LNK2001`.
  The checkpoint placed the recovered body once in client-only `server_stats.c`,
  selected by the two client identities. That placement is inferred. No
  replacement table or preprocessor guard was added to make the server link.
  Evidence:
  `.scratch/goal20/stat-offices-probe/receipt.json` and
  `stat-offices-recovery/receipt.json`, `stat-offices-server-gate.log` and
  `stat-offices-client-unit.json`.

- Inferred `gm_LookupEntityRecordById` is ambiguous in the client tree. The
  shared server helper's 56-byte body searches 768 records and matches TL
  `0x508e40` / Gold `0x505df0` with the ID field at slot-table `+4`. TL
  `0x4cef30` searches only 32 records at `0x9b4a40`..`0x9b8dc0`. The shared
  name does not make those storage domains interchangeable. Call destinations
  decide a rename. Missing client ID-field rows are interior views, not new
  allocations. Evidence:
  `.scratch/goal20/stat-record-lookup-probe/receipt.json` and
  `src/Develop/DieGildeAddOn/game/GOLDTL.spiel62.c`.

- TL statistic-dump begin/end routines at `0x4e73c0` / `0x4e77e0` each
  contain one `sprintf` and return after 34 bytes, followed by 14 alignment
  NOPs. Their 54-byte and 52-byte literals match the reconstructed messages.
  No native log call supports the four placeholder calls that were in
  `server.c`. The year operand is TL `0x7f4c00`, the first four bytes of the
  packed calendar view. Inferred `_g_current_year` resolves through that
  view's recorded native link symbol, keeps the analysis label, and allocates
  no storage. A full Gold `.text` scan finds neither masked code pattern, and
  the Gold file contains neither delimiter literal. No Gold counterpart is
  established. Shifting by the adjacent six formatters is wrong: the guessed
  end address is an existing building-table initializer. The checkpoint
  removed the four placeholder calls. Both shared bodies verify as RELOC 34,
  and the last unowned numeric duplicates were retired. The 54-byte and
  52-byte `.data` formats are compiler-literal rows, not new storage or
  linked-client data verdicts. Production-object comparisons accept every
  operand and literal byte and reject wrong bindings. 79 surrounding bodies
  and typed operands stayed unchanged. The calendar allocation's full extent
  and owner were unresolved.
  Evidence: `.scratch/goal20/stat-dump-delimiters-native.json`,
  `stat-delimiters-final-native.json`, `stat-delimiters-final-objects/` and
  `stat-delimiters-retirement.json`.

- Rebrew's shared relocation catalog must index a data row's exact native
  `link_symbol` as well as its analysis label within the selected target.
  Ignoring the native spelling forced valid field views/compiler literals to
  remain unknown to comparisons. Upstream `080277bb` fixes the common builder.
  Four regressions fail before that fix; 97 focused tests, all 18 hooks, and
  the frozen full suite (11567 passed, 50 skipped) pass. The three-target audit
  finds no native-spelling conflicts or catalog disagreements. Existing
  unknown-address policy is unchanged. Evidence:
  `.scratch/goal20/native-data-catalog-integration.json`.

- The native office queries contain no log calls. Slot queries copy two
  24-byte rows. Affinity reads an unsigned-byte rank at template `+8` and a
  7 by 7 float matrix. TL extents 121/124/193 and Gold extents 121/193 are
  complete. No Gold council counterpart is established; the neighboring Gold
  address is affinity, so a family-wide VA shift binds the wrong function.
  All 960 role-template bytes and 196 matrix-initializer bytes equal the
  server `aemter.c` data. Client rows are declaration-only aliases: not new
  storage and not linked verification. The slot declaration does not prove
  the full backing extent. Evidence:
  `.scratch/goal20/office-query-integration-before/data-evidence.json`,
  `office-query-final-objects-refresh/{18,19}.json`.

- A completely superseded multi-body source needs evidence for every body,
  owner and reference before deletion. The importer's intentional single-body
  restriction does not authorize deleting helpers or storage. This explicit
  query-unit edit separately checks both old bodies and all five target claims
  against native bytes, retains backups, and leaves the automatic guard intact.
  The missing automation is upstream `7ff37e19`. Evidence:
  `.scratch/goal20/office-query-duplicate-retirement/receipt.json`.

- The first statistic formatter's invalid-class fallback is exactly 240 bytes
  past the guarded 10-by-24 class-name view in both clients. The neighbor is
  TL's Begin statistic delimiter and Gold's first-formatter format string.
  Equal code does not make the neighboring strings equal. Keep the
  table-relative address. The complete backing extent and original source
  expression are unproven. A common inline fallback literal, or a new
  allocation, is not established. All 5 indexed name-pointer tables sit in
  each client's zero-filled virtual tail; their extents and owners were
  unresolved. Evidence:
  `.scratch/goal20/stat-identity-provider-evidence.json`,
  `stat-identity-fallback-view.json`.

- The checkpoint uses one shared `srv_FormatStatIdentity` at TL `0x4e73f0` /
  Gold `0x4e58e0`. Both 159-byte bodies, every operand, and the 37-byte format
  match, including wrong-address controls. The fallback keeps the
  class-table `+240` view. Gold's year operand is `0x770ae0`, not `0x770b60`.
  A declaration-only four-byte `g_current_year` view binds it. Seven Gold
  target/flag groups have no current-year operand in their bound bodies.
  The broader legacy `g_7f4c00` users and catalog were left unchanged. No
  backing owner, full table extent, new storage, or linked data verdict is
  inferred. All 85 surrounding bodies and typed operands, and 21 affected
  client checks, passed. Evidence:
  `.scratch/goal20/stat-identity-shared-probe/receipt.json`,
  `stat-identity-final-objects/`, `stat-identity-binding-before/receipt.json`.

- Pool helpers TL `0x41e440` / `0x41e490` / `0x41e4d0` are 69/61/93 bytes
  followed by 11/3/3 NOPs, with no calls or relocations. After removal of
  three unsupported entry logs, the shared `m_alloc.c` definitions match
  every native byte. Clear returns the sum of occupied slots and resets each
  block's used count and every slot's leading occupied word. It does not
  erase slot payloads. Info reports only the first block. Stats sums
  blocks, used, and capacity, and averages stride per block, not per slot.
  All 33 surrounding bodies and typed operands stayed unchanged across the
  server, TL, and Gold compiler contexts. No header, caller, or allocation
  changed. Evidence: `.scratch/goal20/pool-clear-info-stats-objects/`,
  `pool-clear-info-stats-recovery/receipt.json`.

- The bounded pool iterator is 131 bytes plus 13 NOPs in both clients
  (TL `0x41e350` / Gold `0x422ba0`). First is 39+9 (TL `0x41e3e0` / Gold
  `0x422c30`). Free-all is 43+5 (TL `0x41e410` / Gold `0x422c60`). First and
  free-all each have one native call, to the iterator and the tracked-free
  body. The no-log shared first and free-all bodies reproduce every native
  byte and operand in both clients. The receipt does not record a later
  production consolidation. Gold's stored first span is 48 bytes, including
  9 NOPs. The no-log iterator compiles to 136 bytes, with loop-rotation and
  register differences, and is not matched. Nine C spellings, four
  optimization controls, two state-type controls, two CPU controls, and three
  induction controls are rejected evidence, not native-body or original-type
  claims. No asm or guessed storage binding was added. Evidence:
  `.scratch/goal20/pool-shared-frontier-probe/`,
  `pool-next-{c-shapes,flag-controls,state-controls,induction-controls}/`.
