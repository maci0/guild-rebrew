// GLOBAL: SERVER 0x1002575c
extern int g_field_worker_count[];

// GLOBAL: SERVER 0x1002576c
extern int g_field_entry_count[];
// FUNCTION: GOLDTL 0x4f1d20
// SIZE: 832
// FUNCTION: SERVER 0x100109d0
// SIZE: 832

#include "rebrew_types.h"
#include "rebrew_globals.h"
extern void* __cdecl m_AllocTracked(unsigned int size, const char* tag);
extern void __cdecl m_FreeTracked(void* ptr);
extern void* __cdecl memset(void* dest, int c, unsigned int count);

/* Allocates a graveyard field slot: verifies the field type, allocates
 * the slot plus its worker table and slot-entry table, initializes the
 * production slots for the field type, and links the slot to the field. */

int __cdecl gv_AllocGraveyardField(unsigned char* field)
{
	unsigned char* entry;
	void* slot;
	char* entity_cursor;
	char* record_cursor;
	int i;

	entry = (unsigned char*) (g_entity_type_table + field[0] + field[0] * 588);
	if (entry[0] != 0x1d) {
		return 0;
	}
	if (entry[0x247] < 1 || entry[0x247] > 3) {
		return 0;
	}
	slot = m_AllocTracked(0x24, (const char*) 0x1002d474);
	if (!slot) {
		return 0;
	}
	memset(slot, 0, 0x24);
	*(int*) slot = *(int*) (field + 1);
	*(int*) ((char*) slot + 4) = entry[0x247];
	*(void**) ((char*) slot + 0x1c) = (char*) m_AllocTracked(g_field_worker_count[entry[0x247]] * 20,
	    (const char*) 0x1002d45c);
	if (!*(void**) ((char*) slot + 0x1c)) {
		goto cleanup;
	}
	memset(*(void**) ((char*) slot + 0x1c), 0, g_field_worker_count[entry[0x247]] * 20);
	*(void**) ((char*) slot + 0x20) = (char*) m_AllocTracked(g_field_entry_count[entry[0x247]] * 68,
	    (const char*) 0x1002d444);
	if (*(void**) ((char*) slot + 0x20) == 0) {
cleanup:
		if (*(void**) ((char*) slot + 0x1c)) {
			m_FreeTracked(*(void**) ((char*) slot + 0x1c));
			*(void**) ((char*) slot + 0x1c) = 0;
		}
		if (*(void**) ((char*) slot + 0x20)) {
			m_FreeTracked(*(void**) ((char*) slot + 0x20));
			*(void**) ((char*) slot + 0x20) = 0;
		}
		m_FreeTracked(slot);
		return 0;
	}
	memset(*(void**) ((char*) slot + 0x20), 0, g_field_entry_count[entry[0x247]] * 68);
	for (i = 0; i < g_field_entry_count[entry[0x247]]; i++)
		*(unsigned*) ((char*) *(void**) ((char*) slot + 0x20) + i * 0x44) = 0xFFFFFFFFu;
	*(void**) ((char*) slot + 8) = *(void**) ((char*) slot + 0x1c);
	*(char*) ((char*) slot + 0x18) = 1;
	*(char*) ((char*) slot + 0x19) = 0;
	*(char*) ((char*) slot + 0x1a) = 0;
	*(char*) ((char*) slot + 0x1b) = 0;
	entity_cursor = (char*) *(void**) ((char*) slot + 0x1c);
	record_cursor = (char*) *(void**) ((char*) slot + 0x20);
	if (*(int*) ((char*) slot + 4) == 1) {
		*(void**) ((char*) slot + 0x10) = 0;
		*(void**) ((char*) slot + 0xc) = entity_cursor + 0xa0;
		*(void**) ((char*) slot + 0x14) = 0;
		for (i = 0; i < 8; i++) {
			*(int*) entity_cursor = 0;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x44;
			entity_cursor += 0x14;
		}
		for (i = 0; i < 4; i++) {
			*(int*) entity_cursor = 1;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x88;
			entity_cursor += 0x14;
		}
	} else if (*(int*) ((char*) slot + 4) == 2) {
		*(void**) ((char*) slot + 0x14) = 0;
		*(void**) ((char*) slot + 0xc) = entity_cursor + 0xf0;
		*(void**) ((char*) slot + 0x10) = entity_cursor + 0x168;
		for (i = 0; i < 0xc; i++) {
			*(int*) entity_cursor = 0;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x44;
			entity_cursor += 0x14;
		}
		for (i = 0; i < 6; i++) {
			*(int*) entity_cursor = 1;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x88;
			entity_cursor += 0x14;
		}
		for (i = 0; i < 2; i++) {
			*(int*) entity_cursor = 2;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x110;
			entity_cursor += 0x14;
		}
	} else {
		*(void**) ((char*) slot + 0xc) = entity_cursor + 0x140;
		*(void**) ((char*) slot + 0x10) = entity_cursor + 0x1e0;
		*(void**) ((char*) slot + 0x14) = entity_cursor + 0x230;
		for (i = 0; i < 0x10; i++) {
			*(int*) entity_cursor = 0;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x44;
			entity_cursor += 0x14;
		}
		for (i = 0; i < 8; i++) {
			*(int*) entity_cursor = 1;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x88;
			entity_cursor += 0x14;
		}
		for (i = 0; i < 4; i++) {
			*(int*) entity_cursor = 2;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x110;
			entity_cursor += 0x14;
		}
		for (i = 0; i < 2; i++) {
			*(int*) entity_cursor = 3;
			*(void**) (entity_cursor + 0x10) = record_cursor;
			*(unsigned*) (entity_cursor + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (entity_cursor + 8) = 0xFFFFu;
			record_cursor += 0x220;
			entity_cursor += 0x14;
		}
	}
	*(void**) (field + 0x65) = slot;
	return (int) slot;
}
