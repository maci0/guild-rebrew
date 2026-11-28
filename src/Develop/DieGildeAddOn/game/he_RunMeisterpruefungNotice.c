

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6a5a10[];
extern char str_empty[];

int __cdecl gm_CompareGameTime(pos14_7f4c00*, char*);
int __cdecl d2_CreateActionPopupSlot(char*, int, int, char*, int);
void __cdecl he_FreeAction(char*);
void __cdecl d2_CloseActionPopup(char*);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_GetOppositeStatIndex(int);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl sb_FindBankByName(char*);
void __cdecl d3snd_QueueSound(int, int, char*, int, int);
int __cdecl io_AppendText(int, ...);
char* __cdecl gm_QueryEntities(int, int, int, int, int);
void __cdecl d2_EnterBuildingObjekt(char*, int, char*);

void __cdecl he_RunMeisterpruefungNotice(char* u)
{
	char* h;
	int lvl;
	int n;
	int r;
	int text;
	char* q;

	if (gm_CompareGameTime(&gm_GameTime, u + 0x52) < 0) {
		return;
	}
	switch (*(int*) (u + 0x70)) {
	case 0:
		d2_CreateActionPopupSlot(u, 0, 0, g_6a5a10, 0x5fd);
		if (*(char**) (u + 0x74) == 0) {
			he_FreeAction(u);
			return;
		}
		h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
		if (h != 0) {
			lvl = gm_GetOppositeStatIndex(*(unsigned char*) (h + 0x164)) + 1;
			text = h[9] ? 0x15ab : 0x159b;
			n = gm_MapEntityStatRange(*(unsigned char*) (h + 0x164));
			if (h[9] == 0) {
				if (n <= 0xc) {
					r = sb_FindBankByName("BERUF_TRAINING_SPIELER_MAENNLICH");
					d3snd_QueueSound(-8, r, "BERUF_TRAINING_SPIELER_MAENNLICH", n - 1, 0);
				} else {
					r = sb_FindBankByName("ADDON_BERUF_TRAINING_SPIELER_MAENNLICH");
					d3snd_QueueSound(-8, r, "BERUF_TRAINING_SPIELER_MAENNLICH", n - 0xd, 0);
				}
			} else if (n <= 0xc) {
				r = sb_FindBankByName("BERUF_TRAINING_SPIELER_WEIBLICH");
				d3snd_QueueSound(-8, r, "BERUF_TRAINING_SPIELER_WEIBLICH", n - 1, 0);
			} else {
				r = sb_FindBankByName("ADDON_BERUF_TRAINING_SPIELER_WEIBLICH");
				d3snd_QueueSound(-8, r, "BERUF_TRAINING_SPIELER_WEIBLICH", n - 0xd, 0);
			}
			io_AppendText(0x159a, *(unsigned short*) h, lvl + 0x1556, n + text, 4);
		}
		(*(int*) (u + 0x70))++;
		break;
	case 1:
		if (g_100f884 != *(int*) (*(char**) (u + 0x74) + 8) || d2_DialogButtonAction == -1) {
			break;
		}
		if (d2_DialogButtonAction == 2) {
			h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
			if (*(char**) (h + 0x170) != 0) {
				q = gm_QueryEntities(*(int*) (*(char**) (h + 0x170) + 0x5d), 2, 0, 0x13, 6);
				d2_EnterBuildingObjekt(*(char**) (h + 0x170), *(int*) (q + 2), str_empty);
			}
			d2_CloseActionPopup(u);
			he_FreeAction(u);
			return;
		} else if (d2_DialogButtonAction != 1) {
			break;
		}
	case -2:
	case -1:
		d2_CloseActionPopup(u);
		he_FreeAction(u);
		break;
	}
}
