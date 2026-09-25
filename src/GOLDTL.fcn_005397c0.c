// FUNCTION: GOLD 0x532ca0
// SIZE: 354
// FUNCTION: GOLDTL 0x5397c0
// SIZE: 354

#include <windows.h>
#include <string.h>

extern char g_7e22c0[];
extern char g_7e2000[];
extern char g_6a3a34[];
extern int g_14ce8e0;
extern char g_14cf950;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, char*);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_005373e0(int (__cdecl*)(void), int);
char* __cdecl fcn_00471f80(int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_005397c0(void)
{
	int ok;
	char buf[0x104];
	int result;
	int h;
	int e;

	result = 0;
	GetPrivateProfileStringA("Network", "Host", "127.0.0.1", buf, 0x104, g_7e22c0);
	h = fcn_00470820(0, 0, g_6a3a34);
	fcn_00471b60(h);
	fcn_004727a0(h, 2);
	fcn_00519190(0x1cae);
	fcn_004727a0(h, 0);
	e = fcn_00472250(h, 0, 0);
	fcn_00472380(e, buf);
	fcn_004727a0(h, 1);
	ok = fcn_00472250(h, 1, fcn_00519190(0x1cb0));
	while (fcn_005373e0(fcn_005397c0, 0x24087) != 0) {
		if (g_14ce8e0 != 0 || g_14cf950 == 1) {
			g_774654 = 1;
		}
		if ((g_100f1dc != -1 || g_14cf950 == 0x1c) && (g_67d370 == ok || g_14cf950 == 0x1c)) {
			result = 1;
			strcpy(buf, fcn_00471f80(e));
			strcpy(g_7e2000, buf);
			WritePrivateProfileStringA("Network", "Host", buf, g_7e22c0);
			g_774654 = 1;
		}
	}
	fcn_00471e30(h);
	return result;
}
