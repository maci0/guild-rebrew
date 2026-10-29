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
/* SIZE 0x18 */

typedef struct Slot {
	int id;
	int a;
	int b;
	int pad;
} Slot;
/* SIZE 0x10 */

typedef struct Counts {
	int total;
	int blocked;
	int free;
} Counts;

unsigned short __cdecl gm_RandomMod(int n);
void* __cdecl fcn_00508e40(int handle);
void* __cdecl fcn_005463a0(int a, int b, int c);
void* __cdecl he_fn_Handlung(void);
void __cdecl fcn_004a51d0(char* e, int n, Slot* slots, Counts* cnt);
int __cdecl fcn_00495400(int type, int id, int n, Msg* a, Msg* b);

/* ADDRESS: GOLDTL 0x0049adb0 */
int __cdecl fcn_0049adb0(int kind, char* e, int busy, Msg* out1, Msg* out2)
{
	Counts cnt;
	Msg b;
	Msg a;
	Slot slots[3];
	int* p;
	int* q;
	int s;
	void* rec;
	void* o;
	int i;
	int r;
	int n;
	int type;

	type = kind;
	if (type == 0) {
		type = 0x20;
	}
	if (busy != 0) {
		return 0;
	}
	if (kind != 0) {
		return 0;
	}
	p = (int*) (e + 0x5c);
	q = p + 3;
	for (i = 3; i < 8; i++, q++) {
		o = fcn_00508e40(*q);
		if (o != 0 && *(unsigned short*) ((char*) o + 0xa) < 0x28) {
			break;
		}
	}
	q = p + 3;
	for (i = 3; i < 8; i++, q++) {
		s = (int) fcn_00508e40(*q);
		if (s != 0 && *(unsigned short*) (s + 0xa) < 0x28) {
			break;
		}
	}
	memset(&slots, 0, sizeof(slots));
	if (s != 0) {
		slots[0].id = 0x162;
		slots[1].id = 0x163;
		slots[2].id = 0x164;
		n = 3;
	} else if (*(int*) (e + 0x5c) == -1) {
		o = fcn_005463a0(1, 0, 0x41);
		while (o != 0) {
			if (*(int*) ((char*) o + 0xac) == *(int*) (e + 4)) {
				rec = fcn_00508e40(*(int*) ((char*) o + 0xb0));
				if (rec == 0) {
					return 0;
				}
				slots[0].id = 0x167;
				slots[1].id = 0;
				slots[2].id = 0;
				n = 1;
				goto build;
			}
			o = he_fn_Handlung();
		}
		slots[0].id = 0x170;
		slots[1].id = 0;
		slots[2].id = 0;
		n = 1;
	} else {
		return 0;
	}
	rec = e;
build:
	fcn_004a51d0(e, n, slots, &cnt);
	if (cnt.total == 6 && cnt.free == 0) {
		return 0;
	}
	if (cnt.blocked == n) {
		return 0;
	}
	if (cnt.total < 6) {
		if (cnt.free == 0) {
			r = gm_RandomMod(n);
			while (slots[r].a != 0) {
				r = (r + 1) % n;
			}
			a.type = 2;
			a.a = slots[r].id;
			a.b = 1;
			a.f = 0.05f;
			b.type = 7;
			b.a = *(int*) (e + 4);
			b.b = 1;
			r = fcn_00495400(type, *(unsigned short*) e, 2, &a, &b);
			if (r == 0) {
				return 0;
			}
			*out1 = a;
			*out2 = b;
			return r;
		}
	} else {
		if (cnt.free == 0) {
			return 0;
		}
	}
	r = gm_RandomMod(n);
	while (slots[r].a < 1) {
		r = (r + 1) % n;
	}
	a.type = 1;
	a.a = slots[r].b;
	a.b = 1;
	a.f = 0.05f;
	switch (slots[r].id) {
	case 0x170:
		b.a = -1;
		b.type = 0;
		b.b = -1;
		break;
	case 0x167:
		b.a = *(int*) ((char*) rec + 4);
		b.type = 7;
		b.b = -1;
		break;
	case 0x162:
	case 0x163:
	case 0x164:
		b.a = *(int*) (s + 4);
		b.type = 7;
		b.b = -1;
		break;
	default:
		return 0;
	}
	b.d = 0x20;
	if (slots[r].id == 0x170) {
		r = fcn_00495400(type, *(unsigned short*) e, 3, &a, &b);
		if (r == 0) {
			return 0;
		}
		*out1 = a;
		*out2 = b;
		return r;
	}
	*out1 = a;
	*out2 = b;
	return 0x20;
}
