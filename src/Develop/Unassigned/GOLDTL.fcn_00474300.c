#include <string.h>
#include <stdlib.h>
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
extern int tp_d2_SelectedControl;
extern int g_7725e4;
extern char* g_1015ea0;
extern int g_67d8ec;
extern int g_67d3b0;
extern int d2_MouseBottomBoundary;
extern int g_100f1cc;
extern int g_100f1d4;
extern int g_100f898;
extern int g_100f89c;
extern int g_100f940;
extern int g_100f950;

void __cdecl d2_DestroyElement(int id);
int __cdecl d2_MeasureTextWidth(char* s, int font);
void __cdecl d2_PositionControl(int x, int y, int slot);
int __cdecl d2_CreateElement(int x, int y, int a3);
char __cdecl io_TranslateKeyCode(int shift, int ctrl, int alt, char key);

#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00474300 */
void __cdecl d2_HandleTextInput(void)
{
	int saved;

	saved = g_14ce8c2;
	if (g_14cf950 == 0) {
		return;
	}
	switch (g_14cf950) {
	case 14:
		{
			int len;

			len = strlen((*(Combo**) &tp_d2_SelectedControl)->text);
			if (len > 0) {
				((char*) (*(Combo**) &tp_d2_SelectedControl))[len + 0x2b] = 0;
			}
			g_14cf950 = 0;
			goto common_tail;
		}
	case 28:
		((D2_CONTROL_TL*) g_1015ea0)[(*(Combo**) &tp_d2_SelectedControl)->sel].value_03c = 0;
		(*(Combo**) &tp_d2_SelectedControl) = 0;
		g_7725e4 = 0;
		if (g_67d8ec != -1) {
			d2_DestroyElement(g_67d8ec);
			g_67d8ec = -1;
		}
		/* fall through */
	case 1:
	case 59:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
	case 67:
	case 68:
	case 87:
	case 88:
common_tail:
		if ((*(Combo**) &tp_d2_SelectedControl) == 0) {
			return;
		}
		if ((*(Combo**) &tp_d2_SelectedControl)->flags & 2) {
			(*(Combo**) &tp_d2_SelectedControl)->text_len = atoi((*(Combo**) &tp_d2_SelectedControl)->text);
		}
		g_100f898 = d2_MeasureTextWidth((*(Combo**) &tp_d2_SelectedControl)->text, (*(Combo**) &tp_d2_SelectedControl)->text_px) + (*(Combo**) &tp_d2_SelectedControl)->f4;
		if (g_67d8ec != -1) {
			d2_PositionControl(g_100f898, g_100f89c - 7, g_67d8ec);
		}
		return;
	case 15:
		{
		ComboList* list;
		int i;

		list = (ComboList*) *(int*) (&((D2_CONTROL_TL*) g_1015ea0)[(*(Combo**) &tp_d2_SelectedControl)->sel].parent);
		if (g_14cf736 == 0 && g_14cf72a == 0) {
			if (g_100f1cc >= list->count - 1) {
				g_100f1cc = -1;
			}
			for (i = g_100f1cc + 1; i < list->count; i++) {
				if (((D2_CONTROL_TL*) g_1015ea0)[list->items[i]].kind == 0x41 &&
				    ((D2_CONTROL_TL*) g_1015ea0)[list->items[i]].value_048 == 0) {
					goto found15;
				}
			}
		} else {
			if (g_100f1cc == 0) {
				g_100f1cc = list->count;
			}
			for (i = g_100f1cc - 1; i >= 0; i--) {
				if (((D2_CONTROL_TL*) g_1015ea0)[list->items[i]].kind == 0x41 &&
				    ((D2_CONTROL_TL*) g_1015ea0)[list->items[i]].value_048 == 0) {
					goto found15;
				}
			}
		}
		goto tail15;
found15:
		g_100f1cc = i;
		((D2_CONTROL_TL*) g_1015ea0)[(*(Combo**) &tp_d2_SelectedControl)->sel].value_03c = 0;
		(*(Combo**) &tp_d2_SelectedControl) = (Combo*) *(int*) (&((D2_CONTROL_TL*) g_1015ea0)[list->items[i]].data);
		((D2_CONTROL_TL*) g_1015ea0)[(*(Combo**) &tp_d2_SelectedControl)->sel].value_03c = 1;
		g_100f1d4 = d2_MouseBottomBoundary - saved;
		g_100f940 = (*(Combo**) &tp_d2_SelectedControl)->text_len;
		g_100f950 = 0;
tail15:
		if (g_67d8ec != -1) {
			d2_DestroyElement(g_67d8ec);
			g_67d8ec = -1;
		}
		if ((*(Combo**) &tp_d2_SelectedControl)->flags & 1) {
			g_100f898 = d2_MeasureTextWidth((*(Combo**) &tp_d2_SelectedControl)->text, (*(Combo**) &tp_d2_SelectedControl)->text_px) + (*(Combo**) &tp_d2_SelectedControl)->f4;
			g_100f89c = (*(Combo**) &tp_d2_SelectedControl)->f8;
			if (g_67d8ec == -1) {
				g_67d8ec = d2_CreateElement((short) g_100f898, (short) (g_100f89c - 7), g_67d3b0 + 8);
			} else {
				d2_PositionControl(g_100f898, g_100f89c - 7, g_67d8ec);
			}
		}
		g_14cf950 = 0;
		}
		goto common_tail;
	default:
		{
		int len;
		if ((*(Combo**) &tp_d2_SelectedControl)->flags & 2) {
			if (g_14cf950 >= 2 && g_14cf950 <= 0xb && g_14cf736 == 0 && g_14cf72a == 0) {
				_itoa((*(Combo**) &tp_d2_SelectedControl)->text_len, (*(Combo**) &tp_d2_SelectedControl)->text, 10);
			} else {
				goto common_tail;
			}
		}
		len = strlen((*(Combo**) &tp_d2_SelectedControl)->text);
		if (len < (((*(Combo**) &tp_d2_SelectedControl)->flags & 1) ? (*(Combo**) &tp_d2_SelectedControl)->max_len : (unsigned char) (*(Combo**) &tp_d2_SelectedControl)->f24)) {
			if ((*(Combo**) &tp_d2_SelectedControl)->scroll == 0 || g_100f898 <= (*(Combo**) &tp_d2_SelectedControl)->f4 + (*(Combo**) &tp_d2_SelectedControl)->scroll) {
				if (g_14cf736 == 0 && g_14cf72a == 0) {
					(*(Combo**) &tp_d2_SelectedControl)->text[len] = io_TranslateKeyCode(0, 0, 0, g_14cf950);
				} else {
					(*(Combo**) &tp_d2_SelectedControl)->text[len] = io_TranslateKeyCode(1, 0, 0, g_14cf950);
				}
				(*(Combo**) &tp_d2_SelectedControl)->text[len + 1] = 0;
			}
		}
		g_14cf950 = 0;
		}
		goto common_tail;
	}
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_7725d0[68];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_7725d4[4];
unsigned char _dpad_7725f4[4];
#endif
unsigned char _dpad_14ce922[3592];
