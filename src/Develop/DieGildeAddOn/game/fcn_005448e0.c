#include <stdio.h>

int __cdecl fcn_0041e620(void);
void __cdecl fcn_0041e650(void);
void __cdecl fcn_004c2d90(float, int);
unsigned char* __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
void __cdecl fcn_005373e0(int, int);
void __cdecl fcn_005356e0(void);
void __cdecl fcn_004124b0(void);
void __cdecl fcn_004117c0(int);
void __cdecl fcn_004117f0(int);
int __cdecl fcn_0041e680(char*, void*, void*, int, int, int, int, int);
int __cdecl fcn_0041f350(int);
void __cdecl fcn_00473150(unsigned char*);

#include "fcn_005448e0_gconf.h"
__declspec(dllimport) void __stdcall Sleep(unsigned long);
extern void (__stdcall* g_662264)(int);

/* ADDRESS: GOLDTL 0x005448e0 */
void __cdecl fcn_005448e0(void)
{
	char buf[0x104];
	unsigned char* h;
	char* b;
	int saved;
	int t;

	if (*(int*) 0x77492c == 0) {
		fcn_0041e620();
	}
	fcn_004c2d90(0.0f, 0x3e8);
	h = fcn_004730c0(0, 0, *(int*) 0x1040494, *(int*) 0x1040490, (char*) 0x67d67c, 0x5a, 1);
	for (;;) {
		if ((*h & 4) && !(*(float*) 0x678158 >= *(float*) 0x6628a8)) {
			break;
		}
		fcn_005373e0(0, *(int*) 0x7e46ac);
	}
	b = buf;
	saved = *(unsigned char*) 0x772d10;
	*(unsigned char*) 0x772d10 = 0;
	sprintf(b, (char*) 0x6a4538, (char*) 0x6a3658);
	*(int*) 0x6b5c90 = 1;
	fcn_004124b0();
	*(int*) 0x6b5c90 = 0;
	fcn_004117c0(0);
	fcn_004117f0(0);
	fcn_005356e0();
	Sleep(0x1f4);
	*(int*) 0x7747d4 = fcn_0041e680(b, 0, *(void**) 0x7e1f80, 0, 0, 0, 0, 0x8a);
	Sleep(0xc8);
	fcn_0041f350(*(int*) 0x7747d4);
	fcn_00473150(h);
	fcn_005356e0();
	g_662264(*(int*) 0x774940);
	fcn_004117c0(1);
	fcn_004117f0(1);
	*(int*) 0x6b5c90 = 1;
	fcn_004124b0();
	t = *(unsigned char*) 0x7766a2;
	*(int*) 0x6b5c90 = 0;
	*(unsigned char*) 0x14cf950 = 0;
	fcn_004c2d90((float) t * *(float*) 0x665e44, 0x3e8);
	*(unsigned char*) 0x772d10 = (unsigned char) saved;
	if (*(int*) 0x77492c == 0) {
		fcn_0041e650();
	}
}
