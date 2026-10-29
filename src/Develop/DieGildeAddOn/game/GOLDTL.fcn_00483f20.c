#include <string.h>

#pragma intrinsic(memcpy)

/* Entity record handed to the production planner (fields used here only). */
typedef struct {
	char pad0[0x16c];
	int root;			/* +0x16c, production building object */
	char pad170[0x44];
	int flags;			/* +0x1b4 */
	char pad1b8[4];
	unsigned short item;		/* +0x1bc */
} Ent483f20;

/* SIZE 0x58, production entry */
typedef struct {
	int id;				/* +0x00 */
	char pad04[0x18];
	int min1;			/* +0x1c */
	int min2;			/* +0x20 */
	char pad24[0x18];
	int cost;			/* +0x3c */
	int limit;			/* +0x40 */
	char pad44[0x10];
	int flags;			/* +0x54 */
} Prod483f20;

/* SIZE 0x40, resource entry */
typedef struct {
	int id;				/* +0x00 */
	char pad04[0x34];
	int flags;			/* +0x38 */
} Res483f20;

/* Start request handed to fcn_00487f90. */
typedef struct {
	int kind;			/* +0x00 */
	int ent;			/* +0x04 */
	int entry;			/* +0x08 */
} Plan483f20;

extern char* lpObjektePROT;			/* entity type table, entry stride 0x41 */
extern char* g_7f4ca0;			/* slot table, stride 0x21c */
extern Prod483f20* g_100d0c0;		/* production entries */
extern int g_100b0ac;			/* production entry count */
extern Res483f20* g_100b0c4;		/* resource entries */
extern int g_100b0a8;			/* resource entry count */
extern char* g_100b0e8;
extern int g_100dc20;			/* owner production building */
extern int g_100dc34;
extern int g_100dc38;
extern int g_100dc3c;
extern int* g_100dc40;
extern int* g_100dc48;
extern unsigned short g_7f4c04;

void* __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_004849b0(Ent483f20*, void*, void*);
void __cdecl fcn_00487000(Ent483f20*);
void __cdecl fcn_00487970(void*, Ent483f20*, int);
void __cdecl fcn_00487c00(void*, Ent483f20*, int);
void __cdecl fcn_00487470(Ent483f20*);
int __cdecl fcn_00486640(Ent483f20*, Prod483f20*, int);
void __cdecl fcn_004868d0(Ent483f20*, Prod483f20*);
int __cdecl fcn_005b1e40(int);
void* __cdecl fcn_00503d10(int);
int __cdecl gm_eval_SlotVoll(void*, int, int);
int __cdecl gm_RandomMod(int);
void __cdecl fcn_0047e220(void*);
void __cdecl fcn_0047e0e0(Ent483f20*, void*);
void __cdecl fcn_00487e60(Ent483f20*, int);
void __cdecl fcn_00529160(int, int, unsigned short, int);
void __cdecl ai_MeisterCollectTrans(Ent483f20*);
void __cdecl ai_MeisterTrade(Ent483f20*, void*);
void __cdecl fcn_00487f90(Plan483f20*);
int __cdecl wsprintfA(char*, char*, ...);

#define type_entry(id) (lpObjektePROT + (id) * 0x41)
#define slot_at(id) (g_7f4ca0 + (id) * 0x21c)

/* Runs the start preconditions and returns fcn_00486640's answer. */
static __inline int can_start(Ent483f20* e, void* rec, Prod483f20* p, int human)
{
	char* type;
	void* obj;
	int amount;

	if ((p->flags & 0x400) != 0) {
		return 0;
	}
	type = type_entry(p->id);
	if ((*type == 0x17 || *type == 0x25) && p->cost >= 5) {
		return 0;
	}
	if (*(unsigned char*) ((char*) rec + 0x1c) < p->min1) {
		return 0;
	}
	if (*(unsigned char*) ((char*) rec + 0x1d) < p->min2) {
		return 0;
	}
	if (*(unsigned short*) (type + 0x36) > p->limit) {
		return 0;
	}
	obj = fcn_00503d10(p->id);
	if (obj == 0) {
		return 0;
	}
	amount = gm_eval_SlotVoll(obj, p->id, 1000000);
	if (amount < *(unsigned short*) (type + 0x36) + p->cost) {
		return 0;
	}
	return fcn_00486640(e, p, human);
}

static __inline void start_production(Ent483f20* e, Prod483f20* p, char* fmt, char* msg)
{
	p->flags |= 8;
	fcn_004868d0(e, p);
	e->item = (unsigned short) p->id;
	if (fmt != 0) {
		wsprintfA(msg, fmt, type_entry(p->id) + 1);
	}
}

/* ADDRESS: GOLDTL 0x00483f20 */
void __cdecl fcn_00483f20(Ent483f20* e)
{
	Prod483f20* prod;
	Prod483f20* scan;
	Res483f20* res;
	Plan483f20 plan;
	char* slot;
	char* type;
	char* p;
	void* rec;
	void* stk;
	int order[0x20];
	char msg[0x100];
	int count;
	int built;
	int found;
	int i;
	int k;
	int r;
	int t;
	int n;
	int n2;
	int id;
	int owner;

	rec = fcn_00502cd0(*(int*) ((char*) e->root + 0x5d), 2, 6, 0, 0xff);
	if (rec == 0) {
		return;
	}
	stk = fcn_00502cd0(*(int*) ((char*) e->root + 0x5d), 2, 6, 0, 0x2a);
	if (stk == 0) {
		return;
	}
	fcn_004849b0(e, rec, stk);
	fcn_00487000(e);
	fcn_00487970(stk, e, 0x4b);
	fcn_00487c00(stk, e, 0x19);
	fcn_00487470(e);
	owner = e->root;

	if (g_7f4c04 == 8 || g_7f4c04 == 0xd) {
		if ((e->flags & 0x100) == 0) {
			e->item = 0;
			e->flags |= 0x100;
		} else if (e->item != 0) {
			for (i = 0; i < g_100b0ac; i++) {
				if (g_100d0c0[i].id != e->item) {
					continue;
				}
				if (*(unsigned short*) (type_entry(g_100d0c0[i].id) + 0x36) <= g_100d0c0[i].limit &&
				    fcn_00486640(e, &g_100d0c0[i], 1) != 0) {
					start_production(e, &g_100d0c0[i], 0, msg);
					goto after_start;
				}
				break;
			}
		}
	} else {
		found = 0;
		for (i = 0; i < g_100b0ac; i++) {
			if (g_100d0c0[i].id != e->item) {
				continue;
			}
			if (*(unsigned short*) (type_entry(g_100d0c0[i].id) + 0x36) <= g_100d0c0[i].limit &&
			    fcn_00486640(e, &g_100d0c0[i], 1) != 0) {
				start_production(e, &g_100d0c0[i], 0, msg);
				found = 1;
			}
			break;
		}
		e->flags &= ~0x100;
		if (found) {
			goto after_start;
		}
	}

	slot = slot_at(*(unsigned short*) ((char*) e->root + 0x27));
	if (*(char*) (slot + 2) == 6 &&
	    (id = fcn_005b1e40(e->root)) != 0) {
		for (scan = g_100d0c0, i = 0; (char*) scan < (char*) 0x100dbc0; scan = (Prod483f20*) ((char*) scan + 0x58), i++) {
			if (scan->id == id) {
				if (can_start(e, rec, scan, 1)) {
					start_production(e, scan, (char*) 0x67dcc0, msg);
					goto after_start;
				}
				if (fcn_00486640(e, scan, 0) != 0) {
					start_production(e, scan, (char*) 0x67dc88, msg);
					goto after_start;
				}
				break;
			}
		}
	}

	for (i = 0; i < 0x20; i++) {
		order[i] = i;
	}
	for (i = 0; i < 0x20; i++) {
		r = gm_RandomMod(0x20) & 0xffff;
		t = order[i];
		order[i] = order[r];
		order[r] = t;
	}
	count = g_100b0ac;
	if (count > 0) {
		i = 0;
		do {
			prod = &g_100d0c0[order[i]];
			if ((prod->flags & 0x400) == 0 && can_start(e, rec, prod, 1)) {
				start_production(e, prod, (char*) 0x67dc6c, msg);
				goto after_start;
			}
			i++;
		} while (i < count);
	}
	if (count > 0) {
		i = 0;
		do {
			prod = &g_100d0c0[order[i]];
			if ((prod->flags & 0x400) == 0 && can_start(e, rec, prod, 0)) {
				start_production(e, prod, (char*) 0x67dc38, msg);
				goto after_start;
			}
			i++;
		} while (i < count);
	}
	e->item = 0;

after_start:
	fcn_0047e220(rec);
	fcn_0047e0e0(e, rec);

	for (prod = g_100d0c0, i = 0; i < count; i++, prod = &g_100d0c0[i]) {
		if ((prod->flags & 8) != 0) {
			for (k = 0; k < 4; k++) {
				id = *(int*) ((char*) prod + 4 + k * 4);
				if (*(int*) (g_100b0e8 + id * 0x40) <
				    (int) *(unsigned short*) (type_entry(prod->id) + 0x26 + k * 2)) {
					prod->flags &= ~8;
				}
			}
		}
	}
	for (prod = g_100d0c0, i = 0; i < count; i++, prod = &g_100d0c0[i]) {
		if ((prod->flags & 0x400) != 0) {
			prod->flags &= ~8;
		}
	}
	for (res = g_100b0c4, i = 0; i < g_100b0a8; i++, res = (Res483f20*) ((char*) res + 0x40)) {
		if ((res->flags & 0x400) != 0 && (res->flags & 0x10) != 0 && res->id >= 0) {
			g_100d0c0[res->id].flags |= 0x10;
		}
	}

	if (g_100dc20 == e->root && g_100dc38 < 4) {
		i = 0;
		do {
			if (count <= i) {
				break;
			}
			memcpy((char*) 0x100dc60 + g_100dc38 * 0x58, &g_100d0c0[i], 0x58);
			for (k = 0; k < 4; k++) {
				id = *(int*) ((char*) &g_100d0c0[i] + 4 + k * 4);
				if (id >= 0) {
					memcpy((char*) 0x100df20 +
						   (g_100dc40[g_100dc38] + g_100dc38) * 0x40,
					       (char*) 0x100b0c0 + id * 0x40, 0x40);
					g_100dc40[g_100dc38]++;
				}
			}
			g_100dc38++;
			i++;
		} while (g_100dc38 < 4);
	}

	fcn_00487e60(e, 4);

	built = 0;
	for (slot = g_7f4ca0; slot < g_7f4ca0 + 0x600 * 0x21c; slot += 0x21c) {
		if (*(unsigned char*) (slot + 8) == 0) {
			continue;
		}
		if (*(unsigned short*) slot == 0xffff) {
			continue;
		}
		if (*(char*) (slot + 2) == 0x0a) {
			continue;
		}
		if (*(int*) (slot + 0x16c) != e->root) {
			continue;
		}
		if (*(char*) (slot + 0x165) == 0) {
			continue;
		}
		if (*(int*) (slot + 0x184) == 0) {
			continue;
		}
		if (*(int*) (*(int*) (slot + 0x184) + 0x2c) != *(int*) (*(int*) (slot + 0x16c) + 1)) {
			continue;
		}
		p = *(char**) (slot + 0x17c);
		if (p != 0 && *p != 4) {
			continue;
		}
		fcn_00529160(e->root, 0, *(unsigned short*) slot, 0);
		built++;
	}
	if (g_100dc20 == e->root) {
		g_100dc34 = built;
	}

	n = 0;
	for (prod = g_100d0c0, i = 0; i < count; i++, prod = &g_100d0c0[i]) {
		if ((prod->flags & 8) != 0) {
			n++;
		}
		if ((prod->flags & 0x10) != 0) {
			n++;
		}
	}
	if (n >= built) {
		n = built;
	}
	if (built == 0 || n == 0) {
		ai_MeisterCollectTrans(e);
		ai_MeisterTrade(e, rec);
		return;
	}

	for (prod = g_100d0c0, i = 0; i < count; i++, prod = &g_100d0c0[i]) {
		plan.ent = (int) e;
		plan.entry = (int) prod;
		if ((prod->flags & 0x10) != 0) {
			if ((prod->flags & 0x400) == 0) {
				continue;
			}
			plan.kind = 0x8c;
			fcn_00487f90(&plan);
		} else if ((prod->flags & 8) != 0) {
			plan.kind = 4;
			fcn_00487f90(&plan);
		} else {
			continue;
		}
		if (g_100dc20 == e->root && g_100dc3c < 4) {
			memcpy((char*) 0x100ddc0 + g_100dc3c * 0x58, prod, 0x58);
			g_100dc3c++;
		}
	}
	ai_MeisterCollectTrans(e);
	ai_MeisterTrade(e, rec);
}
