extern char g_68ce48[];
extern unsigned short* g_772f24;
extern char g_6b5c60[];
extern int g_772514;
extern char* g_77255c;
extern int g_68bfbc;
extern int g_68bfb8;
extern int g_774654;
extern int g_100f1dc;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl fcn_004e6e20(int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

// FUNCTION: GOLDTL 0x4e15c0

void __cdecl fcn_004e15c0(char* a1)
{
	int h;
	int w;

	h = fcn_00470820(0, 0, g_68ce48);
	fcn_00471d80(h, 3);
	fcn_004727a0(h, 0);
	fcn_00519190(0x10de, *g_772f24);
	a1[0x94] = 0;
	a1[0x14] = (*(char*)g_6b5c60);
	w = fcn_004677e0((*(int*) (g_77255c + 0xc) - 300) / 2 - 8, 8, 300, 0, 100, 0x75, 0x42, g_772514);
	fcn_004e6e20(w, g_68bfbc * 75, 1);
	while (fcn_005373e0(fcn_004e15c0, g_68bfb8) != 0) {
		if (fcn_004e6e20(w, 0, 0) == 0)
			g_774654 = 1;
		if (g_100f1dc == 2) {
			a1[0x94] = 1;
			g_774654 = 1;
		} else if (g_100f1dc == 1) {
			a1[0x94] = 0;
			g_774654 = 1;
		}
	}
	fcn_00471e30(h);
}
