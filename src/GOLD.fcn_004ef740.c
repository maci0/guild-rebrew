/* ADDRESS: GOLD 0x004ef740 */
/* ADDRESS: GOLDTL 0x004f1820 */

// fcn_004ef740 — a->[1] == b->[1] (b at [esp+4]).

int __cdecl fcn_004ef740(int* b, int* a)
{
	return a[1] == b[1];
}

