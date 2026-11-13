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

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
