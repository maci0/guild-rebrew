extern unsigned char gm_ActiveTownIndex;

char* __cdecl gm_FindCityItemHolder(int id);
char* __cdecl fcn_00502cd0(int a, int b, int c, int d);
int __cdecl gm_GetMsgField(char* g, char* s);
int __cdecl gm_GetSeasonTreasury(int a, unsigned char k);
float __cdecl gm_GetSeasonPrice(int id, unsigned char k);

/* ADDRESS: GOLDTL 0x0049c1c0 */
int __cdecl ai_StartObjektKaufen(int a1, int a2, int k, char* it, char* out)
{
	char* g;
	char* s;
	int n;

	if (k == 2 && it[0] == 2) {
		g = gm_FindCityItemHolder(*(int*) (it + 4));
		if (g) {
			s = fcn_00502cd0(*(int*) (g + 0x14), 1, 0, *(int*) (it + 4));
			if (s && gm_GetMsgField(g, s) >= 1) {
				n = gm_GetSeasonTreasury(a2, gm_ActiveTownIndex);
				if (*(float*) (it + 0x14) > 0.0f && *(float*) (it + 0x14) < 1.0f) {
					n = (int) (n * *(float*) (it + 0x14));
				}
				if (n >= (int) gm_GetSeasonPrice(*(int*) (it + 4), gm_ActiveTownIndex)) {
					out[0] = 1;
					*(int*) (out + 4) = *(int*) (g + 2);
					*(int*) (out + 8) = 1;
					return 0xc;
				}
			}
		}
	}
	return 0;
}
