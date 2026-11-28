


extern unsigned char gm_ActiveTownIndex;
extern float flt_1_0;

float __cdecl gm_GetSeasonPrice(int, unsigned char);
double __cdecl gm_RandomFloat01(void);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);

void __cdecl he_GrantScaledGold0a4(char* e)
{
	float v;

	v = gm_GetSeasonPrice(0x2b7, (*(char*)&gm_ActiveTownIndex));
	cm_RequestTransferCurrencyNoKill(*(int*) (e + 4), -1, (*(char*)&gm_ActiveTownIndex), (int) ((gm_RandomFloat01() * 2.0 + flt_1_0) * v));
}
