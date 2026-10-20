#include <string.h>

typedef struct Query {
	int x0;
	int flags;
	char pad8[0x14 - 8];
	int kind;
	char pad18[0x1c - 0x18];
	unsigned short name[0x10];
	char pad3c[0x40 - 0x3c];
	int x40;
	char pad44[0x50 - 0x44];
} Query;
/* SIZE 0x50 */

typedef struct Cand {
	unsigned short* obj;
	float val;
} Cand;
/* SIZE 0x8 */

extern char* g_77261c;
extern unsigned int g_7728bc;

int __cdecl fcn_005cf720(unsigned short, unsigned short, Query*, int);
Cand* __cdecl fcn_004a34d0(void);

/* ADDRESS: GOLDTL 0x004a5340 */
int __cdecl fcn_004a5340(unsigned short* e, unsigned int n, unsigned int* ids,
	float lo, float hi, unsigned short* out)
{
	Query q;
	int k;
	int found;
	int i;
	int j;
	Cand* t;

	if (n > 3) {
		return 0;
	}
	memset(&q, 0, sizeof(q));
	for (j = 0; j < 0x10; j++) {
		q.name[j] = 0xffff;
	}
	k = 0;
	q.kind = 2;
	if (g_77261c != 0 && !(q.flags & 0x10000000)) {
		q.x40 = 0;
		q.flags = *ids;
		if (fcn_005cf720(*e, *((unsigned short*) g_77261c), &q, 0) != 0) {
			*out = *((unsigned short*) g_77261c);
			k = 1;
		}
	}
	for (; k < n; k++) {
		q.flags = ids[k];
		if (k != 0) {
			q.name[k] = out[k - 1];
		} else {
			q.name[0] = *e;
		}
		found = 0;
		i = *(int*) &g_7728bc;
		t = fcn_004a34d0();
		while (i != 0) {
			if (t->obj == 0) {
				return 0;
			}
			if (!(t->val < lo) && !(t->val > hi)
			    && fcn_005cf720(*e, *t->obj, &q, 0) != 0) {
				out[k] = *t->obj;
				found = 1;
			}
			i--;
			t = fcn_004a34d0();
			if (!found) {
				continue;
			}
			break;
		}
		if (!found) {
			return 0;
		}
	}
	return 1;
}
