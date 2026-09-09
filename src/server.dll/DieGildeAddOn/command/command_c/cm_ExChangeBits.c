/* cm_ExChangeBits - proper C */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char s_cm_ExChangeBits___Invalid_Id_1002d114[];

/* Execution handler: modifies a bit-field on an entity.  Resolves
 * the entity, then sets/clears bits at the command-specified offset
 * with the given size (1/2/4 bytes), mask and value.
 *
 * Byte-match note (RELOC, 208/208): three shapes are load-bearing.
 * The `+ [base+0x14]` add is hoisted out of the three-way select and
 * applied once at the merge, matching the target's single
 * `mov ecx,[esi+0x14]; add eax,ecx`.  The select must assign puVar3
 * itself; routing it through a separate `char* sel` local scored
 * 202/208 with the pointer stuck in ecx instead of eax.  The size-1
 * and size-4 blocks re-read through the pointer for the `or` rather
 * than caching the masked value in a local; the cached form costs
 * one instruction each and scored 126/208. */

// FUNCTION: SERVER 0x1000eaa0
// SIZE: 208

int __cdecl cm_ExChangeBits(int cmd, char* result)
{
	void* pv8;
	void* pv4;
	int resolved;
	unsigned int* puVar3;
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
	/* The offset add is hoisted out of the select: the target picks the
	 * base pointer in eax, then adds [esi+0x14] once at the merge point. */
	if (resolved != 0)
		puVar3 = (unsigned int*) resolved;
	else if (pv8 != 0)
		puVar3 = (unsigned int*) pv8;
	else
		puVar3 = (unsigned int*) pv4;
	puVar3 = (unsigned int*) ((char*) puVar3 + *(int*) (base + 0x14));
	size = *(int*) (base + 0x18);
	switch (size) {
	case 1:
		*(unsigned char*) puVar3 = *(unsigned char*) puVar3 &
			(unsigned char) ~*(unsigned char*) (base + 0x20);
		*(unsigned char*) puVar3 = (unsigned char) (*(unsigned char*) (base + 0x1c) |
			*(unsigned char*) puVar3);
		break;
	case 2:
		*(unsigned short*) puVar3 = *(unsigned short*) puVar3 &
			(unsigned short) ~*(unsigned short*) (base + 0x20);
		*(unsigned short*) puVar3 = (unsigned short) (*(unsigned short*) (base + 0x1c) |
			*(unsigned short*) puVar3);
		break;
	case 4:
		*puVar3 = *puVar3 & ~*(unsigned int*) (base + 0x20);
		*puVar3 = *(unsigned int*) (base + 0x1c) | *puVar3;
		break;
	}
	if (result != 0) {
		*result = 1;
	}
	return 0;
}
