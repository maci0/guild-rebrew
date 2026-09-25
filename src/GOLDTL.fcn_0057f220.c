// FUNCTION: GOLDTL 0x0057f220
// SIZE: 192

extern int* g_665f08;
extern char* g_868050;

int __cdecl fcn_0057f220(int* m)
{
	if (m[0] == 0x1b && m[1] != 0 && g_665f08[1] == 4) {
		if (g_868050[*(unsigned char*) m[1] * 589] == 0xd) {
			g_665f08[0] = 0xa;
			g_665f08[1] = 0xa;
			g_665f08[3] = *(int*) 0x6b7fac;
			return 1;
		}
	}
	else if (m[0] == 0x1c && m[1] != 0 && g_868050[*(unsigned char*) m[1] * 589] == 0xd) {
		g_665f08[0] = 0xb;
		g_665f08[1] = 0xb;
		g_665f08[3] = *(int*) 0x6b7fac;
		return 1;
	}
	return 3;
}
