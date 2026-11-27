


extern int* g_665f08;
extern volatile int g_6b7fac;

int __cdecl d2_UpdateTutCh2Action110Step(int* msg)
{
	short* e;

	if (*msg == 0x1a) {
		e = (short*) msg[1];
		if (e != 0 && *e == 0x110) {
			g_665f08[0] = 0xb;
			g_665f08[1] = 0xb;
			g_665f08[3] = g_6b7fac;
			return 1;
		}
	}
	return 3;
}
