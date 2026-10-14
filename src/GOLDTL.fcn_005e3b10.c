

int __cdecl fcn_00468df0(int, int, int, int, int);
void __cdecl fcn_00469110(int, int);

int __cdecl fcn_005e3b10(int a, int b, int c)
{
	int idx;

	idx = fcn_00468df0(0x20, a * 46 + 10, 0xbf, b, c);
	*(int*) (*(char**) 0x1015ea0 + idx * 0x2f4 + 0x6c) = 1;
	fcn_00469110(idx, 300);
	return idx;
}
