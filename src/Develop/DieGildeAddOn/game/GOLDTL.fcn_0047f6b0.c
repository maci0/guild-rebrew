#include <string.h>
#include "Develop/DieGildeAddOn/game/goods_plan.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
/* g_100d0c0: 0x58-byte object records.  The four dwords at +4 select the
 * building instances; +0x54 carries the state flags. */
#pragma pack(push, 1)
#include "production_goods.h"





















/* g_7f4ca0: 0x21c-byte map records. */
typedef struct Ent {
	unsigned short id;    /* 0x000 */
	unsigned char f2;     /* 0x002 */
	char pad3[5];
	unsigned char f8;     /* 0x008 */
	char pad9[0x15c];
	unsigned char f165;   /* 0x165 */
	char pad166[6];
	int f16c;             /* 0x16c */
	char pad170[0xc];
	char* host;           /* 0x17c */
	char pad180[4];
	int f184;             /* 0x184 */
	char pad188[0x94];
} Ent;

/* g_868050: 0x24d-byte level records. */
typedef struct Lvl {
	unsigned char kind;   /* 0x000 */
	char pad1[0x246];
	unsigned char level;  /* 0x247 */
	char pad248[5];
} Lvl;

/* lpObjektePROT: 0x41-byte item definitions. */
typedef struct ItemDef {
	unsigned char kind;   /* 0x00 */
	char pad1[0x25];
	unsigned short f26;   /* 0x26 */
	char pad28[0xe];
	unsigned short f36;   /* 0x36 */
	char pad38[9];
} ItemDef;

/* Scheduler state handed to fcn_00487f90. */
typedef struct Msg {
	int kind;             /* 0x00 */
	char* self;           /* 0x04 */
	char* rec;            /* 0x08 */
	char* p0c;            /* 0x0c */
	char* p10;            /* 0x10 */
	int want;             /* 0x14 */
	int avail;            /* 0x18 */
	int sent;             /* 0x1c */
	int total;            /* 0x20 */
} Msg;
#pragma pack(pop)

 
extern Ent g_7f4ca0[];
extern unsigned char* lpGebaeudePROT;
extern char* lpObjektePROT;
extern char g_7f4ca4[];
extern char gm_GameTime[];
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern int g_100b0ac;
extern int ai_ResourceCount;
extern int g_100dc20;
extern int g_100dc34;

char* __cdecl fcn_00502cd0(int, int, int, ...);
char* __cdecl gm_NextEntityQueryMatch(void);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
char* __cdecl plt_FindPlantInfo(int);
void* __cdecl gm_FindCityItemHolder(int);
void __cdecl fcn_004849b0(char*, char*, char*);
int __cdecl fcn_00486640(char*, int*, int);
void __cdecl fcn_004868d0(char*, int*);
void __cdecl fcn_00487000(char*);
void __cdecl fcn_00487470(char*);
void __cdecl fcn_00487970(char*, char*, int);
void __cdecl fcn_00487c00(char*, char*, int);
void __cdecl ai_CancelBlockedActions(char*, int);
void __cdecl fcn_00487f90(int*);
void __cdecl ai_MeisterCollectTrans(char*);
void __cdecl ai_MeisterTrade(char*, char*);
void __cdecl fcn_0047e220(char*);
void __cdecl cm_SendCopyEntityData(char*);
void __cdecl fcn_00529160(char*, int, int, int);
void __cdecl fcn_004c5aa0(int, int, int, int, int, int);
void* __cdecl gm_eval_SlotVoll(char*, int, int);
int __cdecl init_AllocateGebaeudeSceneSlot(char*);
int __cdecl fcn_005b1e40(int);
int __cdecl plt_CheckZoneAvailability(int, int, int, int);
int __cdecl gm_RandomMod(int);
/* ADDRESS: GOLDTL 0x0047f6b0 */
int __cdecl fcn_0047f6b0(char* a)
{
	Msg st;
	char* t1;
	int* p2;
	int i;
	char* t3;
	int t;
	int flag;
	char* h;
	char* q;
	int j;
	int n;
	int v;
	char* t2;

	t1 = fcn_00502cd0(*(int*) (*(char**) (a + 0x16c) + 0x5d), 2, 6, 0, 0xff);
	if (t1 == 0) {
		return 0;
	}
	t2 = fcn_00502cd0(*(int*) (*(char**) (a + 0x16c) + 0x5d), 2, 6, 0, 0x2a);
	if (t2 == 0) {
		return 0;
	}
	t3 = fcn_00502cd0(*(int*) (*(char**) (a + 0x16c) + 0x5d), 1, 0, 0xfe);
	if (t3 == 0) {
		return 0;
	}
	fcn_004849b0(a, t1, t2);

	if (g_100b0ac > 0) {
		p2 = (int*) &g_100d0c0[0].building_indices[0];
		for (n = g_100b0ac; n != 0; n--) {
			q = (char*) p2;
			for (i = 4; i != 0; i--) {
				if (*(int*) q >= 0 && g_100b0c0[*(int*) q].parent_index >= 0) {
					g_100d0c0[g_100b0c0[*(int*) q].parent_index].flags |= 4;
					for (j = 0; j < ai_ResourceCount; j++) {
						if (g_100d0c0[g_100b0c0[*(int*) q].parent_index].goods_id
						    == g_100b0c0[j].goods_id) {
							g_100b0c0[j].flags |= 4;
						}
					}
				}
				q += 4;
			}
			p2 += 0x16;
		}
	}

	fcn_00487000(a);
	fcn_00487970(t2, a, 0xa);
	fcn_00487c00(t2, a, 0x19);
	fcn_00487470(a);
	if ((*(unsigned char*) (a + 0x1c8) & 0x10) == 0
	    && ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) (*(char**) (a + 0x16c))].category != 0xb) {
		q = fcn_00502cd0(*(int*) (t1 + 0x14), 1, 4, 0x17);
		if (q != 0) {
			while (*(int*) (q + 0xe) != 1) {
				q = gm_NextEntityQueryMatch();
				if (q == 0) {
					*(int*) (a + 0x1c8) |= 0x10;
					goto done_m;
				}
			}
			{
				char m[0xf8];
				memset(m, 0, sizeof(m));
				h = *(char**) (a + 0x16c);
				m[4] = 9;
				*(int*) (m + 8) = *(int*) (g_7f4ca4 +
				                           *(unsigned short*) (h + 0x27) * 0x21c);
				*(int*) (m + 0xc) = *(int*) (h + 1);
				*(int*) (m + 0x10) = 0;
				*(int*) (m + 0x14) = 0;
				*(int*) (m + 0x28) = *(int*) &gm_GameTime;
				*(int*) (m + 0x2c) = g_7f4c04;
				*(int*) (m + 0x30) = g_7f4c08;
				*(short*) (m + 0x34) = g_7f4c0c;
				m[0x36] = 1;
				*(int*) (m + 0x58) = *(int*) (h + 1);
				*(int*) (m + 0x5c) = *(int*) (t1 + 2);
				*(int*) (m + 0x60) = *(int*) (t3 + 2);
				cm_SendCopyEntityData(m);
			}
		}
		*(int*) (a + 0x1c8) |= 0x10;
done_m:
		;
	} else {
		q = t1;
	}

	flag = 0;
	{
		char* s;
		s = he_StartHandlungSearch(2, 0, 9, 3, *(int*) (*(char**) (a + 0x16c) + 1));
		if (s != 0) {
			if (*(int*) (a + 0x17c) != (int) s) {
				fcn_00529160(*(char**) (a + 0x16c), 0, *(unsigned short*) a, (int) s);
			}
			flag = 1;
		}
	}
	h = *(char**) (a + 0x16c);
	if (g_7f4ca0[*(unsigned short*) (h + 0x27)].f2 == 6) {
		v = fcn_005b1e40((int) h);
		if (q != 0) {
			for (i = 0; i < 0x20; i++) {
				if (g_100d0c0[i].goods_id == v) {
					goto found;
				}
			}
		}
	}
	goto scan;

found:
	if ((int) *(unsigned char*) (t2 + 0x1c) < g_100d0c0[i].min_1) {
		goto scan;
	}
	if ((int) *(unsigned char*) (t2 + 0x1d) < g_100d0c0[i].min_2) {
		goto scan;
	}
	if (g_100d0c0[i].unk_40 < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[i].goods_id].value_036) {
		goto scan;
	}
	v = (int) gm_FindCityItemHolder(g_100d0c0[i].goods_id);
	if (v == 0) {
		goto scan;
	}
	t = (int) gm_eval_SlotVoll((char*) v, g_100d0c0[i].goods_id, 0xf4240);
	if (t < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[i].goods_id].value_036 + g_100d0c0[i].unk_3c) {
		goto scan;
	}
	if (((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[i].goods_id].kind == 0x17) {
		q = fcn_00502cd0(*(int*) (t3 + 0x14), 1, 0, g_100d0c0[i].goods_id);
		if (q == 0) {
			goto scan;
		}
		if (*(int*) (q + 0xe) < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[i].goods_id].value_036) {
			goto scan;
		}
		g_100d0c0[i].flags |= 8;
		fcn_004868d0(a, (int*) &g_100d0c0[i]);
	} else if (fcn_00486640(a, (int*) &g_100d0c0[i], 1)) {
		g_100d0c0[i].flags |= 8;
		fcn_004868d0(a, (int*) &g_100d0c0[i]);
	} else if (fcn_00486640(a, (int*) &g_100d0c0[i], 0)) {
		fcn_004868d0(a, (int*) &g_100d0c0[i]);
	} else {
		goto scan;
	}
	goto after;

scan:
	for (i = 0; i < g_100b0ac; i++) {
		if (g_100d0c0[i].flags & 4) {
			continue;
		}
		if ((int) *(unsigned char*) (t2 + 0x1c) < g_100d0c0[i].min_1) {
			continue;
		}
		if ((int) *(unsigned char*) (t2 + 0x1d) < g_100d0c0[i].min_2) {
			continue;
		}
		if (g_100d0c0[i].unk_40 < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[i].goods_id].value_036) {
			continue;
		}
		v = (int) gm_FindCityItemHolder(g_100d0c0[i].goods_id);
		if (v == 0) {
			continue;
		}
		t = (int) gm_eval_SlotVoll((char*) v, g_100d0c0[i].goods_id, 0xf4240);
		if (t < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[i].goods_id].value_036 + g_100d0c0[i].unk_3c) {
			continue;
		}
		if (((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[i].goods_id].kind == 0x17) {
			q = fcn_00502cd0(*(int*) (t3 + 0x14), 1, 0, g_100d0c0[i].goods_id);
			if (q == 0) {
				continue;
			}
			if (*(int*) (q + 0xe) < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[i].goods_id].value_036) {
				continue;
			}
			g_100d0c0[i].flags |= 8;
			fcn_004868d0(a, (int*) &g_100d0c0[i]);
			goto after;
		} else if (fcn_00486640(a, (int*) &g_100d0c0[i], 1)) {
			g_100d0c0[i].flags |= 8;
			fcn_004868d0(a, (int*) &g_100d0c0[i]);
			goto after;
		}
	}

after:
	for (i = 0; i < g_100b0ac; i++) {
		if (g_100d0c0[i].flags & 8) {
			break;
		}
		if (g_100d0c0[i].flags & 4) {
			continue;
		}
		if ((int) *(unsigned char*) (t2 + 0x1c) < g_100d0c0[i].min_1) {
			continue;
		}
		if ((int) *(unsigned char*) (t2 + 0x1d) < g_100d0c0[i].min_2) {
			continue;
		}
		if (g_100d0c0[i].unk_40 < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[i].goods_id].value_036) {
			continue;
		}
		v = (int) gm_FindCityItemHolder(g_100d0c0[i].goods_id);
		if (v == 0) {
			continue;
		}
		t = (int) gm_eval_SlotVoll((char*) v, g_100d0c0[i].goods_id, 0xf4240);
		if (t < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[i].goods_id].value_036 + g_100d0c0[i].unk_3c) {
			continue;
		}
		if (((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[i].goods_id].kind == 0x17) {
			g_100d0c0[i].flags |= 0x10;
			break;
		}
		if (fcn_00486640(a, (int*) &g_100d0c0[i], 0)) {
			fcn_004868d0(a, (int*) &g_100d0c0[i]);
			break;
		}
	}

	for (i = 0; i < g_100b0ac; i++) {
		if ((g_100d0c0[i].flags & 8) == 0) {
			continue;
		}
		if (((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[i].goods_id].kind == 0x17) {
			if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) (*(char**) (a + 0x16c))].category == 0xb) {
				g_100d0c0[i].flags |= 0x10;
			} else {
				q = fcn_00502cd0(*(int*) (t3 + 0x14), 1, 0, g_100d0c0[i].goods_id);
				if (q == 0
				    || *(int*) (q + 0xe) < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[i].goods_id].value_036) {
					g_100d0c0[i].flags =
					    (g_100d0c0[i].flags & ~8) | 0x10;
				}
			}
		} else {
			for (j = 0; j != 4; j++) {
				if (g_100b0c0[g_100d0c0[i].building_indices[j]].stock
				    < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[i].goods_id].ingredient_amounts[0]) {
					g_100d0c0[i].flags &= ~8;
				}
			}
		}
	}

	ai_CancelBlockedActions(a, 4);
	ai_CancelBlockedActions(a, 8);
	ai_CancelBlockedActions(a, 3);

	st.avail = 0;
	for (j = 0; j < 0x300; j++) {
		if (g_7f4ca0[j].f8 > 0 && g_7f4ca0[j].id != 0xffff
		    && g_7f4ca0[j].f2 != 0xa
		    && g_7f4ca0[j].f16c == *(int*) (a + 0x16c)
		    && g_7f4ca0[j].f165 != 0
		    && g_7f4ca0[j].f184 != 0
		    && *(int*) (g_7f4ca0[j].f184 + 0x2c) == *(int*) (*(char**) (a + 0x16c) + 1)
		    && (g_7f4ca0[j].host == 0 || *(unsigned char*) g_7f4ca0[j].host != 0x28)
		    && !(flag != 0 && (char*) a == (char*) &g_7f4ca0[j])) {
			fcn_00529160(*(char**) (a + 0x16c), 0, g_7f4ca0[j].id, 0);
			st.avail++;
		}
	}
	if (g_100dc20 == *(int*) (a + 0x16c)) {
		g_100dc34 = st.avail;
	}
	st.want = 0;
	{
		int* f;

		f = &g_100d0c0[0].flags;
		for (i = 0; i < g_100b0ac; i++) {
			if (*f & 8) {
				st.want++;
			}
			if (*f & 0x10) {
				if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) (*(char**) (a + 0x16c))].category != 0xb) {
					st.want++;
				}
			}
			f = (int*) ((char*) f + 0x58);
		}
	}
	if (st.want >= st.avail) {
		st.want = st.avail;
	}
	if (st.avail == 0 || st.want == 0) {
		ai_MeisterCollectTrans(a);
		ai_MeisterTrade(a, t2);
		return 0;
	}

	st.p0c = t2;
	st.p10 = t3;
	st.self = a;
	st.total = 0;
	st.sent = 0;
	if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) (*(char**) (a + 0x16c))].category != 0xb) {
		goto ltail;
	}
	if ((unsigned short) g_7f4c04 % 2 == 0) {
		*(int*) (a + 0x1b4) &= ~0x20;
		goto ltail;
	}
	if ((*(int*) (a + 0x1b4) & 0x20) != 0) {
		goto ltail;
	}
	v = init_AllocateGebaeudeSceneSlot(*(char**) (a + 0x16c));
	p2 = *(char**) (0x104336c + v * 0x3dc);
	if (p2 == 0) {
		return 0;
	}
	n = *(int*) (*(char**) (a + 0x16c) + 0x71);
	{
		int ch;
		char* g;

		ch = -1;
		for (i = 0; i < 8; i++) {
			if (strstr((char*) p2 + 0x7e24 + i * 0x40, (char*) 0x67dd10) != 0) {
				ch = i;
			}
		}
		for (i = 0; i < g_100b0ac * 4; i++) {
			j = gm_RandomMod(g_100b0ac) & 0xffff;
			if (((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[j].goods_id].kind == 0x17) {
				break;
			}
		}
		if (((OBJECT_PROTOTYPE*) lpObjektePROT)[g_100d0c0[j].goods_id].kind != 0x17) {
			goto lflag;
		}
		g = plt_FindPlantInfo(g_100d0c0[j].goods_id);
		v = 0;
		for (i = 0; i < *(int*) p2 && v < 4; i++) {
			for (j = 0; v < 4 && j < *(int*) p2; j++) {
				if ((int) *(unsigned char*) (*(int*) ((char*) p2 + 0x14)
				                             + i * *(int*) p2 + j) != ch) {
					continue;
				}
				if (plt_CheckZoneAvailability(n, j, i, *(unsigned char*) (g + 0x42)) == 0) {
					continue;
				}
				fcn_004c5aa0(*(int*) (*(char**) (a + 0x16c) + 1), j, i, *(unsigned short*) g, 0, -1);
				v++;
			}
		}
	}
lflag:
	*(int*) (a + 0x1b4) |= 0x20;

ltail:
	{
		char* rec;

		rec = (char*) &g_100d0c0[0];
		for (i = 0; i < g_100b0ac; i++) {
			if (((PRODUCTION_GOODS_RECORD*) rec)->flags & 0x10) {
				if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) (*(char**)(a + 0x16c))].category != 0xb) {
					st.kind = 8;
					st.rec = rec;
					fcn_00487f90((int*) &st);
				}
			}
			if (((PRODUCTION_GOODS_RECORD*) rec)->flags & 8) {
					if (((OBJECT_PROTOTYPE*) lpObjektePROT)[((PRODUCTION_GOODS_RECORD*) rec)->goods_id].kind == 0x17) {
						st.rec = rec;
						if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) (*(char**)(a + 0x16c))].category == 0xb) {
							st.kind = 0x28;
							fcn_00487f90((int*) &st);
							if (g_100dc20 == *(int*)(a + 0x16c) && *(int*) 0x100dc3c < 4) {
								*(PRODUCTION_GOODS_RECORD*) (0x100ddc0 + *(int*) 0x100dc3c * 0x58) =
								    *(PRODUCTION_GOODS_RECORD*) st.rec;
								*(int*) 0x100dc3c = *(int*) 0x100dc3c + 1;
							}
							goto next_rec;
						} else {
							st.kind = 3;
						}
					} else {
						st.kind = 4;
						st.rec = rec;
					}
					fcn_00487f90((int*) &st);
					if (g_100dc20 == *(int*)(a + 0x16c) && *(int*) 0x100dc3c < 4) {
						*(PRODUCTION_GOODS_RECORD*) (0x100ddc0 + *(int*) 0x100dc3c * 0x58) =
						    *(PRODUCTION_GOODS_RECORD*) st.rec;
						*(int*) 0x100dc3c = *(int*) 0x100dc3c + 1;
					}
				}
next_rec:
			rec += 0x58;
		}
	}

	fcn_0047e220(t2);
	ai_MeisterCollectTrans(a);
	ai_MeisterTrade(a, t2);
	return 0;
}
