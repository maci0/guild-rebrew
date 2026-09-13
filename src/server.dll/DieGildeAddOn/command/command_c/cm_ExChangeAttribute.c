/* cm_ExChangeAttribute - proper C */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char s_cm_ExChangeAttribute___Invalid_I_1002d0b0[];

/* Execution handler: applies a batch of attribute deltas to an
 * entity.  Resolves the entity, then walks the command payload's
 * field descriptors (kind/value-count/offset) and adds each value
 * sequence to the entity's memory at the given sizes (1/2/4).
 *
 * Byte-match note: the head matches the reference's resolved out-param
 * pattern (separate `resolved` variable keeps cmd in the base register
 * and folds the pre-resolve field store `mov [ebp+0x10],esi`).  Reading
 * the descriptor with post-increments and a single `+= 2` (rather than
 * an interleaved `puVar5` alias) reproduces the reference's
 * `inc/inc/mov cx,[reg]/add reg,2` schedule.
 *
 * The descriptor-cursor/destination register pair (eax/ecx) is decided
 * by the field offset: reading it into `off`, bumping `src`, and only
 * then forming `dst2 = entity + off` puts the cursor in eax and the
 * destination in ecx as the original does.  Folding the offset load
 * directly into `dst2 = entity + *(unsigned short*) src` swaps them. */

// FUNCTION: SERVER 0x1000e7d0
// SIZE: 256

int __cdecl cm_ExChangeAttribute(int cmd, char* result)
{
	void* entity_or_node;
	void* ent_c;
	int resolved;
	char* entity;
	char* src;
	char* dst2;
	int base;
	int field;
	int ok;
	int size;
	unsigned int n;
	unsigned int i;
	unsigned int off;

	base = cmd;
	field = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x10));
	ok = gm_ResolveEntityById((void**) &resolved, &entity_or_node, &ent_c, field);
	if (ok == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x31f7,
		                   s_cm_ExChangeAttribute___Invalid_I_1002d0b0, 1);
		return 1;
	}
	*(int*) (base + 0x10) = field;
	if (resolved != 0)
		entity = (char*) resolved;
	else if (entity_or_node != 0)
		entity = (char*) entity_or_node;
	else
		entity = (char*) ent_c;
	src = (char*) (base + 0x15);
	i = 0;
	if (*(unsigned char*) (base + 0x14) > 0) {
		do {
			size = *(signed char*) src++;
			n = *(signed char*) src++;
			off = *(unsigned short*) src;
			src += 2;
			dst2 = entity + off;
			switch (size) {
			case 1:
				while (n > 0) {
					*dst2 += *src;
					src++;
					dst2++;
					n--;
				}
				break;
			case 2:
				while (n > 0) {
					*(short*) dst2 += *(short*) src;
					src += 2;
					dst2 += 2;
					n--;
				}
				break;
			case 4:
				while (n > 0) {
					*(int*) dst2 += *(int*) src;
					src += 4;
					dst2 += 4;
					n--;
				}
				break;
			}
			i++;
		} while (i < (unsigned int) *(unsigned char*) (base + 0x14));
	}
	if (result != 0) {
		*result = 1;
	}
	return 0;
}
