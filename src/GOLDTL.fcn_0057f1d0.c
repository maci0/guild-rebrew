// FUNCTION: GOLD 0x00576c30
// SIZE: 73
// FUNCTION: GOLDTL 0x57f1d0
// SIZE: 73

extern int* g_665f08;
extern char g_6b7fac[];

int __cdecl fcn_0057f1d0(int* msg)
{
	short* e;

	if (*msg == 0x1a) {
		e = (short*) msg[1];
		if (e != 0 && *e == 0x110) {
			g_665f08[0] = 0xb;
			g_665f08[1] = 0xb;
			g_665f08[3] = *(volatile int*) g_6b7fac;
			return 1;
		}
	}
	return 3;
}
