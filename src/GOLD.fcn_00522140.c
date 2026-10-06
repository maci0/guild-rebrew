// FUNCTION: GOLD 0x00522140
/* Twin of GOLDTL 0x5270c0; the GOLD slot records are 0x3c4 bytes, not 0x3cc. */

// SIZE 0x3c4
#include "client_types.h"
typedef Slot_f8f110 Slot;

extern int g_623868;
extern int g_623e90;
extern int g_6238ac;
extern int g_623848;
extern Slot_f8f110 g_f8f110[];
extern int g_7662e0[15];
extern int g_623828;
extern int g_62382c;
extern int g_623830;
extern int g_623834;
extern int g_623838;
extern int g_62383c;
extern int g_62384c;
extern int g_623840;
extern int g_623844;
extern int g_623850;
extern int g_623854;

void __cdecl fcn_00475580(int h, int v);
void __cdecl fcn_0053dd30(int v);
void __cdecl fcn_00475a90(int h, int v);

void __cdecl fcn_00522140(int show)
{
	int i;

	g_623e90 = show;
	if (g_623868 != -1) {
		fcn_00475580(g_623868, show);
	}
	fcn_0053dd30(show);
	if (g_623868 != -1) {
		fcn_00475580(g_623868, show);
	}
	if (g_623828 != -1) {
		fcn_00475a90(g_623828, show);
	}
	if (g_62382c != -1) {
		fcn_00475a90(g_62382c, show);
	}
	if (g_623830 != -1) {
		fcn_00475a90(g_623830, show);
	}
	if (g_623834 != -1) {
		fcn_00475a90(g_623834, show);
	}
	if (g_623838 != -1) {
		fcn_00475a90(g_623838, show);
	}
	if (g_62383c != -1) {
		fcn_00475a90(g_62383c, show);
	}
	if (g_62384c != -1) {
		fcn_00475a90(g_62384c, show);
	}
	if (g_623840 != -1) {
		fcn_00475a90(g_623840, show);
	}
	if (g_623844 != -1) {
		fcn_00475a90(g_623844, show);
	}
	if (g_6238ac != -1 && show == 0) {
		fcn_00475a90(g_6238ac, show);
	}
	if (g_623850 != -1) {
		fcn_00475a90(g_623850, show);
	}
	if (g_623854 != -1) {
		fcn_00475a90(g_623854, show);
	}
	if (g_623848 != -1) {
		fcn_00475a90(g_f8f110[g_623848].panel, show);
	}
	for (i = 0; i < 15; i++) {
		if (g_7662e0[i] != -1) {
			fcn_00475a90(g_7662e0[i], show);
		}
	}
}
