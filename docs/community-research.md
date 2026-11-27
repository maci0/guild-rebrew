# Community research

External analysis supplies hypotheses and test cases. Confirm each against the
exact local binary before accepting a name, signature, field or counterpart.
[Reference hashes](build.md#reference-inputs) identify a build. Community target
labels can differ from this project's module names.

## Retained native checks

Checked in the local Gold and GoldTL images on 2026-11-24. The server image
has none of these strings. [Naming](naming_conventions.md) owns adoption rules.

- Both client images contain `ch_SetVisible(): invalid character`. GoldTL
  `0x00402a00` is bound to `ch_SetVisible` in
  `src/Develop/DieGildeAddOn/game/GOLDTL.ch_SetVisible.c`. The Gold copy of the
  same diagnostic is in `src/Develop/Unassigned/ch_SetVisible.c`, which is
  still named `fcn_00402480`.
- Both client images contain `ch_Create:Too many characters!`. Keep that
  spelling, including the missing space, when reviewing the GoldTL `0x00403200`
  name. The current definition is `ch_Create` in
  `src/Develop/Units/m_alloc/GOLDTL.fcn_00403200.c` and reports the string
  through `g_67534c`.
- GoldTL `0x004050c0` and Gold `0x004047a0` are named `ch_RemoveQueueEntry`.
  That name describes the body. No original spelling is attested for it.
- Both client images contain
  `gs_AddBeweis(): Executed---- owner = %i, st_id = %i, slot = %i`. Keep
  `Beweis`. The shared definition is `gs_AddBeweis` in
  `src/Develop/Unassigned/GOLDTL.gs_AddBeweis.c` (GoldTL `0x004f5770`, Gold
  `0x004f3640`).

## Reuse research carefully

Record/replay and shadow fixtures offer designs for API results, call order,
callback mutation, random calls and x87 rounding. Their build hashes, modeled
regions and masks limit the conclusions. Deliberate wrong-output controls help
show whether a harness detects the claimed fault.

Check the license of the exact material before copying source or harnesses.
A dependency's license does not establish the surrounding repository's license.
The pinned research reviews remain in the archive.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
