extern char g_68116c[];
extern char g_681164[];
extern unsigned char g_6a375c;
extern signed char g_6a3440;
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_100f1dc;
extern int g_774654;
extern int g_67d370;
extern int g_7e46ac;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_004693b0(int, ...);
void __cdecl fcn_004695a0(int, int);
void __cdecl fcn_00469470(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00469630(int);
int __cdecl fcn_004b3fe0(int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);

// FUNCTION: GOLDTL 0x4b41b0
// SIZE: 576

int __cdecl fcn_004b41b0(void)
{
	int b1;
	int b2;
	int b3;
	int b4;
	int b6;
	int b5;
	int result;
	int h;
	int t;
	int b0;
	int lst;
	int x;

	result = 0;
	b6 = -1;
	h = fcn_00470820(0, 0, g_68116c);
	fcn_00471b60(h);
	fcn_004727a0(h, 0);
	t = fcn_00519190(0x1ac5, 0x1ac7, 0x1ac8, 0x1ac9, 0x1aca, 0x1acb, 0x1acc);
	b0 = fcn_00472250(h, 0, t);
	b1 = fcn_00472250(h, 0, t + 1);
	b2 = fcn_00472250(h, 0, t + 2);
	b3 = fcn_00472250(h, 0, t + 3);
	b4 = fcn_00472250(h, 0, t + 4);
	b5 = fcn_00472250(h, 0, t + 5);
	if (g_6a375c > 1)
		b6 = fcn_00472250(h, 0, fcn_00519190((int) g_681164, 2, 0x1acd));
	lst = fcn_004693b0(6, b0, b1, b2, b3, b4, b5);
	fcn_004695a0(lst, 0);
	fcn_00469470(lst, fcn_00472250(h, 0, fcn_00519190(0x7e)));
	while (fcn_005373e0(fcn_004b41b0, g_7e46ac) != 0) {
		fcn_00469630(lst);
		if (g_14ce8e0 != 0 || g_14cf950 == 1 || g_100f1dc == 1) {
			result = 0xff;
			g_774654 = 1;
		}
		if (g_100f1dc == 2) {
			x = g_67d370;
			if (x == b0) {
				g_6a3440 = -1;
				result = 0;
			} else {
				if (x == b1)
					g_6a3440 = 0;
				else if (x == b2)
					g_6a3440 = 1;
				else if (x == b3)
					g_6a3440 = 2;
				else if (x == b4)
					g_6a3440 = 3;
				else if (x == b5)
					g_6a3440 = 4;
				else if (x == b6)
					g_6a3440 = 5;
				fcn_004695a0(lst, 0);
				result = fcn_004b3fe0(g_6a3440);
			}
			if (result != 0xff)
				g_774654 = 1;
		}
	}
	fcn_00469510(lst);
	fcn_00471e30(h);
	return result;
}
