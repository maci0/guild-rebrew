extern unsigned char gm_ActiveTownIndex;

char* __cdecl gm_SearchTable67(int id);
float __cdecl gm_GetSeasonPrice(int id, unsigned char k);
int __cdecl cm_SendSellObjekt(int a, int b, int c, int d, unsigned char k, int n);

/* ADDRESS: GOLDTL 0x00497670 */
/* ADDRESS: GOLDDE 0x004860f0 */
int __cdecl ai_RunRaumKaufen(int unused, char* it, char* x)
{
	char* t;

	t = gm_SearchTable67(*(int*) (x + 4));
	if (!t) {
		return 0;
	}
	if (it[0] != 2) {
		return 0;
	}
	cm_SendSellObjekt(*(int*) (t + 1), -1, *(int*) (it + 4), *(int*) (it + 8), gm_ActiveTownIndex, (int) gm_GetSeasonPrice(*(int*) (it + 4), gm_ActiveTownIndex));
	return 0xe;
}
