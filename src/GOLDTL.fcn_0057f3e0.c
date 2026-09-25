// FUNCTION: GOLD 0x00576e10
// SIZE: 72
// FUNCTION: GOLDTL 0x57f3e0
// SIZE: 72

extern int* g_665f08;
extern char g_6b7fac[];

int __cdecl fcn_0057f3e0(int* msg)
{
	short* e;

	if (*msg == 0x19) {
		e = (short*) msg[1];
		if (e != 0 && *e == 0x74) {
			g_665f08[0] = 0xb;
			g_665f08[1] = 0xb;
			g_665f08[3] = *(volatile int*) g_6b7fac;
			return 1;
		}
	}
	return 3;
}
