#include <stdio.h>

extern int g_14673a0;
extern int g_f8a668;
extern int g_6f22a0;
char* __cdecl fcn_004b3c50(int);
int __cdecl fcn_004741e0(int, int, char*);
void __cdecl fcn_004755f0(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_004c3030(int, int, int, int);
int __cdecl fcn_005309d0(void*, int);
void __cdecl fcn_004758e0(int);
int __cdecl fcn_00423460(int*);
void __cdecl fcn_004237f0(int*, int);

/* ADDRESS: GOLD 0x004b5360 */
void __cdecl fcn_004b5360(int id, int flags)
{
	char text[0x100];
	char* rec;
	int window;
	int sound;

	rec = fcn_004b3c50(id);
	window = fcn_004741e0(0, 0, "special\\mission");
	fcn_004755f0(window);
	d2_SetForm(window, 1);
	io_AppendText(*(int*) (rec + 8) + 1);
	io_AppendText((int) "$N");
	io_AppendText(0x7d);
	sprintf(text, "_AUFTRAEGE_VERGABE_HS_%.2d", *(int*) (rec + 0xc));
	sound = fcn_004c3030(-7, 0, (int) text, -1);
	while (fcn_005309d0(fcn_004b5360, flags)) {
		if (g_14673a0)
			g_6f22a0 = 1;
		if (!g_f8a668)
			g_6f22a0 = 1;
	}
	if (window != -1)
		fcn_004758e0(window);
	if (fcn_00423460((int*) sound))
		fcn_004237f0((int*) sound, 0x19);
}
