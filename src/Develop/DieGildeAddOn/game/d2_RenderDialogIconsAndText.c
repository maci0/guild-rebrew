


#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_ClearWindowChildren(int, int);
int __cdecl io_AppendText(char*, ...);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl d2_AddElementToWindow(int, int, int, int);

void __cdecl d2_RenderDialogIconsAndText(int a)
{
	int i;
	int x;
	int y;

	d2_ClearWindowChildren(d2_CurrentWindowId, 1);
	io_AppendText(str_CZ_s, a);
	i = 0;
	x = 0x1c;
	y = 0x1d;
	while (i < 3) {
		d2_AddElementToWindow(x, y, gm_RandomMod(6) + 0x75b, d2_CurrentWindowId);
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
