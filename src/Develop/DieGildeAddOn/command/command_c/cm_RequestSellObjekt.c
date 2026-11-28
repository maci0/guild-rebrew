#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







#pragma pack(1)
// SIZE 0x24d
struct good {
	unsigned char kind;
	char pad1[0x24c];
};
#pragma pack()


extern unsigned char* lpGebaeudePROT;
extern unsigned char gm_ActiveTownIndex;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);

unsigned short __cdecl gm_RandomMod(int);
char* __cdecl gm_QueryEntities();
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_GetMsgField(char*, char*);
int __cdecl fcn_0064d41a(char*, char*, ...);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
float __cdecl gm_GetSeasonPrice(int, unsigned char);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, int);
void __cdecl he_FreeAction(char*);

/* ADDRESS: GOLDDE 0x005371d0 */
void __cdecl cm_RequestSellObjekt(char* e)
{
	int v;
	int amt;
	unsigned char* list[16];
	char msg[0x418];
	char dbg[0x400];
	unsigned char* c;
	unsigned char* sel;
	char* r;
	char* q;
	int n;
	struct BUILDING_PROTOTYPE * p;

	n = 0;
	amt = 0;
	if (*(int*) (e + 0x70) != -2) {
		if (*(int*) (e + 0x70) != 0) {
			return;
		}
		c = gm_StartFilteredEntitySearch(1, 4, *(unsigned short*) (e + 8));
		if (c != 0) {
			for (; c != 0; c = gm_FindNextFilteredEntity()) {
				if (n >= 16) {
					break;
				}
				p = &((struct BUILDING_PROTOTYPE *)lpGebaeudePROT)[*c];
				if (gm_GetBuildingTypeCategory(*c) == 1 || p->category == 9) {
					list[n++] = c;
				}
			}
			if (n != 0) {
				sel = list[gm_RandomMod(n)];
				if (sel != 0) {
					r = gm_QueryEntities(*(int*) (sel + 0x5d), 2, 6, 0, 0x2a);
					if (r == 0) {
						r = gm_QueryEntities(*(int*) (sel + 0x5d), 2, 6, r, 0x116);
					}
					if (r != 0) {
						for (q = gm_QueryEntities(*(int*) (r + 0x14), 1, 5); q != 0; q = gm_NextEntityQueryMatch()) {
							v = gm_GetMsgField(r, q);
							v = (int) (v * 0.25f);
							if (v < 1) {
								v = 1;
							}
							fcn_0064d41a(dbg, "cm_RequestSellObjekt(%i, %i, %i, %i, %i, %i)", -1, *(int*) (r + 2),
							    *(unsigned short*) q, v, gm_ActiveTownIndex, 0);
							cm_SendSellObjekt(-1, *(int*) (r + 2), *(unsigned short*) q, v, gm_ActiveTownIndex, 0);
							amt = (int) (gm_GetSeasonPrice(*(unsigned short*) q, gm_ActiveTownIndex) * v + amt);
						}
					}
				}
				if (((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (e + 8)].entity_state == 6 && amt != 0) {
					io_FormatTextBuffer(msg, 0x10b7, sel, amt);
					he_MessageBoxQuickjump(((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (e + 8)].entity_id, ((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (e + 8)].entity_id,
					    msg, 0, 0x5ec, *(int*) (sel + 1), -1, 0, 0);
				}
			}
		}
	}
	he_FreeAction(e);
}
