#include "client_dialog_helpers.h"

/* Protection money message box. State 0 opens the dialog and seeds the
 * message ids, state 1 waits for the player choice and pushes the answer
 * into the pending message, the cleanup states close the dialog again. */

#pragma pack(push, 2)
typedef struct {
	int a;
	short b0;
	int b1c0;
	short c1;
	short d;
} Pos14;
#pragma pack(pop)

extern short g_7f4c0c;
extern int g_100f884;
extern int g_100f1dc;
extern int g_14cbca0;

int __cdecl fcn_005463a0(int, ...);
int __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_00545780(int a);
void __cdecl fcn_00546190(int a);
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

	msg = 0;
	actor = fcn_005463a0(1, 1, *(int*) (dlg + 0xac));
	if (actor != 0)
		msg = gm_StartFilteredEntitySearch(1, 1, *(int*) (actor + 0xb0));
	if (*(int*) (dlg + 0x70) == -2 || *(int*) (dlg + 0x70) == -1
	    || actor == 0 || msg == 0) {
		if (*(int*) (dlg + 0x74) != 0)
			fcn_00545780(dlg);
		fcn_00546190(dlg);
	}
	switch (*(int*) (dlg + 0x70)) {
	case 0:
		goto open;
	case 1:
		break;
	default:
		return;
	}
	{
		Pos14 t;

		n = fcn_00500cb0(&g_7f4c00, (int*) (dlg + 0x52));
		if (n > 0) {
			fcn_00545780(dlg);
			fcn_00546190(dlg);
			return;
		}
		if (g_100f884 != *(int*) (*(int*) (dlg + 0x74) + 8))
			return;
		if (g_100f1dc == -1)
			return;
		t = *(Pos14*) &g_7f4c00;
		if (g_14cbca0 == -1) {
			t.b0 = 6;
			t.b1c0 = 0;
		}
		if (g_100f1dc == 2) {
			*(int*) (dlg + 0x70) = 3;
			*(Pos14*) (actor + 0x52) = t;
			*(int*) (actor + 0xb8) = 1;
			fcn_004c5620(3, actor);
			fcn_004c5420(*(int*) (msg + 1), 0x5a, 2, 0x100, 0);
			fcn_004c51a0(
			    *(int*) (*(unsigned short*) (actor + 8) * 0x21c
			    + 0x7f4ca4),
			    *(int*) (*(unsigned short*) (msg + 0x27) * 0x21c
			    + 0x7f4ca4), 0, *(int*) (actor + 0xb4));
			if (*(int*) (actor + 0xbc) != -1) {
				msg = gm_StartFilteredEntitySearch(1, 1, *(int*) (actor + 0xbc));
				*(int*) (msg + 0x4d) = *(int*) (msg + 0x4d)
				    + *(int*) (actor + 0xb4);
			}
		} else if (g_100f1dc == 1) {
			*(int*) (dlg + 0x70) = 3;
			*(Pos14*) (actor + 0x52) = t;
			*(int*) (actor + 0xb8) = 0;
			fcn_004c5620(3, actor);
		}
		fcn_00545780(dlg);
		fcn_00546190(dlg);
		return;
	}
open:
	fcn_00545670(dlg, 0, 0, "Berufe\\Messagebox_SCHUTZGELD", 0x5f3);
	if (*(int*) (dlg + 0x74) == 0) {
		fcn_00546190(dlg);
		return;
	}
	d2_SetForm(*(int*) (*(int*) (dlg + 0x74) + 8), 0);
	switch (fcn_0051e070()) {
	case 0:
		io_AppendText((void*) 0x1a8c,
		    (void*) (unsigned int) *(unsigned short*) (actor + 8),
		    (void*) *(int*) (actor + 0xb4), (void*) msg);
		break;
	case 1:
		io_AppendText((void*) 0x1a8c,
		    (void*) (unsigned int) *(unsigned short*) (actor + 8),
		    (void*) msg, (void*) *(int*) (actor + 0xb4));
		break;
	}
	*(Pos14*) (dlg + 0x44) = *(Pos14*) &g_7f4c00;
	*(Pos14*) (dlg + 0x52) = *(Pos14*) &g_7f4c00;
	fcn_00500bb0((int*) (dlg + 0x52), 3, 0, 0);
	fcn_004c30a0(-7, 0, "_NACHRICHTEN_HS_34", 0, 0);
	*(int*) (dlg + 0x70) = *(int*) (dlg + 0x70) + 1;
}
