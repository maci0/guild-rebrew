extern unsigned char g_773d75;

float __cdecl gm_GetSeasonPrice(int id, unsigned char a);
int __cdecl cm_SendSellObjekt(int, int, int, int, char, int);


/* ADDRESS: GOLDTL 0x0049c2b0 */
int __cdecl ai_RunObjektKaufen(int* a, char* e, int* b)
{
	int n;

	if (*e != 2)
		return 0;
	n = (int) gm_GetSeasonPrice(*(int*) (e + 4), (*(char*)&g_773d75));
	cm_SendSellObjekt(a[1], b[1], *(int*) (e + 4), *(int*) (e + 8), (*(char*)&g_773d75), n);
	return 0xc;
}
