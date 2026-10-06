// FUNCTION: GOLD 0x00576c80
// FUNCTION: GOLDTL 0x0057f220

extern int* g_665f08;
extern int g_6b7fac;
extern unsigned char* g_868050;

int __cdecl fcn_0057f220(int* m)
{
	if (m[0] == 0x1b && m[1] != 0 && g_665f08[1] == 4) {
		if (((char*)g_868050)[*(unsigned char*) m[1] * 589] == 0xd) {
			g_665f08[0] = 0xa;
			g_665f08[1] = 0xa;
			g_665f08[3] = *(volatile int*) ((char*)&g_6b7fac);
			return 1;
		}
	}
	else if (m[0] == 0x1c && m[1] != 0 && ((char*)g_868050)[*(unsigned char*) m[1] * 589] == 0xd) {
		g_665f08[0] = 0xb;
		g_665f08[1] = 0xb;
		g_665f08[3] = *(volatile int*) ((char*)&g_6b7fac);
		return 1;
	}
	return 3;
}
