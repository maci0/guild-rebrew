


extern int g_7746d8;
extern int g_7746a0;
extern int g_14b5b94;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_14ad0f8;
extern int g_14b5ab4;

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl fcn_0058d5f0(int);
void __cdecl d2_OpenTransportPanel(int);
void __cdecl d2_RunProduktionDialog(int);
void __cdecl d2_ShowLagerOptions(int, int);
void __cdecl d2_OpenMeisterbriefDialog(int);
void __cdecl d2_OpenBlutracheDialog(int);
void __cdecl d2_ShowPersonalbuch(int, char*);
void __cdecl d3_UpdateBuildingInteriorState(void);

void __cdecl d2_RunZigeunerInteriorHud(int a)
{
	int zig;
	int trans;
	int prod;
	int lager;
	int meister;
	int betteln;
	int personal;

	zig = 0;
	trans = 0;
	prod = 0;
	lager = 0;
	personal = 0;
	meister = 0;
	betteln = 0;
	fcn_005338a0();
	while (main_RunFrameLoop(d2_RunZigeunerInteriorHud, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			zig = RegisterStatusText("contact_ZUTATEN_SUCHEN_ZIGEUNER", g_14b5b94, 0x16);
			trans = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
			prod = RegisterStatusText("contact_PRODUKTION_ZIGEUNER", g_14ad0f8, 0x13);
			lager = RegisterStatusText("contact_LAGER", g_14ad0f0, 0xe);
			betteln = RegisterStatusText("contact_BETTELN", g_14b5ab4, 0x2c);
		}
		if (g_7746d8 & 0x400) {
			personal = RegisterStatusText("contact_PERSONALBUCH", g_14a7b50, 0xc);
			meister = RegisterStatusText("contact_MEISTERBRIEF", g_14a7d28, 0xc);
		}
		if (g_7746a0 != 0) {
			if (g_7746d8 & 0x200) {
				if (g_7746a0 == zig) {
					fcn_0058d5f0(a);
				} else if (g_7746a0 == trans) {
					d2_OpenTransportPanel(a);
				} else if (g_7746a0 == prod) {
					d2_RunProduktionDialog(a);
				} else if (g_7746a0 == lager) {
					d2_ShowLagerOptions(a, 0);
				} else if (g_7746a0 == meister) {
					d2_OpenMeisterbriefDialog(a);
				} else if (g_7746a0 == betteln) {
					d2_OpenBlutracheDialog(a);
				}
			}
			if (g_7746a0 == personal) {
				d2_ShowPersonalbuch(a, "ob_PERSONALBUCH");
			}
		}
		d3_UpdateBuildingInteriorState();
	}
}
