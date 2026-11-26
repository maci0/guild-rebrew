


#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
extern int g_7746d8;
extern int g_7746a0;
extern int g_14b5458;
extern int g_14ad0f8;
extern int g_14b5400;
extern int g_14b53fc;
extern int g_14b59d0[];

void __cdecl fcn_005338a0(void);
int __cdecl main_RunFrameLoop(void (__cdecl*)(char*, char*), int);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_OpenTransportPanel(char*);
void __cdecl d2_ShowLagerOptions(char*, int);
void __cdecl d2_RunDomizilKabinettDialog(char*, char*);
int __cdecl he_GetActionProgress(char*, int*, int*, int);
void __cdecl fcn_00526120(int, int);
void __cdecl fcn_005944d0(char*);
#ifdef REBREW_GOLD
#define fcn_00585030 fcn_0057c950
#endif

void __cdecl fcn_00585030(char*);
void __cdecl fcn_00585910(char*);
void __cdecl d2_RunAlchemyDialog(char*);

void __cdecl d2_RunAlchemistMenu(char* a, char* b)
{
	int book;
	int alch;
	int x;
	int y;
	int contract;
	int store;
	int transport;
	int alchcontract;
	int r;

	contract = 0;
	store = 0;
	transport = 0;
	book = 0;
	alchcontract = 0;
	alch = 0;
	fcn_005338a0();
	while (main_RunFrameLoop(d2_RunAlchemistMenu, 0x67fff) != 0) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_7746d8 & 0x200) {
			alch = RegisterStatusText("contact_REZEPTBUCH", g_14b5458, 0x16);
			book = RegisterStatusText("contact_PRODUKTION_ALCHIMIST", g_14ad0f8, 0x13);
		}
		if (g_7746d8 & 0x400) {
			contract = RegisterStatusText("contact_CONTRACT", g_14b5400, 0xe);
			store = RegisterStatusText("contact_LAGER", g_14ad0f0, 0xe);
			transport = RegisterStatusText("contact_TRANSPORT", g_14ad100, 0x15);
			alchcontract = RegisterStatusText("contact_ALCHIMISTENVERTRAG", g_14b53fc, 0x16);
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == transport) {
				d2_OpenTransportPanel(a);
			} else if (g_7746a0 == store) {
				d2_ShowLagerOptions(a, *(int*) (a + 0x5d));
			} else if (*(int*) (b + 0x1c) != 0) {
				d2_RunDomizilKabinettDialog(a, b);
			} else if (g_7746a0 == book) {
				r = he_GetActionProgress(a, &y, &x, 0);
				if (r != 0) {
					fcn_00526120(g_14b59d0[r], 0x100);
				} else {
					fcn_005944d0(a);
				}
			} else if (g_7746a0 == alch) {
				fcn_00585030(a);
			} else if (g_7746a0 == alchcontract) {
				fcn_00585910(a);
			} else if (g_7746a0 == contract) {
				d2_RunAlchemyDialog(a);
			}
		}
	}
}
