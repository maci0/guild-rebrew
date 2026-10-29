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

extern int __cdecl fcn_004fef00(char* p);
extern int __cdecl fcn_004e8d10(void* p, int n, void* out);
extern int __cdecl fcn_004a9b20(int a1, char* e, int a3, Msg* in, Msg* out);
extern int __cdecl fcn_00495400(int kind, int id, int a3, Msg* b, Msg* a);
extern unsigned short __cdecl gm_RandomMod(unsigned short n);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x00496e60 */
int __cdecl fcn_00496e60(int a1, char* e, int y, Msg* out1, Msg* out2)
{
	Msg b;
	char items[0x18];
	Msg a;
	int r;
	int v;

	if (y) {
		return 0;
	}
	if (*(unsigned char*) (e + 0xd) < 2) {
		b.type = 0xd;
		b.a = 2;
		b.b = 1;
		b.f = 0.44f;
		memset(&a, 0, sizeof(a));
		r = fcn_00495400(10, *(unsigned short*) e, 1, &b, &a);
		if (r) {
			*out1 = b;
			*out2 = a;
			return r;
		}
		return 0;
	}
	if (*(unsigned short*) 0x7f4c04 < 0xd) {
		return 0;
	}
	if (*(unsigned char*) (e + 0x168)) {
		return 0;
	}
	if (fcn_004fef00(e) - *(unsigned short*) (e + 0xa) < 3) {
		return 0;
	}
	r = fcn_004e8d10(e, 2, items);
	if (r) {
		v = *(int*) (items + gm_RandomMod(r) * 0xc);
		if (v != 0 && v <= 0x1b) {
			out1->a = v;
			out1->type = 10;
			return 10;
		}
	} else if (gm_RandomMod(4) == 0) {
		a.type = 0x10;
		a.a = 0x12;
		a.b = 0;
		if (fcn_004a9b20(a1, e, 0, &a, &b)) {
			*out1 = a;
			*out2 = b;
			return 0x27;
		}
	}
	return 0;
}
