// FUNCTION: GOLDTL 0x0057f310
// SIZE: 146

extern int* g_665f08;

int __cdecl fcn_0057f310(int* m)
{
	if (m[0] == 0x19 && m[1] != 0 && g_665f08[1] == 4) {
		if (*(short*) m[1] == 0x13) {
			g_665f08[0] = 0xa;
			g_665f08[1] = 0xa;
			g_665f08[3] = *(int*) 0x6b7fac;
			return 1;
		}
	}
	else if (m[0] == 0x1a && m[1] != 0 && *(short*) m[1] == 0x13) {
		g_665f08[0] = 0xb;
		g_665f08[1] = 0xb;
		g_665f08[3] = *(int*) 0x6b7fac;
		return 1;
	}
	return 3;
}
