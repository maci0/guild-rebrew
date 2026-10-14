
// fcn_004d2650 — if(!fcn_005dfc90(a,0x60cba8,0xa)) add a to list; return 1.

int __cdecl fcn_005dfc90(void*, int, int);

int __cdecl fcn_004d2650(int a)
{
	if (fcn_005dfc90((void*) a, 0x60cba8, 0xa) == 0) {
		int i;
		i = *(int*) 0x6f0d60;
		*(int*) (0x930380 + i * 4) = a;
		*(int*) 0x6f0d60 = i + 1;
	}
	return 1;
}
