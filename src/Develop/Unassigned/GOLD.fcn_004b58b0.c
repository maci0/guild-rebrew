

extern char g_6024c8[];
extern char g_6024c4[];
extern int g_14673a0;
extern int g_f8a668;
extern int g_6f22a0;

int __cdecl fcn_004741e0(int, int, char*);
void __cdecl fcn_004755f0(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_00515990(int);
int __cdecl fcn_005309d0(void*, int);
void __cdecl fcn_004758e0(int);

void __cdecl fcn_004b58b0(int flags)
{
	int h;

	h = fcn_004741e0(0, 0, g_6024c8);
	fcn_004755f0(h);
	d2_SetForm(h, 1);
	fcn_00515990(0x1b99);
	fcn_00515990((int) g_6024c4);
	d2_SetForm(h, 2);
	fcn_00515990(0x7d);
	flags |= 0x80;
	while (fcn_005309d0(fcn_004b58b0, flags) != 0) {
		if (g_14673a0 != 0)
			g_6f22a0 = 1;
		else if (g_f8a668 == 0)
			g_6f22a0 = 1;
	}
	fcn_004758e0(h);
}
