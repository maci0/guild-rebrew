extern char g_6b5c60[];



void __cdecl d2_SetFormTextures(int, char*, char*);

int __cdecl fcn_005351e0(char* o, char n)
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
			d2_SetFormTextures(((int*) (o + 0x228))[i], o + 8 + (i & 3) * 0x80, g_6b5c60);
		} else {
			d2_SetFormTextures(((int*) (o + 0x228))[i], g_6b5c60, g_6b5c60);
		}
	}
	return 1;
}
