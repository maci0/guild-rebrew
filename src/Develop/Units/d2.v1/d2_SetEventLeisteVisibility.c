extern char g_6a476c[];
extern char g_77e8a0[];


void __cdecl d2_SetFormVisibility(int, int);

/* ADDRESS: GOLDDE 0x0052c100 */
void __cdecl d2_SetEventLeisteVisibility(int a1)
{
	if (*(int*) &g_6a476c != -1) {
		d2_SetFormVisibility(*(int*) &g_77e8a0, a1);
	}
}
