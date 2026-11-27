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
#include "client_types.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define SLOTS ((Sefde0Slot*) g_7731b8)

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
extern pos14_7f4c00 g_772fe8;
extern pos14_7f4c00 gm_GameTime;
extern float g_6652c4;
int __cdecl gm_GetElapsedMinutes(char*, char*);
void __cdecl d3_SelectSceneContext(int, int);
int __cdecl fcn_005e9870(Sefde0Entry*);
int __cdecl fcn_005e9da0(Sefde0Entry*);
char* __cdecl fcn_00442910(int, float*, float*, char*);
void __cdecl d3_DestroyObject(void*);
void __cdecl d3_SetNodePosition(char*, int*);
void __cdecl d3_ReleaseLightSlot(int);
void __cdecl fcn_004f01c0(int, int, int, int*);

/* ADDRESS: GOLDTL 0x004efde0 */
void __cdecl fcn_004efde0(void)
{
	int save;
	int elapsed;
	int slot;
	int count;
	int i;
	int state;
	float step;

	elapsed = gm_GetElapsedMinutes((char*) &g_772fe8, (char*) &gm_GameTime);
	if (elapsed < 0) {
		elapsed = 0;
	}
	step = (float) elapsed * g_6652c4;
	g_772fe8 = gm_GameTime;
	step *= g_662a3c;
	save = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 1);
	for (slot = 0; slot < 8; slot++) {
		if (SLOTS[slot].id != -1) {
			count = 0;
			SLOTS[slot].x += step;
			SLOTS[slot].y += step;
			SLOTS[slot].z += step;
			SLOTS[slot].x = MIN(SLOTS[slot].x, 1.0f);
			SLOTS[slot].y = MIN(SLOTS[slot].y, 1.0f);
			SLOTS[slot].z = MIN(SLOTS[slot].z, 1.0f);
			if (!(SLOTS[slot].flags & 2)) {
				if (SLOTS[slot].flags & 4) {
					d3_ReleaseLightSlot(SLOTS[slot].id);
				}
			} else {
				for (i = 0; i < 3; i++) {
					state = SLOTS[slot].entry[i].state;
					if (state == 0) {
						count++;
						if (count >= 3) {
							SLOTS[slot].flags &= ~3;
							if (SLOTS[slot].flags & 4) {
								d3_ReleaseLightSlot(SLOTS[slot].id);
							}
						}
					} else if (state == 1) {
						int runs;
						if (SLOTS[slot].mode == 0) {
							runs = fcn_005e9870(&SLOTS[slot].entry[i]);
						} else {
							runs = fcn_005e9da0(&SLOTS[slot].entry[i]);
						}
						if (runs != 0) {
							if (SLOTS[slot].objects[i] == 0) {
								SLOTS[slot].objects[i] = fcn_00442910(0, (float*) 0x662d70, (float*) 0x662d80, (char*) 0x68ff14);
								*(unsigned char*) (SLOTS[slot].objects[i] + 0x215) |= 1;
								*(unsigned char*) (SLOTS[slot].objects[i] + 0x216) |= 3;
								*(unsigned char*) (SLOTS[slot].objects[i] + 0x215) &= ~2;
							}
							d3_SetNodePosition(SLOTS[slot].objects[i], &SLOTS[slot].entry[i].obj);
						}
						if (SLOTS[slot].entry[i].state == 3) {
							if (SLOTS[slot].objects[i] != 0) {
								d3_DestroyObject(SLOTS[slot].objects[i]);
								SLOTS[slot].objects[i] = 0;
							}
							if (SLOTS[slot].data != 0) {
								*SLOTS[slot].data = i;
							}
							SLOTS[slot].data[i * 4 + 2] = -1;
							if (SLOTS[slot].callback != 0) {
								SLOTS[slot].callback((int) SLOTS[slot].data);
							}
							SLOTS[slot].entry[i].state = 0;
							SLOTS[slot].active[i] = 0;
						} else if (SLOTS[slot].entry[i].state == 2) {
							count++;
							if (SLOTS[slot].objects[i] != 0) {
								d3_DestroyObject(SLOTS[slot].objects[i]);
								SLOTS[slot].objects[i] = 0;
							}
							fcn_004f01c0(SLOTS[slot].flags & 1, SLOTS[slot].id, (int) &SLOTS[slot].entry[i], SLOTS[slot].data);
							if (SLOTS[slot].data != 0) {
								*SLOTS[slot].data = i;
							}
							if (SLOTS[slot].callback != 0) {
								SLOTS[slot].callback((int) SLOTS[slot].data);
							}
							SLOTS[slot].entry[i].state = 0;
							SLOTS[slot].active[i] = 0;
							*SLOTS[slot].data = -1;
						}
					}
				}
				if (count >= 3) {
					SLOTS[slot].flags &= ~3;
					if (SLOTS[slot].flags & 4) {
						d3_ReleaseLightSlot(SLOTS[slot].id);
					}
				}
			}
		}
	}
	d3_SelectSceneContext(save, 1);
}
