#include <string.h>

typedef struct Combo {
	char pad0[4];
	int f4;			/* +0x04 */
	int f8;			/* +0x08 */
	char pad0c[0x18 - 0x0c];
	int max_len;		/* +0x18 */
	int min_len;		/* +0x1c */
	int pos;		/* +0x20 */
	int f24;		/* +0x24 */
	unsigned char flags;	/* +0x28 */
	char pad29[0x2c - 0x29];
	char text[0x100];	/* +0x2c */
	int text_len;		/* +0x12c */
	char pad130[0x134 - 0x130];
	int sel;		/* +0x134 */
	int text_px;		/* +0x138 */
	char pad13c[0x15c - 0x13c];
	int scroll;		/* +0x15c */
} Combo;

typedef struct ComboList {
	char pad0[0x28];
	int* items;		/* +0x28 */
	int count;		/* +0x2c */
} ComboList;

extern short g_14ce8c2;
extern unsigned char g_14cf950;
extern unsigned char g_14cf736;
extern unsigned char g_14cf72a;
extern int g_7725d0;
extern int g_7725e4;
extern int g_1015ea0;
extern int g_67d8ec;
extern int g_67d3b0;
extern int g_6772c0;
extern int g_100f1cc;
extern int g_100f1d4;
extern int g_100f898;
extern int g_100f89c;
extern int g_100f940;
extern int g_100f950;

void __cdecl fcn_0046b2b0(int id);
int __cdecl fcn_0046b520(char* s, int font);
void __cdecl fcn_00469c40(int x, int y, int slot);
int __cdecl fcn_00469c30(int x, int y, int a3);
char __cdecl fcn_00411610(int shift, int ctrl, int alt, char key);
int __cdecl fcn_00657a73(char* s, int len, int base);

/* ADDRESS: GOLDTL 0x00474300 */
void __cdecl fcn_00474300(void)
{
	int saved;
	unsigned char c;
	Combo* w;

	saved = g_14ce8c2;
	c = g_14cf950;
	if (c == 0) {
		return;
	}
	switch (c) {
	case 14:
		{
			int len;
			char* p;

			w = (*(Combo**) &g_7725d0);
			len = strlen(w->text);
			if (len > 0) {
				p = (char*) w;
				p[len + 0x2b] = 0;
				w = (*(Combo**) &g_7725d0);
			}
			g_14cf950 = 0;
		}
		break;
	case 15:
		{
			ComboList* list;
			int i;
			int idx;
			int* cell;
			int* p;
			Combo* w2;

			w = (*(Combo**) &g_7725d0);
			list = (ComboList*) ((int*) g_1015ea0)[w->sel * 189 + 16];
			if (g_14cf736 == 0 && g_14cf72a == 0) {
				i = g_100f1cc;
				if (i >= list->count - 1) {
					i = -1;
					g_100f1cc = -1;
				}
				i++;
				if (i < list->count) {
					p = list->items + i;
					for (;;) {
						idx = *p;
						cell = &((int*) g_1015ea0)[idx * 189];
						if (cell[8] == 0x41 && cell[0x12] == 0) {
							goto found15;
						}
						i++;
						p++;
						if (i >= list->count) {
							break;
						}
					}
				}
			} else {
				i = g_100f1cc;
				if (i == 0) {
					i = list->count;
					g_100f1cc = i;
				}
				i--;
				if (i >= 0) {
					p = list->items + i;
					for (;;) {
						idx = *p;
						cell = &((int*) g_1015ea0)[idx * 189];
						if (cell[8] == 0x41 && cell[0x12] == 0) {
							goto found15;
						}
						i--;
						p--;
						if (i < 0) {
							break;
						}
					}
				}
			}
			goto tail15;
found15:
			g_100f1cc = i;
			w = (*(Combo**) &g_7725d0);
			((int*) g_1015ea0)[w->sel * 189 + 15] = 0;
			idx = list->items[i];
			w2 = (Combo*) ((int*) g_1015ea0)[idx * 189 + 3];
			(*(Combo**) &g_7725d0) = w2;
			((int*) g_1015ea0)[w2->sel * 189 + 15] = 1;
			g_100f1d4 = g_6772c0 - saved;
			g_100f940 = w2->text_len;
			g_100f950 = 0;
tail15:
			if (g_67d8ec != -1) {
				fcn_0046b2b0(g_67d8ec);
				g_67d8ec = -1;
			}
			w = (*(Combo**) &g_7725d0);
			if (w->flags & 1) {
				g_100f898 = fcn_0046b520(w->text, w->text_px) + w->f4;
				g_100f89c = w->f8;
				if (g_67d8ec != -1) {
					fcn_00469c40(g_100f898, g_100f89c - 7, g_67d8ec);
				} else {
					fcn_00469c30((short) g_100f898, (short) (g_100f89c - 7), g_67d3b0 + 8);
					g_67d8ec = g_100f898;
				}
			}
			g_14cf950 = 0;
		}
		break;
	case 28:
		w = (*(Combo**) &g_7725d0);
		((int*) g_1015ea0)[w->sel * 189 + 15] = 0;
		(*(Combo**) &g_7725d0) = 0;
		g_7725e4 = 0;
		if (g_67d8ec != -1) {
			fcn_0046b2b0(g_67d8ec);
			g_67d8ec = -1;
		}
		/* fall through */
	case 1:
		break;
	default:
		{
		int len;
		w = (*(Combo**) &g_7725d0);
		if (w->flags & 2) {
			if (c >= 2 && c <= 0xb && g_14cf736 == 0 && g_14cf72a == 0) {
				fcn_00657a73(w->text, w->text_len, 10);
				c = g_14cf950;
				w = (*(Combo**) &g_7725d0);
			}
		}
		len = strlen(w->text);
		if (len < ((w->flags & 1) ? w->max_len : (unsigned char) w->f24)) {
			if (w->scroll == 0 || g_100f898 <= w->f4 + w->scroll) {
				if (g_14cf736 == 0 && g_14cf72a == 0) {
					w->text[len] = fcn_00411610(0, 0, 0, c);
				} else {
					w->text[len] = fcn_00411610(1, 0, 0, c);
				}
				w = (*(Combo**) &g_7725d0);
				w->text[len + 1] = 0;
				w = (*(Combo**) &g_7725d0);
			}
		}
		g_14cf950 = 0;
		}
		break;
	}
	w = (*(Combo**) &g_7725d0);
	if (w == 0) {
		return;
	}
	if (w->flags & 2) {
		w->text_len = strlen(w->text);
		w = (*(Combo**) &g_7725d0);
	}
	g_100f898 = fcn_0046b520(w->text, w->text_px) + w->f4;
	if (g_67d8ec != -1) {
		fcn_00469c40(g_100f898, g_100f89c - 7, g_67d8ec);
	}
	return;
}
unsigned char _dpad_7725d0[68];
unsigned char _dpad_14ce922[3592];
