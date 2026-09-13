/* rdata_fold.c - keep the library's duplicate `.rdata` COMDATs out of the link.
 *
 * The reference's `.rdata` is the zlib tables followed by `rdata_restore.c`'s
 * blob, which reproduces the reference bytes for `.rdata[0x1a0:0x2608)` and
 * ends exactly where the import descriptors start.  Six LIBCMT objects the
 * link pulls *for their code* then emit their own `.rdata` COMDATs a second
 * time after the blob - 0x1c8 bytes, which push the import directory that far
 * late and take `.rdata`'s raw size from the reference's 0x3000 to 0x4000 (see
 * docs/msvc6-link-layout.md section 3):
 *
 *   0x2608 testfdiv.obj reals + "IsProcessorFeaturePresent" / "KERNEL32"
 *   0x2690 x10fout.obj  "1#QNAN" "1#INF" "1#IND" "1#SNAN"
 *   0x26b0 output.obj   __lookuptable, "(null)", wide "(null)"
 *   0x2740 timeset.obj  __dnames, __mnames
 *   0x2780 tzset.obj    "TZ"
 *   0x2784 a_map.obj    two empty strings
 *
 * The linker folds COMDAT sections *by symbol name*, and msvc6 derives a
 * string literal's `??_C@...` name from its contents.  Referencing the same
 * literals here therefore defines the same COMDATs, and because this object is
 * linked first the library's copies are the ones discarded.  Measured:
 * `.rdata` VirtualSize 0x3041 -> 0x2ff1 and raw size 0x4000 -> 0x3000, i.e.
 * the reference's, with eight of the library's string COMDATs gone from the
 * map (`build/server_lf.map`).
 *
 * The bytes themselves land in `.data` (msvc6 puts referenced literals there,
 * not in `.rdata` - docs/msvc6-link-layout.md, "Why .data is where the
 * literals are"), which is harmless: `rebrew postlink` overwrites `.data`
 * wholesale from the layout package.  The pointer array below exists only to
 * reference the literals without adding a `.text` function; `data_restore.c`'s
 * blob is sized around whatever it adds.
 *
 * Still to fold, to bring the import directory back to the reference's
 * 0x2608 (see the round-121 table in docs/TODO.md): the three `__real@8@`
 * constants testfdiv.obj keeps, `___lookuptable` / `___dnames` / `___mnames`,
 * a_map.obj's two unnamed tables and the two strings its `??_C@` entries hold.
 */
// SUPPORT: SERVER folds the six LIBCMT objects' duplicate .rdata COMDATs

const char* g_rdata_fold_refs[] = {
	"IsProcessorFeaturePresent",
	"KERNEL32",
	"1#QNAN",
	"1#INF",
	"1#IND",
	"1#SNAN",
	"TZ",
	"(null)",
	""
};
