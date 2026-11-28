/* fcn_004dfef0 — register the name and clear the pending flag. */

void __cdecl gm_GenerateShuffledIndices(int, int);

/* ADDRESS: GOLDTL 0x004dfef0 */
void __cdecl cut_InitShufflePool(int count)
{
	gm_GenerateShuffledIndices(count, 0x9afe00);
	*(int*) 0x68bfc8 = count;
	*(int*) 0x772f60 = 0;
}
