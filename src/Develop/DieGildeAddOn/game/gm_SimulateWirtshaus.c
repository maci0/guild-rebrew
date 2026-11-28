#include "Develop/DieGildeAddOn/game/entity_record.h"
#pragma optimize("y", off)
#include <string.h>
extern char gm_EntitySlotTable[];
extern char g_6a5e88[];
extern char gm_ActiveTownIndex;
extern short cm_PacketDeltaBase;
extern float g_665e9c;
extern double dbl_1_5;

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_QueryEntities(int, ...);
char* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl he_FreeAction(char*);
int __cdecl gm_FindMatchingSimEntry(short*, int*, int*);
float __cdecl gm_GetSeasonPrice(int, unsigned char);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl gm_AccumulateTyped2(int);
void __cdecl cm_SendLogAction(unsigned int);
void __cdecl cm_SendTraceEnd(unsigned int);
int __cdecl cm_SendSellObjekt(int, int, short, int, char, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
int __cdecl cm_AppendPacketFieldValue(unsigned char, unsigned char, short, void*);
void __cdecl cm_BeginPacketFieldDelta(int, int);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl gm_AddTime(int*, int, int, int);

/* ADDRESS: GOLDTL 0x00555510 */
void __cdecl gm_SimulateWirtshaus(char* action)
{
	struct {
		unsigned char* p0;
		char* p4;
		char* p8;
	} ent[16];
	int v;
	int x1;
	int y1;
	int count;
	int mx;
	int idx;
	int end;
	int w;
	int i;
	char* p;
	char* q;

	if (*(int*) (action + 0x70) == -2) {
		he_FreeAction(action);
		return;
	}
	p = (char*) ent; count = sizeof(ent);
	__asm {
		mov edi, p
		mov ebx, count
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short fill_done_555510
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	fill_done_555510:
		add ecx, ebx
		rep stosb
	}

	i = 0;
	ent[0].p0 = (unsigned char*) gm_StartFilteredEntitySearch(1, 5, 0x16);
	if (ent[0].p0 != 0) {
		p = (char*) ent;
		do {
			if (i >= 0x10) {
				break;
			}
			q = gm_QueryEntities(*(int*) (*(char**) p + 0x5d), 2, 0, 0x2a, 6);
			if (q != 0) {
				*(int*) (p + 4) = (int) gm_QueryEntities(*(int*) (q + 0x14), 1, 0, 0x179);
				*(int*) (p + 8) = (int) gm_QueryEntities(*(int*) (q + 0x14), 1, 0, 0x17a);
			}
			i++;
			p += 0xc;
		} while ((*(int*) p = (int) gm_FindNextFilteredEntity()) != 0);
	}
	if (*(int*) (action + 0x70) != 0) {
		return;
	}
	i = *(int*) (action + 0xac);
	end = i + 0x180;
	for (; i < end; i++) {
		if (gm_FindMatchingSimEntry((short*) ((char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[i]), (int*) ent, &idx) != 0) {
			x1 = (int) (gm_GetSeasonPrice(0x179, gm_ActiveTownIndex) * dbl_1_5);
			y1 = (int) (gm_GetSeasonPrice(0x17a, gm_ActiveTownIndex) * dbl_1_5);
			v = gm_RandomMod(4) + 3;
			w = gm_AccumulateTyped2((int) ((char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[i]));
			mx = x1;
			if (x1 <= y1) {
				mx = y1;
			}
			if ((float) w > (float) mx * g_665e9c && ent[idx].p4 != 0 && ent[idx].p8 != 0) {
				if ((unsigned short) gm_RandomMod(2) != 0) {
					cm_SendLogAction((unsigned int) g_6a5e88);
					cm_SendSellObjekt(-1, *(int*) (ent[idx].p4 + 6), 0x179, 1, gm_ActiveTownIndex, 0);
					cm_RequestTransferCurrencyNoKill(-1, *(unsigned int*) ((char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[i] + 4), gm_ActiveTownIndex, (int) ((float) x1 * g_665e9c));
					cm_RequestTransferCurrencyNoKill(*(unsigned int*) ((char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (ent[idx].p0 + 0x27)] + 4), -1, gm_ActiveTownIndex, x1);
					cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
					cm_AppendPacketFieldValue(4, 1, (int) *(unsigned short*) ent[idx].p0 - cm_PacketDeltaBase + 0x65, &x1);
					cm_AppendPacketFieldValue(2, 1, (int) *(unsigned short*) ent[idx].p0 - cm_PacketDeltaBase + 0x6b, &v);
					cm_RequestChangeAttribute();
					cm_SendTraceEnd((unsigned int) g_6a5e88);
					cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
					cm_AppendPacketFieldValue(2, 1, (int) *(unsigned short*) ent[idx].p0 - cm_PacketDeltaBase + 0x69, &v);
					cm_RequestChangeAttribute();
				} else {
					cm_SendLogAction((unsigned int) g_6a5e88);
					cm_SendSellObjekt(-1, *(int*) (ent[idx].p8 + 6), 0x17a, 1, gm_ActiveTownIndex, 0);
					cm_RequestTransferCurrencyNoKill(-1, *(unsigned int*) ((char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[i] + 4), gm_ActiveTownIndex, (int) ((float) y1 * g_665e9c));
					cm_RequestTransferCurrencyNoKill(*(unsigned int*) ((char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (ent[idx].p0 + 0x27)] + 4), -1, gm_ActiveTownIndex, y1);
					cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
					cm_AppendPacketFieldValue(4, 1, (int) *(unsigned short*) ent[idx].p0 - cm_PacketDeltaBase + 0x65, &y1);
					cm_AppendPacketFieldValue(2, 1, (int) *(unsigned short*) ent[idx].p0 - cm_PacketDeltaBase + 0x6b, &v);
					cm_RequestChangeAttribute();
					cm_SendTraceEnd((unsigned int) g_6a5e88);
					cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
					cm_AppendPacketFieldValue(2, 1, (int) *(unsigned short*) ent[idx].p0 - cm_PacketDeltaBase + 0x69, &v);
					cm_RequestChangeAttribute();
				}
			} else if (w > x1 && ent[idx].p4 != 0) {
				cm_SendLogAction((unsigned int) g_6a5e88);
				cm_SendSellObjekt(-1, *(int*) (ent[idx].p4 + 6), 0x179, 1, gm_ActiveTownIndex, 0);
				cm_RequestTransferCurrencyNoKill(-1, *(unsigned int*) ((char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[i] + 4), gm_ActiveTownIndex, (int) ((float) x1 * g_665e9c));
				cm_RequestTransferCurrencyNoKill(*(unsigned int*) ((char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (ent[idx].p0 + 0x27)] + 4), -1, gm_ActiveTownIndex, x1);
				cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
				cm_AppendPacketFieldValue(4, 1, (int) *(unsigned short*) ent[idx].p0 - cm_PacketDeltaBase + 0x65, &x1);
				cm_AppendPacketFieldValue(2, 1, (int) *(unsigned short*) ent[idx].p0 - cm_PacketDeltaBase + 0x6b, &v);
				cm_RequestChangeAttribute();
				cm_SendTraceEnd((unsigned int) g_6a5e88);
				cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
				cm_AppendPacketFieldValue(2, 1, (int) *(unsigned short*) ent[idx].p0 - cm_PacketDeltaBase + 0x69, &v);
				cm_RequestChangeAttribute();
			} else if (w > y1) {
				if (ent[idx].p8 != 0) {
					cm_SendLogAction((unsigned int) g_6a5e88);
					cm_SendSellObjekt(-1, *(int*) (ent[idx].p8 + 6), 0x17a, 1, gm_ActiveTownIndex, 0);
					cm_RequestTransferCurrencyNoKill(-1, *(unsigned int*) ((char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[i] + 4), gm_ActiveTownIndex, (int) ((float) y1 * g_665e9c));
					cm_RequestTransferCurrencyNoKill(*(unsigned int*) ((char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (ent[idx].p0 + 0x27)] + 4), -1, gm_ActiveTownIndex, y1);
					cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
					cm_AppendPacketFieldValue(4, 1, (int) *(unsigned short*) ent[idx].p0 - cm_PacketDeltaBase + 0x65, &y1);
					cm_AppendPacketFieldValue(2, 1, (int) *(unsigned short*) ent[idx].p0 - cm_PacketDeltaBase + 0x6b, &v);
					cm_RequestChangeAttribute();
					cm_SendTraceEnd((unsigned int) g_6a5e88);
					cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
					cm_AppendPacketFieldValue(2, 1, (int) *(unsigned short*) ent[idx].p0 - cm_PacketDeltaBase + 0x69, &v);
					cm_RequestChangeAttribute();
				} else if (w > x1) {
					cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
					cm_AppendPacketFieldValue(2, 1, (int) *(unsigned short*) ent[idx].p0 - cm_PacketDeltaBase + 0x69, &v);
					cm_RequestChangeAttribute();
				}
			}
		}
	}
	*(int*) (action + 0xac) = end;
	if (end >= 0x300) {
		*(int*) (action + 0xac) = 0;
		*(int*) (action + 0xb0) = 0;
		*(int*) (action + 0x52) = *(int*) (action + 0x52) + 1;
		*(unsigned short*) (action + 0x56) = 0x16;
		*(int*) (action + 0x58) = 0x1e;
		return;
	}
	gm_AddTime((int*) (action + 0x52), 0, 0xf, 0);
}
