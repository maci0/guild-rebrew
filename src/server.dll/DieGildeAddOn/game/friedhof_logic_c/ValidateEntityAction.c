/* ValidateEntityAction - validates a standard entity action command:
 * resolves the target entity, checks it is an active graveyard field,
 * then spawns the requested number of graveyard entities. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10011890
// SYMBOL: _ValidateEntityAction

extern char* dword_100a8c30;
extern int g_1003546c;
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl SpawnGraveyardEntities(void* building, int count);

int __cdecl ValidateEntityAction(void* cmd)
{
	void* entity;
	unsigned short grave_id;
	unsigned char field_id;

	gm_ResolveEntityById(&entity, 0, 0, *(int*) ((char*) cmd + 8));
	if (entity) {
		grave_id = *(unsigned short*) ((char*) entity + 0x27);
		if (grave_id != 0xffff) {
			if ((char*) 0x100358a0 + grave_id * 0x21c != (char*) g_1003546c) {
				field_id = *(unsigned char*) entity;
				if (dword_100a8c30[field_id + field_id * 588] != 0x1d) {
					return -2;
				}
				if (*(void**) ((char*) entity + 0x65) == 0) {
					return -3;
				}
				return (SpawnGraveyardEntities(entity, *(int*) ((char*) cmd + 0x13)) > 0 ? 4 : 0) + (-4);
			}
		}
	}
	return -1;
}
