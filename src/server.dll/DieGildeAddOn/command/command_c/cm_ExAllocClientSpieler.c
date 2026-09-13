/* Ghidra decompilation reference:
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

ushort __cdecl gm_AllocSpieler(uint, int, int, ushort, int, uint, uint, uint);
char* __cdecl strncpy(char*, const char*, unsigned int);

/* Execution handler: allocates a client-side player entity.
 * Similar to cm_ExAllocSpieler but for client-connected players,
 * updating player slot flags and setting connection state.
 *
 * RELOC 361/361.  Keeping the entity slot as an explicit `off` and
 * folding the g_static_entity_table base into each access reproduces
 * the reference's `lea esi,[eax+eax*8]; shl esi,2` offset form.
 *
 * The first argument must be written as an if/else, not `result ? 6 : 7`.
 * The ternary makes MSVC6 sink the computation to just before the call
 * and put it in ecx; the if/else emits `mov eax,[esp+0x18]; neg eax;
 * sbb eax,eax` right after srand and folds the `add eax,7` into the
 * argument push sequence, matching the reference.  That single change
 * took the function from 287/361 to 361/361.
 *
 * Dead ends against the same cluster, all still 287 or worse:
 * `7 - (result != 0)`, `6 + (result == 0)`, `result == 0 ? 7 : 6`,
 * a `volatile` kind (96/375), hoisting the ternary into the call
 * argument list, and hoisting the trailing gm_AllocSpieler
 * args into locals (86/363). */



// FUNCTION: SERVER 0x1000d570
int __cdecl cm_ExAllocClientSpieler(int cmd, char* result)
{
	unsigned int entity;
	short* entry;
	char* r2;
	int hash_index;
	int off;

	{
		char* c = (char*) cmd;
		unsigned int kind;
		*(int*)(c + 0x10) = g_next_object_id;
		*(int*)(c + 0x45) = rand();
		srv_SeedRandom(*(int*)(c + 0x22));
		if (result)
			kind = 6;
		else
			kind = 7;
		entity = gm_AllocSpieler(kind,
			*(int*)(c + 0x14), *(int*)(c + 0x18),
			*(unsigned short*)(c + 0x1c), 0,
			(unsigned char)*(char*)(c + 0x1e), 0,
			(unsigned char)*(char*)(c + 0x23));
	}
	entity = entity & 0xffff;
	if (entity == 0xffff) {
		LogMessageInternal((char*)0x1002c748, 0x290f, (char*)0x1002cbd4, 1);
		return 1;
	}
	LogMessageInternal((char*)0x1002c748, 0x2917, (char*)0x1002cbbc, 1);
	off = entity * 0x21c;
	hash_index = 0x99099 * (unsigned char)*(char*)(cmd + 3);
	*(int*)(0x10442d00 + hash_index * 4) = *(int*)(g_slot_table + off + 4);
	strncpy(g_slot_table + off + 0x30, (char*)cmd + 0x25, 0x10);
	entry = gm_GetEntityTableEntry(g_slot_table + off);
	if (entry != 0) {
		*(unsigned short*)entry = *(unsigned short*)(g_slot_table + off + 0x50);
		strncpy((char*)entry + 2, (char*)cmd + 0x35, 0x10);
		strncpy(g_slot_table + off + 0x40, (char*)cmd + 0x35, 0x10);
		r2 = (char*)gm_LookupEntityRecordById(*(int*)(g_slot_table + off + 0x60));
		if (r2 != 0)
			strncpy(r2 + 0x40, (char*)cmd + 0x35, 0x10);
	}
	*(int*)(g_slot_table + off + 0x54) = *(int*)(cmd + 0x1f);
	*(unsigned char*)(g_slot_table + off + 0xc) = *(unsigned char*)(cmd + 0x24);
	if (result != (char*)0) {
		result[0] = 1;
		result[1] = 1;
		*(char**)(result + 6) = g_slot_table + off;
	}
	return 0;
}
