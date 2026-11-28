


// SIZE 0x2f4
struct player {
	char name[0x54];
	unsigned short id;
	char pad56[0x29e];
};

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








extern char gm_TownTable[];
extern unsigned char gm_ActiveTownIndex;

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl he_PostEntityMessage(int, int, char*, unsigned char, int, char*);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
void __cdecl he_FreeAction(char*);

void __cdecl he_RunAction0x27(char* u)
{
	char text[0x400];
	char* e;

	switch (*(int*) (u + 0x70)) {
	case 0:
		e = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0xac));
		if (e != 0) {
			io_FormatTextBuffer(text, 0x190b, ((struct player*)gm_TownTable)[*(unsigned char*) (u + 0xb0)].name, *(int*) (u + 0xb4));
			he_PostEntityMessage(((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (u + 8)].entity_id, -1, text, 0, 0x5ff, 0);
			cm_SendSellObjekt(*(int*) (e + 1), -1, ((struct player*)gm_TownTable)[*(unsigned char*) (u + 0xb0)].id, *(int*) (u + 0xb4), gm_ActiveTownIndex, 0);
		}
		he_FreeAction(u);
		return;
	case -2:
	case -1:
		he_FreeAction(u);
		break;
	}
}
