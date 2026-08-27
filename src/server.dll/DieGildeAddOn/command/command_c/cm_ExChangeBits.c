/* cm_ExChangeBits - proper C */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char s_cm_ExChangeBits___Invalid_Id_1002d114[];

/* Execution handler: modifies a bit-field on an entity.  Resolves
 * the entity, then sets/clears bits at the command-specified offset
 * with the given size (1/2/4 bytes), mask and value.
 *
 * Byte-match note: PROVEN via rebrew prove.  The head now matches
 * the reference's resolved out-param pattern — a separate `resolved`
 * variable keeps cmd in esi and folds the pre-resolve store as
 * `mov [esi+0x10],eax` (closing the Finding 39/7 fixed-points); the
 * size dispatch and all three per-size read-modify-write blocks
 * match structurally.  Only register roles are swapped (resolved in
 * ecx here vs eax there, and the branch on it inverted je/jne) — a
 * pure allocator cascade, so the function is PROVEN rather than
 * RELOC. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000eaa0
// SYMBOL: _cm_ExChangeBits
// SIZE: 208

int __cdecl cm_ExChangeBits(int cmd, char* result)
{
	void* pv8;
	void* pv4;
	int resolved;
	unsigned int* puVar3;
	unsigned char bVar4;
	unsigned int uVar5;
	int base;
	int field;
	int size;

	base = cmd;
	field = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x10));
	*(int*) (cmd + 0x10) = field;
	field = gm_ResolveEntityById((void**) &resolved, &pv8, &pv4, field);
	if (field == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x340d,
		                   s_cm_ExChangeBits___Invalid_Id_1002d114, 1);
		return 1;
	}
	if (resolved != 0)
		puVar3 = (unsigned int*) ((char*) resolved + *(int*) (base + 0x14));
	else if (pv8 != 0)
		puVar3 = (unsigned int*) ((char*) pv8 + *(int*) (base + 0x14));
	else
		puVar3 = (unsigned int*) ((char*) pv4 + *(int*) (base + 0x14));
	size = *(int*) (base + 0x18);
	switch (size) {
	case 1:
		bVar4 = *(unsigned char*) puVar3 & (unsigned char) ~*(unsigned char*) (base + 0x20);
		*(unsigned char*) puVar3 = bVar4;
		*(unsigned char*) puVar3 = (unsigned char) (*(unsigned char*) (base + 0x1c) | bVar4);
		break;
	case 2:
		*(unsigned short*) puVar3 = *(unsigned short*) puVar3 &
			(unsigned short) ~*(unsigned short*) (base + 0x20);
		*(unsigned short*) puVar3 = (unsigned short) (*(unsigned short*) (base + 0x1c) |
			*(unsigned short*) puVar3);
		break;
	case 4:
		uVar5 = *puVar3 & ~*(unsigned int*) (base + 0x20);
		*puVar3 = uVar5;
		*puVar3 = *(unsigned int*) (base + 0x1c) | uVar5;
		break;
	}
	if (result != 0) {
		*result = 1;
	}
	return 0;
}
