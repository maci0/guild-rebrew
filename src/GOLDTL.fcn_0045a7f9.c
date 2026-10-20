/* Interior entry: 0x0045a7f9 is inside the body of the function that starts
 * at 0x0045a3a0 (`push ebp; mov ebp,esp; sub esp,0xa4`). The fragment reads
 * the enclosing frame ([ebp-0x58], [ebp-0x18], [ebp-0x1c], [ebp-0x24],
 * [ebp-0x2c8]) and reuses the caller's live esi/edi/ecx, so it is not a
 * standalone function and no C body can reproduce it. Non-C class (interior
 * entry inside 0x0045a3a0). */
/* ADDRESS: GOLDTL 0x0045a7f9 */
int __fastcall fcn_0045a7f9(void *self)
{
    /* Interior fragment of 0x0045a3a0, not a function. */
    return 0;
}
