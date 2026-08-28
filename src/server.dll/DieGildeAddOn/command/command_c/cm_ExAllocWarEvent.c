/* cm_ExAllocWarEvent - proper C */

#include "../command_internal.h"

extern char g_player_slot_0[];
extern void* __cdecl gm_SearchTable67(int);
extern unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
extern unsigned short* __cdecl gm_NextEntityQueryMatch(void);
extern char* __cdecl gm_AllocObjekt(int, int, int);

/* 14-byte war-event field block copied from cmd+0x18 to obj+0x1c. */
#pragma pack(1)
typedef struct war_event_fields {
	int f0;
	int f4;
	int f8;
	unsigned short fc;
} war_event_fields;
#pragma pack()

/* Execution handler: allocates a war/battle event entity.  Resolves
 * attacker and target entities, reuses an existing matching event if
 * one is already queued, and initializes the event parameters.
 *
 * Byte-match note: everything through the player-slot link store
 * (timestamp store, both SearchTable67 calls, the query loop, the
 * alloc and the `lea [ecx+ecx*8]` slot-index chain) matches
 * byte-for-byte, and the trailing 14-byte event copy is reproduced
 * with a packed-struct assignment (`lea ecx,[esi+0x18]` /
 * `lea edx,[eax+0x1c]`, [reg+disp] copies via edi, `mov bl,[eax+0x37]`
 * hoisted before the copy) plus the obj+0x2a/0x32/0x36 stores.  Best
 * effort is 274/280 (obj 274, 258 matched): the clamp epilogue
 * diverges only in the reference's `mov ecx,0x64; mov [eax+0x37],cl`
 * register-form constant store (MSVC6 here always folds to the 4-byte
 * immediate) and the fall-through reload's `xor ecx,ecx` zero-extension
 * (volatile self-assign keeps the separate reload block but picks dl
 * without the xor).  Both are allocation details not steerable from C;
 * a volatile self-assignment reproduces the reference's separate
 * no-clamp return block. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10010140
// SYMBOL: _cm_ExAllocWarEvent
// SIZE: 280

int __cdecl cm_ExAllocWarEvent(int cmd, char* result)
{
	void* attacker;
	void* target;
	unsigned short* q;
	char* obj;
	unsigned int slot_idx;

	(void) result;

	*(int*) (cmd + 0x10) = g_timestamp_0b6c;
	attacker = gm_SearchTable67(*(int*) (cmd + 0x26));
	if (attacker == 0) {
		return 1;
	}
	target = gm_SearchTable67(*(int*) (cmd + 0x14));
	if (target == 0) {
		return 1;
	}
	q = gm_StartEntityQuery(*(int*) ((char*) target + 0x5d), 1, 0, 0xca);
	while (q != 0) {
		if (*(int*) ((char*) q + 0x2a) == *(int*) ((char*) attacker + 1)) {
			break;
		}
		q = gm_NextEntityQueryMatch();
	}
	if (q == 0) {
		obj = gm_AllocObjekt(*(int*) ((char*) target + 1), 0xca, 1);
		if (obj == 0) {
			return 1;
		}
		slot_idx = (unsigned int) *(unsigned char*) (cmd + 3);
		*(int*) (g_player_slot_0 + slot_idx * 0x264264 + 0x264208) = *(int*) (obj + 2);
	} else {
		obj = (char*) q;
	}
	{
		*(war_event_fields*) ((char*) obj + 0x1c) = *(war_event_fields*) ((char*) cmd + 0x18);
	}
	*(int*) (obj + 0x2a) = *(int*) (cmd + 0x26);
	*(int*) (obj + 0x32) = *(int*) (cmd + 0x2e);
	*(unsigned char*) (obj + 0x36) = *(unsigned char*) (cmd + 0x32);
	*(unsigned char*) (obj + 0x37) = (unsigned char) (*(unsigned char*) (obj + 0x37) +
	                                                  *(unsigned char*) (cmd + 0x33));
	if (*(unsigned char*) (obj + 0x37) > 100) {
		*(unsigned char*) (obj + 0x37) = 100;
		return 0;
	}
	*(volatile unsigned char*) (obj + 0x37) = *(volatile unsigned char*) (obj + 0x37);
	return 0;
}
