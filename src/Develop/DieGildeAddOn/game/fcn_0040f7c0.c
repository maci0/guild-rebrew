int __cdecl fcn_00425bf0(void*, int, char*);
int __cdecl fcn_00445600(int, int, int, int);
void __cdecl fcn_00414fb0(int, int, int, int*);
int __cdecl fcn_0040f7c0(int*, int*, int*, int*, int*, int*, int*);

/* ADDRESS: GOLDTL 0x0040f7c0 */
int __cdecl fcn_0040f7c0(int* a1, int* a2, int* a3, int* a4, int* a5, int* a6, int* a7)
{
	int v[5];
	int i;
	int c = 0;
	int g;
	int f;
	int* o;

	g = *(int*) 0x6b7ebc;
	f = (int) fcn_0040f7c0;
	if (g != 0 && *(int*) (g + 0x44) == f) {
		if (*(int*) 0x6b5cbc == 0 && *(int*) 0x6b5cc0 == 0)
			return 0;
		*(int*) (*(int*) 0x6b7e98 + 0xc60) = f;
		return 0;
	}
	o = *(int**) 0x6b7e98;
	if (*(int*) ((int) o + 0xc84) == 1)
		*(int*) ((int) o + 0xc60) = f;
	if (*a1 == 0) {
		fcn_00425bf0((void*) o, *(int*) ((int) o + 0x118), (char*) 0x676958);
		return 0;
	}
	v[0] = fcn_00445600(0, 0x140, 0, *a3);
	v[1] = fcn_00445600(0, 0x140, 0, *a4);
	v[2] = fcn_00445600(0, 0x140, 0, *a5);
	v[3] = fcn_00445600(0, 0x140, 0, *a6);
	v[4] = fcn_00445600(0, 0x140, 0, *a7);
	for (i = 0; i < 5; i++) {
		if (v[i] != 0)
			c++;
	}
	fcn_00414fb0(*a1, *a2 / 0xe, c, v);
	return 1;
}
