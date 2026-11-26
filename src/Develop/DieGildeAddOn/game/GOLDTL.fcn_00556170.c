#include <math.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern int lpGebaeudeINST;
extern int lpGebaeudePROT;
extern unsigned char g_773d75;
extern char gm_GameTime[];

void __cdecl he_FreeAction(char*);
int __cdecl gm_AddTime(char*, int, int, int);
int __cdecl fcn_004c5620(int, char*);
float __cdecl gm_GetCityStatsSummary(char*);
double __cdecl gm_RandomFloat01(void);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl cm_RequestAllocSpieler(int, int, int, int, int, int, int, int);
int __cdecl cm_GetCommandStatus(int);
char* __cdecl cm_GetCommandResult(int);
void __cdecl cm_RequestSetWohnsitz(int, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl gm_GetBuildingSlotLimits(int, int*);
float __cdecl fcn_004ff210(unsigned short, int);

#pragma pack(push, 1)
typedef struct {
	int a;
	int b;
	int c;
	short d;
} UIPos;
#pragma pack(pop)

#define COPY_UI(q) \
	*(UIPos*) ((q) + 0x52) = *(UIPos*) ((char*) gm_GameTime)

/* ADDRESS: GOLDTL 0x00556170 */
void __cdecl he_RunCityPopulationEvent(char* p)
{
	float ts[0xa];
	int limits[2];
	int v34;
	int v38;
	char* ent;
	char* obj;
	int found;
	int n;
	int i;
	int key;
	int idx;
	int type;
	int state;
	int v;
	float f;

	state = *(int*) (p + 0x70);
	if (state == -1 || state == -2) {
		he_FreeAction(p);
		return;
	}
	if (*(unsigned char*) (p + 0x78) & 4) {
		return;
	}
	switch (state) {
	case 0:
		*(int*) (p + 0xb4) = 0;
		*(int*) (p + 0xac) = 0;
		*(float*) (p + 0xb0) = *(float*) (p + 0xb0) * 0.0f;
		gm_AddTime(p + 0x52, 0, 0, 5);
		*(int*) (p + 0x84) = fcn_004c5620(1, p);
		return;
	case 1:
		gm_GetCityStatsSummary((char*) ts);
		f = (float) (((int*) ts)[8] - ((int*) ts)[4]) / (float) ((int*) ts)[8];
		*(float*) (p + 0xb0) = 1.0f - f;
		*(float*) (p + 0xb4) = f / (float) (*(int*) (p + 0xac) + 2);
		gm_AddTime(p + 0x52, 1, 0, 0);
		if (ts[3] < 0.1) {
			*(float*) (p + 0xb0) = (2.0f - ts[9]) * *(float*) (p + 0xb0);
			*(int*) (p + 0x84) = fcn_004c5620(2, p);
			return;
		}
		if (0.3 < ts[3]) {
			*(float*) (p + 0xb0) = (float) fabs((ts[9] + 1.0f) * *(float*) (p + 0xb0));
			*(float*) (p + 0xb4) = (float) fabs(*(float*) (p + 0xb4));
			*(int*) (p + 0x84) = fcn_004c5620(6, p);
			return;
		}
		COPY_UI(p);
		*(short*) (p + 0x56) = 0xf;
		goto anim7;
	case 2:
		if (*(unsigned short*) ((char*) gm_GameTime + 4) >= 0x14) {
			COPY_UI(p);
inc_anim7:
			*(int*) (p + 0x58) += 1;
anim7:
			*(int*) (p + 0x84) = fcn_004c5620(7, p);
			return;
		}
		f = gm_RandomFloat01();
		if (f > *(float*) (p + 0xb0)) {
			*(int*) (p + 0xb8) = -1;
			*(int*) (p + 0xb8) = cm_RequestAllocSpieler(0xff, -1, -1,
				gm_RandomMod(0xc) + 0xf, -1, 0, 0, 2);
			COPY_UI(p);
			gm_AddTime(p + 0x52, 0, 0, 1);
			*(int*) (p + 0x84) = fcn_004c5620(3, p);
			return;
		}
		*(float*) (p + 0xb0) -= *(float*) (p + 0xb4);
		COPY_UI(p);
		gm_AddTime(p + 0x52, 1, 0, 0);
		*(int*) (p + 0x84) = fcn_004c5620(2, p);
		return;
	case 3:
		if (cm_GetCommandStatus(*(int*) (p + 0xb8)) == 0) {
			COPY_UI(p);
			gm_AddTime(p + 0x52, 0, 0, 1);
			*(int*) (p + 0x84) = fcn_004c5620(3, p);
			return;
		}
		if (cm_GetCommandStatus(*(int*) (p + 0xb8)) == 2) {
			gm_AddTime(p + 0x52, 1, 0, 0);
			*(int*) (p + 0xb8) = -1;
			*(int*) (p + 0x84) = fcn_004c5620(6, p);
			return;
		}
		obj = cm_GetCommandResult(*(int*) (p + 0xb8));
		v38 = 0;
		v34 = gm_RandomMod(2) & 0xffff;
		if (obj == 0) {
			gm_AddTime(p + 0x52, 1, 0, 0);
			*(int*) (p + 0xb8) = -1;
			*(int*) (p + 0x84) = fcn_004c5620(6, p);
			return;
		}
		found = 0;
		n = 0x100;
		v = (unsigned short) gm_RandomMod(0x100);
		while (n != 0) {
			ent = (char*) (lpGebaeudeINST + v * 0xa9);
			type = *(unsigned char*) ent;
			if ((char)((BUILDING_PROTOTYPE*)lpGebaeudePROT)[type].category == 1 &&
			    gm_GetBuildingSlotLimits(type, limits) != 0 &&
			    *(unsigned char*) (ent + 0x65) < (unsigned short) limits[0]) {
				found = 1;
			}
			n--;
			v = (v + 1) % 0x100;
			if (found != 0) {
				break;
			}
		}
		if (found)
			cm_RequestSetWohnsitz(*(int*) (obj + 4), *(int*) (ent + 1));
		i = gm_RandomMod(0x32);
		cm_RequestTransferCurrencyNoKill(*(int*) (obj + 4), -1, g_773d75, ((i & 0xffff) + 0x33) * 0x20);
		cm_BeginPacketFieldDelta(obj, *(int*) (obj + 4));
		cm_AppendPacketFieldDelta(1, 1, 2, &v38);
		cm_AppendPacketFieldDelta(1, 1, 0xc, &v34);
		cm_RequestChangeAttribute();
		COPY_UI(p);
		gm_AddTime(p + 0x52, 1, 0, 0);
		*(int*) (p + 0xac) += 1;
		*(int*) (p + 0x84) = fcn_004c5620(1, p);
		return;
	case 6:
		if (*(unsigned short*) ((char*) gm_GameTime + 4) >= 0x14) {
			COPY_UI(p);
			goto inc_anim7;
		}
		f = gm_RandomFloat01();
		if (f > *(float*) (p + 0xb0)) {
			v = (unsigned short) gm_RandomMod(0x300);
			n = 0x300;
			do {
				key = v * 0x21c;
				if (*(unsigned short*) (key + 0x7f4ca0) != 0xffff &&
				    *(char*) (key + 0x7f4ca8) != 0 &&
				    *(char*) (key + 0x7f4ca2) == 0 &&
				    *(int*) (key + 0x7f4e0c) == 0) {
					fcn_004ff210(v, -2000);
					*(int*) (p + 0xac) += 1;
					break;
				}
				n--;
				v = (v + 1) % 0x300;
			} while (n != 0);
			*(int*) (p + 0xb8) = -1;
			COPY_UI(p);
			gm_AddTime(p + 0x52, 0, 0x1e, 0);
			*(int*) (p + 0x84) = fcn_004c5620(1, p);
			return;
		}
		*(float*) (p + 0xb0) -= *(float*) (p + 0xb4);
		COPY_UI(p);
		gm_AddTime(p + 0x52, 1, 0, 0);
		*(int*) (p + 0x84) = fcn_004c5620(6, p);
		return;
	case 7:
		v = (unsigned short) gm_RandomMod(0x300);
		n = 0x300;
		do {
			key = v * 0x21c;
			if (*(unsigned short*) (key + 0x7f4ca0) != 0xffff &&
			    *(char*) (key + 0x7f4ca8) != 0 &&
			    ((*(char*) (key + 0x7f4ca2) == 0 &&
			      *(int*) (key + 0x7f4e10) == 0) ||
			     (*(char*) (key + 0x7f4ca2) == 1 &&
			      *(int*) (key + 0x7f4e10) == 0))) {
				found = 0;
				i = 0x100;
				idx = (unsigned short) gm_RandomMod(0x100);
				while (i != 0) {
					ent = (char*) (lpGebaeudeINST + idx * 0xa9);
					type = *(unsigned char*) ent;
					if ((char)((BUILDING_PROTOTYPE*)lpGebaeudePROT)[type].category == 1 &&
					    gm_GetBuildingSlotLimits(type, limits) != 0 &&
					    *(unsigned char*) (ent + 0x65) < (unsigned short) limits[0]) {
						found = 1;
					}
					i--;
					idx = (idx + 1) % 0x100;
					if (found != 0) {
						break;
					}
				}
				if (found != 0) {
					cm_RequestSetWohnsitz(*(int*) (key + 0x7f4ca4), *(int*) (ent + 1));
				}
				break;
			}
			n--;
			v = (v + 1) % 0x300;
		} while (n != 0);
		gm_AddTime(p + 0x52, 0, 10, 0);
		if (*(unsigned short*) (p + 0x56) >= 0x16) {
			COPY_UI(p);
			*(int*) (p + 0x58) = 0;
			*(int*) (p + 0x52) += 1;
			*(short*) (p + 0x56) = 6;
			*(int*) (p + 0x84) = fcn_004c5620(0, p);
			return;
		}
		if (*(unsigned short*) (p + 0x56) < 0xf) {
			COPY_UI(p);
			*(int*) (p + 0x58) += 1;
			*(int*) (p + 0x84) = fcn_004c5620(0, p);
			return;
		}
		goto anim7;
	default:
		return;
	}
}

static int filler_556170(char *e)
{
	return *(int *)(e + 4);
}
