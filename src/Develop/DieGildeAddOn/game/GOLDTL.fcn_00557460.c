#include "client_dialog_helpers.h"

/* Dark corner dialog ("Dunkle Ecke"). Scans the entity grid around the
 * player for a dark spot, then posts the found entity as the dialog result.
 * arg is the dialog record; state lives at arg+0x70, the selected entity at
 * arg+0xac, the result handle at arg+0x84. */

extern short g_774970;
extern int g_6a5f7c;

int __cdecl fcn_00508e40(int id);
void __cdecl fcn_004c5c80(int a);
void __cdecl fcn_004c57e0(int a, int b);
void __cdecl fcn_004c5da0(int a, int b, int c, int d, int e,
    char* label);
int __cdecl fcn_004c4450(int h);
int* __cdecl fcn_004c4480(int h);
int __cdecl fcn_004c5620(int a, int b);
void __cdecl fcn_00546190(int a, int b, int c);
void __cdecl fcn_00500bb0(int* sel, int a, int b, int c);
void __cdecl fcn_005015e0(void* out, int a, int b, int ent);
int __cdecl fcn_0042e450(void);
int __cdecl fcn_00529670(int a, int b);
float __cdecl fcn_00507f10(int a, int b);

/* ADDRESS: GOLDTL 0x00557460 */
void __cdecl fcn_00557460(int dlg, int arg2)
{
	char text[0x100];
	unsigned char* cell;
	char* line;
	int ent;
	int h;
	int* p;
	int v;
	int i;
	int state;
	int scan;
	int tries;
	float f;
	unsigned char kind;
	unsigned int bits;

	(void) arg2;
	if (*(int*) (dlg + 0x70) == -1 || *(int*) (dlg + 0x70) == -2) {
		if ((*(unsigned char*) (dlg + 0x78) & 2) != 0) {
			ent = fcn_00508e40(*(int*) (dlg + 0xac));
			if (ent != 0) {
				fcn_004c5c80(*(int*) (ent + 4));
				fcn_004c57e0(*(int*) (ent + 4), 1);
			}
		}
		fcn_00546190(dlg, 0, 0);
		return;
	}
	if ((*(unsigned char*) (dlg + 0x78) & 4) != 0)
		return;
	if (*(int*) (dlg + 0x84) != -1) {
		if (fcn_004c4450(*(int*) (dlg + 0x84)) == 0)
			return;
	}
	state = *(int*) (dlg + 0x70);
	ent = 0;
	switch (state) {
	case 0:
		if (fcn_004c4450(*(int*) (dlg + 0xac)) == 1) {
			p = fcn_004c4480(*(int*) (dlg + 0xac));
			*(int*) (dlg + 0xac) = p[1];
			fcn_00500bb0((int*) (dlg + 0x52), 0, 1, 0);
			*(int*) (dlg + 0x84) = fcn_004c5620(1, dlg);
			return;
		}
		fcn_00500bb0((int*) (dlg + 0x52), 0x18, 0, 0);
		*(int*) (dlg + 0x84) = fcn_004c5620(4, dlg);
		return;
	case 1:
		scan = *(unsigned int*) (dlg + 0xc4);
		tries = 0x100;
		h = 0;
		do {
			cell = (unsigned char*) ((int) lpGebaeudeINST + scan * 0xa9);
			kind = lpGebaeudePROT[(unsigned) *cell * 0x24d];
			if (kind < 0x20) {
				bits = 1u << (kind & 0x1f);
			} else {
				bits = 0;
			}
			if ((bits != 0 || kind >= 0x20)
			    && *(int*) (cell + 1) == *(int*) (dlg + 0xb0)) {
				h = (int) cell;
				break;
			}
			(void) bits;
			if ((1u << (kind & 0x1f) & 0xa7fcc3a6) != 0
			    && *(int*) (cell + 1) == *(int*) (dlg + 0xb0)) {
				h = (int) cell;
				break;
			}
			tries--;
			scan = (scan + *(int*) (dlg + 200)) & 0x800000ff;
			cell = 0;
			if ((int) scan < 0)
				scan = ((scan - 1) | 0xffffff00) + 1;
		} while (tries != 0);
		v = (*(int*) (dlg + 200) + scan) & 0x800000ff;
		if ((int) v < 0)
			v = ((v - 1) | 0xffffff00) + 1;
		*(unsigned int*) (dlg + 0xc4) = v;
		if (h != 0) {
			line = (char*) &text;
			fcn_0051af00(line, g_6a5f7c, (void*) h);
			ent = fcn_00508e40(*(int*) (dlg + 0xac));
			if (ent != 0) {
				fcn_004c5c80(*(int*) (ent + 4));
				fcn_004c5da0(*(int*) (ent + 4),
				    *(int*) (h + 1), -1, 0, 1, "Dunkle Ecke");
				fcn_00500bb0((int*) (dlg + 0x52), 0, 5, 0);
				*(int*) (dlg + 0xb8) = *(int*) (h + 1);
				*(int*) (dlg + 0x84) = fcn_004c5620(2, dlg);
				return;
			}
		}
		break;
	case 2:
		h = 0;
		fcn_005015e0(&h, 0, 0, *(int*) (dlg + 0xb8));
		fcn_00500bb0((int*) (dlg + 0x52), 0, 5, 0);
		if (h == 0) {
			*(int*) (dlg + 0x84) = fcn_004c5620(-1, dlg);
			return;
		}
		ent = fcn_00508e40(*(int*) (dlg + 0xac));
		if (ent != 0) {
			v = fcn_00529670(ent, h);
			if (v != 0) {
				*(int*) (dlg + 0xbc) = *(int*) (dlg + 0xbc) - 1;
				{
					float r = fcn_00507f10(
					    (int) ((unsigned short)
					    *(unsigned short*) (h + 0x27) * 0x21c
					    + 0x7f4ca0), 2);
					i = (int) r;
				}
				if (*(int*) (dlg + 0xc0) < 1) {
					*(int*) (dlg + 0xc0) =
					    *(int*) (dlg + 0xc0) + 1;
				} else if (fcn_0042e450() * 0.5f < (float) i) {
					*(int*) (dlg + 0xc0) =
					    *(int*) (dlg + 0xc0) + 1;
				}
			}
		}
		break;
	default:
		break;
	}
	(void) f;
	(void) state;
	(void) text;
}
