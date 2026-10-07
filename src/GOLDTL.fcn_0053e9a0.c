// FUNCTION: GOLDTL 0x53e9a0

extern char g_6a4120[];
extern unsigned char g_77670a;
extern int g_7747b4;
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_005373e0(int (__cdecl*)(void), int);
int __cdecl fcn_004693b0(int, ...);
void __cdecl fcn_004695a0(int, int);
void __cdecl fcn_00469630(int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_0053e9a0(void)
{
	int a1;
	int a2;
	int a3;
	int a4;
	int result;
	int h;
	int s;
	int a0;
	int list;

	result = 0;
	h = fcn_00470820(0, 0, g_6a4120);
	fcn_00471b60(h);
	g_7747b4 = g_77670a;
	s = fcn_00519190(0x1abf);
	a0 = fcn_00472250(h, 0, s);
	a1 = fcn_00472250(h, 0, s + 1);
	a2 = fcn_00472250(h, 0, s + 2);
	a3 = fcn_00472250(h, 0, s + 3);
	a4 = fcn_00472250(h, 0, s + 4);
	list = fcn_004693b0(6, a0, a1, a2, a3, a4, fcn_00472250(h, 0, s + 5));
	fcn_004695a0(list, g_7747b4);
	while (fcn_005373e0(fcn_0053e9a0, 0xc6) != 0) {
		fcn_00469630(list);
		if (g_14ce8e0 != 0 || g_14cf950 == 1) {
			result = 0;
			g_774654 = 1;
		}
		if (g_100f1dc == 2 || g_14cf950 == 0x1c) {
			if (g_67d370 == a0) {
				g_7747b4 = 0;
			} else if (g_67d370 == a1) {
				g_7747b4 = 1;
			} else if (g_67d370 == a2) {
				g_7747b4 = 2;
			} else if (g_67d370 == a3) {
				g_7747b4 = 3;
			} else if (g_67d370 == a4) {
				g_7747b4 = 4;
			}
			result = 1;
			g_774654 = 1;
		} else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	}
	g_77670a = (unsigned char) g_7747b4;
	fcn_00469510(list);
	fcn_00471e30(h);
	return result;
}
