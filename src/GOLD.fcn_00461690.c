int __cdecl fcn_004614e0(int, int, int);

/* ADDRESS: GOLD 0x00461690 */
int __cdecl fcn_00461690(int a, int b, int c)
{
	if (*(unsigned char*) (a + 0x6c) < 0xff)
		return a;
	if (*(unsigned char*) (a + 0x6e) & 1)
		return a;
	if ((unsigned char) b == 0xff)
		return a;
	return fcn_004614e0(a, b, c);
}
