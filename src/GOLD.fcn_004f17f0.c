// FUNCTION: GOLD 0x004f17f0
// SIZE: 685
/* Twin of GOLDTL 0x4f3bb0 (loadsave_dump1.c): GOLD takes the slot from
 * field+0x65 instead of allocating it, and passes each worker's entry index
 * computed from its entry pointer instead of reading an index into a pointer. */

int __cdecl fcn_00430e30(void* buf, int elementSize, int elementCount, void* streamCtx);
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

int __cdecl fcn_004f17f0(void* stream_ctx, unsigned char* field, int c, int d)
{
	GraveyardSlot* slot;
	char* entry;
	char* worker;
	int counter;
	int i;
	int n;

	slot = *(GraveyardSlot**) (field + 0x65);
	if (slot == 0) {
		return 0;
	}
	if (!fcn_00430e30(slot, 4, 1, stream_ctx)) {
		return 0;
	}
	if (!fcn_00430e30(&slot->type, 4, 1, stream_ctx)) {
		return 0;
	}
	if (!fcn_00430e30(&slot->b18, 1, 1, stream_ctx)) {
		return 0;
	}
	if (!fcn_00430e30(&slot->b19, 1, 1, stream_ctx)) {
		return 0;
	}
	if (!fcn_00430e30(&slot->b1a, 1, 1, stream_ctx)) {
		return 0;
	}
	if (!fcn_00430e30(&slot->b1b, 1, 1, stream_ctx)) {
		return 0;
	}
	entry = (char*) slot->entry_table;
	n = g_field_entry_count[slot->type];
	counter = 0;
	while (counter < n) {
		if (!fcn_00430e30(entry, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430e30(entry + 4, 0x10, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430e30(entry + 0x14, 0x10, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430e30(entry + 0x24, 5, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430e30(entry + 0x2c, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430e30(entry + 0x30, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430e30(entry + 0x34, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430e30(entry + 0x38, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430e30(entry + 0x3c, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430e30(entry + 0x40, 4, 1, stream_ctx)) {
			return 0;
		}
		n = g_field_entry_count[slot->type];
		counter++;
		entry += 0x44;
	}
	i = 0;
	worker = (char*) slot->worker;
	while (i < g_field_worker_count[slot->type]) {
		int sid;

		if (!fcn_00430e30(worker, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430e30(worker + 4, 4, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430e30(worker + 8, 2, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430e30(worker + 0xa, 2, 1, stream_ctx)) {
			return 0;
		}
		if (!fcn_00430e30(worker + 0xc, 1, 1, stream_ctx)) {
			return 0;
		}
		sid = (*(char**) (worker + 0x10) - (char*) slot->entry_table) / 0x44;
		if (!fcn_00430e30(&sid, 4, 1, stream_ctx)) {
			return 0;
		}
		i++;
		worker += 0x14;
	}
	return 1;
}

