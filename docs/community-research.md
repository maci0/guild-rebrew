# Community research

External analysis supplies hypotheses and test cases. Confirm each against the
exact local binary before accepting a name, signature, field or counterpart.
The reviews below imported no source, types, storage or verdicts.

## Match the binary

The reviewed community project calls its German TL target GOLD and its English TL
target GOLD_EN. This project calls the English non-TL target GOLD. Use the
[reference hashes](build.md#reference-inputs), not labels or filenames.

The October 19 review is pinned to
[181935f64a2a754c468420503ef7b57bbe27f64b](https://github.com/europa1400-community/europa1400-decompilation/tree/181935f64a2a754c468420503ef7b57bbe27f64b).
Its diagnostic ledger, historical-text parsers, EVT notes, quantization work and
asset decoders are useful leads. Its reconstructed game_g_ files do not attest
original TUs, and its reported harness results were not reproduced here.

## Retained native checks

- TL 0x00402a00 pushes `ch_SetVisible(): invalid character`; the spelling is attested.
- TL 0x00403200 pushes `ch_Create:Too many characters!`; use ch_Create rather than
  the proposed ch_Create_Character name.
- TL 0x004050c0 unlinks and clears a queue record, but its original name remains
  unproved. The descriptive role is not a naming attestation.
- Preserve `gs_AddBeweis` from its original diagnostic rather than translating it
  to a community spelling.

[Naming](naming_conventions.md) owns adoption rules. Current bindings may already
incorporate a reviewed fact; a historical candidate count is not a work queue.

## Reuse research carefully

Record/replay and shadow fixtures offer designs for API results, call order,
callback mutation, random calls and x87 rounding. Their build hashes, modeled
regions and masks limit the conclusions. Deliberate wrong-output controls help
show whether a harness detects the claimed fault.

The reviewed snapshots did not establish a general license for copied
reconstruction source or harnesses. Do not treat a dependency's license as covering
the surrounding repository. The complete pinned review, scope and links remain
in the archive below; it is not a current license or repository-health audit.

## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

The [November 5 archive](archive/2026-11-05-documentation.tar.xz) preserves the full
`docs/community-research.md` notebook, including corrections and receipt paths. Entries below locate
historical claims, not current instructions or verdicts. Hex values include
code/data addresses and constants.

```sh
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/community-research.md | less
```

| Historical section | Referenced hex values |
| --- | --- |
| <a id="community-research-leads"></a>Community research leads | - |
| <a id="exe-branch-follow-up-2026-10-19"></a>EXE branch follow-up, 2026-10-19 | `0x401500`, `0x406850`, `0x40eac0`, `0x41bdc0`, `0x41bf90`, `0x41c290`, `0x41c470`, `0x427c40`, `0x42d880`, `0x42dabe`, `0x42dac0`, `0x4b20e0`, `0x4b2300`, `0x4b2670`, `0x4b2a10`, `0x4b2e20`, `0x4b3010`, `0x4f5770` |
| <a id="earlier-review-2026-10-18"></a>Earlier review, 2026-10-18 | - |
| <a id="match-the-build-first"></a>Match the build first | - |
| <a id="accepted-native-naming-evidence"></a>Accepted native naming evidence | `0x004011f0`, `0x00402a00`, `0x00402a83`, `0x00403200`, `0x0040325c`, `0x004050c0`, `0x0042ff50`, `0x00675328`, `0x0067534c`, `0x0067536c` |
| <a id="useful-native-review-checklists"></a>Useful native review checklists | `0x1000ca10`, `0x1000d930`, `0x10016f60`, `0x10018850` |
| <a id="testing-design-worth-retaining"></a>Testing design worth retaining | - |
| <a id="import-limits-and-replay"></a>Import limits and replay | `0x00402a00`, `0x00403200`, `0x004050c0` |

</details>
