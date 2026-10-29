


#include <string.h>

typedef struct Query {
	int kind;
	char pad4[0x220 - 4];
} Query;
// SIZE 0x220

extern unsigned char* lpGebaeudePROT;

int __cdecl fcn_004fa5b0(int k, char* e, Query* q);
int __cdecl fcn_00504f30(int k, int id);
int __cdecl fcn_004a48e0(char* e, int k);

int __cdecl fcn_004a4bb0(char* a1, char* e, char* a3, char* cmd, char* out, int want)
{
	Query q;
	int k;
	unsigned char* t;
	unsigned char* t2;
	int r;

	memset(&q, 0, sizeof(q));
	q.kind = 1;
	if (*cmd != 5) {
		return 0;
	}
	k = *(int*) (cmd + 4);
	t = lpGebaeudePROT + k * 0x24d;
	if (t[0] == 2) {
		if (*(unsigned char**) (e + 0x170) != 0) {
			t2 = lpGebaeudePROT + **(unsigned char**) (e + 0x170) * 0x24d;
			if (t2[0x247] >= t[0x247] && t2[0] == 2) {
				return 0;
			}
		}
		if (k == 4) {
			r = fcn_004fa5b0(1, e, &q);
			if (r != 2 && r != 4) {
				return 0;
			}
		} else if (k == 5) {
			r = fcn_004fa5b0(5, e, &q);
			if (r != 2 && r != 4) {
				return 0;
			}
		} else if (k == 6) {
			r = fcn_004fa5b0(9, e, &q);
			if (r != 2 && r != 4) {
				return 0;
			}
		} else if (k == 7) {
			r = fcn_004fa5b0(0xc, e, &q);
			if (r != 2 && r != 4) {
				return 0;
			}
		}
	} else if (fcn_00504f30(k, *(unsigned short*) e) == 0) {
		return 0;
	}
	if (want == 0) {
		return 1;
	}
	r = fcn_004a48e0(e, *(int*) (cmd + 4));
	if (r == 0) {
		return 0;
	}
	out[0] = 0xc;
	*(int*) (out + 4) = r;
	*(int*) (out + 8) = 1;
	return 1;
}
