/* loadsave TU part 1 — ls_LoadGraveyardData + ls_InitNewDynastyEntity. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10012000

#include <string.h>

int __cdecl AllocGraveyardField(unsigned char* field);
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_1002575c[];
extern int g_1002576c[];

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
 * then the slot-entry table (g_1002576c[type] entries of 0x44 bytes) and
 * the worker table (g_1002575c[type] entries of 0x14 bytes).  Each entry's
 * worker slot stores a pointer to its 0x44-byte entry in the entry table.
 *
 * NOTE: the stream also reads the 4-byte slot->type (0x1001203e) between
 * the id and the b18/b19/b1a/b1b bytes — the earlier formulation skipped
 * that read.  Remaining byte deltas are MSVC6 register-role blockers
 * (docs/msvc6-allocator.md Findings 12/49); the function is PROVEN. */

int __cdecl ls_LoadGraveyardData(void* stream_ctx, unsigned char* field, int c, int d)
{
	GraveyardSlot* slot;
	char* entry;
	char* worker;
	int counter;

	slot = (GraveyardSlot*) AllocGraveyardField(field);
	if (slot == 0) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(slot, 4, 1, stream_ctx)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked((int*) ((char*) slot + 4), 4, 1, stream_ctx)) {
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
	for (counter = 0; counter < g_1002576c[slot->type]; counter++, entry += 0x44) {
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
	}
	worker = (char*) slot->worker;
	for (counter = 0; counter < g_1002575c[slot->type]; counter++, worker += 0x14) {
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
		if (!ls_ReadVfsDataChecked(&d, 4, 1, stream_ctx)) {
			return 0;
		}
		*(void**) (worker + 0x10) = (void*) &((int*) slot->entry_table)[counter * 0x11];
	}
	return 1;
}

int __cdecl ReadVfsData(void*, int, int, void*);

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx)
{
	/* ReadVfsData wrapper: nonzero on success (unsigned > 0 carry idiom). */
	return (unsigned int) ReadVfsData(outBuffer, elementSize, elementCount, streamCtx) > 0;
}
