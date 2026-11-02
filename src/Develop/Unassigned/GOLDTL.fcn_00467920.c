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
 * Status: SIZE_MISMATCH, match 539/4699, object 4723. The frame is one
 * compiler temporary slot from native: `sub esp,0x260` with the struct at +4
 * because the icon hit test spills e[4] (native keeps it in a register). The
 * native prefix is 34 bytes and diverges on the shared zero register (native
 * ebp, compiler edi). h3/h6 live in f.v1c/f.v28 as in native, so only h1/h0
 * stay in registers. The end marks are four separate calls in native; the
 * 0x46843c block writes each pair's two arms as two guarded statements
 * (`if (v28)` then `if (!v28)`) so the compiler keeps three of the four call
 * sites instead of tail-merging both pairs into one. The v34 pair and the
 * v2c `v28` arm survive; the v2c `!v28` arm still merges with the v34 `!v28`
 * arm, so the region stays 24 bytes over the native 0x364. The 0x468554,
 * 0x468700 and 0x467bc2..0x4681cc blocks are
 * transcribed from the listing; the 0x467bc2 split is `if (!(v20 & 0x400))`
 * with the marks in the taken branch and the colour/bitmap path in the else.
 *
 * The 0x4688d7 gauge ends are three independent blocks, as native has them: a
 * fill loop of (int)(w8.f/GH) marks at e[5]+GH(h0)+GH*(idx-1), then an end-cap
 * rect plus a float-y fill loop under flag 0x10, then a second rect and
 * float-y fill loop under v18 > 0. The glyph height/width come from `hs`
 * (e[3]): that is the pointer the native edi carries on this path, and writing
 * `h1` or H6 keeps that pointer live to the end of the function, rotating the
 * whole register plan and costing more matches than the region gains. The
 * 0x2ec/0x2ed hit flags are byte stores (native `mov byte ptr [esi+0x2ec]`).
 */

extern char* g_1015ea0;			/* 0x01015ea0 element table */
extern float g_6628a8;			/* 0x006628a8 */
extern float g_6628a0;			/* 0x006628a0 */
extern float g_662cf8;			/* 0x00662cf8 */
extern double g_662908;			/* 0x00662908 */
extern double g_662950;			/* 0x00662950 */
extern int g_1015ea4;			/* 0x01015ea4 */
extern int g_67d370;			/* 0x0067d370 */
extern int g_67d378;			/* 0x0067d378 */
extern int g_67d398;			/* 0x0067d398 */
extern int g_102d020;			/* 0x0102d020 */
extern int g_102d024;			/* 0x0102d024 */
extern int g_102d028;			/* 0x0102d028 */
extern int g_100f1e8;			/* 0x0100f1e8 */
extern int g_1040490;			/* 0x01040490 */
extern int g_1040494;			/* 0x01040494 */

typedef struct {
	char pad20[0x20];
	int x20;
} fcn_00467920_Surf;

extern fcn_00467920_Surf* g_77256c;	/* 0x0077256c */

extern char str_67d43c[];
extern char str_67d444[];

char* __cdecl fcn_0047b620(char* p, int i);
void __cdecl fcn_0047a040(int, int, int, int);
int __cdecl fcn_0047cba0(int, int, int, char*, int);
int __cdecl fcn_0047cbf0(int, int, int, char*, int);
int __cdecl fcn_0047ccd0(int, int, int, char*, int);
int __cdecl fcn_0047bf80(int, int, int, int, int, int*);
void __cdecl fcn_0047b9a0(int*, unsigned char, unsigned char, unsigned char);
char* __cdecl fcn_00472880(int idx);
void __cdecl fcn_00468c30(int slot, int n, char* out);
int __cdecl fcn_0046b520(char* text, int font);
void __cdecl fcn_0046bbc0(int x, int y, int surf, char* text, unsigned char flags);
int __cdecl fcn_0046bd20(int, int, int, int, int, int, int);
void __cdecl fcn_00479e00(unsigned char r, unsigned char g, unsigned char b);
int __cdecl fcn_0041bac0(unsigned char r, unsigned char g, unsigned char b);
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
} fcn_00467920_frame;

#define GLYPH_W(p)	(*(unsigned short*) ((char*) (p) + 2))
#define GLYPH_H(p)	(*(unsigned short*) ((char*) (p) + 6))
#define H3		((char*) f.v1c)
#define H6		((char*) f.v28)
#define FLD(base, off)	(*(int*) ((char*) (base) + (off)))

/* ADDRESS: GOLDTL 0x00467920 */
void __cdecl fcn_00467920(int a0, int a1)
{
	fcn_00467920_frame f;
	int* e;
	int* b;
	char* h1;
	char* h0;
	char* hs;
	int n;
	int x;
	int y;
	float ratio;

	e = (int*) (g_1015ea0 + a0 * 0x2f4);
	f.v34 = 0;
	f.v2c = 0;
	hs = (char*) e[3];
	f.v14 = (int) hs;
	h1 = fcn_0047b620(hs, 1);
	h0 = fcn_0047b620(hs, 0);
	f.v1c = (int) fcn_0047b620(hs, 3);
	f.v28 = (int) fcn_0047b620(hs, 6);
	f.v30 = e[0x23];
	f.v10 = e[0x25];
	f.v20 = e[0x26];
	f.v38 = e[0x24];
	f.v24 = e[0x27];
	f.w8.i = f.v10 - f.v38;
	if (!f.w8.i) {
		f.wc.f = (float) f.v38;
		f.v18 = f.wc.f;
	}
	else {
		ratio = (float) f.v24 / (float) f.w8.i;
		f.w8.i = f.v30 - f.v38;
		f.v18 = (float) f.w8.i * ratio;
		f.w8.i = e[0x28] - f.v38;
		f.wc.f = (float) f.w8.i * ratio;
	}
	if (f.v18 > g_6628a8 && f.v18 < g_6628a0) {
		f.v18 = 1.0f;
	}
	if (f.wc.f > g_6628a8 && f.wc.f < g_6628a0) {
		f.wc.f = 1.0f;
	}

	if (f.v20 & 2) {
		b = (int*) a1;

		/* 0x467a69: bar frame */
		fcn_0047a040(e[4], b[0xc], e[4] + GLYPH_W(h0) + f.v24, b[0xe]);

		/* 0x467a90: fill run of the value bar */
		f.w8.f = (float) f.v24;
		if (f.w8.f - f.v18 > 0.0f && !(f.v20 & 8)) {
			f.w0.idx = GLYPH_W(h1);
			n = (int) (f.v18 / (float) f.w0.idx + g_6628a0);
			g_102d020 = n;
			if (f.v10 == f.v38) {
				g_102d020 = 1;
			}
			if (!e[0x13]) {
				for (f.w0.idx = 0; f.w0.idx < g_102d020;
				     f.w0.idx++) {
					x = e[4] + GLYPH_W(h0)
					    + GLYPH_W(h1) * f.w0.idx;
					y = e[5] + (GLYPH_H(H3)
						    - GLYPH_H(h1)) / 2;
					fcn_0047cba0(x, y, a1,
						     (char*) f.v14, 1);
				}
			}
			else {
				for (f.w0.idx = 0; f.w0.idx < g_102d020;
				     f.w0.idx++) {
					x = e[4] + GLYPH_W(h0)
					    + GLYPH_W(h1) * f.w0.idx;
					y = e[5] + (GLYPH_H(H3)
						    - GLYPH_H(h1)) / 2;
					fcn_0047cbf0(x, y, (int) b,
						     (char*) f.v14, 1);
				}
			}
		}

		/* 0x467bc2: bar end marks, or the label colour gradient */
		if (!(f.v20 & 0x400)) {
			/* 0x467bcf: the end mark of the fill run */
			if (f.v20 & 0x10) {
				if (f.wc.f > 0.0f) {
					f.w8.i = e[4] + GLYPH_W(h0);
					fcn_0047a040(e[4], b[0xc],
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
						x = e[4] + GLYPH_W(h0)
						    + GLYPH_W(h1) * f.w0.idx;
						y = e[5] + (GLYPH_H(H3)
							    - GLYPH_H(h1)) / 2;
						fcn_0047cba0(x, y, (int) b,
							     (char*) f.v14, 4);
					}
				}
			}

			/* 0x467ca7: bar frame of the fill run */
			fcn_0047a040(e[4], b[0xc],
				     e[4] + GLYPH_W(h0) + f.v24,
				     b[0xe]);

			if (f.v18 > 0.0f) {
				/* 0x467cce: filled part, no tick offset */
				if (!(f.v20 & 8)) {
					f.wc.i = e[4] + GLYPH_W(h0);
					fcn_0047a040(f.wc.i, b[0xc],
						     (int) ((float) f.wc.i
							    + f.v18),
						     b[0xe]);
					f.w8.i = GLYPH_W(h1);
					n = (int) (f.v18 / (float) f.w8.i
						   + g_6628a0);
					g_102d020 = n;
					if (e[0x13]) {
						for (f.w0.idx = 0;
						     f.w0.idx < g_102d020;
						     f.w0.idx++) {
							x = e[4] + GLYPH_W(h0)
							    + GLYPH_W(h1) * f.w0.idx;
							y = e[5]
							    + (GLYPH_H(H3)
							       - GLYPH_H(h1)) / 2;
							fcn_0047cbf0(x, y,
								     (int) b,
								     (char*) f.v14, 2);
						}
					}
					else {
						for (f.w0.idx = 0;
						     f.w0.idx < g_102d020;
						     f.w0.idx++) {
							x = e[4] + GLYPH_W(h0)
							    + GLYPH_W(h1) * f.w0.idx;
							y = e[5]
							    + (GLYPH_H(H3)
							       - GLYPH_H(h1)) / 2;
							fcn_0047cba0(x, y,
								     (int) b,
								     (char*) f.v14, 2);
						}
					}
					fcn_0047a040(e[4], b[0xc],
						     e[4] + GLYPH_W(h0) + f.v24,
						     b[0xe]);
				}
				/* 0x467e39: filled part with the tick offset */
				else {
					f.wc.i = e[4] + GLYPH_W(h0);
					fcn_0047a040(f.wc.i, b[0xc],
						     (int) ((float) f.wc.i
							    + f.v18),
						     b[0xe]);
					f.w8.i = GLYPH_W(h1);
					n = (int) (f.v18 / (float) f.w8.i
						   + g_6628a0);
					g_102d020 = n;
					if (e[0x13]) {
						for (f.w0.idx = 0;
						     f.w0.idx < g_102d020;
						     f.w0.idx++) {
							x = e[4] + GLYPH_W(h0)
							    + GLYPH_W(h1) * f.w0.idx;
							y = e[5]
							    + (GLYPH_H(H3)
							       - GLYPH_H(h1)) / 2;
							fcn_0047cbf0(x, y,
								     (int) b,
								     (char*) f.v14, 1);
						}
					}
					else {
						for (f.w0.idx = 0;
						     f.w0.idx < g_102d020;
						     f.w0.idx++) {
							x = e[4] + GLYPH_W(h0)
							    + GLYPH_W(h1) * f.w0.idx;
							y = e[5]
							    + (GLYPH_H(H3)
							       - GLYPH_H(h1)) / 2;
							fcn_0047cba0(x, y,
								     (int) b,
								     (char*) f.v14, 1);
						}
					}
				}
			}

			/* 0x467f5c: closing rect of the bar frame */
			fcn_0047a040(e[4], b[0xc],
				     e[4] + GLYPH_W(h0) * 2 + f.v24, b[0xe]);
		}
		else {
			/* 0x467f7d: label colour gradient */
			fcn_0041bac0(0xff, 0x80, 0);
			ratio = f.v18 / f.w8.f * 2.0f;
			if (ratio < 1.0) {
				f.w0.b.v00 = 0xc4 - (int) (-24.0f * ratio);
				f.w0.b.v01 = (int) (220.0f * ratio);
				f.w0.b.v02 = (int) (g_6628a8 * ratio);
			}
			else {
				f.w0.b.v00 = 0xdc - (int) ((ratio - 1.0) * 194.0);
				f.w0.b.v01 = 0xdc - (int) ((ratio - 1.0) * 135.0);
				f.w0.b.v02 = (int) ((ratio - 1.0) * g_662950);
			}
			fcn_00479e00((unsigned char) f.w0.b.v00,
				     (unsigned char) f.w0.b.v01,
				     (unsigned char) f.w0.b.v02);

			/* 0x46802e: label bitmap clipped into the bar rect */
			n = fcn_0047bf80(e[4],
					 e[5] + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
					 e[6], e[7], g_77256c->x20, 0);
			if (n) {
				fcn_0047b9a0((int*) n, 1, 1, 1);
			}
			f.wc.i = e[4] + GLYPH_W(h0);
			fcn_0047a040(f.wc.i, ((int*) a1)[0xc],
				     (int) ((float) f.wc.i + f.v18),
				     ((int*) a1)[0xe]);

			/* 0x4680b3: clamped label bitmap */
			n = fcn_0047bf80(e[4] + GLYPH_W(h0),
					 e[5] + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
					 (int) f.v18, e[7], g_77256c->x20, 0);
			if (n) {
				fcn_0047b9a0((int*) n, f.w0.b.v00, f.w0.b.v01,
					     f.w0.b.v02);
			}

			/* 0x468119: bar rect and tick marks */
			fcn_0047a040(e[4], ((int*) a1)[0xc],
				     e[4] + GLYPH_W(h0) + f.v24,
				     ((int*) a1)[0xe]);
			if (!(f.v20 & 8)) {
				f.wc.i = GLYPH_W(h0);
				f.w8.i = (int) (f.w8.f / (float) f.wc.i
					       + g_6628a0);
				for (f.w0.idx = 0; f.w0.idx < f.w8.i;
				     f.w0.idx++) {
					x = e[4] + GLYPH_W(h0)
					    + GLYPH_W(h0) * f.w0.idx;
					y = e[5] + (GLYPH_H(H3)
						    - GLYPH_H(h0)) / 2;
					fcn_0047cba0(x, y, a1,
						     (char*) f.v14, 1);
				}
			}

			/* 0x4681cc: gauge body rect */
			fcn_0047a040(e[0x0a], e[0x0c], e[0x0b], e[0x0d]);
		}
		if (f.v20 & 0x20) {
			goto body;
		}

		/* 0x4681f0: icon hit test */
		if (g_67d370 == e[0] && !(f.v20 & 0x40)) {
			if (e[0x14] && FLD(e[0x14], 0x198)) {
				n = g_102d028;
			}
			else {
				n = g_100f1e8;
			}
			if (f.v28) {
				if (n >= e[4] && n < e[4] + GLYPH_W(H6)) {
					f.v34 = 1;
				}
				else if (n >= e[4] + e[6] - GLYPH_W(H6)
					 && n < e[4] + e[6]) {
					f.v2c = 1;
				}
			}
			else {
				if (n >= e[4] && n < e[4] + GLYPH_W(H3)) {
					f.v34 = 1;
				}
				else if (n >= e[4] + e[6] - GLYPH_W(H3)
					 && n < e[4] + e[6]) {
					f.v2c = 1;
				}
			}
		}
		*((char*) e + 0x2ec) = (char) f.v34;
		*((char*) e + 0x2ed) = (char) f.v2c;
		if (!e[0x18]) {
			fcn_0047cba0(e[4], e[5] + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
				     (int) e[3], (char*) f.v14, 0);
			if (fcn_0047cba0(e[4] + GLYPH_W(h0) + f.v24,
					 e[5] + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
					 (int) e[3], (char*) f.v14, 5)) {
				goto ticks;
			}
			fcn_0047cba0(e[4] + GLYPH_W(h0) + f.v24,
				     e[5] + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
				     (int) e[3], (char*) f.v14, 0);
		}
		else {
			fcn_0047cbf0(e[4], e[5] + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
				     (int) e[3], (char*) f.v14, 0);
			if (fcn_0047cbf0(e[4] + GLYPH_W(h0) + f.v24,
					 e[5] + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
					 (int) e[3], (char*) f.v14, 5)) {
				goto ticks;
			}
			fcn_0047cbf0(e[4] + GLYPH_W(h0) + f.v24,
				     e[5] + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
				     (int) e[3], (char*) f.v14, 0);
		}

	ticks:
		/* 0x46843c: end marks */
		if (f.v34) {
			if (f.v28) {
				fcn_0047ccd0(e[4], e[5] + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
					     (int) e[3], (char*) f.v14, 6);
			}
			if (!f.v28) {
				fcn_0047ccd0(e[4], e[5] + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
					     (int) e[3], (char*) f.v14, 3);
			}
		}
		else if (f.v2c) {
			fcn_0047a040(e[0x0a], e[0x0c], e[0x0b], e[0x0d]);
			if (f.v28) {
				fcn_0047ccd0(e[4] + e[6] - GLYPH_W(H6), e[5] + (GLYPH_H(H6) - GLYPH_H(h0)) / 2,
					     (int) e[3], (char*) f.v14, 7);
			}
			if (!f.v28) {
				fcn_0047ccd0(e[4] + e[6] - GLYPH_W(H3), e[5] + (GLYPH_H(H3) - GLYPH_H(h0)) / 2,
					     (int) e[3], (char*) f.v14, 3);
			}
		}

	body:
		/* 0x468554: label text */
		if (!(f.v20 & 0x48)) {
			f.v28 = (int) f.v18;
			fcn_0047cba0(e[4] + GLYPH_W(h0) - GLYPH_W(h1) / 2
				     + f.v28, e[5], (int) b, (char*) f.v14, 3);
			if (*(char*) ((char*) e + 0xe8)) {
				fcn_00468c30(a0, f.v30, f.buf);
				fcn_00472880(e[0x21] ? e[0x21]
						     : g_67d398 + 1);
				f.v2c = GLYPH_W(h1);
				fcn_0046bd20(e[4] + GLYPH_W(h0) - f.v2c / 2
					     + f.v28,
					     e[5] + GLYPH_H(h1) / 2
					     - g_1015ea4 / 2 + 1,
					     GLYPH_W(h1), GLYPH_H(h1), (int) b,
					     (int) f.buf, 8);
			}
			else {
				fcn_00472880(e[0x21] ? e[0x21]
						     : g_67d398 + 1);
				f.v2c = e[4] + GLYPH_W(h0)
					- GLYPH_W(h1) / 2 + f.v28;
				f.v28 = e[5] + GLYPH_H(h1) / 2
					- g_1015ea4 / 2 + 2;
				if (f.v20 & 0x1000) {
					sprintf(f.buf, str_67d43c, f.v30);
				}
				else if (f.v20 & 0x800) {
					sprintf(f.buf, str_67d43c,
						(int) ((float) f.v30 * g_662cf8
						       / (float) f.v10
						       + g_662908));
				}
				else {
					sprintf(f.buf, str_67d444, f.v30);
				}
				fcn_0046bd20(f.v2c, f.v28, GLYPH_W(h1),
					     GLYPH_H(h1), (int) b, (int) f.buf, 8);
			}
		}

		/* 0x468700: icon block */
		if (f.v20 & 0x04) {
			fcn_0047a040(0, 0, b[1], b[2]);
			fcn_00472880(e[0x21] ? e[0x21]
					     : (e[0x10] ? FLD(e[0x10], 0x28c)
							: g_67d398 + 1));
			if (e[0x1d]) {
				itoa(f.v30, f.v3c, 10);
				fcn_0047a040(0, 0, g_1040494, g_1040490);
				fcn_0046bbc0(e[4] + (int) f.v18, e[5] - 0x10,
					     (int) b, f.v3c, 0);
			}
			sprintf(f.v3c, str_67d444, f.v38);
			n = (g_1015ea4 - GLYPH_H(h0)) / 2 - 1;
			x = fcn_0046b520(f.v3c, g_67d378);
			fcn_0046bbc0(e[4] - x - 4, e[5] - n,
				     (int) b, f.v3c, 0);
			sprintf(f.v3c, str_67d444, f.v10);
			fcn_0046bbc0(e[4] + e[6] + 4, e[5] - n,
				     (int) b, f.v3c, 0);
		}

		/* 0x46882f: trailing text of the element */
		if (*(char*) ((char*) e + 0xa8)) {
			fcn_0047a040(0, 0, FLD(b, 4), FLD(b, 8));
			*(int*) ((char*) e + 0x10) = 8;
			fcn_00472880(e[0x21] ? e[0x21] : g_67d398 + 1);
			if (f.v20 & 0x80) {
				n = fcn_0046b520((char*) e + 0xa8, g_67d398);
				x = e[4] - n - 0x18;
			}
			else {
				x = e[4] - 0xd;
			}
			fcn_0046bd20(x, e[5] - 0x18, FLD(b, 8), (char*) e + 0xa8,
				     0x20, f.v10, (int) b);
		}

		e[0x1d] = 0;
		return;
	}

	if (!(f.v20 & 1)) {
		e[0x1d] = 0;
		return;
	}

	/* 0x4688d7: gauge ends */
	f.w8.f = (float) f.v24;
	if (f.w8.f - f.v18 > 0.0f && !(f.v20 & 8)) {
		g_102d024 = (int) (f.w8.f / (float) GLYPH_H(hs) + g_6628a0);
		for (f.w0.idx = 0; f.w0.idx < g_102d024; f.w0.idx++) {
			y = e[5] + GLYPH_H(h0)
			    + GLYPH_H(hs) * (f.w0.idx - 1);
			x = e[4] + (GLYPH_W(H3) - GLYPH_W(hs)) / 2;
			fcn_0047cba0(x, y, a1, (char*) f.v14, 1);
		}
	}
	/* 0x468997: end cap */
	if ((f.v20 & 0x10) && f.wc.f > 0.0f) {
		fcn_0047a040(e[4], e[5] + GLYPH_H(h0),
			     e[4] + e[6], e[5] + e[7] - GLYPH_H(h0));
		g_102d024 = (int) (f.wc.f / (float) GLYPH_H(hs) + g_6628a0);
		for (f.w0.idx = 0; f.w0.idx < g_102d024; f.w0.idx++) {
			y = (int) ((float) e[7] - f.wc.f - (float) GLYPH_H(h0)
				   + (float) (e[5]
					      + GLYPH_H(hs) * f.w0.idx));
			x = e[4] + (GLYPH_W(H3) - GLYPH_W(hs)) / 2;
			fcn_0047cba0(x, y, a1, (char*) f.v14, 4);
		}
	}
	/* 0x468a74 */
	if (f.v18 > 0.0f) {
		f.v10 = e[5] + e[7] - GLYPH_H(h0);
		fcn_0047a040(e[4], (int) ((float) GLYPH_H(h0) - f.v18),
			     e[4] + e[6], f.v10);
		g_102d024 = (int) (f.v18 / (float) GLYPH_H(hs) + g_6628a0);
		for (f.w0.idx = 0; f.w0.idx < g_102d024; f.w0.idx++) {
			y = (int) ((float) e[7] - f.v18 - (float) GLYPH_H(h0)
				   + (float) (e[5]
					      + GLYPH_H(hs) * f.w0.idx));
			x = e[4] + (GLYPH_W(H3) - GLYPH_W(hs)) / 2;
			fcn_0047cba0(x, y, a1, (char*) f.v14, 1);
		}
		e[0x1d] = 0;
		return;
	}

	e[0x1d] = 0;
}
