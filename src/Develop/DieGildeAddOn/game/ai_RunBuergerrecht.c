

#include "Develop/DieGildeAddOn/game/game_timestamp.h"
// SIZE 0xe








// SIZE 0xf8
typedef struct {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int target;
	char pad10[0x18];
	GAME_TIMESTAMP at;
	unsigned char code;
	char pad37[0x21];
	unsigned char who;
	char pad59[3];
	int other;
	char pad60[0x98];
} CITIZENSHIP_MSG;

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
} CITIZENSHIP_ENTITY;

#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned char gm_PlayerCount;

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_QueryEntities(int, ...);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl gm_AddTime(GAME_TIMESTAMP*, int, int, int);
void __cdecl cm_SendCopyEntityData(CITIZENSHIP_MSG*);

#pragma optimize("y", off)
/* ADDRESS: GOLDDE 0x00488510 */
int __cdecl ai_RunBuergerrecht(char* entity)
{
	CITIZENSHIP_MSG m;
	GAME_TIMESTAMP st;
	int ret;
	char* s;
	char* r;
	int i;
	int slotIdx;

	s = gm_StartFilteredEntitySearch(1, 5, 0xf);
	ret = 2;
	if (s == 0) {
		return 0;
	}
	r = gm_QueryEntities(*(int*) (s + 0x5d), 2, 6, 0, 0x115);
	if (r == 0) {
		return 0;
	}
	cm_RequestTransferCurrencyNoKill(*(int*) (r + 2), *(int*) (entity + 4), 0, 0x3e80);
	cm_BeginPacketFieldDelta(entity, *(int*) (entity + 4));
	cm_AppendPacketFieldDelta(1, 1, 0xd, &ret);
	cm_RequestChangeAttribute();
	cm_RequestChangeBits(*(int*) (entity + 4), 0x1c8, 4, 0, 0x4000);
	st = (*(GAME_TIMESTAMP*)&gm_GameTime);
	gm_AddTime(&st, gm_RandomMod(4) + 1, gm_RandomMod(8) * 7, 0);
	if (entity[2] == 5) {
		i = 0;
		for (slotIdx = 0; slotIdx < 768; slotIdx++) {
			if (i >= gm_PlayerCount) {
				break;
			}
			if ((*(unsigned char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[slotIdx].entity_type) == 6 || (*(unsigned char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[slotIdx].entity_type) == 7) {
				{
					int dst;
					int n;

					n = sizeof(m);
					dst = (int) &m;
					__asm {
					mov edi, dst
					mov ebx, n
					xor eax, eax
					lea ecx, [edi+edi*2]
					and ecx, 3
					sub ebx, ecx
					jle short L1
					rep stosb
					mov ecx, ebx
					and ebx, 3
					shr ecx, 2
					rep stosd
				L1:
					add ecx, ebx
					rep stosb
					}
				}
				m.owner = (*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[slotIdx].entity_id);
				m.kind = 0x69;
				m.target = -1;
				m.code = 9;
				m.at = st;
				m.who = 2;
				m.other = *(int*) (entity + 4);
				cm_SendCopyEntityData(&m);
				i++;
			}
		}
	}
	return 0x19;
}
