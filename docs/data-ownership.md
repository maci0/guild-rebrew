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

```sh
uv run --frozen rebrew data list --json
uv run --frozen rebrew data bss --json
uv run --frozen rebrew lint --json
```

Use CLI/locked metadata writers, then verify against the current raw image.
Coverage reads canonical inputs; spans, declarations and accounting coverage do
not establish reconstructed or verified bytes. Current queue: [TODO.md](TODO.md).
