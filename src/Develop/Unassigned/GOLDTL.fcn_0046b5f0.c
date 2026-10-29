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
typedef struct {
	char pad0[0x14];
	int flags;
	char pad18[0x10];
	int* layers;
	int count;
	char pad30[0x3cc - 0x30];
} TextWin46b5f0;

typedef struct {
	char pad0[0x11];
	unsigned short w;
	char pad13[2];
	unsigned short adv;
} Glyph46b5f0;

extern char* g_772524;
extern char* g_1015ea0;
extern int g_1015ea4;
extern int g_67d378;
extern int g_67d380;
extern int g_67d384;
extern int g_67d398;
extern TextWin46b5f0 g_1015f40[0x60];

int __cdecl fcn_00466190(int);
int __cdecl fcn_0046bd00(int, int, int);
void __cdecl fcn_00472880(int);
int __cdecl fcn_0047b620(char*, int);
int __cdecl fcn_0047cba0(int, int, int, char*, int);
int __cdecl fcn_0047ccd0(int, int, int, char*, int);
int __cdecl fcn_0047cd20(int, int, int, char*, int);

/* ADDRESS: GOLDTL 0x0046b5f0 */
void __cdecl fcn_0046b5f0(int a1, int y, int surf, int win, int flag, int newflags, int xstart, int xlimit)
{
	TextWin46b5f0* w;
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
	int (*draw)(int, int, int, char*, int);
	char c;

	w = &g_1015f40[win];
	savedFlags = w->flags;
	back = -1;
	sum = 0;
	step = g_67d380;
	rem = 0;
	hflag = 0;
	special = -1;
	if (newflags != 0) {
		w->flags = newflags;
	}
	if (*(int*) 0x772554 == 1) {
		w->flags = savedFlags;
		return;
	}
	for (n = 0; n < *(int*) 0x772530; n++) {
		sum += *(int*) (0x1011ae8 + n * 0x10c);
	}
	base = ((w->flags & 8) >> 3) + ((w->flags & 0x20) ? 2 : 0);
	if (base < w->count) {
		for (k = base; k < w->count; k++) {
			tile = &((Tile46b5f0*) g_1015ea0)[w->layers[k]];
			if (tile->skip78 == 0 && tile->y14 < y + g_1015ea4
			    && y < tile->y14 + tile->h1c && newflags != 0x40) {
				sum += 6 + tile->w18 + g_67d384;
			}
		}
	}
	x = xstart;
	if ((w->flags & 0x80) && *(int*) 0x772530 > 1 && (char) flag == 0) {
		n = (xlimit - sum) - xstart;
		step = n / (*(int*) 0x772530 - 1);
		rem = n % (*(int*) 0x772530 - 1);
	} else if (w->flags & 0x40) {
		x = (xlimit - (*(int*) 0x772530 - 1) * step) - sum;
	} else if (w->flags & 0x100) {
		x = xstart + (((xlimit - (*(int*) 0x772530 - 1) * step) - sum) - xstart) / 2;
	}
	for (i = 0; i < *(int*) 0x772530; i++) {
		rec = (Rec46b5f0*) (0x10119e0 + i * 0x10c);
		base = ((w->flags & 8) >> 3) + ((w->flags & 0x20) ? 2 : 0);
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
				tex = (char*) fcn_00466190(*(int*) 0x67d3b4 + (g_67d378 - g_67d398) * 2);
				special = 0;
				break;
			case ']':
				tex = (char*) fcn_00466190(*(int*) 0x67d3b4 + (g_67d378 - g_67d398) * 2);
				special = 1;
				break;
			}
		}
		if (rec->b104 & 0x40) {
			fcn_0046bd00(rec->b100, rec->b101, rec->b102);
			draw = fcn_0047cd20;
			back = g_67d378;
			if (g_67d378 == 0x55) {
				fcn_00472880(0x53);
			} else if (g_67d378 == 0x56) {
				fcn_00472880(0x54);
			}
		} else {
			draw = fcn_0047cba0;
		}
		if (flag == 0) {
			if (base < w->count) {
				for (k = base; k < w->count; k++) {
					tile = &((Tile46b5f0*) g_1015ea0)[w->layers[k]];
					if (tile->skip78 == 0) {
						while (tile->x10 < rec->f108 + x
						       && x < tile->x10 + tile->w18 + 6
						       && y + g_1015ea4 > tile->y14
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
		if ((rec->b104 & 0x40) && g_67d378 != back) {
			fcn_00472880(back);
		}
	}
	*(int*) 0x772530 = 0;
	w->flags = savedFlags;
}
