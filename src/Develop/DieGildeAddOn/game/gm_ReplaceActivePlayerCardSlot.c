extern char g_1007cd4[];


int __cdecl gm_ReplaceCardSlot(void*, int);

/* ADDRESS: GOLDDE 0x00496aa0 */
int __cdecl gm_ReplaceActivePlayerCardSlot(int a1)
{
	return gm_ReplaceCardSlot((void*) (*(int*) &g_1007cd4 + 4), a1);
}
