# Link and PE layout

Compare the raw linked image, its matching map and the untouched reference.
Postlink copying and replacement-import recipes are retired. [Build instructions](build.md)
own the current procedure; [data ownership](data-ownership.md) owns allocation claims.

## Server geometry

The server reference uses section and file alignment `0x1000`, headers `0x1000`,
and a total file size of `0x46000` bytes.

| Section | RVA | VirtualSize | Raw size | File offset |
| --- | --- | --- | --- | --- |
| .text | 0x1000 | 0x22846 | 0x23000 | 0x1000 |
| .rdata | 0x24000 | 0x2e81 | 0x3000 | 0x24000 |
| .data | 0x27000 | 0x174059c | 0xe000 | 0x27000 |
| .reloc | 0x1768000 | 0x10374 | 0x11000 | 0x35000 |

Raw size rounds file-backed content to FileAlignment. The next section RVA rounds
VirtualSize to SectionAlignment. The next file offset follows the preceding raw
size. BSS contributes virtual extent without file payload.

The IAT begins .rdata; the server has no separate .idata section. A matching import
name list does not establish identical slot order, hints or physical placement.

## Find the actual contribution

Use the selected objects, archive extraction and map before explaining a gap.
`/OPT:REF` can discard compiled contributions; `/OPT:NOREF` does not select omitted
TUs or every archive member. Undefined references can still matter in discarded code.

Keep function order, literal pooling, COMMON alignment, CRT initialization and
archive selection separate. A global address match does not identify its owner.
An initialized zero is not automatically BSS. Adjacent constants need not
share an owner.

## Validate a layout change

Preserve a baseline, rebuild affected targets and compare complete files plus
sections, imports, exports, relocations, resources, headers and layout. Use
`rebrew source organize review` and `rebrew source organize check` for source organization changes and the
placement commands listed in [tooling](tooling-upstream.md).

Do not insert bytes or duplicate storage to improve same-offset agreement.
Alignment requires evidence at the exact site; a gap or short C body is insufficient.

## Archived techniques

Original notebook: `docs/msvc6-link-layout.md` in the [documentation archive](goal-history.md#full-notebooks).

- MSVC 6.0 LINK and PE layout
- Index
- 1. Section geometry: three rules, and the arithmetic that follows (`0x00001000`, `0x00002e81`, `0x00010374`, `0x00022846`, `0x00024000`, `0x00027000`, `0x00035000`, `0x0174059c`, `0x01768000`)
- 2. `.data`: the gap blob, and the one number that matters
- The split link's tail blob, and what the raw-link `.data` figure measures
- The prefix cannot be dodged by reordering: sections merge by name
- Why `.data` is where the literals are
- 3. `.rdata` (map section 2): the prefix contract
- Discarding the duplicates instead: COMDAT folding by symbol name
- 4. The import layer
- 5. Linker flags measured
- 6. What postlink is allowed to overwrite (and what it is not)
- 7. Measuring it (recipes)
- 8. Traps
- 9. Explicit zero initialization and tentative definitions choose different native storage
- 10. Removing one float literal can change owner positions without shrinking VirtualSize
- 11. Import member format does not by itself determine IAT slots or final thunk alignment
- 12. Live base relocations and the linker's relocation-section reservation are separate
- 13. Selectany readonly scalars change storage and retention without folding these literals (`0x100252e8`, `0x100252f4`, `0x10025fc0`, `0x10025fcc`, `0x40301040`, `0x40400040`)
- 14. COMMON retention directives do not substitute for native allocation ordering (`0x10034684`, `0x10034a6c`, `0x10035408`, `0x100e7100`, `0x1166d3a0`, `0x11763334`)
- 15. SP5 and SP6 use the same LINK; Win98 optimization changes file alignment (`0x1002383e`, `0x10023840`)
- 16. A native DOS-stub control can hide failure from an overlap-only byte count
- 17. `/RELEASE` computes the checksum from the native output
- 18. The configured reference has altered headers; local stock copies recover Rich records (`0x3fdd84a0`, `0x699004a9`)
- 19. Identical memory-copy members need call-reference evidence to bind names (`0x1001b200`, `0x1001eab0`)
- 20. Retaining a stock empty alias member changes native final-thunk alignment (`0x1002383e`, `0x10023840`, `0x1002384e`)
- 21. Other stock CRT builds do not supply the missing BSS storage
- 22. Tested native export and assembler aliases do not provide the required data binding
- 23. Removing duplicate named floats shrinks readonly storage without changing code
- 24. Pure readonly object order restores strings; `/ORDER` moves literal COMDATs to the front (`0x100241a0`, `0x100241a4`, `0x100241ac`, `0x100252e8`, `0x10025314`, `0x10025340`, `0x10025f58`, `0x10025fb0`)
- 25. Shared game/CRT double pools remove the remaining readonly extent surplus (`0x10025348`, `0x10025fc0`)
- 26. Publishing an empty private helper changes native ICF despite identical object bodies (`0x10006f30`, `0x10016660`)
- 27. COFF operand identity detects storage blocks that cannot be placed contiguously (`0x1001a162`, `0x1001a186`, `0x10023842`, `0x10026008`, `0x10026010`, `0x10031aac`, `0x10034310`, `0x10034620`, `0x10034624`, `0x10034638`, `0x10034664`, `0x10034668`, `0x10034680`, `0x10034684`, `0x10035408`, `0x10035538`, `0x10035550`, `0x10035568`, `0x10035580`, `0x10035864`, `0x11764084`, `0x1176408c`, `0x11764090`, `0x11764094`, `0x117651e0`, `0x1176550c`, `0xffffffe0`)
- 28. A separate type-table C object restores 832 bytes without changing function order (`0x10025340`, `0x10025598`, `0x100255a0`, `0x10025668`, `0x1002566c`, `0x10025680`, `0x100256c4`, `0x100257d8`, `0x10025fc0`, `0x40400040`)
- 29. Native LINK also writes its timestamp inside the readonly export directory (`0x3fdd84a0`, `0x699004a9`, `0x6abe3d64`, `0x6abe3e26`)
- 30. Order every source readonly COMDAT to interleave the real compiler pools (`0x100241a0`, `0x10025680`, `0x10025698`, `0x100256c4`, `0x100257c4`, `0x100257c8`, `0x100257d8`, `0x10025fbf`, `0x10026008`)
- 31. Request stock CRT data members before their deferred dependencies place them late (`0x0173f8bc`, `0x0173f8dc`, `0x100241a0`, `0x10026418`, `0x10026488`, `0x100264a0`, `0x100264c8`, `0x100264e0`, `0x100265f0`, `0x10026607`, `0x10026608`, `0x10033cf0`, `0x10033ee0`, `0x10033f80`, `0x10034260`, `0x40300040`)
- 32. Restore real writable owners before removing their duplicated literals (`0x0173f81c`, `0x0173f8dc`, `0x0174059c`, `0x1002944c`, `0x10029ae8`, `0x10029af0`, `0x1002a0e8`, `0x1002a0f0`, `0x1002a0f4`, `0x1002a0f8`, `0x1002a1a8`, `0x1002a1cc`, `0x1002c050`, `0x1002e2d7`)
- 33. Keep the shared zlib version characters before their existing pointer
- 34. Retention order can place existing stock CRT data without adding code (`0x0173f81c`, `0x0174059c`, `0x1001e8b4`, `0x10033bb0`, `0x10033bc8`, `0x10033cd4`, `0x10033dd4`, `0x10033ee0`, `0x10034110`)
- 35. Early BSS ordering fixes known owners but shifts the remaining allocation (`0x0173f81c`, `0x0173f83c`, `0x100294dc`, `0x100294f8`, `0x10034610`, `0x10034614`, `0x10034643`, `0x10035408`, `0x1003540c`, `0x10035478`, `0x10035880`)
- 36. Canonical promotion of the three stock-data anchors (`0x10033bb0`)
- 37. Ordinary stock data cannot be placed with native ORDER
- 38. A native LIB-generated EXP keeps its own export timestamp through LINK (`0x40000040`, `0x42100040`, `0x6abe6ef8`, `0x6abe6f2e`)
- 39. Native clock control needs both ELF clock ABIs; frozen LIB and LINK repeat exactly (`0x3fdd84a0`, `0x699004a9`)
- 40. Canonical native timestamp recipe and base-dependency repair (`0x3fdd84a0`, `0x699004a9`)
- 41. Five true late COMMON owners fit the existing connection/allocator interval (`0x01585584`, `0x0173f81c`, `0x10034670`, `0x10034674`, `0x10035000`, `0x101deb00`, `0x11762e84`, `0x11762ea0`, `0x11764084`)
- 42. Native ORDER restores the stock CRT COMMON tail's relative geometry (`0x0173f7fc`, `0x0173f81c`, `0x100317d8`, `0x10034684`, `0x10035408`, `0x10035538`, `0x11765008`, `0x11765010`, `0x11765020`, `0x11765120`, `0x11765228`, `0x11765260`, `0x11765380`, `0x11766208`, `0x11766210`, `0x11766220`, `0x11766320`, `0x11766398`, `0x11766428`, `0x11766460`, `0x11766580`, `0x11767598`, `0x3fdd84a0`, `0x699004a9`, `0xc0400080`)
- 43. One stock COMMON root restores the full 1140-byte CRT initialized prefix (`0x0173f7fc`, `0x0173f800`, `0x10033ba0`, `0x10033bb0`, `0x10033bc8`, `0x10033cd4`, `0x10033ee0`, `0x10033eec`, `0x10033ef0`, `0x10033f80`, `0x10034013`, `0x3fdd84a0`, `0x699004a9`)
- 44. Direct stock import objects are not a substitute for this archive selection (`0x60101020`)
- 45. MAP-visible archive members are a lower bound on actual loaded members (`0xc0300080`)
- 46. Bind the native CMake drivers together; compiler-cache changes can remove objects
- 47. Native COFF debug output exposes private stock CRT storage (`0x11766770`, `0x1176677c`, `0x11766780`, `0x117667ac`, `0x117667d4`, `0x117667e8`, `0x117667f4`, `0x117667f8`, `0x117667fc`)
- 48. Library attribution must preserve a source's target link position (`0x0045f380`)
- 49. A shorter COMMON order lets ordinary CRT BSS precede unordered game storage (`0x0173f7fc`, `0x10034610`, `0x10034670`, `0x100346b4`, `0x10034708`, `0x10034720`, `0x100347a8`, `0x10034820`, `0x100349f0`, `0x10034ad8`, `0x10035408`, `0x10035498`, `0x100354b0`, `0x10035538`, `0x100355d8`, `0x100357a8`, `0x10035864`, `0x1166d360`, `0x117632e0`)
- 50. COMMON input ownership controls allocation without adding storage (`0x0173f7fc`)
- 51. Related binaries confirm the border-adjacent word, without proving its owner (`0x005ec140`, `0x00663388`, `0x0066b4b8`, `0x10024650`, `0x1002469c`, `0x100246a0`)
- 52. Dead-code removal changes live relocations without changing this reservation (`0x017321f0`, `0x01732634`)
- 53. Resolve ordinal names from stock imports before changing call bindings (`0x10024170`, `0x10024178`, `0x1002417c`)
- 54. CRC ownership now names the actual readonly library table (`0x100241a0`)
- 55. Empty aligned data inputs explain the timezone displacement (`0x0173f800`, `0x10033f80`, `0x10034014`, `0x10034018`, `0x10034020`, `0x10034034`, `0x100340a0`, `0x10034220`, `0x10034260`, `0x100342c8`, `0x10034310`, `0x10034348`, `0x10034350`)
- 56. Complete stock data matching must validate pointer identities
- 57. Removing an unsupported duplicate root restores CRT data and all relocation sites (`0x0173f800`, `0x10023812`)
- 58. IAT placement and the hint/name pool have separate orders (`0x10001130`, `0x1001a160`)
- 59. Place the actual callback without shifting the other COMMON owners (`0x0173f800`, `0x10034610`, `0x10035408`, `0x1014c6c4`, `0x1176641c`)
- 60. Three native logging COMMONs fit when earlier real counters move (`0x0173f7f0`, `0x10034614`)
- 61. Bound omitted stock storage before adding library inputs (`0x0173f81c`)
- 62. Compiler debug records alone leave the small reservation control unchanged
- 63. A fixup-and-page bound fits the saved reservation controls (`0x0173f7f0`)
- 64. A native page-boundary experiment supports the reservation cap
- 65. Promote allocator ownership with actual fields in existing alignment intervals (`0x0173f7d0`)
- 66. A measured server flag fits beside the clock run without moving other COMMONs (`0x0173f7c8`)
- 67. BSS section suffixes do not solve the early-CRT and late-COMMON boundary
- 68. Sole game providers in native archives expose two separate ordering constraints (`0x0173f71c`, `0x0173f7e8`, `0x0173f7f0`, `0x0173f7fc`, `0x0173f808`)
- 69. Native header controls retain Rich data; BREPRO changes the timestamp (`0xffffffff`)
- 70. Layout freshness must hash the actual saved PE headers
- 71. SP5's normal PE path always builds Rich; ROM bypass changes the format (`0x00406eec`, `0x00406f6c`, `0x0043fdd0`, `0x00445806`, `0x00445810`, `0x00445822`, `0x00445834`, `0x00445c6a`, `0x00445c9a`, `0x004471a4`, `0x004493ce`, `0x0045c180`, `0x004693b0`, `0x004693b4`, `0x00480f6c`, `0x2e6cd894`, `0x536e6144`, `0x68636952`, `0x884f3421`, `0x8877c039`, `0xaa559966`, `0xc236f034`, `0xc3b8ddfa`, `0xf93bf822`, `0xffffffff`)
- 72. Natural import selection improves the complete file despite more IAT displacement (`0x0173f7c8`)
- 73. Import contributions are sorted through the tool runtime's qsort (`0x0040f580`, `0x0040f5d6`, `0x0040f630`, `0x0040f680`, `0x00442020`, `0x004422a9`, `0x0173f7c8`)
- 74. Smoke bootstrap needs a recipe, not an assumed golden
- 75. Native Microsoft runtime and WinSock roots are now production inputs (`0x0173f7c8`, `0x1001a160`, `0x10023840`)
- 76. SP5's reservation path caps fixup space independently of missing BSS (`0x004391d4`, `0x00440ede`, `0x00440ee9`, `0x00440f1a`, `0x00440f40`, `0x00442f76`, `0x00442f85`)
- 77. Untouched GOG reference restores the native header contract (`0x3fdd84a0`)
- 78. A real source cohort changes Rich counts without changing runtime bytes (`0x2e67c711`, `0xc3b8ddfa`, `0xee63f9ee`)
- 79. Restoring literal ownership removes the full-cohort layout regression (`0x4662de1a`)
- 80. An extra native producer record can improve header bytes and regress code
- 81. Directory grouping is not original TU ownership or cross-target layout proof
- 82. Real compatible source grouping predicts and restores the native PE offset
- 83. Placement checks must use the active target and native LINK positions (`0x00677918`, `0x10027046`, `0x10027078`)
- 84. Merging stock BSS into data materializes an incompatible native section
- 85. Removing an array alignment gap can lose correct address bindings
- 86. Two real query pointers fill a native alignment interval without moving bulk storage (`0x1003464c`, `0x10034650`, `0x10034654`, `0x10034658`, `0x1003465c`, `0x10035464`, `0x1003546c`, `0x10035478`, `0x1014c6d4`, `0x1014c6d8`)
- 87. Genuine early counters can use existing alignment without moving large arrays (`0x10034690`, `0x10034694`, `0x10034698`, `0x1003469c`, `0x100346a0`, `0x10138684`, `0x10138688`, `0x1013868c`, `0x10138690`, `0x10138694`, `0x10138698`, `0x1013869c`)
- 5a. `/OPT:REF` with game-function anchors (2026-10-06) (`0x10023840`)
- 5b. Import slots, `.rdata`, and what is left (2026-10-06) (`0x100256b4`, `0x100260b3`)
- 5c. Locale data, import thunks, and the BSS model (2026-10-06) (`0x1001a160`, `0x100270f8`, `0x10027488`)
- 5d. Generated BSS, data-only TUs and what is left (2026-10-06) (`0x100256a0`, `0x10034620`)
- 5e. The server was linked from source files shared with the client (2026-10-07)
- 5f. Reconstructed client code in the shared files: status (2026-10-08) (`0x00402220`, `0x00402320`, `0x00402340`, `0x00402370`, `0x00402604`, `0x0041ca10`, `0x0041d950`, `0x0041daf0`, `0x0041db30`, `0x0041dd90`, `0x0041e350`, `0x0041e4d0`, `0x004208a0`, `0x00421347`, `0x0042dcd0`, `0x0042df70`, `0x0042dfb0`, `0x0042e410`, `0x0042e4a0`, `0x0042e4c5`, `0x0042e4d0`, `0x0042e5a0`, `0x0042f6d0`, `0x0042fe60`, `0x0042ff50`, `0x00430870`, `0x00430c50`, `0x00430f70`, `0x00431070`, `0x004310f0`, `0x00433690`, `0x004337f0`, `0x00433fd0`, `0x0045d520`, `0x0045d5d0`, `0x004627e0`, `0x00464500`, `0x004645a0`, `0x00465750`, `0x00465790`, `0x004657d0`, `0x004bcc20`, `0x004bcc50`, `0x004bd1e0`, `0x004bdf40`, `0x004c4dc0`, `0x004c76c0`, `0x004c7870`, `0x004cb6f0`, `0x004cc2b0`, `0x004cc590`, `0x004cd750`, `0x004cd7a0`, `0x004ce590`, `0x004e73c0`, `0x004e7c70`, `0x004e8a80`, `0x004e98d0`, `0x004ec410`, `0x004ec520`, `0x004ec810`, `0x004ec8a0`, `0x004ec9e0`, `0x004ecaa0`, `0x004ecc20`, `0x004ece30`, `0x004eceb0`, `0x004ed240`, `0x004ed800`, `0x004edce0`, `0x004edd30`, `0x004ee080`, `0x004ee290`, `0x004eed10`, `0x004eefe0`, `0x004ef0d0`, `0x004ef2e0`, `0x004ef770`, `0x004efc50`, `0x004efd30`, `0x004efd70`, `0x004f0960`, `0x004f09c0`, `0x004f0c90`, `0x004f0da0`, `0x004f0e40`, `0x004f0eb0`, `0x004f0f60`, `0x004f0ff0`, `0x004f1290`, `0x004f13a0`, `0x004f1450`, `0x004f14c0`, `0x004f1790`, `0x004f1890`, `0x004f1a10`, `0x004f1a40`, `0x004f3800`, `0x004f3900`, `0x004f3e60`, `0x004ff860`, `0x004fffb0`, `0x00500240`, `0x00500480`, `0x00500660`, `0x005007f0`, `0x00500a20`, `0x00500c80`, `0x00501490`, `0x00502780`, `0x00503a70`, `0x00504eb0`, `0x00506ee0`, `0x00508220`, `0x0050b710`, `0x0050b750`, `0x0050b780`, `0x0050b7a0`, `0x0050bb50`, `0x0050bc10`, `0x0051e080`, `0x0051e490`, `0x0051e9d0`, `0x0051ea70`, `0x0051eb20`, `0x0051ebc0`, `0x0051ecf0`, `0x0051f170`, `0x0051f480`, `0x0051ffc0`, `0x00520310`, `0x00520860`, `0x005208e0`, `0x00520d90`, `0x005212c0`, `0x00521420`, `0x00521530`, `0x00521840`, `0x00521920`, `0x005222a0`, `0x005224b0`, `0x005224f0`, `0x00522510`, `0x00522e30`, `0x00524040`, `0x00524610`, `0x0060f190`, `0x00675170`, `0x00679e60`, `0x0067a0d4`, `0x0068a9d0`, `0x0068a9dc`, `0x0068b400`, `0x0068dec0`, `0x0068e020`, `0x0068fea0`, `0x00696540`, `0x006995bc`, `0x006995d8`, `0x006a375c`, `0x006b7fdc`, `0x006b7fe0`, `0x006b7fe4`, `0x006b7fe8`, `0x006b7fec`, `0x006f0dc8`, `0x006f1b87`, `0x006f1b88`, `0x006f1bb8`, `0x00772f78`, `0x00772fe7`, `0x00772fe8`, `0x00773d37`, `0x00773d38`, `0x00773d3c`, `0x00773d44`, `0x00773d64`, `0x00773d68`, `0x007746c4`, `0x007746cc`, `0x00774970`, `0x007e2480`, `0x007ea3c0`, `0x007f3ac4`, `0x0085ab80`, `0x0085ab88`, `0x0085ab90`, `0x00868054`, `0x00868058`, `0x00868060`, `0x008680a8`, `0x00868c40`, `0x00868c78`, `0x0090e094`, `0x0099ec10`, `0x0099ec14`, `0x010058e0`, `0x010058e4`, `0x01552000`, `0x01552010`, `0x0f83f840`, `0x0f840be0`, `0x0f97c68c`, `0x0f97d6c0`, `0x0f97d6c8`, `0x0f9977fc`, `0x0f997808`, `0x100128f0`, `0x10017fb0`, `0x1001f855`, `0x1002706c`, `0x1002a0f0`, `0x1002a1d0`, `0x1002c050`, `0x10034610`, `0x10034668`, `0x1003466c`, `0x10034670`, `0x10034678`, `0x10034684`, `0x10034688`, `0x10035407`, `0x10035410`, `0x10035447`, `0x10035497`, `0x1009b770`, `0x11766204`, `0xffffffff`)
- 5g. Orphan data in the reference: what the server image records about its discarded code (2026-10-08) (`0x00402220`, `0x00402320`, `0x00402340`, `0x004a6210`, `0x004a6550`, `0x004ad8c0`, `0x004c3ff0`, `0x004c5530`, `0x004e7990`, `0x004e7c70`, `0x004ec710`, `0x004f2810`, `0x004f3ef0`, `0x004f4440`, `0x004f4830`, `0x004f6d60`, `0x004fcda0`, `0x00500c80`, `0x00508220`, `0x0050b710`, `0x0050b7a0`, `0x0050c830`, `0x00588aa0`, `0x005b2c60`, `0x00664f38`, `0x00665264`, `0x00665288`, `0x006652e8`, `0x00675170`, `0x0068d9a0`, `0x0068dec0`, `0x0068ff68`, `0x00696438`, `0x00696540`, `0x00696560`, `0x00699361`, `0x00699362`, `0x00773da8`, `0x007747b0`, `0x01552000`, `0x0f840c80`, `0x0f8c16c4`, `0x0f997808`, `0x100245a0`, `0x1002469c`, `0x100246a0`, `0x100252e8`, `0x10025314`, `0x10025340`, `0x1002566c`, `0x100256d8`, `0x1002573c`, `0x100257e0`, `0x10027030`, `0x1002956c`, `0x10029698`, `0x1002979c`, `0x10029af0`, `0x1002a0f0`, `0x1002dcf0`, `0x1002dd48`, `0x1002dd68`, `0x10030b6a`, `0x10030b74`, `0x10030eac`)
- 88. Faithful office-query guards remove discarded relocation reservations
- 89. Allocator source correction restores stock CRT selection and server data (`0x1002350a`)
- Current-input and additional-build audit (2026-10-11)
- Previous 100% build reproduced (2026-10-11)
- Gold formatter archive evidence (2026-10-12) (`0x005de7a2`, `0x005e1210`, `0x005e1c1d`)
- Temporary server layout configuration (2026-10-11)
- Shared tracking and pool cleanup helpers (2026-10-11)
- Shared command-chain placement (2026-10-15)
- 90. `.text` lead pads realign objects whose predecessors compiled short (`0x0026d000`, `0x00275000`, `0x00279000`, `0x00401d10`)
- 91. The client calendar is one 14-byte storage at 0x7f4c00 (`0x0072c59c`, `0x007f4c00`, `0x007f4c04`)
- 92. Forced archive members need a reference-presence test (`0x00462500`, `0x00462930`, `0x00464900`, `0x0061cc98`, `0x0062c591`)
- 93. The data-prefix pad
- 94. The .rdata prefix pad (`0x0023f000`, `0x00262000`)
