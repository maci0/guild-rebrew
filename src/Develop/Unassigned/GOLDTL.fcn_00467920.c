/*
 * Value gauge / progress bar renderer for one HUD element.
 *
 * Reads the element's bar geometry from the 0x2f4-byte element record, derives
 * the fill ratio from the recorded value fields, clamps both bar ends away from
 * the degenerate range and then draws the bar, its frame, its tick marks and
 * its label.
 *
 * The reconstruction carries the native frame as one local: `f`'s member
 * offsets are the native frame offsets, `f.buf` is the text buffer at 0x5c and
 * `f.v3c` the itoa scratch at 0x3c. Native frame is `sub esp,0x25c` with no
 * compiler temporary slots: native reuses the w0/w8/wc members as int-to-float
 * and 16-bit-load scratch, so those members are unions here. `f.w0.b` is the
 * byte view native writes the label colour triple through (offsets 0..2).
 * Native body 0x467920..0x468b7a.
 *
 * Native regions, in order:
 *   0x467920  element fetch, sprite handle lookups, fill ratio, clamps
 *   0x467a5c  flag 0x02: bar frame and fill loops
 *   0x467bc2  flag 0x400: split; else draws the label colour gradient, the
 *             clipped label bitmaps, the bar rect and the tick marks
 *   0x4681cc  gauge body rect, icon hit test, icon fills and end marks
 *   0x468554  label text and the 0x468700 icon text block
 *   0x46882f  trailing element text
 *   0x4688d7  flag 0x01: gauge ends and their fill loops
 *
 */

extern char* g_1015ea0;			/* 0x01015ea0 element table */
extern float g_6628a8;			/* 0x006628a8 */
extern float g_6628a0;			/* 0x006628a0 */
extern float g_662cf8;			/* 0x00662cf8 */
extern double g_662908;			/* 0x00662908 */
extern int d2_FontHeight;			/* 0x01015ea4 */
extern int d2_CurrentElementId;			/* 0x0067d370 */
extern int d2_CurrentFont;			/* 0x0067d378 */
extern int d2_DefaultFont;			/* 0x0067d398 */
extern int g_102d020;			/* 0x0102d020 */
extern int g_102d024;			/* 0x0102d024 */
extern int g_102d028;			/* 0x0102d028 */
extern int d2_MouseX;			/* 0x0100f1e8 */
extern int d2_ScreenHeight;			/* 0x01040490 */
extern int g_1040494;			/* 0x01040494 */

#include "Develop/Units/d2.v1/d2_surface.h"






extern char str_67d43c[];
extern char str_67d444[];

char* __cdecl d2_GetBankEntry(char* p, int i);
void __cdecl d2_SetClipRect(int, int, int, int);
int __cdecl d2_DrawSpriteFromSet(int, int, int, char*, int);
int __cdecl d2_DrawDimmedSpriteFrame(int, int, int, char*, int);
int __cdecl d2_DrawHighlightSprite(int, int, int, char*, int);
int __cdecl d2_QueueTexturedQuad(int, int, int, int, int, int*);
void __cdecl d2_SetQuadVertexColor(int*, unsigned char, unsigned char, unsigned char);
char* __cdecl d2_SelectFont(int idx);
void __cdecl d2_GetValueGaugeStepLabel(int slot, int n, char* out);
int __cdecl d2_MeasureTextWidth(char* text, int font);
void __cdecl d2_DrawDefaultFontText(int x, int y, int surf, char* text, unsigned char flags);
int __cdecl d2_DrawWordWrappedText(int, int, int, int, int, int, int);
void __cdecl d2_SetActiveTextColor(unsigned char r, unsigned char g, unsigned char b);
int __cdecl d2_PackColorForPixelFormat(unsigned char r, unsigned char g, unsigned char b);
int __cdecl sprintf(char* buf, const char* fmt, ...);
char* __cdecl itoa(int value, char* buf, int radix);

/* Native frame image; member offsets are the native frame offsets. The
 * unions are native's own scratch reuse, not extra members. */
typedef struct {
	union {
		struct {
			char v00, v01, v02, v03;
		} b;
		int idx;
		float fl;
	} w0;
	int v04;
	union {
		int i;
		float f;
	} w8;
	union {
		float f;
		int i;
	} wc;
	int v10, v14;
	float v18;
	int v1c, v20, v24, v28, v2c, v30, v34, v38;
	char v3c[0x20];
	char buf[0x200];
} D2_GAUGE_DRAW_FRAME;

#define GLYPH_W(p)	(*(unsigned short*) ((char*) (p) + 2))
#define GLYPH_H(p)	(*(unsigned short*) ((char*) (p) + 6))
#define H3		((char*) f.v1c)
#define H6		((char*) f.v28)
#define FLD(base, off)	(*(int*) ((char*) (base) + (off)))
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00467920 */
void __cdecl d2_DrawValueGauge(int slotIndex, int surface)
{
	D2_GAUGE_DRAW_FRAME f;
	int* e;
	int* b;
	char* h1;
	char* h0;
	char* hs;
	int n;
	int x;
	int y;
	float ratio;

	e = (int*) ((char*) &((D2_CONTROL_TL*) g_1015ea0)[slotIndex]);
	f.v34 = 0;
	f.v2c = 0;
	hs = (char*) *(int*) (&(*(D2_CONTROL_TL*) e).data);
	f.v14 = (int) hs;
	h1 = d2_GetBankEntry(hs, 1);
	h0 = d2_GetBankEntry(hs, 0);
	f.v1c = (int) d2_GetBankEntry(hs, 3);
	f.v28 = (int) d2_GetBankEntry(hs, 6);
	f.v30 = (*(D2_CONTROL_TL*) e).payload.fields.value_08c;
	f.v10 = (*(D2_CONTROL_TL*) e).payload.fields.value_094;
	f.v20 = (*(D2_CONTROL_TL*) e).payload.fields.value_098;
	f.v38 = (*(D2_CONTROL_TL*) e).payload.fields.value_090;
	f.v24 = (*(D2_CONTROL_TL*) e).payload.fields.value_09c;
	f.w8.i = f.v10 - f.v38;
	if (!f.w8.i) {
		f.wc.f = (float) f.v38;
		f.v18 = f.wc.f;
	}
	else {
		ratio = (float) f.v24 / (float) f.w8.i;
		f.w8.i = f.v30 - f.v38;
		f.v18 = (float) f.w8.i * ratio;
		f.w8.i = (*(D2_CONTROL_TL*) e).payload.fields.value_0a0 - f.v38;
		f.wc.f = (float) f.w8.i * ratio;
	}
	if (f.v18 > g_6628a8 && f.v18 < g_6628a0) {
		f.v18 = 1.0f;
	}
	if (f.wc.f > g_6628a8 && f.wc.f < g_6628a0) {
		f.wc.f = 1.0f;
	}

	if (f.v20 & 2) {
		b = (int*) surface;

		/* 0x467a69: bar frame */
		d2_SetClipRect((*(D2_CONTROL_TL*) e).x, b[0xc], (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0) + f.v24, b[0xe]);

		/* 0x467a90: fill run of the value bar */
		f.w8.f = (float) f.v24;
		if (f.w8.f - f.v18 > 0.0f && !(f.v20 & 8)) {
			f.w0.idx = GLYPH_W(h1);
			n = (int) (f.w8.f / (float) f.w0.idx + g_6628a0);
			g_102d020 = n;
			if (f.v10 == f.v38) {
				g_102d020 = 1;
			}
			if (!(*(D2_CONTROL_TL*) e).disabled) {
				for (f.w0.idx = 0; f.w0.idx < g_102d020;
				     f.w0.idx++) {
					x = (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0)
					    + GLYPH_W(h1) * f.w0.idx;
					y = (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H3)
						    - GLYPH_H(h1)) / 2;
					d2_DrawSpriteFromSet(x, y, surface,
						     (char*) f.v14, 1);
				}
			}
			else {
				for (f.w0.idx = 0; f.w0.idx < g_102d020;
				     f.w0.idx++) {
					x = (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0)
					    + GLYPH_W(h1) * f.w0.idx;
					y = (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H3)
						    - GLYPH_H(h1)) / 2;
					d2_DrawDimmedSpriteFrame(x, y, (int) b,
						     (char*) f.v14, 1);
				}
			}
		}

		/* 0x467bc2: bar end marks, or the label colour gradient */
		if (!(f.v20 & 0x400)) {
			/* 0x467bcf: the end mark of the fill run */
			if (f.v20 & 0x10) {
				if (f.wc.f > 0.0f) {
					f.w8.i = (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0);
					d2_SetClipRect((*(D2_CONTROL_TL*) e).x, b[0xc],
						     (int) ((float) f.w8.i
							    + f.wc.f),
						     b[0xe]);
					f.w8.i = GLYPH_W(h1);
					n = (int) (f.wc.f / (float) f.w8.i
						   + g_6628a0);
					g_102d020 = n;
					for (f.w0.idx = 0;
					     f.w0.idx < g_102d020;
					     f.w0.idx++) {
						x = (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0)
						    + GLYPH_W(h1) * f.w0.idx;
						y = (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H3)
							    - GLYPH_H(h1)) / 2;
						d2_DrawSpriteFromSet(x, y, (int) b,
							     (char*) f.v14, 4);
					}
				}
			}

			/* 0x467ca7: bar frame of the fill run */
			d2_SetClipRect((*(D2_CONTROL_TL*) e).x, b[0xc],
				     (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0) + f.v24,
				     b[0xe]);

			if (f.v18 > 0.0f) {
				/* 0x467cce: filled part, no tick offset */
				if (!(f.v20 & 8)) {
					f.wc.i = (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0);
					d2_SetClipRect(f.wc.i, b[0xc],
						     (int) ((float) f.wc.i
							    + f.v18),
						     b[0xe]);
					f.w8.i = GLYPH_W(h1);
					n = (int) (f.v18 / (float) f.w8.i
						   + g_6628a0);
					g_102d020 = n;
					if ((*(D2_CONTROL_TL*) e).disabled) {
						for (f.w0.idx = 0;
						     f.w0.idx < g_102d020;
						     f.w0.idx++) {
							x = (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0)
							    + GLYPH_W(h1) * f.w0.idx;
							y = (*(D2_CONTROL_TL*) e).y
							    + (GLYPH_H(H3)
							       - GLYPH_H(h1)) / 2;
							d2_DrawDimmedSpriteFrame(x, y,
								     (int) b,
								     (char*) f.v14, 2);
						}
					}
					else {
						for (f.w0.idx = 0;
						     f.w0.idx < g_102d020;
						     f.w0.idx++) {
							x = (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0)
							    + GLYPH_W(h1) * f.w0.idx;
							y = (*(D2_CONTROL_TL*) e).y
							    + (GLYPH_H(H3)
							       - GLYPH_H(h1)) / 2;
							d2_DrawSpriteFromSet(x, y,
								     (int) b,
								     (char*) f.v14, 2);
						}
					}
					d2_SetClipRect((*(D2_CONTROL_TL*) e).x, b[0xc],
						     (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0) + f.v24,
						     b[0xe]);
				}
				/* 0x467e39: filled part with the tick offset */
				else {
					f.wc.i = (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0);
					d2_SetClipRect(f.wc.i, b[0xc],
						     (int) ((float) f.wc.i
							    + f.v18),
						     b[0xe]);
					f.w8.i = GLYPH_W(h1);
					n = (int) (f.v18 / (float) f.w8.i
						   + g_6628a0);
					g_102d020 = n;
					if ((*(D2_CONTROL_TL*) e).disabled) {
						for (f.w0.idx = 0;
						     f.w0.idx < g_102d020;
						     f.w0.idx++) {
							x = (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0)
							    + GLYPH_W(h1) * f.w0.idx;
							y = (*(D2_CONTROL_TL*) e).y
							    + (GLYPH_H(H3)
							       - GLYPH_H(h1)) / 2;
							d2_DrawDimmedSpriteFrame(x, y,
								     (int) b,
								     (char*) f.v14, 1);
						}
					}
					else {
						for (f.w0.idx = 0;
						     f.w0.idx < g_102d020;
						     f.w0.idx++) {
							x = (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0)
							    + GLYPH_W(h1) * f.w0.idx;
							y = (*(D2_CONTROL_TL*) e).y
							    + (GLYPH_H(H3)
							       - GLYPH_H(h1)) / 2;
							d2_DrawSpriteFromSet(x, y,
								     (int) b,
								     (char*) f.v14, 1);
						}
					}
				}
			}

			/* 0x467f5c: closing rect of the bar frame */
			d2_SetClipRect((*(D2_CONTROL_TL*) e).x, b[0xc],
				     (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0) * 2 + f.v24, b[0xe]);
		}
		else {
			/* 0x467f7d: label colour gradient */
			d2_PackColorForPixelFormat(0xff, 0x80, 0);
			ratio = f.v18 / f.w8.f * 2.0f;
			if (ratio < 1.0) {
				f.w0.b.v00 = 0xc4 - (int) (-24.0f * ratio);
				f.w0.b.v01 = (int) (220.0f * ratio);
				f.w0.b.v02 = (int) (g_6628a8 * ratio);
			}
			else {
				f.w0.b.v00 = 0xdc - (int) ((ratio - 1.0) * 194.0);
				f.w0.b.v01 = 0xdc - (int) ((ratio - 1.0) * 135.0);
				f.w0.b.v02 = (int) ((ratio - 1.0) * 0.0);
			}
			d2_SetActiveTextColor((unsigned char) f.w0.b.v00,
				     (unsigned char) f.w0.b.v01,
				     (unsigned char) f.w0.b.v02);

			/* 0x46802e: label bitmap clipped into the bar rect */
			n = d2_QueueTexturedQuad((*(D2_CONTROL_TL*) e).x,
					 (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H3) - GLYPH_H(h1)) / 2,
					 (*(D2_CONTROL_TL*) e).width, (*(D2_CONTROL_TL*) e).height, (int) g_77256c->surface, 0);
			if (n) {
				d2_SetQuadVertexColor((int*) n, 1, 1, 1);
			}
			f.wc.i = (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0);
			d2_SetClipRect(f.wc.i, ((int*) surface)[0xc],
				     (int) ((float) f.wc.i + f.v18),
				     ((int*) surface)[0xe]);

			/* 0x4680b3: clamped label bitmap */
			n = d2_QueueTexturedQuad((*(D2_CONTROL_TL*) e).x + GLYPH_W(h0),
					 (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H3) - GLYPH_H(h1)) / 2,
					 (int) f.v18, (*(D2_CONTROL_TL*) e).height, (int) g_77256c->surface, 0);
			if (n) {
				d2_SetQuadVertexColor((int*) n, f.w0.b.v00, f.w0.b.v01,
					     f.w0.b.v02);
			}

			/* 0x468119: bar rect and tick marks */
			d2_SetClipRect((*(D2_CONTROL_TL*) e).x, ((int*) surface)[0xc],
				     (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0) + f.v24,
				     ((int*) surface)[0xe]);
			if (!(f.v20 & 8)) {
				f.wc.i = GLYPH_W(h1);
				f.w8.i = (int) (f.w8.f / (float) f.wc.i
					       + g_6628a0);
				for (f.w0.idx = 0; f.w0.idx < f.w8.i;
				     f.w0.idx++) {
					x = (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0)
					    + GLYPH_W(h1) * f.w0.idx;
					y = (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H3)
						    - GLYPH_H(h1)) / 2;
					d2_DrawSpriteFromSet(x, y, surface,
						     (char*) f.v14, 1);
				}
			}

			/* 0x4681cc: gauge body rect */
			d2_SetClipRect((*(D2_CONTROL_TL*) e).clip_left, (*(D2_CONTROL_TL*) e).clip_top, (*(D2_CONTROL_TL*) e).clip_right, (*(D2_CONTROL_TL*) e).clip_bottom);
		}
		if (f.v20 & 0x20) {
			goto body;
		}

		/* 0x4681f0: icon hit test */
		if (d2_CurrentElementId == (*(D2_CONTROL_TL*) e).value_000 && !(f.v20 & 0x40)) {
			if ((*(D2_CONTROL_TL*) e).value_050 && FLD((*(D2_CONTROL_TL*) e).value_050, 0x198)) {
				n = g_102d028;
			}
			else {
				n = d2_MouseX;
			}
			if (f.v28) {
				if (n >= (*(D2_CONTROL_TL*) e).x && n < (*(D2_CONTROL_TL*) e).x + GLYPH_W(H6)) {
					f.v34 = 1;
				}
				else if (n >= (*(D2_CONTROL_TL*) e).x + (*(D2_CONTROL_TL*) e).width - GLYPH_W(H6)
					 && n < (*(D2_CONTROL_TL*) e).x + (*(D2_CONTROL_TL*) e).width) {
					f.v2c = 1;
				}
			}
			else {
				if (n >= (*(D2_CONTROL_TL*) e).x && n < (*(D2_CONTROL_TL*) e).x + GLYPH_W(H3)) {
					f.v34 = 1;
				}
				else if (n >= (*(D2_CONTROL_TL*) e).x + (*(D2_CONTROL_TL*) e).width - GLYPH_W(H3)
					 && n < (*(D2_CONTROL_TL*) e).x + (*(D2_CONTROL_TL*) e).width) {
					f.v2c = 1;
				}
			}
		}
		*((char*) e + 0x2ec) = (char) f.v34;
		*((char*) e + 0x2ed) = (char) f.v2c;
		if (!(*(D2_CONTROL_TL*) e).value_060) {
			d2_DrawSpriteFromSet((*(D2_CONTROL_TL*) e).x, (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
				     surface, (char*) f.v14, 0);
			if (d2_DrawSpriteFromSet((*(D2_CONTROL_TL*) e).x + GLYPH_W(h0) + f.v24,
					 (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
					 surface, (char*) f.v14, 5)) {
				goto ticks;
			}
			d2_DrawSpriteFromSet((*(D2_CONTROL_TL*) e).x + GLYPH_W(h0) + f.v24,
				     (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
				     surface, (char*) f.v14, 0);
		}
		else {
			d2_DrawDimmedSpriteFrame((*(D2_CONTROL_TL*) e).x, (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
				     surface, (char*) f.v14, 0);
			if (d2_DrawDimmedSpriteFrame((*(D2_CONTROL_TL*) e).x + GLYPH_W(h0) + f.v24,
					 (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
					 surface, (char*) f.v14, 5)) {
				goto ticks;
			}
			d2_DrawDimmedSpriteFrame((*(D2_CONTROL_TL*) e).x + GLYPH_W(h0) + f.v24,
				     (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
				     surface, (char*) f.v14, 0);
		}

	ticks:
		/* 0x46843c: end marks */
		if (f.v34) {
			if (f.v28) {
				d2_DrawHighlightSprite((*(D2_CONTROL_TL*) e).x, (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
					     surface, (char*) f.v14, 6);
			}
			if (!f.v28) {
				d2_DrawHighlightSprite((*(D2_CONTROL_TL*) e).x, (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
					     surface, (char*) f.v14, 3);
			}
		}
		else if (f.v2c) {
			d2_SetClipRect((*(D2_CONTROL_TL*) e).clip_left, (*(D2_CONTROL_TL*) e).clip_top, (*(D2_CONTROL_TL*) e).clip_right, (*(D2_CONTROL_TL*) e).clip_bottom);
			if (f.v28) {
				d2_DrawHighlightSprite((*(D2_CONTROL_TL*) e).x + (*(D2_CONTROL_TL*) e).width - GLYPH_W(H6), (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H6) - GLYPH_H(h0)) / 2,
					     surface, (char*) f.v14, 7);
			}
			if (!f.v28) {
				d2_DrawHighlightSprite((*(D2_CONTROL_TL*) e).x + (*(D2_CONTROL_TL*) e).width - GLYPH_W(H3), (*(D2_CONTROL_TL*) e).y + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
					     surface, (char*) f.v14, 3);
			}
		}

	body:
		/* 0x468554: label text */
		if (!(f.v20 & 0x48)) {
			f.v28 = (int) f.v18;
			d2_DrawSpriteFromSet((*(D2_CONTROL_TL*) e).x + GLYPH_W(h0) - GLYPH_W(H3) / 2
				     + f.v28, (*(D2_CONTROL_TL*) e).y, (int) b, (char*) f.v14, 3);
			if (*(char*) ((char*) e + 0xe8)) {
				d2_GetValueGaugeStepLabel(slotIndex, f.v30, f.buf);
				d2_SelectFont((*(D2_CONTROL_TL*) e).font ? (*(D2_CONTROL_TL*) e).font
						     : d2_DefaultFont + 1);
				f.v2c = GLYPH_W(H3);
				d2_DrawWordWrappedText((*(D2_CONTROL_TL*) e).x + GLYPH_W(h0) - f.v2c / 2
					     + f.v28,
					     (*(D2_CONTROL_TL*) e).y + GLYPH_H(H3) / 2
					     - d2_FontHeight / 2 + 1,
					     GLYPH_W(H3), GLYPH_H(H3), (int) b,
					     (int) f.buf, 8);
			}
			else {
				d2_SelectFont((*(D2_CONTROL_TL*) e).font ? (*(D2_CONTROL_TL*) e).font
						     : d2_DefaultFont + 1);
				f.v2c = (*(D2_CONTROL_TL*) e).x + GLYPH_W(h0)
					- GLYPH_W(H3) / 2 + f.v28;
				f.v28 = (*(D2_CONTROL_TL*) e).y + GLYPH_H(H3) / 2
					- d2_FontHeight / 2 + 2;
				if (f.v20 & 0x1000) {
					sprintf(f.buf, str_67d43c, f.v30);
				}
				else if (f.v20 & 0x800) {
					sprintf(f.buf, str_67d43c,
						(int) ((float) f.v30 * g_662cf8
						       / (float) f.v10
						       + 0.5));
				}
				else {
					sprintf(f.buf, str_67d444, f.v30);
				}
				d2_DrawWordWrappedText(f.v2c, f.v28, GLYPH_W(H3),
					     GLYPH_H(H3), (int) b, (int) f.buf, 8);
			}
		}

		/* 0x468700: icon block */
		if (f.v20 & 0x04) {
			d2_SetClipRect(0, 0, b[1], b[2]);
			d2_SelectFont((*(D2_CONTROL_TL*) e).font ? (*(D2_CONTROL_TL*) e).font
					     : (*(int*) (&(*(D2_CONTROL_TL*) e).parent) ? FLD(*(int*) (&(*(D2_CONTROL_TL*) e).parent), 0x28c)
							: d2_DefaultFont + 1));
			if ((*(D2_CONTROL_TL*) e).value_074) {
				itoa(f.v30, f.v3c, 10);
				d2_SetClipRect(0, 0, g_1040494, d2_ScreenHeight);
				d2_DrawDefaultFontText((*(D2_CONTROL_TL*) e).x + (int) f.v18, (*(D2_CONTROL_TL*) e).y - 0x10,
					     (int) b, f.v3c, 0);
			}
			sprintf(f.v3c, str_67d444, f.v38);
			n = (d2_FontHeight - GLYPH_H(h0)) / 2 - 1;
			x = d2_MeasureTextWidth(f.v3c, d2_CurrentFont);
			d2_DrawDefaultFontText((*(D2_CONTROL_TL*) e).x - x - 4, (*(D2_CONTROL_TL*) e).y - n,
				     (int) b, f.v3c, 0);
			sprintf(f.v3c, str_67d444, f.v10);
			d2_DrawDefaultFontText((*(D2_CONTROL_TL*) e).x + (*(D2_CONTROL_TL*) e).width + 4, (*(D2_CONTROL_TL*) e).y - n,
				     (int) b, f.v3c, 0);
		}

		/* 0x46882f: trailing text of the element */
		if (*(char*) ((char*) e + 0xa8)) {
			d2_SetClipRect(0, 0, FLD(b, 4), FLD(b, 8));
			/* Four pending pushes make 0x46884f the v10 scratch, not flags. */
			d2_SelectFont((*(D2_CONTROL_TL*) e).font ? (*(D2_CONTROL_TL*) e).font : d2_DefaultFont + 1);
			x = (*(D2_CONTROL_TL*) e).x;
			y = (*(D2_CONTROL_TL*) e).y - 0xd;
			n = 8;
			if (f.v20 & 0x80) {
				x = (*(D2_CONTROL_TL*) e).x - d2_MeasureTextWidth((char*) e + 0xa8, d2_DefaultFont) - 0x18;
				y = (*(D2_CONTROL_TL*) e).y;
				n = 0x10;
			}
			d2_DrawWordWrappedText(x, y, (*(D2_CONTROL_TL*) e).width, 0x20, (int) b, (int) ((char*) e + 0xa8), n);
		}

		(*(D2_CONTROL_TL*) e).value_074 = 0;
		return;
	}

	if (!(f.v20 & 1)) {
		(*(D2_CONTROL_TL*) e).value_074 = 0;
		return;
	}

	/* 0x4688d7: gauge ends */
	f.w8.f = (float) f.v24;
	if (f.w8.f - f.v18 > 0.0f && !(f.v20 & 8)) {
		f.v10 = GLYPH_H(h1);
		g_102d024 = (int) (f.w8.f / (float) f.v10 + g_6628a0);
		for (f.w0.idx = 0; f.w0.idx < g_102d024; f.w0.idx++) {
			y = (*(D2_CONTROL_TL*) e).y + GLYPH_H(h0)
			    + GLYPH_H(h1) * (f.w0.idx - 1);
			x = (*(D2_CONTROL_TL*) e).x + (GLYPH_W(H3) - GLYPH_W(h1)) / 2;
			d2_DrawSpriteFromSet(x, y, surface, (char*) f.v14, 1);
		}
	}
	/* 0x468997: end cap */
	if ((f.v20 & 0x10) && f.wc.f > 0.0f) {
		d2_SetClipRect((*(D2_CONTROL_TL*) e).x, (*(D2_CONTROL_TL*) e).y + GLYPH_H(h0),
			     (*(D2_CONTROL_TL*) e).x + (*(D2_CONTROL_TL*) e).width, (*(D2_CONTROL_TL*) e).y + (*(D2_CONTROL_TL*) e).height - GLYPH_H(h0));
		f.v10 = GLYPH_H(h1);
		g_102d024 = (int) (f.wc.f / (float) f.v10 + g_6628a0);
		for (f.w0.idx = 0; f.w0.idx < g_102d024; f.w0.idx++) {
			f.v10 = GLYPH_H(h0);
			f.w8.i = (*(D2_CONTROL_TL*) e).y + GLYPH_H(h1) * f.w0.idx;
			y = (int) ((float) (*(D2_CONTROL_TL*) e).height - f.wc.f - (float) f.v10
				   + (float) f.w8.i);
			x = (*(D2_CONTROL_TL*) e).x + (GLYPH_W(H3) - GLYPH_W(h1)) / 2;
			d2_DrawSpriteFromSet(x, y, surface, (char*) f.v14, 4);
		}
	}
	/* 0x468a74 */
	if (f.v18 > 0.0f) {
		f.v10 = (*(D2_CONTROL_TL*) e).y + (*(D2_CONTROL_TL*) e).height - GLYPH_H(h0);
		d2_SetClipRect((*(D2_CONTROL_TL*) e).x, (int) ((float) f.v10 - f.v18),
			     (*(D2_CONTROL_TL*) e).x + (*(D2_CONTROL_TL*) e).width, f.v10);
		f.v10 = GLYPH_H(h1);
		g_102d024 = (int) (f.v18 / (float) f.v10 + g_6628a0);
		for (f.w0.idx = 0; f.w0.idx < g_102d024; f.w0.idx++) {
			f.v10 = GLYPH_H(h0);
			f.w8.i = (*(D2_CONTROL_TL*) e).y + GLYPH_H(h1) * f.w0.idx;
			y = (int) ((float) (*(D2_CONTROL_TL*) e).height - f.v18 - (float) f.v10
				   + (float) f.w8.i);
			x = (*(D2_CONTROL_TL*) e).x + (GLYPH_W(H3) - GLYPH_W(h1)) / 2;
			d2_DrawSpriteFromSet(x, y, surface, (char*) f.v14, 1);
		}
		(*(D2_CONTROL_TL*) e).value_074 = 0;
		return;
	}

	(*(D2_CONTROL_TL*) e).value_074 = 0;
}
