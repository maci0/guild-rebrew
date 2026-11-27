/* Draws one minimap/office slot: resolves the slot record from the global
 * table, picks the frame colour, draws the glyph runs and finally the label. */

#include "Develop/Units/d2.v1/d2_gui.h"
extern int d2_FontHeight;
extern int d2_CurrentElementId;
extern int tp_d2_SelectedControl;
extern int g_7725fc;
extern int d2_ClipBottom;
extern double g_662908;

typedef struct Glyph {
	unsigned short id;
	unsigned short w;
	unsigned short pad4;
	unsigned short h;
} Glyph;

void __cdecl d2_SelectFont(int font);
Glyph* __cdecl d2_GetBankEntry(char* font, int c);
void __cdecl d2_DrawSpriteFromSet(int x, int y, int surf, char* font, int c);
void __cdecl d2_SetClipRect(int a, int b, int c, int d);
void __cdecl d2_DrawWordWrappedText(int x, int y, int w, int h, int surf, char* text, int flags);

/* ADDRESS: GOLDTL 0x00468e40 */
void __cdecl d2_DrawTextButton(int slotIndex, int surface)
{
	char* slot;
	char* font;
	Glyph* leftGlyph;
	Glyph* rightGlyph;
	Glyph* middleGlyph;
	int innerWidth;
	int flags;
	int glyphBase;
	unsigned char color;
	int i;

	glyphBase = 0; color = 8; slot = (char*)&((D2_CONTROL_TL*)g_1015ea0)[slotIndex];
	flags = *(int*) &((D2_CONTROL_TL*)slot)->flags_1d0;
	if ((flags & 2) && tp_d2_SelectedControl == 0) {
		if (!(((char*)&((D2_CONTROL_TL*)g_1015ea0)[d2_CurrentElementId] != slot) && *(int*) &((D2_CONTROL_TL*)slot)->value_038 == 0)
		    && *(int*) &((D2_CONTROL_TL*)slot)->disabled == 0) {
			if (flags & 1) {
				*(int*) &((D2_CONTROL_TL*)slot)->value_03c = 1;
			}
		} else if (flags & 1) {
			*(int*) &((D2_CONTROL_TL*)slot)->value_03c = 0;
		}
	}
	if (!(flags & 2) && *(int*) &((D2_CONTROL_TL*)slot)->value_058 != 0 && *(int*) &((D2_CONTROL_TL*)slot)->disabled == 0) {
		*(int*) &((D2_CONTROL_TL*)slot)->value_03c = *(int*) &((D2_CONTROL_TL*)slot)->value_038;
	}
	if (*(int*) &((D2_CONTROL_TL*)slot)->value_03c != 0) {
		color = 10;
	} else if (*(int*) &((D2_CONTROL_TL*)slot)->value_060 != 0) {
		color = 9;
	}
	d2_SelectFont(*(int*) &((D2_CONTROL_TL*)slot)->font);
	font = *(char**) &((D2_CONTROL_TL*)slot)->data;
	leftGlyph = d2_GetBankEntry(font, 0);
	rightGlyph = d2_GetBankEntry(font, 1);
	middleGlyph = d2_GetBankEntry(font, 2);
	innerWidth = (*(int*) &((D2_CONTROL_TL*)slot)->width - rightGlyph->w) - leftGlyph->w;
	if (*(int*) &((D2_CONTROL_TL*)slot)->value_03c != 0) {
		glyphBase = 3;
	}
	d2_DrawSpriteFromSet(*(int*) &((D2_CONTROL_TL*)slot)->x, *(int*) &((D2_CONTROL_TL*)slot)->y, surface, font, glyphBase);
	d2_DrawSpriteFromSet((*(int*) &((D2_CONTROL_TL*)slot)->width - rightGlyph->w) + *(int*) &((D2_CONTROL_TL*)slot)->x,
	    *(int*) &((D2_CONTROL_TL*)slot)->y, surface, font, glyphBase + 1);

	d2_SetClipRect(*(int*) &((D2_CONTROL_TL*)slot)->x + leftGlyph->w - 1, g_7725fc, *(int*) &((D2_CONTROL_TL*)slot)->x + leftGlyph->w + innerWidth, d2_ClipBottom);
	i = 0;
	if (0.0 < (double) (innerWidth / middleGlyph->w) + 0.5) {
		do {
			d2_DrawSpriteFromSet(middleGlyph->w * i + leftGlyph->w + *(int*) &((D2_CONTROL_TL*)slot)->x,
			    *(int*) &((D2_CONTROL_TL*)slot)->y, surface, font, glyphBase + 2);
			i++;
		} while ((double) i < (double) (innerWidth / middleGlyph->w) + 0.5);
	}
	d2_DrawWordWrappedText(*(int*) &((D2_CONTROL_TL*)slot)->x,
	    ((leftGlyph->h >> 1) - d2_FontHeight / 2) + 1 + *(int*) &((D2_CONTROL_TL*)slot)->y,
	    *(int*) &((D2_CONTROL_TL*)slot)->width, *(int*) &((D2_CONTROL_TL*)slot)->height, surface, slot + 0x8c, color);
}
