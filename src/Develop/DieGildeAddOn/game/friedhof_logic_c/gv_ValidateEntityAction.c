/* gv_ValidateEntityAction - validates a standard entity action command:
 * resolves the target entity, checks it is an active graveyard field,
 * then spawns the requested number of graveyard entities. */

// FUNCTION: SERVER 0x10011890

#include "rebrew_types.h"
#include "rebrew_globals.h"
extern unsigned short* g_entity_table_end; /* 0x1003546c */
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl gv_SpawnEntities(void* building, int count);

int __cdecl gv_ValidateEntityAction(void* cmd)
{
	void* entity;
	unsigned short grave_id;
	unsigned char field_id;

	gm_ResolveEntityById(&entity, 0, 0, *(int*) ((char*) cmd + 8));
	if (entity) {
		grave_id = *(unsigned short*) ((char*) entity + 0x27);
		if (grave_id != 0xffff) {
			if ((char*) 0x100358a0 + grave_id * 0x21c != (char*) g_entity_table_end) {
				field_id = *(unsigned char*) entity;
				if (g_entity_type_table[field_id + field_id * 588] != 0x1d) {
					return -2;
				}
				if (*(void**) ((char*) entity + 0x65) == 0) {
					return -3;
				}
				return gv_SpawnEntities(entity, *(int*) ((char*) cmd + 0x13)) > 0 ? 0 : -4;
			}
		}
	}
	return -1;
}
