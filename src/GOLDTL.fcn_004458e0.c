// SIZE 0xc
typedef struct {
	float x;
	float y;
	float z;
} Vec3;

// SIZE 0x10
typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec4;

// SIZE 0x40
typedef struct {
	float m[4][4];
} Mat;

// SIZE 0x38
typedef struct {
	char p0[0xc];
	char xc[0x2c];
} Slot;

typedef struct Ent Ent;

// SIZE 0x21c
struct Ent {
	char p0[0x4c];
	Vec3 pos;
	char p58[0x2c];
	Vec3 x84;
	char p90[0x158];
	Slot* slots;
	char p1ec[8];
	Ent* next;
	char p1f8[8];
	Ent* child;
	char p204[0x14];
	int kind;
};

int __cdecl fcn_00445600(Ent*, int, Ent*, int);
void __cdecl fcn_00455350(Ent*, void*, Vec4*);
void __cdecl fcn_00438cb0(Ent*, void*);
void __cdecl fcn_004557c0(Ent*, int, int, Mat*);
void __cdecl fcn_0043a0a0(Ent*);
void __cdecl fcn_00439aa0(Ent*);
void __cdecl fcn_00439c00(Ent*, Ent*);
void __cdecl fcn_004458a0(Ent*, Vec4*, Mat*);
void __cdecl fcn_00445760(Ent*, Vec4*, Mat*, Slot*, char*);

// FUNCTION: GOLDTL 0x004458e0

char __cdecl fcn_004458e0(Ent* e, Ent* parent)
{
	Vec3 v;
	Vec4 wpos;
	Mat wm;
	Vec4 tmp[7];
	Mat mats[7];
	Ent* p;
	int i;

	if (e == parent || e == 0) {
		return 0;
	}
	if (parent != 0) {
		for (p = parent->child; p != 0; p = p->next) {
			if (p == e) {
				return 1;
			}
		}
		if (fcn_00445600(e, 0x1ff, parent, 0) != 0) {
			return 0;
		}
	}
	if (e->kind >= 5 && e->slots != 0) {
		v.x = e->x84.x;
		v.y = e->x84.y;
		v.z = e->x84.z;
		for (i = 0; i < 7; i++) {
			fcn_00455350(e, &e->slots[i], &tmp[i]);
			fcn_00438cb0(e, e->slots[i].xc);
			fcn_004557c0(e, 0, 1, &mats[i]);
		}
		fcn_00438cb0(e, &v);
	}
	fcn_00455350(e, &e->pos, &wpos);
	fcn_004557c0(e, 0, 1, &wm);
	fcn_0043a0a0(e);
	if (parent == 0) {
		fcn_00439aa0(e);
	} else {
		fcn_00439c00(parent, e);
	}
	fcn_004458a0(e, &wpos, &wm);
	if (e->kind >= 5 && e->slots != 0) {
		for (i = 0; i < 7; i++) {
			fcn_00445760(e, &tmp[i], &mats[i], &e->slots[i], e->slots[i].xc);
		}
	}
	return 1;
}
