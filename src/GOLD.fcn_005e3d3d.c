// FUNCTION: GOLD 0x005e3d3d
// fcn_005e3d3d — scan table from [0x14ead3c], return node with [n+0xc] close to a.

int __cdecl fcn_005e3d3d(int a)
{
	char* p;
	char* end;
	p = *(char**) 0x14ead3c;
	end = (char*) (*(int*) 0x14ead38 * 5 + p * 4);
	while (p != 0) {
		if ((a - *(int*) (p + 0xc)) < 0x100000) {
			return (int) p;
		}
		p += 0x14;
	}
	return 0;
}
