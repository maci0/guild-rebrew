


extern int g_7746d8;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14ad288;
extern int g_14ad0e8;
extern int g_7746a0;
extern int g_6a25f0;

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl fcn_0059a0e0(void);
void __cdecl d2_HandleErnten(char*, int);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl fcn_0059c000(char*);
void __cdecl fcn_005c5b10(char*);
void __cdecl fcn_005c79a0(char*);
void __cdecl ob_HandleBepflanzung(char*);

void __cdecl fcn_0059c9a0(char* e)
{
	int zs;
	int sp;
	int x;
	int lager;
	int holz;
	int gelage;
	int transport;

	lager = 0;
	transport = 0;
	holz = 0;
	gelage = 0;
	sp = 0;
	zs = 0;
	fcn_005338a0();
	x = *(int*) (e + 0x71);
	while (main_RunFrameLoop((void*) fcn_0059c9a0, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			lager = RegisterStatusText("contact_LAGER", g_14ad0f0, 0xe);
			holz = RegisterStatusText("contact_PRODUKTION_HOLZ", g_14ad288, 0x13);
			gelage = RegisterStatusText("contact_GELAGE", g_14ad0e8, 0x16);
			transport = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
			zs = RegisterStatusText("ob_ZIELSCHEIBE", g_14abc2c, 0xc);
			sp = RegisterStatusText("ob_STROHPUPPE", g_14abc30, 0xc);
		}
		fcn_0059a0e0();
		d2_HandleErnten(e, x);
		if (g_7746a0 != 0) {
			if (g_7746a0 == transport) {
				d2_OpenTransportPanel(e);
			} else if (g_7746a0 == lager) {
				d2_ShowLagerOptions(e, *(int*) (e + 0x5d));
			} else if (g_7746a0 == holz) {
				fcn_0059c000(e);
			} else if (g_7746a0 == gelage) {
				fcn_005c5b10(e);
			} else if (g_7746a0 == zs) {
				fcn_005c79a0(e);
			} else if (g_7746a0 == sp) {
				fcn_005c79a0(e);
			}
		}
		if (g_100f1dc != -1 && d2_CurrentElementId == g_6a25f0) {
			ob_HandleBepflanzung(e);
		}
	}
}
