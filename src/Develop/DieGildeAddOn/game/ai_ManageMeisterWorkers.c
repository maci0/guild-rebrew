#include <string.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "Develop/client_types.h"

/* One 0x21c-byte record of the 0x7f4ca0 table. Only the fields this body
 * reads are named; the rest stays padding. */
typedef struct Ent {
	unsigned short id;
	unsigned char kind;
	char pad3[0x165 - 3];
	unsigned char role;
	char pad166[0x16c - 0x166];
	char* home;
	char pad170[0x174 - 0x170];
	int slots;
	char pad178[0x21c - 0x178];
} Ent;
// SIZE 0x21c

extern pos14_7f4c00 gm_GameTime;
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern char gm_EntityIdField[];
extern unsigned char* lpGebaeudePROT;

int __cdecl gm_RandomMod(int);
int __cdecl gm_CheckEntityType(unsigned char*);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
float __cdecl gm_GetHireWage(unsigned char*, int, int, int);
void __cdecl cm_SendCopyEntityData(char*);

/* Offers a building slot to the local player: counts the records and work
 * slots already bound to the entity's owner, and either reports the pending
 * offer or asks for a new builder. */
/* ADDRESS: GOLDTL 0x00487000 */
void __cdecl ai_ManageMeisterWorkers(char* meister)
{
	char msg[0xf8];
	char* ent;
	int p;
	char* rec;
	char* sp;
	int q;
	char* slot;
	int n;
	int tick;
	int i;

	if ((*(short*) &gm_GameTimeHour) != 7 && (*(short*) &gm_GameTimeHour) != 0xc && (*(short*) &gm_GameTimeHour) != 0x12) {
		*(unsigned int*) (meister + 0x1b4) &= 0xffffffbf;
		return;
	}
	if (*(unsigned int*) (meister + 0x1b4) & 0x40) {
		return;
	}
	*(unsigned int*) (meister + 0x1b4) |= 0x40;
	if ((*(unsigned char*) ((char*) 0x7f4ca0
	                        + *(unsigned short*) (*(char**) (meister + 0x16c) + 0x27) * 0x21c + 2) == 6
	     || *(unsigned char*) ((char*) 0x7f4ca0 + *(unsigned short*) (*(char**) (meister + 0x16c) + 0x27) * 0x21c + 2) == 7)
	    && !(*(unsigned int*) (meister + 0x1b4) & 2)) {
		return;
	}
	ent = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) (*(char**) (meister + 0x16c))];
	for (p = 0x7f4e05; p < 0x85a205; p += 0x21c) {
		rec = (char*) (p - 0x165);
		if (*(unsigned short*) rec == 0xffff) {
			continue;
		}
		if (*(char**) (rec + 0x16c) != *(char**) (meister + 0x16c)) {
			continue;
		}
		if (*(char*) (rec + 0x165) == 0) {
			continue;
		}
		if (*(char*) (rec + 0x165) != (char)((BUILDING_PROTOTYPE*)ent)->role_230) {
			continue;
		}
		if (*(int*) (rec + 0x174) < 4) {
			continue;
		}
		memset(msg, 0, sizeof(msg));
		msg[4] = 0x32;
		*(int*) (msg + 8) = *(int*) (gm_EntityIdField
		                           + *(unsigned short*) (*(char**) (meister + 0x16c) + 0x27) * 0x21c);
		*(int*) (msg + 0xc) = *(int*) (*(char**) (meister + 0x16c) + 1);
		*(int*) (msg + 0x28) = gm_GameTime.a;
		*(int*) (msg + 0x2c) = gm_GameTimeHour;
		*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
		msg[0x36] = 2;
		*(short*) (msg + 0x34) = gm_GameTimeTailWord;
		*(int*) (msg + 0x58) = *(int*) (rec + 4);
		cm_SendCopyEntityData(msg);
	}
	n = 0;
	for (q = 0x7f4e0c; q < 0x85a20c; q += 0x21c) {
		if (*(unsigned short*) (q - 0x16c) == 0xffff) {
			continue;
		}
		if (*(char**) q != *(char**) (meister + 0x16c)) {
			continue;
		}
		if (*(unsigned char*) (q - 7) == 0) {
			continue;
		}
		n++;
	}
	slot = he_StartHandlungSearch(2, 0, 6, 3, *(int*) (*(char**) (meister + 0x16c) + 1));
	if (slot != 0) {
		sp = slot + 0xb0;
		for (i = 0xc; i != 0; i--) {
			if (*(int*) sp != 0) {
				n++;
			}
			sp += 4;
		}
	}
	if (n >= (int) (((BUILDING_PROTOTYPE*)lpGebaeudePROT)
	                                    [*(unsigned char*) (*(char**) (meister + 0x16c))].capacity_231
	                + ((BUILDING_PROTOTYPE*)lpGebaeudePROT)
	                                     [*(unsigned char*) (*(char**) (meister + 0x16c))].capacity_232)) {
		return;
	}
	tick = (int) gm_GetHireWage((unsigned char*) ((char*) 0x7f4ca0
	                                           + *(unsigned short*) (*(char**) (meister + 0x16c) + 0x27) * 0x21c),
	                          *(unsigned char*) (*(char**) (meister + 0x16c)), -1, 1);
	if (n != 0) {
		if (*(unsigned int*) (meister + 0x1c8) & 8) {
			return;
		}
		if (*(int*) (meister + 0x1b8) < tick) {
			return;
		}
		if ((int) (gm_RandomMod(0x48) & 0xffff) < (0x12 - n) * 2) {
			return;
		}
	}
	if (slot != 0) {
		return;
	}
	memset(msg, 0, sizeof(msg));
	msg[4] = 6;
	*(int*) (msg + 8) = *(int*) (gm_EntityIdField
	                           + *(unsigned short*) (*(char**) (meister + 0x16c) + 0x27) * 0x21c);
	*(int*) (msg + 0xc) = *(int*) (*(char**) (meister + 0x16c) + 1);
	*(int*) (msg + 0x28) = gm_GameTime.a;
	*(int*) (msg + 0x2c) = gm_GameTimeHour;
	msg[0x36] = 1;
	*(int*) (msg + 0x30) = gm_GameTimeSliceDword;
	*(short*) (msg + 0x34) = gm_GameTimeTailWord;
	*(int*) (msg + 0x5c) = 1;
	gm_CheckEntityType((unsigned char*) *(char**) (meister + 0x16c));
	*(int*) (msg + 0x8c) = -1;
	msg[0x59] = 1;
	msg[0x58] = ((BUILDING_PROTOTYPE*)lpGebaeudePROT)
	                             [*(unsigned char*) (*(char**) (meister + 0x16c))].role_230;
	cm_SendCopyEntityData(msg);
	*(int*) (meister + 0x1b8) -= tick;
}
