int __cdecl evt_LogScriptError(void*, int, char*);
int __cdecl fcn_00445600(int, int, int, int);
void __cdecl fcn_00414fb0(int, int, int, int*);
int __cdecl ObjectFlight(int*, int*, int*, int*, int*, int*, int*);

/* ADDRESS: GOLDTL 0x0040f7c0 */
int __cdecl ObjectFlight(int* a1, int* a2, int* a3, int* a4, int* a5, int* a6, int* a7)
{
	int values[5];
	int i;
	int count = 0;
	int g;
	int handler;
	int* o;

	g = *(int*) 0x6b7ebc;
	handler = (int) ObjectFlight;
	if (g != 0 && *(int*) (g + 0x44) == handler) {
		if (*(int*) 0x6b5cbc == 0 && *(int*) 0x6b5cc0 == 0)
			return 0;
		*(int*) (*(int*) 0x6b7e98 + 0xc60) = handler;
		return 0;
	}
	o = *(int**) 0x6b7e98;
	if (*(int*) ((int) o + 0xc84) == 1) {
		*(int*) ((int) o + 0xc60) = handler;
		o = *(int**) 0x6b7e98;
	}
	if (*a1 == 0) {
		evt_LogScriptError((void*) o, *(int*) ((int) o + 0x118), (char*) 0x676958);
		return 0;
	}
	values[0] = fcn_00445600(0, 0x140, 0, *a3);
	values[1] = fcn_00445600(0, 0x140, 0, *a4);
	values[2] = fcn_00445600(0, 0x140, 0, *a5);
	values[3] = fcn_00445600(0, 0x140, 0, *a6);
	values[4] = fcn_00445600(0, 0x140, 0, *a7);
	for (i = 0; i < 5; i++) {
		if (values[i] != 0)
			count++;
	}
	fcn_00414fb0(*a1, *a2 / 0xe, count, values);
	return 1;
}
