

extern int* g_665f08;
extern char g_6a8364[];
extern int g_772514;
#include "client_types.h"
extern s_1015f4c g_1015f4c[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471d80(int, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);

void __cdecl fcn_00580560(void)
{
	g_665f08[26] = fcn_00470820(0, 0, g_6a8364);
	fcn_00471d80(g_665f08[26], 3);
	fcn_004727a0(g_665f08[26], 0);
	g_665f08[27] = fcn_004677e0(((int*)g_1015f4c)[g_772514 * 243] / 2 - 200, 5, 0x190, 0, 0x190, 0x75,
	    0x42, g_772514);
}
