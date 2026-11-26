


extern int g_7746d8;
extern int g_14ad1d8;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_7746a0;

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl fcn_00597ec0(char*);
void __cdecl d2_RunProduktionDialog(char*);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl d2_ShowPersonalbuch(char*, char*);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl d2_OpenMeisterbriefDialog(char*);

void __cdecl d2_RunSchreibstubeMenu(char* e)
{
	int meister;
	int lager;
	int prod;
	int personal;
	int transport;

	meister = 0;
	lager = 0;
	prod = 0;
	personal = 0;
	transport = 0;
	fcn_005338a0();
	while (main_RunFrameLoop((void*) d2_RunSchreibstubeMenu, 0x67fff) != 0) {
		fcn_00597ec0(e);
		if (g_7746d8 & 0x200) {
			prod = RegisterStatusText("contact_PRODUKTION_SCHREIBEN", g_14ad1d8, 0x13);
			lager = RegisterStatusText("contact_LAGER", g_14ad0f0, 0xe);
			transport = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
			personal = RegisterStatusText("ob_PERSONALBUCH", g_14a7b50, 0xc);
			meister = RegisterStatusText("ob_MEISTERBRIEF", g_14a7d28, 0xc);
		}
		if (g_7746a0 != 0 && (g_7746d8 & 0x200)) {
			if (g_7746a0 == personal) {
				d2_ShowPersonalbuch(e, "ob_PERSONALBUCH");
			} else if (g_7746a0 == lager) {
				d2_ShowLagerOptions(e, *(int*) (e + 0x5d));
			} else if (g_7746a0 == prod) {
				d2_RunProduktionDialog(e);
			} else if (g_7746a0 == transport) {
				d2_OpenTransportPanel(e);
			} else if (g_7746a0 == meister) {
				d2_OpenMeisterbriefDialog(e);
			}
		}
	}
}
