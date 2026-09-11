#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
typedef int(__cdecl* ALLOCFN)(int, int, int);

#pragma intrinsic(memcpy, memset)

// SIZE 0x2c
#pragma pack(push, 1)
// SIZE 0x43
typedef struct {
	short active;
	int id;
	char pad[0x3d];
} Record;
#pragma pack(pop)

void __cdecl gm_InitObjektHersteller(void);
void __cdecl gm_InitEntitySlots(void);
extern int g_100a8cf8;
extern int g_1009b764;
/* fcn.1001a140 — the original binary calls this thunk (srand(timeGetTime()))
 * between the producible-count loop and the exit log; the reversed CRT
 * provided it as `getpid` before run_000.c was dropped (c77489a). */
extern void __cdecl srv_SeedRandomWithTime(void);


// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10015950
// gm_Open

/* RELOC, 861/861.  The category byte load must be split
 * across `def_row`/`cat_p` and dereferenced through `volatile char*` so
 * msvc6 materializes the address (`mov ecx,eax; add ecx,ebx; mov cl,[ecx]`)
 * instead of folding it into `[eax+ebx]`.  Both halves are required:
 * folding it back into one expression, even with the volatile cast, is
 * 5 bytes short and scores 750.
 *
 * The prologue player-copy loop now matches byte for byte.  Two separate
 * locals are required, and each one decides a different thing:
 *   - `copy_dst` (= dst + 3) is the memcpy destination.  It must have a
 *     second use in the loop body, or msvc6 folds the lea into the call
 *     argument instead of emitting it.  Reading the first store through it
 *     (`copy_dst[-4]`) as well as the third (`copy_dst[-1]`) is what pulls
 *     the lea above the stores, matching the reference (846 -> 849).
 *   - `base` (= dst + 2) carries the two middle stores as `base[-2]` and
 *     `base[-1]`.  That is what sets the store base register 8 bytes higher
 *     so the displacements land on [-4]/[0]/[+4]/[+8] as the reference has
 *     them (849 -> 858).
 * Both are needed: with `copy_dst` alone the schedule is right but every
 * displacement is 8 low, and with `base` alone the lea trails the stores.
 * Dead ends measured on the way: routing all four stores through `copy_dst`
 * (843), only the first store through it (846), `copy_dst` assigned after
 * the first store (SIZE_MISMATCH, 211), a `char*` typed `copy_dst` with byte
 * displacements (SIZE_MISMATCH, 786), and biasing `dst_player_ptr` itself by
 * +2 (849, same as no bias) or +1/-1/-2 (worse).
 *
 * The producible-count loop's SIB base/index roles (`[esi+eax+0x21]`, counter
 * as base and table as index) come from the induction variable's form, not
 * from the addend order.  Counting rows in `row_index` and spelling every
 * address as `g_entity_type_table + row_index * 0x24d + disp` makes msvc6
 * strength-reduce the multiply into the loop-carried register and give it the
 * base role; accumulating a byte offset (`table_offset += 0x24d`) gives the
 * reloaded table pointer the base role instead, whatever the addend order.
 * The final read-modify-write is spelled out twice rather than routed through
 * a pointer local.  A pointer local forces a `lea` into a register plus
 * `[reg]` accesses and lands 2 bytes short (859); the double spelling keeps
 * the load and store as direct `[counter + table + disp]` operands.
 * Dead ends on this loop: addend-order swaps and array-subscript spellings
 * (no change, 858), `(char*) table_offset` casts and a pointer-local rmw on
 * the offset-accumulating shape (785, SIZE_MISMATCH), caching the table
 * pointer in a local (671), an `unsigned char` count (697), seeding the count
 * from the byte instead of zero (711), and keeping `row_index * 0x24d` in
 * `table_offset` rather than inlining it at each use (798). */

int __cdecl gm_Open(int map_id)
{
	unsigned int* src_player_ptr;
	unsigned int* dst_player_ptr;
	unsigned int player_field;
	FILE* file_handle;
	unsigned short slot_entry;
	char item_category;
	int producible_count;
	unsigned short* slot_ptr;
	int slot_counter;
	int slot_idx;
	unsigned char path_buf[512];
	int row_index;
	char* def_row;
	char* cat_p;

	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4d3, "gm_Open(): enter", 1);
	/* 0x10031204 is "gm_Open(): St\344dte" (Latin-1 a-umlaut, byte 0xe4).  The
	   text sits in a relocation slot, so a wrong string still scores RELOC;
	   see docs/msvc6-c-shapes.md section 36. */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4d6, "gm_Open(): St\344dte", 1);
	src_player_ptr = (unsigned int*) &g_100a8cf8;
	dst_player_ptr = (unsigned int*) &g_1009b764;
	do {
		unsigned int* copy_dst;
		unsigned int* base;
		base = dst_player_ptr + 2;
		copy_dst = dst_player_ptr + 3;
		copy_dst[-4] = src_player_ptr[-0x14];
		player_field = *src_player_ptr;
		base[-2] = 1000;
		base[-1] = player_field;
		copy_dst[-1] = 1000;
		memcpy((void*) copy_dst, (void*) &g_producer_id_table, 0x2a80);
		src_player_ptr = src_player_ptr + 0xbd;
		dst_player_ptr = dst_player_ptr + 0xaa4;
	} while ((int) src_player_ptr < (int) 0x100a9bbc);
	/* 0x100311f0 is "gm_Open(): Geb\344ude" (Latin-1 a-umlaut, byte 0xe4). */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4e3, "gm_Open(): Geb\344ude", 1);
	g_entity_type_table = (char*) m_AllocTracked(0xca78, (const char*) 0x100311d8);
	if (g_entity_type_table == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4e8, "Memory could not be allocated!", 1);
		return -1;
	}
	g_entity_ptr = (unsigned char*) m_AllocTracked(0xa900, (const char*) 0x100311a0);
	memset((void*) g_entity_ptr, 0, 0xa900);
	if (g_entity_ptr == 0) {
		return -2;
	}
	sprintf((char*) path_buf, (char*) 0x1003118c, map_id, (char*) 0x10031194);
	file_handle = fopen((char*) path_buf, (char*) 0x1002944c);
	if (file_handle == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4f5, (char*) 0x10031154, 1);
		return -3;
	}
	fread((void*) g_entity_type_table, 0x24d, 0x58, file_handle);
	fflush(file_handle);
	g_item_def_table = (char*) m_AllocTracked(0xb9dc, (const char*) 0x10031140);
	if (g_item_def_table == 0) {
		return -4;
	}
	g_query_base = (unsigned short*) m_AllocTracked(0x14f218, (const char*) 0x1003112c);
	if (g_query_base == 0) {
		return -5;
	}
	memset((void*) g_query_base, 0, 0x14f218);
	sprintf((char*) path_buf, (char*) 0x1003118c, map_id, (char*) 0x10031120);
	file_handle = fopen((char*) path_buf, (char*) 0x1002944c);
	if (file_handle == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
			0x52d,
			"Objekt-Daten konnten nicht geladen werden! (A_Obj.dat)",
			1
		);
		return -6;
	}
	fread((void*) g_item_def_table, 0x41, 0x2dc, file_handle);
	fflush(file_handle);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x536, "gm_Open(): gm_InitObjektHersteller", 1);
	gm_InitObjektHersteller();
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x53a, "gm_Open(): gm_KillAllSpieler", 1);
	gm_InitEntitySlots();
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
		0x53e,
		"gm_Open(): ---- Das dusselige Datendesign hinbiegen !! -----",
		1
	);
	row_index = 0;
	do {
		producible_count = 0;
		slot_counter = 0x40;
		slot_ptr = (unsigned short*) (g_entity_type_table + row_index * 0x24d + 0x23);
		do {
			slot_entry = *slot_ptr;
			if (slot_entry != 0xffff) {
				slot_idx = slot_entry & 0x7fff;
				def_row = g_item_def_table + slot_idx * 0x40;
				cat_p = (char*) slot_idx;
				cat_p += (int) def_row;
				item_category = *(volatile char*) cat_p;
				if (((item_category == '\x02') || (item_category == '\x06')) && (slot_idx != 0xfd) &&
					((slot_entry & 0x8000) != 0)) {
					producible_count = producible_count + 1;
				}
			}
			slot_ptr = slot_ptr + 1;
			slot_counter = slot_counter + -1;
		} while (slot_counter != 0);
		*(char*) (g_entity_type_table + row_index * 0x24d + 0x21) =
			*(char*) (g_entity_type_table + row_index * 0x24d + 0x21) + producible_count;
		row_index = row_index + 1;
	} while (row_index < 0x58);
	/* Original seeds the RNG from the system timer before the exit log
	 * (fcn.1001a140 = srand(timeGetTime())). */
	srv_SeedRandomWithTime();
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x588, "gm_Open(): exit", 1);
	return 0;
}


/* Resets all entities to initial state. Walks the entity
 * tables and clears all active entities without deallocation. */
int g_citizen_count;
extern unsigned char g_current_season;
extern int g_dynasty_field_44;
char g_dynasty_field_48;
extern char g_dynasty_field_49;
extern int g_dynasty_field_4c;
char g_query_active;
char g_query_flag1;
char g_query_flag2;
char g_query_flag3;
extern unsigned char* g_query_filter_base;
unsigned short* g_query_cursor;
extern unsigned short* g_entity_table_end;
extern unsigned char g_slot_table[];
extern char g_entity_state_base[];
extern unsigned char g_entity_type_bytes[];
int g_array_count = 0;
/* Canonical definitions live in Units/m_alloc/m_alloc2.c. */
int g_flag_3c = 0;
void* g_array_ptr = 0;
char g_stream_pool[1] = {
    0x00,
};
int g_stream_count[4] = {
    0x00, 0x00, 0x00, 0x00,
};
int g_connection_counter = 0;

