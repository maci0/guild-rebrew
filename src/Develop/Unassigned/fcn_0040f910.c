int __cdecl fcn_00445600(int, int, int, int);
void __cdecl fcn_00412e50(int, int);

/* ADDRESS: GOLDTL 0x0040f910 */
int __cdecl fcn_0040f910(int* a0, int* a1)
{
	int p;

	if (*(int*) 0x6b7ebc != 0 && *(int*) (*(int*) 0x6b7ebc + 0x44) == (int) fcn_0040f910) {
		if (*(int*) 0x6b5cbc != 0 || *(int*) 0x6b5cc0 != 0) {
			*(int*) (*(int*) 0x6b7e98 + 0xc60) = (int) fcn_0040f910;
			return 0;
		}
		return 0;
	}
	if (*(int*) (*(int*) 0x6b7e98 + 0xc84) == 1) {
		*(int*) (*(int*) 0x6b7e98 + 0xc60) = (int) fcn_0040f910;
	}
	p = fcn_00445600(0, 0x160, 0, *a1);
	if (p != 0) {
		fcn_00412e50(p, *a0 / 17);
	}
	return 1;
}
