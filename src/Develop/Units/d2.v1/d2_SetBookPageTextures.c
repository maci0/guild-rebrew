extern char str_empty[];



void __cdecl d2_SetFormTextures(int, char*, char*);

int __cdecl d2_SetBookPageTextures(char* o, char n)
{
	int i;

	if (o == 0) {
		return 0;
	}
	if (n > o[0x271]) {
		return 0;
	}
	for (i = 0; i < o[0x271]; i++) {
		if (i >= n && i <= n + 1) {
			d2_SetFormTextures(((int*) (o + 0x228))[i], o + 8 + (i & 3) * 0x80, str_empty);
		} else {
			d2_SetFormTextures(((int*) (o + 0x228))[i], str_empty, str_empty);
		}
	}
	return 1;
}
