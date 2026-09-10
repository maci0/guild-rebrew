/* HireProductionWorker - hires a production worker: validates the building's
 * entity and workers, finds a free slot entry via FindSlotEntryFiltered,
 * initializes the slot from the requested entity, clears the slot's entry
 * list, and books the production amount when positive. */

// FUNCTION: SERVER 0x100111b0

extern unsigned short* g_entity_table_end; /* 0x1003546c */
extern char* g_entity_type_table; /* 0x100A8C30 */
extern int g_worker_entry_count[];
extern float table_1002572c[];
/* 189 4-byte entries per object type; only the low word of each entry is read. */
extern unsigned int g_entity_slot_table[];
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl gv_CheckSlotActive(void* slot, int type);
extern void* __cdecl FindSlotEntryFiltered(void* a, void* b, int c, int d, int e);
extern int __cdecl fcn_10016ea0(int a, int b, int c);
extern int __cdecl gm_AddOrAccumulateObject(int a, int b, int c);
extern int __cdecl _ftol(void);

int __cdecl HireProductionWorker(void* req)
{
	void* entity1;
	void* entity2;
	void* workers;
	void* slot;
	unsigned short grave_id;
	unsigned char field_id;
	unsigned short word1;
	unsigned short word2;
	int ftol_val;
	int j;

	gm_ResolveEntityById(&entity1, 0, 0, *(int*) ((char*) req + 8));
	if (!entity1 ||
	    *(unsigned short*) ((char*) entity1 + 0x27) == 0xffff ||
	    (char*) 0x100358a0 + *(unsigned short*) ((char*) entity1 + 0x27) * 0x21c == (char*) g_entity_table_end)
		return -1;
	field_id = *(unsigned char*) entity1;
	if (g_entity_type_table[field_id + field_id * 588] != 0x1d) {
		return -2;
	}
	workers = *(void**) ((char*) entity1 + 0x65);
	if (!workers) {
		return -3;
	}
	if (!gv_CheckSlotActive(workers, *(int*) ((char*) req + 0xc))) {
		return -4;
	}
	gm_ResolveEntityById(0, 0, &entity2, *(int*) ((char*) req + 4));
	if (!entity2) {
		return -6;
	}
	if (*(int*) ((char*) req + 0xc) < 0 || *(int*) ((char*) req + 0xc) > 3) {
		return -5;
	}
	slot = FindSlotEntryFiltered(entity2, entity1, 0, 0x10010700, *(int*) ((char*) req + 0xc));
	if (!slot) {
		return -7;
	}
	*(int*) ((char*) slot + 4) = *(int*) ((char*) entity2 + 4);
	*(unsigned short*) ((char*) slot + 8) = *(unsigned short*) ((char*) entity2 + 0x50);
	*(unsigned short*) ((char*) slot + 0xa) =
	    *(unsigned short*) ((char*) req + 0x11) + *(unsigned short*) ((char*) 0x10035880);
	*(unsigned char*) ((char*) slot + 0xc) = 0xff;
	for (j = 0; j < g_worker_entry_count[*(int*) ((char*) req + 0xc)]; j++) {
		*(int*) ((char*) *(void**) ((char*) slot + 0x10) + j * 0x44) = -1;
	}
	if (*(int*) ((char*) req + 0x13) > 0) {
		word1 = (unsigned short) g_entity_slot_table[(unsigned int) *(unsigned char*) 0x10035439 * 189];
		fcn_10016ea0(*(int*) ((char*) entity2 + 4), word1, *(int*) ((char*) req + 0x13));
		word2 = (unsigned short) g_entity_slot_table[(unsigned int) *(unsigned char*) 0x10035439 * 189];
		ftol_val = (int) (*(int*) ((char*) req + 0x13) * table_1002572c[*(int*) ((char*) req + 0xc)]);
		gm_AddOrAccumulateObject(*(int*) ((char*) 0x100358a4 + *(unsigned short*) ((char*) entity1 + 0x27) * 0x21c),
		    word2, ftol_val);
	}
	return 0;
}
