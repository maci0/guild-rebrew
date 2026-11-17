#include "client_data.h"
extern char g_68da68[];
/* Slot pairing probe: matches the caller argument against two entries of the
 * 24-byte slot table at 0x9a9220 and a 24-byte type record at 0x68da68, then
 * bumps the per-entry counters. */

typedef struct SlotRec {
	unsigned char type;
	char pad_001[3];
	int id;
	unsigned char tag;
	char pad_009[3];
	int count;
	unsigned char state;
	char pad_011[7];
} SlotRec; /* 0x18 */

typedef struct TypeRec {
	int f0;
	int f1;
	int f2;
	int f3;
	int f4;
	int f5;
} TypeRec; /* 0x18 */

extern void* __cdecl gm_LookupEntityRecordById(int id);

/* ADDRESS: GOLDTL 0x004e7ff0 */
int __cdecl fcn_004e7ff0(unsigned char* arg)
{
	unsigned char* owner;
	SlotRec* slot;
	SlotRec* other;
	TypeRec rec;
	unsigned char c;
	unsigned char want;
	int i;
	int j;

	owner = (unsigned char*) gm_LookupEntityRecordById(*(int*) arg);
	if (owner == 0) {
		goto fail;
	}
	if (*(unsigned short*) owner == 0xffff) {
		goto fail;
	}
	if (*(unsigned char*) (owner + 0x168) != 0) {
		goto fail;
	}
	want = arg[4];
	slot = (SlotRec*) g_9a9220;
	for (i = 0; (int) slot < (int) g_9a9220 + 0x2d0; slot++, i++) {
		if (slot->type == want) {
			goto found;
		}
	}
fail:
	return 0;
found:
	if (i >= 0x1e) {
		goto fail;
	}
	c = arg[6];
	if (((SlotRec*) g_9a9220)[i].tag != c) {
		goto fail;
	}
	if (arg[5] == 0xff) {
		if (((SlotRec*) g_9a9220)[i].id != -1) {
			goto fail;
		}
		if (((SlotRec*) g_9a9220)[i].state != 3) {
			goto fail;
		}
		if (((SlotRec*) g_9a9220)[i].count >= 4) {
			goto fail;
		}
		*(unsigned char*) (owner + 0x168) = c;
		((SlotRec*) g_9a9220)[i].count++;
		return 1;
	}
	want = arg[5];
	other = (SlotRec*) g_9a9220;
	for (j = 0; (int) other < (int) g_9a9220 + 0x2d0; other++, j++) {
		if (((SlotRec*) g_9a9220)[j].type == want) {
			goto found2;
		}
	}
	return 0;
found2:
	if (j >= 0x1e) {
		goto fail;
	}
	if (((SlotRec*) g_9a9220)[i].tag != ((SlotRec*) g_9a9220)[j].tag) {
		goto fail;
	}
	rec = ((TypeRec*) g_68da68)[((SlotRec*) g_9a9220)[i].tag];
	if (rec.f0 != c) {
		goto fail;
	}
	if (rec.f4 == 0) {
		goto fail;
	}
	if (((SlotRec*) g_9a9220)[i].id != -1) {
		goto fail;
	}
	if (((SlotRec*) g_9a9220)[i].state != 3) {
		goto fail;
	}
	if (((SlotRec*) g_9a9220)[i].count >= 4) {
		goto fail;
	}
	if (((SlotRec*) g_9a9220)[j].id != -1) {
		goto fail;
	}
	if (((SlotRec*) g_9a9220)[j].count >= 4) {
		goto fail;
	}
	*(unsigned char*) (owner + 0x168) = c;
	((SlotRec*) g_9a9220)[i].count++;
	((SlotRec*) g_9a9220)[j].count++;
	return 1;
}
