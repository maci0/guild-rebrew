// FUNCTION: GOLDTL 0x0049b7c0

#include <string.h>

// SIZE 0x18
typedef struct Msg {
	unsigned char type;
	char pad[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Msg;

// SIZE 0x10
typedef struct Slot {
	int id;
	int a;
	int b;
	char* item;
} Slot;

// SIZE 0xc
typedef struct Counts {
	int total;
	int blocked;
	int free;
} Counts;

unsigned short __cdecl fcn_0042e410(int n);
void __cdecl fcn_004a51d0(char* e, int n, Slot* slots, Counts* cnt);
int __cdecl fcn_00495400(int kind, int id, int a3, Msg* b, Msg* a);

/* Each arm declares its own message pair (block scope) so the pair lands in
 * the reference slots; every arm keeps its own call-and-copy tail, which c2
 * cross-jumps into one call site as in the reference. */
int __cdecl fcn_0049b7c0(int kind, char* e, int busy, Msg* out1, Msg* out2)
{
	Slot slots[10];
	Counts cnt;
	int r;
	int i;

	r = kind;
	if (r == 0) {
		r = 0x22;
	}
	if (busy == 0 && kind == 0) {
		memset(slots, 0, sizeof(slots));
		slots[0].id = 0x17c;
		slots[1].id = 0x171;
		slots[2].id = 0x16f;
		slots[3].id = 0x15c;
		slots[4].id = 0x15a;
		slots[5].id = 0x22e;
		slots[6].id = 0x22a;
		slots[7].id = 0x2b4;
		slots[8].id = 0x2b5;
		slots[9].id = 0x2b3;
		fcn_004a51d0(e, 10, slots, &cnt);
		if ((cnt.total != 6 || cnt.free != 0) && cnt.blocked != 10) {
			if (cnt.total < 6 && cnt.free == 0) {
				Msg a;
				Msg b;

				i = fcn_0042e410(10);
				while (slots[i].a != 0) {
					i = (i + 1) % 10;
				}
				a.type = 2;
				a.a = slots[i].id;
				a.b = 1;
				a.f = 0.05f;
				b.type = 7;
				b.a = *(int*) (e + 4);
				b.b = 1;
				r = fcn_00495400(r, *(unsigned short*) e, 2, &a, &b);
				if (r != 0) {
					*out1 = a;
					*out2 = b;
				}
				return r;
			}
			if (cnt.free != 0) {
				Msg a;
				Msg b;

				i = fcn_0042e410(10);
				while (slots[i].a < 1) {
					i = (i + 1) % 10;
				}
				a.type = 1;
				a.a = slots[i].b;
				a.b = 1;
				b.type = 0;
				b.a = -1;
				b.b = -1;
				b.d = 0x22;
				if (i == 0) {
					r = fcn_00495400(r, *(unsigned short*) e, 4, &a, &b);
					if (r != 0) {
						*out1 = a;
						*out2 = b;
					}
					return r;
				}
				if (i < 4) {
					r = fcn_00495400(r, *(unsigned short*) e, 3, &a, &b);
					if (r != 0) {
						*out1 = a;
						*out2 = b;
					}
					return r;
				}
				*out1 = a;
				*out2 = b;
				return 0x22;
			}
		}
	}
	return 0;
}
