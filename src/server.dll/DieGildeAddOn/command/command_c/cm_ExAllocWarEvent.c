/* cm_ExAllocWarEvent - proper C */

#include "../command_internal.h"

extern char g_connections[];
extern void* __cdecl gm_SearchTable67(int);
extern unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
extern unsigned short* __cdecl gm_NextEntityQueryMatch(void);
extern char* __cdecl gm_AllocObjekt(int, int, int);

/* 14-byte war-event field block copied from cmd+0x18 to obj+0x1c. */
#pragma pack(1)
// SIZE 0xe
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
 * The clamp epilogue needs a 32-bit `clamped` temp assigned in both
 * arms of the if/else and stored once after the join.  That form emits
 * the reference's `mov ecx,0x64` / `xor ecx,ecx; mov cl,[eax+0x37]`
 * register-width materialization; storing the constant or the reloaded
 * byte directly at each return folds to an immediate store instead. */

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
	unsigned int clamped;

	(void) result;

	*(int*) (cmd + 0x10) = g_next_object_id;
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
		*(int*) (g_connections + slot_idx * 0x264264 + 0x264208) = *(int*) (obj + 2);
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
		clamped = 100;
	} else {
		clamped = *(unsigned char*) (obj + 0x37);
	}
	*(unsigned char*) (obj + 0x37) = (unsigned char) clamped;
	return 0;
}
