extern unsigned char gm_ActiveTownIndex;
extern double g_662a20;
extern double g_664f18;
extern double dbl_0_01;

char* __cdecl gm_QueryEntities(int, int, int, ...);
int __cdecl gm_AccumulateTyped2(char* entity);
int __cdecl cm_RequestMoveCredits(int a1, int a2, char a3, int a4);
int __cdecl cm_SendSellObjekt(int a1, int a2, int a3, int a4, char a5, int a6);
float __cdecl gm_GetSeasonPrice(int id, unsigned char a);
unsigned int __cdecl cut_RandMod(unsigned int n);
int __cdecl _ftol(void);
char* __cdecl gm_NextEntityQueryMatch(void);
short* __cdecl gm_GetEntityTableEntry(char* entity);

/* ADDRESS: GOLDTL 0x004d5110 */
/* ADDRESS: GOLDDE 0x004c2060 */
int __cdecl gm_TransferAndSellAssets(char* bld1, char* bld2, char* entity, char* otherEntity)
{
	char* p1;
	char* p2;
	char* match;
	int v;
	int delay;

	p1 = gm_QueryEntities(*(int*) (bld2 + 0x5d), 2, 6, 0, 0x116);
	p2 = gm_QueryEntities(*(int*) (bld1 + 0x5d), 2, 6, 0, 0x2a);
	v = gm_AccumulateTyped2(otherEntity);
	v = v < 0 ? 0 : v;
	if (v >= 0x9c400) {
		v = 0x9c400;
	}
	v = (int) (((double) cut_RandMod(0x32) * g_662a20 + g_664f18) * v);
	cm_RequestMoveCredits(*(int*) (entity + 4), *(int*) (otherEntity + 4), gm_ActiveTownIndex, v);
	if (p2 != 0 && p1 != 0) {
		match = gm_QueryEntities(*(int*) (p2 + 0x14), 1, 5);
		while (match != 0) {
			delay = (int) (((double) (cut_RandMod(0x14) + 0x50) * 0.01) * *(int*) (match + 0xe));
			if (delay < 1) {
				delay = 1;
			}
			cm_SendSellObjekt(*(int*) (p1 + 2), *(int*) (p2 + 2), (unsigned int) (unsigned short) *(short*) match, delay, gm_ActiveTownIndex, 0);
			v = (int) (gm_GetSeasonPrice(*(unsigned short*) match, gm_ActiveTownIndex) * delay + v);
			match = gm_NextEntityQueryMatch();
		}
	}
	p1 = (char*) gm_GetEntityTableEntry(entity);
	if (p1 != 0) {
		*(int*) (p1 + 0x1c) += v;
	}
	return v;
}
