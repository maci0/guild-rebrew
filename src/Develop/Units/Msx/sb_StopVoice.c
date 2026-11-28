extern int g_6b7d7c;



extern volatile int g_6b7fac;
int __cdecl msx_EndSample(int);

void __cdecl sb_StopVoice(int* p, int fade)
{
	if (g_6b7d7c != 0 && p != 0) {
		if (fade != 0) {
			p[5] |= 2;
			p[4] = (g_6b7fac * 2 + g_6b7fac) * 4 + g_6b7fac;
			return;
		}
		msx_EndSample(p[0]);
		p[5] |= 8;
	}
}
