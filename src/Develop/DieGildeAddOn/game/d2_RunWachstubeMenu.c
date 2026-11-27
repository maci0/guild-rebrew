


extern int g_7746d8;
extern int g_14ad118;
extern int g_14ad168;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_7746a0;
extern char* g_7746cc;

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl d2_RunEquipmentDialog(char*);
void __cdecl d2_RunWorkerTrainingDialog(char*);

void __cdecl d2_RunWachstubeMenu(char* e)
{
	int lager;
	int transport;
	int ausruesten;
	int regen;

	lager = 0;
	transport = 0;
	ausruesten = 0;
	regen = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop((void*) d2_RunWachstubeMenu, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			ausruesten = RegisterStatusText("contact_AUSRUESTEN", g_14ad118, 0xd);
			regen = RegisterStatusText("contact_REGENERATION", g_14ad168, 0x17);
		}
		if (g_7746d8 & 0x400) {
			lager = RegisterStatusText("contact_LAGER", g_14ad0f0, 0xe);
			transport = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == lager) {
				d2_ShowLagerOptions(e, *(int*) (g_7746cc + 0x14));
			} else if (g_7746a0 == transport) {
				d2_OpenTransportPanel(e);
			} else if (g_7746a0 == ausruesten) {
				d2_RunEquipmentDialog(e);
			} else if (g_7746a0 == regen) {
				d2_RunWorkerTrainingDialog(e);
			}
		}
	}
}
