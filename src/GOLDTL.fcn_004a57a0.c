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

extern char *g_77261c;
extern int g_664398[];

int __cdecl fcn_005cf720(unsigned short, unsigned short, Query *, int);
int __cdecl gm_RandomMod(int);
float __cdecl fcn_0050f980(int, int, int);

/* ADDRESS: GOLDTL 0x004a57a0 */
unsigned int __cdecl fcn_004a57a0(unsigned short *e, int a1, int n, char *src, float lo, float hi, unsigned short *out)
{
	int step;
	float val;
	Query q;
	int count;
	int found;
	unsigned int i;
	unsigned int len;

	step = g_664398[gm_RandomMod(0x10) & 0xffff];
	memset(&q, 0, sizeof(q));
	{
	int flag = 0;
	len = n * 2;
	if (len > 0x20) {
		len = 0x20;
	}
	memcpy(q.name, src, len);
	q.kind = 2;
	if (g_77261c != 0) {
		q.x40 = 0;
		q.flags = a1;
		if (fcn_005cf720(*e, *((unsigned short *) g_77261c), &q, 0) != 0) {
			*out = *((unsigned short *) g_77261c);
			return 1;
		}
	}
	q.flags = a1;
	if (0.0 < lo || hi < 100.0) {
		if (lo < hi) {
			flag = 1;
		}
	}
	count = 0x300;
	found = 0;
	i = gm_RandomMod(0x300) & 0xffff;
	for (;;) {
		if (count == 0) {
			if (found) {
				return 1;
			}
			return 0;
		}
		if (fcn_005cf720(*e, (unsigned short) i, &q, 0) != 0) {
			if (flag == 0 || (val = fcn_0050f980(i, *e, 1), !(val < lo) && !(val > hi))) {
				found = 1;
				*out = (unsigned short) i;
			}
		}
		count--;
		i = (i + step) % 0x300;
		if (found) {
			return 1;
		}
	}
	}
}
