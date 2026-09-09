/* ReplaceProductionWorker - proper C */

// FUNCTION: SERVER 0x10011540
// SIZE: 288

extern char* g_entity_type_table;
extern int g_1003546c;
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
int __cdecl gv_CheckSlotActive(void* slot, int type);
void* __cdecl GetSlotEntry(void* worker, int worktype, unsigned char job);

int __cdecl ReplaceProductionWorker(void* a)
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
	    0x100358a0 + (unsigned int) (*(unsigned short*) ((char*) rec + 0x27) & limit) * 540 ==
	        g_1003546c)
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
	slot = GetSlotEntry((void*) worker, *(int*) ((char*) a + 0xc),
	                       *(unsigned char*) ((char*) a + 0x10));
	if (slot == 0)
		return -7;
	*(unsigned short*) ((char*) slot + 8) = slot_off;
	*(int*) ((char*) slot + 4) = owner_id;
	return 0;
}
