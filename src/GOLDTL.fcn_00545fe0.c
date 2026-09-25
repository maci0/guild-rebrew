// FUNCTION: GOLDTL 0x545fe0
// SIZE: 431

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

// SIZE 0xa0
struct blob160 {
	int v[0x28];
};

// SIZE 0x14c
struct unit {
	unsigned char kind;
	char pad1[3];
	int serial;
	unsigned short house;
	char pada[2];
	int owner;
	int value;
	int params[12];
	struct pos14 pos;
	char pad52[0x1e];
	int f70;
	int f74;
	unsigned char flags;
	char pad79[3];
	int f7c;
	char pad80[4];
	int f84;
	char pad88[4];
	int extra[8];
	struct blob160 blob;
};

// SIZE 0xf8
struct spawn {
	char pad0[4];
	unsigned char kind;
	char pad5[3];
	int owner;
	int value;
	int params[6];
	struct pos14 pos;
	unsigned char flags;
	char pad37;
	int extra[8];
	struct blob160 blob;
};

extern void (__cdecl* g_7d1d80[])(struct unit*);
extern int g_7dc440[];
extern struct unit g_77e980[1024];
extern struct unit* g_7d1980[256];
extern int g_7749d0;
extern int g_7749d4;
extern int g_7749d8;
extern int g_7dc424;

char* __cdecl fcn_00508e40(int);

struct unit* __cdecl fcn_00545fe0(struct spawn* t)
{
	char* e;
	int i;
	int j;
	int k;
	struct unit* u;

	e = 0;
	if (t->kind >= 0xa7 || g_7d1d80[t->kind] == 0 || g_7dc440[t->kind] == 0) {
		return 0;
	}
	if (t->owner != -1) {
		e = fcn_00508e40(t->owner);
		if (e == 0) {
			return 0;
		}
	}
	for (i = 0; i < 1024; i++) {
		if (g_77e980[i].kind == 0) {
			break;
		}
	}
	if (i == 1024) {
		return 0;
	}
	u = &g_77e980[i];
	if (i > g_7749d4) {
		g_7749d4 = i;
	}
	if (t->owner == -1) {
		u->owner = -1;
		u->house = 0xffff;
	} else {
		u->owner = *(int*) (e + 4);
		u->house = *(unsigned short*) e;
	}
	if (t->flags & 8) {
		for (j = 0; j < 256; j++) {
			if (g_7d1980[j] == 0) {
				break;
			}
		}
		if (j == 256) {
			return 0;
		}
		g_7d1980[j] = u;
		if (j > g_7749d8) {
			g_7749d8 = j;
		}
	}
	u->kind = t->kind;
	u->serial = g_7749d0++;
	u->value = t->value;
	for (k = 0; k < 12; k++) {
		u->params[k] = t->params[k];
	}
	u->pos = t->pos;
	u->flags = t->flags;
	u->f70 = 0;
	u->f74 = 0;
	u->f7c = 0;
	u->f84 = -1;
	for (k = 0; k < 8; k++) {
		u->extra[k] = t->extra[k];
	}
	u->blob = t->blob;
	g_7d1d80[t->kind](u);
	g_7dc424++;
	return u;
}
