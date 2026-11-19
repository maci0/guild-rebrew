

void __cdecl ch_DestroyCharacter(int);

void __cdecl ch_ClearCharacters(void)
{
	int a;
	int v;

	for (a = 0x14d0020; a < 0x14d0c20; a += 4) {
		v = *(int*) a;
		if (v != 0) {
			ch_DestroyCharacter(v);
			*(int*) a = 0;
		}
	}
}
