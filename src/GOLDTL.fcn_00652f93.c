/* Frame-sharing helper, not a standalone function: 0x00652f93 is entered by
 * `call 0x00652f93` from 0x00652f8b in the body at 0x00652f4b, and it reads
 * and writes the caller's frame: `and byte ptr [ebp-0x2c8], 0xfe` first,
 * `fst qword ptr [ebp-0x2d0]`, `[ebp-0x90]`, `fldcw [ebp-0xa4]`. It has no
 * prologue of its own, contains a mid-body `ret` (0x00652ff6) after restoring
 * the caller's control word, and ends with `jmp 0x00652fef` back into itself
 * (loop), so the stored 312-byte extent ends with no terminator at
 * 0x006530cb. Non-C class (interior entry, shared frame). */
/* ADDRESS: GOLDTL 0x00652f93 */
int __cdecl fcn_00652f93(void)
{
    /* Frame-sharing fragment of 0x00652f4b, not a function. */
    return 0;
}
