


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








extern unsigned char gm_ActiveTownIndex;
extern char g_699874[];
extern char g_6a6b70[];

int __cdecl cm_GetCommandStatus(int);
char* __cdecl cm_GetCommandResult(int);
char* __cdecl gm_SearchTable67(int);
void __cdecl cm_SendSetGebBesitzer(int, int, int);
int __cdecl gm_ConvertUnitsToAmount(int, unsigned char);
void __cdecl cm_RequestMoveCredits(int, int, unsigned char, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
int __cdecl he_GetEntityReturnTarget(char*, int*, int*);
void __cdecl ch_StartMovement(int, int, int, int, int, char*);
void __cdecl he_FreeAction(char*);

void __cdecl he_RunInitBetrieb(char* u)
{
	int site;
	int target;
	char text[0x400];
	char* p;
	char* t;
	ENTITY_RECORD* h;

	switch (*(int*) (u + 0x70)) {
	case 0:
		if (cm_GetCommandStatus(*(int*) (u + 0xac)) == 0) {
			break;
		}
		p = cm_GetCommandResult(*(int*) (u + 0xac));
		t = gm_SearchTable67(*(int*) (u + 0xb4));
		if (p == 0 || t == 0) {
			goto kill;
		}
		if (*(unsigned short*) (t + 0x25) != 0xffff) {
			cm_SendSetGebBesitzer(*(int*) (t + 1), ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (t + 0x25)].entity_id, *(int*) (p + 4));
		} else {
			cm_SendSetGebBesitzer(*(int*) (t + 1), *(int*) (p + 4), *(int*) (p + 4));
		}
		cm_RequestMoveCredits(*(int*) (p + 4), -1, gm_ActiveTownIndex, gm_ConvertUnitsToAmount(0xbb8, gm_ActiveTownIndex));
		if (*(int*) (u + 0xbc) == 0) {
			goto kill;
		}
		h = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (t + 0x25)]);
		if (h != 0) {
			if (h->entity_state == 6 || h->entity_state == 7) {
				io_FormatTextBuffer(text, 0x17e6, t, *(unsigned short*) p, *(int*) (u + 0xbc));
				he_MessageBoxQuickjump(h->entity_id, -1, text, 0, 0x5ec, *(int*) (t + 1), -1, 0, g_699874);
			}
			cm_RequestMoveCredits(h->entity_id, -1, gm_ActiveTownIndex, *(int*) (u + 0xbc));
		}
		cm_SendSetGebBesitzer(*(int*) (t + 1), *(int*) (p + 4), *(int*) (p + 4));
		if (he_GetEntityReturnTarget(p, &site, &target) != 0) {
			ch_StartMovement(*(int*) (p + 4), site, target, 0, 0, g_6a6b70);
		}
	case -2:
	case -1:
kill:
		he_FreeAction(u);
		break;
	}
}
