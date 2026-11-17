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
#include "Develop/DieGildeAddOn/game/game_data.h"
#define MIN(a, b) ((a) < (b) ? (a) : (b))
/* Current slot: idx counts ints, 0x5c per 0x170-byte slot of the table at g_7731b8. */
#define SLOT ((Sefde0Slot*) ((char*) g_7731b8 + idx * 4))

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
	int active[3];
	char* objects[3];
	int (*callback)(int);
	int* data;
} Sefde0Slot;

extern int g_7731b8[];
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
	int* statep;
	char* obj;
	int save;
	int idx;
	int count;
	int i;
	int flags;
	int state;
	float step;
	float x;
	float y;
	float z;


	idx = fcn_00500d20((char*) 0x772fe8, (char*) 0x7f4c00);
	if (idx < 0) {
		idx = 0;
	}
	step = (float) idx * *(float*) 0x6652c4;
	*(int*) 0x772fe8 = *(int*) 0x7f4c00;
	*(int*) 0x772fec = *(int*) 0x7f4c04;
	*(int*) 0x772ff0 = *(int*) 0x7f4c08;
	*(short*) 0x772ff4 = *(short*) 0x7f4c0c;
	step = step * *(float*) 0x662a3c;
	save = g_6b8010; fcn_004432d0(0, 1);
	count = 0; idx = 0;
	for (;;) {
		if (SLOT->id != -1) {
			x = step + SLOT->x;
			SLOT->x = x;
			y = step + SLOT->y;
			SLOT->y = y;
			z = step + SLOT->z;
			SLOT->z = z;
			SLOT->x = MIN(x, 1.0f);
			SLOT->y = MIN(y, 1.0f);
			SLOT->z = MIN(z, 1.0f);
			if (SLOT->flags & 2) {
				i = 0;
				count = 0;
				statep = &SLOT->entry[0].state;
				while (i < 3) {
					state = *statep;
					if (state == 0) {
						count++;
						if (count >= 3) {
							SLOT->flags &= ~3;
							if (SLOT->flags & 4) {
								fcn_004efd70(SLOT->id);
							}
						}
					} else if (state == 1) {
						int runs;
						if (SLOT->mode == 0) {
							runs = fcn_005e9870((Sefde0Entry*) (statep - 0x17));
						} else {
							runs = fcn_005e9da0((Sefde0Entry*) (statep - 0x17));
						}
						if (runs != 0) {
							obj = ((char*) g_7731b8[idx + i + 0x57]);
							if (obj == 0) {
								obj = fcn_00442910(0, (float*) 0x662d70, (float*) 0x662d80, (char*) 0x68ff14);
								g_7731b8[idx + i + 0x57] = (int) obj;
								*(unsigned char*) (obj + 0x215) |= 1;
								*(unsigned char*) (((char*) g_7731b8[idx + i + 0x57]) + 0x216) |= 3;
								*(unsigned char*) (((char*) g_7731b8[idx + i + 0x57]) + 0x215) &= ~2;
							}
							fcn_00438b40(((char*) g_7731b8[idx + i + 0x57]), statep - 0xb);
						}
						if (*statep == 3) {
							obj = ((char*) g_7731b8[idx + i + 0x57]);
							if (obj != 0) {
								d3_DestroyObject(obj);
								g_7731b8[idx + i + 0x57] = (int) 0;
							}
							if (SLOT->data != 0) {
								*SLOT->data = i;
							}
							*(int*) ((char*) SLOT->data + i * 0x10 + 8) = -1;
							if (SLOT->callback != 0) {
								SLOT->callback((int) SLOT->data);
							}
							*statep = 0;
							g_7731b8[idx + i + 0x54] = 0;
						} else if (*statep == 2) {
							count++;
							obj = ((char*) g_7731b8[idx + i + 0x57]);
							if (obj != 0) {
								d3_DestroyObject(obj);
								g_7731b8[idx + i + 0x57] = (int) 0;
							}
							fcn_004f01c0(SLOT->flags & 1, SLOT->id, (int) (statep - 0x17), SLOT->data);
							if (SLOT->data != 0) {
								*SLOT->data = i;
							}
							if (SLOT->callback != 0) {
								SLOT->callback((int) SLOT->data);
							}
							*statep = 0;
							g_7731b8[idx + i + 0x54] = 0;
							*SLOT->data = -1;
						}
					}
					i++;
					statep += 0x1a;
				}
				if (count >= 3) {
					SLOT->flags &= ~3;
					if (SLOT->flags & 4) {
						fcn_004efd70(SLOT->id);
					}
				}
			} else if (SLOT->flags & 4) {
				fcn_004efd70(SLOT->id);
			}
		}
		idx += 0x5c;
		if (idx >= 0x2e0) {
			break;
		}
	}
	fcn_004432d0(save, 1);
}
