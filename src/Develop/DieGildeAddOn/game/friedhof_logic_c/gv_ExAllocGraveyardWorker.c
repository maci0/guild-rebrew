#include "../entity.h"

// FUNCTION: GOLDTL 0x4f3310
// SIZE: 992
// FUNCTION: SERVER 0x10011bf0

#include "rebrew_types.h"
#include "rebrew_globals.h"
extern unsigned short* g_entity_table_end; /* 0x1003546c */
extern int g_citizen_count;
extern int g_next_object_id;
extern int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern int __cdecl gv_CheckSlotActive(void* worker, int worktype);
extern void* __cdecl gv_GetSlotEntry(void* worker, int worktype, unsigned char job);
extern int __cdecl gm_RandomMod(int n);
extern float __cdecl gm_RandomFloat01(void);
extern void __cdecl LogMessageInternal(char* module, unsigned int line, char* msg, int severity);
extern void* __cdecl memset(void* dest, int c, unsigned int size);
extern char* __cdecl strcpy(char* dest, const char* src);

int __cdecl gv_ExAllocGraveyardWorker(void* req)
{
	void* entry;
	void* entity;
	void* slot;
	void* workers;
	void* slot_ptr;
	int grave_cursor;
	char* grave;
	int chosen;
	int j;
	int count;
	int job_id;
	unsigned char field_id;
	int one;
	int neg;
	int off;

	if (*(int*) ((char*) req + 0x15) != 0x1b && *(int*) ((char*) req + 0x15) != 0x1c)
		return -6;
	gm_ResolveEntityById(&entity, 0, 0, *(int*) ((char*) req + 8));
	if (!entity ||
	    *(unsigned short*) ((char*) entity + 0x27) == 0xffff ||
	    (char*) 0x100358a0 + *(unsigned short*) ((char*) entity + 0x27) * 0x21c == (char*) g_entity_table_end)
		return -1;
	field_id = *(unsigned char*) entity;
	if (g_entity_type_table[field_id + field_id * 588] != 0x1d)
		return -2;
	workers = *(void**) ((char*) entity + 0x65);
	if (!workers)
		return -3;
	if (!gv_CheckSlotActive(workers, *(int*) ((char*) req + 0xc)))
		return -4;
	slot = gv_GetSlotEntry(workers, *(int*) ((char*) req + 0xc), *(unsigned char*) ((char*) req + 0x10));
	if (!slot)
		return 0xffff;
	slot_ptr = *(void**) ((char*) slot + 0x10);
	j = 0;
	count = g_worker_entry_count[*(int*) ((char*) req + 0xc)];
	if (j >= count)
		goto fail_ffff;
	job_id = *(int*) ((char*) req + 0x11);
	{
		char* q = (char*) slot_ptr;
		for (; j < count; j++, q = q + 0x44) {
			entry = q;
			if (*(int*) q == job_id)
				break;
		}
		slot_ptr = q;
	}
	if (!entry || *(int*) entry != job_id)
		goto fail_ffff;
	chosen = 0;
	grave_cursor = 0x100358a0;
	while (grave_cursor < 0x1009aca0) {
		if (*(unsigned short*) grave_cursor == 0xffff)
			break;
		grave_cursor += 0x21c;
		chosen++;
	}
	if (chosen == 0x300) {
		chosen = 0;
		grave_cursor = 0x100358a2;
		while (grave_cursor < 0x1009aca2) {
			if (*(unsigned char*) grave_cursor == 0xf)
				break;
			grave_cursor += 0x21c;
			chosen++;
		}
		if (chosen == 0x300) {
			LogMessageInternal((char*) 0x1002d48c, 0x6ef, (char*) 0x1002d4bc, 1);
			return 0xffff;
		}
	}
	if (*(unsigned char*) ((char*) 0x100358a2 + chosen * 0x21c) == 0xf)
		g_citizen_count--;
	off = chosen * 0x21c;
	grave = (char*) 0x100358a0 + off;
	memset(grave, 0, 0x21c);
	/* volatile: the slot-index store below writes the same halfword, so
	 * without the qualifier msvc6 drops this write and the object loses the
	 * reference's `mov word ptr [ebp],0xffff` at 0x10011db3. */
	neg = -1;
	{
		char* m2 = grave + 0x5c;
		*(int*) ((char*) 0x100358a4 + off) = neg;
		memset(m2, neg, 32);
		*(volatile unsigned short*) grave = 0xffff;
	}
	/* Both counters are read before the entity stores and written back after,
	 * matching the reference's edi/ecx traffic at 0x10011dd2-0x10011dff.
	 * Bumping them in place emits a load-inc-store round trip each. */
	{
		int live = g_citizen_count + 1;
		int seq;
		*(int*) (grave + 0x170) = (int) entity;
		*(int*) (grave + 0x16c) = (int) entity;
		seq = g_next_object_id;
		*(int*) (grave + 4) = seq;
		g_next_object_id = seq + 1;
		one = 1;
		*(volatile unsigned short*) grave = (unsigned short) chosen;
		g_citizen_count = live;
	}
	*(volatile unsigned char*) (grave + 2) = 0x14;
	*(int*) (grave + 0x1f0) = 0;
	*(int*) (grave + 0x210) = -1;
	*(unsigned char*) (grave + 0x215) = 0;
	*(unsigned char*) (grave + 0x216) = 0;
	*(unsigned char*) (grave + 0x217) = 0;
	*(unsigned char*) (grave + 0x218) = (unsigned char) one;
	*(int*) (grave + 0x1e4) = 0x3f800000; /* 1.0f */
	*(unsigned char*) (grave + 8) = 0x64;
	*(unsigned short*) (grave + 0xa) = 0x10;
	*(unsigned char*) (grave + 0x164) = 0;
	*(unsigned char*) (grave + 0x166) = 0;
	*(unsigned char*) (grave + 0x165) = *(unsigned char*) ((char*) req + 0x15);
	*(unsigned char*) (grave + 0x1f4) = 0;
	*(int*) (grave + 0x190) = 4;
	*(int*) (grave + 0x194) = 0;
	*(unsigned char*) (grave + 0xd) = (unsigned char) one;
	*(int*) (grave + 0x18c) = -1;
	*(int*) (grave + 0x20c) = -1;
	*(unsigned short*) (grave + 0x50) = 0x7fff;
	{
		int n;
		for (n = 0; n < 5; n++)
			*(unsigned char*) (grave + 0x80 + n) = *(unsigned char*) ((char*) entry + 0x24 + n) >> 1;
	}
	*(unsigned char*) (grave + 9) = *(unsigned char*) ((char*) entry + 0x38);
	*(volatile int*) (grave + 0x10) = 0;
	strcpy((char*) grave + 0x30, (char*) entry + 4);
	strcpy((char*) grave + 0x40, (char*) *(void* volatile*) &entry + 0x14);
	{
		int n;
		volatile int iv;
		iv = 0;
		*(float*) (grave + 0x14) =
		    *(float*) 0x10025680 / (gm_RandomFloat01() * *(float*) 0x100257c8 + *(float*) 0x100257c4);
		*(int*) (grave + 0x18) = 0;
		*(int*) (grave + 0x1c) = 0x447a0000; /* 1000.0f */
		*(int*) (grave + 0x20) = 0;
		*(int*) (grave + 0x24) = 0;
		*(unsigned short*) (grave + 0x28) = 0;
		*(int*) (grave + 0x2c) = 0;
		for (n = 0; n < 0x90000; n += 0x300) {
			int a = n + *(volatile unsigned short*) grave;
			int byte_offset;
			int random_value;
			int col;
			random_value = gm_RandomMod(0x40);
			g_relationship_matrix_secondary[a] = 0;
			g_relationship_matrix_primary[a] = (unsigned char) random_value - 0x20;
			col = iv;
			byte_offset = *(volatile unsigned short*) grave * 0x300 + col;
			/* The counter bump sits between the call and its stores to
			 * match the reference's `add esi,0x300` / `inc edx` at
			 * 0x10011f68, ahead of the store pair at 0x10011f75. */
			random_value = gm_RandomMod(0x40);
			iv = iv + 1;
			g_relationship_matrix_primary[byte_offset] = (unsigned char) random_value - 0x20;
			g_relationship_matrix_secondary[byte_offset] = 0;
		}
	}
	if (*(int*) entry == *(int*) ((char*) slot + 4)) {
		int n;
		count = g_worker_entry_count[*(int*) ((char*) req + 0xc)];
		if (count > 0) {
			slot_ptr = *(void**) ((char*) slot + 0x10);
			for (n = 0; n < count; n++, slot_ptr = (char*) slot_ptr + 0x44) {
				if (*(int*) slot_ptr == -1)
					continue;
				if (*(int*) slot_ptr != *(int*) entry) {
					*(int*) ((char*) slot + 4) = *(int*) slot_ptr;
					goto clear_entry;
				}
			}
		}
		*(int*) ((char*) slot + 4) = -1;
		*(unsigned short*) ((char*) slot + 8) = 0xffff;
	}
clear_entry:
	memset(entry, 0, 0x44);
	*(int*) entry = -1;
	return (short) *(volatile unsigned short*) grave;
	/* With this label inside the log block, msvc6 routes the three
	 * entry-search exits to the `!slot` epilogue at 0x10011cdb; placed here
	 * they reach the log path's epilogue at 0x10011d77, as in the reference. */
fail_ffff:
	return 0xffff;
}
