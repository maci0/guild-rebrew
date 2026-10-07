extern unsigned int g_7e1f60;
extern signed char g_6a3440;
extern unsigned char g_6a375c;
extern int g_100f1dc;
extern int g_774654;
extern int g_14ce8e0;
extern int g_7e242c;

// FUNCTION: GOLDTL 0x53cf30

__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
int __cdecl fcn_004b3db0(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_004b5530(int, int);

int __cdecl fcn_0053cf30(void)
{
	int r;
	int h;

	g_7e1f60 = timeGetTime();
	r = fcn_004b3db0(g_6a3440);
	if (g_6a375c > 1) {
		h = fcn_00470820(0, 0, "Menu\\GET_MISSION_WARNING");
		fcn_00471b60(h);
		fcn_004727a0(h, 0);
		fcn_00519190(0x1adc);
		fcn_00519190(0x1add);
		while (fcn_005373e0((void*) fcn_0053cf30, 0xc6) != 0) {
			if (g_100f1dc == 2) {
				g_774654 = 1;
			} else if (g_100f1dc == 1) {
				r = 0;
				g_774654 = 1;
			}
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
				r = 0;
			}
		}
		if (h != -1) {
			fcn_00471e30(h);
		}
	}
	if (r != 0) {
		fcn_004b5530(r, 0xc6);
	}
	g_7e242c = r;
	return r;
}
