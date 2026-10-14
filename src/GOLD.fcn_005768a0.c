/* ADDRESS: GOLDTL 0x0057ee40 */
/* ADDRESS: GOLD 0x005768a0 */
// fcn_005768a0 — *a==0x1a && *(a+4) ? 1 : 0.

int __cdecl fcn_005768a0(int* a)
{
	if (*a == 0x1a && *(a + 1) != 0) {
		return 1;
	}
	return 0;
}
