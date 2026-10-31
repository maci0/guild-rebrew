#include "client_dialog_helpers.h"

/* Protection money message box. State 0 opens the dialog and seeds the
 * message ids, state 1 waits for the player choice and pushes the answer
 * into the pending message, the cleanup states close the dialog again. */

extern short g_7f4c0c;
extern int g_100f884;
extern int g_100f1dc;
extern int g_14cbca0;

int __cdecl fcn_005463a0(int a);
int __cdecl gm_StartFilteredEntitySearch(int a);
void __cdecl fcn_00545780(int a);
void __cdecl fcn_00546190(int a, int b, int c);
int __cdecl fcn_00500cb0(void* sel, int* out);
void __cdecl fcn_00545670(int a, int b, int c, char* caption, int d);
int __cdecl fcn_0051e070(void);
int __cdecl fcn_00500bb0(int* sel, int a, int b, int c);
void __cdecl fcn_004c5620(int a, int b);
void __cdecl fcn_004c5420(int a, int b, int c, int d, int e);
void __cdecl fcn_004c30a0(int a, int b, char* name, int c, int d);

/* ADDRESS: GOLDTL 0x00553110 */
void __cdecl fcn_00553110(int dlg, int a1, int a2)
{
	int msg;
	int actor;
	int n;
	int id;
	int v0;
	int v1;
	int col;

	msg = 0;
	actor = fcn_005463a0(1);
	if (actor != 0)
		msg = gm_StartFilteredEntitySearch(1);
	if (*(int*) (dlg + 0x70) == -2 || *(int*) (dlg + 0x70) == -1
	    || actor == 0 || msg == 0) {
		if (*(int*) (dlg + 0x74) != 0)
			fcn_00545780(dlg);
		fcn_00546190(dlg, 0, 0);
	}
	if (*(int*) (dlg + 0x70) != 0) {
		if (*(int*) (dlg + 0x70) != 1)
			return;
		n = fcn_00500cb0((void*) 0x7f4c00, (int*) (dlg + 0x52));
		id = g_7f4c0c;
		v0 = g_7f4c00;
		if (n > 0) {
			fcn_00545780(dlg);
			fcn_00546190(dlg, 0, 0);
			return;
		}
		if (g_100f884 != *(int*) (*(int*) (dlg + 0x74) + 8))
			return;
		if (g_100f1dc == -1)
			return;
		col = g_7f4c08;
		v1 = g_7f4c04;
		if (g_14cbca0 == -1) {
			col = g_7f4c08 & 0xffff0000;
			v1 = 6;
		}
		if (g_100f1dc == 2) {
			*(int*) (dlg + 0x70) = 3;
			*(int*) (actor + 0x52) = v0;
			*(int*) (actor + 0xb8) = 1;
			*(int*) (actor + 0x56) = v1;
			*(int*) (actor + 0x5a) = col;
			*(short*) (actor + 0x5e) = (short) id;
			fcn_004c5620(3, actor);
			fcn_004c5420(*(int*) (msg + 1), 0x5a, 2, 0x100, 0);
			fcn_004c51a0(
			    *(int*) ((unsigned short) (actor + 8) * 0x21c
			    + 0x7f4ca4),
			    *(int*) ((unsigned short) (msg + 0x27) * 0x21c
			    + 0x7f4ca4), 0, *(int*) (actor + 0xb4));
			if (*(int*) (actor + 0xbc) != -1) {
				n = gm_StartFilteredEntitySearch(1);
				*(int*) (n + 0x4d) = *(int*) (n + 0x4d)
				    + *(int*) (actor + 0xb4);
			}
		} else if (g_100f1dc == 1) {
			*(int*) (dlg + 0x70) = 3;
			*(int*) (actor + 0x52) = v0;
			*(int*) (actor + 0xb8) = 0;
			*(int*) (actor + 0x56) = v1;
			*(int*) (actor + 0x5a) = col;
			*(short*) (actor + 0x5e) = (short) id;
			fcn_004c5620(3, actor);
		}
		fcn_00545780(dlg);
		fcn_00546190(dlg, 0, 0);
		return;
	}
	fcn_00545670(dlg, 0, 0, "Berufe\\Messagebox_SCHUTZGELD", 0x5f3);
	if (*(int*) (dlg + 0x74) == 0) {
		fcn_00546190(dlg, 0, 0);
		return;
	}
	d2_SetForm(*(int*) (*(int*) (dlg + 0x74) + 8), 0);
	n = fcn_0051e070();
	if (n == 0) {
		n = *(int*) (actor + 0xb4);
		id = *(unsigned short*) (actor + 8);
	} else if (n == 1) {
		id = *(unsigned short*) (actor + 8);
		n = msg;
		msg = *(int*) (actor + 0xb4);
	} else {
		goto after;
	}
	io_AppendText((void*) 0x1a8c, (void*) id, (void*) n, (void*) msg);
after:
	*(int*) (dlg + 0x44) = g_7f4c00;
	*(int*) (dlg + 0x48) = g_7f4c04;
	*(int*) (dlg + 0x4c) = g_7f4c08;
	*(short*) (dlg + 0x50) = g_7f4c0c;
	*(int*) (dlg + 0x52) = g_7f4c00;
	*(int*) (dlg + 0x56) = g_7f4c04;
	*(int*) (dlg + 0x5a) = g_7f4c08;
	*(short*) (dlg + 0x5e) = g_7f4c0c;
	fcn_00500bb0((int*) (dlg + 0x52), 3, 0, 0);
	fcn_004c30a0(-7, 0, "_NACHRICHTEN_HS_34", 0, 0);
	*(int*) (dlg + 0x70) = *(int*) (dlg + 0x70) + 1;
}
