extern int g_100f884; extern char g_7749e8;
extern unsigned char** g_7749e4;
#include <stdio.h>

#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_774964;
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl gm_CompareGameTime(void*, void*);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_MapEntityStatRange(int);
int __cdecl gm_GetOppositeStatIndex(int);
void __cdecl fcn_00545670(char*, int, int, char*, int);
void __cdecl he_FreeAction(char*);
void __cdecl d2_SetForm(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl io_AppendText(int, ...);
void __cdecl cm_RequestSetEntityLevel(int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
int __cdecl sb_FindBankByName(char*);
void __cdecl d3snd_QueueSound(int, int, char*, int, int);
void __cdecl fcn_00545780(int);

/* ADDRESS: GOLDTL 0x00565350 */
void __cdecl he_RunMeisterpruefungPassed(int action)
{
	unsigned char* ent;
	char* p;
	int* slot;
	char buf[1024];
	char name[64];
	int x;
	int y;
	int z;
	char kind;
	int v;
	int statIndex;
	int v7;
	int v8;
	int v9;

	if (g_774970 != *(unsigned short*) (action + 8))
		return;
	if (!g_774964)
		return;
	if (0 < gm_CompareGameTime((void*) (action + 0x44), (void*) 0x7f4c00))
		return;
	if (!*(unsigned char*) (action + 0xb1)) {
		v = gm_LookupEntityRecordById(*(unsigned int*) (action + 0xac));
		if (v) {
			*(unsigned char*) (action + 0xb0) = *(char*) (v + 0x164);
			*(unsigned char*) (action + 0xb1) = *(char*) (v + 0x164) - 1;
		}
	}
	switch (*(int*) (action + 0x70)) {
	case 0:
		fcn_00545670((char*) action, 0, 0, "Berufe\\Meisterpruefung_BESTANDEN", 0x5ec);
		if (!*(int*) (action + 0x74)) {
			he_FreeAction((char*) action);
			return;
		}
		d2_SetForm(*(int*) (*(int*) (action + 0x74) + 8), 0);
		d2_CenterDialogWindows(*(int*) (*(int*) (action + 0x74) + 8));
		ent = (unsigned char*) gm_LookupEntityRecordById(*(unsigned int*) (action + 0xac));
		y = *(unsigned char*) (ent + 9) ? 0x18f : 0x130;
		x = gm_MapEntityStatRange(*(unsigned char*) (action + 0xb0));
		z = gm_GetOppositeStatIndex(*(unsigned char*) (action + 0xb0)) + 1;
		d2_SetForm(*(int*) (*(int*) (action + 0x74) + 8), 1);
		io_AppendText(0x15c3, g_773d75 * 0x2f4 + (int) 0x868080, (int) 0x7f4c00,
			*(unsigned char*) (action + 0xb1) + y, (int) ((float) ((z - 1) * 0.5) + (3 * x + 0x155a)), x + 0x158a);
		cm_RequestSetEntityLevel(*(int*) (ent + 4), *(unsigned char*) (action + 0xb1));
		kind = *(char*) (ent + 2);
		if (kind == 6 || kind == 7 || kind == 5) {
			io_FormatTextBuffer(buf, 0x1c1f, *(unsigned short*) ent,
				*(unsigned char*) (action + 0xb0) + y, *(unsigned char*) (action + 0xb1) + y);
			p = (char*) 0x7f4ca4; do {
				kind = *(char*) (p - 2);
				if ((kind == 6 || kind == 7) && *(int*) p != *(int*) (ent + 4))
					he_PostEntityMessage(*(int*) p, -1, buf, 0, 0x5fe, 0);
			} while (p += 0x21c, (int) p < 0x85a0a4);
			*(unsigned int*) (ent + 0x1c8) &= 0x7fffffff;
		}
		*(int*) (action + 0x70) = *(int*) (action + 0x70) + 1;
		return;
	case 1:
		ent = (unsigned char*) gm_LookupEntityRecordById(*(unsigned int*) (action + 0xac));
		x = gm_MapEntityStatRange(*(unsigned char*) (action + 0xb0));
		statIndex = gm_GetOppositeStatIndex(*(unsigned char*) (action + 0xb0)) + 1;
		sprintf(name, "brk_%02i", x);
		v7 = sb_FindBankByName("BERUF_BESTANDEN");
		if (x > 12) {
			if (!*(char*) (ent + 9))
				v = sb_FindBankByName("ADDON_BERUF_LISTE_MAENNLICH");
			else
				v = sb_FindBankByName("ADDON_BERUF_LISTE_WEIBLICH");
			v8 = sb_FindBankByName("ADDON_GEBAEUDE_LISTE");
			v9 = sb_FindBankByName("ADDON_BERUFE_VEREINIGUNG_UNTERSCHRIFT");
		} else {
			if (!*(char*) (ent + 9))
				v = sb_FindBankByName("BERUF_LISTE_MAENNLICH");
			else
				v = sb_FindBankByName("BERUF_LISTE_WEIBLICH");
			v8 = sb_FindBankByName("GEBAEUDE_LISTE");
			v9 = sb_FindBankByName("BERUFE_VEREINIGUNG_UNTERSCHRIFT");
		}
		if (statIndex < 3)
			d3snd_QueueSound(-7, 0, "FanfarePositivKurz", -1, 0);
		else if (statIndex < 5)
			d3snd_QueueSound(-7, 0, "FanfarePositivMittel", -1, 0);
		else
			d3snd_QueueSound(-7, 0, "FanfarePositivLang", -1, 0);
		d3snd_QueueSound(-6, v7, "SELBST", 1, 0);
		d3snd_QueueSound(-8, v, name, statIndex - 2, 0);
		d3snd_QueueSound(-6, v7, "SELBST", 0, 0);
		statIndex--;
		d3snd_QueueSound(-8, v8, name, (int) (3.0 - ((double) statIndex + 1.0) * 0.5), 0);
		d3snd_QueueSound(-6, v7, "GEZEICHNET", -1, 0);
		d3snd_QueueSound(-8, v9, "_BERUFE_VEREINIGUNG_UNTERSCHRIFT", x > 12 ? x - 13 : x - 1, 0);
		d3snd_QueueSound(-7, 0, "MausclickLinks_s_01", -1, 0);
		*(int*) (action + 0x70) = *(int*) (action + 0x70) + 1;
		return;
	case 2:
		break;
	case 0xfffffffe:
	case 0xffffffff:
		fcn_00545780(action);
		he_FreeAction((char*) action);
		return;
	default:
		return;
	}
	slot = (int*) *(int*) (action + 0x74);
	if (!slot) {
		*(unsigned int*) (action + 0x70) = 0;
		return;
	}
	if (g_100f884 != slot[2]) {
		if (!g_7749e8)
			return;
		if ((int) g_7749e4 != (int) slot)
			return;
	}
	if (g_100f1dc == -1) {
		if (!g_7749e8)
			return;
		if ((int) g_7749e4 != (int) slot)
			return;
	} else {
		if (g_100f1dc == 2) {
			fcn_00545780(action);
			he_FreeAction((char*) action);
			return;
		}
		if (g_100f1dc == 1) {
			fcn_00545780(action);
			he_FreeAction((char*) action);
			g_7749e8 = 0;
			return;
		}
	}
	if (!g_7749e8)
		return;
	fcn_00545780(action);
	he_FreeAction((char*) action);
	g_7749e8 = 0;
}
