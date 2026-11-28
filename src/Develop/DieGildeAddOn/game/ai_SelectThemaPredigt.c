extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/game_data.h"
unsigned short __cdecl gm_RandomMod(unsigned short n);
char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl amt_GetRoleTemplate(int kind, int* out);
int __cdecl amt_FindOfficeSlotsByKind(int kind, int max, void* out);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
unsigned int __cdecl gm_FindEntityCandidatesInRange(unsigned short* a0, unsigned int a1, unsigned int* a2,
				  float a3, float a4, unsigned short* a5);
void __cdecl cm_BeginPacketFieldDelta(char* obj, int id);
void __cdecl cm_AppendPacketFieldDelta(int a, int b, int offset, void* value);
void __cdecl cm_RequestChangeAttribute(void);
#include "Develop/DieGildeAddOn/game/entity_record.h"
/* ADDRESS: GOLDTL 0x00493200 */
/* ADDRESS: GOLDDE 0x00482050 */
int __cdecl ai_SelectThemaPredigt(char* actorEntity, char* sermonObj)
{
	char slots[0x90];
	char* pick;
	int rec[2];
	int count;
	int left;
	int index;
	int roll;
	int r;
	int m;
	unsigned int code;
	unsigned int pos;
	float f;
	unsigned char kind;
	unsigned char b;

	pick = 0;
	roll = gm_RandomMod(3);
	if (actorEntity == 0 || sermonObj == 0) {
		return 0;
	}
	kind = *(unsigned char*) (actorEntity + 0x130);
	if (kind == 0 || *(int*) (actorEntity + 0x194) < 2) {
		return 0;
	}
	if (kind == 7) {
		if (*(unsigned char*) (actorEntity + 0x166) == 0) {
			goto other;
		}
		if (amt_GetRoleTemplate(*(unsigned char*) (actorEntity + 0x166), rec) == 0) {
			return 0;
		}
		count = amt_FindOfficeSlotsByKind(rec[1], 6, slots);
		if (count == 0) {
			return 0;
		}
		index = gm_RandomMod(count);
		left = count;
		do {
			r = *(int*) (slots + index * 24 + 4);
			if (*(int*) (actorEntity + 4) != r) {
				pick = gm_LookupEntityRecordById(r);
				if (pick != 0) {
					f = gm_CalcEntityFavor(*(unsigned short*) actorEntity, *(unsigned short*) pick, 1);
					r = gm_RandomMod(0x1e);
					if ((float) r + g_662c98 > f) {
						break;
					}
					pick = 0;
				}
			}
			left--;
			index = (index + 1) % count;
		} while (left != 0);
	} else if (kind == 0xa) {
		code = 0xc00;
		pos = gm_RandomMod(0x1e);
		if (gm_FindEntityCandidatesInRange((unsigned short*) actorEntity, 1, &code, 0.0f,
				 (float) (int) pos + g_662c98, (unsigned short*) &pos) == 0) {
			goto other;
		}
		pick = ((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[(pos & 0xffff)]);
	}
	if (pick != 0) {
		b = 1;
		cm_BeginPacketFieldDelta(sermonObj, *(int*) (sermonObj + 2));
		cm_AppendPacketFieldDelta(4, 1, 0x1e, pick + 4);
		cm_AppendPacketFieldDelta(1, 1, 0x22, &b);
		b = (unsigned char) gm_RandomMod(8);
		cm_AppendPacketFieldDelta(1, 1, 0x1c, &b);
		b = (unsigned char) gm_RandomMod(8);
		cm_AppendPacketFieldDelta(1, 1, 0x1d, &b);
		cm_RequestChangeAttribute();
		return 1;
	}

other:
	kind = *(unsigned char*) (actorEntity + 0x130);
	if (kind != 3 && kind != 4 && roll == 0) {
		return 0;
	}
	m = -1;
	b = 1;
	cm_BeginPacketFieldDelta(sermonObj, *(int*) (sermonObj + 2));
	cm_AppendPacketFieldDelta(4, 1, 0x1e, &m);
	cm_AppendPacketFieldDelta(1, 1, 0x22, &b);
	b = 0xff;
	cm_AppendPacketFieldDelta(1, 1, 0x1c, &b);
	cm_AppendPacketFieldDelta(1, 1, 0x1d, &b);
	cm_RequestChangeAttribute();
	return 1;
}
