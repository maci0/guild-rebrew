// FUNCTION: GOLD 0x004f9e30
// FUNCTION: GOLDTL 0x004fc490

extern char g_696470[];
extern char g_69645c[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_99f6a0[];
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_00470820(int a, int b, char* s);
void __cdecl fcn_00471b60(int h);
void __cdecl fcn_00473a90(int a, int b);
void __cdecl fcn_004727a0(int h, int b);
void __cdecl fcn_00519190(char* fmt, ...);
int __cdecl fcn_005373e0(void* fn, int y);
void __cdecl fcn_00471e30(int h);

void __cdecl fcn_004fc490(void)
{
	int h;
	int i;

	h = fcn_00470820(0, 0, g_696470);
	fcn_00471b60(h);
	fcn_00473a90(0, 0);
	fcn_004727a0(h, 0);
	for (i = 0; i < 0x11; i++) {
		fcn_00519190(g_69645c, (*(int*)&g_7f4c00) + i - 0x10, ((int*)g_99f6a0)[i]);
	}
	do {
		if (g_14ce8e0) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_004fc490, 0x677c7));
	fcn_00471e30(h);
}
