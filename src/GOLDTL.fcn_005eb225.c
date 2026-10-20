/* ADDRESS: GOLDTL 0x005eb225 */

/* The 43-byte inventory extent is not one function. It holds five unrelated
 * bodies: a jmp [0x6ad660] import thunk (6 bytes), two 3-byte mov eax,ecx
 * getters, an argument thunk that calls 0x613478 then jumps through
 * [0x6ad650], and a 21-byte two-field setter ending in ret 8. No single C
 * function emits that span, so no body is reconstructed here. */
int __cdecl fcn_005eb225(void)
{
	return 0;
}
