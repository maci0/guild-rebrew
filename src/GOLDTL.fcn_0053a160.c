// FUNCTION: GOLD 0x00533620
// FUNCTION: GOLDTL 0x53a160

extern char g_6a3a80[];
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;
extern unsigned char g_7747b0;
extern signed char g_6a3440;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_005373e0(int (__cdecl*)(void), int);
int __cdecl fcn_004693b0(int, int, int, int);
void __cdecl fcn_00469630(int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00539490(void);
int __cdecl fcn_00539930(int);
int __cdecl fcn_0053a020(void);

int __cdecl fcn_0053a160(void)
{
	int list;
	int b;
	int c;
	int result;
	int h;
	int a;

	result = 0;
	h = fcn_00470820(0, 0, g_6a3a80);
	fcn_00471b60(h);
	fcn_004727a0(h, 0);
	fcn_00519190(0x1ca5);
	a = fcn_00472250(h, 0, fcn_00519190(0x1ca6));
	b = fcn_00472250(h, 0, fcn_00519190(0x1ca7));
	c = fcn_00472250(h, 0, fcn_00519190(0x1ca8));
	list = fcn_004693b0(3, a, b, c);
	(*(unsigned char*)&g_6a3440) = 0xfe;
	while (fcn_005373e0(fcn_0053a160, 0x24087) != 0) {
		fcn_00469630(list);
		if (g_14ce8e0 != 0 || g_14cf950 == 1) {
			g_774654 = 1;
			result = 0;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == a) {
				(*(int*)&g_7747b0) = 5;
				fcn_00471af0(h, 0);
				if (fcn_00539490() != 0) {
					g_774654 = 1;
					result = 1;
				}
				fcn_00471af0(h, 1);
			} else if (g_67d370 == b) {
				(*(int*)&g_7747b0) = 5;
				fcn_00471af0(h, 0);
				if (fcn_00539930(0) != 0) {
					g_774654 = 1;
					result = 1;
				}
				fcn_00471af0(h, 1);
			} else if (g_67d370 == c) {
				(*(int*)&g_7747b0) = 4;
				fcn_00471af0(h, 0);
				if (fcn_0053a020() != 0) {
					g_774654 = 1;
					result = 1;
				}
				fcn_00471af0(h, 1);
			}
		}
	}
	fcn_00469510(list);
	fcn_00471e30(h);
	return result;
}
