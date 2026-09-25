// FUNCTION: GOLDTL 0x0057fa40
// SIZE: 120

extern int* g_665f08;
extern char* g_868050;

int __cdecl fcn_0057ed10(int* m);

int __cdecl fcn_0057fa40(int* m)
{
	if (g_665f08[14] >= 0 && m[0] == 0x25 && m[3] == 0x155) {
		g_665f08[14] = 1;
		return 1;
	}
	if (g_665f08[14] >= 1 && m[1] != 0 && m[0] == 0x24) {
		if (g_868050[*(unsigned char*) m[1] * 589] == 0xa) {
			g_665f08[14] = 2;
			return 1;
		}
		return 0;
	}
	return fcn_0057ed10(m);
}
