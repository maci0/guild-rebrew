#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* g_77253c;

void __cdecl d2_SelectFont(int font);
void __cdecl d2_FlushQueuedQuads(int a, int b, int c);
void __cdecl d2_DrawTexturedQuad(int x, int y, int w, int h, int color, float alpha);
void __cdecl d2_DrawWordWrappedText(int x, int y, int w, int h, int surf, char* text, int flags);

/* ADDRESS: GOLDTL 0x00469fd0 */
void __cdecl d2_DrawElementTooltip(char* e)
{
	char* name;
	unsigned char fl;
	int x;
	int y;

	name = e + 0xcc;
	if (*name != 0 && !(*(int*) (e + 0x1d0) & 0x40)) {
		fl = 8;
		if (*(int*) (e + 0x60) != 0) {
			fl = 9;
		}
		if (*(int*) (e + 0x70) != 0) {
			fl |= 0x10;
		}
		if (*(int*) (e + 0x54) != 0) {
			fl |= 4;
		}
		if (*(int*) (e + 0x1d0) & 8) {
			fl |= 0x20;
		}
		x = *(int*) (e + 0x10);
		if (*(int*) (e + 0x1dc) != -1) {
			x += *(int*) (e + 0x1dc);
		}
		y = *(int*) (e + 0x14);
		if (*(int*) (e + 0x1e0) != -1) {
			y += *(int*) (e + 0x1e0);
		} else {
			y -= 0x10;
		}
		d2_SelectFont(*(int*) (e + 0x1cc) != 0 ? *(int*) (e + 0x1cc) : d2_DefaultFont + 1);
		if (*(int*) (e + 0x1d0) & 0x20) {
			d2_FlushQueuedQuads(0, 0, 0);
			d2_DrawTexturedQuad(*(int*) (e + 0x10), *(int*) (e + 0x14), *(int*) (e + 0x1d4), *(int*) (e + 0x1d8), *(int*) (g_77253c + 0x50), 0.5f);
		}
		if (*(int*) (e + 0x1d0) & 4) {
			d2_DrawWordWrappedText(*(int*) (e + 0x10) - 0x30, *(int*) (e + 0x14) + *(int*) (e + 0x1c), *(int*) (e + 0x1d4) + 0x60, *(int*) (e + 0x1c), g_77250c, name, fl);
		} else {
			d2_DrawWordWrappedText(x - 0x30, y, *(int*) (e + 0x1d4) + 0x60, *(int*) (e + 0x1c), g_77250c, name, fl);
		}
	}
}
