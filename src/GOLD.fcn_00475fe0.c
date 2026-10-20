/* ADDRESS: GOLD 0x00475fe0 */
int __cdecl fcn_00475fe0(int a, int b)
{
	if (b > *(int*) (0xfb11a4 + a * 171 * 4) || b < 0)
		return -1;
	return *(int*) (0xfb1024 + (b + a * 171) * 4);
}
