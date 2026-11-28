

#include <string.h>
#pragma intrinsic(memset)

typedef struct {
	int w;
	char* p;
} D2_DEAL_SUMMARY_BTN;
// SIZE 0x8

#include "Develop/DieGildeAddOn/game/entity_record.h"






extern D2_DEAL_SUMMARY_BTN g_776ca0[256];


void __cdecl d2_SetForm(int, int);
int __cdecl gm_BuildDealSummary(int, char*);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_GetWindowListItem(int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"

void __cdecl d2_PopulateDealSummaryList(int win, int sub, int idx, int unused)
{
	char buf[0x220];
	int k;
	char* r;

	d2_SetForm(win, sub);
	memset(g_776ca0, 0, sizeof(g_776ca0));
	gm_BuildDealSummary(idx, buf);
	io_AppendText(0x1efa, ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[idx].value_194);
	k = 0;
	while (*(int*) (buf + 0x35 + k * 0x1e) != 0 && k < 256) {
		r = buf + 0x35 + k * 0x1e;
		g_776ca0[k].w = d2_GetWindowListItem(win, sub, io_AppendText(0x1efb, 2, *(int*) (r + 8), *(int*) (r + 0xc)));
		g_776ca0[k].p = *(char**) (r + 4);
		d2_SetElementValue(g_776ca0[k].w, *(int*) (g_776ca0[k].p + 8));
		k++;
	}
}
