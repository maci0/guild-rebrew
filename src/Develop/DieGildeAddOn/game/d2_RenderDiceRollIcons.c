#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_ClearWindowChildren(int, int);
int __cdecl io_AppendText(char*, ...);
void __cdecl d2_AddElementToWindow(int, int, int, int);
unsigned short __cdecl gm_RandomMod(unsigned short);

/* ADDRESS: GOLDTL 0x005a0ad0 */
/* ADDRESS: GOLDDE 0x00585950 */
void __cdecl d2_RenderDiceRollIcons(int a, unsigned char* p)
{
	int y, x, i;

	d2_ClearWindowChildren(d2_CurrentWindowId, 1);
	io_AppendText(str_CZ_s, a);

	if (*(char*) (*(int*) p + 2) == 6) {
		i = 0;
		x = 0x1c;
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
		d2_AddElementToWindow(x, y, gm_RandomMod(6) + 0x75b, d2_CurrentWindowId);
	}
	else {
		i = 0;
		x = 0x1c;
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
		d2_AddElementToWindow(x, y, gm_RandomMod(6) + 0x75b, d2_CurrentWindowId);
	}
}
