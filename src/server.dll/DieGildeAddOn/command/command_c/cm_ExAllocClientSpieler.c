/* Ghidra decompilation reference:
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

ushort __cdecl gm_CreateEntityFromParents(uint, int, int, ushort, int, uint, uint, uint);
char* __cdecl strncpy(char*, const char*, unsigned int);

/* Execution handler: allocates a client-side player entity.
 * Similar to cm_ExAllocSpieler but for client-connected players,
 * updating player slot flags and setting connection state.
 *
 * Conversion state: pure C (naked wrapper removed).  The head diverges
 * on MSVC6 register allocation: the reference keeps cmd in edi, entity
 * in esi and materializes the `result ? 6 : 7` first arg first in eax
 * (`mov ebx,[esp+0x18]; mov eax,ebx; neg eax; sbb eax,eax; add eax,7`);
 * every C formulation allocates cmd→esi/entity→edi and computes the
 * conditional last in ecx — best-effort 142/361
 * (docs/msvc6-allocator.md GRA class). */



// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000d570
int __cdecl cm_ExAllocClientSpieler(int cmd, char* result)
{
	unsigned int entity;
	char* rec;
	short* t;
	char* r2;
	int f;

	{
		char* c = (char*) cmd;
		*(int*)(c + 0x10) = g_timestamp_0b6c;
		*(int*)(c + 0x45) = rand();
		srand(*(int*)(c + 0x22));
		entity = gm_CreateEntityFromParents(result ? 6 : 7,
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
	rec = (char*)g_static_entity_table_358a0 + entity * 0x21c;
	f = 0x99099 * (unsigned char)*(char*)(cmd + 3);
	*(int*)(0x10442d00 + f * 4) = *(int*)(rec + 4);
	strncpy(rec + 0x30, (char*)cmd + 0x25, 0x10);
	t = gm_GetEntityTableEntry(rec);
	if (t != 0) {
		*(unsigned short*)t = *(unsigned short*)(rec + 0x50);
		strncpy((char*)t + 2, (char*)cmd + 0x35, 0x10);
		strncpy(rec + 0x40, (char*)cmd + 0x35, 0x10);
		r2 = (char*)gm_LookupEntityRecordById(*(int*)(rec + 0x60));
		if (r2 != 0)
			strncpy(r2 + 0x40, (char*)cmd + 0x35, 0x10);
	}
	*(int*)(rec + 0x54) = *(int*)(cmd + 0x1f);
	*(unsigned char*)(rec + 0xc) = *(unsigned char*)(cmd + 0x24);
	if (result != (char*)0) {
		result[0] = 1;
		result[1] = 1;
		*(char**)(result + 6) = rec;
	}
	return 0;
}
