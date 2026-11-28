#include <string.h>
#pragma intrinsic(strcpy)
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char gm_EntitySlotTable[];
extern char gm_InWorldHud;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_DialogButtonAction;
extern int g_100f884;
extern char g_7749e8;
extern int tp_d2_ActiveHudSlot;

int __cdecl d2_CreateActionPopupSlot(char*, short, short, char*, int);
void __cdecl d2_CloseActionPopup(char*);
void __cdecl he_FreeAction(char*);
char* __cdecl gm_LookupEntityRecordById(int);
int* __cdecl d3snd_QueueSound(int, int, char*, int, int);
void __cdecl d2_CenterDialogWindows(int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl gm_CompareGameTime(void*, void*);

/* ADDRESS: GOLDTL 0x0055b020 */
void __cdecl d2_ShowTitleAward(char* o)
{
	short* slot;
	char* g;
	char buf[0x200];
	int state;
	int st;
	int code;
	int kind;
	int end;
	int id;

	slot = (short*) ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*)(o + 8)]);
	if (gm_LocalPlayerSlot != *(unsigned short*) (o + 8))
		return;
	if (gm_InWorldHud == 0)
		return;
	if (gm_CompareGameTime(o + 0x52, (void*) 0x7f4c00) == 1)
		return;
	g = gm_LookupEntityRecordById(*(int*) (o + 0xbc));
	state = *(int*) (o + 0x70);
	if (state == -2 || state == -1 || *slot == -1 || g == 0) {
		if (*(int*) (o + 0x74))
			d2_CloseActionPopup(o);
		he_FreeAction(o);
		return;
	}
	if (state != 0) {
		if (state != 1)
			return;
		id = *(int*) (o + 0x74);
		if (id == 0) {
			*(int*) (o + 0x70) = 0;
			return;
		}
		if (g_100f884 != *(int*) (id + 8) && g_7749e8 == 0)
			return;
		if (d2_DialogButtonAction == 2) {
			d2_CloseActionPopup(o);
			he_FreeAction(o);
			return;
		}
		if (g_7749e8 == 0)
			return;
		if (tp_d2_ActiveHudSlot != id)
			return;
		g_7749e8 = 0;
		d2_CloseActionPopup(o);
		he_FreeAction(o);
		return;
	}
	if (*(int*) (o + 0x74) == 0) {
		if (g == (char*) slot)
			d2_CreateActionPopupSlot(o, 0, 0, "SPECIAL\\TITEL", 0x5fd);
		else
			d2_CreateActionPopupSlot(o, 0, 0, "SPECIAL\\TITEL_ANDERE", 0x5fe);
	}
	if (*(int*) (o + 0x74) == 0) {
		he_FreeAction(o);
		return;
	}
	d2_CenterDialogWindows(*(int*) (*(int*) (o + 0x74) + 8));
	d2_SetForm(*(int*) (*(int*) (o + 0x74) + 8), 1);
	if (g == (char*) slot) {
		kind = 0;
		if (*(char*) (g + 0xd) == 9) {
			code = 0x42a9;
			if (*(char*) (g + 9) == 1)
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_W_02");
			else
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_M_02");
		} else if (*(char*) (g + 0xd) == 8) {
			code = 0x42a7;
			if (*(char*) (g + 9) == 1)
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_W_01");
			else
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_M_01");
		} else {
			code = 0x42a5;
			if (*(char*) (g + 9) == 1)
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_W_00");
			else
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_M_00");
		}
		if (*(char*) (g + 9) == 1)
			code += 1;
		d3snd_QueueSound(-7, 0, "FanfarePositivHeldenhaftLang", 0, 100);
		d3snd_QueueSound(-7, 0, buf, 0, 100);
		if (*(int*) (o + 0xc0) == 0x25) {
			kind = 0x42ab;
			if (*(char*) (g + 9) == 1)
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_WEIBLICH_HS_00");
			else
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_MAENNLICH_HS_00");
		} else if (*(int*) (o + 0xc0) == 0x24) {
			kind = 0x42af;
			if (*(char*) (g + 9) == 1)
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_WEIBLICH_HS_02");
			else
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_MAENNLICH_HS_02");
		} else if (*(int*) (o + 0xc0) == 0x23) {
			kind = 0x42ad;
			if (*(char*) (g + 9) == 1)
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_WEIBLICH_HS_01");
			else
				strcpy(buf, "_VERLEIHUNG_REICHSAMT_MAENNLICH_HS_01");
		}
		d3snd_QueueSound(-7, 0, buf, 0, 100);
		d3snd_QueueSound(-7, 0, "MausclickLinks_s_01", -1, 0);
		if (*(char*) (g + 9) == 0)
			end = 0x253;
		else
			end = *(int*) (o + 0xc0) + 0x27b;
		io_AppendText(kind, code, (int) (o + 0xac), end);
	} else {
		st = *(int*) (o + 0xc0);
		kind = 0;
		if (st == 0x25)
			kind = 0x42ac;
		else if (st == 0x24)
			kind = 0x42b0;
		else if (st == 0x23)
			kind = 0x42ae;
		if (*(char*) (g + 9) == 0)
			end = 0x253;
		else
			end = st + 0x27b;
		io_AppendText(kind, *(unsigned short*) g, end);
	}
	d2_SetForm(*(int*) (*(int*) (o + 0x74) + 8), 2);
	io_AppendText(0x161c);
	*(int*) (o + 0x70) = 1;
}
