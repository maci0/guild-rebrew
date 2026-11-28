


extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/entity_record.h"

unsigned short* __cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
int __cdecl gm_CheckEntityStock(void*, int, char);
int __cdecl d2_ShowModalMessageBox(char*, int);
void __cdecl cm_RequestMoveCredits(int, int, char, int);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, int);
void __cdecl he_FreeAction(char*);

/* ADDRESS: GOLDDE 0x00589070 */
void __cdecl d2_AcceptLoanOffer(char* building, char* offer)
{
	char txt[0x200];
	char msg[0x400];
	unsigned short* g;
	char* slot;
	char* p;

	g = gm_LookupEntityRecordById(*(int*) (offer + 0xb0));
	io_FormatTextBuffer(msg, 0x18d5, *(int*) (offer + 0xb4));
	if (building == 0) {
		return;
	}
	if (gm_CheckEntityStock(g, *(int*) (offer + 0xb4), (*(char*)&gm_ActiveTownIndex)) == 0) {
		return;
	}
	if (d2_ShowModalMessageBox(msg, 1) == 0) {
		return;
	}
	slot = ((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (building + 0x27)]);
	cm_RequestMoveCredits(*(int*) (building + 1), *(int*) (offer + 0xb0), (*(char*)&gm_ActiveTownIndex), *(int*) (offer + 0xb4));
	p = (char*) gm_GetEntityTableEntry((char*) (g));
	if (p != 0) {
		*(int*) (p + 0x48) += *(int*) (offer + 0xb4);
	}
	if (slot[2] != 5) {
		io_FormatTextBuffer(txt, 0x18d8, *g, building, *(int*) (offer + 0xb4));
		he_MessageBoxQuickjump(*(int*) (slot + 4), -1, txt, 0, 0x5ec, *(int*) (building + 1), -1, 0, 0);
	}
	he_FreeAction(offer);
}
