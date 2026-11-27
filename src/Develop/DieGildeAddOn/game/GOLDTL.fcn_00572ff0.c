#include <string.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "client_types.h"

typedef struct { unsigned char kind; unsigned char rest[0x24c]; } BuildingProto572ff0;
typedef struct {
	char pad0[4];
	char kind;
	char pad5[3];
	int owner;
	int f0c;
	char pad10[0x18];
	pos14_7f4c00 when;
	char code;
	char pad37[0x21];
	int f58;
	int f5c;
	int f60;
	char pad64[0x3c];
	int fa0;
	char pada4[0x54];
} Msg572ff0;
extern char g_7f4ca0[];

extern pos14_7f4c00 gm_GameTime;
extern unsigned char g_773d75;
extern char* gm_CityEntity;
extern char* lpGebaeudePROT;
extern char* lpObjektePROT;

char* __cdecl fcn_00502cd0(int, int, ...);
int __cdecl gm_ResolveEntityById(void**, void**, void**, int);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl cm_GetCommandStatus(int);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
int __cdecl cm_SendCopyEntityData(char*);
void __cdecl gm_AddTime(char*, int, int, int);
void __cdecl he_SetActionSubject(char*, int);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl gm_CanTradeWithObject(char*, char*);
char* __cdecl gm_FindCityItemHolder(int);
float __cdecl gm_GetSeasonPrice(int, unsigned char);
int __cdecl gm_GetStorageSlotCapacity(char*, int);
int __cdecl gm_GetMsgField(char*, char*);
int __cdecl gm_eval_SlotVoll(char*, int, int);
int __cdecl gm_GetSeasonTreasury(char*, unsigned char);
void __cdecl he_FreeAction(char*);
int __cdecl sprintf(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x00572ff0 */
void __cdecl he_RunHandelsrouteTrade(char* a)
{
	Msg572ff0 msg;
	char buf[0x70];
	char* pktA = 0;
	char* pktB = 0;
	char* itm = 0;
	char* ent;
	char* q;
	char* e2;
	char* r;
	char* r2;
	char* tmp;
	unsigned short* ps;
	int* pi;
	int left = 0;
	int amt = 0;
	int flag = 0;
	int n = 0;
	int i;
	int found;
	int cnt;
	int t;
	int m = 0;
	int d;
	int lim;
	int cand;

	if (*(int*) (a + 0x70) == -2) {
		*(int*) (a + 0x70) = 0;
		he_SetActionSubject(a, *(unsigned short*) gm_CityEntity);
	}
	if (*(int*) (a + 0xe8) != -1) {
		if (!cm_GetCommandStatus(*(int*) (a + 0xe8))) {
			gm_AddTime(a + 0x52, 0, 1, 0);
			return;
		}
		*(int*) (a + 0xe8) = -1;
	}
	if (*(int*) (a + 0xec) != -1) {
		if (!cm_GetCommandStatus(*(int*) (a + 0xec))) {
			gm_AddTime(a + 0x52, 0, 1, 0);
			return;
		}
		*(int*) (a + 0xec) = -1;
	}
	gm_ResolveEntityById(0, (void**) &pktA, 0, *(int*) (a + 0xac));
	gm_ResolveEntityById((void**) &pktB, 0, 0, *(int*) (a + 0xb0));
	gm_ResolveEntityById(0, 0, (void**) &itm, *(int*) (a + 0xb4));
	if (pktA == 0 || pktB == 0) {
		he_FreeAction(a);
		return;
	}
	ent = he_StartHandlungSearch(2, 0, 0xf, 2, *(unsigned short*) (a + 8));
	while (ent != 0) {
		if (*(int*) (ent + 0xac) == *(int*) (a + 0xac)) {
			if (*(int*) (ent + 0xb4) != *(int*) (a + 0xb0)) {
				he_FreeAction(a);
				return;
			}
			gm_AddTime(a + 0x52, 0, 5, 0);
			return;
		}
		ent = he_fn_Handlung();
	}
	if (*(char*) (a + 0xf1) == 0 && gm_CanTradeWithObject(pktB, pktA) == 0) {
		gm_CanTradeWithObject(pktB, pktA);
		he_FreeAction(a);
		return;
	}
	q = fcn_00502cd0(*(int*) (pktA + 0x14), 1, 0, 0x1dd);
	n = *(unsigned char*) (q + 0x1c);
	if (n >= 3) {
		n = 3;
	}
	found = 0;
	i = 0;
	ps = (unsigned short*) (a + 0xd6);
	while (i < n) {
		if (ps[-3] != 0 || ps[0] != 0) {
			found = 1;
		}
		i++;
		ps++;
		if (found) {
			break;
		}
	}
	if (!found) {
		e2 = fcn_00502cd0(*(int*) (pktB + 0x5d), 2, 6, 0, 0x2a);
		if (e2 != 0) {
			r = fcn_00502cd0(*(int*) (q + 0x14), 1, 5);
			while (r != 0) {
				*(int*) (a + 0xe8) = cm_SendSellObjekt(*(int*) (e2 + 2),
				    *(int*) (q + 2), *(unsigned short*) r, *(int*) (r + 0xe),
				    g_773d75, 0);
				r = gm_NextEntityQueryMatch();
			}
		} else {
			e2 = fcn_00502cd0(*(int*) (pktB + 0x5d), 2, 6, 0, 0x116);
			if (e2 != 0) {
				r = fcn_00502cd0(*(int*) (q + 0x14), 1, 5);
				while (r != 0) {
					*(int*) (a + 0xe8) = cm_SendSellObjekt(*(int*) (e2 + 2),
					    *(int*) (q + 2), *(unsigned short*) r, *(int*) (r + 0xe),
					    g_773d75, 0);
					r = gm_NextEntityQueryMatch();
				}
			}
		}
		if (*(int*) (a + 0xe8) != -1) {
			gm_AddTime(a + 0x52, 0, 5, 0);
			return;
		}
		he_FreeAction(a);
		return;
	}
	found = 0;
	i = 0;
	ps = (unsigned short*) (a + 0xd0);
	while (i < n) {
		if (ps[0] != 0) {
			found = 1;
		}
		i++;
		ps++;
		if (found) {
			break;
		}
	}
	if (found) {
		if (n <= 0) {
			goto done;
		}
		pi = (int*) (a + 0xb8);
		ps = (unsigned short*) (a + 0xd0);
		cnt = n;
		do {
			if (ps[0] == 0 || pi[0] != *(int*) (pktB + 1)) {
				goto i1next;
			}
			r2 = fcn_00502cd0(*(int*) (q + 0x14), 1, 0, ps[0]);
			if (r2 == 0) {
				goto i1next;
			}
			if (((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) pktB].category == '\n') {
				e2 = gm_FindCityItemHolder(ps[0]);
			} else {
				e2 = fcn_00502cd0(*(int*) (pktB + 0x5d), 2, 6, 0, 0x2a);
				if (e2 == 0) {
					e2 = fcn_00502cd0(*(int*) (pktB + 0x5d), 2, 6,
					    0, 0x116);
				}
			}
			if (e2 == 0) {
				goto i1next;
			}
			t = gm_GetMsgField(q, r2);
			m = gm_eval_SlotVoll(e2, *(unsigned short*) r2, t);
			d = (int) (gm_GetSeasonPrice(*(unsigned short*) r2, g_773d75)
			    * 0.9);
			if (t < m) {
				m = t;
			}
			cm_SendSellObjekt(*(int*) (e2 + 2),
			    *(int*) (q + 2), *(unsigned short*) r2, m, g_773d75, d);
			if (itm != 0) {
				*(int*) (itm + 0x1b8) = *(int*) (itm + 0x1b8) + d * m;
			}
			if ((t -= m) != 0) {
				d = (int) (gm_GetSeasonPrice(*(unsigned short*) r2,
				    g_773d75) * 0.8);
				*(int*) (a + 0xe8) = cm_SendSellObjekt(-1,
				    *(int*) (q + 2), *(unsigned short*) r2, t,
				    g_773d75, d);
			}
i1next:
			ps[0] = 0;
			pi[0] = -1;
			ps++;
			pi++;
		} while (--cnt != 0);
		goto done;
	}
	if (itm != 0 && *(int*) (itm + 0x16c) != 0) {
		left = gm_GetSeasonTreasury(g_7f4ca0
		    + *(unsigned short*) (*(int*) (itm + 0x16c) + 0x27) * 0x21c,
		    g_773d75);
		if (left >= *(int*) (itm + 0x1b8)) {
			left = *(int*) (itm + 0x1b8);
		}
	}
	if (n <= 0) {
		goto done;
	}
	pi = (int*) (a + 0xc4);
	ps = (unsigned short*) (a + 0xd6);
	cnt = n;
	do {
		if (ps[0] == 0 || pi[0] != *(int*) (pktB + 1)) {
			goto i2advance;
		}
		if (((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) pktB].category == '\n') {
			e2 = gm_FindCityItemHolder(ps[0]);
		} else {
			e2 = fcn_00502cd0(*(int*) (pktB + 0x5d), 2, 6, 0, 0x2a);
			if (e2 == 0) {
				e2 = fcn_00502cd0(*(int*) (pktB + 0x5d), 2, 6,
				    0, 0x116);
			}
		}
		if (e2 == 0) {
			goto i2next;
		}
		r2 = fcn_00502cd0(*(int*) (e2 + 0x14), 1, 0, ps[0]);
		if (r2 == 0) {
			goto i2advance;
		}
		if (((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) pktB].category != '\n') {
			amt = (int) (gm_GetSeasonPrice(*(unsigned short*) r2, g_773d75)
			    * *(float*) (pktB + 0x49));
		} else {
			amt = (int) (gm_GetSeasonPrice(*(unsigned short*) r2, g_773d75)
			    * 1.1);
		}
		lim = pi[6];
		t = gm_GetStorageSlotCapacity(e2, *(unsigned short*) r2);
		cand = (unsigned int) (t * *(int*) (r2 + 0x1c)) >> 2;
		cand = gm_GetMsgField(e2, r2) - cand;
		if ((unsigned int) lim >= (unsigned int) cand) {
			t = gm_GetStorageSlotCapacity(e2, *(unsigned short*) r2);
			cand = (unsigned int) (t * *(int*) (r2 + 0x1c)) >> 2;
			lim = gm_GetMsgField(e2, r2) - cand;
		}
		t = left / amt;
		m = lim < t ? lim : t;
		m = m < 0 ? 0 : m;
		if (m != 0) {
			*(int*) (a + 0xe8) = cm_SendSellObjekt(*(int*) (q + 2),
			    *(int*) (e2 + 2), *(unsigned short*) r2, m, g_773d75, amt);
		}
		if (itm != 0 && *(int*) (itm + 0x16c) != 0) {
			sprintf(buf, (char*) 0x6a7d00, itm + 0x30,
			    *(int*) (itm + 0x16c) + 5, amt * m, left, m,
			    (int) (((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(unsigned short*) r2]) + 1));
		}
		left -= amt * m;
		if (itm != 0) {
			*(int*) (itm + 0x1b8) = *(int*) (itm + 0x1b8) - amt * m;
		}
i2next:
		if (m != 0 || *(char*) (a + 0xf0) == 0) {
			ps[0] = 0;
			pi[0] = -1;
		} else {
			flag |= 1;
		}
i2advance:
		ps++;
		pi++;
	} while (--cnt != 0);
done:
	if (*(char*) (a + 0xf0) != 0 && flag != 0) {
		if ((unsigned short) gm_GameTime.b >= 0x14) {
			gm_AddTime(a + 0x52, 0, 5, 0);
			*(char*) (a + 0xf0) = 0;
			return;
		}
		gm_AddTime(a + 0x52, 0, 0x1e, 0);
		*(char*) (a + 0xf0) = (char) (*(char*) (a + 0xf0) - 1);
		return;
	}
	*(int*) (a + 0xb0) = -1;
	i = 0;
	pi = (int*) (a + 0xb8);
	ps = (unsigned short*) (a + 0xd0);
	while (i < n) {
		if (ps[0] != 0) {
			*(int*) (a + 0xb0) = pi[0];
		}
		i++;
		ps++;
		pi++;
		if (*(int*) (a + 0xb0) != -1) {
			break;
		}
	}
	if (*(int*) (a + 0xb0) == -1) {
		i = 0;
		pi = (int*) (a + 0xc4);
		ps = (unsigned short*) (a + 0xd6);
		while (i < n) {
			if (ps[0] != 0) {
				*(int*) (a + 0xb0) = pi[0];
			}
			i++;
			ps++;
			pi++;
			if (*(int*) (a + 0xb0) != -1) {
				break;
			}
		}
		if (*(int*) (a + 0xb0) == -1) {
			tmp = 0;
			gm_ResolveEntityById(0, (void**) &tmp, 0, *(int*) (a + 0x10));
			*(int*) (a + 0xb0) = *(int*) (tmp + 1);
		}
	}
	if (*(char*) (a + 0xf1) != 0) {
		gm_AddTime(a + 0x52, 1, 0x1e, 0);
		return;
	}
	memset(&msg, 0, sizeof(msg));
	msg.when = gm_GameTime;
	msg.kind = 0x0f;
	msg.f0c = -1;
	msg.code = 2;
	msg.owner = *(int*) (g_7f4ca0 + 4 + *(unsigned short*) (a + 8) * 0x21c);
	msg.f58 = *(int*) (pktA + 2);
	msg.f5c = *(int*) (pktB + 1);
	msg.f60 = *(int*) (a + 0xb0);
	msg.fa0 = *(int*) (a + 4);
	if (msg.f5c == msg.f60) {
		gm_AddTime(a + 0x52, 0, 5, 0);
		return;
	}
	*(int*) (a + 0xec) = cm_SendCopyEntityData((char*) &msg);
	gm_AddTime(a + 0x52, 0, 10, 0);
}
