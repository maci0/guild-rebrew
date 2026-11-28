extern char g_9b0dc0[];


void __cdecl cut_DestroyActiveCharacter(int);

/* ADDRESS: GOLDDE 0x004c6f70 */
void __cdecl cut_DestroyAllActiveCharacters(void)
{
	int a;
	int v;

	for (a = (int) &g_9b0dc0; a < ((int) &g_9b0dc0 + 0x40); a += 4) {
		v = *(int*) a;
		if (v != 0) {
			cut_DestroyActiveCharacter(v);
		}
	}
}
