

extern int g_6ad580;
extern int g_6ad568;
extern int g_772514;
#include "client_types.h"
extern s_1015f4c g_1015f4c[];
extern int g_776644;
extern int g_776648;
extern unsigned char g_773d75;

void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
int __cdecl fcn_0050b710(int, char);
void __cdecl fcn_00472380(int, int, int, int, int);
void __cdecl fcn_00472170(int, int);

void __cdecl fcn_005e6d10(int show)
{
	if (show != 0) {
		if (g_6ad580 == -1) {
			fcn_004727a0(g_6ad568, 5);
			g_6ad580 = fcn_004677e0(0, 0, ((int*)g_1015f4c)[g_772514 * 243] - 0xb4, 0, 100, 0x7b, 2,
			    g_772514);
			fcn_00472380(g_6ad580, fcn_0050b710(g_776644, (*(char*)&g_773d75)), fcn_0050b710(g_776648, (*(char*)&g_773d75)),
			    fcn_0050b710(g_776644, (*(char*)&g_773d75)), 1);
		}
		else {
			fcn_00472170(g_6ad580, show);
		}
	}
}
