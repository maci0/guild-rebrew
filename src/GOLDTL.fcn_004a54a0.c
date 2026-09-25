// FUNCTION: GOLDTL 0x4a54a0
// SIZE: 286

#include <string.h>

typedef struct Query {
	int x0;
	int flags;
	char pad8[0x14 - 8];
	int kind;
	char pad18[0x1c - 0x18];
	char name[0x20];
	char pad3c[0x40 - 0x3c];
	int x40;
	char pad44[0x50 - 0x44];
} Query;
// SIZE 0x50

typedef struct Cand {
	unsigned short* obj;
	float val;
} Cand;
// SIZE 8

extern unsigned short* g_77261c;
extern int g_7728bc;

int __cdecl fcn_005cf720(unsigned short a, unsigned short b, Query* q, int c);
Cand* __cdecl fcn_004a34d0(void);

int __cdecl fcn_004a54a0(unsigned short* e, int a2, unsigned int n, char* src, float lo, float hi, unsigned short* out)
{
	Query q;
	unsigned int len;
	int i;
	Cand* t;

	memset(&q, 0, sizeof(q));
	len = n * 2;
	if (len > 0x20) {
		len = 0x20;
	}
	memcpy(q.name, src, len);
	q.kind = 2;
	if (g_77261c != 0 && !(q.flags & 0x10000000)) {
		q.x40 = 0;
		q.flags = a2;
		if (fcn_005cf720(*e, *g_77261c, &q, 0) != 0) {
			*out = *g_77261c;
			return 1;
		}
	}
	q.x40 = 0;
	for (i = g_7728bc; t = fcn_004a34d0(), i != 0 && t->obj != 0; i--) {
		if (!(t->val < lo) && !(t->val > hi) && fcn_005cf720(*e, *t->obj, &q, 0) != 0) {
			*out = *t->obj;
			return 1;
		}
	}
	return 0;
}
