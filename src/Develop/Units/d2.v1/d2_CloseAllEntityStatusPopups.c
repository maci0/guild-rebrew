extern char g_9ba2e0[];


void __cdecl d2_CloseWindow(int);

/* ADDRESS: GOLDDE 0x004bcf60 */
void __cdecl d2_CloseAllEntityStatusPopups(void)
{
	int a;
	int v;

	for (a = (int) &g_9ba2e0; a < ((int) &g_9ba2e0 + 0x80); a += 4) {
		v = *(int*) a;
		if (v != -1) {
			d2_CloseWindow(v);
			*(int*) a = -1;
		}
	}
}
