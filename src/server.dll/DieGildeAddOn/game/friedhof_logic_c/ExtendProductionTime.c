/* ExtendProductionTime - proper C */

// FUNCTION: SERVER 0x100113b0
// SYMBOL: _ExtendProductionTime
// SIZE: 390

extern int g_1003546c;
extern char* g_entity_type_table; /* 0x100A8C30 */
/* 189 4-byte entries per object type; only the low word of each entry is read. */
extern unsigned int g_entity_slot_table[];
extern float table_1002572c[];
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl gv_CheckSlotActive(void* slot, int type);
extern void* __cdecl GetSlotEntry(void* worker, int worktype, unsigned char job);
extern int __cdecl fcn_10016ea0(int a, int b, int c);
extern int __cdecl gm_AddOrAccumulateObject(int a, int b, int c);
extern int __cdecl _ftol(void);

/* Extends a production slot's remaining time: resolves the building's
 * entity, verifies the grave slot, then adds the building's production
 * time to the slot and accumulates the produced goods. */

int __cdecl ExtendProductionTime(void* building)
{
	void* entity;
	void* workers;
	void* object;
	void* slot;
	unsigned short grave_id;
	unsigned char field_id;
	unsigned short word1;
	unsigned short word2;
	int obj4;
	int ftol_val;

	gm_ResolveEntityById(&entity, 0, 0, *(int*) ((char*) building + 8));
	if (entity) {
		grave_id = *(unsigned short*) ((char*) entity + 0x27);
		if (grave_id != 0xffff) {
			if ((char*) 0x100358a0 + grave_id * 0x21c != (char*) g_1003546c) {
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
				gm_ResolveEntityById(0, 0, &object, *(int*) ((char*) building + 4));
				if (!object) {
					return -6;
				}
				slot = GetSlotEntry(workers, *(int*) ((char*) building + 0xc),
				    *(unsigned char*) ((char*) building + 0x10));
				if (!slot) {
					return -7;
				}
				*(short*) ((char*) slot + 0xa) += *(short*) ((char*) building + 0x11);
				if (*(int*) ((char*) building + 0x13) > 0) {
					obj4 = *(int*) ((char*) object + 4);
					word1 = (unsigned short) g_entity_slot_table[(unsigned int) *(unsigned char*) 0x10035439 * 189];
					fcn_10016ea0(obj4, word1, *(int*) ((char*) building + 0x13));
					word2 = (unsigned short) g_entity_slot_table[(unsigned int) *(unsigned char*) 0x10035439 * 189];
					ftol_val = (int) (*(int*) ((char*) building + 0x13) * table_1002572c[*(int*) ((char*) building + 0xc)]);
					gm_AddOrAccumulateObject(*(int*) ((char*) 0x100358a4 + *(unsigned short*) ((char*) entity + 0x27) * 0x21c),
					    word2, ftol_val);
				}
				return 0;
			}
		}
	}
	return -1;
}
