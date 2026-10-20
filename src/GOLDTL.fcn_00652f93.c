/* Interior entry: 0x00652f93 is inside a larger x87 helper body; its first
 * instruction is `and byte ptr [ebp-0x2c8], 0xfe`, it reads the enclosing
 * frame ([ebp-0x2d0] fst, [ebp-0x90], [ebp-0xa4] control word) and ends with
 * `ret` at 0x00652ff6 after restoring `fldcw [ebp-0xa4]`. No prologue and no
 * local frame of its own, so it is not a standalone function. Non-C class
 * (interior entry, frame shared with the enclosing helper). */
/* ADDRESS: GOLDTL 0x00652f93 */
int __cdecl fcn_00652f93(void)
{
    /* Interior fragment, not a function. */
    return 0;
}
