int __cdecl fcn_005dfb95(int, int);
float __cdecl fcn_005de9be(int);

/* ADDRESS: GOLD 0x0044eae0 */
void __cdecl fcn_0044eae0(int unused, int obj)
{
	float v;
	int idx;
	int base;

	(void) unused;
	v = fcn_005de9be(fcn_005dfb95(0, 0x5ebb58));
	idx = *(int*) (obj + 8);
	base = *(int*) (obj + 0x10);
	*(float*) (base + idx * 224 + 0xdc) = v;
}
