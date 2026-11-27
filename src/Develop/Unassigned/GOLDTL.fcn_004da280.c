

void __cdecl cut_DestroyActiveCharacter(int);

void __cdecl cut_DestroyAllActiveCharacters(void)
{
	int a;
	int v;

	for (a = 0x9b0dc0; a < 0x9b0e00; a += 4) {
		v = *(int*) a;
		if (v != 0) {
			cut_DestroyActiveCharacter(v);
		}
	}
}
