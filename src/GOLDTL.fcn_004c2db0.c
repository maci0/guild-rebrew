/* ADDRESS: GOLD 0x004c24e0 */
/* ADDRESS: GOLDTL 0x004c2db0 */

int __cdecl fcn_004c2db0(unsigned a1, int a2)
{
	if (a2 == 1) {
		return (a1 & 1) - 2;
	}
	return (int) (a1 % 3) - 5;
}
