/* rdata_fold.c - fold two all-zero LIBCMT .rdata literals out of the link.
 *
 * scripts/split_blob.py places every member .rdata section the link keeps at
 * its reference offset inside rdata_restore.c's range.  It cannot place the
 * all-zero literals: a_map.obj's "\0" and L"\0" (and the same pair in two
 * other members) match every zero run in the blob, and the reference already
 * holds their bytes.  Left alone they would land after the blob and push the
 * import directory late (docs/msvc6-link-layout.md section 3).
 *
 * The linker folds COMDAT sections by symbol name, and msvc6 derives a string
 * literal's `??_C@...` name from its contents, so referencing the same two
 * literals here defines the same COMDATs; this object is linked before the
 * members, so theirs are the copies discarded.
 */
// SUPPORT: SERVER folds the library's all-zero .rdata literals

/* ".data$zz" sorts after every plain .data contribution, so these bytes
 * (which the reference has in .rdata) do not displace the library .data. */
#pragma data_seg(".data$zz")
const char* g_rdata_fold_refs[] = {
	"\0",
	L"\0"
};

/* Measured negative (round 122): output.obj's ___lookuptable and
 * timeset.obj's ___dnames / ___mnames cannot be folded.  They are plain
 * (non-COMDAT) .rdata in LIBCMT, so a definition of ours does not discard
 * theirs - /FORCE:MULTIPLE keeps both sections and the surplus grows by the
 * definition.  split_blob.py places them instead. */
