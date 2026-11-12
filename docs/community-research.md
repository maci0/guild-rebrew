# Community research

External analysis supplies hypotheses and test cases. Confirm each against the
exact local binary before accepting a name, signature, field or counterpart.
Use the [reference hashes](build.md#reference-inputs) to identify a build.
Community target labels can differ from this project's module names.

## Retained native checks

- The TL binary contains `ch_SetVisible(): invalid character`. The current
  0x00402a00 binding is `ch_SetVisible`.
- The TL binary contains the `ch_Create` overflow diagnostic. Preserve its spelling
  when reviewing the 0x00403200 name.
- TL 0x004050c0 is currently named `ch_RemoveQueueEntry`. The descriptive name
  does not establish its original spelling.
- Preserve `gs_AddBeweis` from its original diagnostic rather than translating it
  to a community spelling.

[Naming](naming_conventions.md) owns adoption rules. Current bindings may already
incorporate a reviewed fact; a historical candidate count is not a work queue.

## Reuse research carefully

Record/replay and shadow fixtures offer designs for API results, call order,
callback mutation, random calls and x87 rounding. Their build hashes, modeled
regions and masks limit the conclusions. Deliberate wrong-output controls help
show whether a harness detects the claimed fault.

Check the license of the exact material before copying source or harnesses.
A dependency's license does not establish the surrounding repository's license.
The pinned research reviews remain in the archive.

## Archived techniques

Original notebook: `docs/community-research.md` in the [documentation archive](goal-history.md#full-notebooks).

- Community research leads
- EXE branch follow-up, 2026-10-19 (`0x00401500`, `0x00406850`, `0x0040eac0`, `0x0041bdc0`, `0x0041bf90`, `0x0041c290`, `0x0041c470`, `0x00427c40`, `0x0042d880`, `0x0042dabe`, `0x0042dac0`, `0x004b20e0`, `0x004b2300`, `0x004b2670`, `0x004b2a10`, `0x004b2e20`, `0x004b3010`, `0x004f5770`)
- Earlier review, 2026-10-18
- Match the build first
- Accepted native naming evidence (`0x004011f0`, `0x00402a00`, `0x00402a83`, `0x00403200`, `0x0040325c`, `0x004050c0`, `0x0042ff50`, `0x00675328`, `0x0067534c`, `0x0067536c`)
- Useful native review checklists (`0x1000ca10`, `0x1000d930`, `0x10016f60`, `0x10018850`)
- Testing design worth retaining
- Import limits and replay (`0x00402a00`, `0x00403200`, `0x004050c0`)
