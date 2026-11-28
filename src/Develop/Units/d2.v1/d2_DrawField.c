#include <stdio.h>
#include <string.h>

#include "Develop/client_types.h"
#include "Develop/Units/d2.v1/d2_gui.h"

typedef struct
{
	int i[0x2f4 / 4];
} fcn_00466550_Ent;

typedef struct
{
	unsigned short id;
	unsigned short w;
	unsigned short h;
	unsigned short pad6;
} fcn_00466550_Glyph;

extern UI_FIELD g_102d140[];
extern char* d2_Controls;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67d374;
extern int g_67d39c;
extern int g_7725a0;
extern int g_7725a4;
extern char* d2_FileObjTable;
extern int d2_ScreenSurface;
extern int d2_ResourceOffset;
extern int tp_d2_SelectedControl;
extern float flt_0_0;

int __cdecl d2_MeasureTextWidth(char* s, int font);
void __cdecl d2_DrawDefaultFontText(int x, int y, int surf, char* text, int flags);
void __cdecl d2_DrawWordWrappedText(int x, int y, int w, int h, int surf, char* text, int flags);
void __cdecl d2_SelectFont(int font);
void __cdecl d2_SetClipRect(int a, int b, int c, int d);
fcn_00466550_Glyph* __cdecl d2_GetBankEntry(char* font, int c);
void __cdecl d2_DrawSpriteFromSet(int x, int y, int surf, char* font, int c);
void __cdecl d2_DrawDimmedSpriteFrame(int x, int y, int surf, char* font, int c);

/* ADDRESS: GOLDTL 0x00466550 */
/* ADDRESS: GOLDDE 0x0045a0d0 */
void __cdecl d2_DrawField(int idx, int surf)
{
	UI_FIELD* f;
	fcn_00466550_Ent* e;
	fcn_00466550_Glyph* g0;
	fcn_00466550_Glyph* g1;
	fcn_00466550_Glyph* g2;
	char* font;
	unsigned int flags;
	int w0;
	int v;
	int n;
	int i;
	int y;
	int width;
	char buf[32];
	char buf2[32];
	char buf3[40];

	f = &g_102d140[idx];
	d2_SelectFont(f->font);
	flags = f->flags;
	if (flags & 1) {
		if (f->def == -1 && !(flags & 0x200)) {
			f->w = d2_MeasureTextWidth(((char*) f + 0x2c), f->font);
		} else {
			f->w = ((D2_CONTROL_TL*) (d2_Controls))[f->ent].width;
		}
		if (f->w < 0x30) {
			f->w = 0x30;
		}
		v = *(int*) ((char*) f + 0x15c);
		if (v >= 1) {
			if (f->w < v) {
				v = f->w;
			}
			f->w = v;
		}
		d2_SetClipRect(0, 0, g_1040494, d2_ScreenHeight);
		((D2_CONTROL_TL*) (d2_Controls))[f->ent].width = f->w;
		if (((D2_CONTROL_TL*) (d2_Controls))[f->ent].value_03c != 0 || d2_CurrentElementId == f->ent) {
			d2_DrawDefaultFontText(f->x, f->y, surf, ((char*) f + 0x2c), 2);
		} else {
			d2_DrawDefaultFontText(f->x, f->y, surf, ((char*) f + 0x2c), 0);
		}
	} else if (flags & 2) {
		v = f->max;
		for (n = 0; n < 10; n++) {
			if (v <= 0) {
				break;
			}
			v /= 10;
		}
		f->digits = n;
		if (flags & 4) {
			v = f->f140 * f->f12c;
			if (v < 1000) {
				sprintf(buf, (char*) 0x67d464, v);
			} else if (v < 1000000) {
				sprintf(buf, (char*) 0x67d45c, (double) v * *(double*) 0x662a20);
			} else {
				sprintf(buf, (char*) 0x67d454, (double) v * *(double*) 0x664060);
			}
		} else if (flags & 8) {
			sprintf(buf2, (char*) 0x67d448, f->digits);
			sprintf(buf, buf2, f->f140 * f->f12c);
		} else {
			sprintf(buf, (char*) 0x67d444, f->f12c);
		}
		e = (fcn_00466550_Ent*) &((D2_CONTROL_TL*) d2_Controls)[f->ent];
		if (f->def == -1) {
			font = (char*) d2_GetResourceData(g_67d39c);
			g0 = d2_GetBankEntry(font, 0);
			g1 = d2_GetBankEntry(font, 1);
			g2 = d2_GetBankEntry(font, 2);
			((D2_CONTROL_TL*) e)->width = f->w = g0->w + f->digits * 14 + g2->w;
			((D2_CONTROL_TL*) e)->x = f->x;
			v = f->w - g0->w - g1->w;
			d2_DrawSpriteFromSet(f->x, ((D2_CONTROL_TL*) e)->y, surf, font, 0);
			d2_DrawSpriteFromSet(f->x + f->w - g1->w, ((D2_CONTROL_TL*) e)->y, surf, font, 1);
			w0 = ((D2_CONTROL_TL*) e)->x + g0->w;
			d2_SetClipRect(w0 - 1, g_7725fc, w0 + v, d2_ClipBottom);
			i = 0;
			if (0.0 < (double) (v / g2->w) + 0.5) {
				do {
					d2_DrawSpriteFromSet(g2->w * i + g0->w + ((D2_CONTROL_TL*) e)->x,
					    ((D2_CONTROL_TL*) e)->y, surf, font, 2);
					i++;
				} while ((double) i < (double) (v / g2->w) + 0.5);
			}
			d2_SelectFont(d2_DefaultFont);
			d2_DrawWordWrappedText(f->x, ((D2_CONTROL_TL*) e)->y + 1, v, ((D2_CONTROL_TL*) e)->height,
			    surf, buf, 0x10);
		} else {
			font = (char*) d2_GetResourceData(f->def);
			((D2_CONTROL_TL*) e)->value_1d4 = *(unsigned short*) (font + 6);
			((D2_CONTROL_TL*) e)->value_1d8 = *(unsigned short*) (font + 8);
			if (((D2_CONTROL_TL*) e)->value_060 != 0 && ((D2_CONTROL_TL*) e)->value_1f4.real == flt_0_0) {
				d2_DrawDimmedSpriteFrame(f->x, f->y, surf, font, d2_ResourceOffset);
			} else {
				d2_DrawSpriteFromSet(f->x, f->y, surf, font, d2_ResourceOffset);
			}
			if (((D2_CONTROL_TL*) e)->value_1f4.real != flt_0_0) {
				y = (int) ((*(double*) 0x6629c8 - ((D2_CONTROL_TL*) e)->value_1f4.real)
				    * ((D2_CONTROL_TL*) e)->height + f->y);
				if (y > d2_ClipBottom) {
					y = d2_ClipBottom;
				}
				d2_SetClipRect(d2_ClipLeft, g_7725fc, d2_ClipRight, y);
				d2_DrawDimmedSpriteFrame(f->x, f->y, d2_ScreenSurface, font, d2_ResourceOffset);
				d2_SetClipRect(d2_ClipLeft, g_7725fc, d2_ClipRight, d2_ClipBottom);
				if (d2_CurrentElementId != ((D2_CONTROL_TL*) e)->value_000) {
					width = (int) (((((D2_CONTROL_TL*) (d2_Controls))[f->ent].value_1f4.real > *(double*) 0x6629c8)
					    ? *(double*) 0x6629c8
					    : ((D2_CONTROL_TL*) (d2_Controls))[f->ent].value_1f4.real) * *(double*) 0x662c38);
					sprintf(buf3, (char*) 0x67d43c, width);
					d2_SelectFont(d2_DefaultFont + 1);
					d2_DrawWordWrappedText(f->x,
					    ((D2_CONTROL_TL*) e)->y + ((D2_CONTROL_TL*) e)->height - 0xf,
					    *(unsigned short*) (font + 6), f->h, surf,
					    buf3, 0x28);
				}
			}
		}
		if (f->def != -1 && !(flags & 0x100) && f->f12c != 0
		    && !(flags & 0x20)) {
			if (e->i[0x3c / 4] != 0) {
				d2_DrawDefaultFontText(f->x,
				    f->y + *(short*) (d2_FileObjTable + f->def * 0x54 + 0x52),
				    surf, buf, 2);
			} else {
				d2_DrawDefaultFontText(f->x,
				    f->y + *(short*) (d2_FileObjTable + f->def * 0x54 + 0x52),
				    surf, buf, 0);
			}
		} else {
			strcpy(((char*) f + 0x2c), buf);
		}
	}
	if (g_67d374 != -1
	    && *(char*) ((char*) &((D2_CONTROL_TL*) (d2_Controls))[f->ent] + 0xcc) != 0
	    && (char*) &((D2_CONTROL_TL*) d2_Controls)[g_67d374] == (char*) &((D2_CONTROL_TL*) d2_Controls)[f->ent]
	    && tp_d2_SelectedControl == 0) {
		g_7725a4 = (int) ((char*) &((D2_CONTROL_TL*) d2_Controls)[f->ent]);
		g_7725a0 = *(int*) (&((D2_CONTROL_TL*) (d2_Controls))[f->ent].parent);
	}
}
