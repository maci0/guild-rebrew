


extern int g_7746d8;
extern int g_14ad0f8;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14ad0e8;
extern int g_7746a0;

void __cdecl fcn_0057e880(int, char*, int, int);
void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_0059a0e0(void);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl fcn_0059c000(char*);
void __cdecl fcn_005c5b10(char*);
void __cdecl fcn_005c79a0(char*);

void __cdecl fcn_0059c800(char* e)
{
	int d;
	int g;
	int f;
	int a;
	int b;
	int c;

	a = 0;
	c = 0;
	b = 0;
	d = 0;
	f = 0;
	g = 0;
	fcn_0057e880(0x1b, e, 0, 0);
	fcn_005338a0();
	while (fcn_005373e0((void*) fcn_0059c800, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			a = RegisterStatusText("contact_PRODUKTION_METALL", g_14ad0f8, 0x13);
			b = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
			c = RegisterStatusText("contact_LAGER", g_14ad0f0, 0xe);
			d = RegisterStatusText("contact_GELAGE", g_14ad0e8, 0x16);
			if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x35) != 0) {
				f = RegisterStatusText("ob_STROHPUPPE", g_14abc30, 0x17);
			}
			if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x34) != 0) {
				g = RegisterStatusText("ob_ZIELSCHEIBE", g_14abc2c, 0x17);
			}
		}
		fcn_0059a0e0();
		if (g_7746a0 != 0) {
			if (g_7746a0 == b) {
				d2_OpenTransportPanel(e);
			} else if (g_7746a0 == c) {
				d2_ShowLagerOptions(e, 0);
			} else if (g_7746a0 == a) {
				fcn_0059c000(e);
			} else if (g_7746a0 == d) {
				fcn_005c5b10(e);
			} else if (g_7746a0 == g || g_7746a0 == f) {
				fcn_005c79a0(e);
			}
		}
	}
	fcn_0057e880(0x1c, e, 0, 0);
}
