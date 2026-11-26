


extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_ClearWindowChildren(int, int);
int __cdecl io_AppendText(char*, ...);
void __cdecl d2_AddElementToWindow(int, int, int, int);

void __cdecl fcn_005a0be0(int a, unsigned char* p)
{
	int i;
	int x;
	int y;

	d2_ClearWindowChildren(d2_CurrentWindowId, 1);
	io_AppendText(g_6a9694, a);
	i = 0;
	x = 0x1c;
	if (*(char*) (*(int*) p + 2) == 6) {
		y = 0x1d;
		while (i < p[4]) {
			d2_AddElementToWindow(x, y, p[0xc + i] + 0x75a, d2_CurrentWindowId);
			i++;
			if (i % 8 == 0) {
				x = 0;
			}
			else {
				x += 0x3a;
			}
			y = i > 7 ? 0x46 : 0x1d;
		}
	}
	else {
		y = 0x1d;
		while (i < p[4]) {
			d2_AddElementToWindow(x, y, 0x761, d2_CurrentWindowId);
			i++;
			if (i % 8 == 0) {
				x = 0;
			}
			else {
				x += 0x3a;
			}
			y = i > 7 ? 0x46 : 0x1d;
		}
	}
}
