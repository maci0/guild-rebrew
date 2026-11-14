#include <string.h>

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

typedef struct Msg {
	unsigned char type;
	char pad[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Msg;

typedef struct Ent {
	unsigned short id;
	char pad2[2];
	int x4;
	char pad8;
	unsigned char x9;
	char padA[0x15c];
	unsigned char x166;
	char pad167[0xb5];
} Ent;

typedef struct Rec18 {
	char pad0[8];
	unsigned char x8;
	char pad9[0xf];
} Rec18;

extern char g_7f4ca0[];

int __cdecl gm_RandomMod(unsigned short n);
void __cdecl fcn_004a51d0(char* e, int n, Slot* slots, Counts* cnt);
int __cdecl fcn_00495400(int who, int idx, int arg, Msg* out1, Msg* out2);
int __cdecl fcn_004e8b40(int idx, Rec18* out);
int __cdecl fcn_004a5340(char* e, int a, int* b, float c, float r, unsigned short* out);

/* ADDRESS: GOLDTL 0x0049a0c0 */
int __cdecl fcn_0049a0c0(int kind, char* e, int a2, Msg* out1, Msg* out2)
{
	Slot slot[12];
	Counts cnt;
	Msg a;
	Msg b;
	Rec18 q;
	int r;
	int i;
	int k;
	int total;
	int free;

	k = kind;
	if (k == 0) {
		k = 0x1c;
	}
	if (a2 != 0 || kind != 0) {
		return 0;
	}
	memset(slot, 0, sizeof(slot));
	slot[0].id = 0x155;
	slot[1].id = 0x15d;
	slot[2].id = 0x157;
	slot[3].id = 0x15f;
	slot[4].id = 0x159;
	slot[5].id = 0x165;
	slot[6].id = 0x166;
	slot[7].id = 0x16b;
	slot[8].id = 0x170;
	slot[9].id = 0x167;
	slot[10].id = 0x229;
	slot[11].id = 0x2b6;
	fcn_004a51d0(e, 12, slot, &cnt);
	total = cnt.total;
	free = cnt.free;
	if (total == 6 && free == 0) {
		return 0;
	}
	if (cnt.blocked == 12) {
		return 0;
	}
	if (total < 6) {
		if (free != 0) {
			goto pick_used;
		}
	} else {
		if (free != 0) {
			goto pick_used;
		}
		return 0;
	}
	{
		if (!fcn_004e8b40(((Ent*) e)->x166, &q)) {
			i = 7;
		} else {
			if (q.x8 < 4) {
				i = 0;
			} else if (q.x8 < 7) {
				i = 2;
			} else {
				i = 4;
			}
		}
		while (slot[i].a != 0) {
			i = (i + 1) % 12;
		}
		b.type = 2;
		b.a = slot[i].id;
		b.b = 1;
		b.f = 0.05f;
		a.type = 7;
		a.a = ((Ent*) e)->x4;
		a.b = 1;
		r = fcn_00495400(k, ((Ent*) e)->id, 2, &b, &a);
		if (r != 0) {
			*out1 = b;
			*out2 = a;
		}
		return r;
	}
pick_used:
	i = gm_RandomMod(12) & 0xffff;
	while (slot[i].a < 1) {
		i = (i + 1) % 12;
	}
	a.type = 1;
	a.a = slot[i].b;
	a.b = 1;
	b.type = 0;
	b.a = -1;
	b.b = -1;
	b.d = 0x1c;
	if (i == 9) {
		unsigned short picked;
		int mask;
		mask = (((Ent*) e)->x9 ? 1 : 2) | 0xf00500;
		if (fcn_004a5340(e, 1, &mask, 10.0f, (gm_RandomMod(0x20) & 0xffff) + 40.0f, &picked) == 0) {
			return 0;
		}
		b.type = 7;
		b.a = ((Ent*) g_7f4ca0)[picked].x4;
		b.b = -1;
	} else if (i == 10) {
		int mask;
		unsigned short picked;
		mask = (((Ent*) e)->x9 == 1 ? 2 : 1) | 0xf00500;
		if (fcn_004a5340(e, 1, &mask, 10.0f, (gm_RandomMod(0x20) & 0xffff) + 40.0f, &picked) == 0) {
			return 0;
		}
		b.type = 7;
		b.a = ((Ent*) g_7f4ca0)[picked].x4;
		b.b = -1;
	} else if (i == 8) {
		r = fcn_00495400(k, ((Ent*) e)->id, 3, &a, &b);
		if (r != 0) {
			*out1 = a;
			*out2 = b;
		}
		return r;
	}
	*out1 = a;
	*out2 = b;
	return 0x1c;
}
