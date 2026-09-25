typedef struct Kind {
	char pad0[0x247];
	unsigned char cap;
	char pad248[0x24d - 0x248];
} Kind;
// SIZE 0x24d

extern Kind* g_868050;

char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int id, int c, int d);
char* __cdecl gm_AddObjekt(void);
char* __cdecl fcn_00502cd0(int a, int b, int c, int d);
int __cdecl fcn_005463a0(int a, int b, int c, int d, int e);

// FUNCTION: GOLDTL 0x4ab010
// SIZE: 192
int __cdecl fcn_004ab010(unsigned short* e, char* o1, char* o2)
{
	char* s;
	char* q;

	for (s = gm_StartFilteredEntitySearch(2, 4, *e, 5, 0x16); s; s = gm_AddObjekt()) {
		if (g_868050[*(unsigned char*) s].cap > 1) {
			q = fcn_00502cd0(*(int*) (s + 0x5d), 1, 0, 0x120);
			if (q && fcn_00502cd0(*(int*) (q + 0x14), 1, 0, 0x12c) && !fcn_005463a0(2, 0, 0x74, 3, *(int*) (s + 1))) {
				o1[0] = 4;
				*(int*) (o1 + 4) = *(int*) (s + 1);
				o2[0] = 1;
				*(int*) (o2 + 4) = *(int*) (q + 2);
				return 1;
			}
		}
	}
	return 0;
}
