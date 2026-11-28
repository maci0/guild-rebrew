extern char s_6a5b84[];
extern char s_6a5b8c[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_662948;
extern float g_6640b4;
extern char* lpGebaeudePROT;
extern char* lpGebaeudeINST;
extern unsigned char g_slot_table[2];
#include "Develop/DieGildeAddOn/game/building_prototype.h"
void* __cdecl m_alloc(unsigned int size, const char* tag);
unsigned short __cdecl gm_RandomMod(int n);
float __cdecl gm_RandomFloat01Squared(void);
int __cdecl cm_GetCommandStatus(unsigned int id);
void* __cdecl cm_GetCommandResult(unsigned int id);
unsigned int __cdecl cm_SendSetHE(int state, void* ev);
void __cdecl cm_RequestKillSpieler(unsigned int h, int flag);
void __cdecl cm_SendCancelCharacterActions(unsigned int h);
void __cdecl ch_StartMovement(unsigned int h, unsigned int id, int a3, int a4, int a5, char* tag);
void __cdecl gm_AddTime(void* q, int a2, int a3, int a4);
float __cdecl gm_ApplyPlagueInfection(char* entity);
void* __cdecl gm_LookupEntityRecordById(unsigned int slot_id);
void __cdecl gm_ResolveEntityById(char** out, int a2, int a3, int id);
void __cdecl io_FormatTextBuffer(char* buf, char* fmt, ...);
int __cdecl gm_IsEntityAtBuilding(char* a, char* b);
void __cdecl he_FreeAction(void* ev);
void __cdecl he_ResolveAccidentOutcome(char* a1, char* a2, char* a3, char* a4, int a5, float a6);
void __cdecl he_RunPlagueSpread(void* ev);
void __cdecl he_NotifyPlagueInfection(char* a1, char* a2);
typedef struct { unsigned char kind; char unknown[0x24c]; } BUILDING_PROT_5522;
/* ADDRESS: GOLDTL 0x005522d0 */
/* ADDRESS: GOLDDE 0x00538680 */
void __cdecl he_RunPlagueEvent(char* ev)
{
	char buf[512];
	int picks[16];
	float scores[16];
	char* ent;
	char* slot;
	char* listp;
	void* rec;
	void* found;
	void* p;
	int nent;
	int slot_no;
	int bit_lo;
	int bit_hi;
	unsigned char sel;
	int left;
	int i;
	int n;
	int count;
	int state;
	float best;
	float f;

	if (*(int*) (ev + 0x70) == -1 || *(int*) (ev + 0x70) == -2) {
		if (*(unsigned char*) (ev + 0x78) & 2) {
			for (i = 0; i < 4; i++) {
				p = gm_LookupEntityRecordById(*(unsigned int*) (ev + 0xbc + i * 4));
				if (p) {
					cm_SendCancelCharacterActions(*(unsigned int*) ((char*) p + 4));
					cm_RequestKillSpieler(*(unsigned int*) ((char*) p + 4), 1);
				}
			}
		}
		he_FreeAction(ev);
		return;
	}
	if (*(unsigned char*) (ev + 0x78) & 4) {
		return;
	}
	if (*(int*) (ev + 0x84) != -1 && !cm_GetCommandStatus(*(unsigned int*) (ev + 0x84))) {
		return;
	}
	if (*(int*) (ev + 0x70) == 5) {
		he_RunPlagueSpread(ev);
	}
	switch (*(unsigned int*) (ev + 0x70)) {
	case 0:
		for (i = 0; i < 4; i++) {
			p = 0;
			if (cm_GetCommandStatus(*(unsigned int*) (ev + 0xbc + i * 4)) == 1) {
				p = cm_GetCommandResult(*(unsigned int*) (ev + 0xbc + i * 4));
			}
			if (p != 0) {
				*(unsigned int*) (ev + 0xbc + i * 4) = *(unsigned int*) ((char*) p + 4);
			}
			else {
				*(unsigned int*) (ev + 0xbc + i * 4) = 0xffffffff;
			}
		}
		gm_AddTime(ev + 0x52, 0, 1, 0);
		*(unsigned int*) (ev + 0x84) = cm_SendSetHE(1, ev);
		return;
	case 1:
		slot_no = *(unsigned int*) (ev + 0xb0);
		n = 0x100;
		do {
			bit_hi = 0;
			listp = lpGebaeudeINST + slot_no * 0xa9;
			rec = listp;
			sel = ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) listp].category;
			bit_lo = 0;
			if (sel > 0x1f) {
				bit_hi = 1 << ((sel - 0x20) & 0x1f);
			}
			else {
				bit_lo = 1 << (sel & 0x1f);
			}
			if (*(unsigned short*) (listp + 0x27) != 0xffff
				&& ((bit_lo & 0x807c4110) || (bit_hi & 1))) {
				break;
			}
			rec = 0;
			n--;
			slot_no = (slot_no + *(int*) (ev + 0xb4)) % 256;
		} while (n);
		slot_no = (slot_no + *(int*) (ev + 0xb4)) % 256;
		*(unsigned int*) (ev + 0xb0) = slot_no;
		if (!rec) {
			gm_AddTime(ev + 0x52, 0, 1, 0);
			*(unsigned int*) (ev + 0x84) = cm_SendSetHE(-1, ev);
			return;
		}
		io_FormatTextBuffer(buf, s_6a5b8c, rec);
		count = 0;
		for (i = 0; i < 4; i++) {
			p = gm_LookupEntityRecordById(*(unsigned int*) (ev + 0xbc + i * 4));
			if (p) {
				cm_SendCancelCharacterActions(*(unsigned int*) ((char*) p + 4));
				ch_StartMovement(*(unsigned int*) ((char*) p + 4),
					*(unsigned int*) ((char*) rec + 1), -1, 0, 1, s_6a5b84);
				count++;
			}
		}
		gm_AddTime(ev + 0x52, 0, count > 0 ? 5 : 0x14, 0);
		*(unsigned int*) (ev + 0xcc) = *(unsigned int*) ((char*) rec + 1);
		*(unsigned int*) (ev + 0x84) = cm_SendSetHE(2, ev);
		return;
	case 2:
		gm_ResolveEntityById((char**) &rec, 0, 0, *(unsigned int*) (ev + 0xcc));
		gm_AddTime(ev + 0x52, 0, 5, 0);
		if (!rec) {
			*(unsigned int*) (ev + 0x84) = cm_SendSetHE(-1, ev);
			return;
		}
		for (i = 0; i < 4; i++) {
			p = gm_LookupEntityRecordById(*(unsigned int*) (ev + 0xbc + i * 4));
			if (p && !gm_IsEntityAtBuilding((char*) p, (char*) rec)) {
				*(unsigned int*) (ev + 0x70) = 2;
				gm_AddTime(ev + 0x52, 0, 5, 0);
				*(unsigned int*) (ev + 0x84) = cm_SendSetHE(2, ev);
				return;
			}
		}
		if (*(unsigned short*) ((char*) rec + 0x27) != 0xffff) {
			slot = (char*) g_slot_table
				+ *(unsigned short*) ((char*) rec + 0x27) * 0x21c;
			found = 0;
			i = 0;
			nent = 0;
			best = 1000.0f;
			for (n = 0; n < 16; n++) {
				picks[n] = -1;
			}
			ent = (char*) g_slot_table + 0x16c;
			left = 0;
			do {
				if (nent >= 16) {
					break;
				}
				if (*(unsigned char*) (ent - 0x16a) == 0 && *(void**) ent == rec) {
					scores[nent] = 1000.0f;
					picks[nent] = i;
					nent++;
				}
				else if (*(unsigned char*) (ent - 0x16a) == 1 && *(void**) ent == rec) {
					found = ent - 0x16c;
				}
				ent += 0x21c;
				i++;
			} while ((int) ent < 0x85a20c);
			if (nent == 0) {
				goto after_scan;
			}
			f = gm_RandomFloat01Squared();
			if (f > g_662948) {
				f = 1.0f;
			}
			f = f * nent;
			if (!(f > 1.0f)) {
				f = 1.0f;
			}
			count = (int) f;
			for (n = 0; n < count; n++) {
				left = 1;
				scores[n] = gm_ApplyPlagueInfection((char*) g_slot_table + picks[n] * 0x21c);
			}
			p = found;
			if (found && !gm_RandomMod(8)) {
				best = gm_ApplyPlagueInfection((char*) found);
				left = 1;
			}
			if (!gm_RandomMod(0x100)) {
				gm_ApplyPlagueInfection(slot);
			}
			if (left) {
				he_NotifyPlagueInfection(slot, (char*) rec);
			}
			for (n = 0; n < count; n++) {
				if (scores[n] < g_6640b4) {
					he_ResolveAccidentOutcome(ev, (char*) g_slot_table + picks[n] * 0x21c,
						slot, (char*) rec, 1, scores[n]);
				}
			}
			if (best < g_6640b4) {
				he_ResolveAccidentOutcome(ev, (char*) found, slot, (char*) rec, 1, best);
			}
		}
after_scan:
		state = *(int*) (ev + 0xac) - 1;
		*(int*) (ev + 0xac) = state;
		if (state > 0) {
			*(unsigned int*) (ev + 0x84) = cm_SendSetHE(1, ev);
			return;
		}
		gm_ResolveEntityById((char**) &rec, 0, 0, *(unsigned int*) (ev + 0xd0));
		if (!rec) {
			break;
		}
		count = 0;
		for (i = 0; i < 4; i++) {
			p = gm_LookupEntityRecordById(*(unsigned int*) (ev + 0xbc + i * 4));
			if (p) {
				cm_SendCancelCharacterActions(*(unsigned int*) ((char*) p + 4));
				ch_StartMovement(*(unsigned int*) ((char*) p + 4),
					*(unsigned int*) ((char*) rec + 1), -1, 0, 1, s_6a5b84);
				count++;
			}
		}
		gm_AddTime(ev + 0x52, 0, count > 0 ? 1 : 10, 0);
		*(unsigned int*) (ev + 0x84) = cm_SendSetHE(3, ev);
		return;
	case 3:
		gm_AddTime(ev + 0x52, 0, 5, 0);
		gm_ResolveEntityById((char**) &rec, 0, 0, *(unsigned int*) (ev + 0xd0));
		if (!rec) {
			break;
		}
		for (i = 0; i < 4; i++) {
			p = gm_LookupEntityRecordById(*(unsigned int*) (ev + 0xbc + i * 4));
			if (p && !gm_IsEntityAtBuilding((char*) p, (char*) rec)) {
				*(unsigned int*) (ev + 0x70) = 3;
				gm_AddTime(ev + 0x52, 0, 5, 0);
				*(unsigned int*) (ev + 0x84) = cm_SendSetHE(3, ev);
				return;
			}
		}
		break;
	default:
		return;
	}
	*(unsigned int*) (ev + 0x84) = cm_SendSetHE(-1, ev);
}
