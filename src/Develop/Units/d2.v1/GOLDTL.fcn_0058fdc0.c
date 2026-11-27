extern int g_7746d8;
extern int g_14b5874;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_7746a0;

extern char g_6a9934[];
extern char g_6a956c[];
extern char g_6a9924[];
extern char g_6a9914[];
extern char g_6a9580[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d3_TriggerFriedhofChatScript(char*);
void __cdecl he_DispatchEntityInteractReturn(char*);
void __cdecl d2_RunProduktionDialog(char*);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl d2_RunPersonalbuchDialog(char*, char*);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl d2_OpenMeisterbriefDialog(char*);

/* ADDRESS: GOLDTL 0x0058fdc0 */
void __cdecl fcn_0058fdc0(char* e)
{
	int r1;
	int r2;
	int r3;
	int r4;
	int r5;

	r1 = 0;
	r2 = 0;
	r3 = 0;
	r4 = 0;
	r5 = 0;
	fcn_005338a0();
	while (main_RunFrameLoop((void*) fcn_0058fdc0, 0x67fff) != 0) {
		d3_TriggerFriedhofChatScript(e);
		if (g_7746d8 & 0x200) {
			r1 = RegisterStatusText(g_6a9934, g_14b5874, 0x13);
			r2 = RegisterStatusText(g_6a956c, g_14ad100, 0x15);
			r3 = RegisterStatusText(g_6a9924, g_14a7d28, 0xc);
			r4 = RegisterStatusText(g_6a9914, g_14a7b50, 0xc);
			r5 = RegisterStatusText(g_6a9580, g_14ad0f0, 0xe);
			he_DispatchEntityInteractReturn(e);
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == r1) {
				d2_RunProduktionDialog(e);
			} else if (g_7746a0 == r2) {
				d2_OpenTransportPanel(e);
			} else if (g_7746a0 == r3) {
				d2_OpenMeisterbriefDialog(e);
			} else if (g_7746a0 == r4) {
				d2_RunPersonalbuchDialog(e, g_6a9914);
			} else if (g_7746a0 == r5) {
				d2_ShowLagerOptions(e, *(int*) (e + 0x5d));
			}
		}
	}
}
