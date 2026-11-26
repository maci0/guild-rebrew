typedef struct Slots {
	int v[0x2d];
	char* obj;
} Slots;
// SIZE 0xb8
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern unsigned char* lpGebaeudePROT;
extern unsigned char g_773d75;
extern float g_664174;

int* __cdecl gm_GetChainNodeAtIndex(int, int);
char* __cdecl gm_SearchTable67(int);
int __cdecl gm_CollectBuildingStock(char*, Slots*, int);
char* __cdecl fcn_0050d490(char*);
int __cdecl gm_CalcEntityInventoryStats(char*, Slots*);
char* __cdecl fcn_00503d10(int);
char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl gm_GetMsgField(char*, char*);
int __cdecl gm_eval_SlotVoll(char*, int, int);
float __cdecl fcn_0050bb50(int, unsigned char);
int __cdecl fcn_0050d320(char*, int);
int __cdecl fcn_004c51f0(int, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x004c0240 */
void __cdecl fcn_004c0240(char* a0, int a1)
{
	char* rec;
	char* t;
	char* v4;
	char* pkt;
	char* src;
	char* item;
	int n;
	int c;
	int cnt;
	int val;
	Slots buf;
	Slots stats;

	if (*(int*) (a0 + 0x29) == 0) {
		return;
	}
	rec = (char*) gm_GetChainNodeAtIndex(*(int*) (a0 + 0x29), *(int*) (a0 + 0x2d));
	pkt = gm_SearchTable67(*(int*) (rec + 4));
	if (pkt == 0) {
		return;
	}
	t = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) pkt];
	if ((((char)(((BUILDING_PROTOTYPE*)t)->category)) != 0xa && ((char)(((BUILDING_PROTOTYPE*)t)->category)) != 0x1c) && gm_CollectBuildingStock(pkt, &buf, 0) == 0) {
		return;
	}
	v4 = fcn_0050d490(a0);
	if (gm_CalcEntityInventoryStats(a0, &stats) == 0) {
		return;
	}
	rec += 0x20;
	for (cnt = 3; cnt != 0; cnt--) {
		if (*(int*) rec != 0) {
			if (((char)(((BUILDING_PROTOTYPE*)t)->category)) == 0xa) {
				src = fcn_00503d10(*(int*) rec);
			} else if (((char)(((BUILDING_PROTOTYPE*)t)->category)) == 0x1c) {
				src = fcn_00502cd0(*(int*) (pkt + 0x5d), 2, 0, 0x1db, 6);
			} else {
				src = buf.obj;
			}
			item = fcn_00502cd0(*(int*) (stats.obj + 0x14), 1, 0, *(int*) rec);
			if (item != 0) {
				n = *(int*) (rec + 4);
				if (!(n < gm_GetMsgField(stats.obj, item))) {
					n = gm_GetMsgField(stats.obj, item);
				}
				c = gm_eval_SlotVoll(src, *(int*) rec, n);
				if (c > 0) {
					val = 0;
					if (*(unsigned short*) (pkt + 0x27) != *(unsigned short*) v4) {
						if (((char)(((BUILDING_PROTOTYPE*)t)->category)) == 0xa) {
							val = (int) (fcn_0050bb50(*(unsigned short*) item, g_773d75) *
								     g_664174);
						} else {
							val = (int) (fcn_0050bb50(*(unsigned short*) item, g_773d75) *
								     *(float*) (pkt + 0x49));
						}
					}
					if (fcn_0050d320(v4, a1) >= val * c) {
						fcn_004c51f0(*(int*) (src + 2), *(int*) (stats.obj + 2),
							     *(int*) rec, c, a1, val);
					}
				}
			}
		}
		rec += 8;
	}
}
