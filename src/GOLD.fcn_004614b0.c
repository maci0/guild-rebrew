void __cdecl fcn_0045f8c0(int, int, int);

/* ADDRESS: GOLD 0x004614b0 */
int __cdecl fcn_004614b0(int a)
{
	int s;

	s = a;
	if (*(char*) 0x633450 != 0) {
		if ((*(unsigned char*) (s + 0x68) & 4) != 0)
			fcn_0045f8c0(s, 0, 0);
	}
	return s;
}
