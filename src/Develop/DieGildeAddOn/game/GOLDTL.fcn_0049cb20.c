#include <string.h>

typedef struct Msg {
	unsigned char type;
	char pad1[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Msg;
/* SIZE 0x18 */

unsigned short __cdecl gm_RandomMod(int n);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_00495400(int kind, int id, int n, Msg* b1, Msg* b2);
int __cdecl fcn_004aa580(char* e, char* a2, char* out);

/* ADDRESS: GOLDTL 0x0049cb20 */
int __cdecl fcn_0049cb20(int a1, char* e, int busy, Msg* out1, Msg* out2)
{
	Msg a;
	Msg b;
	Msg c;
	Msg d;
	int r;

	if (busy != 0) {
		return 0;
	}
	if (*(int*) (e + 0x1e8) & 0x100) {
		if (gm_RandomMod(4) != 0) {
			return 0;
		}
	}
	if (*(char**) (e + 0x170) == 0) {
		if (e[2] != 3) {
			a.type = 5;
			a.a = 4;
			a.b = 1;
			b.type = 0;
			b.a = 0;
			b.b = 0;
			r = fcn_00495400(0x28, *(unsigned short*) e, 1, &a, &b);
			if (r != 0) {
				*out1 = a;
				*out2 = b;
			}
			return r;
		}
	} else {
		if (e[2] != 3) {
			if (fcn_00502cd0(*(int*) (*(char**) (e + 0x170) + 0x5d), 2, 6, 0, 0x15) == 0) {
				a.type = 2;
				a.a = 0x15;
				a.b = 1;
				a.f = 0.44f;
				b.type = 4;
				b.a = *(int*) (*(char**) (e + 0x170) + 1);
				b.b = 1;
				r = fcn_00495400(0x29, *(unsigned short*) e, 1, &a, &b);
				if (r != 0) {
					*out1 = a;
					*out2 = b;
				}
				return r;
			}
		}
	}
	if (*(char*) (e + 0x1e8) & 4) {
		memset(&c, 0, sizeof(c));
		memset(&d, 0, sizeof(d));
		if (fcn_004aa580(e, (char*) &c, (char*) &d) == 0) {
			return 0;
		}
		*out1 = c;
		*out2 = d;
		return 0x29;
	}
	return 0;
}
