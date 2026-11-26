


extern char g_68149c[];

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_CheckEntityType(char*);
int __cdecl gm_IsWarehouse(char*);
unsigned short __cdecl gm_RandomMod(unsigned short);
char* __cdecl fcn_00445600(int, int, int, char*);
void __cdecl d3_TransformPoint(char*, char*, float*);

int __cdecl gm_PickRandomBuildingPoint(float* out)
{
	char* list[0x100];
	unsigned short n;
	char* e;
	char* r;

	n = 0;
	for (e = gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_FindNextFilteredEntity()) {
		if (gm_CheckEntityType(e) == 0 && gm_IsWarehouse(e) == 0 && *(int*) (e + 0x61) != 0)
			list[n++] = e;
	}
	e = list[gm_RandomMod(n)];
	r = fcn_00445600(*(int*) (e + 0x61), 0x300, 0, g_68149c);
	if (r != 0) {
		d3_TransformPoint(r, r + 0x4c, out);
	} else {
		e = *(char**) (e + 0x61);
		d3_TransformPoint(e, e + 0x4c, out);
	}
	return 1;
}
