


#include <string.h>

// SIZE 0x50
typedef struct {
	int a;
	int size;
	__int64 cd;
	int kind;
	int f14;
	int pad18;
	int ids[8];
	int pad3c[5];
} Req;

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"









extern __int64 g_666018;
extern char* g_14a5590;

#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned char* __cdecl d2_OpenTargetPicker(Req*, char*, int, int);
unsigned char* __cdecl gm_LookupEntityRecordById(int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
float __cdecl fcn_004ff210(unsigned short, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
void __cdecl fcn_005dbe90(char*);

int __cdecl gm_ObjDisruptTargetRivals(ENTITY_RECORD* obj, int* arg)
{
	ENTITY_RECORD* picks[3];
	Req req;
	char text[0x800];
	char text2[0x200];
	ENTITY_RECORD* e;
	int start;
	int step;
	int n;
	int i;

	if (obj->entity_state == 6) {
		memset(&req, 0, sizeof(req));
		memset(req.ids, 0xff, sizeof(req.ids));
		req.f14 = 3;
		req.size = 0x400;
		req.kind = 6;
		req.cd = g_666018;
		e = (ENTITY_RECORD*) d2_OpenTargetPicker(&req, g_14a5590, 0, 0);
		if (e == 0) {
			return 0;
		}
	} else {
		e = (ENTITY_RECORD*) gm_LookupEntityRecordById(arg[1]);
		if (e == 0) {
			return 0;
		}
	}
	start = gm_RandomMod(0x300);
	step = gm_RandomSearchSteps[gm_RandomMod(0x10)];
	n = 3;
	do {
		if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[start].entity_index != 0xffff && ((ENTITY_RECORD_VIEW*)g_7f4ca0)[start].class_166 && ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[start]) != obj &&
			((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[start]) != e) {
			n--;
			picks[n] = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[start]);
		}
		start = (start + step) % 0x300;
	} while (n != 0);
	for (i = 0; i < 3; i++) {
		cm_RequestCopyEntityData(e->entity_id, picks[i]->entity_id, gm_RandomMod(0x20) + 0x14, 1);
	}
	fcn_004ff210(e->entity_index, -0x32 - gm_RandomMod(0x40));
	if (e->entity_state == 6 || e->entity_state == 7) {
		io_FormatTextBuffer(text, 0x100d, picks[0]->entity_index, picks[0]->entity_index, picks[1]->entity_index, picks[2]->entity_index);
		he_PostEntityMessage(e->entity_id, -1, text, 1, 0x5fb, 0);
	}
	if (picks[0]->entity_state == 6 || picks[0]->entity_state == 7) {
		io_FormatTextBuffer(text, 0x100e, e->entity_index, picks[1]->entity_index, picks[2]->entity_index);
		he_PostEntityMessage(picks[0]->entity_id, -1, text, 1, 0x5fb, 0);
	}
	if (picks[1]->entity_state == 6 || picks[1]->entity_state == 7) {
		io_FormatTextBuffer(text, 0x100f, e->entity_index, picks[0]->entity_index, picks[2]->entity_index);
		he_PostEntityMessage(picks[1]->entity_id, -1, text, 1, 0x5fb, 0);
	}
	if (picks[2]->entity_state == 6 || picks[2]->entity_state == 7) {
		io_FormatTextBuffer(text, 0x100f, e->entity_index, picks[0]->entity_index, picks[1]->entity_index);
		he_PostEntityMessage(picks[2]->entity_id, -1, text, 1, 0x5fb, 0);
	}
	arg[4] = 1;
	if (obj->entity_state == 6) {
		io_FormatTextBuffer(text2, 0x10a1, e->entity_index, picks[0]->entity_index, picks[1]->entity_index, picks[2]->entity_index);
		io_FormatTextBuffer(text, 0xfe8, text2);
		fcn_005dbe90(text);
	}
	return 1;
}
