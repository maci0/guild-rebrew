


#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_14ad0e0;
extern int g_14ad210;
extern int g_14ad1c8;
extern int g_14ad280;
extern int g_14ad218;
extern int sv_ClickedObjekt;

int __cdecl d3_FindSceneObject(int, int, int, char*);
int __cdecl RegisterStatusText(char*, int, int);
void __cdecl d2_OpenTransportPanel(char*);

/* ADDRESS: GOLDDE 0x0057d670 */
void __cdecl d2_OpenContactEinkaufPanel(char* e)
{
	int r;

	r = 0;
	if (gm_LocalPlayerSlot != *(unsigned short*) (e + 0x27)) {
		if (d3_FindSceneObject(0, 0x60, 0, "contact_EINKAUF")) {
			r = RegisterStatusText("contact_EINKAUF", g_14ad0e0, 0x10);
		} else if (d3_FindSceneObject(0, 0x60, 0, "contact_EINKAUF_METALL")) {
			r = RegisterStatusText("contact_EINKAUF_METALL", g_14ad210, 0x10);
		} else if (d3_FindSceneObject(0, 0x60, 0, "contact_EINKAUF_SKRIPTE")) {
			r = RegisterStatusText("contact_EINKAUF_SKRIPTE", g_14ad1c8, 0x10);
		} else if (d3_FindSceneObject(0, 0x60, 0, "contact_EINKAUF_HOLZ")) {
			r = RegisterStatusText("contact_EINKAUF_HOLZ", g_14ad280, 0x10);
		} else if (d3_FindSceneObject(0, 0x60, 0, "contact_EINKAUF_STEIN")) {
			r = RegisterStatusText("contact_EINKAUF_STEIN", g_14ad218, 0x10);
		}
	}
	if (gm_LocalPlayerSlot != *(unsigned short*) (e + 0x27) && sv_ClickedObjekt != 0 && sv_ClickedObjekt == r) {
		d2_OpenTransportPanel(e);
	}
}
