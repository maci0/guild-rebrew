// FUNCTION: GOLD 0x4ad0a0
// FUNCTION: GOLDTL 0x4ad1c0

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern int g_7728cc;
extern int g_7728c4;

int __cdecl fcn_004e8a80(int, int*);
char* __cdecl fcn_004ad130(int, int*);
char* __cdecl gm_RandomMod(int);
void __cdecl fcn_004c4fc0(int, int, int, char*, int, int, int, int);

void __cdecl fcn_004ad1c0(void)
{
	int kind;
	int a[6];
	int b[6];
	int limit;
	char* p;

	limit = (*(int*)&g_7f4c00) + 0x578;
	if (fcn_004e8a80(0x26, a) == 0)
		return;
	if (fcn_004e8a80(0x27, b) == 0)
		return;
	if (a[1] == -1 && g_7728cc != -1) {
		p = fcn_004ad130(g_7728cc, &kind);
		if (p != 0 && *(int*) (p + 4) <= limit)
			fcn_004c4fc0(0x15, g_7728cc, -1, gm_RandomMod(8) + 0x19, -1, 0, 0, 0);
	}
	if (b[1] == -1 && g_7728c4 != -1) {
		p = fcn_004ad130(g_7728c4, &kind);
		if (p != 0 && *(int*) (p + 4) <= limit)
			fcn_004c4fc0(0x16, g_7728c4, -1, gm_RandomMod(8) + 0x19, -1, 0, 0, 0);
	}
}
