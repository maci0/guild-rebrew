/*
 * Collects the goods a building needs into the object record table
 * (g_100d0c0), prices them, and ranks them.
 */
#include <string.h>
#include "Develop/DieGildeAddOn/game/goods_plan.h"

/* g_100d0c0: 0x58-byte object records. */
#pragma pack(push, 1)
#include "production_goods.h"






















/* Statistics block filled by fcn_0050de80. */
typedef struct Stats {
	int x0;
	int n;
	int x8[16];
	unsigned short x48[16];
	int x68[16];
	int xa8;
	int xac;
	int xb0;
	char* xb4;
} Stats;

/* g_868050: 0x24d-byte level records. */
typedef struct Lvl {
	unsigned char kind;   /* 0x000 */
	char pad1[0x24c];
} Lvl;
#pragma pack(pop)

 
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* lpObjektePROT;
extern char* lpGebaeudePROT;
extern float g_664124;

char* __cdecl fcn_00502cd0(int, int, int, ...);
char* __cdecl gm_NextEntityQueryMatch(void);
char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_FindRecordById(int);
int __cdecl gm_GetMsgField(char*, char*);
int __cdecl gm_eval_SlotVoll(char*, int, int);
int __cdecl fcn_0050de80(char*, Stats*);
int __cdecl fcn_0050c710(char*, int, int);
void __cdecl fcn_004c52d0(int, int);
void __cdecl fcn_00486500(PRODUCTION_GOODS_RECORD*);

/* ADDRESS: GOLDTL 0x004849b0 */
void __cdecl fcn_004849b0(char* a, char* prod, char* craft)
{
	Stats st;
	PRODUCTION_GOODS_RECORD tmp;
	char* p;
	char* e;
	char* r;
	GOODS_PLAN_ENTRY* segp;
	int i;
	int j;
	int k;
	int type;
	int found;
	int x;
	unsigned short id;
	unsigned char kind;

	g_100b0ac = 0;
	p = fcn_00502cd0(*(int*) (prod + 0x14), 1, 5);
	while (p != 0) {
		if (*(int*) (p + 0xe)  > 1 && g_100b0ac < 0x20) {
			g_100d0c0[g_100b0ac].goods_id = *(unsigned short*) p;
			for (j = 0; j != 4; j++) {
				g_100d0c0[g_100b0ac].building_indices[j] = -1;
			}
			g_100d0c0[g_100b0ac].min_1 = 0;
			g_100d0c0[g_100b0ac].min_2 = 0;
			g_100d0c0[g_100b0ac].unk_48 = 0x21;
			g_100d0c0[g_100b0ac].value = -1.0e10f;
			g_100d0c0[g_100b0ac].amount = 0;
			g_100d0c0[g_100b0ac].unk_3c = 0;
			g_100d0c0[g_100b0ac].unk_40 = 0;
			g_100d0c0[g_100b0ac].unk_44 = 0;
			g_100d0c0[g_100b0ac].flags = 0;
			g_100b0ac++;
		}
		p = gm_NextEntityQueryMatch();
	}

	ai_ResourceCount = 0;
	for (k = 0; k < g_100b0ac; k++) {
		for (j = 0; j != 4; j++) {
			id = *(unsigned short*) (lpObjektePROT +
			                         g_100d0c0[k].goods_id * 0x41 + 0x2e +
			                         j * 2);
			if (id == 0) {
				continue;
			}
			if (ai_ResourceCount >= 1) {
				for (i = 0; i < ai_ResourceCount; i++) {
					if (g_100b0c0[i].goods_id == id) {
						g_100d0c0[k].building_indices[j] = i;
						break;
					}
				}
			}
			if (g_100d0c0[k].building_indices[j] != -1) {
				continue;
			}
			if (ai_ResourceCount >= 0x80) {
				return;
			}
			segp = &g_100b0c0[ai_ResourceCount];
			segp->goods_id = id;
			segp->parent_index = -1;
			segp->supplier = 0;
			segp->unk_10 = 0;
			segp->requested = 0;
			segp->unk_18 = 0;
			segp->price = -1.0e10f;
			segp->allocated = 0;
			g_100d0c0[k].building_indices[j] = ai_ResourceCount;
			segp->stock = 0;
			ai_ResourceCount++;
			segp->state_30 = 0x21;
			segp->flags = 0;
		}
	}

	kind = ((Lvl*) lpGebaeudePROT)[*(unsigned char*) *(char**) (a + 0x16c)].kind;
	if (kind == 0xe || kind == 8 || kind == 0x20) {
		if (ai_ResourceCount > 0) {
			for (k = 0; k < ai_ResourceCount; k++) {
				type = g_100b0c0[k].goods_id;
				if (type == 0x1c7 || type == 0x1c4 ||
				    type == 0x1c5 || type == 0x1c6 ||
				    type == 0x2af || type == 0x2b0) {
					g_100b0c0[k].flags |= 0x24;
					for (i = 0; i < g_100b0ac; i++) {
						if (g_100d0c0[i].goods_id == type) {
							g_100d0c0[i].flags |= 0x24;
							break;
						}
					}
					if (i >= g_100b0ac) {
						g_100d0c0[g_100b0ac].goods_id = type;
						for (j = 0; j != 4; j++) {
							g_100d0c0[g_100b0ac].building_indices[j] = -1;
						}
						g_100d0c0[g_100b0ac].min_1 = 0;
						g_100d0c0[g_100b0ac].min_2 = 0;
						g_100d0c0[g_100b0ac].value = -1.0e10f;
						g_100d0c0[g_100b0ac].amount = 0;
						g_100d0c0[g_100b0ac].unk_3c = 0;
						g_100d0c0[g_100b0ac].unk_40 = 0;
						g_100d0c0[g_100b0ac].unk_44 = 0;
						g_100d0c0[g_100b0ac].unk_48 = 0x21;
						g_100d0c0[g_100b0ac].flags = 0x24;
						g_100b0ac = g_100b0ac + 1;
					}
				} else if (type == 0x1c1 || type == 0x1c2 ||
				           type == 0x1c3) {
					g_100b0c0[k].flags |= 0x204;
					for (i = 0; i < g_100b0ac; i++) {
						if (g_100d0c0[i].goods_id == type) {
							g_100d0c0[i].flags |= 0x204;
							break;
						}
					}
					if (i >= g_100b0ac) {
						g_100d0c0[g_100b0ac].goods_id = type;
						for (j = 0; j != 4; j++) {
							g_100d0c0[g_100b0ac].building_indices[j] = -1;
						}
						g_100d0c0[g_100b0ac].min_1 = 0;
						g_100d0c0[g_100b0ac].min_2 = 0;
						g_100d0c0[g_100b0ac].value = -1.0e10f;
						g_100d0c0[g_100b0ac].amount = 0;
						g_100d0c0[g_100b0ac].unk_3c = 0;
						g_100d0c0[g_100b0ac].unk_40 = 0;
						g_100d0c0[g_100b0ac].unk_44 = 0;
						g_100d0c0[g_100b0ac].unk_48 = 0x21;
						g_100d0c0[g_100b0ac].flags = 0x204;
						g_100b0ac = g_100b0ac + 1;
					}
				}
			}
		}
	}

	kind = ((Lvl*) lpGebaeudePROT)[*(unsigned char*) *(char**) (a + 0x16c)].kind;
	if ((kind == 0x1d || kind == 0x1f) && ai_ResourceCount > 0) {
		for (k = 0; k < ai_ResourceCount; k++) {
			type = g_100b0c0[k].goods_id;
			if (type == 0x225 || type == 0x226 || type == 0x227 ||
			    type == 0x293 || type == 0x294 || type == 0x295) {
				g_100b0c0[k].flags |= 0x404;
				for (i = 0; i < g_100b0ac; i++) {
					if (g_100d0c0[i].goods_id == type) {
						g_100d0c0[i].flags |= 0x404;
						break;
					}
				}
				if (i >= g_100b0ac) {
					g_100d0c0[g_100b0ac].goods_id = type;
					for (j = 0; j != 4; j++) {
						g_100d0c0[g_100b0ac].building_indices[j] = -1;
					}
					g_100d0c0[g_100b0ac].min_1 = 0;
					g_100d0c0[g_100b0ac].min_2 = 0;
					g_100d0c0[g_100b0ac].value = -1.0e10f;
					g_100d0c0[g_100b0ac].amount = 0;
					g_100d0c0[g_100b0ac].unk_3c = 0;
					g_100d0c0[g_100b0ac].unk_40 = 0;
					g_100d0c0[g_100b0ac].unk_44 = 0;
					g_100d0c0[g_100b0ac].unk_48 = 0x21;
					g_100d0c0[g_100b0ac].flags = 0x404;
					g_100b0ac = g_100b0ac + 1;
				}
			}
		}
	}

	for (k = 0; k < ai_ResourceCount; k++) {
		if (g_100b0ac > 0) {
			for (i = 0; i < g_100b0ac; i++) {
				if (g_100d0c0[i].goods_id == g_100b0c0[k].goods_id) {
					break;
				}
			}
			if (i < g_100b0ac) {
				g_100b0c0[k].parent_index = i;
			}
		}
	}

	for (i = 0; i < g_100b0ac; i++) {
		p = fcn_00502cd0(*(int*) (craft + 0x14), 1, 0, g_100d0c0[i].goods_id);
		if (p == 0) {
			g_100d0c0[i].unk_3c = 0;
		} else {
			g_100d0c0[i].unk_3c = gm_GetMsgField(craft, p);
		}
		g_100d0c0[i].unk_40 =
		    gm_eval_SlotVoll(craft, g_100d0c0[i].goods_id, 0xf4240);
	}

	for (k = 0; k < ai_ResourceCount; k++) {
		p = fcn_00502cd0(*(int*) (craft + 0x14), 1, 0, g_100b0c0[k].goods_id);
		if (p == 0) {
			g_100b0c0[k].stock = 0;
		} else {
			g_100b0c0[k].stock = gm_GetMsgField(craft, p);
			if (g_100b0c0[k].stock == 0) {
				fcn_004c52d0(*(int*) (craft + 2), g_100b0c0[k].goods_id);
			}
		}
		g_100b0c0[k].capacity =
		    gm_eval_SlotVoll(craft, g_100b0c0[k].goods_id, 0xf4240);
	}

	for (e = fcn_005463a0(2, 0, 0xb, 3,
	                     *(int*) (*(char**) (a + 0x16c) + 1));
	     e != 0;
	     e = he_fn_Handlung()) {
		r = gm_FindRecordById(*(int*) (e + 0xac));
		if (r == 0) {
			continue;
		}
		fcn_0050de80(r, &st);
		for (i = 0; i < st.x0; i++) {
			id = st.x48[i];
			if (id == 0) {
				continue;
			}
			found = 0;
			for (j = 0; found == 0 && j < 3; j++) {
				if (((unsigned short*) (e + 0xd0))[j] == id) {
					found = 1;
				}
			}
			if (found != 0) {
				continue;
			}
			for (j = 0; j < g_100b0ac; j++) {
				if (id == g_100d0c0[j].goods_id) {
					g_100d0c0[j].amount += st.x68[i];
				}
			}
			for (j = 0; j < ai_ResourceCount; j++) {
				if (id == g_100b0c0[j].goods_id) {
					g_100b0c0[j].allocated += st.x68[i];
				}
			}
		}
		for (j = 0; j < 3; j++) {
			id = ((unsigned short*) (e + 0xd6))[j];
			if (id == 0) {
				continue;
			}
			for (i = 0; i < g_100b0ac; i++) {
				if (id == g_100d0c0[i].goods_id) {
					g_100d0c0[i].amount += ((int*) (e + 0xdc))[j];
				}
			}
			for (i = 0; i < ai_ResourceCount; i++) {
				if (id == g_100b0c0[i].goods_id) {
					g_100b0c0[i].allocated += ((int*) (e + 0xdc))[j];
				}
			}
		}
	}

	kind = ((Lvl*) lpGebaeudePROT)[*(unsigned char*) *(char**) (a + 0x16c)].kind;
	if (kind == 8 || kind == 0xe) {
		for (e = fcn_005463a0(2, 0, 0x14, 3,
		                     *(int*) (*(char**) (a + 0x16c) + 1));
		     e != 0;
		     e = he_fn_Handlung()) {
			for (k = 0; k < ai_ResourceCount; k++) {
				if (g_100b0c0[k].goods_id !=
				    (int) *(unsigned short*) (e + 0xae)) {
					continue;
				}
				x = fcn_0050c710(*(char**) (a + 0x16c), 0xb, 1);
				g_100b0c0[k].allocated =
				    (int) (((float) x * 0.01f + g_6628a0) *
				               g_664124 +
				           (float) g_100b0c0[k].allocated);
			}
		}
	}

	kind = ((Lvl*) lpGebaeudePROT)[*(unsigned char*) *(char**) (a + 0x16c)].kind;
	if (kind == 8) {
		for (e = fcn_005463a0(2, 0, 0x15, 3,
		                     *(int*) (*(char**) (a + 0x16c) + 1));
		     e != 0;
		     e = he_fn_Handlung()) {
			for (k = 0; k < ai_ResourceCount; k++) {
				if (g_100b0c0[k].goods_id !=
				    (int) *(unsigned short*) (e + 0xae)) {
					continue;
				}
				x = fcn_0050c710(*(char**) (a + 0x16c), 0xb, 1);
				g_100b0c0[k].allocated =
				    (int) (((float) x * 0.01f + g_6628a0) *
				               g_664124 +
				           (float) g_100b0c0[k].allocated);
			}
		}
	}

	kind = ((Lvl*) lpGebaeudePROT)[*(unsigned char*) *(char**) (a + 0x16c)].kind;
	if (kind == 0x1d || kind == 0x1f) {
		for (e = fcn_005463a0(2, 0, 0x8c, 3,
		                     *(int*) (*(char**) (a + 0x16c) + 1));
		     e != 0;
		     e = he_fn_Handlung()) {
			for (k = 0; k < ai_ResourceCount; k++) {
				if (g_100b0c0[k].goods_id !=
				    (int) *(unsigned short*) (e + 0xac)) {
					continue;
				}
				x = fcn_0050c710(*(char**) (a + 0x16c), 0xb, 1);
				g_100b0c0[k].allocated =
				    (int) (((float) x * 0.01f + g_6628a0) *
				               g_664124 +
				           (float) g_100b0c0[k].allocated);
			}
		}
	}

	for (i = 0; i < g_100b0ac; i++) {
		fcn_00486500(&g_100d0c0[i]);
	}

	for (i = 0; i < g_100b0ac; i++) {
		for (j = i; j < g_100b0ac; j++) {
			if (g_100d0c0[i].slope < g_100d0c0[j].slope) {
				tmp = g_100d0c0[i];
				g_100d0c0[i] = g_100d0c0[j];
				g_100d0c0[j] = tmp;
			}
		}
	}

	for (k = 0; k < ai_ResourceCount; k++) {
		if (g_100b0c0[k].parent_index != -1) {
			for (j = 0; j < g_100b0ac; j++) {
				if (g_100b0c0[k].goods_id == g_100d0c0[j].goods_id) {
					g_100b0c0[k].flags |= 0x40;
					g_100d0c0[j].flags |= 0x40;
					g_100b0c0[k].parent_index = j;
				}
			}
		}
	}

	for (i = 0; i < g_100b0ac; i++) {
		g_100d0c0[i].unk_48 = i;
	}
}
unsigned char _dpad_100af80[320];
unsigned char _dpad_100b0c0[8192];
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_100d0c0[2884];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_100d0c4[48];
unsigned char _dpad_100d0f8[20];
unsigned char _dpad_100d114[2732];
#endif
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_100d0c4[48];
unsigned char _dpad_100d0f8[20];
unsigned char _dpad_100d114[2732];
#endif
