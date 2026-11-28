extern char g_9afe00[];
extern char g_68bfc8[];
extern char g_772f60[];
/* fcn_004dfef0 — register the name and clear the pending flag. */

void __cdecl gm_GenerateShuffledIndices(int, int);

/* ADDRESS: GOLDTL 0x004dfef0 */
/* ADDRESS: GOLDDE 0x004cc910 */
void __cdecl cut_InitShufflePool(int count)
{
	gm_GenerateShuffledIndices(count, (int) &g_9afe00);
	*(int*) &g_68bfc8 = count;
	*(int*) &g_772f60 = 0;
}
