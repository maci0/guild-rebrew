extern char* g_104049c;

char __cdecl fcn_0045d040(char* a);

// FUNCTION: GOLDTL 0x45d090
// SIZE: 63
char __cdecl fcn_0045d090(char* a, int v)
{
	if (a != 0) {
		if ((a[0x54] & 2) != 0) {
			a = g_104049c + *(int*) (a + 0x44) * 0x70;
		}
		if (*(int*) (a + 0x60) != v) {
			*(int*) (a + 0x60) = v;
			return fcn_0045d040(a);
		}
	}
	return 0;
}
