extern int g_6b7d7c;



extern int g_6b7fac;
int __cdecl fcn_0042a880(int);

void __cdecl fcn_004237f0(int* p, int a2)
{
	if (g_6b7d7c != 0 && p != 0) {
		if (a2 != 0) {
			p[5] |= 2;
			p[4] = ((*(volatile int*)&g_6b7fac) * 2 + (*(volatile int*)&g_6b7fac)) * 4 + (*(volatile int*)&g_6b7fac);
			return;
		}
		fcn_0042a880(p[0]);
		p[5] |= 8;
	}
}
