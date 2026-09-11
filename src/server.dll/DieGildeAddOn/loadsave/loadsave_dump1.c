/* loadsave TU part 1 — ls_LoadGraveyardData + ls_InitNewDynastyEntity. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10012000

#include <string.h>

int __cdecl gv_AllocField(unsigned char* field);
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_field_worker_count[];
extern int g_field_entry_count[];

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
 * (0x10012440), one to gv_AllocField (0x100109d0), and the globals
 * g_field_entry_count (x2) and g_field_worker_count (x2), all confirmed against
 * db/server.dll_functions.csv and the target disassembly. */

int __cdecl ls_LoadGraveyardData(void* stream_ctx, unsigned char* field, int c, int d)
{
	GraveyardSlot* slot;
	char* entry;
	char* worker;
	int counter;
	int i;
	int n;

	slot = (GraveyardSlot*) gv_AllocField(field);
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

