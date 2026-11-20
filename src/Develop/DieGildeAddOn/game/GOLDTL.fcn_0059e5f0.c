


extern int g_7746d8;
extern int g_14ad278;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_7746a0;

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl fcn_00597ec0(char*);
void __cdecl fcn_005944d0(char*);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl d2_ShowPersonalbuch(char*, char*);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl fcn_005cf560(char*);

void __cdecl fcn_0059e5f0(char* e)
{
	int prod;
	int lager;
	int transport;
	int meister;
	int personal;

	meister = 0;
	lager = 0;
	prod = 0;
	transport = 0;
	personal = 0;
	fcn_005338a0();
	while (fcn_005373e0((void*) fcn_0059e5f0, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			prod = RegisterStatusText("contact_PRODUKTION_TISCHLER", g_14ad278, 0x13);
		}
		if (g_7746d8 & 0x400) {
			lager = RegisterStatusText("contact_LAGER", g_14ad0f0, 0xe);
			transport = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
			meister = RegisterStatusText("ob_MEISTERBRIEF", g_14a7d28, 0xc);
			personal = RegisterStatusText("ob_PERSONALBUCH", g_14a7b50, 0xc);
		}
		fcn_00597ec0(e);
		if (g_7746a0 != 0) {
			if (g_7746a0 == prod) {
				fcn_005944d0(e);
			} else if (g_7746a0 == transport) {
				d2_OpenTransportPanel(e);
			} else if (g_7746a0 == personal) {
				d2_ShowPersonalbuch(e, "ob_PERSONALBUCH");
			} else if (g_7746a0 == lager) {
				d2_ShowLagerOptions(e, *(int*) (e + 0x5d));
			} else if (g_7746a0 == meister) {
				fcn_005cf560(e);
			}
		}
	}
}
