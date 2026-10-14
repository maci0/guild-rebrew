/* gv_ValidateEntityAction - validates a standard entity action command:
 * resolves the target entity, checks it is an active graveyard field,
 * then spawns the requested number of graveyard entities. */



#include "rebrew_types.h"
#include "rebrew_globals.h"
#define g_entity_table_end (*(unsigned int*) 0x773da8)
#define g_entity_type_table ((char*) *(unsigned int*) 0x868050)
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl fcn_004f1ad0(void* entity, int cmd_arg);

int __cdecl gv_ValidateEntityAction(void* cmd)
{
	void* entity;
	unsigned short grave_id;
	unsigned char field_id;
	int v;

	gm_ResolveEntityById(&entity, 0, 0, *(int*) ((char*) cmd + 8));
	if (entity) {
		grave_id = *(unsigned short*) ((char*) entity + 0x27);
		if (grave_id != 0xffff) {
			if ((char*) 0x7f4ca0 + grave_id * 0x21c != (char*) g_entity_table_end) {
				field_id = *(unsigned char*) entity;
				if (g_entity_type_table[field_id + field_id * 588] != 0x1d) {
					return -2;
				}
				if (*(void**) ((char*) entity + 0x65) == 0) {
					return -3;
				}
				v = fcn_004f1ad0(entity, *(int*) ((char*) cmd + 0x13));
				return v <= 0 ? -4 : 0;
			}
		}
	}
	return -1;
}
