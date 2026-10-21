/* Interior entry: 0x0045a7f9 is a fall-through continuation of the body that
 * starts at 0x0045a3a0, not a function. 0x0045a3a0's last instruction
 * (`mov eax, 0xcccccccd` at 0x0045a7f4) ends exactly at 0x0045a7f9 and the
 * next byte is `mul edx`, the second half of a divide-by-10. The 275-byte
 * extent ends on the enclosing epilogue (`pop edi; pop esi; pop ebx;
 * mov esp,ebp; pop ebp; ret`) at 0x0045a905. The stored split is a
 * merge/split artifact: extent spec is 0x0045a3a0=1388 with the 0x0045a7f9
 * entry dropped. Non-C class (interior continuation, shared frame and
 * registers). */
/* ADDRESS: GOLDTL 0x0045a7f9 */
int __cdecl fcn_0045a7f9(void)
{
    /* Interior continuation of 0x0045a3a0, not a function. */
    return 0;
}
