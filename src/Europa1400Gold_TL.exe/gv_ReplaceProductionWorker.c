/* gv_ReplaceProductionWorker - proper C */

// FUNCTION: GOLDTL 0x4f2a80
// SIZE: 288


#include "rebrew_types.h"
#include "rebrew_globals.h"
extern unsigned short* g_entity_table_end; /* TL 0x773da8 (server 0x1003546c) */
extern unsigned char* g_entity_type_table; /* TL 0x868050 (server 0x100a8c30) */
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
int __cdecl gv_CheckSlotActive(void* slot, int type);
void* __cdecl gv_GetSlotEntry(void* worker, int worktype, unsigned char job);

int __cdecl gv_ReplaceProductionWorker(void* a)
{
	void* rec;
	void* rec2;
	void* slot;
	unsigned short slot_off;
	unsigned short limit;
	int owner_id;
	int worker;
	int type;

	owner_id = -1;
	limit = 0xffff;
	slot_off = limit;
	gm_ResolveEntityById(&rec, 0, 0, *(int*) ((char*) a + 8));
	if (rec == 0 ||
	    *(unsigned short*) ((char*) rec + 0x27) == limit ||
	    0x7f4ca0 + (unsigned int) (*(unsigned short*) ((char*) rec + 0x27) & limit) * 540 ==
	        g_entity_table_end)
		return -1;
	type = *(unsigned char*) rec;
	if (*(unsigned char*) (g_entity_type_table + type + type * 0x24c) != 0x1d)
		return -2;
	worker = *(int*) ((char*) rec + 0x65);
	if (worker == 0)
		return -3;
	if (!gv_CheckSlotActive((void*) worker, *(int*) ((char*) a + 0xc)))
		return -4;
	if (*(int*) ((char*) a + 4) != -1) {
		gm_ResolveEntityById(0, 0, &rec2, *(int*) ((char*) a + 4));
		if (rec2 == 0)
			return -6;
		owner_id = *(int*) ((char*) a + 4);
		slot_off = *(unsigned short*) ((char*) rec2 + 0x50);
	}
	slot = gv_GetSlotEntry((void*) worker, *(int*) ((char*) a + 0xc),
	                       *(unsigned char*) ((char*) a + 0x10));
	if (slot == 0)
		return -7;
	*(unsigned short*) ((char*) slot + 8) = slot_off;
	*(int*) ((char*) slot + 4) = owner_id;
	return 0;
}
