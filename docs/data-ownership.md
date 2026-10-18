# Data ownership

One source definition or selected library member owns storage. Headers declare
it; users reference it. An address, `extern`, inventory row or byte match alone
does not establish ownership. [AGENTS.md](../AGENTS.md) owns the full rules.

| Storage kind | Meaning |
| --- | --- |
| Object | One C definition or selected archive member supplies bytes. |
| Import | Linker-owned function-pointer slot; terminators are spans. |
| Compiler literal | A source/library object emits the complete literal. |
| Alias/view | Existing allocation plus evidenced offset/extent; record `backing`. |
| Span | Layout interval without a standalone source owner. |

Game declarations belong in the owning subsystem header or
`src/Develop/rebrew_globals.h`; CRT declarations belong in
`src/Develop/crt_globals.h`. Stock libraries retain their storage. `link_symbol`
records an evidenced native spelling; interior addresses remain views.

## Extents and layout

Include terminators, every array element and the complete evidenced allocation.
A `g_before_<next>` / `g_text_before_<text>` span covers only otherwise unnamed
bytes. Shrink, split or retire it when a named extent grows. Lint W038 reports
unbacked overlaps; W037 checks definition extents.

`scripts/gen_bss_layout.py` tiles allocations addressed through separate native
symbols (`g_slot_table`, `g_entity_base`, town/city records, save info, connections
and allocator root). Interior symbols preserve compiler alias behavior; managed
rows describe their backing allocation. Pads outside allocations are spans.
This measured recipe does not establish original source ownership or justify
inventing storage from gaps.

Obsolete `g_data_restore_gap`, misplaced `__sbh_threshold` and invented
`__sbh_initialized` records were removed because they overlapped real storage.
The [ownership audit](data-ownership-evidence.json) preserves inputs, counts and
stock CRT relocation evidence. Assignment of an owner never promotes a verdict.
An unsized identity-only GLOBAL row can record an address without asserting an object, interior alias or
allocation owner; leave unsupported storage fields unset.

## Historical storage investigation — October 4

The then-current native DLL had 54 differing CRT pointer bytes and a 3,604-byte
virtual data shortfall. The 15 COFF fields belonged to stdio, lock and locale
initializers; reference backing required 4,096/96/one bytes respectively.
Required CRT locations overlapped the 414,720-byte game slot allocation or ran
past the built virtual end `0x11766788`. Absolute addresses would have borrowed
another object's storage.

The early interval `0x10034684..0x10035408` (3,460 bytes) lacked an evidenced
owner. Source-order controls preserved all 125 objects' runtime contributions,
section payloads, import slots and HIGHLOW sites. A related retail `server_TL.dll`
matched CRT/counter bodies but reversed counter/shutdown layout; its extents
could not be imported. No original producer MAP/PDB was found in the checked
artifacts; the nested German Gold installer was not exhaustively inspected.

These are historical findings, superseded as current status by later server
gates. They remain useful negative controls, not an active mismatch inventory.
Receipts: `.scratch/data-100-current/`, `.scratch/data-client-layout/` and
`.scratch/data-direct-storage/` (`required-storage-conflicts.json`, `audit.json`,
`rebuild-comparison.json`, `initializer-evidence.json`, `blocker-audit.json`,
`disc-crt-comparison.json`, `disc-shutdown-comparison.json`). Full chronology is
in the [archive](goal-history.md#full-notebooks).

## Check changes

Function rows and `[source.definitions]` / `[source.files]` live in format-3
`rebrew-functions.toml`. Data rows stay format 2 in `rebrew-data.toml`. The
separate source store is retired. Use the locked writers. The default target
is `Europa1400Gold_TL.exe`; `data bss` takes one target per invocation.

```sh
uv run rebrew data list --all-targets --json
uv run rebrew data bss --target server.dll --json
uv run rebrew lint --all-targets --json
```

Repeat `data bss` with `--target Europa1400Gold.exe` or
`--target Europa1400Gold_TL.exe` when that image is the one under review.
Then compare against the current raw image. Coverage reads canonical inputs.
Spans, declarations and accounting coverage do not establish reconstructed or
verified bytes. Current queue: [TODO.md](TODO.md).


## VFS stream and directory entry are distinct (Goal81, 2026-10-17)

The private `VFS_FILE` in `src/Develop/Units/vfs/vfs.c` is a 24-byte directory
entry: name, offset, source directory, packed flag, timestamp and archive.
`vfs_OpenStream` instead requests 320 bytes from its pool and accesses mode flags
at `+0x13c`. Keep the stream boundary opaque (`void*`) until its complete layout
is reviewed. The earlier scratch claim that this constructor returns a
`VFS_FILE*` was wrong; its correction is retained in
`.scratch/goal80-scene/stream-boundary.json` and
`.scratch/goal81-vfs/stream-extent-evidence.json`.

The repaired TL closer uses existing declarations for pool-head address
`0x6b7fe4` and counter `0x6b7fec`. Neither declaration allocates bytes or proves
its selected raw-link owner. No data row, global definition, stable type binding,
padding or stored data verdict is added. A heap stream is not a new global.
The download buffer's old integer field and the 44-byte download-state layout
span are a separate ownership/type review; do not turn that span into an
invented struct allocation to simplify the stream cutover.

## Stream contracts do not create storage owners (Goal82, 2026-10-17)

The opaque-pointer cutover changes declarations, formals and locals. It adds no
stream allocation, copied data, layout filler or replacement CRT storage. The
320-byte pooled stream is distinct from the private 24-byte directory entry.
The download-buffer field is a separate ownership/layout question; its byte-pointer view does not establish a typed storage owner.

TL building reader operands identify version data at `0x6a23ac`, auxiliary count
at `0x10058e0` and auxiliary buffer pointer at `0x10058e4`. The full native proof
checks these addresses. Five new identity rows describe those three separate
4-byte slots and the complete 13/9-byte `f3g:PlantMap` / `AHM_INFO` literals at
`0x6a23d0` / `0x699820`. All are physically in `.data`; the auxiliary slots are
in its zero-filled virtual tail. The version initializer is `0x1005a`, and all
67 native references access a dword. Server definitions at different addresses
do not own these TL slots. The 24 bytes after the pointer remain unassigned.
Literal content and native operands agree; raw linked placement and pool owners
remain unverified. No C storage or stored data verdict was added.

The Gold dialog adds 13 declaration identities, including two unsized arrays.
Its scalar slots are 4 bytes and the two IIDs are 16 bytes in `.rdata`.
`DD_DEVICE` / `DD_DRIVER` compiler layouts match native strides `0x338` / `0x214`
and the accessed field offsets; their complete array allocations and owners are
unknown. Physical `.data` tail placement is recorded without inventing a `.bss`
allocation. Private COM declarations describe accessed prefixes only; no full
interface allocation extent or SDK contract is claimed. Receipts:
`.scratch/goal82-vfs/{data-binding-preview.json,data-binding-applied.json,
dd-device-type.json,dd-driver-type.json}`.

The town loader initially introduced a byte-array declaration for `g_85ab80`
beside an existing `Row502450[]` declaration in its game user. Both now include
`client_town.h`, retaining the existing inferred record names and fields.
Three complete objects/five definitions preserve their bytes and fixups.
Compiler-checked cell/row strides are `0x80` / `0x2a90` in both clients;
native index arithmetic independently confirms them. This declaration repair
restores the prior conflict counts 0/3/1; it does not allocate the table or
establish its complete extent/owner.

Three final TL identities bind `g_85ab80`, `g_14a5320` and the complete 24-byte
`_STADTAUSWAHL_%s_INFO+0` literal at `0x6a22a8`. Both globals remain unsized:
the five-row cursor view contains the existing unsized `g_85ab90` view and ends
at `g_entity_type_table`, while the text pointer base has no proven bound.
The gap to `g_14a5770` is not an array length. The literal's next referenced
neighbor begins exactly at `0x6a22c0`. No alias, storage definition, allocation
size or owner is created. Receipts: `.scratch/goal82-vfs/town-data-preview.json`
and `town-data-applied.json`.

The stock `_realloc` candidate also remains unreviewed. Its 815-byte object
extraction crosses an inventoried native entry at `0x6500c2`; the CLI refuses
that extent repair. No library SIZE, native identity or provider was installed.
See `.scratch/goal82-vfs/realloc-extent-observation.json`.

Goal83 records Gold sentinel `g_fc2700` as an unsized identity and its list-head
pointer `g_fc28f4` as a four-byte alias backed by that identity at offset `0x1f4`.
Both addresses lie in the zero-filled `.data` tail. The existing D3 header is a
declaration home; no definition, full static extent, provider or data-verification
verdict was added. The initializer's accesses through `+0x224` and a separate
`0x228` heap allocation do not establish the sentinel's static allocation.
Receipts: `.scratch/goal83-gold-list-integration/data-{preview,applied}.json` and
`.scratch/goal83-gold-scene/helper-followup/data-followup/REPORT.md`.

At the Goal83 scene-view checkpoint, the TL declaration conflict count was
seven. The earlier Goal82 count of three describes its checkpoint; neither is
a live census.
