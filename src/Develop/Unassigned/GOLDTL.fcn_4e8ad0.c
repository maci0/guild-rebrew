
// fcn_004e6f10 — a < 0x28 ? [0x68da6c + a*0x18] : 0.

/* ADDRESS: GOLDTL 0x004e8ad0 */
int __cdecl fcn_004e6f10(int a)
{
	if (a >= 0x28) {
		return 0;
	}
	return *(int*) (0x68da6c + a * 0x18);
}
