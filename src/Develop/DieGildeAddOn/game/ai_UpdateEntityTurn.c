extern char g_666028[];
extern char g_85a0a2[];
extern char g_10085d0[];
extern char g_90e094[];
extern char gm_SlotTableKindView[];
extern char g_7f4c06[];
extern char ai_FeudTargetEntity[];
#include "Develop/DieGildeAddOn/game/client_actions.h"

#pragma pack(push, 1)
typedef struct AI_TURN_ENTITY {
	unsigned short id;
	unsigned char kind;
	char pad3;
	unsigned int seed;
	char pad8[0x21c - 8];
} AI_TURN_ENTITY;
// SIZE 0x21c

typedef struct AI_TURN_BUILDING {
	unsigned char kind;
	char pad1[4];
	char name[0x22];
	unsigned short x27;
	char pad29[0x5a - 0x29];
	unsigned char x5a;
	char pad5b[0xa9 - 0x5b];
} AI_TURN_BUILDING;
// SIZE 0xa9

typedef struct AI_TURN_PROTO {
	unsigned char kind;
	char pad1[0x223 - 1];
	unsigned char x223;
	char pad224[0x230 - 0x224];
	unsigned char x230;
	char pad231[0x24d - 0x231];
} AI_TURN_PROTO;
// SIZE 0x24d
#pragma pack(pop)

extern unsigned char* lpGebaeudePROT;
extern char gm_EntitySlotTable[];

int __cdecl ai_IsEntityTurnActive(AI_TURN_ENTITY*);
AI_TURN_ENTITY* __cdecl ai_UpdateEntityFeud(AI_TURN_ENTITY*);
void __cdecl ai_BuildActionCandidates(AI_TURN_ENTITY*);
void __cdecl cm_RequestAssignWorker(AI_TURN_BUILDING*, int, int, int);
int __cdecl ai_SelectEntityMethod(int);
void __cdecl ai_RunSelectedMethod(int);
int __cdecl gm_GetBuildingTypeCategory(int);
int __cdecl sprintf(char*, char*, ...);

/* ADDRESS: GOLDTL 0x0047d810 */
/* ADDRESS: GOLDDE 0x0046c7d0 */
void __cdecl ai_UpdateEntityTurn(AI_TURN_ENTITY* entity)
{
	int remaining;
	char buf[1024];
	int found;
	unsigned int lo;
	unsigned int hi;
	AI_TURN_BUILDING* building;
	AI_TURN_PROTO* proto;
	char* candidate;
	unsigned int state;
	int x223;
	int x230;

	if (!ai_IsEntityTurnActive(entity)) {
		return;
	}
	if (*(unsigned int*) ((char*) entity + 0x1cc) & 0x3000) {
		return;
	}
	remaining = 0x100;
	building = *(AI_TURN_BUILDING**) &g_90e094;
	do {
		if (building->kind) {
			proto = &((AI_TURN_PROTO*) lpGebaeudePROT)[building->kind];
			lo = 0;
			hi = 0;
			if (proto->kind > 0x1f) {
				hi = 1 << (proto->kind - 0x20);
			}
			else {
				lo = 1 << proto->kind;
			}
			if (building->x27 == entity->id && !(building->x5a & 1)
			 && ((*(unsigned int*) &g_666028 & lo) || (*(unsigned int*) ((int) &g_666028 + 0x4) & hi))) {
				found = 0;
				candidate = (char*) &gm_SlotTableKindView;
				do {
					if ((int) candidate >= (int) &g_85a0a2) {
						break;
					}
					if (*(unsigned short*) (candidate - 2) != 0xffff
					 && *(AI_TURN_BUILDING**) (candidate + 0x16a) == building
					 && (*(unsigned char*) candidate == 1 || *(unsigned char*) candidate == 2)) {
						found = 1;
					}
					candidate += 0x21c;
				} while (!found);
				if (gm_GetBuildingTypeCategory(building->kind) != 6 && !found) {
					proto = &((AI_TURN_PROTO*) lpGebaeudePROT)[building->kind];
					x223 = proto->x223;
					x230 = proto->x230;
					cm_RequestAssignWorker(building, 1, x230, x223);
					sprintf(buf, "%li:%02li - %s stellt Meister f\374r '%s' ein", *(unsigned short*) &gm_GameTimeHour,
					 *(int*) &g_7f4c06, (char*) entity + 0x30, building->name);
				}
			}
		}
		building++;
		remaining--;
	} while (remaining);
	if (*(unsigned char*) ((char*) entity + 8) <= 0) {
		return;
	}
	*(int*) &ai_FeudTargetEntity = (int) ai_UpdateEntityFeud(entity);
	ai_BuildActionCandidates(entity);
	state = *((unsigned char*) entity + 0x132);
	if (!*((char*) entity + 0x1b1) && ai_SelectEntityMethod(entity->id)) {
		if (*((unsigned char*) entity + 0x132) != state
		 || (*(unsigned int*) ((int) &g_10085d0 + *((unsigned char*) entity + 0x132) * 0x94) & 0x200)) {
			ai_RunSelectedMethod(entity->id);
		}
	}
	*(int*) &ai_FeudTargetEntity = 0;
}
