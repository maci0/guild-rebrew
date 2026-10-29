#include <string.h>

typedef struct Msg {
	unsigned char type;
	char pad[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Msg;
// SIZE 0x18

typedef struct Slot {
	int id;
	int a;
	int b;
	char* item;
} Slot;

typedef struct Counts {
	int total;
	int blocked;
	int free;
} Counts;

typedef struct F8 {
	unsigned int mask;
	int b;
} F8;
// SIZE 0x8

extern char* g_77261c;
extern char g_7f4ca4[];

int __cdecl gm_RandomMod(int n);
void __cdecl fcn_004a51d0(char* e, int n, Slot* slots, Counts* cnt);
int __cdecl fcn_004a5340(char* e, int a, unsigned int* colors, int c, float r, unsigned short* ids);
int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);
int __cdecl fcn_00495400(int kind, int id, int a3, Msg* b, Msg* a);

/* ADDRESS: GOLDTL 0x0049b1f0 */
int __cdecl fcn_0049b1f0(int kind, char* e, int busy, Msg* out1, Msg* out2)
{
	Slot slot[12];
	Counts cnt;
	Msg a;
	Msg b;
	unsigned int colors[2];
	unsigned short ids[2];
	F8 f;
	Slot* sv;
	int id;
	int found;
	int r;
	int i;

	if (kind == 0) {
		kind = 0x1c;
	} else {
		return 0;
	}
	if (busy != 0) {
		return 0;
	}
	memset(slot, 0, sizeof(slot));
	slot[0].id = 0x169;
	slot[1].id = 0x16a;
	slot[2].id = 0x177;
	slot[3].id = 0x178;
	slot[4].id = 0x17d;
	slot[5].id = 0x16d;
	slot[6].id = 0x17b;
	slot[7].id = 0x22c;
	slot[8].id = 0x22b;
	slot[9].id = 0x22d;
	slot[10].id = 0x29a;
	slot[11].id = 0x29c;
	fcn_004a51d0(e, 12, slot, &cnt);
	if (cnt.total == 6 && cnt.free == 0) {
		return 0;
	}
	if (cnt.blocked == 0xc) {
		return 0;
	}
	if (cnt.total < 6) {
		if (cnt.free != 0) {
			goto occupied;
		}
		i = gm_RandomMod(0xc) & 0xffff;
		while (slot[i].a != 0) {
			i = (i + 1) % 12;
		}
		a.type = 2;
		a.a = slot[i].id;
		a.b = 1;
		a.f = 0.05f;
		b.type = 7;
		b.a = *(int*) (e + 4);
		b.b = 1;
		r = fcn_00495400(kind, *(unsigned short*) e, 2, &a, &b);
		if (r == 0) {
			return 0;
		}
		*out1 = a;
		*out2 = b;
		return r;
	}
	if (cnt.free == 0) {
		return 0;
	}
occupied:
	i = gm_RandomMod(0xc) & 0xffff;
	while (slot[i].a <= 0) {
		i = (i + 1) % 12;
	}
	a.type = 1;
	a.b = 1;
	a.a = slot[i].b;
	a.f = 0.05f;
	sv = &slot[i];
	id = sv->id;
	if (id != 0x169 && id != 0x16d) {
		colors[0] = (id != 0x29a) ? 0xf00500 : 0xf00d00;
	} else {
		colors[0] = 0xf00500;
		colors[1] = 0xf00500;
	}
	if (id == 0x177) {
		colors[0] |= 0x10000;
	}
	f.mask = 0xa07c4390;
	f.b = 1;
	if (id != 0x178) {
		if (fcn_004a5340(e, (id != 0x169 && id != 0x16d) ? 1 : 2, colors, 0,
			(float) (gm_RandomMod(0x40) & 0xffff), ids) == 0) {
			return 0;
		}
	} else {
		found = -1;
		if (g_77261c == 0 ||
			(fcn_004a5e60(g_77261c, 4, f, 0, 100.0f, &found), found == -1)) {
			if (fcn_004a5e60(e, 6, f, 0, (float) (gm_RandomMod(0x40) & 0xffff), &found) == 0) {
				return 0;
			}
		}
	}
	if (id == 0x17b || id == 0x17d || id == 0x29a || id == 0x29c ||
		(id >= 0x22b && id <= 0x22d)) {
		b.type = 7;
		b.a = *(int*) (g_7f4ca4 + (ids[0] & 0xffff) * 540);
		b.b = -1;
	} else if (id == 0x169 || id == 0x16d) {
		b.type = 7;
		b.a = *(int*) (g_7f4ca4 + (ids[0] & 0xffff) * 540);
		b.b = *(int*) (g_7f4ca4 + (ids[1] & 0xffff) * 540);
	} else if (id == 0x177) {
		char* p;

		p = *(char**) (g_7f4ca4 + (ids[0] & 0xffff) * 540 + 0x16c);
		b.type = 4;
		b.a = *(int*) (p + 1);
		b.b = -1;
	} else if (id == 0x178) {
		b.type = 4;
		b.a = found;
		b.b = -1;
	} else {
		return 0;
	}
	b.d = 0x21;
	r = 0x21;
	if (i > 1) {
		r = fcn_00495400(kind, *(unsigned short*) e, 4, &a, &b);
		if (r == 0) {
			return 0;
		}
	}
	*out1 = a;
	*out2 = b;
	return r;
}
