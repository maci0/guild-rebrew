


extern int d2_SelectedEntityUiFlags;
extern int g_14ab954;
extern int g_14ab8f4;
extern int g_14ab918;
extern int g_14ab934;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int sv_ClickedObjekt;
extern char io_LastKeyScancode;
extern int gm_AllEntitiesControllable;

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(char*, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl d2_RunChurchSermonDialog(char*);
void __cdecl d2_RunTaufeDialog(char*, int);
void __cdecl d2_OpenBeichteDialog(char*);
void __cdecl d2_RunKircheSpendenDialog(char*);

void __cdecl d2_RunKircheMenu(char* e, int msg)
{
	int predigt;
	int weih;
	int beicht;
	int spende;

	beicht = 0;
	spende = 0;
	predigt = 0;
	weih = 0;
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop((void*) d2_RunKircheMenu, 0x67fff) != 0) {
		if (d2_SelectedEntityUiFlags & 0x200) {
			predigt = RegisterStatusText("contact_PREDIGT", g_14ab954, 0x16);
			weih = RegisterStatusText("ob_WEIHWASSERBECKEN", g_14ab8f4, 0x16);
		}
		if (*(unsigned short*) (e + 0x27) != gm_LocalPlayerSlot && *(unsigned short*) (e + 0x27) != 0xffff) {
			if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0xf2) != 0) {
				beicht = RegisterStatusText("ob_KIRCHE_BEICHTSTUHLRAUM", g_14ab918, 0x16);
			} else {
				beicht = 0;
			}
			spende = RegisterStatusText("ob_SPENDENKAESTCHEN", g_14ab934, 0x16);
			weih = RegisterStatusText("ob_WEIHWASSERBECKEN", g_14ab8f4, 0x16);
		}
		if (sv_ClickedObjekt != 0) {
			if (d2_SelectedEntityUiFlags & 0x200) {
				if (sv_ClickedObjekt == predigt) {
					d2_RunChurchSermonDialog(e);
				} else if (sv_ClickedObjekt == weih) {
					d2_RunTaufeDialog(e, msg);
				}
			}
			if (*(unsigned short*) (e + 0x27) != gm_LocalPlayerSlot) {
				if (sv_ClickedObjekt == beicht) {
					d2_OpenBeichteDialog(e);
				}
				if (sv_ClickedObjekt == spende) {
					d2_RunKircheSpendenDialog(e);
				}
				if (sv_ClickedObjekt == weih) {
					d2_RunTaufeDialog(e, msg);
				}
			}
		} else if (io_LastKeyScancode == 0x30 && gm_AllEntitiesControllable != 0) {
			d2_OpenBeichteDialog(e);
		}
	}
}
