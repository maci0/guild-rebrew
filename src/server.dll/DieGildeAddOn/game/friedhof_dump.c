/* friedhof_logic TU - proper C (aggregate of the per-function files). */

// CFLAGS: /O2 /Gd

int g_save_version;
// FUNCTION: SERVER 0x10010530
// SYMBOL: _gv_CheckSlotActive
// SIZE: 113

int __cdecl gv_CheckSlotActive(void* slot, int type)
{
	if (type == 0) {
		if (*(int*) ((char*) slot + 8) != 0 && *(unsigned char*) ((char*) slot + 0x18) != 0)
			return 1;
		return 0;
	}
	if (type == 1) {
		if (*(int*) ((char*) slot + 0xc) != 0 && *(unsigned char*) ((char*) slot + 0x19) != 0)
			return 1;
		return 0;
	}
	if (type == 2) {
		if (*(int*) ((char*) slot + 0x10) != 0 && *(unsigned char*) ((char*) slot + 0x1a) != 0)
			return 1;
		return 0;
	}
	if (type == 3) {
		if (*(int*) ((char*) slot + 0x14) != 0 && *(unsigned char*) ((char*) slot + 0x1b) != 0)
			return 1;
		return 0;
	}
	return 1;
}

// FUNCTION: SERVER 0x10010d10
// SYMBOL: _UpgradeGraveyardField
// SIZE: 570

extern char* dword_100a8c30;
extern void __cdecl m_FreeTracked(void* ptr);
int __cdecl AllocGraveyardField(unsigned char* field);
void __cdecl AssignProductionSlot(void* slot);

/* Upgrades a graveyard field to the next maturity level: allocates a new
 * field slot via AllocGraveyardField, copies the worker data across, then
 * frees the old allocation.  Returns the new field data pointer. */

int __cdecl UpgradeGraveyardField(unsigned char* field)
{
	unsigned char* entry;
	void* old_alloc;
	void* new_alloc;
	int maturity;
	int level;
	int count8;
	int count10;
	int i;

	entry = (unsigned char*) (dword_100a8c30 + field[0] + field[0] * 588);
	if (entry[0] != 0x1d)
		return 0;
	old_alloc = *(void**) (field + 0x65);
	if (old_alloc == 0)
		return 0;
	level = *(int*) ((char*) old_alloc + 4);
	if (level >= 3)
		return 0;
	maturity = entry[0x247];
	if (maturity - level != 1)
		return 0;
	*(void**) (field + 0x65) = 0;
	new_alloc = AllocGraveyardField(field);
	if (new_alloc == 0) {
		*(void**) (field + 0x65) = old_alloc;
		return 0;
	}
	if (maturity == 2) {
		memcpy(*(void**) (*(char**) ((char*) new_alloc + 8) + 0x10),
		       *(void**) (*(char**) ((char*) old_alloc + 8) + 0x10), 0x88 * 4);
		memcpy(*(void**) (*(char**) ((char*) new_alloc + 0xc) + 0x10),
		       *(void**) (*(char**) ((char*) old_alloc + 0xc) + 0x10), 0x88 * 4);
		count8 = 8;
		count10 = 0;
	} else {
		memcpy(*(void**) (*(char**) ((char*) new_alloc + 8) + 0x10),
		       *(void**) (*(char**) ((char*) old_alloc + 8) + 0x10), 0xcc * 4);
		memcpy(*(void**) (*(char**) ((char*) new_alloc + 0xc) + 0x10),
		       *(void**) (*(char**) ((char*) old_alloc + 0xc) + 0x10), 0xcc * 4);
		memcpy(*(void**) (*(char**) ((char*) new_alloc + 0x10) + 0x10),
		       *(void**) (*(char**) ((char*) old_alloc + 0x10) + 0x10), 0x88 * 4);
		count8 = 0xc;
		count10 = 2;
	}
	if (((char**) old_alloc)[2] != 0 && count8 > 0) {
		for (i = 0; i < count8; i++) {
			*(int*) ((char*) ((char**) new_alloc)[2] + i * 0x14) =
			    *(int*) ((char*) ((char**) old_alloc)[2] + i * 0x14);
			*(int*) ((char*) ((char**) new_alloc)[2] + i * 0x14 + 4) =
			    *(int*) ((char*) ((char**) old_alloc)[2] + i * 0x14 + 4);
			*(unsigned short*) ((char*) ((char**) new_alloc)[2] + i * 0x14 + 8) =
			    *(unsigned short*) ((char*) ((char**) old_alloc)[2] + i * 0x14 + 8);
			*(unsigned short*) ((char*) ((char**) new_alloc)[2] + i * 0x14 + 0xa) =
			    *(unsigned short*) ((char*) ((char**) old_alloc)[2] + i * 0x14 + 0xa);
			*(unsigned char*) ((char*) ((char**) new_alloc)[2] + i * 0x14 + 0xc) =
			    *(unsigned char*) ((char**) ((char**) old_alloc)[2] + i * 0x14 + 0xc);
		}
	}
	if (((char**) old_alloc)[3] != 0 && count10 > 0) {
		for (i = 0; i < count10; i++) {
			*(int*) ((char*) ((char**) new_alloc)[3] + i * 0x14) =
			    *(int*) ((char*) ((char**) old_alloc)[3] + i * 0x14);
			*(int*) ((char*) ((char**) new_alloc)[3] + i * 0x14 + 4) =
			    *(int*) ((char*) ((char**) old_alloc)[3] + i * 0x14 + 4);
			*(unsigned short*) ((char*) ((char**) new_alloc)[3] + i * 0x14 + 8) =
			    *(unsigned short*) ((char*) ((char**) old_alloc)[3] + i * 0x14 + 8);
			*(unsigned short*) ((char*) ((char**) new_alloc)[3] + i * 0x14 + 0xa) =
			    *(unsigned short*) ((char*) ((char**) old_alloc)[3] + i * 0x14 + 0xa);
			*(unsigned char*) ((char*) ((char**) new_alloc)[3] + i * 0x14 + 0xc) =
			    *(unsigned char*) ((char*) ((char**) old_alloc)[3] + i * 0x14 + 0xc);
		}
	}
	((char*) new_alloc)[0x18] = ((char*) old_alloc)[0x18];
	((char*) new_alloc)[0x19] = ((char*) old_alloc)[0x19];
	((char*) new_alloc)[0x1a] = ((char*) old_alloc)[0x1a];
	((char*) new_alloc)[0x1b] = ((char*) old_alloc)[0x1b];
	AssignProductionSlot(old_alloc);
	return *(int*) (field + 0x65);
}


// FUNCTION: SERVER 0x10011940
// SYMBOL: _gv_MoveSlotEntry
// SIZE: 674

extern char* dword_100a8c30;
extern int g_1003546c;
extern int g_next_object_id;
extern int g_1002574c[];
extern float table_1002572c[];
extern unsigned int table_100a8c94[];
extern unsigned char g_current_season;
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
int __cdecl gv_CheckSlotActive(void* slot, int type);
void* __cdecl gv_GetSlotEntry(void* worker, int worktype, unsigned char job);
void* __cdecl FindSlotEntryFiltered(void* filter_arg, void* entity, void* cursor,
                                    void* filter, int type);
int __cdecl fcn_10016ea0(int a, int b, int c);
int __cdecl gm_AddOrAccumulateObject(int a, int b, int c);
int __cdecl _ftol(void);

/* Moves a graveyard worker's slot entry to the field it currently works
 * in: finds the source entry and a free destination slot, copies the
 * entry across, clears the source, and accumulates the produced goods
 * for the current season. */

int __cdecl gv_MoveSlotEntry(void* a, void* arg2)
{
	void* rec;
	void* rec2;
	void* slot;
	void* found;
	int* src_entry;
	int* dst_entry;
	int* dst_end;
	int count;
	int i;

	gm_ResolveEntityById(&rec, 0, 0, *(int*) a);
	if (rec == 0)
		return -6;
	gm_ResolveEntityById(0, 0, &rec2, *(int*) ((char*) a + 4));
	if (rec2 == 0)
		return -1;
	if (*(unsigned short*) ((char*) rec2 + 0x27) == 0xffff)
		return -1;
	i = *(unsigned short*) ((char*) rec2 + 0x27) & 0xffff;
	if (0x100358a0 + i * 540 == g_1003546c)
		return -1;
	if (*(unsigned char*) (dword_100a8c30 + *(unsigned char*) rec2 +
	    *(unsigned char*) rec2 * 588) != 0x1d)
		return -2;
	slot = *(void**) ((char*) rec2 + 0x65);
	if (slot == 0)
		return -3;
	if (!gv_CheckSlotActive(slot, *(int*) ((char*) a + 8)))
		return -4;
	found = gv_GetSlotEntry(slot, *(int*) ((char*) a + 8),
	                        *(unsigned char*) ((char*) a + 0xc));
	if (found == 0)
		return -7;
	if (*(unsigned short*) ((char*) found + 8) != *(unsigned short*) ((char*) a + 0x50))
		return -7;

	src_entry = *(int**) ((char*) found + 0x10);
	dst_end = src_entry + g_1002574c[*(unsigned char*) ((char*) a + 0xd)] * 17;
	dst_entry = *(int**) ((char*) slot + 0x10) + g_1002574c[*(int*) ((char*) a + 8)] * 17;

	found = FindSlotEntryFiltered(a, rec2, 0, (void*) 0x10010700,
	                              *(unsigned char*) ((char*) a + 0xd));
	if (found == 0)
		return -7;

	for (;;) {
		if (*dst_entry == -1)
			break;
		if (dst_entry >= src_entry)
			break;
		if (*dst_entry != -1) {
			memcpy(dst_entry, src_entry, 0x44);
			memset(src_entry, 0, 0x44);
			*src_entry = -1;
			break;
		}
		dst_entry += 0x11;
		if (dst_entry >= src_entry)
			break;
	}

	*(int*) ((char*) found + 4) = -1;
	*(unsigned short*) ((char*) found + 8) = 0xffff;
	*(unsigned short*) ((char*) found + 0xa) = 0xff;
	*(int*) ((char*) a + 0x15) = g_next_object_id;

	count = *(int*) ((char*) a + 0x11);
	if (count > 0) {
		fcn_10016ea0(*(int*) ((char*) arg2 + 4),
		             table_100a8c94[g_current_season * 189], 0);
		i = _ftol((float) count * table_1002572c[*(unsigned char*) ((char*) a + 0xd)]);
		gm_AddOrAccumulateObject(0x100358a4 + i * 540,
		                         table_100a8c94[g_current_season * 189], i);
	}
	return 0;
}

