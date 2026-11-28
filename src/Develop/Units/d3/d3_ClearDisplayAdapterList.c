extern char g_6b5de8[];


void __cdecl d3_RemoveDisplayAdapter(int);

/* ADDRESS: GOLDDE 0x00417fe0 */
void __cdecl d3_ClearDisplayAdapterList(void)
{
	while (*(unsigned*) &g_6b5de8 > 0) {
		d3_RemoveDisplayAdapter(0);
	}
}
