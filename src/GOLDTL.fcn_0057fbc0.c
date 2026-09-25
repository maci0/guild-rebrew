// FUNCTION: GOLD 0x005775f0
// SIZE: 181
// FUNCTION: GOLDTL 0x0057fbc0
// SIZE: 181

extern int* g_665f08;
extern char* g_868050;
extern short g_774970;

int __cdecl fcn_0057fbc0(int* m)
{
	if (g_665f08[14] >= 0 && m[0] == 0x28 && m[3] == 0x155) {
		g_665f08[14] = 1;
		return 1;
	}
	if (g_665f08[14] >= 1 && m[0] == 0x27 && m[3] == 0x1d0) {
		g_665f08[14] = 2;
		return 1;
	}
	if (g_665f08[14] >= 2 && m[1] != 0 && m[0] == 0x24 &&
	    g_868050[*(unsigned char*) m[1] * 589] == 0x12 && *(short*) (m[1] + 0x27) == g_774970) {
		g_665f08[14] = 3;
		return 1;
	}
	if (m[0] == 0x1a || m[0] == 0x1c) {
		return 1;
	}
	return 0;
}
