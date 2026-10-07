extern char g_6b5c60[];

// FUNCTION: GOLDTL 0x5351e0

void __cdecl fcn_004712d0(int, char*, char*);

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
			fcn_004712d0(((int*) (o + 0x228))[i], o + 8 + (i & 3) * 0x80, g_6b5c60);
		} else {
			fcn_004712d0(((int*) (o + 0x228))[i], g_6b5c60, g_6b5c60);
		}
	}
	return 1;
}
