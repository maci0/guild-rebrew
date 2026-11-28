typedef struct Slots {
	int v[0x2d];
	char* obj;
} Slots;
// SIZE 0xb8
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern unsigned char* lpGebaeudePROT;
extern char gm_TownTable[];
extern unsigned char gm_ActiveTownIndex;

int* __cdecl gm_GetChainNodeAtIndex(int, int);
char* __cdecl gm_ResolveParentEntity(char*);
char* __cdecl gm_SearchTable67(int);
int __cdecl gm_CollectBuildingStock(char*, Slots*, int);
int __cdecl gm_CalcEntityInventoryStats(char*, Slots*);
char* __cdecl gm_FindCityItemHolder(int);
char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl gm_GetMsgField(char*, char*);
int __cdecl gm_eval_SlotVoll(char*, int, int);
float __cdecl gm_GetSeasonPrice(int, unsigned char);
int __cdecl gm_GetSeasonTreasury(char*, char);
void __cdecl txt_GetCitySelectInfo(char*, char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
int __cdecl cm_SendSellObjekt(int, int, int, int, char, int);

/* ADDRESS: GOLDTL 0x004c0460 */
void __cdecl he_BuyTransportCargoAtStop(char* e, char who)
{
	int* p;
	char* q;
	char* par;
	int k;
	BUILDING_PROTOTYPE *t;
	Slots a = {0};
	Slots b = {0};
	char name[0x80];
	char text[0x400];
	char* src;
	char* o;
	int n;
	int m;
	int val;
	int* d;

	if (*(int*) (e + 0x29) == 0) {
		return;
	}
	d = gm_GetChainNodeAtIndex(*(int*) (e + 0x29), *(int*) (e + 0x2d));
	par = gm_ResolveParentEntity(e);
	q = gm_SearchTable67(d[1]);
	if (q == 0) {
		return;
	}
	t = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) q];
	if (t->category != 10 && t->category != 0x1c) {
		if (gm_CollectBuildingStock(q, &a, 0) == 0) {
			return;
		}
	}
	if (gm_CalcEntityInventoryStats(e, &b) == 0) {
		return;
	}
	for (k = 3, p = d + 2; k != 0; k--, p += 2) {
		if (p[0] == 0) {
			continue;
		}
		val = 0;
		if (t->category == 10) {
			src = gm_FindCityItemHolder(p[0]);
		} else if (t->category == 0x1c) {
			src = fcn_00502cd0(*(int*) (q + 0x5d), 2, 0, 0x1dc, 6);
		} else {
			src = a.obj;
		}
		o = fcn_00502cd0(*(int*) (src + 0x14), 1, 0, p[0]);
		if (o == 0) {
			continue;
		}
		n = p[1];
		if (n >= gm_GetMsgField(src, o)) {
			n = gm_GetMsgField(src, o);
		}
		m = gm_eval_SlotVoll(b.obj, p[0], n);
		if (*(short*) (q + 0x27) != *(short*) par) {
			if (t->category == 10) {
				val = (int) (gm_GetSeasonPrice(*(unsigned short*) o, gm_ActiveTownIndex) * 1.1f);
			} else if (t->category == 0x1c) {
				val = (int) (gm_GetSeasonPrice(*(unsigned short*) o, q[0x65]) * 1.1f);
			} else {
				val = (int) (gm_GetSeasonPrice(*(unsigned short*) o, gm_ActiveTownIndex) * *(float*) (q + 0x49));
			}
		}
		if (m > 0) {
			if (gm_GetSeasonTreasury(par, who) < m * val) {
				txt_GetCitySelectInfo(gm_TownTable + who * 756, name);
				io_FormatTextBuffer(text, 0x42f0, name, 0xc14, name, who);
				he_PostEntityMessage(*(int*) (par + 4), -1, text, 0, 0x5ef, "");
			}
			cm_SendSellObjekt(*(int*) (b.obj + 2), *(int*) (src + 2), p[0], m, who, val);
		}
	}
}
