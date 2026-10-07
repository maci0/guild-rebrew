// FUNCTION: GOLDTL 0x53e420

extern char g_68116c[];
extern char g_6a4078[];
extern int g_776704;
extern signed char g_6a3440;
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_005373e0(int (__cdecl*)(void), int);
int __cdecl fcn_004693b0(int, ...);
void __cdecl fcn_004695a0(int, int);
void __cdecl fcn_00469630(int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_0053e420(void)
{
	int a1;
	int a2;
	int a3;
	int a4;
	int a5;
	int a6;
	int result;
	int h;
	int s;
	int a0;
	int list;

	result = 0;
	h = fcn_00470820(0, 0, g_68116c);
	fcn_00471b60(h);
	fcn_004727a0(h, 0);
	s = fcn_00519190(0x1ac5, 0x1ac7, 0x1ac8, 0x1ac9, 0x1aca, 0x1acb, 0x1acc);
	a0 = fcn_00472250(h, 0, s);
	a1 = fcn_00472250(h, 0, s + 1);
	a2 = fcn_00472250(h, 0, s + 2);
	a3 = fcn_00472250(h, 0, s + 3);
	a4 = fcn_00472250(h, 0, s + 4);
	a5 = fcn_00472250(h, 0, s + 5);
	a6 = fcn_00472250(h, 0, fcn_00519190((int) g_6a4078, 0x1acd));
	if (g_776704 <= -1) {
		g_776704 = -1;
	}
	list = fcn_004693b0(7, a0, a1, a2, a3, a4, a5, a6);
	if (g_776704 != -1) {
		fcn_004695a0(list, g_776704 + 1);
	} else {
		fcn_004695a0(list, 0);
	}
	while (fcn_005373e0(fcn_0053e420, 0xc6) != 0) {
		fcn_00469630(list);
		if (g_14ce8e0 != 0 || g_14cf950 == 1) {
			g_774654 = 1;
		}
		if (g_100f1dc == 2) {
			if (g_67d370 == a0) {
				(*(char*)&g_6a3440) = -1;
			} else if (g_67d370 == a1) {
				(*(char*)&g_6a3440) = 0;
			} else if (g_67d370 == a2) {
				(*(char*)&g_6a3440) = 1;
			} else if (g_67d370 == a3) {
				(*(char*)&g_6a3440) = 2;
			} else if (g_67d370 == a4) {
				(*(char*)&g_6a3440) = 3;
			} else if (g_67d370 == a5) {
				(*(char*)&g_6a3440) = 4;
			} else if (g_67d370 == a6) {
				(*(char*)&g_6a3440) = 5;
			}
			g_776704 = (*(char*)&g_6a3440);
			if (g_776704 != -1) {
				fcn_004695a0(list, g_776704 + 1);
			} else {
				fcn_004695a0(list, 0);
			}
			result = 1;
			g_774654 = 1;
		} else if (g_100f1dc == 1) {
			g_774654 = 1;
		}
	}
	fcn_00469510(list);
	fcn_00471e30(h);
	return result;
}
