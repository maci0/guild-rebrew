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

// FUNCTION: GOLDTL 0x0049ab50
// SIZE: 396
int __cdecl fcn_0049ab50(int kind, char* e, int busy, Msg* out1, Msg* out2)
{
	Counts cnt;
	Slot slot;
	Msg a;
	Msg b;
	int r;

	if (kind == 0) {
		kind = 0x1f;
	}
	if (busy == 0) {
		memset(&slot, 0, sizeof(slot));
		if (*(int*) (e + 0x2c) != 0) {
			slot.id = 0x17e;
		} else if (fcn_0042e410(3) == 0) {
			slot.id = 0x175;
		} else {
			return 0;
		}
		fcn_004a51d0(e, 1, &slot, &cnt);
		if ((cnt.total != 6 || cnt.free != 0) && cnt.blocked != 1) {
			if (cnt.total < 6 && cnt.free == 0) {
				a.type = 2;
				a.a = slot.id;
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
				a.a = -1;
				a.b = -1;
				b.a = slot.b;
				b.type = 1;
				b.b = 1;
				a.type = 0;
				a.d = 0x1f;
				r = fcn_00495400(kind, *(unsigned short*) e, 4, &b, &a);
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
