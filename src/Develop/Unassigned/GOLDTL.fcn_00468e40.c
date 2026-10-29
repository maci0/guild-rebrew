/* Draws one minimap/office slot: resolves the slot record from the global
 * table, picks the frame colour, draws the glyph runs and finally the label. */

extern char* g_1015ea0;
extern int g_1015ea4;
extern int g_67d370;
extern int g_7725d0;
extern int g_7725fc;
extern int g_67d968;
extern double g_662950;
extern double g_662908;

typedef struct Glyph {
	unsigned short id;
	unsigned short w;
	unsigned short h;
	unsigned short pad6;
} Glyph;

void __cdecl fcn_00472880(int font);
Glyph* __cdecl fcn_0047b620(char* font, int c);
void __cdecl fcn_0047cba0(int x, int y, int surf, char* font, int c);
void __cdecl fcn_0047a040(int a, int b, int c, int d);
void __cdecl fcn_0046bd20(int x, int y, int w, int h, int surf, char* text, int flags);

/* ADDRESS: GOLDTL 0x00468e40 */
void __cdecl fcn_00468e40(int a0, int a1)
{
	char* v1;
	char* v2;
	Glyph* v3;
	Glyph* v4;
	Glyph* v5;
	int v6;
	int v7;
	int v8;
	char v9;
	int i;

	v1 = g_1015ea0 + a0 * 0x2f4;
	v7 = *(int*) (v1 + 0x1d0);
	v8 = 0;
	v9 = 8;
	if ((v7 & 2) && g_7725d0 == 0) {
		if (((g_1015ea0 + g_67d370 * 0x2f4 != v1) && *(int*) (v1 + 0x38) == 0)
		    || *(int*) (v1 + 0x4c) != 0) {
			if (v7 & 1) {
				*(int*) (v1 + 0x3c) = 0;
			}
		} else if (v7 & 1) {
			*(int*) (v1 + 0x3c) = 1;
		}
	}
	if (!(v7 & 2) && *(int*) (v1 + 0x58) != 0 && *(int*) (v1 + 0x4c) == 0) {
		*(int*) (v1 + 0x3c) = *(int*) (v1 + 0x38);
	}
	if (*(int*) (v1 + 0x3c) != 0) {
		v9 = 10;
	} else if (*(int*) (v1 + 0x60) != 0) {
		v9 = 9;
	}
	fcn_00472880(*(int*) (v1 + 0x84));
	v2 = *(char**) (v1 + 0xc);
	v3 = fcn_0047b620(v2, 0);
	v4 = fcn_0047b620(v2, 1);
	v5 = fcn_0047b620(v2, 2);
	v6 = (*(int*) (v1 + 0x18) - v4->w) - v3->w;
	if (*(int*) (v1 + 0x3c) != 0) {
		v8 = 3;
	}
	fcn_0047cba0(*(int*) (v1 + 0x10), *(int*) (v1 + 0x14), a1, v2, v8);
	fcn_0047cba0((*(int*) (v1 + 0x18) - v4->w) + *(int*) (v1 + 0x10),
	    *(int*) (v1 + 0x14), a1, v2, v8 + 1);
	v7 = *(int*) (v1 + 0x10) + v3->w;
	fcn_0047a040(v7 - 1, g_7725fc, v7 + v6, g_67d968);
	i = 0;
	if (g_662950 < (double) (v6 / v5->w) + g_662908) {
		do {
			fcn_0047cba0(v5->w * i + v3->w + *(int*) (v1 + 0x10),
			    *(int*) (v1 + 0x14), a1, v2, v8 + 2);
			i++;
		} while ((double) i < (double) (v6 / v5->w) + g_662908);
	}
	fcn_0046bd20(*(int*) (v1 + 0x10),
	    ((v3->h >> 1) - g_1015ea4 / 2) + 1 + *(int*) (v1 + 0x14),
	    *(int*) (v1 + 0x18), *(int*) (v1 + 0x1c), a1, v1 + 0x8c, v9);
}
