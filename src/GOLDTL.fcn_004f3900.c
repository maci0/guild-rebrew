// FUNCTION: GOLDTL 0x004f3900
// SIZE: 685
/* Save counterpart of the graveyard loader (GOLDTL 0x4f3bb0,
 * loadsave_dump1.c); twin of GOLD 0x4f17f0. */

int __cdecl fcn_00430910(void* buf, int elementSize, int elementCount, void* streamCtx);
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

int __cdecl fcn_004f3900(void* stream_ctx, unsigned char* field)
{
	GraveyardSlot* slot;
	char* entry;
	char* worker;
	int i;

	slot = *(GraveyardSlot**) (field + 0x65);
	if (slot == 0) {
		return 0;
	}
	if (!fcn_00430910(slot, 4, 1, stream_ctx)) {
		return 0;
	}
	if (!fcn_00430910(&slot->type, 4, 1, stream_ctx)) {
		return 0;
	}
	if (!fcn_00430910(&slot->b18, 1, 1, stream_ctx)) {
		return 0;
	}
	if (!fcn_00430910(&slot->b19, 1, 1, stream_ctx)) {
		return 0;
	}
	if (!fcn_00430910(&slot->b1a, 1, 1, stream_ctx)) {
		return 0;
	}
	if (!fcn_00430910(&slot->b1b, 1, 1, stream_ctx)) {
		return 0;
	}
	entry = (char*) slot->entry_table;
	for (i = 0; i < g_field_entry_count[slot->type]; i++, entry += 0x44) {
		if (!fcn_00430910(entry, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430910(entry + 4, 0x10, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430910(entry + 0x14, 0x10, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430910(entry + 0x24, 5, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430910(entry + 0x2c, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430910(entry + 0x30, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430910(entry + 0x34, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430910(entry + 0x38, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430910(entry + 0x3c, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430910(entry + 0x40, 4, 1, stream_ctx)) {
			return 0;
		}
	}
	worker = (char*) slot->worker;
	for (i = 0; i < g_field_worker_count[slot->type]; i++, worker += 0x14) {
		int sid;

		if (!fcn_00430910(worker, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430910(worker + 4, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430910(worker + 8, 2, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430910(worker + 0xa, 2, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430910(worker + 0xc, 1, 1, stream_ctx)) {
			return 0;
		}
		sid = (*(char**) (worker + 0x10) - (char*) slot->entry_table) / 0x44;
		if (!fcn_00430910(&sid, 4, 1, stream_ctx)) {
			return 0;
		}
	}
	return 1;
}
