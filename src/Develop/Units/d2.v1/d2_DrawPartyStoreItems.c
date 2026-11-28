

#include <stdio.h>
#include <string.h>

#pragma pack(push, 1)
typedef struct Item {
	unsigned short id;
	char pad2[0xa - 2];
	int owner;
	int count;
} Item;
#pragma pack(pop)

typedef struct Group {
	char pad0[0x14];
	int first;
} Group;

typedef struct Party {
	char pad0[0x100];
	int stores[3];
} Party;

typedef struct Slot {
	char pad0[0x18];
	int h;
	char pad1c[0x6c - 0x1c];
	int centered;
	char pad70[0x84 - 0x70];
	int color;
	char pad88[0x2f4 - 0x88];
} Slot;
// SIZE 0x2f4

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_CurrentWindowId;
extern char str_empty[];
extern char* d2_Controls;
extern char* g_14b52c0;
extern unsigned char gm_ActiveTownIndex;

Group* __cdecl gm_QueryEntities(int a, int b, int c, ...);
int __cdecl d2_AddElementToWindow(int x, int y, int id, int win);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetLabelText(int, char*);
float __cdecl gm_GetSeasonPrice(int, unsigned char);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
Item* __cdecl gm_NextEntityQueryMatch(void);

/* ADDRESS: GOLDDE 0x004c23e0 */
int __cdecl d2_DrawPartyStoreItems(int x, int y, int mode)
{
	int n;
	int total;
	int k;
	int tx;
	int lbl;
	char text[0x100];
	Item* e;
	int px;
	int py;

	n = 0;
	total = 0;
	for (k = 0; k < 3; k++) {
		if (((Party*)g_772eb4)->stores[k] == -1) {
			continue;
		}
		e = (Item*) gm_QueryEntities(0, 2, 7, 1, ((Party*)g_772eb4)->stores[k]);
		e = (Item*) gm_QueryEntities(((Group*) e)->first, 1, 0, 0x1dd);
		e = (Item*) gm_QueryEntities(((Group*) e)->first, 1, 5);
		for (; e != 0; e = gm_NextEntityQueryMatch()) {
			if (mode != 0 && (mode != 1 || e->owner != gm_LocalPlayerSlot) && (mode != 2 || e->owner == gm_LocalPlayerSlot)) {
				continue;
			}
			px = x + n % 5 * 0x78;
			py = y + n / 5 * 0x60;
			d2_AddElementToWindow(px, py, 0x525, d2_CurrentWindowId);
			d2_AddElementToWindow(px, py, e->id + 0xdf, d2_CurrentWindowId);
			tx = px - 0x10;
			lbl = d2_ShowTxt(tx, py - 0xf, &(*(char*)str_empty), d2_CurrentWindowId);
			(*(int*)&((D2_CONTROL_TL*)d2_Controls)[lbl].font) = 0x56;
			(*(int*)&((D2_CONTROL_TL*)d2_Controls)[lbl].width) = 0x50;
			(*(int*)&((D2_CONTROL_TL*)d2_Controls)[lbl].value_06c) = 1;
			sprintf(text, "%i ", e->count);
			strcat(text, g_14b52c0);
			d2_SetLabelText(lbl, text);
			lbl = d2_ShowTxt(tx, py + 0x34, &(*(char*)str_empty), d2_CurrentWindowId);
			(*(int*)&((D2_CONTROL_TL*)d2_Controls)[lbl].font) = 0x56;
			(*(int*)&((D2_CONTROL_TL*)d2_Controls)[lbl].width) = 0x50;
			(*(int*)&((D2_CONTROL_TL*)d2_Controls)[lbl].value_06c) = 1;
			io_FormatTextBuffer(text, "%T", (int) gm_GetSeasonPrice(e->id, gm_ActiveTownIndex) * e->count);
			d2_SetLabelText(lbl, text);
			total = (int)(gm_GetSeasonPrice(e->id, gm_ActiveTownIndex) * e->count + total);
			n++;
		}
	}
	return total;
}
