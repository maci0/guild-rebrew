/* gv_UpdateProductionProgress - advances a production slot's progress by the
 * building's production time, clamped to [0, 0xff]. */

// FUNCTION: GOLDTL 0x4f2d90
// SIZE: 240

#include "rebrew_types.h"
#include "rebrew_globals.h"
extern unsigned short* g_entity_table_end; /* 0x1003546c */
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl gv_CheckSlotActive(void* slot, int type);
extern void* __cdecl gv_GetSlotEntry(void* worker, int worktype, unsigned char job);

int __cdecl gv_UpdateProductionProgress(void* building)
{
	void* entity;
	unsigned short grave_id;
	unsigned char field_id;
	void* workers;
	void* slot;
	int sum;
	int neg;

	gm_ResolveEntityById(&entity, 0, 0, *(int*) ((char*) building + 8));
	if (entity) {
		grave_id = *(unsigned short*) ((char*) entity + 0x27);
		if (grave_id != 0xffff) {
			if ((char*) 0x100358a0 + grave_id * 0x21c != (char*) g_entity_table_end) {
				field_id = *(unsigned char*) entity;
				if (g_entity_type_table[field_id + field_id * 588] != 0x1d) {
					return -2;
				}
				workers = *(void**) ((char*) entity + 0x65);
				if (!workers) {
					return -3;
				}
				if (!gv_CheckSlotActive(workers, *(int*) ((char*) building + 0xc))) {
					return -4;
				}
				slot = gv_GetSlotEntry(workers, *(int*) ((char*) building + 0xc), *(unsigned char*) ((char*) building + 0x10));
				if (!slot) {
					return -7;
				}
				sum = *(unsigned char*) ((char*) slot + 0xc);
				sum = *(int*) ((char*) building + 0x13) + sum;
				/* Spelling the negative clamp as an explicit setle/dec/and
				 * mask, rather than a ternary, is what emits the target's
				 * byte-load-then-copy pair ahead of the add. */
				neg = (sum <= 0) ? 1 : 0;
				sum &= neg - 1;
				if (sum >= 0xff) {
					sum = 0xff;
				}
				*(unsigned char*) ((char*) slot + 0xc) = (unsigned char) sum;
				return 0;
			}
		}
	}
	return -1;
}
