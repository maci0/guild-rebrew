# Data ownership

The `server.dll` inventory has 640 annotated labels. Every label has a section;
there are no conflicting types, duplicate C definitions, or unresolved storage
owners. Layout spans are explicitly marked and do not allocate storage. These
figures describe the inventory, not byte-perfect reconstruction of the DLL.

| Kind | Labels | Meaning |
| --- | ---: | --- |
| Object | 243 | A C definition or a selected library object owns storage. |
| Import | 100 | The PE linker creates a slot pointing to an imported function. |
| Compiler literal | 60 | A source translation unit or library object emits the literal. |
| Storage view | 56 | An existing allocation owns the bytes; the label identifies a view. |
| Layout span | 181 | An interval in the reference layout, without a standalone definition. |

An owner defines or supplies storage. A user reads, writes, or takes its address.
A declaration makes its name and type available. Including a header or referring
to a variable does not make that translation unit an owner. Keep one canonical
definition and declare it `extern` in shared headers.

Game globals are declared in `src/Develop/rebrew_globals.h`; linked CRT globals
are declared in `src/Develop/crt_globals.h`. CRT declarations do not replace
stock `LIBCMT` definitions. Keep game constants with their owning game source,
even when their reference addresses fall among CRT data. Do not create a region
translation unit to copy library storage.

`__imp__*` labels are four-byte data slots containing imported function pointers.
The function itself is code. Rebrew identifies these slots from the reference
PE import table and names their owner as `linker:DLL!function`. Import terminators
are layout spans, not additional import functions.

Use managed metadata relationships for interior views (`storage_kind = "alias"`,
`backing`) and names that differ from the selected native symbol (`link_symbol`).
The CRT mappings here are supported by selected archive symbols and relocations
in byte-matched stock CRT functions. Compiler literals require complete matching
reference/native bytes. An address coincidence, a similar name, or a declaration
alone does not establish ownership.

A layout span (`storage_kind = "span"`) covers only bytes no named row covers:
the hole between two named globals, named `g_before_<next>` (`g_text_before_<text>`
before a string literal). A span that overlaps a named row is stale; shrink,
split or drop it when an extent grows, and keep its `extern` view in
`src/crt_region/section_spans.c` and `src/layout_spans.h` at the row's name and
size. `rebrew lint` W038 reports any overlap between named rows except alias rows
with a `backing`.

`scripts/gen_bss_layout.py` tiles each reference allocation that code also
addresses through interior names (`g_slot_table`, `g_entity_base`,
`g_town_records`, `g_city_records`, `g_save_info`, `g_connections`,
`g_alloc_root`): the allocation's own name becomes a small leading definition,
each interior name its own definition, and `g_gap_<va>` pads fill the rest.
Code needs the interior names as separate symbols (the compiler's alias
analysis and store scheduling depend on it), so C cannot define the whole
allocation at once. The rows record the reference allocation's full extent;
interior names and pads inside it are `alias` rows backed by it, and pads outside
any allocation are spans. W037 therefore reports five rows whose leading
definition is shorter than the allocation (`g_slot_table`, `g_entity_base`,
`g_city_records`, `g_save_info`, `g_connections`); `g_town_records` and
`g_alloc_root` are emitted under the names the code uses (`g_entity_end`,
`g_alloc_root_name`), so W037 finds no definition to compare. These warnings stay
until Rebrew can record a tiled allocation.

Complete extents include string terminators and all array elements. The audit
corrected 64 one-byte string records against full source initializers or native
compiler literals and recorded 48 previously unstored fixed extents. Five struct and function-pointer
tables now cover every declared element. Labels at the first byte of an allocation
remain views without changing the actual definition into an alias. BSS coverage
uses those extents and the union of overlapping backing allocations. Its complete
documented coverage includes explicit zero-fill alignment and unknown layout
spans; it does not establish that all those bytes have been reconstructed.

Three obsolete restore records were removed: `g_data_restore_gap`, the incorrectly
located `__sbh_threshold`, and the invented `__sbh_initialized` heap interval.
Their ranges overlapped existing game storage and did not represent extra globals.
Real metadata-only objects and literals now have source identity annotations.

Run `rebrew data list --json`, `rebrew data bss --json`, and `rebrew lint --json`
after changes. Update globals through Rebrew CLI or its locked metadata APIs;
never edit the managed TOML by hand. Regenerate all coverage documents with
`rebrew coverage build --json` so Recoverage receives owners, users, declarations, and
storage kinds from the same inventory.

[Audit evidence](data-ownership-evidence.json) records input hashes, the inventory
summary, raw-link data-verification counts, and the stock CRT relocation proofs.
Raw-link differences and missing native symbols remain separate verification
findings; assigning an owner never promotes a data verdict.

Data coverage checkpoint (2026-10-04): seven previously untracked initialized
intervals total 515 bytes. Complete reference/native comparisons establish the
Error.c diagnostic literal pool and trace literals, their alignment intervals,
one VFS alignment byte, and four readonly alignment bytes after the dynasty
trait constant. `src/layout_spans.h` declares these as inventory views; none
allocates storage. Managed rows and fresh verification evidence were written
through the locked metadata API, and all three coverage documents regenerated.

At that checkpoint, `rebrew status` data coverage is 64,029/66,664 bytes (96.0%), with zero
untracked bytes, 526 verified rows and ten drift rows. The raw DLL and original
hashes remain unchanged. The remaining three initialized-data drift records
contain 54 differing bytes in CRT initializer pointers: two references to the
stdio buffer, four critical-section pointers, and nine locale null-string
pointers. Seven BSS records extend beyond the native virtual data section;
its size remains 3,604 bytes short. Complete data reconstruction is unfinished.
The previously investigated 3,460-byte early zero-fill interval still lacks
an established storage owner; recording a span does not supply that storage.

Evidence is in `.scratch/data-100-current/`: `gap-evidence.json` records complete
interval comparisons and binary/map hashes; `after-data.json` and
`verification-inputs.json` record fresh raw comparisons; `final-status.json`
records accounting. Lint has zero errors (84 existing warnings), and ordinary
server source verification passes all 316 compiled candidates, including 56
library checks. Those source results do not prove data placement.
`initializer-evidence.json` additionally checks the complete fixed bytes of
three stock CRT data contributions and attributes all 54 differing bytes to
their 15 actual COFF relocation fields. Their backing extents are 4,096 bytes
of stdio COMMON storage, 96 bytes of ordinary lock BSS, and one byte of locale
BSS. No archive, object, initializer pointer, or binary was patched.

The follow-up backing-storage check binds the current slot-table allocation to
its complete 414,720-byte COMMON definition and native MAP address. Both required
early CRT extents (the 96-byte lock block and one-byte locale null) currently
fall inside that game allocation. The required stdio buffer also extends 3,576
bytes beyond the native data virtual end at `0x11766788`. Correct initializer
addresses therefore require moving the actual backing allocations; assigning
absolute reference addresses would give the CRT somebody else's storage.
Evidence: `.scratch/data-client-layout/required-storage-conflicts.json`.

A complete fixed-code search for the server's 26-byte sequence-counter body,
requiring all three HIGHLOW fields to resolve to the same counter, finds the
two known server bodies and no identical body in either client. This is a
negative result for that exact code shape, not proof that a semantic counterpart
is absent. No client layout or missing-storage extent was imported from it.
The searched `original`, `references`, desktop `ai-decomp`, and sibling original/
symbol/archive paths supplied no original MAP/PDB/DBG archive. An original map
or source artifact could establish the presently unknown early storage owner.
Data remains 96.0%, with all ten drift records retained at that checkpoint.

Native rebuild and allocation audit (2026-10-04): every direct object COMMON
definition and ordinary BSS contribution has a native MAP anchor within the
linked data extent. The regenerated build contains 125 C objects, 76 COMMON
definitions and two BSS contributions (one COMDAT); none is unanchored. The
export object allocates no BSS or COMMON. An obsolete CMake entry for the removed
empty `spiel3.c` and a cached retired compiler-driver command required a fresh
CMake configuration before compiling with the configured Docker toolchain.

That rebuild exposed an ordering regression in Rebrew: `file_va` parsed only
inline markers, so migrated pure C sources sorted by path. The helpers now pass
the configured metadata root to the shared annotation parser; both ordering
commands retain function VA order. Sixty focused tests pass, and ruff/mypy
checks pass. Broader parser/source/build checks pass 217 tests and fail one
untouched annotation test concerning inline GLOBALS. The isolated fix is saved
in `docs/rebrew-patches/goal-metadata-source-order.patch` and applied to the
sibling Rebrew checkout; it does not include other pending tool changes.

After relinking, all four complete section payloads, public symbol bindings,
import slots/hints and HIGHLOW sites reproduce the previous accepted native
build. All 125 objects have identical runtime contributions to their prior
objects; 4,107 guarded source/header/configuration inputs are unchanged. The
stock CRT archive is unchanged. The fresh raw DLL SHA256 is
`03859f4831e16f8a3cd6b6ed9bfce63af72e36b7bf739996677aa113b7237fbd`;
267 changed bytes relative to the previous build are confined to PE headers
(file offsets `0x3c` through `0x27f`). The data section still differs from the
reference at the same 54 CRT pointer bytes and remains 3,604 virtual bytes short.
No production artifact was copied from a scratch candidate or transformed.

Receipts are in `.scratch/data-direct-storage/`: `audit.json`,
`export-storage.json`, `rebuild-comparison.json`, `header-source-guards.json`,
the fresh configure/build logs and `build-check-after.json`. The rejected
alphabetical-order build is retained separately under `reordered-regression/`.
These controls establish reproducibility of the remaining mismatch; they do
not identify the original early BSS owner or complete data reconstruction.

Fresh ordinary CLI verification of that rebuilt raw image passes all 316
source candidates (41 EXACT, 275 RELOC, including 56 compiled library checks)
and records the data evidence through the managed writer. Its data comparison
reports 577 matched, 57 mismatched and seven missing out of 641 metadata rows;
those totals include import rows and differ from the initialized-byte progress
denominator. The command exits one for the remaining data disagreement, with
zero source failures. Stored initialized-byte accounting remains
64,029/66,664 (96.0%), 526 verified rows and ten drift rows. The verification
receipt is `.scratch/data-direct-storage/full-verification.json`.
Final status confirms `last_verify.stale=false`. Lint reports zero errors and
84 existing warnings; coverage documents for all three targets are regenerated.
`final-status.json`, `lint-final.json` and `coverage-final.json` preserve those
checks alongside the complete section comparison in `complete-section-guards.json`.

Additional artifact audit (2026-10-04): local symbol/archive candidates in
Downloads, Documents and Desktop supplied no original producer MAP/PDB. The
retail `gilde.dbg` candidate is empty; the NASM map has placeholder addresses;
`server-new.pdb` belongs to a prior reconstruction. The GOG installer and the
standard disc directory contain no original symbol or source entries. Only the
outer directory of the separate German Gold archive was inspected; its nested
installer is not claimed to lack symbols.

The standard disc supplies an older MSVC `server_TL.dll`, SHA256
`fbf4970dd32b8fa07c7bbcb5fcc76b044ddcfe9fe76817d7a1ccde48fb00fd71`.
Complete fixed CRT data payloads and their relocation shapes uniquely match
the 640-byte stdio table, 192-byte lock table and 60-byte locale contribution.
Both complete 26-byte counter bodies match with identical relocation shapes
and three references to each respective counter. The complete 68-byte exported
shutdown body also matches; its three import slots resolve to the same APIs.
This establishes the older counter and shutdown-flag identities, but the
relative layout reverses: its sequence counter is at `0x100300b0`, before the
shutdown flag at `0x10030218`; the current target's shutdown flag at `0x10034680`
precedes the counter at `0x10035408`. The older layout cannot supply the current
target's unknown early allocation, and no storage extent was imported from it.

The native/reference inputs and stored verdicts are unchanged. Data remains
96.0%; the goal is blocked on evidence identifying the original owner and full
extent of `0x10034684..0x10035408`, rather than another source-order or compiler
control. An original target MAP/PDB/source artifact, or equivalent direct
allocation evidence, is needed for a justified repair. `blocker-audit.json`,
`disc-crt-comparison.json`, `disc-shutdown-comparison.json` and the disc extraction
provenance under `.scratch/data-direct-storage/` preserve the audit. The sparse
`standard-disc-header.iso` supplies only the first 8 MiB of the disc payload for
directory inspection; the two DLLs were extracted directly from verified raw
CD sector extents, not from its absent later file payloads.
