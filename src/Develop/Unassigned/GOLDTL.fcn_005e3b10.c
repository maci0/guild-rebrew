

int __cdecl d2_AddWindowTextButton(int, int, int, int, int);
void __cdecl d2_SetElementWidth(int, int);

int __cdecl fcn_005e3b10(int a, int b, int c)
{
	int idx;

	idx = d2_AddWindowTextButton(0x20, a * 46 + 10, 0xbf, b, c);
	*(int*) (*(char**) 0x1015ea0 + idx * 0x2f4 + 0x6c) = 1;
	d2_SetElementWidth(idx, 300);
	return idx;
}
