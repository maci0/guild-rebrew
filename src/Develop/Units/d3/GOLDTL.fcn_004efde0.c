/*
 * Per frame update of the eight "kugel" sprite slots.
 *
 * Every live slot falls with the frame step, is clamped against the ground
 * height and then advances its three effect states. A state entry reports
 * through its sphere test when it still runs; the matching object handle is
 * created on demand and positioned from the entry. Finished entries count
 * up and clear the slot flags once all three are done.
 *
 * Map entry layout: the id sits at +0x00, flags at +0x04, the position at
 * +0x08, the selector at +0x14, three effect entries of 0x68 bytes from
 * +0x18, an object handle at +0x150, a callback at +0x168 and the data
 * pointer at +0x16c.
 */

#define MIN(a, b) ((a) > (b) ? (b) : (a))

typedef struct Sefde0Entry {
	int f00[12];
	int obj;
	int f34[10];
	int state;
	int f60[2];
} Sefde0Entry;

typedef struct Sefde0Slot {
	int id;
	int flags;
	float x;
	float y;
	float z;
	int mode;
	Sefde0Entry entry[3];
	int handle;
	int f154[5];
	int (*callback)(int);
	int* data;
} Sefde0Slot;

int __cdecl fcn_00500d20(char*, char*);
void __cdecl fcn_004432d0(int, int);
int __cdecl fcn_005e9870(Sefde0Entry*);
int __cdecl fcn_005e9da0(Sefde0Entry*);
char* __cdecl fcn_00442910(int, float*, float*, char*);
void __cdecl d3_DestroyObject(void*);
void __cdecl fcn_00438b40(char*, int*);
void __cdecl fcn_004efd70(int);
void __cdecl fcn_004f01c0(int, int, int, int*);

/* ADDRESS: GOLDTL 0x004efde0 */
void __cdecl fcn_004efde0(void)
{
	Sefde0Slot* slot;
	Sefde0Entry* entry;
	char* obj;
	int save;
	int idx;
	int count;
	int i;
	int flags;
	int state;
	int runs;
	float step;
	float x;
	float y;
	float z;

	save = *(int*) 0x6b8010;
	idx = fcn_00500d20((char*) 0x772fe8, (char*) 0x7f4c00);
	if (idx < 0) {
		idx = 0;
	}
	step = (float) idx * *(float*) 0x6652c4 * *(float*) 0x662a3c;
	*(int*) 0x772fe8 = *(int*) 0x7f4c00;
	*(int*) 0x772fec = *(int*) 0x7f4c04;
	*(int*) 0x772ff0 = *(int*) 0x7f4c08;
	*(short*) 0x772ff4 = *(short*) 0x7f4c0c;
	fcn_004432d0(0, 1);
	count = 0;
	slot = (Sefde0Slot*) 0x7731b8;
	for (;;) {
		if (slot->id != -1) {
			x = step + slot->x;
			slot->x = x;
			y = step + slot->y;
			slot->y = y;
			z = step + slot->z;
			slot->z = z;
			slot->x = MIN(x, *(float*) 0x6628a0);
			slot->y = MIN(y, *(float*) 0x6628a0);
			slot->z = MIN(z, *(float*) 0x6628a0);
			if (slot->flags & 2) {
				i = 0;
				count = 0;
				entry = slot->entry;
				while (i < 3) {
					state = entry->state;
					if (state == 0) {
						count++;
						if (count >= 3) {
							slot->flags &= ~3;
							if (slot->flags & 4) {
								fcn_004efd70(slot->id);
							}
						}
					} else if (state == 1) {
						if (slot->mode != 0) {
							runs = fcn_005e9da0(entry);
						} else {
							runs = fcn_005e9870(entry);
						}
						if (runs != 0) {
							obj = *(char**) (0x773314 + (idx + i) * 4);
							if (obj == 0) {
								obj = fcn_00442910(0, (float*) 0x662d70, (float*) 0x662d80, (char*) 0x68ff14);
								*(char**) (0x773314 + (idx + i) * 4) = obj;
								*(unsigned char*) (obj + 0x215) |= 1;
								*(unsigned char*) (obj + 0x216) |= 3;
								*(unsigned char*) (obj + 0x215) &= ~2;
							}
							fcn_00438b40(obj, (int*) (entry + 1));
						}
						if (entry->state == 3) {
							obj = *(char**) (0x773314 + (idx + i) * 4);
							if (obj != 0) {
								d3_DestroyObject(obj);
								*(char**) (0x773314 + (idx + i) * 4) = 0;
							}
							if (slot->data != 0) {
								*slot->data = i;
							}
							*(int*) ((char*) slot->data + i * 0x10 + 8) = -1;
							if (slot->callback != 0) {
								slot->callback((int) slot->data);
							}
							entry->state = 0;
							*(int*) (0x773308 + (idx + i) * 4) = 0;
						} else if (entry->state == 2) {
							count++;
							obj = *(char**) (0x773314 + (idx + i) * 4);
							if (obj != 0) {
								d3_DestroyObject(obj);
								*(char**) (0x773314 + (idx + i) * 4) = 0;
							}
							fcn_004f01c0(slot->flags & 1, slot->id, (int) entry, slot->data);
							if (slot->data != 0) {
								*slot->data = i;
							}
							if (slot->callback != 0) {
								slot->callback((int) slot->data);
							}
							entry->state = 0;
							*(int*) (0x773308 + (idx + i) * 4) = 0;
							*slot->data = -1;
						}
					}
					i++;
					entry++;
				}
				if (count >= 3) {
					slot->flags &= ~3;
					if (slot->flags & 4) {
						fcn_004efd70(slot->id);
					}
				}
			} else if (slot->flags & 4) {
				fcn_004efd70(slot->id);
			}
		}
		idx += 0x5c;
		slot++;
		if (idx >= 0x2e0) {
			break;
		}
	}
	fcn_004432d0(save, 1);
}
