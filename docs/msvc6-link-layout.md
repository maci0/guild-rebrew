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

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.
