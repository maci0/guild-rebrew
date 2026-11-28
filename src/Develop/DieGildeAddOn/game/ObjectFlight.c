extern char g_6b5cbc[];
extern char g_676958[];
int __cdecl evt_LogScriptError(void*, int, char*);
int __cdecl d3_FindSceneObject(int, int, int, int);
void __cdecl d3_CreateFlightAnimation(int, int, int, int*);
int __cdecl ObjectFlight(int*, int*, int*, int*, int*, int*, int*);

/* ADDRESS: GOLDTL 0x0040f7c0 */
/* ADDRESS: GOLDDE 0x0040e5c0 */
int __cdecl ObjectFlight(int* a1, int* a2, int* a3, int* a4, int* a5, int* a6, int* a7)
{
	int values[5];
	int i;
	int count = 0;
	int g;
	int handler;
	int* o;

	g = *(int*) ((int) &g_6b5cbc + 0x2200);
	handler = (int) ObjectFlight;
	if (g != 0 && *(int*) (g + 0x44) == handler) {
		if (*(int*) &g_6b5cbc == 0 && *(int*) ((int) &g_6b5cbc + 0x4) == 0)
			return 0;
		*(int*) (*(int*) ((int) &g_6b5cbc + 0x21dc) + 0xc60) = handler;
		return 0;
	}
	o = *(int**) ((int) &g_6b5cbc + 0x21dc);
	if (*(int*) ((int) o + 0xc84) == 1) {
		*(int*) ((int) o + 0xc60) = handler;
		o = *(int**) ((int) &g_6b5cbc + 0x21dc);
	}
	if (*a1 == 0) {
		evt_LogScriptError((void*) o, *(int*) ((int) o + 0x118), (char*) &g_676958);
		return 0;
	}
	values[0] = d3_FindSceneObject(0, 0x140, 0, *a3);
	values[1] = d3_FindSceneObject(0, 0x140, 0, *a4);
	values[2] = d3_FindSceneObject(0, 0x140, 0, *a5);
	values[3] = d3_FindSceneObject(0, 0x140, 0, *a6);
	values[4] = d3_FindSceneObject(0, 0x140, 0, *a7);
	for (i = 0; i < 5; i++) {
		if (values[i] != 0)
			count++;
	}
	d3_CreateFlightAnimation(*a1, *a2 / 0xe, count, values);
	return 1;
}
