/*
 * Re-balances the goods stock of one town building: queries the producers,
 * sells or buys the missing goods through the trade packets and finally
 * reports the request to the server.
 */
#include <string.h>
#include <stdio.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
typedef struct {
	int x0;
	int n;
	int x8[16];
	unsigned short x48[16];
	int x68[16];
	int xa8;
	int xac;
	int xb0;
	char* xb4;
} Stats; /* 0xb8 */

typedef struct {
	int f00;              /* +0x00 */
	unsigned char type;   /* +0x04 */
	unsigned char f05;
	unsigned char flag;   /* +0x06 */
	unsigned char f07;
	int state;            /* +0x08 */
	int f0c;              /* +0x0c */
	int f10;
	int f14;
	int f18;
	char pad1c[0x28 - 0x1c];
	int p28;
	int p2c;
	int p30;
	unsigned short p34;
	unsigned char flag2;  /* +0x36 */
	char pad37[0x58 - 0x37];
	int f58;
	int f5c;              /* +0x5c */
	int f60;              /* +0x60 */
	int slots[6];         /* +0x64 */
	unsigned short ids[6];/* +0x7c */
	int f88[4];           /* +0x88 */
	char pad98[0x9d - 0x98];
	unsigned char skip;   /* +0x9d */
	char pad9e[0xf8 - 0x9e];
} Msg; /* 0xf8 */

extern int lpObjektePROT;
extern unsigned char g_773d75;
extern int gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

int __cdecl gm_CollectBuildingStock(char*, void*, int);
int __cdecl gm_CalcEntityInventoryStats(char*, Stats*);
char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl gm_GetStorageSlotCapacity(char*, int);
float __cdecl fcn_0050bb50(int, unsigned char);
int __cdecl ai_GetMaxActiveTradeActions(void);
int __cdecl he_CountActiveTradeActions(void);
int __cdecl cm_SendCopyEntityData(void*);
int __cdecl cm_RequestMoveCredits(int, int, char, int);
int __cdecl cm_SendLogAction(int);
int __cdecl cm_SendTraceEnd(int);
int __cdecl cm_SendSellObjekt(int, int, short, int, char, int);
int __cdecl gm_AddTime(void*, int, int, int);
int __cdecl gm_QueryEntitySum(int, int);


/* ADDRESS: GOLDTL 0x0048cdb0 */
unsigned int __cdecl fcn_0048cdb0(char* o, char* req)
{
	Msg m;
	Stats st;
	char name[0xb8];
	char line[0x400];
	int totals[4];
	char* item;
	int i;
	int n;
	int k;
	char* q;
	int j;
	char* e;
	char* g;
	int amt;
	int lim;
	int sum;
	int want;
	int idx;

	n = 0;
	k = 0;
	if (*(float*) 0x100d0f4 <= 0.0f || *(int*) 0x100d10c == 0)
		return 0;
	gm_CollectBuildingStock(*(char**) (o + 0x16c), name, 0);
	for (i = 0; i < *(int*) 0x100e74c; i++) {
		item = (char*) *(int*) (0x100dbc0 + i * 4);
		if (*(unsigned char*) (item + 0x12) < 0x21) {
			memset(&m, 0, 0xf8);
			m.type = 0x10;
			m.state = *(int*) (*(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c + 0x7f4ca4);
			m.f0c = *(int*) (*(int*) (o + 0x16c) + 1);
			m.p28 = gm_GameTime;
			m.p2c = g_7f4c04;
			m.p30 = g_7f4c08;
			m.flag2 = 1;
			m.p34 = g_7f4c0c;
			gm_AddTime(&m.p28, 0, 0, 10);
			m.f58 = *(int*) (item + 2);
			m.slots[0] = 5;
			m.ids[4] = 0;
			m.ids[5] = 0;
			m.f5c = 100 - (int) *(unsigned char*) (item + 0x12);
			cm_SendCopyEntityData(&m);
		}
		else {
			memset(&m, 0, sizeof(m));
			if (he_CountActiveTradeActions() > ai_GetMaxActiveTradeActions())
				m.skip = 1;
			for (j = 0; j < 3; j++) {
				m.ids[j] = 0;
				m.slots[j] = -1;
				m.ids[j + 3] = 0;
				m.slots[j + 3] = -1;
			}
			gm_CalcEntityInventoryStats(item, &st);
			q = fcn_00502cd0(*(int*) (item + 0x14), 1, 0, 0x1dd);
			j = 0;
			if (st.x0 > 0) {
				for (; j < st.x0; j++) {
					if (st.x48[j] == 0)
						continue;
					sprintf(line, (char*) 0x67e918, *(int*) (o + 0x16c) + 5, st.x68[j], (char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[st.x48[j]] + 1);
					for (e = 0, lim = 0x100b0c0; lim < 0x100d0c0 && !e; lim += 0x40) {
						if (*(int*) lim == (int) st.x48[j])
							e = (char*) lim;
					}
					if (st.x68[j] == 0)
						continue;
					sprintf(line, (char*) 0x67e8c0, *(int*) (o + 0x16c) + 5, st.x68[j], (char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[st.x48[j]] + 1);
					sprintf(line, (char*) 0x67e358, -1, *(int*) (q + 2), (int) st.x48[j], st.x68[j], g_773d75, (double) (int) fcn_0050bb50((int) st.x48[j], g_773d75));
					cm_SendSellObjekt(-1, *(int*) (q + 2), (short) st.x48[j], st.x68[j], (char) g_773d75, (int) fcn_0050bb50((int) st.x48[j], g_773d75));
					*(int*) (o + 0x1b8) = (int) (fcn_0050bb50((int) st.x48[j], g_773d75) + *(int*) (o + 0x1b8));
					st.x48[j] = 0;
					st.x68[j] = 0;
				}
			}
			amt = gm_GetStorageSlotCapacity(q, *(int*) 0x100d0c0);
			lim = *(int*) 0x100d10c;
			if (amt < lim)
				lim = amt;
			sprintf(line, (char*) 0x67e358, *(int*) (q + 2), *(int*) (req + 2), *(int*) 0x100d0c0, lim, g_773d75, 0);
			if (*(int*) 0x100d10c <= amt)
				amt = *(int*) 0x100d10c;
			cm_SendSellObjekt(*(int*) (q + 2), *(int*) (req + 2), *(short*) 0x100d0c0, amt, (char) g_773d75, 0);
			m.ids[n] = *(unsigned short*) 0x100d0c0;
			m.slots[n] = *(int*) (*(int*) 0x100d0d4 + 1);
			n++;
			st.x48[0] = *(unsigned short*) 0x100d0c0;
			j = 1;
			if (n < 3) {
				do {
					if (j >= *(int*) 0x100b0ac)
						break;
					e = (char*) (0x100d0c0 + j * 0x58);
					if (!(*(float*) (e + 0x34) <= 0.0f))
						break;
					if (*(int*) (*(int*) (e + 0x14) + 1) == m.slots[3] && *(int*) (e + 0x4c) != 0) {
						lim = gm_GetStorageSlotCapacity(q, *(int*) e);
						if (st.x0 > 0) {
							for (idx = 0; idx < st.x0; idx++) {
								if (st.x48[idx] != 0)
									continue;
								want = *(int*) (e + 0x4c);
								if (lim < want)
									want = lim;
								sprintf(line, (char*) 0x67e358, *(int*) (q + 2), *(int*) (req + 2), *(int*) e, want, g_773d75, 0);
								want = *(int*) (e + 0x4c);
								if (lim < want)
									want = lim;
								cm_SendSellObjekt(*(int*) (q + 2), *(int*) (req + 2), *(int*) e, want, (char) g_773d75, 0);
								m.ids[n] = *(unsigned short*) e;
								m.slots[n] = *(int*) (*(int*) (e + 0x14) + 1);
								n++;
								st.x48[idx] = *(unsigned short*) e;
							}
						}
					}
					j++;
				} while (n < 3);
			}
			memset(totals, 0, sizeof(totals));
			j = 0;
			if (k < 3) {
				do {
					if (j >= *(int*) 0x100b0a8)
						break;
					e = (char*) (0x100b0c0 + j * 0x40);
					if (!(*(float*) (e + 0x20) <= 0.0f))
						break;
					g = (char*) *(int*) (e + 8);
					if (*(int*) (g + 1) != m.slots[0] || *(int*) (e + 0x34) == 0) {
						j++;
						continue;
					}
					amt = gm_GetStorageSlotCapacity(q, *(int*) (e + 0x0c));
					if (g == 0) {
						j++;
						continue;
					}
					m.ids[k + 3] = *(unsigned short*) e;
					m.slots[k + 3] = *(int*) (g + 1);
					if (amt >= *(int*) (e + 0x34))
						amt = *(int*) (e + 0x34);
					m.f88[k] = amt;
					if (*g == 'G')
						totals[*(int*) (g + 0x65)] = (int) (totals[*(int*) (g + 0x65)] + amt * *(float*) (e + 0x1c));
					k++;
					j++;
				} while (k < 3);
			}
			for (k = 1; k < 4; k++) {
				sum = gm_QueryEntitySum(*(int*) (0x7f4e18 + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c), k);
				want = totals[k];
				if (want > sum) {
					want = (want * 9) / 8;
					cm_SendLogAction((int) (char*) 0x67e8b0);
					cm_RequestMoveCredits(*(int*) (0x7f4ca4 + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c), -1, (char) k, want);
					cm_RequestMoveCredits(-1, *(int*) (0x7f4ca4 + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c), (char) g_773d75, (int) ((double) want * 1.03));
					cm_SendTraceEnd((int) (char*) 0x67e8b0);
				}
				else if (want * 2 < sum) {
					want = sum - (want * 9) / 8;
					cm_SendLogAction((int) (char*) 0x67e8b0);
					cm_RequestMoveCredits(*(int*) (0x7f4ca4 + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c), -1, (char) g_773d75, want);
					cm_RequestMoveCredits(-1, *(int*) (0x7f4ca4 + *(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c), (char) k, (int) ((double) want * 1.03));
					cm_SendTraceEnd((int) (char*) 0x67e8b0);
				}
			}
			lim = m.slots[0];
			if (lim == -1)
				lim = m.slots[3];
			m.type = 0x0b;
			m.state = *(int*) (*(unsigned short*) (*(int*) (o + 0x16c) + 0x27) * 0x21c + 0x7f4ca4);
			m.f0c = *(int*) (*(int*) (o + 0x16c) + 1);
			m.p28 = gm_GameTime;
			m.p2c = g_7f4c04;
			m.p30 = g_7f4c08;
			m.p34 = g_7f4c0c;
			m.flag2 = 1;
			m.f58 = *(int*) (item + 2);
			m.f5c = lim;
			m.f60 = *(int*) (o + 4);
			if (*(int*) 0x100b0a4 == 0) {
				cm_SendCopyEntityData(&m);
				*(int*) 0x772620 = *(int*) 0x772620 + 1;
			}
		}
	}
	return 1;
}
