#include <stdlib.h>

typedef struct
{
	unsigned short f0;
	unsigned short w;
	unsigned short f4;
	unsigned short h;
} D2_POPUP_GLYPH;
// SIZE 0x8

typedef struct
{
	int i[0x2f4 / 4];
} D2_POPUP_ELEMENT;
// SIZE 0x2f4

extern char* d2_Controls;
extern int g_67d394;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_ScreenHeight;
extern int g_1040494;
extern short io_ActiveCursorY;
extern int g_102d028;
extern int g_102d02c;

char* __cdecl d2_GetResourceData(int id);
D2_POPUP_GLYPH* __cdecl d2_GetBankEntry(char* font, int c);
void __cdecl d2_SetClipRect(int a, int b, int c, int d);
void __cdecl d2_DrawSpriteFromSet(int x, int y, int surf, char* font, int c);
void __cdecl d2_SelectFont(int font);
void __cdecl d2_DrawWordWrappedText(int x, int y, int w, int h, int surf, char* text, int flags);

/* ADDRESS: GOLDTL 0x004663e0 */
void __cdecl d2_DrawFieldSliderPopup(char* f, int surf)
{
	D2_POPUP_ELEMENT* e;
	char* font;
	D2_POPUP_GLYPH* g0;
	D2_POPUP_GLYPH* g1;
	D2_POPUP_GLYPH* g2;
	D2_POPUP_GLYPH* g3;
	int x;
	int y;
	char buf[24];

	e = &((D2_POPUP_ELEMENT*)d2_Controls)[*(int*) (f + 0x134)];
	font = d2_GetResourceData(g_67d394);
	g0 = d2_GetBankEntry(font, 0);
	g1 = d2_GetBankEntry(font, 1);
	g2 = d2_GetBankEntry(font, 2);
	g3 = d2_GetBankEntry(font, 3);
	x = e->i[0x10 / 4] - 0x20;
	y = *(int*) (f + 0x20) - g0->h - 0x64;
	d2_SetClipRect(0, 0, g_1040494, d2_ScreenHeight);
	d2_DrawSpriteFromSet(x, y, surf, font, 0);
	d2_DrawSpriteFromSet(x, g0->h + y + 0x64, surf, font, 1);
	d2_DrawSpriteFromSet(x, g0->h + y, surf, font, 2);
	y = io_ActiveCursorY - g3->h / 2;
	x += g0->w / 2 - g3->w / 2;
	d2_DrawSpriteFromSet(x, y, surf, font, 3);
	g_102d028 = x;
	g_102d02c = y;
	if (*(int*) (f + 0x12c) < 100000 && *(int*) (f + 0x12c) > -100000) {
		d2_SelectFont(d2_DefaultFont + 1);
		_itoa(*(int*) (f + 0x12c), buf, 10);
		d2_DrawWordWrappedText(x, y, g3->w, g3->h, surf, buf, 8);
	}
}
