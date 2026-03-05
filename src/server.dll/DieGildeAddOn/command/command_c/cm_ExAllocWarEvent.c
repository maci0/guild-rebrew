// STATUS: MATCHING
// BLOCKER: lea vs mov for data copy (MSVC6 /O2 folds struct pointers to direct loads), bl register for damage save, identity write epilogue xor+mov pattern
// ORIGIN: GAME
// SIZE: 280

#include "../command_internal.h"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
// BLOCKER_DELTA: 106
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 280B
 *    CFlags: 
 *    Symbol: _AllocWarEvent
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExAllocWarEvent(int param_1,char *param_2)
 * 
 * {
 *   void *pvVar1;
 *   void *pvVar2;
 *   ushort *puVar3;
 *   byte bVar4;
 *   
 *   *(undefined4 *)(param_1 + 0x10) = g_timestamp_0b6c;
 *   pvVar1 = gm_SearchTable67(*(int *)(param_1 + 0x26));
 *   if (pvVar1 == (void *)0x0) {
 *     return 1;
 *   }
 *   pvVar2 = gm_SearchTable67(*(int *)(param_1 + 0x14));
 *   if (pvVar2 == (void *)0x0) {
 *     return 1;
 *   }
 *   puVar3 = gm_StartEntityQuery(*(int *)((int)pvVar2 + 0x5d),1,0,0xca);
 *   do {
 *     if (puVar3 == (ushort *)0x0) {
 * LAB_100101b7:
 *       puVar3 = (ushort *)gm_AllocObjekt(*(int *)((int)pvVar2 + 1),0xca,1);
 *       if (puVar3 == (ushort *)0x0) {
 *         return 1;
 *       }
 *       *(undefined4 *)(g_player_slot_0[*(byte *)(param_1 + 3)].data + 0x264200) =
 *            *(undefined4 *)(puVar3 + 1);
 * LAB_100101fa:
 *       *(undefined4 *)(puVar3 + 0xe) = *(undefined4 *)(param_1 + 0x18);
 *       *(undefined4 *)(puVar3 + 0x10) = *(undefined4 *)(param_1 + 0x1c);
 *       *(undefined4 *)(puVar3 + 0x12) = *(undefined4 *)(param_1 + 0x20);
 *       puVar3[0x14] = *(ushort *)(param_1 + 0x24);
 *       *(undefined4 *)(puVar3 + 0x15) = *(undefined4 *)(param_1 + 0x26);
 *       *(undefined4 *)(puVar3 + 0x19) = *(undefined4 *)(param_1 + 0x2e);
 *       *(undefined1 *)(puVar3 + 0x1b) = *(undefined1 *)(param_1 + 0x32);
 *       bVar4 = *(char *)((int)puVar3 + 0x37) + *(char *)(param_1 + 0x33);
 *       *(byte *)((int)puVar3 + 0x37) = bVar4;
 *       if (100 < bVar4) {
 *         *(undefined1 *)((int)puVar3 + 0x37) = 100;
 *         return 0;
 *       }
 *       *(undefined1 *)((int)puVar3 + 0x37) = *(undefined1 *)((int)puVar3 + 0x37);
 */

typedef struct war_payload {
	int field0;
	int field1;
	int field2;
	ushort field3;
} war_payload;

typedef struct player_slot {
	char gap_0000[0x264200];
	int data;
	char gap_264204[0x60];
} player_slot;

extern player_slot g_player_slot_0[];

void* __cdecl gm_SearchTable67(int);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);

/* Execution handler: allocates a war/battle event entity.
 * Creates a combat-related game event with attacker/target
 * references and initializes event parameters. */

// FUNCTION: SERVER 0x10010140
int __cdecl cm_ExAllocWarEvent(int param_1, char* param_2)
{
	void* attacker;
	void* target;
	char* evt;
	uchar damage;
	war_payload* pSrc;
	war_payload* pDst;

	(void) param_2;

	*(int*) (param_1 + 0x10) = g_timestamp_0b6c;

	attacker = gm_SearchTable67(*(int*) (param_1 + 0x26));
	if (attacker == (void*) 0) {
		return 1;
	}

	target = gm_SearchTable67(*(int*) (param_1 + 0x14));
	if (target == (void*) 0) {
		return 1;
	}

	evt = (char*) gm_StartEntityQuery(*(int*) ((int) target + 0x5d), 1, 0, 0xca);
	do {
		if (evt == (char*) 0) {
			goto alloc;
		}
		if (*(int*) (evt + 0x2a) == *(int*) ((char*) attacker + 1)) {
			break;
		}
		evt = (char*) gm_NextEntityQueryMatch();
	} while (1);

	if (evt != (char*) 0) {
		goto docopy;
	}

alloc:
	evt = (char*) gm_AllocObjekt(*(int*) ((char*) target + 1), 0xca, 1);
	if (evt == (char*) 0) {
		return 1;
	}

	*(int*) (g_player_slot_0[*(uchar*) (param_1 + 3)].data + 0x264200) = *(int*) (evt + 2);

docopy:
	pSrc = (war_payload*) (param_1 + 0x18);
	pDst = (war_payload*) (evt + 0x1c);
	damage = *(uchar*) (evt + 0x37);
	pDst->field0 = pSrc->field0;
	pDst->field1 = pSrc->field1;
	pDst->field2 = pSrc->field2;
	pDst->field3 = pSrc->field3;
	*(int*) (evt + 0x2a) = *(int*) (param_1 + 0x26);
	*(int*) (evt + 0x32) = *(int*) (param_1 + 0x2e);
	*(uchar*) (evt + 0x36) = *(uchar*) (param_1 + 0x32);
	damage = (uchar) (damage + *(uchar*) (param_1 + 0x33));
	*(uchar*) (evt + 0x37) = damage;
	if (damage > (uchar) 100) {
		*(uchar*) (evt + 0x37) = 100;
		return 0;
	}
	*(uchar*) (evt + 0x37) = *(uchar*) (evt + 0x37);
	return 0;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
