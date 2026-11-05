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
An initialized zero is not automatically BSS. Source-adjacent constants need not
share a logical owner.

## Validate a layout change

Preserve a baseline, rebuild affected targets and compare complete files plus
sections, imports, exports, relocations, resources, headers and layout. Use
`rebrew source organize review/check` for source organization changes and the
placement commands listed in [tooling](tooling-upstream.md).

Do not insert bytes or duplicate storage to improve same-offset agreement.
Alignment requires evidence at the exact site; a gap or short C body is insufficient.


## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

The [November 5 archive](archive/2026-11-05-documentation.tar.xz) preserves the full
`docs/msvc6-link-layout.md` notebook, including corrections and receipt paths. Entries below locate
historical claims, not current instructions or verdicts. Hex values include
code/data addresses and constants.

```sh
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/msvc6-link-layout.md | less
```

| Historical section | Referenced hex values |
| --- | --- |
| <a id="msvc-60-link-and-pe-layout"></a>MSVC 6.0 LINK and PE layout | - |
| <a id="index"></a>Index | - |
| <a id="1-section-geometry-three-rules-and-the-arithmetic-that-follows"></a>1. Section geometry: three rules, and the arithmetic that follows | `0x001000`, `0x002e81`, `0x010374`, `0x022846`, `0x024000`, `0x027000`, `0x035000`, `0x174059c`, `0x1768000` |
| <a id="2-data-the-gap-blob-and-the-one-number-that-matters"></a>2. `.data`: the gap blob, and the one number that matters | - |
| <a id="the-split-links-tail-blob-and-what-the-raw-link-data-figure-measures"></a>The split link's tail blob, and what the raw-link `.data` figure measures | - |
| <a id="the-prefix-cannot-be-dodged-by-reordering-sections-merge-by-name"></a>The prefix cannot be dodged by reordering: sections merge by name | - |
| <a id="why-data-is-where-the-literals-are"></a>Why `.data` is where the literals are | - |
| <a id="3-rdata-map-section-2-the-prefix-contract"></a>3. `.rdata` (map section 2): the prefix contract | - |
| <a id="discarding-the-duplicates-instead-comdat-folding-by-symbol-name"></a>Discarding the duplicates instead: COMDAT folding by symbol name | - |
| <a id="4-the-import-layer"></a>4. The import layer | - |
| <a id="5-linker-flags-measured"></a>5. Linker flags measured | - |
| <a id="6-what-postlink-is-allowed-to-overwrite-and-what-it-is-not"></a>6. What postlink is allowed to overwrite (and what it is not) | - |
| <a id="7-measuring-it-recipes"></a>7. Measuring it (recipes) | - |
| <a id="8-traps"></a>8. Traps | - |
| <a id="9-explicit-zero-initialization-and-tentative-definitions-choose-different-native-storage"></a>9. Explicit zero initialization and tentative definitions choose different native storage | - |
| <a id="10-removing-one-float-literal-can-change-owner-positions-without-shrinking-virtualsize"></a>10. Removing one float literal can change owner positions without shrinking VirtualSize | - |
| <a id="11-import-member-format-does-not-by-itself-determine-iat-slots-or-final-thunk-alignment"></a>11. Import member format does not by itself determine IAT slots or final thunk alignment | - |
| <a id="12-live-base-relocations-and-the-linkers-relocation-section-reservation-are-separate"></a>12. Live base relocations and the linker's relocation-section reservation are separate | - |
| <a id="13-selectany-readonly-scalars-change-storage-and-retention-without-folding-these-literals"></a>13. Selectany readonly scalars change storage and retention without folding these literals | `0x100252e8`, `0x100252f4`, `0x10025fc0`, `0x10025fcc`, `0x40301040`, `0x40400040` |
| <a id="14-common-retention-directives-do-not-substitute-for-native-allocation-ordering"></a>14. COMMON retention directives do not substitute for native allocation ordering | `0x10034684`, `0x10034a6c`, `0x10035408`, `0x100e7100`, `0x1166d3a0`, `0x11763334` |
| <a id="15-sp5-and-sp6-use-the-same-link-win98-optimization-changes-file-alignment"></a>15. SP5 and SP6 use the same LINK; Win98 optimization changes file alignment | `0x1002383e`, `0x10023840` |
| <a id="16-a-native-dos-stub-control-can-hide-failure-from-an-overlap-only-byte-count"></a>16. A native DOS-stub control can hide failure from an overlap-only byte count | - |
| <a id="17-release-computes-the-checksum-from-the-native-output"></a>17. `/RELEASE` computes the checksum from the native output | - |
| <a id="18-the-configured-reference-has-altered-headers-local-stock-copies-recover-rich-records"></a>18. The configured reference has altered headers; local stock copies recover Rich records | `0x3fdd84a0`, `0x699004a9` |
| <a id="19-identical-memory-copy-members-need-call-reference-evidence-to-bind-names"></a>19. Identical memory-copy members need call-reference evidence to bind names | `0x1001b200`, `0x1001eab0` |
| <a id="20-retaining-a-stock-empty-alias-member-changes-native-final-thunk-alignment"></a>20. Retaining a stock empty alias member changes native final-thunk alignment | `0x1002383e`, `0x10023840`, `0x1002384e` |
| <a id="21-other-stock-crt-builds-do-not-supply-the-missing-bss-storage"></a>21. Other stock CRT builds do not supply the missing BSS storage | - |
| <a id="22-tested-native-export-and-assembler-aliases-do-not-provide-the-required-data-binding"></a>22. Tested native export and assembler aliases do not provide the required data binding | - |
| <a id="23-removing-duplicate-named-floats-shrinks-readonly-storage-without-changing-code"></a>23. Removing duplicate named floats shrinks readonly storage without changing code | - |
| <a id="24-pure-readonly-object-order-restores-strings-order-moves-literal-comdats-to-the-front"></a>24. Pure readonly object order restores strings; `/ORDER` moves literal COMDATs to the front | `0x100241a0`, `0x100241a4`, `0x100241ac`, `0x100252e8`, `0x10025314`, `0x10025340`, `0x10025f58`, `0x10025fb0` |
| <a id="25-shared-gamecrt-double-pools-remove-the-remaining-readonly-extent-surplus"></a>25. Shared game/CRT double pools remove the remaining readonly extent surplus | `0x10025348`, `0x10025fc0` |
| <a id="26-publishing-an-empty-private-helper-changes-native-icf-despite-identical-object-bodies"></a>26. Publishing an empty private helper changes native ICF despite identical object bodies | `0x10006f30`, `0x10016660` |
| <a id="27-coff-operand-identity-detects-storage-blocks-that-cannot-be-placed-contiguously"></a>27. COFF operand identity detects storage blocks that cannot be placed contiguously | `0x1001a162`, `0x1001a186`, `0x10023842`, `0x10026008`, `0x10026010`, `0x10031aac`, `0x10034310`, `0x10034620`, `0x10034624`, `0x10034638`, `0x10034664`, `0x10034668`, `0x10034680`, `0x10034684`, `0x10035408`, `0x10035538`, `0x10035550`, `0x10035568`, `0x10035580`, `0x10035864`, `0x11764084`, `0x1176408c`, `0x11764090`, `0x11764094`, `0x117651e0`, `0x1176550c`, `0xffffffe0` |
| <a id="28-a-separate-type-table-c-object-restores-832-bytes-without-changing-function-order"></a>28. A separate type-table C object restores 832 bytes without changing function order | `0x10025340`, `0x10025598`, `0x100255a0`, `0x10025668`, `0x1002566c`, `0x10025680`, `0x100256c4`, `0x100257d8`, `0x10025fc0`, `0x40400040` |
| <a id="29-native-link-also-writes-its-timestamp-inside-the-readonly-export-directory"></a>29. Native LINK also writes its timestamp inside the readonly export directory | `0x3fdd84a0`, `0x699004a9`, `0x6abe3d64`, `0x6abe3e26` |
| <a id="30-order-every-source-readonly-comdat-to-interleave-the-real-compiler-pools"></a>30. Order every source readonly COMDAT to interleave the real compiler pools | `0x100241a0`, `0x10025680`, `0x10025698`, `0x100256c4`, `0x100257c4`, `0x100257c8`, `0x100257d8`, `0x10025fbf`, `0x10026008` |
| <a id="31-request-stock-crt-data-members-before-their-deferred-dependencies-place-them-late"></a>31. Request stock CRT data members before their deferred dependencies place them late | `0x173f8bc`, `0x173f8dc`, `0x100241a0`, `0x10026418`, `0x10026488`, `0x100264a0`, `0x100264c8`, `0x100264e0`, `0x100265f0`, `0x10026607`, `0x10026608`, `0x10033cf0`, `0x10033ee0`, `0x10033f80`, `0x10034260`, `0x40300040` |
| <a id="32-restore-real-writable-owners-before-removing-their-duplicated-literals"></a>32. Restore real writable owners before removing their duplicated literals | `0x173f81c`, `0x173f8dc`, `0x174059c`, `0x1002944c`, `0x10029ae8`, `0x10029af0`, `0x1002a0e8`, `0x1002a0f0`, `0x1002a0f4`, `0x1002a0f8`, `0x1002a1a8`, `0x1002a1cc`, `0x1002c050`, `0x1002e2d7` |
| <a id="33-keep-the-shared-zlib-version-characters-before-their-existing-pointer"></a>33. Keep the shared zlib version characters before their existing pointer | - |
| <a id="34-retention-order-can-place-existing-stock-crt-data-without-adding-code"></a>34. Retention order can place existing stock CRT data without adding code | `0x173f81c`, `0x174059c`, `0x1001e8b4`, `0x10033bb0`, `0x10033bc8`, `0x10033cd4`, `0x10033dd4`, `0x10033ee0`, `0x10034110` |
| <a id="35-early-bss-ordering-fixes-known-owners-but-shifts-the-remaining-allocation"></a>35. Early BSS ordering fixes known owners but shifts the remaining allocation | `0x173f81c`, `0x173f83c`, `0x100294dc`, `0x100294f8`, `0x10034610`, `0x10034614`, `0x10034643`, `0x10035408`, `0x1003540c`, `0x10035478`, `0x10035880` |
| <a id="36-canonical-promotion-of-the-three-stock-data-anchors"></a>36. Canonical promotion of the three stock-data anchors | `0x10033bb0` |
| <a id="37-ordinary-stock-data-cannot-be-placed-with-native-order"></a>37. Ordinary stock data cannot be placed with native ORDER | - |
| <a id="38-a-native-lib-generated-exp-keeps-its-own-export-timestamp-through-link"></a>38. A native LIB-generated EXP keeps its own export timestamp through LINK | `0x40000040`, `0x42100040`, `0x6abe6ef8`, `0x6abe6f2e` |
| <a id="39-native-clock-control-needs-both-elf-clock-abis-frozen-lib-and-link-repeat-exactly"></a>39. Native clock control needs both ELF clock ABIs; frozen LIB and LINK repeat exactly | `0x3fdd84a0`, `0x699004a9` |
| <a id="40-canonical-native-timestamp-recipe-and-base-dependency-repair"></a>40. Canonical native timestamp recipe and base-dependency repair | `0x3fdd84a0`, `0x699004a9` |
| <a id="41-five-true-late-common-owners-fit-the-existing-connectionallocator-interval"></a>41. Five true late COMMON owners fit the existing connection/allocator interval | `0x1585584`, `0x173f81c`, `0x10034670`, `0x10034674`, `0x10035000`, `0x101deb00`, `0x11762e84`, `0x11762ea0`, `0x11764084` |
| <a id="42-native-order-restores-the-stock-crt-common-tails-relative-geometry"></a>42. Native ORDER restores the stock CRT COMMON tail's relative geometry | `0x173f7fc`, `0x173f81c`, `0x100317d8`, `0x10034684`, `0x10035408`, `0x10035538`, `0x11765008`, `0x11765010`, `0x11765020`, `0x11765120`, `0x11765228`, `0x11765260`, `0x11765380`, `0x11766208`, `0x11766210`, `0x11766220`, `0x11766320`, `0x11766398`, `0x11766428`, `0x11766460`, `0x11766580`, `0x11767598`, `0x3fdd84a0`, `0x699004a9`, `0xc0400080` |
| <a id="43-one-stock-common-root-restores-the-full-1140-byte-crt-initialized-prefix"></a>43. One stock COMMON root restores the full 1140-byte CRT initialized prefix | `0x173f7fc`, `0x173f800`, `0x10033ba0`, `0x10033bb0`, `0x10033bc8`, `0x10033cd4`, `0x10033ee0`, `0x10033eec`, `0x10033ef0`, `0x10033f80`, `0x10034013`, `0x3fdd84a0`, `0x699004a9` |
| <a id="44-direct-stock-import-objects-are-not-a-substitute-for-this-archive-selection"></a>44. Direct stock import objects are not a substitute for this archive selection | `0x60101020` |
| <a id="45-map-visible-archive-members-are-a-lower-bound-on-actual-loaded-members"></a>45. MAP-visible archive members are a lower bound on actual loaded members | `0xc0300080` |
| <a id="46-bind-the-native-cmake-drivers-together-compiler-cache-changes-can-remove-objects"></a>46. Bind the native CMake drivers together; compiler-cache changes can remove objects | - |
| <a id="47-native-coff-debug-output-exposes-private-stock-crt-storage"></a>47. Native COFF debug output exposes private stock CRT storage | `0x11766770`, `0x1176677c`, `0x11766780`, `0x117667ac`, `0x117667d4`, `0x117667e8`, `0x117667f4`, `0x117667f8`, `0x117667fc` |
| <a id="48-library-attribution-must-preserve-a-sources-target-link-position"></a>48. Library attribution must preserve a source's target link position | `0x45f380` |
| <a id="49-a-shorter-common-order-lets-ordinary-crt-bss-precede-unordered-game-storage"></a>49. A shorter COMMON order lets ordinary CRT BSS precede unordered game storage | `0x173f7fc`, `0x10034610`, `0x10034670`, `0x100346b4`, `0x10034708`, `0x10034720`, `0x100347a8`, `0x10034820`, `0x100349f0`, `0x10034ad8`, `0x10035408`, `0x10035498`, `0x100354b0`, `0x10035538`, `0x100355d8`, `0x100357a8`, `0x10035864`, `0x1166d360`, `0x117632e0` |
| <a id="50-common-input-ownership-controls-allocation-without-adding-storage"></a>50. COMMON input ownership controls allocation without adding storage | `0x173f7fc` |
| <a id="51-related-binaries-confirm-the-border-adjacent-word-without-proving-its-owner"></a>51. Related binaries confirm the border-adjacent word, without proving its owner | `0x005ec140`, `0x00663388`, `0x0066b4b8`, `0x10024650`, `0x1002469c`, `0x100246a0` |
| <a id="52-dead-code-removal-changes-live-relocations-without-changing-this-reservation"></a>52. Dead-code removal changes live relocations without changing this reservation | `0x17321f0`, `0x1732634` |
| <a id="53-resolve-ordinal-names-from-stock-imports-before-changing-call-bindings"></a>53. Resolve ordinal names from stock imports before changing call bindings | `0x10024170`, `0x10024178`, `0x1002417c` |
| <a id="54-crc-ownership-now-names-the-actual-readonly-library-table"></a>54. CRC ownership now names the actual readonly library table | `0x100241a0` |
| <a id="55-empty-aligned-data-inputs-explain-the-timezone-displacement"></a>55. Empty aligned data inputs explain the timezone displacement | `0x173f800`, `0x10033f80`, `0x10034014`, `0x10034018`, `0x10034020`, `0x10034034`, `0x100340a0`, `0x10034220`, `0x10034260`, `0x100342c8`, `0x10034310`, `0x10034348`, `0x10034350` |
| <a id="56-complete-stock-data-matching-must-validate-pointer-identities"></a>56. Complete stock data matching must validate pointer identities | - |
| <a id="57-removing-an-unsupported-duplicate-root-restores-crt-data-and-all-relocation-sites"></a>57. Removing an unsupported duplicate root restores CRT data and all relocation sites | `0x173f800`, `0x10023812` |
| <a id="58-iat-placement-and-the-hintname-pool-have-separate-orders"></a>58. IAT placement and the hint/name pool have separate orders | `0x10001130`, `0x1001a160` |
| <a id="59-place-the-actual-callback-without-shifting-the-other-common-owners"></a>59. Place the actual callback without shifting the other COMMON owners | `0x173f800`, `0x10034610`, `0x10035408`, `0x1014c6c4`, `0x1176641c` |
| <a id="60-three-native-logging-commons-fit-when-earlier-real-counters-move"></a>60. Three native logging COMMONs fit when earlier real counters move | `0x173f7f0`, `0x10034614` |
| <a id="61-bound-omitted-stock-storage-before-adding-library-inputs"></a>61. Bound omitted stock storage before adding library inputs | `0x173f81c` |
| <a id="62-compiler-debug-records-alone-leave-the-small-reservation-control-unchanged"></a>62. Compiler debug records alone leave the small reservation control unchanged | - |
| <a id="63-a-fixup-and-page-bound-fits-the-saved-reservation-controls"></a>63. A fixup-and-page bound fits the saved reservation controls | `0x173f7f0` |
| <a id="64-a-native-page-boundary-experiment-supports-the-reservation-cap"></a>64. A native page-boundary experiment supports the reservation cap | - |
| <a id="65-promote-allocator-ownership-with-actual-fields-in-existing-alignment-intervals"></a>65. Promote allocator ownership with actual fields in existing alignment intervals | `0x173f7d0` |
| <a id="66-a-measured-server-flag-fits-beside-the-clock-run-without-moving-other-commons"></a>66. A measured server flag fits beside the clock run without moving other COMMONs | `0x173f7c8` |
| <a id="67-bss-section-suffixes-do-not-solve-the-early-crt-and-late-common-boundary"></a>67. BSS section suffixes do not solve the early-CRT and late-COMMON boundary | - |
| <a id="68-sole-game-providers-in-native-archives-expose-two-separate-ordering-constraints"></a>68. Sole game providers in native archives expose two separate ordering constraints | `0x173f71c`, `0x173f7e8`, `0x173f7f0`, `0x173f7fc`, `0x173f808` |
| <a id="69-native-header-controls-retain-rich-data-brepro-changes-the-timestamp"></a>69. Native header controls retain Rich data; BREPRO changes the timestamp | `0xffffffff` |
| <a id="70-layout-freshness-must-hash-the-actual-saved-pe-headers"></a>70. Layout freshness must hash the actual saved PE headers | - |
| <a id="71-sp5s-normal-pe-path-always-builds-rich-rom-bypass-changes-the-format"></a>71. SP5's normal PE path always builds Rich; ROM bypass changes the format | `0x406eec`, `0x406f6c`, `0x43fdd0`, `0x445806`, `0x445810`, `0x445822`, `0x445834`, `0x445c6a`, `0x445c9a`, `0x4471a4`, `0x4493ce`, `0x45c180`, `0x4693b0`, `0x4693b4`, `0x480f6c`, `0x2e6cd894`, `0x536e6144`, `0x68636952`, `0x884f3421`, `0x8877c039`, `0xaa559966`, `0xc236f034`, `0xc3b8ddfa`, `0xf93bf822`, `0xffffffff` |
| <a id="72-natural-import-selection-improves-the-complete-file-despite-more-iat-displacement"></a>72. Natural import selection improves the complete file despite more IAT displacement | `0x173f7c8` |
| <a id="73-import-contributions-are-sorted-through-the-tool-runtimes-qsort"></a>73. Import contributions are sorted through the tool runtime's qsort | `0x40f580`, `0x40f5d6`, `0x40f630`, `0x40f680`, `0x442020`, `0x4422a9`, `0x173f7c8` |
| <a id="74-smoke-bootstrap-needs-a-recipe-not-an-assumed-golden"></a>74. Smoke bootstrap needs a recipe, not an assumed golden | - |
| <a id="75-native-microsoft-runtime-and-winsock-roots-are-now-production-inputs"></a>75. Native Microsoft runtime and WinSock roots are now production inputs | `0x173f7c8`, `0x1001a160`, `0x10023840` |
| <a id="76-sp5s-reservation-path-caps-fixup-space-independently-of-missing-bss"></a>76. SP5's reservation path caps fixup space independently of missing BSS | `0x4391d4`, `0x440ede`, `0x440ee9`, `0x440f1a`, `0x440f40`, `0x442f76`, `0x442f85` |
| <a id="77-untouched-gog-reference-restores-the-native-header-contract"></a>77. Untouched GOG reference restores the native header contract | `0x3fdd84a0` |
| <a id="78-a-real-source-cohort-changes-rich-counts-without-changing-runtime-bytes"></a>78. A real source cohort changes Rich counts without changing runtime bytes | `0x2e67c711`, `0xc3b8ddfa`, `0xee63f9ee` |
| <a id="79-restoring-literal-ownership-removes-the-full-cohort-layout-regression"></a>79. Restoring literal ownership removes the full-cohort layout regression | `0x4662de1a` |
| <a id="80-an-extra-native-producer-record-can-improve-header-bytes-and-regress-code"></a>80. An extra native producer record can improve header bytes and regress code | - |
| <a id="81-directory-grouping-is-not-original-tu-ownership-or-cross-target-layout-proof"></a>81. Directory grouping is not original TU ownership or cross-target layout proof | - |
| <a id="82-real-compatible-source-grouping-predicts-and-restores-the-native-pe-offset"></a>82. Real compatible source grouping predicts and restores the native PE offset | - |
| <a id="83-placement-checks-must-use-the-active-target-and-native-link-positions"></a>83. Placement checks must use the active target and native LINK positions | `0x00677918`, `0x10027046`, `0x10027078` |
| <a id="84-merging-stock-bss-into-data-materializes-an-incompatible-native-section"></a>84. Merging stock BSS into data materializes an incompatible native section | - |
| <a id="85-removing-an-array-alignment-gap-can-lose-correct-address-bindings"></a>85. Removing an array alignment gap can lose correct address bindings | - |
| <a id="86-two-real-query-pointers-fill-a-native-alignment-interval-without-moving-bulk-storage"></a>86. Two real query pointers fill a native alignment interval without moving bulk storage | `0x1003464c`, `0x10034650`, `0x10034654`, `0x10034658`, `0x1003465c`, `0x10035464`, `0x1003546c`, `0x10035478`, `0x1014c6d4`, `0x1014c6d8` |
| <a id="87-genuine-early-counters-can-use-existing-alignment-without-moving-large-arrays"></a>87. Genuine early counters can use existing alignment without moving large arrays | `0x10034690`, `0x10034694`, `0x10034698`, `0x1003469c`, `0x100346a0`, `0x10138684`, `0x10138688`, `0x1013868c`, `0x10138690`, `0x10138694`, `0x10138698`, `0x1013869c` |
| <a id="5a-optref-with-game-function-anchors-2026-10-06"></a>5a. `/OPT:REF` with game-function anchors (2026-10-06) | `0x10023840` |
| <a id="5b-import-slots-rdata-and-what-is-left-2026-10-06"></a>5b. Import slots, `.rdata`, and what is left (2026-10-06) | `0x100256b4`, `0x100260b3` |
| <a id="5c-locale-data-import-thunks-and-the-bss-model-2026-10-06"></a>5c. Locale data, import thunks, and the BSS model (2026-10-06) | `0x1001a160`, `0x100270f8`, `0x10027488` |
| <a id="5d-generated-bss-data-only-tus-and-what-is-left-2026-10-06"></a>5d. Generated BSS, data-only TUs and what is left (2026-10-06) | `0x100256a0`, `0x10034620` |
| <a id="5e-the-server-was-linked-from-source-files-shared-with-the-client-2026-10-07"></a>5e. The server was linked from source files shared with the client (2026-10-07) | - |
| <a id="5f-reconstructed-client-code-in-the-shared-files-status-2026-10-08"></a>5f. Reconstructed client code in the shared files: status (2026-10-08) | `0x402220`, `0x402320`, `0x402340`, `0x402370`, `0x402604`, `0x41ca10`, `0x41d950`, `0x41daf0`, `0x41db30`, `0x41dd90`, `0x41e350`, `0x41e4d0`, `0x4208a0`, `0x421347`, `0x42dcd0`, `0x42df70`, `0x42dfb0`, `0x42e410`, `0x42e4a0`, `0x42e4c5`, `0x42e4d0`, `0x42e5a0`, `0x42f6d0`, `0x42fe60`, `0x42ff50`, `0x430870`, `0x430c50`, `0x430f70`, `0x431070`, `0x4310f0`, `0x433690`, `0x4337f0`, `0x433fd0`, `0x45d520`, `0x45d5d0`, `0x4627e0`, `0x464500`, `0x4645a0`, `0x465750`, `0x465790`, `0x4657d0`, `0x4bcc20`, `0x4bcc50`, `0x4bd1e0`, `0x4bdf40`, `0x4c4dc0`, `0x4c76c0`, `0x4c7870`, `0x4cb6f0`, `0x4cc2b0`, `0x4cc590`, `0x4cd750`, `0x4cd7a0`, `0x4ce590`, `0x4e73c0`, `0x4e7c70`, `0x4e8a80`, `0x4e98d0`, `0x4ec410`, `0x4ec520`, `0x4ec810`, `0x4ec8a0`, `0x4ec9e0`, `0x4ecaa0`, `0x4ecc20`, `0x4ece30`, `0x4eceb0`, `0x4ed240`, `0x4ed800`, `0x4edce0`, `0x4edd30`, `0x4ee080`, `0x4ee290`, `0x4eed10`, `0x4eefe0`, `0x4ef0d0`, `0x4ef2e0`, `0x4ef770`, `0x4efc50`, `0x4efd30`, `0x4efd70`, `0x4f0960`, `0x4f09c0`, `0x4f0c90`, `0x4f0da0`, `0x4f0e40`, `0x4f0eb0`, `0x4f0f60`, `0x4f0ff0`, `0x4f1290`, `0x4f13a0`, `0x4f1450`, `0x4f14c0`, `0x4f1790`, `0x4f1890`, `0x4f1a10`, `0x4f1a40`, `0x4f3800`, `0x4f3900`, `0x4f3e60`, `0x4ff860`, `0x4fffb0`, `0x500240`, `0x500480`, `0x500660`, `0x5007f0`, `0x500a20`, `0x500c80`, `0x501490`, `0x502780`, `0x503a70`, `0x504eb0`, `0x506ee0`, `0x508220`, `0x50b710`, `0x50b750`, `0x50b780`, `0x50b7a0`, `0x50bb50`, `0x50bc10`, `0x51e080`, `0x51e490`, `0x51e9d0`, `0x51ea70`, `0x51eb20`, `0x51ebc0`, `0x51ecf0`, `0x51f170`, `0x51f480`, `0x51ffc0`, `0x520310`, `0x520860`, `0x5208e0`, `0x520d90`, `0x5212c0`, `0x521420`, `0x521530`, `0x521840`, `0x521920`, `0x5222a0`, `0x5224b0`, `0x5224f0`, `0x522510`, `0x522e30`, `0x524040`, `0x524610`, `0x60f190`, `0x675170`, `0x679e60`, `0x67a0d4`, `0x68a9d0`, `0x68a9dc`, `0x68b400`, `0x68dec0`, `0x68e020`, `0x68fea0`, `0x696540`, `0x6995bc`, `0x6995d8`, `0x6a375c`, `0x6b7fdc`, `0x6b7fe0`, `0x6b7fe4`, `0x6b7fe8`, `0x6b7fec`, `0x6f0dc8`, `0x6f1b87`, `0x6f1b88`, `0x6f1bb8`, `0x772f78`, `0x772fe7`, `0x772fe8`, `0x773d37`, `0x773d38`, `0x773d3c`, `0x773d44`, `0x773d64`, `0x773d68`, `0x7746c4`, `0x7746cc`, `0x774970`, `0x7e2480`, `0x7ea3c0`, `0x7f3ac4`, `0x85ab80`, `0x85ab88`, `0x85ab90`, `0x868054`, `0x868058`, `0x868060`, `0x8680a8`, `0x868c40`, `0x868c78`, `0x90e094`, `0x99ec10`, `0x99ec14`, `0x10058e0`, `0x10058e4`, `0x1552000`, `0x1552010`, `0xf83f840`, `0xf840be0`, `0xf97c68c`, `0xf97d6c0`, `0xf97d6c8`, `0xf9977fc`, `0xf997808`, `0x100128f0`, `0x10017fb0`, `0x1001f855`, `0x1002706c`, `0x1002a0f0`, `0x1002a1d0`, `0x1002c050`, `0x10034610`, `0x10034668`, `0x1003466c`, `0x10034670`, `0x10034678`, `0x10034684`, `0x10034688`, `0x10035407`, `0x10035410`, `0x10035447`, `0x10035497`, `0x1009b770`, `0x11766204`, `0xffffffff` |
| <a id="5g-orphan-data-in-the-reference-what-the-server-image-records-about-its-discarded-code-2026-10-08"></a>5g. Orphan data in the reference: what the server image records about its discarded code (2026-10-08) | `0x402220`, `0x402320`, `0x402340`, `0x4a6210`, `0x4a6550`, `0x4ad8c0`, `0x4c3ff0`, `0x4c5530`, `0x4e7990`, `0x4e7c70`, `0x4ec710`, `0x4f2810`, `0x4f3ef0`, `0x4f4440`, `0x4f4830`, `0x4f6d60`, `0x4fcda0`, `0x500c80`, `0x508220`, `0x50b710`, `0x50b7a0`, `0x50c830`, `0x588aa0`, `0x5b2c60`, `0x664f38`, `0x665264`, `0x665288`, `0x6652e8`, `0x675170`, `0x68d9a0`, `0x68dec0`, `0x68ff68`, `0x696438`, `0x696540`, `0x696560`, `0x699361`, `0x699362`, `0x773da8`, `0x7747b0`, `0x1552000`, `0xf840c80`, `0xf8c16c4`, `0xf997808`, `0x100245a0`, `0x1002469c`, `0x100246a0`, `0x100252e8`, `0x10025314`, `0x10025340`, `0x1002566c`, `0x100256d8`, `0x1002573c`, `0x100257e0`, `0x10027030`, `0x1002956c`, `0x10029698`, `0x1002979c`, `0x10029af0`, `0x1002a0f0`, `0x1002dcf0`, `0x1002dd48`, `0x1002dd68`, `0x10030b6a`, `0x10030b74`, `0x10030eac` |
| <a id="88-faithful-office-query-guards-remove-discarded-relocation-reservations"></a>88. Faithful office-query guards remove discarded relocation reservations | - |
| <a id="89-allocator-source-correction-restores-stock-crt-selection-and-server-data"></a>89. Allocator source correction restores stock CRT selection and server data | `0x1002350a` |
| <a id="current-input-and-additional-build-audit-2026-10-11"></a>Current-input and additional-build audit (2026-10-11) | - |
| <a id="previous-100-build-reproduced-2026-10-11"></a>Previous 100% build reproduced (2026-10-11) | - |
| <a id="gold-formatter-archive-evidence-2026-10-12"></a>Gold formatter archive evidence (2026-10-12) | `0x005de7a2`, `0x005e1210`, `0x005e1c1d` |
| <a id="temporary-server-layout-configuration-2026-10-11"></a>Temporary server layout configuration (2026-10-11) | - |
| <a id="shared-tracking-and-pool-cleanup-helpers-2026-10-11"></a>Shared tracking and pool cleanup helpers (2026-10-11) | - |
| <a id="shared-command-chain-placement-2026-10-15"></a>Shared command-chain placement (2026-10-15) | - |
| <a id="90-text-lead-pads-realign-objects-whose-predecessors-compiled-short"></a>90. `.text` lead pads realign objects whose predecessors compiled short | `0x26d000`, `0x275000`, `0x279000`, `0x401d10` |
| <a id="91-the-client-calendar-is-one-14-byte-storage-at-0x7f4c00"></a>91. The client calendar is one 14-byte storage at 0x7f4c00 | `0x72c59c`, `0x7f4c00`, `0x7f4c04` |
| <a id="92-forced-archive-members-need-a-reference-presence-test"></a>92. Forced archive members need a reference-presence test | `0x462500`, `0x462930`, `0x464900`, `0x61cc98`, `0x62c591` |
| <a id="93-the-data-prefix-pad"></a>93. The data-prefix pad | - |
| <a id="94-the-rdata-prefix-pad"></a>94. The .rdata prefix pad | `0x23F000`, `0x262000` |

</details>
