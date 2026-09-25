// FUNCTION: GOLD 0x0057e3a0
// SIZE: 336
// FUNCTION: GOLDTL 0x586a80
// SIZE: 336

extern char g_6a93e0[];
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;

char* __cdecl fcn_004ec7d0(char*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_005373e0(int (__cdecl*)(char*), int);
void __cdecl fcn_004ed190(char*);
void __cdecl fcn_004eec10(char*);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_00586a80(char* a)
{
	int result;
	int h;
	int s;
	int b1;
	int b2;
	char* p;

	result = 0;
	if (fcn_004ec7d0(a) == 0) {
		return 0;
	}
	h = fcn_00470820(0, 0, g_6a93e0);
	fcn_00473a90(0, 0);
	fcn_00471b60(h);
	fcn_004727a0(h, 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(h, 1);
	fcn_00519190(0x403d, 0x182);
	fcn_004727a0(h, 2);
	s = fcn_00519190(0x403e);
	b1 = fcn_00472250(h, 2, s);
	b2 = fcn_00472250(h, 2, s + 1);
	g_100f1dc = -1;
	do {
		p = fcn_004ec7d0(a);
		if (p == 0) {
			g_774654 = 1;
			fcn_005373e0(fcn_00586a80, 0x20007);
			fcn_00471e30(h);
			return 0;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == b1) {
				result = 1;
				fcn_004ed190(a);
				fcn_004eec10(p);
				g_774654 = 1;
			} else if (g_67d370 == b2) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0(fcn_00586a80, 0x677c7) != 0);
	fcn_00471e30(h);
	return result;
}
