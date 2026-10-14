/* ADDRESS: GOLDTL 0x004fbd20 */

// fcn_004f97a0 — a < 5 ? [0x99f580 + a] : 0x7e (both byte returns).

unsigned char __cdecl fcn_004f97a0(int a)
{
	if (a >= 5) {
		return 0x7e;
	}
	return *(unsigned char*) (0x99f580 + a);
}
