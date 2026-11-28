extern unsigned char gm_PlayerCount;
extern int ai_DispatchedTradeCount;

char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);


/* ADDRESS: GOLDTL 0x0047d1e0 */
/* ADDRESS: GOLDDE 0x0046c1a0 */
int __cdecl he_CountActiveTradeActions(void)
{
	int n;
	char* p;

	n = 0;
	for (p = he_StartHandlungSearch(1, 0, 0xb); p != 0; p = he_fn_Handlung()) {
		if (p[0xf1] == 0)
			n++;
	}
	return gm_PlayerCount * ai_DispatchedTradeCount + n;
}
