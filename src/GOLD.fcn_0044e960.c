int __cdecl fcn_005dfb95(int, int);
int __cdecl atoi(int);

/* ADDRESS: GOLD 0x0044e960 */
void __cdecl fcn_0044e960(int unused, int obj)
{
	char v;
	int idx;
	int base;

	(void) unused;
	v = (char) atoi(fcn_005dfb95(0, 0x5ebb58));
	idx = *(int*) (obj + 8);
	base = *(int*) (obj + 0x10);
	*(unsigned char*) (base + idx * 224 + 0xc4) = (unsigned char) v;
}
