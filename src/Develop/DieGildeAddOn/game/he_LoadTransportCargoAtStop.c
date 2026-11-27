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
char* __cdecl gm_FindCityItemHolder(int);
char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl gm_GetMsgField(char*, char*);
int __cdecl gm_eval_SlotVoll(char*, int, int);
float __cdecl gm_GetSeasonPrice(int, unsigned char);
int __cdecl gm_GetSeasonTreasury(char*, int);
int __cdecl cm_SendSellObjekt(int, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x004c0240 */
void __cdecl he_LoadTransportCargoAtStop(char* route, int difficulty)
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

	if (*(int*) (route + 0x29) == 0) {
		return;
	}
	rec = (char*) gm_GetChainNodeAtIndex(*(int*) (route + 0x29), *(int*) (route + 0x2d));
	pkt = gm_SearchTable67(*(int*) (rec + 4));
	if (pkt == 0) {
		return;
	}
	t = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) pkt];
	if ((((char)(((BUILDING_PROTOTYPE*)t)->category)) != 0xa && ((char)(((BUILDING_PROTOTYPE*)t)->category)) != 0x1c) && gm_CollectBuildingStock(pkt, &buf, 0) == 0) {
		return;
	}
	v4 = fcn_0050d490(route);
	if (gm_CalcEntityInventoryStats(route, &stats) == 0) {
		return;
	}
	rec += 0x20;
	for (cnt = 3; cnt != 0; cnt--) {
		if (*(int*) rec != 0) {
			if (((char)(((BUILDING_PROTOTYPE*)t)->category)) == 0xa) {
				src = gm_FindCityItemHolder(*(int*) rec);
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
							val = (int) (gm_GetSeasonPrice(*(unsigned short*) item, g_773d75) *
								     g_664174);
						} else {
							val = (int) (gm_GetSeasonPrice(*(unsigned short*) item, g_773d75) *
								     *(float*) (pkt + 0x49));
						}
					}
					if (gm_GetSeasonTreasury(v4, difficulty) >= val * c) {
						cm_SendSellObjekt(*(int*) (src + 2), *(int*) (stats.obj + 2),
							     *(int*) rec, c, difficulty, val);
					}
				}
			}
		}
		rec += 8;
	}
}
