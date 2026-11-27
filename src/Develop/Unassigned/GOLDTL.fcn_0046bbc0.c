#include <string.h>

extern char* g_772524;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_1040494;
extern int g_67d384;
extern int g_772548;
extern int g_772544;
extern char s_67d474[];

int __cdecl d2_FindResourceByName(char* name);
char* __cdecl d2_GetResourceData(int id);
char* __cdecl d2_GetBankEntry(char* font, int c);
void __cdecl d2_DrawHighlightSprite(int x, int y, int surf, char* font, int c);
void __cdecl d2_DrawDimmedSpriteFrame(int x, int y, int surf, char* font, int c);
void __cdecl d2_DrawSpriteFromSet(int x, int y, int surf, char* font, int c);

/* ADDRESS: GOLDTL 0x0046bbc0 */
void __cdecl d2_DrawDefaultFontText(int x, int y, int surf, char* text, unsigned char flags)
{
	int x0;
	int i;
	unsigned char c;
	char* g;

	x0 = x;
	if (g_772524 == 0) {
		g_772524 = d2_GetResourceData(d2_FindResourceByName(s_67d474));
	}
	d2_FontHeight = *(unsigned short*) (g_772524 + 8);
	for (i = 0; i < (int) strlen(text); i++) {
		c = text[i];
		g = d2_GetBankEntry(g_772524, c);
		x -= *(unsigned short*) (g + 0x11);
		if (c != '~') {
			if (c != ' ') {
				if (flags & 2) {
					d2_DrawHighlightSprite(x, y, surf, g_772524, c);
				} else if (flags & 1) {
					d2_DrawDimmedSpriteFrame(x, y, surf, g_772524, c);
				} else {
					d2_DrawSpriteFromSet(x, y, surf, g_772524, c);
				}
				x += *(unsigned short*) (g + 0x15) + g_67d384;
			} else {
				x += g_67d380;
			}
		}
		if (x >= g_1040494) {
			break;
		}
	}
	g_772548 = d2_FontHeight;
	g_772544 = x - x0;
}
