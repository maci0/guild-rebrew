extern int g_772f2c;
extern unsigned short* cut_ActivePlayerEntity;
extern unsigned short* cut_CombatDefenderEntity;
extern char* g_772eb4;
extern int d3_ActiveScene;

char* __cdecl gm_LookupEntityRecordIn32SlotTable(int id);
int* __cdecl gm_FindOrCreateEntitySlot(char*, char*);
float __cdecl gm_GetEntityHealthRatio(char*);
int __cdecl gm_RandomMod(int);
int __cdecl cut_FindCombatTarget(char*);
char* __cdecl d3_FindNearestEscapeNode(char*);
void __cdecl d3_TransformPoint(char*, char*, float*);
char __cdecl d3sm_SampleHeight(int, float*, int*, int*, float*);

/* ADDRESS: GOLDTL 0x004d4430 */
void __cdecl cut_UpdateCombatTeamOrders(char* a0)
{
	int* p;
	int* base;
	int i;
	int n;
	int v;
	int* x;
	int t;
	char* e;
	char* r;
	float pos[4]; /* native frame has one more word than three floats */
	int col;
	int row;
	float height;

	if (g_772f2c < 1) {
		return;
	}
	p = (int*) (a0 + 0x98);
	for (n = 16; n != 0; n--, p = (int*) ((char*) p + 0x2c)) {
		if (g_772f2c > 1) {
			if (p[0] == 3 || p[0] == 4) {
				continue;
			}
			if (p[0] == 2) {
				if (*(char*) (gm_LookupEntityRecordIn32SlotTable(p[3]) + 8) != 0) {
					continue;
				}
			}
		}
		p[-1] = -1;
		p[0] = 0;
	}
	if ((int) cut_ActivePlayerEntity == (int) cut_CombatDefenderEntity) {
		base = (int*) (g_772eb4 + 0xc0);
	} else {
		base = (int*) (g_772eb4 + 0x80);
	}
	for (i = 0; i < 16; i++) {
		if (base[i] == -1) {
			continue;
		}
		e = gm_LookupEntityRecordIn32SlotTable(base[i]);
		gm_FindOrCreateEntitySlot(a0, e);
		v = (int) (gm_GetEntityHealthRatio(e) * 100.0);
		if (v >= 20 || (unsigned short) gm_RandomMod(100) <= 0x1e) {
			t = cut_FindCombatTarget(e);
			if (t == 0) {
				continue;
			}
			x = gm_FindOrCreateEntitySlot(a0, e);
			x[0] = *(int*) (e + 4);
			x[1] = 2;
			x[4] = *(int*) (t + 4);
		} else {
			r = d3_FindNearestEscapeNode(e);
			d3_TransformPoint(r, r + 0x4c, pos);
			if (d3sm_SampleHeight(*(int*) (d3_ActiveScene + 0xb0), pos, &col, &row, &height)) {
				continue;
			}
			x = gm_FindOrCreateEntitySlot(a0, e);
			x[0] = *(int*) (e + 4);
			x[1] = 3;
			x[4] = col;
			x[5] = row;
		}
	}
}
