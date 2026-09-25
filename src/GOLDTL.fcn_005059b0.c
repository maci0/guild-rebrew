// FUNCTION: GOLD 0x502b60
// SIZE: 720
// FUNCTION: GOLDTL 0x005059b0
// SIZE: 710

#pragma pack(push, 1)
// SIZE 0x65
typedef struct {
	unsigned char type;
	int key;
	char pad5[0x20];
	unsigned short owner;
	unsigned short slot;
	char pad29[0x38];
	int placed;
} Estate;

// SIZE 0xe
typedef struct {
	char pad0[0xa];
	int id;
} Link;

// SIZE 0x1d0
typedef struct Model {
	char pad0[0x34];
	struct Model* body;
	char pad38[0x50];
	int res;
	char pad8c[0x98];
	struct Model** parts;
	char pad128[0xa4];
	int visible;
} Model;

// SIZE 0x43
typedef struct {
	unsigned short kind;
	char pad2[8];
	int id;
	char pade[6];
	Link* link;
	char pad18[4];
	int key;
	char pad20[0x1b];
	Model* model;
	char pad3f[4];
} Obj;
#pragma pack(pop)

// SIZE 0x21c
typedef struct {
	char pad0[2];
	unsigned char type;
	char pad3;
	int id;
	char pad8[0x4c];
	int scene;
	char pad58[0x118];
	Estate* best;
	char pad174[0xa8];
} Entity;

// SIZE 0x170
typedef struct {
	char pad0[0x165];
	char busy;
	char pad166[6];
	int task;
	char pad170[0x44];
	int flags;
} Figure;

extern char* g_868050;
extern Obj* g_868054;
extern char* g_99ec10;
extern Entity g_7f4ca0[];
extern Entity* g_773da8;
extern int g_6b8010;

void __cdecl fcn_005b1c90(int);
void __cdecl fcn_005b1b30(Estate*);
void __cdecl fcn_00505c80(Estate*);
Figure* __cdecl fcn_0050dc90(Estate*);
int __cdecl fcn_00413190(int);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_00402aa0(Model*);
void __cdecl fcn_00442a30(Model*, int, int, int);
void __cdecl fcn_0052dd80(Estate*);
void __cdecl fcn_0052d9d0(Estate*);

void __cdecl fcn_005059b0(Estate* s, unsigned short owner, int slot)
{
	char* rec;
	Entity* e;
	Figure* f;
	Obj* q;
	Model* m;
	int saved;
	int sc;
	int i;

	rec = g_868050 + s->type * 0x24d;
	s->owner = owner;
	if (slot == 0xffff) {
		return;
	}
	if (s->slot != slot) {
		if (s->slot != 0xffff && g_7f4ca0[s->slot].type == 6) {
			fcn_005b1c90(s->key);
		}
		if (g_7f4ca0[slot].type == 6) {
			fcn_005b1b30(s);
		}
	}
	if (s->slot != 0xffff && g_7f4ca0[s->slot].best == s) {
		g_7f4ca0[s->slot].best = 0;
	}
	s->slot = slot;
	if (*rec == 2) {
		fcn_00505c80(s);
		if (*rec == 2) {
			if (g_7f4ca0[s->slot].best == 0 || g_7f4ca0[s->slot].best->type <= s->type) {
				g_7f4ca0[s->slot].best = s;
			}
		}
	}
	if (g_7f4ca0[slot].type == 6 || g_7f4ca0[slot].type == 7) {
		f = fcn_0050dc90(s);
		if (f != 0) {
			f->busy = 0;
			f->flags &= ~1;
			if (*rec == 5 || *rec == 9) {
				f->task = 0;
			}
		}
	}
	q = g_868054;
	for (i = 0x5008; i != 0; i--) {
		if (q->kind != 0 && g_99ec10[q->kind * 0x41] == 0x1d && q->key == s->key) {
			q->id = g_7f4ca0[slot].id;
			if (q->link != 0) {
				q->link->id = g_7f4ca0[slot].id;
			}
			saved = g_6b8010;
			m = q->model;
			if (g_7f4ca0[slot].scene != 0 && (g_7f4ca0[slot].type == 5 || g_7f4ca0[slot].type == 6 || g_7f4ca0[slot].type == 7)) {
				sc = g_7f4ca0[slot].scene - 0x599;
			} else {
				sc = 0;
			}
			fcn_004432d0(fcn_00413190(m->res), 1);
			if (m->body->visible == 0) {
				fcn_00402aa0(m);
			}
			fcn_00442a30(*m->parts, (*m->parts)->visible, sc, 1);
			fcn_004432d0(saved, 1);
		}
		q++;
	}
	e = &g_7f4ca0[slot];
	if (e != g_773da8 && s->placed != 0 && (e->type == 6 || e->type == 7 || e->type == 5)) {
		saved = g_6b8010;
		fcn_004432d0(0, 1);
		fcn_0052dd80(s);
		fcn_0052d9d0(s);
		fcn_004432d0(saved, 1);
		return;
	}
	saved = g_6b8010;
	fcn_004432d0(0, 1);
	fcn_0052dd80(s);
	fcn_004432d0(saved, 1);
}
