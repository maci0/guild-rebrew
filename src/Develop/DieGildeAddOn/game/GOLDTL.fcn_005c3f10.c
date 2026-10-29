#include "client_dialog_helpers.h"

/* Dialog runner for one entity's action panel. Opens the dialog, then loops
 * on the message feed: tracks the hovered slot, follows the selection when
 * the record owner changes and finally runs the close/cleanup sequence.
 * arg is the entity record: kind byte at +0, owner word at +0x25, owner
 * word at +0x27, flags at +0x5a/+0x5b. */

extern short g_774970;
extern int g_67d370;
extern int g_7747b0;
extern int g_774654;
extern char g_773d75;
extern int g_14ab294;

int __cdecl fcn_0057ec20(int a);
void __cdecl fcn_0057e880(int a, int b, int c, int d);
int __cdecl fcn_00504bd0(int a);
void __cdecl fcn_00473a90(int a, int b);
int __cdecl fcn_0050cf50(int a);
int __cdecl fcn_00504f30(int a, int b, int c);
int __cdecl fcn_005463a0(int a);
int __cdecl he_fn_Handlung(int a);
int __cdecl gm_SearchTable67(int a);
int __cdecl fcn_00508da0(int a);
int __cdecl fcn_00526120(char* text, int mode);
void __cdecl fcn_004c5530(void* a);
int __cdecl fcn_00471f80(int a);
void __cdecl fcn_004c4510(int a, int b, int c, int d);
void __cdecl fcn_004c4700(int a, int b, int c, void* d);
void __cdecl fcn_004c53a0(void);
int __cdecl fcn_005373e0(int a, int b);

/* ADDRESS: GOLDTL 0x005c3f10 */
void __cdecl fcn_005c3f10(char* ent)
{
	char text[0x48];
	char name[0x100];
	int dlg;
	int other;
	int h;
	int cur;
	int hover;
	int changed;
	int prev;
	int guard;
	int i;
	char* s;
	char* d;
	char c;

	changed = 1;
	hover = 0;
	prev = -1;
	guard = 0;
	if ((*(unsigned char*) (ent + 0x5b) & 4) == 0) {
		if (*(unsigned short*) (ent + 0x25) == g_774970) {
			if (fcn_0057ec20(0x100) == 0)
				return;
			if (*(unsigned short*) (ent + 0x25) == g_774970)
				fcn_0057e880(0x10, (int) ent, 0, 0);
		} else {
			if (fcn_0057ec20(0x4000) == 0)
				return;
		}
		fcn_00504bd0(*(unsigned char*) ent);
		dlg = fcn_00470820(0, 0, (char*) 0x6ac690);
		fcn_00471b60(dlg);
		fcn_00473a90(0, 0);
		fcn_0050cf50((int) ent);
		fcn_00504f30(*(unsigned char*) ent, (int) g_774970, 0);
		if ((*(unsigned char*) (ent + 0x5a) & 2) != 0
		    && *(unsigned short*) (ent + 0x25) != g_774970) {
			other = fcn_005463a0(1);
			while (other != 0
			    && *(int*) (other + 0xac) != *(int*) (ent + 1))
				other = he_fn_Handlung(0);
		}
		do {
			if ((*(unsigned char*) (ent + 0x5b) & 4) != 0
			    || gm_SearchTable67(*(int*) (ent + 1)) == 0)
				g_774654 = 1;
			if (*(unsigned short*) (ent + 0x5a) != prev)
				changed = 1;
			if (*(unsigned short*) (ent + 0x27) == g_774970) {
				h = fcn_005463a0(1);
				while (h != 0
				    && *(int*) (h + 0xac) != *(int*) (ent + 1))
					h = he_fn_Handlung(0);
				if (h != hover) {
					changed = 1;
					hover = h;
				}
			}
			prev = *(unsigned short*) (ent + 0x5a);
			if (changed) {
				changed = 0;
				d2_SetForm(dlg, 1);
				guard = fcn_00508da0((int) ent);
			}
			if (g_67d370 == -1) {
				fcn_00471af0(dlg, 0);
				fcn_005c3820(ent);
			}
			(void) guard;
			(void) text;
			(void) name;
			(void) s;
			(void) d;
			(void) c;
			(void) i;
		} while (fcn_005373e0(0x5c3f10, 0x657c7) != 0);
		if (guard != -1) {
			s = (char*) fcn_00471f80(guard);
			d = name;
			do {
				c = *s++;
				*d++ = c;
			} while (c != 0);
			fcn_004c4510((int) ent, *(int*) (ent + 1), 0, 0);
			fcn_004c4700(1, 0x20, 5, name);
			fcn_004c53a0();
		}
		fcn_00471e30(dlg);
		if (*(unsigned short*) (ent + 0x25) == g_774970)
			fcn_0057e880(0x10, (int) ent, 1, 0);
	}
}
