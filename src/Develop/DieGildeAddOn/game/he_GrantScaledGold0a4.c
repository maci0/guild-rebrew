


extern unsigned char g_773d75;
extern float g_6628a0;

float __cdecl gm_GetSeasonPrice(int, unsigned char);
double __cdecl gm_RandomFloat01(void);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);

void __cdecl he_GrantScaledGold0a4(char* e)
{
	float v;

	v = gm_GetSeasonPrice(0x2b7, (*(char*)&g_773d75));
	cm_RequestTransferCurrencyNoKill(*(int*) (e + 4), -1, (*(char*)&g_773d75), (int) ((gm_RandomFloat01() * 2.0 + g_6628a0) * v));
}
