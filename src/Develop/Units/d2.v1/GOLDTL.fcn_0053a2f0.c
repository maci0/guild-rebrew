extern int g_1040480;
extern int g_1040484;
extern int g_1040488;
extern int g_104048c;
extern char g_14cf950;
extern int g_774654;




int __cdecl fcn_0046e940(int, int, int, int, int);
int __cdecl io_AppendText(char*);
int __cdecl fcn_00472250(int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_0046f280(int);

void __cdecl fcn_0053a2f0(void)
{
	int w;
	int t;

	g_1040488 = 0;
	g_1040480 = 1;
	g_1040484 = 1;
	g_104048c = 2;
	w = fcn_0046e940(0x20, 0x60, 0x26c, 0x190, 0x15);
	t = fcn_00472250(-1, w, io_AppendText("$3ABetrag:%m"));
	d2_SetElementValue(t, 0, 0x2710, 0);
	while (fcn_005373e0((void*) fcn_0053a2f0, 0x24087) != 0) {
		if (g_14cf950 == 1) {
			g_774654 = 1;
		}
	}
	fcn_0046f280(w);
}
