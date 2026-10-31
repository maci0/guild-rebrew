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
		return 0;
	}
	if (*(unsigned short*) owner == 0xffff) {
		return 0;
	}
	if (*(unsigned char*) (owner + 0x168) != 0) {
		return 0;
	}
	want = arg[4];
	slot = (SlotRec*) 0x9a9220;
	for (i = 0; (unsigned char*) slot < (unsigned char*) 0x9a94f0; slot++, i++) {
		if (slot->type == want) {
			break;
		}
	}
	if (i >= 0x1e) {
		return 0;
	}
	c = arg[6];
	if (slot->tag != c) {
		return 0;
	}
	if (arg[5] == 0xff) {
		if (slot->id != -1) {
			return 0;
		}
		if (slot->state != 3) {
			return 0;
		}
		if (slot->count >= 4) {
			return 0;
		}
		*(unsigned char*) (owner + 0x168) = c;
		slot->count++;
		return 1;
	}
	want = arg[5];
	other = (SlotRec*) 0x9a9220;
	for (j = 0; (unsigned char*) other < (unsigned char*) 0x9a94f0; other++, j++) {
		if (other->type == want) {
			break;
		}
	}
	if (j >= 0x1e) {
		return 0;
	}
	if (slot->tag != other->tag) {
		return 0;
	}
	rec = ((TypeRec*) 0x68da68)[slot->tag];
	if (rec.f0 != c) {
		return 0;
	}
	if (rec.f4 != 0) {
		return 0;
	}
	if (slot->id != -1) {
		return 0;
	}
	if (slot->state != 3) {
		return 0;
	}
	if (slot->count >= 4) {
		return 0;
	}
	if (other->id != -1) {
		return 0;
	}
	if (other->count >= 4) {
		return 0;
	}
	*(unsigned char*) (owner + 0x168) = c;
	slot->count++;
	other->count++;
	return 1;
}
