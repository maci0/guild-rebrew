extern char g_14d0020[];


void __cdecl ch_DestroyCharacter(int);

/* ADDRESS: GOLDDE 0x0040af70 */
void __cdecl ch_ClearCharacters(void)
{
	int a;
	int v;

	for (a = (int) &g_14d0020; a < ((int) &g_14d0020 + 0xc00); a += 4) {
		v = *(int*) a;
		if (v != 0) {
			ch_DestroyCharacter(v);
			*(int*) a = 0;
		}
	}
}
