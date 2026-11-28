

void __cdecl sb_LoadSampleBank(int, int);

/* ADDRESS: GOLDDE 0x0040fcd0 */
void __cdecl LoadSampleBank(int* p)
{
	sb_LoadSampleBank(*p, 1);
}
