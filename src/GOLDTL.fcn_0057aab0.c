#include <math.h>

// SIZE 0x58
typedef struct {
	char pad0[0x4c];
	float x;
	float y;
	float z;
} Pos57aa;

#pragma pack(push, 1)
// SIZE 0xa9
typedef struct {
	unsigned char office;
	char pad1[0x26];
	unsigned short owner;
	char pad29[0x38];
	Pos57aa* pos;
	char pad65[0x44];
} Bld57aa;

// SIZE 0x24d
typedef struct {
	unsigned char kind;
	char pad1[0x24c];
} Office57aa;
#pragma pack(pop)

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x164];
	Bld57aa* home;
	Bld57aa* work;
	char pad174[0xa8];
} Unit57aa;

extern Bld57aa* g_90e094;
extern Office57aa* g_868050;
extern unsigned short* g_773da8;
extern Unit57aa g_7f4ca0[768];
extern char g_6b5c60[];

int __cdecl fcn_0057a890(Unit57aa*, float, int, int*);
void __cdecl fcn_005498b0(int, Unit57aa*, Unit57aa*, Bld57aa*, int, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);

// SIZE 0x10
typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec57aa;

static __inline void v3set(Vec57aa* d, float x, float y, float z)
{
	d->x = x;
	d->y = y;
	d->z = z;
}

static __inline float v3len(Vec57aa* v)
{
	float l;

	l = (float) sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	return l;
}

// FUNCTION: GOLDTL 0x57aab0
// SIZE: 668
void __cdecl fcn_0057aab0(Bld57aa* self, int mode, int who, int side)
{
	float range;
	float d;
	Unit57aa* house;
	int i;
	int tmp;
	Vec57aa p;
	Vec57aa q;
	Vec57aa dv;
	char buf[0x800];
	Bld57aa* b;
	Pos57aa* bp;
	unsigned int lo;
	unsigned int hi;
	Office57aa* o;
	int role;
	int v;
	int j;
	Unit57aa* u;

	if (self->pos == 0) {
		return;
	}
	if (mode == 2) {
		range = 1500.0f;
	} else if (mode == 1) {
		range = 800.0f;
	} else {
		range = 400.0f;
	}
	v3set(&p, self->pos->x, self->pos->y, self->pos->z);
	for (i = 0; i < 0x100; i++) {
		lo = 0;
		b = &g_90e094[i];
		o = &g_868050[b->office];
		hi = 0;
		if (o->kind > 0x1f) {
			hi = 1 << (o->kind - 0x20);
		} else {
			lo = 1 << o->kind;
		}
		if (b->owner == 0xffff || b->owner == *g_773da8) {
			continue;
		}
		bp = b->pos;
		if (bp == 0) {
			continue;
		}
		if (!(lo & 0x807c4116) && !(hi & 1)) {
			continue;
		}
		v3set(&q, bp->x, bp->y, bp->z);
		dv.x = p.x - q.x;
		dv.y = p.y - q.y;
		dv.z = p.z - q.z;
		house = &g_7f4ca0[b->owner];
		if ((d = v3len(&dv)) > range) {
			continue;
		}
		for (j = 0; j < 768; j++) {
			u = &g_7f4ca0[j];
			if (u->id == 0xffff || u->type >= 10 || (u->owner & 3) != side) {
				continue;
			}
			if (u->home != 0 && u->home == b) {
				role = 3;
			} else if (u->work != 0 && u->work == b) {
				role = 2;
			} else if (house == u) {
				role = 1;
			} else {
				continue;
			}
			v = fcn_0057a890(u, (1.0f - d / range) * 0.5f + 0.25f, who, &tmp);
			if (v == 0) {
				continue;
			}
			if (role == 3) {
				fcn_005498b0(0, u, house, b, v, tmp);
			} else if (role == 1 && (u->type == 6 || u->type == 7)) {
				fcn_0051af00(buf, 0x163c, v + 0x1632);
				fcn_00545d40(u->owner, -1, buf, 0, 0x5f7, g_6b5c60);
			}
		}
	}
}
