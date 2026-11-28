typedef struct Ent {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	unsigned char alive;
	char pad9[0x166 - 9];
	unsigned char x166;
	char pad167[2];
	unsigned char x169;
	char pad16a[0x1cc - 0x16a];
	int flags;
	char pad1d0[0x21c - 0x1d0];
} Ent;
// SIZE 0x21c

typedef struct Rec18 {
	char pad0[8];
	unsigned char x8;
	char pad9[3];
	int xc;
	char pad10[8];
} Rec18;
// SIZE 0x18

typedef struct PRIVILEGE_INCOME_INFO {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	char pad3;
	int va;
	int vb;
	int vc;
} PRIVILEGE_INCOME_INFO;
// SIZE 0x10

#include "Develop/DieGildeAddOn/game/entity_record.h"
extern float g_665264[];
extern int gm_QueuedCommandCount;

int __cdecl amt_GetRoleTemplate(int idx, Rec18* out);
int __cdecl gm_GetLawEntry(int idx, void* dst);
char* __cdecl gm_GetGuildHall(int n);
char* __cdecl gm_QueryEntities(int, int, int, int, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl cm_RequestModifyHealth(int, int);

/* ADDRESS: GOLDTL 0x004fcda0 */
/* ADDRESS: GOLDDE 0x004e88d0 */
int __cdecl amt_ProcessPrivilegeIncome(unsigned short id, int pay, PRIVILEGE_INCOME_INFO* out)
{
	Rec18 q;
	int info[9];
	float mult;
	char* w;
	int r;
	int c;
	int amount;

	r = 0;
	out->a = (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].class_166);
	out->b = (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].grade);
	if ((*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].flags_1cc) & 0x1000) {
		c = 0x26;
	} else if ((*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].flags_1cc) & 0x2000) {
		c = 0x27;
	} else if ((*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].flags_1cc) & 0x800) {
		c = 0x25;
	} else if ((*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].flags_1cc) & 0x400) {
		c = 0x24;
	} else {
		c = ((*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].flags_1cc) & 0x200) ? 0x23 : 0;
	}
	out->c = c;
	out->va = 0;
	out->vb = 0;
	out->vc = 0;
	if ((((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].entity_index) != 0xffff && (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].entity_type) < 0xa &&
		(((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].health) > 0
	    && ((((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].class_166) != 0 || (((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].grade) != 0 ||
	    	((*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].flags_1cc) & 0xe00) != 0)) {
		gm_GetLawEntry(0xf, info);
		mult = g_665264[info[6]];
		amt_GetRoleTemplate((((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].grade), &q);
		out->vb = (int) ((q.xc << 5) * mult);
		amt_GetRoleTemplate((((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].class_166), &q);
		out->va = (int) ((q.xc << 5) * mult);
		amt_GetRoleTemplate(out->c, &q);
		out->vc = (int) ((q.xc << 5) * mult);
		r = 1;
		if (pay != 0) {
			w = gm_GetGuildHall(1);
			if (w == 0) {
				return 0;
			}
			if (gm_QueryEntities(*(int*) (w + 0x5d), 2, 6, 0, 0x115) == 0) {
				return 0;
			}
			if (out->va != 0) {
				cm_RequestTransferCurrencyNoKill((((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].entity_id), -1, 0, out->va);
				gm_QueuedCommandCount++;
			}
			if (out->vb != 0) {
				cm_RequestTransferCurrencyNoKill((((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].entity_id), -1, 0, out->vb);
				gm_QueuedCommandCount++;
			}
			if (out->vc != 0) {
				cm_RequestTransferCurrencyNoKill((((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].entity_id), -1, 0, out->vc);
				gm_QueuedCommandCount++;
			}
			if ((((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].entity_type) == 3) {
				amount = (gm_RandomMod((unsigned short) (q.x8 + 2)) + q.x8) * 6400;
				cm_RequestTransferCurrencyNoKill((((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].entity_id), -1, 0, amount);
				cm_RequestModifyHealth((((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].entity_id), q.x8);
				gm_QueuedCommandCount += 2;
			}
		}
	}
	return r;
}
