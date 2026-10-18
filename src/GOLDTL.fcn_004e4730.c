extern int g_772f3c;
extern int g_6b8300;
extern char g_77666a;
extern int* g_772f40;
extern int g_77250c;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern int g_772f4c;
extern int g_6791c8;
extern int g_67a370;
extern int g_6791d0;
extern int g_68bfc4;
extern unsigned char* g_772f50;
extern int g_1040490;
extern int g_1040494;
extern char g_67d67c[];

typedef void(__cdecl* hook_4e4730)(char*, int, char*, int);

int __cdecl fcn_00413160(void);
void __cdecl fcn_004432d0(int, int);
int __cdecl fcn_0064d41a(char*, char*, ...);
#include "client_scene_loader.h"
void __cdecl fcn_004428d0(char*, int, int);
void __cdecl fcn_00476970(int);
int __cdecl fcn_00500e20(int*);
void __cdecl fcn_0052a7d0(void);
#include "Develop/Units/d3/d3_d3d.h"
void __cdecl fcn_00473150(int);
void __cdecl fcn_004730c0(int, int, int, int, char*, int, int);

/* ADDRESS: GOLDTL 0x004e4730 */

void __cdecl fcn_004e4730(char* a1)
{
	char buf[0x80];
	char* ui;
	int n;

	if (g_772f3c != 0)
		return;
	{
		int s;

		s = fcn_00413160();
		fcn_004432d0(s, 0);
		fcn_0064d41a(buf, "scenes/*%s", a1);
		fcn_00448360(buf, 0, 0);
		fcn_004432d0(0, 1);
		fcn_004432d0(s, 0);
	}
	if (((char*)g_6b8300) != 0) {
		if (g_77666a == 0) {
			n = 2;
			((char*)g_6b8300)[0x8036] = (((char*)g_6b8300)[0x8036] & 0xeb) | 8;
		} else {
			n = 1;
			((char*)g_6b8300)[0x8036] = (((char*)g_6b8300)[0x8036] & 0xe7) | 4;
		}
		fcn_004428d0(((char*)g_6b8300), n >> 1, 1);
	}
	if ((((char*)g_772f40)[0x26] & 0x20) != 0)
		fcn_00476970(g_77250c);
	if (fcn_00500e20(&(*(int*)&g_7f4c00)) == 3)
		fcn_0052a7d0();
	g_6791c8 = -2;
	g_772f4c++;
	if (((char*)g_67a370) != 0) {
		ui = *(char**) (((char*)g_67a370) + 0x3c8);
		if (ui != 0 && *(hook_4e4730*) (ui + 0x210) != 0)
			(*(hook_4e4730*) (ui + 0x210))(((char*)g_67a370), 4, ui + 0x214, 0);
	}
	g_68bfc4 = g_6791d0;
	fcn_00443230(1);
	if ((*(int*)&g_772f50) != 0) {
		fcn_00473150((*(int*)&g_772f50));
		(*(int*)&g_772f50) = 0;
	}
	fcn_004730c0(0, 0, g_1040494, g_1040490, g_67d67c, 0x5a, 0xa);
}
