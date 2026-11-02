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
 * `f.v3c` the itoa scratch at 0x3c. `f.buf` is sized 0x1f8 rather than the
 * native 0x200 because the compiler spills two dwords after the struct; struct
 * plus spills total the native 0x25c frame. Native body 0x467920..0x468b7a.
 *
 * Native regions, in order:
 *   0x467920  element fetch, sprite handle lookups, fill ratio, clamps
 *   0x467a5c  flag 0x02: bar frame and fill loops
 *   0x4681cc  gauge body rect, icon hit test, icon fills and end marks
 *   0x468554  label text and the 0x468700 icon text block
 *   0x46882f  trailing element text
 *   0x4688d7  flag 0x01: gauge ends and their fill loops
 *
 * Status: equal native prefix is 34 bytes; it diverges on the shared zero
 * register (native ebp, compiler edi). The 0x4681cc..0x468554 region is
 * transcribed from the listing. All frame accesses sit 8 bytes above the
 * native slots because the compiler places its two spill dwords below the
 * struct, and the 0x468554 label block and 0x468700 icon text block still
 * differ in detail.
 */

extern char* g_1015ea0;			/* 0x01015ea0 element table */
extern float g_6628a8;			/* 0x006628a8 */
extern float g_6628a0;			/* 0x006628a0 */
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
extern int g_77256c;			/* 0x0077256c */

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

/* Native frame image; member offsets are the native frame offsets. */
typedef struct {
	char v00, v01, v02, v03;
	int v04;
	int v08;
	float v0c;
	int v10, v14;
	float v18;
	int v1c, v20, v24, v28, v2c, v30, v34, v38;
	char v3c[0x20];
	char buf[0x1f8];
} fcn_00467920_frame;

#define GLYPH_W(p)	(*(unsigned short*) ((char*) (p) + 2))
#define GLYPH_H(p)	(*(unsigned short*) ((char*) (p) + 6))
#define FLD(base, off)	(*(int*) ((char*) (base) + (off)))

/* ADDRESS: GOLDTL 0x00467920 */
void __cdecl fcn_00467920(int a0, int a1)
{
	fcn_00467920_frame f;
	int* e;
	int* b;
	char* h1;
	char* h0;
	char* h3;
	char* h6;
	int i;
	int n;
	int x;
	int y;
	int dx;
	float ratio;

	e = (int*) (g_1015ea0 + a0 * 0x2f4);
	f.v34 = 0;
	f.v2c = 0;
	f.v14 = e[3];
	h1 = fcn_0047b620((char*) e[3], 1);
	h0 = fcn_0047b620((char*) e[3], 0);
	h3 = fcn_0047b620((char*) e[3], 3);
	h6 = fcn_0047b620((char*) e[3], 6);
	f.v1c = (int) h3;
	f.v28 = (int) h6;
	f.v30 = e[0x23];
	f.v10 = e[0x25];
	f.v20 = e[0x26];
	f.v38 = e[0x24];
	f.v24 = e[0x27];
	f.v08 = f.v10 - f.v38;
	if (!f.v08) {
		f.v0c = (float) f.v38;
		f.v18 = f.v0c;
	}
	else {
		ratio = (float) f.v24 / (float) f.v08;
		f.v18 = (float) (f.v30 - f.v38) * ratio;
		f.v0c = (float) (e[0x28] - f.v38) * ratio;
	}
	if (g_6628a8 < f.v18 && f.v18 < g_6628a0) {
		f.v18 = 1.0f;
	}
	if (g_6628a8 < f.v0c && f.v0c < g_6628a0) {
		f.v0c = 1.0f;
	}

	if (f.v30 & 2) {
		b = (int*) a1;

		/* 0x467a69: bar frame */
		fcn_0047a040(e[4], b[0xc], e[4] + GLYPH_W(h0) + f.v30, b[0xe]);

		/* 0x467a90: fill run of the value bar */
		if ((float) f.v24 - f.v18 > 0.0f && !(f.v20 & 8)) {
			n = (int) (f.v18 / (float) GLYPH_W(h1) + g_6628a0);
			g_102d020 = n;
			if (f.v10 == f.v38) {
				g_102d020 = 1;
			}
			if (!e[0x13]) {
				for (i = 0; i < g_102d020; i++) {
					x = e[4] + GLYPH_W(h0) + GLYPH_W(h1) * i;
					y = e[5] + (GLYPH_H(h3) - GLYPH_H(h1)) / 2;
					fcn_0047cba0(x, y, (int) b, (char*) f.v14, 1);
				}
			}
			else {
				for (i = 0; i < g_102d020; i++) {
					x = e[4] + GLYPH_W(h0) + GLYPH_W(h1) * i;
					y = e[5] + (GLYPH_H(h3) - GLYPH_H(h1)) / 2;
					fcn_0047cbf0(x, y, (int) b, (char*) f.v14, 1);
				}
			}
		}

		/* 0x467bc2: upper mark run and right cap */
		if (f.v20 & 0x10) {
			if (f.v0c > 0.0f) {
				fcn_0047a040(e[4], b[0xc],
					     e[5] + GLYPH_W(h0), b[0xe]);
				g_102d020 = (int) (f.v0c / (float) GLYPH_W(h1)
						   + g_6628a0);
				for (i = 0; i < g_102d020; i++) {
					x = e[4] + GLYPH_W(h0) + GLYPH_W(h1) * i;
					y = e[5] + (GLYPH_H(h3) - GLYPH_H(h1)) / 2;
					fcn_0047cba0(x, y, (int) b, (char*) f.v14, 4);
				}
			}
		}
		fcn_0047a040(e[4], b[0xc], e[4] + GLYPH_W(h0) + f.v24 + f.v30,
			     b[0xe]);

		/* 0x467cce: second fill run */
		if (f.v18 > 0.0f) {
			if (f.v20 & 8) {
				goto mark;
			}
			fcn_0047a040(e[4], b[0xc], e[4] + GLYPH_W(h0) + f.v18 + f.v24,
				     b[0xe]);
			g_102d020 = (int) (f.v18 / (float) GLYPH_W(h1) + g_6628a0);
			if (!e[0x13]) {
				for (i = 0; i < g_102d020; i++) {
					x = e[4] + GLYPH_W(h0) + GLYPH_W(h1) * i;
					y = e[5] + (GLYPH_H(h3) - GLYPH_H(h1)) / 2;
					fcn_0047cbf0(x, y, (int) b, (char*) f.v14, 2);
				}
			}
			else {
				for (i = 0; i < g_102d020; i++) {
					x = e[4] + GLYPH_W(h0) + GLYPH_W(h1) * i;
					y = e[5] + (GLYPH_H(h3) - GLYPH_H(h1)) / 2;
					fcn_0047cba0(x, y, (int) b, (char*) f.v14, 2);
				}
			}
			fcn_0047a040(e[4], b[0xc], e[4] + GLYPH_W(h0) + f.v24, b[0xe]);
		}

	mark:
		/* 0x467f5c: closing rect of the bar frame */
		fcn_0047a040(e[4], b[0xc], e[4] + GLYPH_W(h0) * 2 + f.v24, b[0xe]);
		fcn_0047a040(e[0x0a], e[0x0b], e[0x0c], e[0x0d]);

		/* 0x467f7d: label text colour and text run */
		if (f.v20 & 0x40) {
			if (f.v30 & 0x04) {
				fcn_00479e00((unsigned char) f.v00,
					     (unsigned char) f.v01,
					     (unsigned char) f.v02);
			}
			fcn_00468c30(a0, f.v30, f.buf);
			fcn_00472880(e[0x21] ? e[0x21] : g_67d398 + 1);
			fcn_0046bd20(e[4] + GLYPH_W(h1) / 2 - g_1015ea4 / 2 + 1,
				     e[5] + GLYPH_H(h6) / 2 + 2, (int) b,
				     (int) f.buf, 8, 0, 0);
		}

		/* 0x4681cc: gauge body rect */
		fcn_0047a040(e[0x0a], e[0x0c], e[0x0b], e[0x0d]);
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
				if (n >= e[4] && n < e[4] + GLYPH_W(h6)) {
					f.v34 = 1;
				}
				else if (n >= e[4] + e[6] - GLYPH_W(h6)
					 && n < e[4] + e[6]) {
					f.v2c = 1;
				}
			}
			else {
				if (n >= e[4] && n < e[4] + GLYPH_W(h3)) {
					f.v34 = 1;
				}
				else if (n >= e[4] + e[6] - GLYPH_W(h3)
					 && n < e[4] + e[6]) {
					f.v2c = 1;
				}
			}
		}
		e[0x2ec] = (char) f.v34;
		e[0x2ed] = (char) f.v2c;
		if (!e[0x18]) {
			fcn_0047cba0(e[4], e[5] + (GLYPH_H(h3) - GLYPH_H(h0)) / 2,
				     (int) e[3], (char*) f.v14, 0);
			if (fcn_0047cba0(e[4] + GLYPH_W(h0) + f.v24,
					 e[5] + (GLYPH_H(h3) - GLYPH_H(h0)) / 2,
					 (int) e[3], (char*) f.v14, 5)) {
				goto ticks;
			}
			fcn_0047cba0(e[4] + GLYPH_W(h0) + f.v24,
				     e[5] + (GLYPH_H(h3) - GLYPH_H(h0)) / 2,
				     (int) e[3], (char*) f.v14, 0);
		}
		else {
			fcn_0047cbf0(e[4], e[5] + (GLYPH_H(h3) - GLYPH_H(h0)) / 2,
				     (int) e[3], (char*) f.v14, 0);
			if (fcn_0047cbf0(e[4] + GLYPH_W(h0) + f.v24,
					 e[5] + (GLYPH_H(h3) - GLYPH_H(h0)) / 2,
					 (int) e[3], (char*) f.v14, 5)) {
				goto ticks;
			}
			fcn_0047cbf0(e[4] + GLYPH_W(h0) + f.v24,
				     e[5] + (GLYPH_H(h3) - GLYPH_H(h0)) / 2,
				     (int) e[3], (char*) f.v14, 0);
		}

	ticks:
		/* 0x46843c: end marks */
		if (f.v34) {
			if (f.v28) {
				fcn_0047ccd0(e[4],
					     e[5] + (GLYPH_H(h3) - GLYPH_H(h0)) / 2,
					     (int) e[3], (char*) f.v14, 6);
			}
			else {
				fcn_0047ccd0(e[4],
					     e[5] + (GLYPH_H(h3) - GLYPH_H(h0)) / 2,
					     (int) e[3], (char*) f.v14, 3);
			}
		}
		else if (f.v2c) {
			fcn_0047a040(e[0x0a], e[0x0c], e[0x0b], e[0x0d]);
			if (f.v28) {
				fcn_0047ccd0(e[4] + e[6] - GLYPH_W(h6),
					     e[5] + (GLYPH_H(h6) - GLYPH_H(h0)) / 2,
					     (int) e[3], (char*) f.v14, 7);
			}
			else {
				fcn_0047ccd0(e[4] + e[6] - GLYPH_W(h3),
					     e[5] + (GLYPH_H(h3) - GLYPH_H(h0)) / 2,
					     (int) e[3], (char*) f.v14, 3);
			}
		}

	body:
		/* 0x468554: label text */
		if (!(f.v20 & 0x48)) {
			f.v08 = (float) (int) f.v18;
			fcn_0047cba0(e[4] + GLYPH_W(h0) / 2,
				     e[5] + (GLYPH_H(h3) - GLYPH_H(h1)) / 2 + (int) f.v08,
				     (int) b, (char*) f.v14, 3);
			fcn_00468c30(a0, f.v30, f.buf);
			fcn_00472880(e[0x21] ? e[0x21] : g_67d398 + 1);
			fcn_0046bd20(e[4] + GLYPH_W(h1) / 2 - g_1015ea4 / 2 + 1,
				     e[5] + GLYPH_H(h6) / 2 + 2, (int) b,
				     (int) f.buf, 8, 0, 0);
		}

		/* 0x468700: icon block */
		if (f.v20 & 0x04) {
			fcn_0047a040(0, 0, FLD(b, 4), FLD(b, 8));
			fcn_00472880(e[0x21] ? e[0x21] : g_67d398 + 1);
			if (e[0x1d]) {
				itoa(f.v30, f.v3c, 10);
				fcn_0047a040(0, 0, g_1040490, g_1040494);
				fcn_0046bbc0(e[4] - 0x10 + (int) f.v18 + 1,
					     e[5] - 0x10 + 0, (int) b, f.v3c, 0);
			}
			sprintf(f.v3c, str_67d444, f.v38);
			fcn_0046b520(f.v3c, g_67d378);
			fcn_0046bbc0(e[4] - (g_1015ea4 - GLYPH_W(h6)) / 2 - 1,
				     e[5] + 0, (int) b, f.v3c, 0);
			fcn_0046bbc0(e[4] + e[6] + 4,
				     e[5] + 0, (int) b, f.v3c, 0);
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

	if (!(f.v30 & 1)) {
		e[0x1d] = 0;
		return;
	}

	/* 0x4688d7: gauge ends */
	if ((float) f.v24 - f.v18 > 0.0f && (f.v30 & 0x10)) {
		fcn_0047a040(e[4] + GLYPH_W(h3), e[5] + GLYPH_H(h3),
			     e[4], e[5]);
		g_102d024 = (int) (f.v18 / (float) GLYPH_H(h6) + g_6628a0);
		for (i = 0; i < g_102d024; i++) {
			y = e[5] + GLYPH_H(h6) * (i - 1) + GLYPH_H(h0);
			x = e[4] + (GLYPH_W(h1) - GLYPH_W(h3)) / 2;
			fcn_0047cba0(x, y, (int) b, (char*) f.v14, 1);
		}
		/* 0x468997: end cap */
		if (f.v0c > 0.0f) {
			fcn_0047a040(e[5] + GLYPH_W(h0), e[4] + GLYPH_H(h6),
				     e[5], e[4]);
			g_102d024 = (int) (f.v0c / (float) GLYPH_H(h6) + g_6628a0);
			for (i = 0; i < g_102d024; i++) {
				x = e[4] + GLYPH_H(h6) * i + e[5];
				y = e[5] + (GLYPH_W(h3) - GLYPH_W(h0)) / 2;
				fcn_0047cba0(x, y, (int) b, (char*) f.v14, 4);
			}
		}
		/* 0x468a74 */
		if (f.v18 > 0.0f) {
			y = e[5] + GLYPH_H(h0);
			fcn_0047a040(e[4] + GLYPH_H(h6) - GLYPH_W(h0), e[5],
				     e[4], e[5] + GLYPH_H(h0));
			g_102d024 = (int) (f.v18 / (float) GLYPH_H(h6) + g_6628a0);
			for (i = 0; i < g_102d024; i++) {
				x = e[4] + GLYPH_H(h6) * i + e[5];
				y = e[5] + (GLYPH_W(h3) - GLYPH_W(h0)) / 2;
				fcn_0047cba0(x, y, (int) b, (char*) f.v14, 1);
			}
			e[0x1d] = 0;
			return;
		}
	}

	e[0x1d] = 0;
}
