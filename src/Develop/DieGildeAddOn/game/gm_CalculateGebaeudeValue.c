#if defined(REBREW_GOLD)
extern unsigned char* g_7e3f30;

extern char* g_item_def_table;
unsigned short* __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
float __cdecl eval_ObjektPreis2Credits(int, unsigned char);

/* ADDRESS: GOLD 0x00509b40 */
int __cdecl gm_CalculateGebaeudeValue(unsigned char* a0, int scale)
{
	unsigned char* row;
	unsigned short* words;
	unsigned short* ent;
	unsigned short* rec;
	unsigned char* kind;
	int acc;
	int i;
	int id;
	char seen;

	row = g_7e3f30 + *a0 * 0x24d;
	acc = *(int*) (row + 0x249) * 0xf00;
	ent = 0;
	seen = 0;
	i = 0;
	words = (unsigned short*) (row + 0x25);
	for (; i < 0x40; i++, words++) {
		if (words[-1] == 0) {
			break;
		}
		id = words[-1] & 0x7fff;
		kind = (unsigned char*) g_item_def_table + (id << 6) + id;
		if (!seen) {
			if (*kind != 2 && *kind != 6) {
				continue;
			}
			ent = fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 0, id);
			if (ent == 0) {
				continue;
			}
			acc = (int) (eval_ObjektPreis2Credits(ent[0], *((unsigned char*) ent + 0x12)) + acc);
			if (i >= 0x3f) {
				continue;
			}
			id = words[0] & 0x7fff;
			if (g_item_def_table[id * 0x41] != 2 && g_item_def_table[id * 0x41] != 6) {
				seen = 1;
			}
		} else if (ent != 0) {
			rec = fcn_00502cd0(*(int*) ((unsigned char*) ent + 0x14), 1, 0, id);
			if (rec != 0) {
				acc = (int) (eval_ObjektPreis2Credits(rec[0], *((unsigned char*) rec + 0x12)) + acc);
			}
			if (i >= 0x3f) {
				continue;
			}
			id = words[0] & 0x7fff;
			if (g_item_def_table[id * 0x41] == 2 || g_item_def_table[id * 0x41] == 6) {
				seen = 0;
			}
		}
	}
	return (int) (acc * (scale * 0.01f));
}
#else
#pragma pack(push, 1)
/* SIZE 0x24d */
typedef struct {
	char pad0[0x23];
	unsigned short ids[0x40];
	char pad_a3[0x1a6];
	int value;
} Lvl50cf;
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
/* SIZE 0x41 */
typedef struct {
	unsigned char kind;
	char pad1[0x40];
} Kind50cf;
#pragma pack(pop)

extern unsigned char* lpGebaeudePROT;
extern char* lpObjektePROT;


float __cdecl eval_ObjektPreis2Credits(int, unsigned char);
char* __cdecl fcn_00502cd0(int, int, int, int);

/* ADDRESS: GOLDTL 0x0050cf50 */
int __cdecl gm_CalculateGebaeudeValue(unsigned char* buildingRecordArg, int percentScale)
{
	BUILDING_PROTOTYPE* lvl;
	char* t;
	char* q;
	unsigned char k;
	unsigned char flag;
	/* two slots: the native frame is 8 bytes while only one holds the
	   int/float accumulator pun at [ebp-8] */
	int acc[2];
	int i;
	int id;

	lvl = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[buildingRecordArg[0]];
	acc[0] = lvl->base_value * 0xf00;
	t = 0;
	flag = 0;
	for (i = 0; i < 0x40; i++) {
		if (lvl->components[i] == 0) {
			break;
		}
		id = lvl->components[i] & 0x7fff;
		k = ((OBJECT_PROTOTYPE*) lpObjektePROT)[id].kind;
		if (!flag) {
			if (k == 2 || k == 6) {
				t = fcn_00502cd0(*(int*) (buildingRecordArg + 0x5d), 1, 0, id);
				if (t != 0) {
					acc[0] = (int) (acc[0] + eval_ObjektPreis2Credits(*(unsigned short*) t, *(unsigned char*) (t + 0x12)));
					if (i < 0x3f) {
						k = ((OBJECT_PROTOTYPE*) lpObjektePROT)[lvl->components[i + 1] & 0x7fff].kind;
						if (k != 2 && k != 6) {
							flag = 1;
						}
					}
				}
			}
		} else {
			if (t != 0) {
				q = fcn_00502cd0(*(int*) (t + 0x14), 1, 0, id);
				if (q != 0) {
					acc[0] = (int) (acc[0] + eval_ObjektPreis2Credits(*(unsigned short*) q, *(unsigned char*) (q + 0x12)));
				}
				if (i < 0x3f) {
					k = ((OBJECT_PROTOTYPE*) lpObjektePROT)[lvl->components[i + 1] & 0x7fff].kind;
					if (k == 2 || k == 6) {
						flag = 0;
					}
				}
			}
		}
	}
	return (int) (acc[0] * (0.01f * percentScale));
}
#endif
