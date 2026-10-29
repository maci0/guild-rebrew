extern char g_68ce48[];
extern unsigned short* g_772f24;
extern int g_772f2c;
extern char g_6b5c60[];
extern int g_772514;
extern char* g_77255c;
extern int g_68bfbc;
extern int g_68bfb8;
extern int g_100f1dc;
extern int g_67d370;
extern int g_774654;

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl fcn_004e6e20(int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_004cfca0(void);
void __cdecl fcn_00471e30(int);


/* ADDRESS: GOLDTL 0x004e16e0 */
void __cdecl fcn_004e16e0(char* a1, int* a2)
{
	int b2;
	char* x;
	char* y;
	char* who;
	int h;
	int t;
	int b0;
	int b1;
	int w;

	x = fcn_00508e40(a2[13]);
	y = fcn_00508e40(a2[14]);
	if (*(int*) (x + 4) == ((int*)g_772f24)[1])
		who = y;
	else
		who = x;
	h = fcn_00470820(0, 0, g_68ce48);
	fcn_00471d80(h, 3);
	d2_SetForm(h, 0);
	t = fcn_00519190(0x10e6, g_772f2c, *(unsigned short*) ((int*)g_772f24), *(unsigned short*) who);
	b0 = fcn_00472250(h, 0, t);
	b1 = fcn_00472250(h, 0, t + 1);
	b2 = fcn_00472250(h, 0, t + 2);
	a1[0x94] = 4;
	a1[0x14] = (*(char*)g_6b5c60);
	w = fcn_004677e0((*(int*) (g_77255c + 0xc) - 300) / 2 - 8, 8, 300, 0, 100, 0x75, 0x42, g_772514);
	fcn_004e6e20(w, g_68bfbc * 75, 1);
	while (fcn_005373e0(fcn_004e16e0, g_68bfb8) != 0) {
		fcn_004cfca0();
		if (g_100f1dc != -1) {
			if (g_67d370 == b0)
				a1[0x94] = 2;
			else if (g_67d370 == b1)
				a1[0x94] = 3;
			else if (g_67d370 == b2)
				a1[0x94] = 4;
			g_774654 = 1;
		}
		if (fcn_004e6e20(w, 0, 0) == 0)
			g_774654 = 1;
	}
	fcn_00471e30(h);
}
