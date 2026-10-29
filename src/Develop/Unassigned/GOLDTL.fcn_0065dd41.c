/* CRT band. Not one function: the stored 151-byte extent holds a 3-byte leaf
 * (`xor eax,eax; ret`) at 0x0065dd41 and eight forwarding wrappers starting at
 * 0x0065dd44, 0x0065dd55, 0x0065dd66, 0x0065dd77, 0x0065dd8b, 0x0065dd9f,
 * 0x0065ddb3 and 0x0065ddc7. Each wrapper pushes two constants, re-pushes its
 * own incoming argument slot from [esp+0xc], calls 0x0065de21 and returns; the
 * next row 0x0065ddd8 repeats the same merge. Non-C class for one body
 * (thunk sequence, merged extent). */
/* ADDRESS: GOLDTL 0x0065dd41 */
int __cdecl fcn_0065dd41(void)
{
	return 0;
}
