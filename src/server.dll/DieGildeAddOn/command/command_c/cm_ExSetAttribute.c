
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

#include "../../../Units/Error/error.h"
#include "../command_internal.h"

extern char s_cm_ExSetAttribute___Invalid_Id_1002d0d4[];

/* Command handler: applies attribute updates to a game entity.
 * Resolves the target entity by ID from the command packet (offset 0x10),
 * then iterates over a list of field descriptors starting at offset 0x15.
 * Each descriptor contains: fieldSize (1/2/4 bytes), count, and a 16-bit
 * offset into the entity struct. Copies 'count' elements of the given size
 * from the command buffer into the entity at the specified offset.
 * Sets *param_2 = 1 on success (if non-null). Returns 1 on invalid entity ID.
 *
 * Shape follows the byte-matching sibling cm_ExChangeAttribute (0x1000e7d0):
 * a separate `resolved` out-param variable keeps cmd in the base register,
 * and the pre-resolve field store is emitted after the resolve call. */

// FUNCTION: SERVER 0x1000e8d0
int __cdecl cm_ExSetAttribute(int cmd, char* result)
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
	*(int*) (base + 0x10) = field;
	ok = gm_ResolveEntityById((void**) &resolved, &entity_or_node, &ent_c, field);
	if (ok == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x32ed,
		                   s_cm_ExSetAttribute___Invalid_Id_1002d0d4, 1);
		return 1;
	}
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
					*dst2 = *src;
					dst2++;
					src++;
					n--;
				}
				break;
			case 2:
				while (n > 0) {
					*(short*) dst2 = *(short*) src;
					src += 2;
					dst2 += 2;
					n--;
				}
				break;
			case 4:
				while (n > 0) {
					*(int*) dst2 = *(int*) src;
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

#ifdef __clang__
#pragma clang diagnostic pop
#endif
