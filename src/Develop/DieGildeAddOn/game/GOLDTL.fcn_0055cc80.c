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
#include "client_data.h"
int __cdecl fcn_00500cb0(char*, char*);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
float __cdecl fcn_005101e0(char*, int, int, int);
int __cdecl gm_AccumulateTyped2(char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, int);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_004c6090(char*, int, int, int);
int __cdecl fcn_004c4450(int);
char* __cdecl fcn_004c4480(int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl cm_RequestChrMoveToUniverse(int, int, int, char*);
int __cdecl gm_RandomMod(int);
void __cdecl fcn_00500bb0(char*, int, int, int);
#include "Develop/DieGildeAddOn/game/game_data.h"
typedef struct S55cc80Proto { unsigned char bytes[0x24d]; } S55cc80Proto;
/* ADDRESS: GOLDTL 0x0055cc80 */
void __cdecl fcn_0055cc80(char* self)
{
	char buf[0x400];
	S55cc80Packet* packet;
	unsigned short* answer;
	char* q;
	int state;
	int slot;
	int started;
	int count;
	int t;
	int src;

	state = *(int*) (self + 0x70);
	switch (state) {
	case -2:
	case -1:
		fcn_00546190(self);
		return;
	case 0:
		state = *(int*) (self + 0x70) + 1;
		*(int*) (self + 0x70) = state;
		return;
	case 1:
		if (fcn_00500cb0(self + 0x52, (char*) &g_7f4c00) >= 0) {
			return;
		}
		packet = (S55cc80Packet*) gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10));
		if (packet == 0) {
			fcn_00546190(self);
			return;
		}
		slot = packet->slot;
		t = (int)fcn_005101e0((char*) &g_7f4ca0 + slot * 0x21c, packet->idx0, *(unsigned char*)(self + 0xac), -1);
		src = gm_AccumulateTyped2((char*) &g_7f4ca0 + slot * 0x21c);
		if (t > src) {
			io_FormatTextBuffer(buf, 0x1a41, (char*) packet);
			he_MessageBoxQuickjump(*(int*) ((unsigned long)&g_7f4ca4 + slot * 0x21c), *(int*) (self + 0x10), buf, 0, 0x5f2, packet->handle, *(int*) (self + 0xb4), 0, 0);
			fcn_00546190(self);
			return;
		}
		started = 0;
		{
			int* p;

			p = (int*) (self + 0xb0);
			if (*p <= 0) {
				started = 1;
			} else {
				q = (char*) fcn_004c6090((char*) packet, 1, 0, ((S55cc80Proto*)lpGebaeudePROT)[packet->idx0].bytes[0x223 + *(unsigned char*)(self + 0xac)]);
				*(int*) (self + 0xb8) = (int) q;
			}
		}
		if (started >= 1) {
			fcn_00546190(self);
			return;
		}
		state = *(int*) (self + 0x70) + 1;
		*(int*) (self + 0x70) = state;
		return;
	case 2:
		if (fcn_004c4450(*(int*) (self + 0xb8)) == 0) {
			return;
		}
		answer = (unsigned short*) fcn_004c4480(*(int*) (self + 0xb8));
		if (answer == 0) {
			fcn_00545d40(*(int*) ((unsigned long)&g_7f4ca4 + (*(unsigned short*) (self + 8)) * 0x21c), -1, (char*) 0x6a628c, 0, 0x5f8, 0);
			fcn_00546190(self);
			return;
		}
		*(int*) 0x7746d4 = 1;
		*(int*) (self + 0xbc) = *(int*) (answer + 2);
		packet = (S55cc80Packet*) gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10));
		if (packet == 0) {
			fcn_00546190(self);
			return;
		}
		q = fcn_004c4480(*(int*) (self + 0xb8));
		*(unsigned char*) (q + 0x165) = 0;
		*(unsigned char*) (q + 0x164) = ((S55cc80Proto*)lpGebaeudePROT)[packet->idx0].bytes[0x223 + *(unsigned char*)(self + 0xac)];
		{
			int* p;

			p = (int*) (self + 0xb0);
			if (*p <= 0) {
				goto move;
			}
			t = (int)fcn_005101e0((char*) &g_7f4ca0 + packet->slot * 0x21c, packet->idx0, *(unsigned char*)(self + 0xac), -1);
			*(int*) (self + 0xb0) = *(int*) (self + 0xb0) - 1;
			if (*(unsigned char*) ((unsigned long)&g_7f4ca2 + (*(unsigned short*) (self + 8)) * 0x21c) == 6 || *(unsigned char*) ((unsigned long)&g_7f4ca2 + (*(unsigned short*) (self + 8)) * 0x21c) == 7) {
				io_FormatTextBuffer(buf, 0x1bb1, t, (unsigned int)answer[0], (char*) packet);
				he_MessageBoxQuickjump(*(int*)((unsigned long)&g_7f4ca4+(*(unsigned short*)(self+8)) * 0x21c), packet->handle, buf, 0, 0x5f2, packet->handle, *(int*)(self+0xb4), 0, 0x6a6278);
			}
			fcn_004c51a0(*(int*) (answer + 2), *(int*) ((unsigned long)&g_7f4ca4 + (*(unsigned short*) (self + 8)) * 0x21c), *(unsigned char*) &g_773d75, t);
		}
	move:
		t = *(int*) (self + 0xb4);
		if (t == 0) {
			packet = (S55cc80Packet*) fcn_00502cd0(packet->kind, 1, 0, packet->id);
		} else if (t != -1) {
			goto send;
		} else {
			packet = (S55cc80Packet*) fcn_00502cd0(packet->kind, 1, 0, 0xfd);
		}
		if (packet != 0) {
			t = *(int*) ((char*) packet + 2);
		} else {
			t = -1;
		}
	send:
		cm_RequestChrMoveToUniverse(*(int*) (self + 0xbc), *(int*) (self + 0x10), t, (char*) 0x675908);
		if (*(int*) (self + 0xb0) <= 0) {
			fcn_00546190(self);
			return;
		}
		t = gm_RandomMod(10) & 0xffff;
		fcn_00500bb0(self + 0x52, 0, t + 10, 0);
		*(int*) (self + 0x70) = 1;
		return;
	}
}
