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

unsigned short __cdecl fcn_0042e410(int n);
void __cdecl fcn_004a51d0(char* e, int n, Slot* slots, Counts* cnt);
int __cdecl fcn_00495400(int kind, int id, int a3, Msg* b, Msg* a);

// FUNCTION: GOLDTL 0x0049a590
int __cdecl fcn_0049a590(int kind, char* e, int busy, Msg* out1, Msg* out2)
{
	Counts cnt;
	Slot slot[2];
	Msg a;
	Msg b;
	int r;
	int i;

	if (kind == 0) {
		kind = 0x1d;
	}
	if (busy == 0) {
		memset(slot, 0, sizeof(slot));
		slot[0].id = 0x173;
		slot[1].id = 0x15b;
		fcn_004a51d0(e, 2, slot, &cnt);
		if ((cnt.total != 6 || cnt.free != 0) && cnt.blocked != 2) {
			if (cnt.total < 6 && cnt.free == 0) {
				i = fcn_0042e410(2);
				while (slot[i].a != 0) {
					i = (i + 1) % 2;
				}
				a.type = 2;
				a.a = slot[i].id;
				a.b = 1;
				a.f = 0.05f;
				b.type = 7;
				b.a = *(int*) (e + 4);
				b.b = 1;
				r = fcn_00495400(kind, *(unsigned short*) e, 2, &a, &b);
				if (r != 0) {
					*out1 = a;
					*out2 = b;
				}
				return r;
			}
			if (cnt.free != 0) {
				i = fcn_0042e410(2);
				while (slot[i].a < 1) {
					i = (i + 1) % 2;
				}
				b.type = 1;
				b.b = 1;
				b.a = slot[i].b;
				a.type = 0;
				a.a = -1;
				a.b = -1;
				a.d = 0x1d;
				if (i != 0) {
					r = 0x1d;
				} else {
					r = fcn_00495400(kind, *(unsigned short*) e, 4, &b, &a);
				}
				if (r != 0) {
					*out1 = b;
					*out2 = a;
				}
				return r;
			}
		}
	}
	return 0;
}
