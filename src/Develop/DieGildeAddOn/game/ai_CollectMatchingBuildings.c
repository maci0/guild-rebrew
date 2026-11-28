extern int g_6643d8[];
extern unsigned char* g_entity_ptr;

unsigned short __cdecl gm_RandomMod(int a0);
int __cdecl ai_MatchesBuildingFilter(unsigned short* a0, int* a1, int a2);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, int a2);

/* ADDRESS: GOLDTL 0x004a5fe0 */
/* ADDRESS: GOLDDE 0x004949e0 */
int __cdecl ai_CollectMatchingBuildings(unsigned short* actor, int arg1, int arg2, int mask, float minFavor, float maxFavor, int maxCount, int* entityIds)
{
	int flag;
	int step;
	int buf[20];
	int limit;
	int count;
	int bldEntry;
	int i;
	int idx;
	float favor;

	step = g_6643d8[gm_RandomMod(0x10)];
	flag = 0;
	buf[5] = 0;
	buf[2] = arg2;
	buf[3] = mask | 0x80000000;
	buf[4] = arg1;
	if ((minFavor > 0.0 || maxFavor < 100.0) && minFavor < maxFavor) {
		flag = 1;
	}
	i = 0x100;
	idx = gm_RandomMod(0x100);
	limit = maxCount & 0xff;
	count = 0;
	if (limit > 0) {
		do {
			if (i == 0) {
				break;
			}
			bldEntry = (int) &g_entity_ptr[idx * 169];
			if (*(char*) bldEntry == 0) {
				goto next;
			}
			if (ai_MatchesBuildingFilter(actor, buf, bldEntry) == 0) {
				goto next;
			}
			if (flag != 0) {
				favor = gm_CalcEntityFavor(*(unsigned short*) (bldEntry + 0x27), *actor, 1);
				if (favor < *(float*) (buf + 0x11) || favor > *(float*) (buf + 0x11)) {
					goto next;
				}
			}
			entityIds[count] = *(int*) (bldEntry + 1);
			count++;
next:
			i--;
			idx = (idx + step) % 0x100;
		} while (count < limit);
	}
	return count;
}
