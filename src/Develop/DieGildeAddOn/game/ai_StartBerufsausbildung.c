extern float g_664150;
extern unsigned char gm_ActiveTownIndex;

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_IsNpcEntityState(char*);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl gm_CalcPersonWealth(unsigned short);
int __cdecl gm_GetSeasonTreasury(char*, char);
unsigned short __cdecl gm_RandomMod(int);
char* __cdecl gm_GetEntityTableEntry(char*);
int __cdecl gm_MapEntityStatRange(int);
int __cdecl gm_GetRangeStatId(int, int);

/* ADDRESS: GOLDTL 0x004a0bb0 */
int __cdecl ai_StartBerufsausbildung(int busy, char* ent, int pending, char* out1, char* out2)
{
	char* q;
	char* best;
	int i;
	int scale;
	int rnd;
	int idx;
	unsigned short w;

	if (pending != 0) {
		return 0;
	}
	if (busy != 0) {
		return 0;
	}
	if (*(unsigned char*) (ent + 2) != 5) {
		q = gm_LookupEntityRecordById(*(int*) (ent + 0x5c));
		if (q != 0) {
			if (*(unsigned char*) (q + 2) == 5 || *(unsigned char*) (q + 2) == 6 || *(unsigned char*) (q + 2) == 7) {
				return 0;
			}
			if (*(char*) (q + 9) == 0) {
				if (gm_IsNpcEntityState(q) != 0) {
					return 0;
				}
			}
		}
	}
	best = 0;
	for (i = 0; i < 5; i++) {
		q = gm_LookupEntityRecordById(*(int*) (ent + 0x68 + i * 4));
		if (q == 0) {
			continue;
		}
		if (*(unsigned char*) (q + 8) <= 0) {
			continue;
		}
		if ((float) (*(unsigned short*) (q + 0xa) + 4) >= *(float*) (q + 0x20)) {
			if (*(unsigned char*) (q + 0x164) == 0) {
				if (he_StartHandlungSearch(2, 2, *(unsigned short*) q, 0, 0x5e) == 0) {
					if (best == 0 || *(unsigned short*) (q + 0xa) > *(unsigned short*) (best + 0xa)) {
						best = q;
					}
				}
			}
		}
	}
	if (best == 0) {
		return 0;
	}
	scale = (int) ((float) gm_CalcPersonWealth(*(unsigned short*) ent) * g_664150);
	if (gm_GetSeasonTreasury(ent, (char) gm_ActiveTownIndex) < scale * 6) {
		return 0;
	}
	w = (unsigned short) gm_RandomMod(0xf);
	idx = w + 1;
	if (*(unsigned char*) (ent + 2) == 5) {
		q = gm_GetEntityTableEntry(ent);
		rnd = gm_RandomMod(0x10) & 0xffff;
		for (i = 0x10; i != 0; i--) {
			if (rnd != 0 && q[rnd + 0x74] == 0) {
				idx = rnd;
				break;
			}
			rnd = (rnd + 1) % 0x10;
		}
	} else if (*(unsigned char*) (ent + 0x164) != 0) {
		idx = gm_MapEntityStatRange(*(unsigned char*) (ent + 0x164));
	}
	*out1 = 7;
	*(int*) (out1 + 4) = *(int*) (best + 4);
	*out2 = 0x17;
	*(int*) (out2 + 4) = gm_GetRangeStatId(idx, 1);
	*(int*) (out2 + 0x10) = scale;
	return 0x3a;
}
