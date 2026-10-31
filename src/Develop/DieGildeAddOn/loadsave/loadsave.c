extern char g_save_session_state[];
extern char g_saved_dynasty_field[];
extern int g_next_object_id;
extern char s_gzip_mode_rb[];
extern char g_dynasty_initial_trait_offset[];
#include "../game/entity.h"
#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "../../Units/vfs/vfs.h"
#include "../game/entity.h"

#include <stdlib.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "../../download_state.h"
#include "loadsave.h"
extern int g_file_version; 


extern unsigned int ls_ID2Ptr(void);
#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "../../Units/vfs/vfs.h"
#include "../game/entity.h"




extern int g_citizen_count;

extern unsigned int gm_LookupEntityRecordById(unsigned int);
extern int gm_ResolveEntityById(void**, void**, void**, int);
extern void gm_EntitySetField(void);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, int, int, ...);

extern int g_query_limit; 
extern int g_entity_id_counter;
extern int g_sequence_counter;



int g_file_version = 0x1005a;

char g_save_header_tail[] = "Savegame";

extern int g_active_player_count; /* 0x1003543c */
extern unsigned short* g_entity_table_end; /* 0x1003546c */

extern int g_save_header_aux;

extern int g_save_header_aux_b;

extern int g_save_extra_field;

/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings. */

/* ls_LoadEntities — deserializes the static-entity table from the save
 * stream.  Reads the header (2-byte id/count slot reused for the per-record
 * id read, 4-byte header field living in the ctx arg slot, extra fields),
 * then loops `header_field` times reading one entity record (0x21c stride)
 * with version-gated sections.
 *
 * Byte-match note: RELOC 2268/2268.  The reference reuses ONE local slot
 * for the initial 2-byte read and the per-iteration id read (so the C uses a
 * single `id` variable), bounds the loop with `header_field`, and allocates
 * header_field to the dead ctx arg slot (sub esp,0xc — 3 frame dwords). */

extern int g_aux_entity_count; /* 0x101de454 */

extern int g_save_info[2];







int __cdecl amt_fio_LoadAemter(void* stream, int version);
extern unsigned int ls_ID2Ptr(void);

/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings. */

extern int g_aux_entity_buffer; /* 0x101de55c */

extern int g_recv_game_buffer;


#include <string.h>

int __cdecl gv_AllocGraveyardField(unsigned char* field);

extern int g_field_worker_count[4];
extern int g_field_entry_count[4];

// SIZE 0x24
typedef struct {
	int id;           /* 0x00 */
	int type;         /* 0x04 */
	char data[0x10];  /* 0x08 */
	char b18;         /* 0x18 */
	char b19;         /* 0x19 */
	char b1a;         /* 0x1a */
	char b1b;         /* 0x1b */
	void* worker;     /* 0x1c */
	void* entry_table; /* 0x20 */
} GraveyardSlot;

/* Client-only (TL 0x4f3900, discarded): writes the graveyard slot of a field that ls_LoadGraveyardData
 * reads back (the client places it right before the loader). */
int __cdecl gv_fio_SaveGraveyardData(void* stream_ctx, unsigned char* field)
{
	extern unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);
	GraveyardSlot* slot;
	char* entry;
	char* worker;
	int i;

	slot = *(GraveyardSlot**) (field + 0x65);
	if (slot == 0) {
		return 0;
	}
	if (!vfs_fwrite(slot, 4, 1, stream_ctx)) {
		return 0;
	}
	if (!vfs_fwrite(&slot->type, 4, 1, stream_ctx)) {
		return 0;
	}
	if (!vfs_fwrite(&slot->b18, 1, 1, stream_ctx)) {
		return 0;
	}
	if (!vfs_fwrite(&slot->b19, 1, 1, stream_ctx)) {
		return 0;
	}
	if (!vfs_fwrite(&slot->b1a, 1, 1, stream_ctx)) {
		return 0;
	}
	if (!vfs_fwrite(&slot->b1b, 1, 1, stream_ctx)) {
		return 0;
	}
	entry = (char*) slot->entry_table;
	for (i = 0; i < g_field_entry_count[slot->type]; i++, entry += 0x44) {
		if (!vfs_fwrite(entry, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!vfs_fwrite(entry + 4, 0x10, 1, stream_ctx)) {
			return 0;
		}
		if (!vfs_fwrite(entry + 0x14, 0x10, 1, stream_ctx)) {
			return 0;
		}
		if (!vfs_fwrite(entry + 0x24, 5, 1, stream_ctx)) {
			return 0;
		}
		if (!vfs_fwrite(entry + 0x2c, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!vfs_fwrite(entry + 0x30, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!vfs_fwrite(entry + 0x34, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!vfs_fwrite(entry + 0x38, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!vfs_fwrite(entry + 0x3c, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!vfs_fwrite(entry + 0x40, 4, 1, stream_ctx)) {
			return 0;
		}
	}
	worker = (char*) slot->worker;
	for (i = 0; i < g_field_worker_count[slot->type]; i++, worker += 0x14) {
		int sid;

		if (!vfs_fwrite(worker, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!vfs_fwrite(worker + 4, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!vfs_fwrite(worker + 8, 2, 1, stream_ctx)) {
			return 0;
		}
		if (!vfs_fwrite(worker + 0xa, 2, 1, stream_ctx)) {
			return 0;
		}
		if (!vfs_fwrite(worker + 0xc, 1, 1, stream_ctx)) {
			return 0;
		}
		sid = (*(char**) (worker + 0x10) - (char*) slot->entry_table) / 0x44;
		if (!vfs_fwrite(&sid, 4, 1, stream_ctx)) {
			return 0;
		}
	}
	return 1;
}

/* Loads a graveyard field's savegame data: the slot header (id + type),
 * then the slot-entry table (g_field_entry_count[type] entries of 0x44 bytes) and
 * the worker table (g_field_worker_count[type] entries of 0x14 bytes).  Each entry's
 * worker slot stores a pointer to its 0x44-byte entry in the entry table.
 *
 * NOTE: the stream also reads the 4-byte slot->type (0x1001203e) between
 * the id and the b18/b19/b1a/b1b bytes.
 *
 * Shape notes (728/728, RELOC, from 88):
 * - The second loop reads its stream dword into `sid`, a local declared in the
 *   loop BODY, not into the function-scope `counter` the first loop counts
 *   with.  This is what closed the function.  Taking the address of `counter`
 *   made it stack-resident across both loops, which forced loop 1's latch to
 *   load the counter into ecx and the bound into eax, the mirror of the
 *   target's registers.  A body-scoped local is live only inside loop 2, so it
 *   coalesces onto the slot `counter` no longer needs and MSVC6 emits the
 *   target's [esp+0x1c] for both roles.  Function-scope spellings of the same
 *   idea all fall short: the dead `d` parameter fixes the latch but homes the
 *   read at [esp+0x24] (726/728); a function-scope local grows the frame from
 *   `push ecx` to `sub esp,8` (27/728); `field` moves the counter home to
 *   [esp+0x18] (725); `n` is 238; counting loop 1 in `c` or `d` is 24.
 *   An earlier note here claimed reading into `d` cost 9 bytes via a live
 *   &slot->type CSE; that was measured against the old loop-2 shape.
 * - The first loop's bound is a local reloaded at the TOP of the body, not
 *   folded into the latch compare.  Folding it emits `cmp eax,[edx*4+g]`
 *   where the target emits `mov ecx,[edx*4+g]; cmp eax,ecx`, 2 bytes short
 *   and a one-instruction shift through the rest of the function.
 * - Preheader statement order is entry, then n, then counter (docs
 *   msvc6-c-shapes.md §33); the other five permutations score 696-699.
 *
 * The ebx<->ebp role swap for `slot` (15 of the old 20 bytes) is closed by
 * loop 2, not loop 1.  Establishing `i = 0` BEFORE `worker` and spelling the
 * loop as a `while` with both increments in the body makes the counter, not
 * the worker cursor, the first value loop 2 establishes; the allocator then
 * gives `slot` ebx and the entry cursor ebp, matching the target at every one
 * of the 13 sites.  The `for (i = 0; ...; i++, worker += 0x14)` form with
 * `worker` assigned first scores 708 and is the shape every earlier batch
 * kept.  Verified in a standalone probe first: `i`-first flips the entry
 * `mov eax,ebx` and every `[ebx+disp]` operand at once.
 *
 * Confirmed inert or worse, measured on the whole function at the 723 shape
 * this file had before the loop-2 fix: swapping loop 2's two increments, 723;
 * spelling loop 2's store as `(char*) slot->entry_table + counter * 0x44`, 723;
 * `n > counter` as the loop 1 condition, 723; `!(counter >= n)`, 723;
 * `counter != n` and the unsigned compare, 721; `counter - n < 0`, 716, which
 * does put counter in eax and the bound in ecx as the target does but emits
 * `sub`/`js` for the latch; hoisting `worker` above `i` again, 708; a volatile
 * read on the bound, 707 to 718 depending on placement; `counter` incremented
 * through a volatile self-read, 707; splitting the bound into two locals, 723.
 *
 * The lever for loop 1's latch was NOT a latch spelling.  counter++ before the
 * bound reload always folds the bound into the compare (`cmp eax,[edx*4+g]`,
 * 2 bytes short, 481/728); the bound reload first always emitted the unfolded
 * compare with eax and ecx exchanged.  Roughly 60 spellings of the latch
 * itself, of the loop condition and of the declaration order never separated
 * the two, because the cause was outside loop 1 entirely: `counter` was
 * address-taken by loop 2's stream read, which pinned it to the stack for the
 * whole function.  Narrowing that read target to a body-scoped local in loop 2
 * fixed the latch and the slot together.  Found on an offline whole-function
 * probe (.scratch/lsprobe/sweep5.py) that scores the latch out of objdump
 * directly, which is far faster than iterating through rebrew test.
 *
 * All 27 relocation slots resolved: 23 calls to ReadVfsDataChecked
 * (0x10012440), one to gv_AllocGraveyardField (0x100109d0), and the globals
 * g_field_entry_count (x2) and g_field_worker_count (x2), all confirmed against
 * db/server.dll_functions.csv and the target disassembly. */

int __cdecl ls_LoadGraveyardData(void* stream_ctx, unsigned char* field)
{
	GraveyardSlot* slot;
	char* entry;
	char* worker;
	int counter;
	int i;
	int n;

	slot = (GraveyardSlot*) gv_AllocGraveyardField(field);
	if (slot == 0) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(slot, 4, 1, stream_ctx)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(&slot->type, 4, 1, stream_ctx)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(&slot->b18, 1, 1, stream_ctx)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(&slot->b19, 1, 1, stream_ctx)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(&slot->b1a, 1, 1, stream_ctx)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(&slot->b1b, 1, 1, stream_ctx)) {
		return 0;
	}
	entry = (char*) slot->entry_table;
	n = g_field_entry_count[slot->type];
	counter = 0;
	while (counter < n) {
		if (!ls_ReadVfsDataChecked(entry, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(entry + 4, 0x10, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(entry + 0x14, 0x10, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(entry + 0x24, 5, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(entry + 0x2c, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(entry + 0x30, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(entry + 0x34, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(entry + 0x38, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(entry + 0x3c, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(entry + 0x40, 4, 1, stream_ctx)) {
			return 0;
		}
		n = g_field_entry_count[slot->type];
		counter++;
		entry += 0x44;
	}
	/* `i` before `worker`, and a while with both increments in the body:
	 * that is what puts `slot` in ebx and the entry cursor in ebp, matching
	 * the target at all 13 sites. The for-loop form with `worker` first
	 * scores 708. */
	i = 0;
	worker = (char*) slot->worker;
	while (i < g_field_worker_count[slot->type]) {
		int sid;

		if (!ls_ReadVfsDataChecked(worker, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(worker + 4, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(worker + 8, 2, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(worker + 0xa, 2, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(worker + 0xc, 1, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&sid, 4, 1, stream_ctx)) {
			return 0;
		}
		*(void**) (worker + 0x10) = (void*) &((int*) slot->entry_table)[sid * 0x11];
		i++;
		worker += 0x14;
	}
	return 1;
}


extern int __cdecl gm_RandomMod(int n);
extern int __cdecl amt_FindEntity26(int entity_id);
extern int __cdecl amt_FindEntity27(int entity_id);
extern int __cdecl gm_AddObjekt(int a, int b, int c);
extern unsigned char g_current_season;
/* 189 4-byte entries per object type; only the low word of each entry is read. */

void __cdecl InitNewDynastyEntity(int a, void* unused, unsigned short word_arg, void* entity)
{
	int i;
	int j;
	int cursor;
	int off;
	int flags;
	int k;

	(void) unused;

	if (a == 0x15) {
		flags = *(int*) ((char*) entity + 0x1cc);
		flags |= 0x1000;
		*(int*) ((char*) entity + 0x1cc) = flags;
		amt_FindEntity26(*(int*) ((char*) entity + 4));
	} else {
		flags = *(int*) ((char*) entity + 0x1cc);
		flags |= 0x2000;
		*(int*) ((char*) entity + 0x1cc) = flags;
		amt_FindEntity27(*(int*) ((char*) entity + 4));
	}
	*(unsigned short*) ((char*) entity + 0xa) = word_arg;
	*(char*) ((char*) entity + 0xc) = 0;
	for (cursor = (int) g_relationship_matrix_primary; cursor < (int) g_relationship_matrix_primary + 0x90000; cursor += 0x300) {
		i = 0;
		off = cursor - (int) g_relationship_matrix_primary;
		for (; i < 0x300; i++) {
			g_relationship_matrix_primary[off + i] = (unsigned char) (gm_RandomMod(0x40) - 0x20);
			g_relationship_matrix_secondary[off + i] = 0;
		}
	}
	*(unsigned short*) ((char*) entity + 0x50) = 0x7fff;
	*(int*) ((char*) entity + 0x7c) = 0;
	*(char*) ((char*) entity + 0x58) = 0;
	for (k = 0; k < 8; k++) {
		((int*) ((char*) entity + 0x5c))[k] = -1;
	}
	*(int*) ((char*) entity + 0x170) = 0;
	*(int*) ((char*) entity + 0x16c) = 0;
	*(float*) ((char*) entity + 0x1c) = 1000.0f;
	*(float*) ((char*) entity + 0x14) = 1.0f;
	*(float*) ((char*) entity + 0x20) = 12.0f;
	*(float*) ((char*) entity + 0x10) = 330.0f;
	*(float*) ((char*) entity + 0x18) = 1000.0f;
	for (j = 0; j < 5; j++) {
		*(char*) ((char*) entity + 0x80 + j) =
			(char) (long) ((float) (gm_RandomMod(0x2a) & 0xffff) + *(float*) &g_dynasty_initial_trait_offset);
	}
	*(char*) ((char*) entity + 0xd) = 9;
	gm_AddObjekt(*(int*) ((char*) entity + 4),
	             (unsigned short) g_entity_slot_table[(unsigned int) g_current_season * 189],
	             0xf42400);
	gm_RandomMod(2);
	*(char*) ((char*) entity + 2) = 3;
}


/* Client-only savegame writers (TL 0x51ebc0, 0x51f170, 0x520860; discarded). Each writes what the
 * matching loader reads back: the object table, the 16 dynamic entities and the two relationship
 * matrices. The client saves through vfs_fwrite, whose unsigned result 0 means failure. */

int __cdecl ls_SaveObjects(void* file)
{
	extern unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);
	int count;
	int i;
	unsigned char* rec;

	count = 0;
	for (i = 0; i < 0x5008; i++) {
		if (*(short*) ((unsigned char*) g_query_base + i * 0x43) != 0) {
			count++;
		}
	}
	if (vfs_fwrite(&count, 4, 1, file) <= 0) {
		return 0;
	}
	for (i = 0; i < 0x5008; i++) {
		rec = (unsigned char*) g_query_base + i * 0x43;
		if (*(short*) rec != 0) {
			if (vfs_fwrite(rec, 2, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 2, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 6, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0xa, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0xe, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x12, 1, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(rec + 0x13, 1, 1, file) <= 0) {
				return 0;
			}
			rec += 0x1c;
			if (vfs_fwrite(rec, 0x1f, 1, file) <= 0) {
				return 0;
			}
		}
	}
	return 1;
}

/* Client-only (TL 0x51ecf0, discarded): writes the building table that ls_LoadBuildingEntityState
 * reads back, the plant map, graveyard and alchemist records of special buildings, then the
 * building-site boxes. The client reallocates the box buffer to its own size before writing it. */
int __cdecl ls_SaveBuildingEntityState(void* file)
{
	extern unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);
	extern int __cdecl gv_fio_SaveGraveyardData(void* stream_ctx, unsigned char* field);
	extern int __cdecl ahm_fio_SaveAhmInfo(void* file, char* obj);
	int count;
	int i;
	char* esi;
	int j;

	count = 0;
	for (i = 0; i < 0x100; i++) {
		if (g_entity_ptr[i * 0xa9] != 0) {
			count++;
		}
	}
	if (vfs_fwrite(&count, 4, 1, file) <= 0) {
		return 0;
	}
	for (i = 0; i < 0x100; i++) {
		esi = (char*) (g_entity_ptr + i * 0xa9);
		if (esi[0] == 0) {
			continue;
		}
		if (vfs_fwrite(esi, 1, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x01, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x05, 0x20, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x25, 2, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x27, 2, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x29, 2, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x2b, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x2f, 1, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x34, 1, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x35, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x39, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x3d, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x41, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x45, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x49, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x4d, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x51, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x55, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x5a, 2, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(esi + 0x5c, 1, 1, file) <= 0) {
			return 0;
		}
		if (esi[0] == 0x1e) {
			for (j = 0; j < 0x40; j++) {
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18), 4, 1, file) <= 0) {
					return 0;
				}
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18 + 4), 4, 1, file) <= 0) {
					return 0;
				}
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18 + 8), 1, 1, file) <= 0) {
					return 0;
				}
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18 + 9), 1, 1, file) <= 0) {
					return 0;
				}
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18 + 0xa), 2, 1, file) <= 0) {
					return 0;
				}
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18 + 0x10), 4, 1, file) <= 0) {
					return 0;
				}
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18 + 0xc), 1, 1, file) <= 0) {
					return 0;
				}
				if (vfs_fwrite((void*) (*(int*) (esi + 0x71) + j * 0x18 + 0xd), 1, 1, file) <= 0) {
					return 0;
				}
			}
		}
		else if (esi[0] == 0x48 || esi[0] == 0x49 || esi[0] == 0x4a) {
			if (gv_fio_SaveGraveyardData(file, (unsigned char*) esi) == 0) {
				return 0;
			}
		}
		else if (esi[0] == 0x4b || esi[0] == 0x4c || esi[0] == 0x4d) {
			if (ahm_fio_SaveAhmInfo(file, esi) == 0) {
				return 0;
			}
		}
		else {
			if (vfs_fwrite(esi + 0x65, 0x30, 1, file) <= 0) {
				return 0;
			}
		}
		if (vfs_fwrite(esi + 0x99, 0x10, 1, file) <= 0) {
			return 0;
		}
	}
	if (vfs_fwrite(&g_aux_entity_count, 4, 1, file) <= 0) {
		return 0;
	}
	g_aux_entity_buffer = (int) realloc((void*) g_aux_entity_buffer, g_aux_entity_count * 0x60);
	for (i = 0; i < g_aux_entity_count; i++) {
		if (vfs_fwrite((void*) (g_aux_entity_buffer + i * 0x60), 0x40, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite((void*) (g_aux_entity_buffer + i * 0x60 + 0x40), 0x10, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite((void*) (g_aux_entity_buffer + i * 0x60 + 0x50), 0x10, 1, file) <= 0) {
			return 0;
		}
	}
	return 1;
}

int __cdecl ls_SaveDynamicEntities(void* f)
{
	extern unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);
	extern int g_file_version;
	int i;

	for (i = 0; i < 16; i++) {
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0, 2, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x2, 0x10, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x14, 4, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x28, 4, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x1c, 4, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x20, 4, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x2c, 4, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x30, 4, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x34, 4, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x38, 4, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x40, 4, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x44, 4, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x48, 4, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x4c, 4, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x50, 4, 1, f) <= 0) {
			return 0;
		}
		if (g_file_version >= 0x10014) {
			if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x54, 4, 1, f) <= 0) {
				return 0;
			}
			if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x58, 4, 1, f) <= 0) {
				return 0;
			}
			if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x5c, 4, 1, f) <= 0) {
				return 0;
			}
			if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x3c, 4, 1, f) <= 0) {
				return 0;
			}
			if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x64, 4, 1, f) <= 0) {
				return 0;
			}
			if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x68, 4, 1, f) <= 0) {
				return 0;
			}
			if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x6c, 4, 1, f) <= 0) {
				return 0;
			}
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x60, 4, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x74, 0x11, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x88, 4, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x8c, 0x10, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x9c, 0xc, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0xa8, 4, 1, f) <= 0) {
			return 0;
		}
		if (vfs_fwrite((char*) g_entity_base + i * 0xac + 0x70, 4, 1, f) <= 0) {
			return 0;
		}
	}
	return 1;
}

/* Client-only (TL 0x51f480, discarded): writes the player slots that ls_LoadEntities reads back, after
 * the slot count and the ids of the records the header pointers name (-1 for none). Two fields follow
 * the server's loader, not the client's: the client writes its local player slot (0x774970) first, and
 * the server reads that field into a local because it has no such variable; and the client writes the
 * fields at slot + 0x54 and + 0x18c less 0x59a and 0x639, which its loader adds back and the server's
 * loader does not. */
int __cdecl ls_SaveEntities(void* file)
{
	extern unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);
	char* s;
	char* slot;
	int i;
	int none;
	int id;
	int tmp;
	int count;

	s = (char*) file;
	none = -1;
#if defined(REBREW_SERVER)
	if (vfs_fwrite(&none, 2, 1, s) <= 0) {
#else
	if (vfs_fwrite((void*) 0x774970, 2, 1, s) <= 0) {
#endif
		return 0;
	}
	count = 0;
	for (slot = (char*) g_slot_table; slot < (char*) g_slot_table + 0x65400; slot += 0x21c) {
		if (*(unsigned short*) slot != 0xffff) {
			count++;
		}
	}
	if (vfs_fwrite(&count, 4, 1, s) <= 0) {
		return 0;
	}
	if (vfs_fwrite(g_save_header_aux ? (char*) g_save_header_aux + 4 : (char*) &none, 4, 1, s) <= 0) {
		return 0;
	}
	if (vfs_fwrite(g_save_header_aux_b ? (char*) g_save_header_aux_b + 4 : (char*) &none, 4, 1, s) <= 0) {
		return 0;
	}
	for (i = 0; i < 8; i++) {
		id = -1;
		if (vfs_fwrite((&g_save_extra_field)[i] ? (char*) (&g_save_extra_field)[i] + 4 : (char*) &id, 4, 1, s) <= 0) {
			return 0;
		}
	}
	for (slot = (char*) g_slot_table; slot < (char*) g_slot_table + 0x65400; slot += 0x21c) {
		if (*(unsigned short*) slot == 0xffff) {
			continue;
		}
		if (vfs_fwrite(slot, 2, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x20c, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 2, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 4, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 8, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 9, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0xa, 2, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0xc, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0xd, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x10, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x14, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x18, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1c, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x20, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x24, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x28, 2, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x2c, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x30, 0x10, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x40, 0x10, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x50, 2, 1, s) <= 0) {
			return 0;
		}
#if defined(REBREW_SERVER)
		if (vfs_fwrite(slot + 0x54, 4, 1, s) <= 0) {
#else
		tmp = *(int*) (slot + 0x54) - 0x59a;
		if (vfs_fwrite(&tmp, 4, 1, s) <= 0) {
#endif
			return 0;
		}
		if (vfs_fwrite(slot + 0x58, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x5c, 0x20, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x7c, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x80, 5, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x88, 0xa8, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x164, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x165, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x166, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x167, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x168, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x169, 1, 1, s) <= 0) {
			return 0;
		}
		none = -1;
		if (vfs_fwrite(*(char**) (slot + 0x16c) ? *(char**) (slot + 0x16c) + 1 : (char*) &none, 4, 1, s) <= 0) {
			return 0;
		}
		none = -1;
		if (vfs_fwrite(*(char**) (slot + 0x170) ? *(char**) (slot + 0x170) + 1 : (char*) &none, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x174, 4, 1, s) <= 0) {
			return 0;
		}
		none = -1;
		if (vfs_fwrite(*(char**) (slot + 0x17c) ? *(char**) (slot + 0x17c) + 4 : (char*) &none, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x180, 1, 1, s) <= 0) {
			return 0;
		}
#if defined(REBREW_SERVER)
		if (vfs_fwrite(slot + 0x18c, 4, 1, s) <= 0) {
#else
		tmp = *(int*) (slot + 0x18c) - 0x639;
		if (vfs_fwrite(&tmp, 4, 1, s) <= 0) {
#endif
			return 0;
		}
		if (vfs_fwrite(slot + 0x190, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x194, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x198, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x19c, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1a0, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1a4, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1a8, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1ac, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1b0, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1b1, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1b4, 0x10, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1c8, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1cc, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1d0, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1d4, 0x10, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1e4, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1e8, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1ec, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1f0, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1c5, 1, 1, s) <= 0) {
			return 0;
		}
		id = *(int**) (slot + 0x184) ? **(int**) (slot + 0x184) : -1;
		if (vfs_fwrite(&id, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x1f4, 0x18, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x210, 4, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x214, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x215, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x216, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x217, 1, 1, s) <= 0) {
			return 0;
		}
		if (vfs_fwrite(slot + 0x218, 1, 1, s) <= 0) {
			return 0;
		}
	}
	return 1;
}

/* Client-only (TL 0x520310, discarded): writes the five town tables and four city records that
 * ls_LoadTownData reads back, always with 0x55 records per town. */
int __cdecl ls_SaveTownData(void* file)
{
	extern unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);
	extern unsigned char g_city_records[];
	typedef struct {
		short id; /* 0x00 */
		short pad02;
		int a04; /* 0x04 */
		int a08; /* 0x08 */
		int a0c; /* 0x0c */
		char pad10[0x10];
		int a20; /* 0x20 */
		int a24; /* 0x24 */
		char pad28[4];
		int a2c;   /* 0x2c */
		int a30;   /* 0x30 */
		int a34;   /* 0x34 */
		int a38;   /* 0x38 */
		short a3c; /* 0x3c */
		char pad3e[0x42];
	} TOWN_REC; /* 0x80 */

	typedef struct {
		int h[4];           /* 0x00 */
		TOWN_REC rec[0x55]; /* 0x10 */
	} TOWN;                 /* 0x2a90 */

	typedef struct {
		char name[0x20]; /* 0x000 */
		char pad20[0x20];
		char a40[8]; /* 0x040 */
		char a48;    /* 0x048 */
		char pad49[3];
		int a4c;   /* 0x04c */
		int a50;   /* 0x050 */
		short a54; /* 0x054 */
		short pad56;
		char a58[8]; /* 0x058 */
		char a60;    /* 0x060 */
		char a61;    /* 0x061 */
		char pad62[2];
		char a64[10][8]; /* 0x064 */
		char ab4[10][8]; /* 0x0b4 */
		char a104;       /* 0x104 */
		char a105;       /* 0x105 */
		char pad106[2];
		int a108[4];    /* 0x108 */
		int a118[4];    /* 0x118 */
		int a128;       /* 0x128 */
		char a12c[0xb]; /* 0x12c */
		char a137;      /* 0x137 */
		char a138[7];   /* 0x138 */
		char a13f;      /* 0x13f */
		char a140;      /* 0x140 */
		char a141;      /* 0x141 */
		char a142;      /* 0x142 */
		char pad143;
		char a144[8][0x12]; /* 0x144 */
		int a1d4;           /* 0x1d4 */
		int a1d8;           /* 0x1d8 */
		char a1dc[0xd0];    /* 0x1dc */
		char pad2ac[0x40];
		char a2ec[8]; /* 0x2ec */
	} City;           /* 0x2f4 */
	int count;
	int j;
	TOWN* town;
	TOWN_REC* rec;
	City* city;

	count = 0x55;
	if (vfs_fwrite(&count, 4, 1, file) <= 0) {
		return 0;
	}
	for (count = 0; count < 5; count++) {
		town = &((TOWN*) g_entity_end)[count];
		if (vfs_fwrite(&town->h[0], 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&town->h[1], 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&town->h[2], 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&town->h[3], 4, 1, file) <= 0) {
			return 0;
		}
		for (j = 0; j < 0x55; j++) {
			rec = &town->rec[j];
			if (vfs_fwrite(&rec->id, 2, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&rec->a04, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&rec->a08, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&rec->a0c, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&rec->a20, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&rec->a24, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&rec->a30, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&rec->a34, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&rec->a38, 4, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&rec->a3c, 2, 1, file) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&rec->a2c, 4, 1, file) <= 0) {
				return 0;
			}
		}
	}
	for (count = 0; count < 4; count++) {
		city = &((City*) g_city_records)[count];
		if (vfs_fwrite(city->name, 0x20, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(city->a40, 8, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&city->a48, 1, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&city->a4c, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&city->a50, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&city->a54, 2, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(city->a58, 8, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&city->a60, 1, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&city->a61, 1, 1, file) <= 0) {
			return 0;
		}
		for (j = 0; j < 10; j++) {
			if (vfs_fwrite(city->a64[j], 8, 1, file) <= 0) {
				return 0;
			}
		}
		for (j = 0; j < 10; j++) {
			if (vfs_fwrite(city->ab4[j], 8, 1, file) <= 0) {
				return 0;
			}
		}
		if (vfs_fwrite(&city->a104, 1, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&city->a105, 1, 1, file) <= 0) {
			return 0;
		}
		for (j = 0; j < 4; j++) {
			if (vfs_fwrite(&city->a108[j], 4, 1, file) <= 0) {
				return 0;
			}
		}
		for (j = 0; j < 4; j++) {
			if (vfs_fwrite(&city->a118[j], 4, 1, file) <= 0) {
				return 0;
			}
		}
		if (vfs_fwrite(&city->a128, 4, 1, file) <= 0) {
			return 0;
		}
		for (j = 0; j < 0xb; j++) {
			if (vfs_fwrite(&city->a12c[j], 1, 1, file) <= 0) {
				return 0;
			}
		}
		if (vfs_fwrite(&city->a137, 1, 1, file) <= 0) {
			return 0;
		}
		for (j = 0; j < 7; j++) {
			if (vfs_fwrite(&city->a138[j], 1, 1, file) <= 0) {
				return 0;
			}
		}
		if (vfs_fwrite(&city->a13f, 1, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&city->a140, 1, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&city->a141, 1, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&city->a142, 1, 1, file) <= 0) {
			return 0;
		}
		for (j = 0; j < 8; j++) {
			if (vfs_fwrite(city->a144[j], 0x12, 1, file) <= 0) {
				return 0;
			}
		}
		if (vfs_fwrite(&city->a1d4, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&city->a1d8, 4, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(city->a1dc, 0xd0, 1, file) <= 0) {
			return 0;
		}
		if (vfs_fwrite(city->a2ec, 8, 1, file) <= 0) {
			return 0;
		}
	}
	return 1;
}

int __cdecl ls_SaveRelationships(void* file)
{
	extern unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);
	int i;
	int j;

	for (j = 0; j < 0x300; j++) {
		for (i = 0; i < 0x300; i++) {
			if (vfs_fwrite(&g_relationship_matrix_primary[j * 0x300 + i], 1, 1, file) <= 0) {
				return 0;
			}
		}
	}
	for (j = 0; j < 0x300; j++) {
		for (i = 0; i < 0x300; i++) {
			if (vfs_fwrite(&g_relationship_matrix_secondary[j * 0x300 + i], 1, 1, file) <= 0) {
				return 0;
			}
		}
	}
	return 1;
}

int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);
#if defined(REBREW_SERVER)
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx)
{
	/* vfs_ReadData wrapper: nonzero on success (unsigned > 0 carry idiom). */
	return (unsigned int) vfs_ReadData(outBuffer, elementSize, elementCount, streamCtx) > 0;
}
#endif

#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "../../Units/vfs/vfs.h"
#include "../game/entity.h"

#include <stdlib.h>


extern int g_file_version; /* 0x1002d4ec */

#include "save_header_tail.h"
extern char g_save_header_tail[]; /* 0x1002d4f0 */
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
int __cdecl ls_LoadSavegameHeader(void* stream, char* dest)
{
	void* buf;
	int i;

	buf = m_alloc(0xe100, "ls:tmp");
	if (!ls_ReadVfsDataChecked(dest, 4, 1, stream)) {
		return 0;
	}
	g_file_version = *(int*) dest;
	if (!ls_ReadVfsDataChecked(dest + 4, 1, 1, stream)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(dest + 5, 0x20, 1, stream)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(dest + 0x28, 8, 1, stream)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(dest + 0x30, 1, 1, stream)) {
		return 0;
	}
	if (g_file_version >= 0x10033) {
		if (!ls_ReadVfsDataChecked(dest + 0x31, 1, 1, stream)) {
			return 0;
		}
	}
	if (g_file_version >= 0x10028) {
		if (!ls_ReadVfsDataChecked(dest + 0x32, 0xe, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(dest + 0x40, 0x10, 1, stream)) {
			return 0;
		}
		if (g_file_version >= 0x10054) {
			if (!ls_ReadVfsDataChecked(dest + 0x50, 0x10, 1, stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(dest + 0x63, 1, 1, stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(dest + 0x64, 4, 1, stream)) {
				return 0;
			}
		}
		if (!ls_ReadVfsDataChecked(dest + 0x60, 1, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(dest + 0x61, 1, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(dest + 0x62, 1, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(dest + 0x68, 4, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(dest + 0x6c, 1, 1, stream)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(dest + 0x6d, 1, 1, stream)) {
			return 0;
		}
		if (g_file_version >= 0x1002b) {
			if (!ls_ReadVfsDataChecked(dest + 0x70, 4, 1, stream)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(dest + 0x74, 4, 1, stream)) {
				return 0;
			}
		}
		else {
			*(int*) (dest + 0x70) = -1;
			*(int*) (dest + 0x74) = -1;
		}
		if (g_file_version >= 0x10034) {
			for (i = 0; i < 8; i++) {
				if (!ls_ReadVfsDataChecked(dest + 0x78 + i * 4, 4, 1, stream)) {
					return 0;
				}
			}
		}
		if (!ls_ReadVfsDataChecked(buf, 0xe100, 1, stream)) {
			return 0;
		}
	}
	if (buf != 0) {
		m_FreeTracked(buf);
	}
	if (g_file_version < 0x10025) {
		return 0;
	}
	if (g_file_version >= 0x10038) {
		if (!ls_ReadVfsDataChecked(dest + 0x98, 4, 1, stream)) {
			return 0;
		}
	}
	else {
		*(int*) (dest + 0x98) = 2;
	}
	if (g_file_version >= 0x10039) {
		dest += 0x9c;
		if (!ls_ReadVfsDataChecked(dest, 0x60, 1, stream)) {
			return 0;
		}
	}
	else {
		*(struct SaveHeaderTail*) (dest + 0x9c) = *(struct SaveHeaderTail*) g_save_header_tail;
	}
	return 1;
}
#endif

void __cdecl gm_CleanupObjectEntities(void);
extern int g_query_limit; /* 0x10035450 */
#if defined(REBREW_SERVER)
int __cdecl ls_LoadExistingEntities(void* arg1)
{
	int count;
	int i;
	unsigned char* record_cursor;

	gm_CleanupObjectEntities();
	if (!ls_ReadVfsDataChecked(&count, 4, 1, arg1)) {
		return 0;
	}
	for (i = 0; i < count; i++) {
		record_cursor = (unsigned char*) g_query_base + i * 0x43;
		if (!ls_ReadVfsDataChecked(record_cursor, 2, 1, arg1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(record_cursor + 2, 4, 1, arg1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(record_cursor + 6, 4, 1, arg1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(record_cursor + 0xa, 4, 1, arg1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(record_cursor + 0xe, 4, 1, arg1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(record_cursor + 0x12, 1, 1, arg1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(record_cursor + 0x13, 1, 1, arg1)) {
			return 0;
		}
		record_cursor += 0x1c;
		if (!ls_ReadVfsDataChecked(record_cursor, 0x1f, 1, arg1)) {
			return 0;
		}
	}
	g_query_limit = count;
	return 1;
}
#endif
/* Loads building entity state from a save file. Reads
 * building type, owner, upgrade level, and production
 * state for each building entity. */

extern int g_citizen_count;


/* Loads town-level data from a save file. Reads town name,
 * treasury, population, building counts, and political
 * state (offices, elections). */

#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "../../Units/vfs/vfs.h"
#include "../game/entity.h"

#include <stdlib.h>
#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

int __cdecl gv_AllocGraveyardField(int);


int __cdecl ahm_AllocAhmInfo(void* stream, int slot);
extern int g_file_version; /* 0x1002d4ec */
extern int g_aux_entity_count; /* 0x101de454 */
extern int g_aux_entity_buffer; /* 0x101de55c */


/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings.
 *
 * Shape notes (whole-image linked residue 5404 -> 4740 over the byte-offset form):
 * - The outer loop, the 0x1e arm and the aux loop are counted index loops
 *   (`ptr + i * 0xa9`; `base + i * 0x18 + N` with `i < 0x40`;
 *   `buf + i * 0x60 + N`).  Strength reduction then gives the reference's
 *   `xor ebx,ebx` / `lea [ebx+edx+N]` induction, its `mov ecx,ebx;
 *   add ecx,edx` first site, `lea esi,[edx+ecx]`, and `xor esi,esi` inside
 *   the aux guard.  Byte-offset loops (`i += 0x18`) put the load on the left
 *   of every address sum and lose 2 bytes at the first site.
 * - The state block is `memset` + `|= 1` (docs/msvc6-c-shapes.md section 71).
 *   Its extra candidates are what give the -1 sentinel `ebp` (`or ebp,-1` once,
 *   three `mov [..],ebp`), so the field reads need no `volatile` any more; with
 *   the plain loads the scheduler also hoists each load above the pushes, as
 *   the reference does.
 * - The state block addresses `esi + 0x99` directly (no `state_ptr` local).
 *   That lets c2 prove `[eax]` and `[esi+0xa5]` disjoint without /Ow, which
 *   is what places the 0xa5 store inside the `|= 1` read-modify-write.
 * - Byte-exact at the link under the default `/O2 /Gd` (measured, whole-image
 *   .text 4740 -> 4735).  Under `/O2 /Gd /Ow` the 0x4b-0x4d arm emits
 *   `add esp,8` before `mov [ebx],eax` (the stores stop aliasing), 5 bytes. */


unsigned int __cdecl ls_LoadBuildingEntityState(void* stream_ctx)
{
	int entity_count;
	int current_index;
	char* esi;
	int load_result;
	int* ebx;
	int dummy;
	register int neg1;

	gm_ResetAllEntities();

	if (!ls_ReadVfsDataChecked(&entity_count, 4, 1, stream_ctx)) {
		return 0;
	}

	current_index = 0;
	if (0 < entity_count) {
		neg1 = -1;
		while (current_index < entity_count) {
			esi = (char*) (g_entity_ptr + current_index * 0xa9);

			if (!ls_ReadVfsDataChecked(esi, 1, 1, stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x01, 4, 1, stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x05, 0x20, 1, stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x25, 2, 1, stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x27, 2, 1, stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x29, 2, 1, stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x2b, 4, 1, stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x2f, 1, 1, stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x34, 1, 1, stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x35, 4, 1, stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x39, 4, 1, stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x3d, 4, 1, stream_ctx)) {
				return 0;
			}

			ebx = (int*) (esi + 0x41);
			if (!ls_ReadVfsDataChecked(ebx, 4, 1, stream_ctx)) {
				return 0;
			}
			if (*ebx > 4) {
				*ebx = 2;
			}

			if (!ls_ReadVfsDataChecked(esi + 0x45, 4, 1, stream_ctx)) {
				return 0;
			}

			if (g_file_version >= 0x10028) {
				if (!ls_ReadVfsDataChecked(esi + 0x49, 4, 1, stream_ctx)) {
					return 0;
				}
			}

			if (g_file_version < 0x10032) {
				if (!ls_ReadVfsDataChecked(&dummy, 4, 1, stream_ctx)) {
					return 0;
				}
			}

			if (g_file_version >= 0x10057) {
				if (!ls_ReadVfsDataChecked(esi + 0x4d, 4, 1, stream_ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(esi + 0x51, 4, 1, stream_ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(esi + 0x55, 4, 1, stream_ctx)) {
					return 0;
				}
			}

			if (!ls_ReadVfsDataChecked(esi + 0x5a, 2, 1, stream_ctx)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x5c, 1, 1, stream_ctx)) {
				return 0;
			}

			if (esi[0] == 0x1e) {
				*(int*) (esi + 0x71) = (int) m_alloc(0x600, "f3g:PlantMap");
				for (load_result = 0; load_result < 0x40; load_result++) {
					if (!ls_ReadVfsDataChecked((void*) (*(int*) (esi + 0x71) + load_result * 0x18), 4, 1, stream_ctx)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(int*) (esi + 0x71) + load_result * 0x18 + 4),
							4,
							1,
							stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(int*) (esi + 0x71) + load_result * 0x18 + 8),
							1,
							1,
							stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(int*) (esi + 0x71) + load_result * 0x18 + 9),
							1,
							1,
							stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(int*) (esi + 0x71) + load_result * 0x18 + 0xa),
							2,
							1,
							stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(int*) (esi + 0x71) + load_result * 0x18 + 0x10),
							4,
							1,
							stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(int*) (esi + 0x71) + load_result * 0x18 + 0xc),
							1,
							1,
							stream_ctx
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (*(int*) (esi + 0x71) + load_result * 0x18 + 0xd),
							1,
							1,
							stream_ctx
						)) {
						return 0;
					}
					*(int*) (*(int*) (esi + 0x71) + load_result * 0x18 + 0x14) = 0;
				}
			}
			else if (esi[0] == 0x48 || esi[0] == 0x49 || esi[0] == 0x4a) {
				if (g_file_version >= 0x10047) {
					load_result = ls_LoadGraveyardData(stream_ctx, (unsigned char*) esi);
				}
				else {
					if (!ls_ReadVfsDataChecked(esi + 0x65, 0x30, 1, stream_ctx)) {
						return 0;
					}
					*(int*) (esi + 0x65) = gv_AllocGraveyardField((int) esi);
					goto label_10012d72;
				}
				if (load_result == 0) {
					return 0;
				}
			}
			else if (esi[0] == 0x4b || esi[0] == 0x4c || esi[0] == 0x4d) {
				if (g_file_version >= 0x10049) {
					load_result = ahm_AllocAhmInfo(stream_ctx, (int) esi);
				}
				else {
					int* ahm_info;
					if (!ls_ReadVfsDataChecked(esi + 0x65, 0x30, 1, stream_ctx)) {
						return 0;
					}
					ahm_info = (int*) m_alloc(0x3c, "AHM_INFO");
					*(int*) (esi + 0x65) = (int) ahm_info;
					*ahm_info = neg1;
					goto label_10012d72;
				}
				if (load_result == 0) {
					return 0;
				}
			}
			else {
				if (!ls_ReadVfsDataChecked(esi + 0x65, 0x30, 1, stream_ctx)) {
					return 0;
				}
			}

		label_10012d72:
			if (g_file_version >= 0x10043) {
				if (!ls_ReadVfsDataChecked(esi + 0x99, 0x10, 1, stream_ctx)) {
					return 0;
				}
			}
			else {
				memset(esi + 0x99, 0, 0x10);
				*(int*) (esi + 0x99) |= 1;
				*(int*) (esi + 0xa5) = neg1;
			}

			*(int*) (esi + 0x30) = 0x1388;
			*(int*) (esi + 0x95) = neg1;
			current_index++;
		}
	}

	if (!ls_ReadVfsDataChecked(&g_aux_entity_count, 4, 1, stream_ctx)) {
		return 0;
	}

	g_aux_entity_buffer = (int) realloc((void*) g_aux_entity_buffer, g_aux_entity_count * 0x60);
	for (load_result = 0; load_result < g_aux_entity_count; load_result++) {
		if (!ls_ReadVfsDataChecked((void*) (g_aux_entity_buffer + load_result * 0x60), 0x40, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked((void*) (g_aux_entity_buffer + load_result * 0x60 + 0x40), 0x10, 1, stream_ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked((void*) (g_aux_entity_buffer + load_result * 0x60 + 0x50), 0x10, 1, stream_ctx)) {
			return 0;
		}
	}

	return 1;
}


#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "../../Units/vfs/vfs.h"
#include "../game/entity.h"

#include <stdlib.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"


extern int g_file_version; /* 0x1002d4ec */
/* 0x1009aca2: two bytes into the 0xac-byte entity records at g_entity_base. */
#define g_dynamic_entities ((char*) g_entity_base + 2)


/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings. */

int __cdecl ls_LoadDynamicEntities(void* file)
{
    int i;
    int count;
    int i2;
    char* record_cursor;

    for (i = 0; i < 16; i++) {

        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac - 2], 2, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac], 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x12], 4, 1, file)) {
            return 0;
        }
        if (g_file_version >= 0x1002c) {
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x26], 4, 1, file)) {
                return 0;
            }
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x1a], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x1e], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x2a], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x2e], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x32], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x36], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x3e], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x42], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x46], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x4a], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x4e], 4, 1, file)) {
            return 0;
        }
        if (g_file_version >= 0x10014) {
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x52], 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x56], 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x5a], 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x3a], 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x62], 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x66], 4, 1, file)) {
                return 0;
            }
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x6a], 4, 1, file)) {
                return 0;
            }
        }
        if (g_file_version >= 0x10056) {
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x5e], 4, 1, file)) {
                return 0;
            }
        }
        else {
            *(int*) (&g_dynamic_entities[i * 0xac + 0x5e]) = 0x3f800000;
        }
        if (g_file_version >= 0x10015) {
            count = (g_file_version < 0x10046) ? 0x0e : 0x11;
            for (i2 = 0; i2 < count; i2++) {
                if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x72 + i2], 1, 1, file)) {
                    return 0;
                }
            }
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x86], 4, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x8a], 0x10, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x9a], 0x0c, 1, file)) {
            return 0;
        }
        if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0xa6], 4, 1, file)) {
            return 0;
        }
        if (g_file_version >= 0x10018) {
            if (!ls_ReadVfsDataChecked(&g_dynamic_entities[i * 0xac + 0x6e], 4, 1, file)) {
                return 0;
            }
        }
    }

    return 1;
}


#if !defined(REBREW_SERVER)
extern unsigned short g_774970;
#endif

int __cdecl ls_LoadEntities(void* ctx)
{
	int id;
	int header_field;
	char* slot;
	int* slot_ext_ptr;
	int i;

#if defined(REBREW_SERVER)
	if (ls_ReadVfsDataChecked(&id, 2, 1, ctx) == 0) {
#else
	if (ls_ReadVfsDataChecked(&g_774970, 2, 1, ctx) == 0) {
#endif
		return 0;
	}
	if (ls_ReadVfsDataChecked(&header_field, 4, 1, ctx) == 0) {
		return 0;
	}
	g_citizen_count = header_field;
	if (ls_ReadVfsDataChecked(&g_save_header_aux, 4, 1, ctx) == 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked(&g_save_header_aux_b, 4, 1, ctx) == 0) {
		return 0;
	}

	if (g_file_version >= 0x10017) {
		int* p = &g_save_extra_field;
		while ((int) p < (int) &g_save_extra_field + 0x20) {
			if (ls_ReadVfsDataChecked(p, 4, 1, ctx) == 0) {
				return 0;
			}
			p = p + 1;
		}
	}

	for (i = 0; i < header_field; i = i + 1) {
		if (ls_ReadVfsDataChecked(&id, 2, 1, ctx) == 0) {
			return 0;
		}
		slot = (char*) ((int) g_slot_table + ((int) (unsigned short) id) * 0x21c);
		*(short*) slot = id;

		if (g_file_version >= 0x1003e) {
			if (ls_ReadVfsDataChecked(slot + 0x20c, 4, 1, ctx) == 0) {
				return 0;
			}
		}
		else {
			*(int*) (slot + 0x20c) = -1;
		}

		if (ls_ReadVfsDataChecked(slot + 2, 1, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 4, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 8, 1, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 9, 1, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0xa, 2, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0xc, 1, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0xd, 1, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x10, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x14, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x18, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1c, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x20, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x24, 4, 1, ctx) == 0) {
			return 0;
		}

		if (g_file_version >= 0x1003b) {
			if (ls_ReadVfsDataChecked(slot + 0x28, 2, 1, ctx) == 0) {
				return 0;
			}
			if (ls_ReadVfsDataChecked(slot + 0x2c, 4, 1, ctx) == 0) {
				return 0;
			}
		}

		if (ls_ReadVfsDataChecked(slot + 0x30, 0x10, 1, ctx) == 0) {
			return 0;
		}

		if (g_file_version >= 0x10031) {
			if (ls_ReadVfsDataChecked(slot + 0x40, 0x10, 1, ctx) == 0) {
				return 0;
			}
		}

		if (ls_ReadVfsDataChecked(slot + 0x50, 2, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x54, 4, 1, ctx) == 0) {
			return 0;
		}
#if !defined(REBREW_SERVER)
		*(int*) (slot + 0x54) += 0x59a;
#endif
		if (ls_ReadVfsDataChecked(slot + 0x58, 1, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x5c, 0x20, 1, ctx) == 0) {
			return 0;
		}

		if (g_file_version >= 0x10024) {
			if (ls_ReadVfsDataChecked(slot + 0x7c, 4, 1, ctx) == 0) {
				return 0;
			}
		}

		if (ls_ReadVfsDataChecked(slot + 0x80, 5, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x88, 0xa8, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x164, 1, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x165, 1, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x166, 1, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x167, 1, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x168, 1, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x169, 1, 1, ctx) == 0) {
			return 0;
		}

		*(int*) (slot + 0x16c) = 0;
		if (ls_ReadVfsDataChecked(slot + 0x16c, 4, 1, ctx) == 0) {
			return 0;
		}
		*(int*) (slot + 0x170) = 0;
		if (ls_ReadVfsDataChecked(slot + 0x170, 4, 1, ctx) == 0) {
			return 0;
		}

		if (g_file_version >= 0x10020) {
			if (ls_ReadVfsDataChecked(slot + 0x174, 4, 1, ctx) == 0) {
				return 0;
			}
		}
		else {
			if (ls_ReadVfsDataChecked(slot + 0x174, 2, 1, ctx) == 0) {
				return 0;
			}
		}

		*(int*) (slot + 0x17c) = 0;
		if (ls_ReadVfsDataChecked(slot + 0x17c, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x180, 1, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x18c, 4, 1, ctx) == 0) {
			return 0;
		}
#if !defined(REBREW_SERVER)
		*(int*) (slot + 0x18c) += 0x639;
#endif

		slot_ext_ptr = (int*) (slot + 0x190);
		if (ls_ReadVfsDataChecked(slot_ext_ptr, 4, 1, ctx) == 0) {
			return 0;
		}
		if (g_file_version < 0x1003e) {
			*slot_ext_ptr = 4;
		}

		if (ls_ReadVfsDataChecked(slot + 0x194, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x198, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x19c, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1a0, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1a4, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1a8, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1ac, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1b0, 1, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1b1, 1, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1b4, 0x10, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1c8, 4, 1, ctx) == 0) {
			return 0;
		}

		if (g_file_version >= 0x10049) {
			if (ls_ReadVfsDataChecked(slot + 0x1cc, 4, 1, ctx) == 0) {
				return 0;
			}
		}
		else {
			*(int*) (slot + 0x1cc) = 0;
		}

		if (ls_ReadVfsDataChecked(slot + 0x1d0, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1d4, 0x10, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1e4, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1e8, 4, 1, ctx) == 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked(slot + 0x1ec, 4, 1, ctx) == 0) {
			return 0;
		}

		if (g_file_version >= 0x1002a) {
			if (ls_ReadVfsDataChecked(slot + 0x1f0, 4, 1, ctx) == 0) {
				return 0;
			}
		}

		if (g_file_version >= 0x10021) {
			if (ls_ReadVfsDataChecked(slot + 0x1c5, 1, 1, ctx) == 0) {
				return 0;
			}
		}

		{
			int probe;
			if (ls_ReadVfsDataChecked(&probe, 4, 1, ctx) == 0) {
				return 0;
			}
			*(int*) (slot + 0x184) = probe;
		}

		if (g_file_version >= 0x10021) {
			if (ls_ReadVfsDataChecked(slot + 0x1f4, 0x18, 1, ctx) == 0) {
				return 0;
			}
		}

		if (g_file_version >= 0x10036) {
			if (ls_ReadVfsDataChecked(slot + 0x210, 4, 1, ctx) == 0) {
				return 0;
			}
			if (ls_ReadVfsDataChecked(slot + 0x214, 1, 1, ctx) == 0) {
				return 0;
			}
			if (ls_ReadVfsDataChecked(slot + 0x215, 1, 1, ctx) == 0) {
				return 0;
			}
			if (ls_ReadVfsDataChecked(slot + 0x216, 1, 1, ctx) == 0) {
				return 0;
			}
			if (ls_ReadVfsDataChecked(slot + 0x217, 1, 1, ctx) == 0) {
				return 0;
			}
			if (ls_ReadVfsDataChecked(slot + 0x218, 1, 1, ctx) == 0) {
				return 0;
			}
		}
	}

	(void) i;
	return 1;
}

#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "../../Units/vfs/vfs.h"
#include "../game/entity.h"

#include <stdlib.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"


extern int g_file_version; /* 0x1002d4ec */


/* ls_LoadTownData — two-phase save load.  Phase 1 walks the per-player
 * building-slot table (0x1009b768, stride 0x2a90): 4 header dwords, then
 * `count` (default 0x3e) records of 0x80 bytes.  Phase 2 walks the town
 * records (0x100a8c88, stride 0x2f4) with name/timestamps/flags/population/
 * resource pairs/political state.
 *
 * Byte-match note: RELOC, 1361/1361.  The
 * count-read is MSVC6-split: `&count` lands in the dead file-arg slot
 * (lea [esp+0x18]) while the phase-1 loop bound reloads the 0x3e copy at
 * [esp+0x10] — the read value is dead, exactly as in the reference build.
 * Phase 1 needs the derived-sub-pointer forms (`hdr = ptr - 8`,
 * `r = inner - 8`) so MSVC6 folds them back into single-base lea [ebx-8]/
 * [edi-8] addressing instead of normalizing extra induction bases; the
 * outer loop variable must be an `int` (signed `jl` bound compare).
 * Phase 2 needs a `while` loop (the `for` form miscompiles: stride 0x5e8
 * instead of 0x2f4, skipping records) with an `int` loop variable (signed
 * `jl` bound compare, as in the reference) and the reads anchored on the
 * derived `q = ptr2 - 8`; ptr2 then stays memory-resident (arg-slot
 * induction, `mov ebx,[esp+0x18]` reload at the head) matching the
 * reference.
 *
 * Phase 2 uses TWO bases, matching the reference: the head reads (through
 * ptr2+0x21) stay on `q = ptr2 - 8`, and everything from the second
 * 10x8 loop onward moves to `b = ptr2 - 0x48`, which the reference holds
 * in ebp for the rest of the record (`lea edi,[ebp+0xb4]`,
 * `lea eax,[ebp+0x104]`, `add ebp,0x2ec` for the final version-gated
 * read).  Anchoring that tail on `q` instead cost 25 matches and 19 bytes.
 *
 * Every phase-2 read from the second 10x8 loop onward used to sit 0x10 too
 * high (b+0xc4 where the reference reads b+0xb4, through b+0x2fc against
 * b+0x2ec).  That was a real read-offset bug, not just a byte mismatch: the
 * reference's record layout is contiguous, the first 10x8 loop ending at
 * b+0xb4 exactly where the second begins (`lea edi,[ebp+0xb4]` at
 * 0x10013dfb, `add ebp,0x2ec` at 0x10014025).  Corrected, 727 -> 729.
 *
 * What closed the remaining edi<->ebx role swap (729 -> RELOC): `inner` and
 * `i` were function-scope locals shared by the phase-1 and phase-2 loops.
 * That shared residency pinned phase 2's record base into ebx instead of the
 * reference's edi, shifting every instruction from 174 on.  Declaring a
 * separate `inner`/`i` pair inside each of the two loop bodies freed the
 * register and the tail fell out with the reference's roles: 729 -> 1290.
 * The seven phase-2 sub-loops then needed the reference's statement order,
 * counter zeroed before the pointer is set up and incremented before the
 * pointer advances, which the `do { } while (i < N)` form emits: 1290 ->
 * 1357.  The last four bytes were the first 10x8 loop's latch, fixed by
 * moving its `inner += 8` into the `for` third clause so the increment pairs
 * with the counter: 1357 -> 1361/1361, RELOC.
 *
 * All 46 `~~` operands resolved: the only call target is 0x10012440
 * (ls_ReadVfsDataChecked, db/server.dll_functions.csv) and the only global
 * is 0x1002d4ec (g_file_version, rebrew_globals.h:18). */

int __cdecl ls_LoadTownData(void* file)
{
	int count; extern unsigned char g_city_records[];
	int ptr;
	int ptr2;
	void* ctx;

	ctx = (void*) file;
	count = 0x3e;
	if (g_file_version >= 0x10048) {
		if (!ls_ReadVfsDataChecked(&count, 4, 1, ctx)) {
			return 0;
		}
	}

	for (ptr = (int) g_entity_end + 8; ptr < (int) g_entity_end + 0xd4d8; ptr += 0x2a90) {
		char* inner;
		int i;
		char* hdr = (char*) (ptr - 8);
		if (!ls_ReadVfsDataChecked(hdr, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(hdr + 4, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(hdr + 8, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(hdr + 0xc, 4, 1, ctx)) {
			return 0;
		}

		i = 0;
		if (count > 0) {
			inner = (char*) (ptr + 0x10);
			do {
				char* r = inner - 8;
				if (!ls_ReadVfsDataChecked(r, 2, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 4, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 8, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0xc, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x20, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x24, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x30, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x34, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x38, 4, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x3c, 2, 1, ctx)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(r + 0x2c, 4, 1, ctx)) {
					return 0;
				}
				i++;
				inner += 0x80;
			} while (i < count);
		}

	}

	ptr2 = (int) g_city_records + 0x48;
	while (ptr2 < (int) g_city_records + 0xc18) {
		char* q = (char*) (ptr2 - 8);
		char* b = (char*) (ptr2 - 0x48);
		char* inner;
		int i;

		if (!ls_ReadVfsDataChecked(q - 0x40, 0x20, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q, 8, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 8, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0xc, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x10, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x14, 2, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x18, 8, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x20, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(q + 0x21, 1, 1, ctx)) {
			return 0;
		}

		inner = (char*) (ptr2 + 0x1c);
		for (i = 0; i < 10; i++, inner += 8) {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, ctx)) {
				return 0;
			}
		}

		i = 0;
		inner = b + 0xb4;
		do {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, ctx)) {
				return 0;
			}
			i++;
			inner += 8;
		} while (i < 10);

		if (!ls_ReadVfsDataChecked(b + 0x104, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x105, 1, 1, ctx)) {
			return 0;
		}

		i = 0;
		inner = b + 0x108;
		do {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, ctx)) {
				return 0;
			}
			i++;
			inner += 4;
		} while (i < 4);

		i = 0;
		inner = b + 0x118;
		do {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, ctx)) {
				return 0;
			}
			i++;
			inner += 4;
		} while (i < 4);

		if (!ls_ReadVfsDataChecked(b + 0x128, 4, 1, ctx)) {
			return 0;
		}

		i = 0;
		inner = b + 0x12c;
		do {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, ctx)) {
				return 0;
			}
			i++;
			inner++;
		} while (i < 0xb);

		if (!ls_ReadVfsDataChecked(b + 0x137, 1, 1, ctx)) {
			return 0;
		}

		i = 0;
		inner = b + 0x138;
		do {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, ctx)) {
				return 0;
			}
			i++;
			inner++;
		} while (i < 7);

		if (!ls_ReadVfsDataChecked(b + 0x13f, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x140, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x141, 1, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x142, 1, 1, ctx)) {
			return 0;
		}

		i = 0;
		inner = b + 0x144;
		do {
			if (!ls_ReadVfsDataChecked(inner, 0x12, 1, ctx)) {
				return 0;
			}
			i++;
			inner += 0x12;
		} while (i < 8);

		if (!ls_ReadVfsDataChecked(b + 0x1d4, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x1d8, 4, 1, ctx)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(b + 0x1dc, 0xd0, 1, ctx)) {
			return 0;
		}

		if (g_file_version >= 0x10037) {
			if (!ls_ReadVfsDataChecked(b + 0x2ec, 8, 1, ctx)) {
				return 0;
			}
		}

		ptr2 += 0x2f4;
	}

	return 1;
}

/* Client-only: reads the two 768x768 relationship matrices of a savegame
 * (256 or 512 rows in older versions).  No server function calls it, so
 * /OPT:REF discards it; its absolute fixups still count toward LINK's .reloc
 * reservation. */
int __cdecl ls_LoadRelationships(void* stream_ctx)
{
	extern int g_file_version;
	extern char g_relationship_matrix_primary[];
	extern char g_relationship_matrix_secondary[];
	int n;
	int i;
	int j;

	if (g_file_version < 0x1003a) {
		n = 0x100;
	}
	else {
		n = g_file_version < 0x10042 ? 0x200 : 0x300;
	}
	for (j = 0; j < n; j++) {
		for (i = 0; i < n; i++) {
			if (ls_ReadVfsDataChecked(&g_relationship_matrix_primary[j * 0x300 + i], 1, 1, stream_ctx) == 0) {
				return 0;
			}
		}
	}
	if (g_file_version >= 0x10036) {
		for (j = 0; j < n; j++) {
			for (i = 0; i < n; i++) {
				if (ls_ReadVfsDataChecked(&g_relationship_matrix_secondary[j * 0x300 + i], 1, 1, stream_ctx) == 0) {
					return 0;
				}
			}
		}
	}
	return 1;
}


// RELOC, 491/491. The entity loop indexes from the record base (rec = entity_cursor -
// 0x170, positive offsets) so msvc6 keeps the address CSE out of the
// null-check; with entity_cursor-relative negative offsets it hoists `lea [esi-4]` above
// the `je` and shifts every following byte (187/491).
// The list walks need both the target'record_cursor copy-propagation and its eax/ecx
// roles, and those are two separate decisions. Guarding on node'record_cursor successor
// then walking a second cursor (nxt) that is seeded from node and written
// back at the end gives `mov ecx,eax` + `mov eax,[ecx+0x3f]`; walking node
// itself gives the same shape with the registers swapped (461/491), and the
// original do/while over nxt copy-propagates into `mov eax,[eax+0x3f]`
// (488/491). Probed in .scratch/pv3/w3-w6.c.

unsigned int ls_ID2Ptr(void)
{
	int v1;
	int v2;
	int v3;
	unsigned char* entity_cursor;
	int* id_cursor;
	int i;
	char* record_cursor;
	unsigned int idx;
	void* node;
	void* nxt;
	unsigned char* rec;

	g_entity_table_end = gm_LookupEntityRecordById(g_entity_table_end);
	if (g_entity_table_end == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c", 0x1016,
		    "ls_ID2Ptr(): Stadtspieler Id not found", 1);
		return 0;
	}
	g_active_player_count = (int) gm_StartFilteredEntitySearch(1, 5, 0xa);
	if (g_file_version >= 0x10017) {
		for (id_cursor = (int*) &g_save_extra_field; (int) id_cursor < (int) ((char*) &g_save_extra_field + 0x20); id_cursor++) {
			*id_cursor = gm_LookupEntityRecordById(*id_cursor);
		}
	}
	for (entity_cursor = (unsigned char*) g_slot_table + 0x170; (int) entity_cursor < (int) g_slot_table + 0x65570; entity_cursor += 0x21c) {
		rec = entity_cursor - 0x170;
		if (*(unsigned short*) rec == 0xffff) {
			continue;
		}
		if (*(int*) (rec + 0x16c) == -1) {
			*(int*) (rec + 0x16c) = 0;
		} else {
			gm_ResolveEntityById((void**) (rec + 0x16c), 0, 0, *(int*) (rec + 0x16c));
		}
		if (*(int*) (rec + 0x170) == -1) {
			*(int*) (rec + 0x170) = 0;
		} else {
			gm_ResolveEntityById((void**) (rec + 0x170), 0, 0, *(int*) (rec + 0x170));
		}
	}
	for (i = 0; i < g_query_limit; i++) {
		record_cursor = (char*) g_query_base + i * 0x43;
		idx = *(unsigned short*) record_cursor;
		if (*(char*) (g_item_def_table + idx * 64 + idx) == 0x1d) {
			*(int*) (record_cursor + 0x24) = 0;
		}
		if (*(int*) (record_cursor + 6) != -1) {
			if (!gm_ResolveEntityById(&v1, &v2, &v3, *(int*) (record_cursor + 6))) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c", 0x1050,
				    "ls_ID2Ptr(): Houston, wir haben ein Problem...", 1);
			} else if (v1 != 0) {
				node = *(void**) (v1 + 0x5d);
				if (node == 0) {
					*(void**) (v1 + 0x5d) = record_cursor;
				} else {
					if (*(void**) ((char*) node + 0x3f) != 0) {
						nxt = node;
						do {
							nxt = *(void**) ((char*) nxt + 0x3f);
						} while (*(void**) ((char*) nxt + 0x3f) != 0);
						node = nxt;
					}
					*(void**) ((char*) node + 0x3f) = record_cursor;
				}
			} else if (v2 != 0) {
				node = *(void**) (v2 + 0x14);
				if (node == 0) {
					*(void**) (v2 + 0x14) = record_cursor;
				} else {
					if (*(void**) ((char*) node + 0x3f) != 0) {
						nxt = node;
						do {
							nxt = *(void**) ((char*) nxt + 0x3f);
						} while (*(void**) ((char*) nxt + 0x3f) != 0);
						node = nxt;
					}
					*(void**) ((char*) node + 0x3f) = record_cursor;
				}
			} else {
				node = *(void**) (v3 + 0x178);
				if (node == 0) {
					*(void**) (v3 + 0x178) = record_cursor;
				} else {
					if (*(void**) ((char*) node + 0x3f) != 0) {
						nxt = node;
						do {
							nxt = *(void**) ((char*) nxt + 0x3f);
						} while (*(void**) ((char*) nxt + 0x3f) != 0);
						node = nxt;
					}
					*(void**) ((char*) node + 0x3f) = record_cursor;
				}
			}
		}
	}
	gm_EntitySetField();
	return 1;
}

/* Canonical definitions live in Units/m_alloc/m_alloc2.c. */
extern char g_stream_pool[1]; /* 0x10034670 */
extern int g_stream_count; /* 0x10034678 */
/* Canonical definition lives in game/spiel_c/gm_NextEntityQueryMatch.c. */
extern int g_query_filter_owner;


int srv_RecvGame(void)
{
	void* file_handle;
	int load_status;
	char* entity_state_ptr;

	file_handle = vfs_OpenStream((unsigned char*) g_download_buffer, g_download_total_size, s_gzip_mode_rb); /* shortcut: integer buffer view; type after download-state ownership review. */
	if (file_handle == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x11fe,
			"ls_RecvGame(): Can\'t open File",
			1
		);
		m_FreeTracked((void*) g_recv_game_buffer);
		g_recv_game_buffer = 0;
		return 0;
	}
	ls_LoadSavegameHeader(file_handle, (char*) g_save_info);
	if (((g_save_info[1] & 2) == 0) || (0x1005a < g_save_info[0]) || (g_save_info[0] < 0x10013)) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x120a,
			"srv_RecvGame(): Can\'t load Counter",
			1
		);
		CloseVfsStream(file_handle);
		m_FreeTracked((void*) g_recv_game_buffer);
		g_recv_game_buffer = 0;
		return 0;
	}
	*(int*) &g_entity_table_end = 0;
	if (ls_ReadVfsDataChecked((void*) &g_next_object_id, 4, 1, file_handle) == 0
		|| ls_ReadVfsDataChecked((void*) &g_chain_id_start, 4, 1, file_handle) == 0
		|| ls_ReadVfsDataChecked((void*) &g_current_year, 0xe, 1, file_handle) == 0
		|| ls_ReadVfsDataChecked((void*) &g_current_season, 1, 1, file_handle) == 0
		|| ls_ReadVfsDataChecked((void*) &g_entity_table_end, 4, 1, file_handle) == 0
		|| ls_ReadVfsDataChecked((void*) &g_next_family_index, 4, 1, file_handle) == 0
		|| ls_ReadVfsDataChecked((void*) &gm_CurrentHumanFamilyCount, 4, 1, file_handle) == 0
		|| ls_ReadVfsDataChecked((void*) &g_citizen_count, 4, 1, file_handle) == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x121e,
			"srv_RecvGame(): Can\'t load Counter",
			1
		);
		CloseVfsStream(file_handle);
		m_FreeTracked((void*) g_recv_game_buffer);
		g_recv_game_buffer = 0;
		return 0;
	}
	ls_ReadVfsDataChecked((void*) &g_saved_dynasty_field, 4, 1, file_handle);
	ls_ReadVfsDataChecked((void*) &g_save_session_state, 0x18, 1, file_handle);
	if (g_file_version >= 0x10030) {
		ls_ReadVfsDataChecked((void*) &g_entity_id_counter, 4, 1, file_handle);
	}
	if (g_file_version >= 0x1003d) {
		ls_ReadVfsDataChecked((void*) &g_sequence_counter, 4, 1, file_handle);
	} else {
		g_sequence_counter = 1000000;
	}
	load_status = ls_LoadExistingEntities(file_handle);
	if (load_status == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x1234,
			"srv_RecvGame(): Can\'t load Objects",
			1
		);
		CloseVfsStream(file_handle);
		m_FreeTracked((void*) g_recv_game_buffer);
		g_recv_game_buffer = 0;
		return 0;
	}
	load_status = ls_LoadBuildingEntityState(file_handle);
	if (load_status == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x123d,
			"LoadGame(): Can\'t load Buildings",
			1
		);
		CloseVfsStream(file_handle);
		m_FreeTracked((void*) g_recv_game_buffer);
		g_recv_game_buffer = 0;
		return 0;
	}
	load_status = ls_LoadDynamicEntities(file_handle);
	if (load_status == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x1246,
			"srv_RecvGame(): Can\'t load Dynasties",
			1
		);
		CloseVfsStream(file_handle);
		m_FreeTracked((void*) g_recv_game_buffer);
		g_recv_game_buffer = 0;
		return 0;
	}
	load_status = ls_LoadEntities(file_handle);
	if (load_status == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x124f,
			"srv_RecvGame(): Can\'t load Players",
			1
		);
		CloseVfsStream(file_handle);
		m_FreeTracked((void*) g_recv_game_buffer);
		g_recv_game_buffer = 0;
		return 0;
	}
	entity_state_ptr = (char*) &g_entity_state_base;
	do {
		if (*(unsigned short*) (entity_state_ptr - 2) != 0xffff &&
			*entity_state_ptr == '\x06') {
			*entity_state_ptr = '\x05';
		}
		entity_state_ptr = entity_state_ptr + 0x21c;
	} while ((int) entity_state_ptr < (int) ((char*) &g_entity_state_base + 0x65400));
	load_status = ls_LoadTownData(file_handle);
	if (load_status == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x125b,
			"srv_RecvGame(): Can\'t load Towns",
			1
		);
		CloseVfsStream(file_handle);
		m_FreeTracked((void*) g_recv_game_buffer);
		g_recv_game_buffer = 0;
		return 0;
	}
	if (g_file_version >= 0x10045) {
		load_status = amt_fio_LoadAemter(file_handle, g_file_version);
		if (load_status == 0) {
			LogMessageInternal(
				"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
				0x1266,
				"srv_RecvGame(): Can\'t load Aemter",
				1
			);
			CloseVfsStream(file_handle);
			return 0;
		}
	}
	load_status = ls_ID2Ptr();
	if (load_status == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x126f,
			"srv_RecvGame(): Can\'t convert IDs to Pointers",
			1
		);
		CloseVfsStream(file_handle);
		m_FreeTracked((void*) g_recv_game_buffer);
		g_recv_game_buffer = 0;
		return 0;
	}
	CloseVfsStream(file_handle);
	return 1;
}
unsigned char _dpad_1002d444[168];
unsigned char _dpad_10035a10[414352];
