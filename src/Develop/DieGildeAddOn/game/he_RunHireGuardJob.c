/*
 * Kugel (ball) packet state machine, one step per frame.
 *
 * The state word lives at self+0x70. States below zero only unlink the
 * instance; state 0 arms state 1, state 1 sends the ball request when the
 * network slot is free and builds the local packet, state 2 waits for the
 * answer, moves the ball once, and then restarts the timer with a random
 * delay. The local packet buffer holds the map slot index at +0x27, the
 * source index at +0, the object handle at +1 and an id at +0x29.
 */
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#pragma pack(push, 1)
typedef struct S55cc80Packet {
	unsigned char idx0;
	int handle;
	char pad05[0x22];
	unsigned short slot;
	unsigned short id;
	char pad2b[0x32];
	int kind;
} S55cc80Packet;
#pragma pack(pop)
#include "Develop/DieGildeAddOn/game/client_data.h"
extern int g_7746d4;
int __cdecl gm_CompareGameTime(char*, char*);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
float __cdecl gm_GetScaledWorkforceOutput(char*, int, int, int);
int __cdecl gm_AccumulateTyped2(char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, int);
void __cdecl he_FreeAction(char*);
int __cdecl cm_RequestAssignWorker(char*, int, int, int);
int __cdecl cm_GetCommandStatus(int);
char* __cdecl cm_GetCommandResult(int);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
char* __cdecl gm_QueryEntities(int, int, int, int);
void __cdecl cm_RequestChrMoveToUniverse(int, int, int, char*);
int __cdecl gm_RandomMod(int);
void __cdecl gm_AddTime(char*, int, int, int);
#include "Develop/DieGildeAddOn/game/game_data.h"
typedef struct S55cc80Proto { unsigned char bytes[0x24d]; } S55cc80Proto;
/* ADDRESS: GOLDTL 0x0055cc80 */
void __cdecl he_RunHireGuardJob(char* self)
{
	char buf[0x400];
	S55cc80Packet* packet;
	unsigned short* answer;
	char* q;
	char* row;
	int state, started, count;
	int t;
	int src; BUILDING_PROTOTYPE* proto; unsigned char job;
#include "Develop/DieGildeAddOn/game/entity_record.h"
	state = *(int*) (self + 0x70);
	switch (state) {
	case 1:
		if (gm_CompareGameTime(self + 0x52, (char*) &gm_GameTime) >= 0) {
			return;
		}
		packet = (S55cc80Packet*) gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10));
		if (packet == 0) {
			he_FreeAction(self);
			return;
		}
		row = (char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[packet->slot];
		t = (int)gm_GetScaledWorkforceOutput(row, packet->idx0, *(unsigned char*)(self + 0xac), -1);
		proto = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[packet->idx0];
		src = gm_AccumulateTyped2((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[packet->slot]);
		if (t > src) {
			io_FormatTextBuffer(buf, 0x1a41, (char*) packet);
			he_MessageBoxQuickjump(*(int*) ((unsigned long)&gm_EntityIdField + packet->slot * 0x21c), *(int*) (self + 0x10), buf, 0, 0x5f2, packet->handle, *(int*) (self + 0xb4), 0, 0);
			he_FreeAction(self);
			return;
		}
		started = 0;
		{
			int* p;
			p = (int*) (self + 0xb0);
			for (; started < 1; started++, p++) {
				if (*p > 0) {
					q = (char*) cm_RequestAssignWorker((char*) packet, 1, 0, ((unsigned char*)proto)[0x223 + *(unsigned char*)(self + 0xac)]);
					*(int*) (self + 0xb8) = (int) q;
					break;
				}
			}
		}
		if (started >= 1) {
			he_FreeAction(self);
			return;
		}
		state = *(int*) (self + 0x70);
	case 0:
		state++;
		*(int*) (self + 0x70) = state;
		return;
	case 2:
		if (cm_GetCommandStatus(*(int*) (self + 0xb8)) == 0) {
			return;
		}
		answer = (unsigned short*) cm_GetCommandResult(*(int*) (self + 0xb8));
		if (answer == 0) {
			he_PostEntityMessage(*(int*) ((unsigned long)&gm_EntityIdField + (*(unsigned short*) (self + 8)) * 0x21c), -1, (char*) 0x6a628c, 0, 0x5f8, 0);
			he_FreeAction(self);
			return;
		}
		g_7746d4 = 1;
		*(int*) (self + 0xbc) = *(int*) (answer + 2);
		packet = (S55cc80Packet*) gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10));
		if (packet == 0) {
			he_FreeAction(self);
			return;
		}
		proto = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[packet->idx0];
		q = cm_GetCommandResult(*(int*) (self + 0xb8));
		job = ((unsigned char*)proto)[0x223 + *(unsigned char*)(self + 0xac)];
		*(unsigned char*) (q + 0x164) = job;
		*(unsigned char*) (q + 0x165) = 0;
		for (count = 0; count < 1; count++) {
			if (((int*) (self + 0xb0))[count] <= 0) {
				continue;
			}
			row = (char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[packet->slot];
			t = (int)gm_GetScaledWorkforceOutput(row, packet->idx0, *(unsigned char*)(self + 0xac), -1);
			((int*) (self + 0xb0))[count] = ((int*) (self + 0xb0))[count] - 1;
			if (*(unsigned char*) ((unsigned long)&gm_SlotTableKindView + (*(unsigned short*) (self + 8)) * 0x21c) == 6 ||
				*(unsigned char*) ((unsigned long)&gm_SlotTableKindView + (*(unsigned short*) (self + 8)) * 0x21c) == 7) {
				io_FormatTextBuffer(buf, 0x1bb1, t, (unsigned int)answer[0], (char*) packet);
				he_MessageBoxQuickjump(*(int*)((unsigned long)&gm_EntityIdField+(*(unsigned short*)(self+8)) * 0x21c), packet->handle, buf, 0, 0x5f2, packet->handle, *(int*)(self+0xb4), 0, 0x6a6278);
			}
			cm_RequestTransferCurrencyNoKill(*(int*) (answer + 2), *(int*) ((unsigned long)&gm_EntityIdField + (*(unsigned short*) (self + 8)) * 0x21c), *(unsigned char*) &gm_ActiveTownIndex, t);
			break;
		}
		t = *(int*) (self + 0xb4);
		if (t != 0) {
			if (t != -1) {
				goto send;
			}
			packet = (S55cc80Packet*) gm_QueryEntities(packet->kind, 1, 0, 0xfd);
		} else {
			packet = (S55cc80Packet*) gm_QueryEntities(packet->kind, 1, 0, packet->id);
		}
		if (packet != 0) {
			t = *(int*) ((char*) packet + 2);
		} else {
			t = -1;
		}
	send:
		cm_RequestChrMoveToUniverse(*(int*) (self + 0xbc), *(int*) (self + 0x10), t, (char*) 0x675908);
		for (count = 0; count < 1; count++) {
			if (((int*) (self + 0xb0))[count] > 0) break;
		}
		if (count >= 1) {
			he_FreeAction(self);
			return;
		}
		gm_AddTime(self + 0x52, 0, (gm_RandomMod(10) & 0xffff) + 10, 0);
		*(int*) (self + 0x70) = 1;
		return;
	case -2:
	case -1:
		he_FreeAction(self);
		return;
	}
}
