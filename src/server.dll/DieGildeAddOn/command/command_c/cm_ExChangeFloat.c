/* cm_ExChangeFloat - proper C */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char s_cm_ExChangeFloat___Invalid_Id_1002d134[];

/* Execution handler: modifies a floating-point attribute on an
 * entity. Resolves the entity, then adds the command's float delta
 * to the field at the given offset. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000eb70
// SIZE: 144

int __cdecl cm_ExChangeFloat(int cmd, char* result)
{
	void* ent_a;
	void* ent_c;
	int resolved;
	int cmd_base;
	int object_id;
	int entity;

	cmd_base = cmd;
	object_id = gm_GetFieldByType(cmd, *(int*) (cmd + 0x10));
	*(int*) (cmd + 0x10) = object_id;
	object_id = gm_ResolveEntityById(&ent_c, &ent_a, (void**) &resolved, object_id);
	if (object_id == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x347f,
		                   s_cm_ExChangeFloat___Invalid_Id_1002d134, 1);
		return 1;
	}
	entity = resolved;
	if (entity == 0)
		entity = (int) ent_a;
	if (entity == 0)
		entity = (int) ent_c;
	/* Folding the offset into entity before the load puts the offset temp in
	 * edx; re-reading it inside the store expression keeps it in ecx. */
	entity = entity + *(int*) (cmd_base + 0x14);
	*(float*) entity = *(float*) (cmd_base + 0x18) + *(float*) entity;
	if (result != (char*) 0x0) {
		*result = '\x01';
	}
	return 0;
}
