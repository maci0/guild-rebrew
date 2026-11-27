#include <string.h>

// SIZE 0x2f4
typedef struct {
	char pad0[0x10];
	int x10;
	int y14;
	int w18;
	int h1c;
	char pad20[0x58];
	int skip78;
	char pad7c[0x2f4 - 0x7c];
} Tile46b5f0;

// SIZE 0x10c
typedef struct {
	char text[0x100];
	unsigned char b100;
	unsigned char b101;
	unsigned char b102;
	char pad103;
	unsigned char b104;
	char pad105[3];
	int f108;
} Rec46b5f0;

// SIZE 0x3cc
#include "Develop/Units/d2.v1/d2_win.h"









#pragma pack(push, 1)
typedef struct {
	char pad0[0x11];
	unsigned short w;
	char pad13[2];
	unsigned short adv;
} Glyph46b5f0;
#pragma pack(pop)

extern char* g_772524;
extern char* g_1015ea0;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67d384;
extern int g_772554;
extern D2_WIN g_1015f40[0x60];

int __cdecl d2_GetResourceData(int);
int __cdecl d2_SetTextColor(int, int, int);
void __cdecl d2_SelectFont(int);
int __cdecl fcn_0047b620(char*, int);
int __cdecl fcn_0047cba0(int, int, int, char*, int);
int __cdecl fcn_0047ccd0(int, int, int, char*, int);
int __cdecl fcn_0047cd20(int, int, int, char*, int);

/* ADDRESS: GOLDTL 0x0046b5f0 */
void __cdecl d2_RenderMarkupLine(int a1, int y, int surf, int win, int flag, int newflags, int xstart, int xlimit)
{
	D2_WIN* w;
	Rec46b5f0* rec;
	Tile46b5f0* tile;
	Glyph46b5f0* glyph;
	char* tex;
	int savedFlags;
	int back;
	int sum;
	int n;
	int i;
	int k;
	int j;
	int base;
	int step;
	int rem;
	int special;
	int hflag;
	int x;
	int lastc;
	int cnt;
	int (*draw)(int, int, int, char*, int);
	char c;

	w = &g_1015f40[win];
	savedFlags = (*(int*) &w->pad14[0]);
	lastc = 0;
	sum = 0;
	rem = 0;
	hflag = 0;
	back = -1;
	special = -1;
	step = g_67d380;
	if (newflags != 0) {
		(*(int*) &w->pad14[0]) = newflags;
	}
	if (g_772554 == 1) {
		goto out;
	}
	cnt = *(int*) 0x772530;
	for (n = 0; n < cnt; n++) {
		sum += *(int*) (0x1011ae8 + n * 0x10c);
	}
	base = (((*(int*) &w->pad14[0]) & 8) >> 3) + (((*(int*) &w->pad14[0]) & 0x20) ? 2 : 0);
	if (base < w->count) {
		for (k = base; k < w->count; k++) {
			tile = &((Tile46b5f0*) g_1015ea0)[w->children[k]];
			if (tile->skip78 == 0 && tile->y14 < y + d2_FontHeight
			    && y < tile->y14 + tile->h1c && newflags != 0x40) {
				sum += 6 + tile->w18 + g_67d384;
			}
		}
	}
	x = xstart;
	if (((*(int*) &w->pad14[0]) & 0x80) && *(int*) 0x772530 > 1 && (char) flag == 0) {
		n = (xlimit - sum) - xstart;
		step = n / (*(int*) 0x772530 - 1);
		rem = n % (*(int*) 0x772530 - 1);
	} else if ((*(int*) &w->pad14[0]) & 0x40) {
		x = (xlimit - (*(int*) 0x772530 - 1) * step) - sum;
	} else if ((*(int*) &w->pad14[0]) & 0x100) {
		x = xstart + (((xlimit - (*(int*) 0x772530 - 1) * step) - sum) - xstart) / 2;
	}
	for (i = 0; i < *(int*) 0x772530; i++) {
		rec = (Rec46b5f0*) (0x10119e0 + i * 0x10c);
		base = (((*(int*) &w->pad14[0]) & 8) >> 3) + (((*(int*) &w->pad14[0]) & 0x20) ? 2 : 0);
		c = rec->text[0];
		flag = 0;
		special = -1;
		if (c == '$') {
			switch (rec->text[1]) {
			case 'H':
				hflag = 1;
				/* fall through */
			case 'M':
				flag = 1;
				break;
			case 'T':
				x = rec->f108;
				flag = 1;
				break;
			case '[':
				tex = (char*) d2_GetResourceData(*(int*) 0x67d3b4 + (d2_CurrentFont - d2_DefaultFont) * 2);
				special = 0;
				break;
			case ']':
				tex = (char*) d2_GetResourceData(*(int*) 0x67d3b4 + (d2_CurrentFont - d2_DefaultFont) * 2);
				special = 1;
				break;
			}
		}
		if (rec->b104 & 0x40) {
			d2_SetTextColor(rec->b100, rec->b101, rec->b102);
			draw = fcn_0047cd20;
			back = d2_CurrentFont;
			if (d2_CurrentFont == 0x55) {
				d2_SelectFont(0x53);
			} else if (d2_CurrentFont == 0x56) {
				d2_SelectFont(0x54);
			}
		} else {
			draw = fcn_0047cba0;
		}
		if (flag == 0) {
			if (base < w->count) {
				for (k = base; k < w->count; k++) {
					tile = &((Tile46b5f0*) g_1015ea0)[w->children[k]];
					if (tile->skip78 == 0) {
						while (tile->x10 < rec->f108 + x
						       && x < tile->x10 + tile->w18 + 6
						       && y + d2_FontHeight > tile->y14
						       && y < tile->y14 + tile->h1c
						       && newflags != 0x40) {
							x = tile->x10 + tile->w18 + 6;
						}
					}
				}
			}
			if (special == -1) {
				if (hflag != 0) {
					if ((int) strlen(rec->text) > 0) {
						j = 0;
						do {
							c = rec->text[j];
							lastc = (unsigned char) c;
							if (c != '~') {
								glyph = (Glyph46b5f0*) fcn_0047b620(g_772524, (unsigned char) c);
								if (j != 0) {
									x -= glyph->w;
								}
								if (fcn_0047ccd0(x, y, surf, g_772524, (unsigned char) c)) {
									x += glyph->adv + g_67d384;
								}
							}
							if (x > xlimit) {
								break;
							}
							j++;
						} while (j < (int) strlen(rec->text));
					}
				} else {
					if ((int) strlen(rec->text) > 0) {
						j = 0;
						do {
							c = rec->text[j];
							lastc = (unsigned char) c;
							if (c != '~') {
								glyph = (Glyph46b5f0*) fcn_0047b620(g_772524, (unsigned char) c);
								if (j != 0) {
									x -= glyph->w;
								}
								if (draw(x, y, surf, g_772524, (unsigned char) c)) {
									x += glyph->adv + g_67d384;
									*(int*) 0x772608 = *(int*) 0x772608 - 1;
								}
							}
							if (x > xlimit) {
								break;
							}
							j++;
						} while (j < (int) strlen(rec->text));
					}
				}
				hflag = 0;
			} else {
				glyph = (Glyph46b5f0*) fcn_0047b620(tex, special);
				if (fcn_0047cba0(x, y, surf, tex, special)) {
					x += glyph->adv + g_67d384;
				}
			}
		}
		if (lastc != '~' && flag == 0) {
			x += step;
			if (rem != 0) {
				x++;
				rem--;
			}
		}
		if ((rec->b104 & 0x40) && d2_CurrentFont != back) {
			d2_SelectFont(back);
		}
	}
	*(int*) 0x772530 = 0;
out:
	(*(int*) &w->pad14[0]) = savedFlags;
}
