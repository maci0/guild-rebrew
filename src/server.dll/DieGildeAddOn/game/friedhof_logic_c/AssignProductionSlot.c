/* AssignProductionSlot - fills a production slot entry from the owner entity. */

// FUNCTION: SERVER 0x10010fa0
// SIZE: 525

#include "rebrew_types.h"
#include "rebrew_globals.h"
extern unsigned short* g_entity_table_end; /* 0x1003546c */
extern int g_worker_entry_count[];
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl gv_CheckSlotActive(void* slot, int type);
extern void* __cdecl GetSlotEntry(void* worker, int worktype, unsigned char job);

#pragma intrinsic(strcpy)

/* 4-byte value plus its trailing flag byte, copied as one 5-byte unit. */
#pragma pack(push, 1)
// SIZE 0x5
struct slot_tail {
	int value;
	char flag;
};
#pragma pack(pop)

int __cdecl AssignProductionSlot(void* req)
{
	void* building;
	void* owner;
	void* workers;
	void* slot;
	int* entries;
	int* selected;
	int* walk;
	int count;
	int i;

	gm_ResolveEntityById(&building, 0, 0, *(int*) ((char*) req + 8));
	if (!building ||
	    *(unsigned short*) ((char*) building + 0x27) == 0xffff ||
	    (char*) 0x100358a0 + *(unsigned short*) ((char*) building + 0x27) * 0x21c ==
	        (char*) g_entity_table_end)
		return -1;
	if (g_entity_type_table[*(unsigned char*) building +
	                   *(unsigned char*) building * 588] != 0x1d)
		return -2;
	workers = *(void**) ((char*) building + 0x65);
	if (!workers)
		return -3;
	if (!gv_CheckSlotActive(workers, *(int*) ((char*) req + 0xc)))
		return -4;
	gm_ResolveEntityById(0, 0, &owner, *(int*) ((char*) req + 4));
	if (!owner)
		return -6;
	slot = GetSlotEntry(workers, *(int*) ((char*) req + 0xc),
	                    *(unsigned char*) ((char*) req + 0x10));
	if (!slot ||
	    *(unsigned short*) ((char*) slot + 8) !=
	        *(unsigned short*) ((char*) owner + 0x50))
		return -7;

	i = 0;
	entries = *(int**) ((char*) slot + 0x10);
	selected = entries;
	count = g_worker_entry_count[*(int*) ((char*) req + 0xc)];
	for (; i < count; i++) {
		walk = (int*) ((char*) entries + i * 0x44);
		if (*selected == -1)
			break;
		if (*walk == -1) {
			selected = &entries[i * 17];
			break;
		}
		if (*(int*) ((char*) selected + 0x40) >
		    *(int*) ((char*) walk + 0x40))
			selected = walk;
	}

	*selected = *(int*) ((char*) owner + 4);
	strcpy((char*) selected + 4, (char*) owner + 0x30);
	strcpy((char*) selected + 0x14, (char*) owner + 0x40);
	*(struct slot_tail*) ((char*) selected + 0x24) =
	    *(struct slot_tail*) ((char*) owner + 0x80);
	*(int*) ((char*) selected + 0x2c) =
	    (unsigned char) *((char*) owner + 0x167);
	*(int*) ((char*) selected + 0x30) =
	    (unsigned char) *((char*) owner + 0xd);
	*(int*) ((char*) selected + 0x34) =
	    (unsigned char) *((char*) owner + 0x164);
	*(int*) ((char*) selected + 0x38) =
	    (unsigned char) *((char*) owner + 9);
	*(int*) ((char*) selected + 0x40) = g_current_year;
	*(int*) ((char*) selected + 0x3c) = *(int*) ((char*) owner + 0x18c);
	return 0;
}
