/* cm_ExChangeAttribute - proper C */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char s_cm_ExChangeAttribute___Invalid_I_1002d0b0[];

/* Execution handler: applies a batch of attribute deltas to an
 * entity.  Resolves the entity, then walks the command payload's
 * field descriptors (kind/value-count/offset) and adds each value
 * sequence to the entity's memory at the given sizes (1/2/4).
 *
 * Byte-match note: PROVEN via rebrew prove.  The head now matches
 * the reference's resolved out-param pattern (separate `resolved`
 * variable keeps cmd in the base register and folds the pre-resolve
 * field store `mov [ebp+0x10],esi`), closing the Finding 38
 * fixed-point.  The three add-to-memory loops still swap register
 * roles with the reference ({count,offset,dst}->ecx, src->eax there;
 * reversed here) — a pure allocator cascade, so the function is
 * PROVEN rather than RELOC. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000e7d0
// SYMBOL: _cm_ExChangeAttribute
// SIZE: 242

int __cdecl cm_ExChangeAttribute(int cmd, char* result)
{
	void* pv8;
	void* pv4;
	int resolved;
	char* entity;
	char* src;
	char* dst2;
	unsigned short* puVar5;
	int base;
	int field;
	int ok;
	int size;
	unsigned int n;
	unsigned int i;

	base = cmd;
	field = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x10));
	ok = gm_ResolveEntityById((void**) &resolved, &pv8, &pv4, field);
	if (ok == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x31f7,
		                   s_cm_ExChangeAttribute___Invalid_I_1002d0b0, 1);
		return 1;
	}
	*(int*) (base + 0x10) = field;
	if (resolved != 0)
		entity = (char*) resolved;
	else if (pv8 != 0)
		entity = (char*) pv8;
	else
		entity = (char*) pv4;
	src = (char*) (base + 0x15);
	i = 0;
	if (*(unsigned char*) (base + 0x14) > 0) {
		do {
			size = *(signed char*) src;
			n = *(signed char*) (src + 1);
			src++;
			puVar5 = (unsigned short*) (src + 1);
			src++;
			dst2 = entity + *puVar5;
			src += 2;
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
