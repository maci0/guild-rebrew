// FUNCTION: GOLD 0x00426450
// SIZE: 76
// FUNCTION: GOLDTL 0x4228c0
// SIZE: 76

extern int* g_6b7d78;
extern int g_6b7d7c;
extern char g_14cb980[];

char* __cdecl fcn_004228c0(char* key)
{
	char* p;
	int i;

	p = ((char*)g_6b7d78);
	if (g_6b7d7c == 0) {
		return g_14cb980;
	}
	for (; p != 0; p = *(char**) (p + 0x13c)) {
		for (i = 0; i < *(int*) (p + 0x134); i++) {
			if (*(char**) (p + 0x138) + i * 0x40 == key) {
				return p;
			}
		}
	}
	return p;
}
