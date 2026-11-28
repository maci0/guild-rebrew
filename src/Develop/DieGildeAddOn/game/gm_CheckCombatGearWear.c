#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
/* Owned (both targets) by src/GOLDTL.fcn_004cef70.c. */
extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
unsigned short __cdecl gm_RandomMod(int);
void __cdecl gm_RemoveSpecialTableItems(void*);

void __cdecl cm_AppendPacketFieldValue(int, int, int, char*);
void __cdecl cm_RequestChangeAttribute(void);
void* __cdecl gm_GetEquippedCombatGear(void*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);


/* ADDRESS: GOLDTL 0x004ce740 */
/* ADDRESS: GOLDDE 0x004bbee0 */
char __cdecl gm_CheckCombatGearWear(char* entity)
{
	char buf[0x800];
	char c;
	signed char c0;
	unsigned short idx;
	void* e;
	void* q;
	char* p;
	int r;

	c = 1;
	if (entity == 0) {
		return 0;
	}
	if ((*(int*) (entity + 0x1c8) & 0x20000000) == 0) {
		return 0;
	}
	c0 = *(signed char*) (entity + 0x1c5);
	if (gm_RandomMod(10) < (unsigned short) (unsigned char) c0) {
		c = -c0;
		gm_RemoveSpecialTableItems(entity);
		cm_BeginPacketFieldDelta(entity, *(int*) (entity + 4));
		cm_AppendPacketFieldValue(1, 1, entity - cm_PacketDeltaBase + 0x1c5, &c);
		cm_RequestChangeAttribute();
		e = *(void**) (entity + 0x16c);
		if (e != 0) {
			idx = *(unsigned short*) ((char*) e + 0x27);
			if (idx != 0xffff) {
				p = ((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[idx]);
				if (*(char*)&((ENTITY_RECORD_VIEW*)p)->entity_type == 6 || *(char*)&((ENTITY_RECORD_VIEW*)p)->entity_type == 7) {
					q = gm_GetEquippedCombatGear(entity);
					r = *(int*) q;
					if (r != 0) {
						io_FormatTextBuffer(buf, 0x1bca, r * 2 + 0x9a8,
						    *(unsigned short*) entity, *(int*) (entity + 0x16c));
						he_PostEntityMessage(*(int*)&((ENTITY_RECORD_VIEW*)p)->entity_id, -1, buf, 0, 0x5f2, 0);
					}
				}
			}
		}
		return 1;
	}
	cm_BeginPacketFieldDelta(entity, *(int*) (entity + 4));
	cm_AppendPacketFieldValue(1, 1, entity - cm_PacketDeltaBase + 0x1c5, &c);
	cm_RequestChangeAttribute();
	cm_RequestChangeBits(*(int*) (entity + 4), 0x1c8, 4, 0, 0x20000000);
	return 0;
}
