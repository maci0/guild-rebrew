#include "client_types.h"








typedef struct Place579 {
	char pad0[8];
	unsigned short idx;      /* 0x08 */
	char padA[2];
	int xc;                  /* 0x0c */
	int x10;                 /* 0x10 */
	char pad14[0x52 - 0x14];
	pos14_7f4c00 pos52;             /* 0x52 */
	char pad60[0x70 - 0x60];
	int status;              /* 0x70 */
	char pad74[0x8c - 0x74];
	int x8c;                 /* 0x8c */
	char pad90[0xac - 0x90];
	float add;               /* 0xac */
	int xb0;                 /* 0xb0 */
	unsigned char xb4;       /* 0xb4 */
	char padb5[0xb8 - 0xb5];
	int xb8;                 /* 0xb8 */
	pos14_7f4c00 posBC;             /* 0xbc */
} Place579;

extern pos14_7f4c00 gm_GameTime;
extern char g_7f4ca0[];
extern float g_696540[];
extern float g_696550[];

int __cdecl gm_GetSeason(int* pos);
void __cdecl gm_AddTime(pos14_7f4c00* pos, int a, int b, int c);
char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl fcn_00529160(int a, int b, int id, int d);
void* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);
char* __cdecl gv_GetSlotEntry(int a, int b, unsigned char c);
int __cdecl gm_GetElapsedMinutes(pos14_7f4c00* a, pos14_7f4c00* b);

int __cdecl fcn_004f2d30(char* p, int a, int b, int c);
char* __cdecl fcn_0050dc90(char* p);
void __cdecl io_FormatTextBuffer(char* buf, int a, int b, int c, char* p);
void __cdecl he_MessageBoxQuickjump(int a, int b, char* text, int c, int d, int e,
	int f, int g, char* fmt);
void __cdecl he_FreeAction(char* a0);

/* Placement step for the transport/warehouse action: validates the current
   map cell, advances the hauled amount along the way, places the icon and
   reports the action text. */
/* ADDRESS: GOLDTL 0x00579de0 */
void __cdecl he_RunGrabpflege(char* a0)
{
	Place579* place;
	char text[1024];
	char* entity;
	char* slot;
	char* fig;
	char* rec;
	int win;
	int value;
	int v;
	int row;
	float f;

	win = gm_GetSeason((int*) &gm_GameTime);
	value = *(int*) &gm_GameTime.b & 0xffff;
	if (((float) value >= g_696550[win] || (float) value < g_696540[win])
		&& ((Place579*) a0)->status != -1
		&& ((Place579*) a0)->status != -2) {
		((Place579*) a0)->posBC = gm_GameTime;
		gm_AddTime(&((Place579*) a0)->pos52, 0, 5, 0);
		return;
	}
	place = (Place579*) a0;
	if (place->idx == 0xffff || place->xc == -1) {
		goto end;
	}
	entity = gm_LookupEntityRecordById(place->x8c);
	if (entity) {
		fcn_00529160(0, 0, *(unsigned short*) entity, (int) place);
	} else {
		place->status = -1;
	}
	rec = (char*) gm_StartFilteredEntitySearch(1, 1, place->x10);
	if (!rec) {
		place->status = -1;
	}
	slot = gv_GetSlotEntry(*(int*) (rec + 0x65), place->xb0, place->xb4);
	if (!slot) {
		place->status = -1;
	}
	if (place->status == 0) {
		v = gm_GetElapsedMinutes(&place->posBC, &gm_GameTime);
		f = (float) (4 - *(int*) slot) * v * *(float*) 0x662a3c;
		if ((entity[0x165] == 0x1b || entity[0x165] == 0x1c)
			&& (*(unsigned char*) (entity + 0x1b4) & 1)) {
			f *= *(float*) 0x6628bc;
		}
		place->add += f;
		place->pos52 = gm_GameTime;
		gm_AddTime(&place->pos52, 0, 5, 0);
		place->xb8 -= v;

		place->posBC = gm_GameTime;
		if (place->xb8 <= 0) {
			place->status = -1;
		}
		if ((int) (*(unsigned char*) (slot + 0xc)) + (int) place->add >= 0xff) {
			place->status = -1;
		}
	}
	if (place->status < -2) {
		return;
	}
	if (place->status >= 0) {
		return;
	}
	v = (int) place->add;
	if (slot != 0 && v > 0) {
		fcn_004f2d30(rec, place->xb0, place->xb4, v);
		if (!entity) {
			he_FreeAction(a0);
			return;
		}
		fig = fcn_0050dc90(rec);
		io_FormatTextBuffer(text, 0x4126, 0x411e, *(unsigned short*) entity, rec);
		row = (int) (*(unsigned short*) (a0 + 8)) * 0x21c;
		if ((g_7f4ca0[row + 2] == 6 || g_7f4ca0[row + 2] == 7)
			&& (!fig || !(*(unsigned char*) (fig + 0x1b4) & 1))) {
			he_MessageBoxQuickjump(*(int*) (g_7f4ca0 + row + 4), -1, text, 0, 0x5ec,
				*(int*) (rec + 1), -1, 0, (char*) 0x6a7f70);
		}
	}
	if (entity) {
		fcn_00529160(0, 0, *(unsigned short*) entity, 0);
	}
end:
	he_FreeAction(a0);
}
