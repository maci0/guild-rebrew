#include <stdlib.h>
#include <string.h>

typedef struct Query {
	int x0;
	int flags;
	char pad8[0x14 - 8];
	int kind;
	char pad18[0x1c - 0x18];
	char name[0x20];
	char pad3c[0x50 - 0x3c];
} Query;
// SIZE 0x50

// SIZE 0x21c
typedef struct {
	unsigned short slot;
	unsigned char type;
	char pad3[0x161];
	unsigned char job;
	char pad165[0xb7];
} Entity_4a5960;

extern int g_664398[];
extern char g_7f4ca0[];

unsigned short __cdecl gm_RandomMod(int);
int __cdecl fcn_00508f80(unsigned short, int);
int __cdecl fcn_005cf720(unsigned short a, unsigned short b, Query* q, int c);
float __cdecl fcn_0050f980(int, int, int);

/* ADDRESS: GOLDTL 0x004a5960 */

/* Collects up to max entities near e's level into out, walking the entity
 * table from a random start with a random stride: first those with a job
 * other than 0x52, then jobless ones. */
unsigned int __cdecl fcn_004a5960(unsigned short* e, unsigned int max, int a2, float lo, float hi, unsigned short* out)
{
	Query q;
	int step;
	unsigned int cnt;
	int ranged;
	int tries;
	int i;
	float f;
	unsigned char t;
	unsigned char job;

	step = g_664398[gm_RandomMod(0x10)];
	ranged = 0;
	memset(&q, 0, sizeof(q));
	memset(q.name, 0xff, sizeof(q.name));
	if ((lo > 0.0 || hi < 100.0) && lo < hi) {
		ranged = 1;
	}
	q.kind = 2;
	q.flags = a2;
	a2 = fcn_00508f80(*e, 0);
	tries = 0x300;
	cnt = 0;
	i = gm_RandomMod(0x300);
	while (cnt < max && tries != 0) {
		t = ((Entity_4a5960*)g_7f4ca0)[i].type;
		if (t != 8 && t != 7 && t != 5 && t != 9 && t != 0x14) {
			job = ((Entity_4a5960*)g_7f4ca0)[i].job;
			if (job != 0 && job != 0x52 && fcn_005cf720(*e, (unsigned short) i, &q, 0) != 0
			    && abs(a2 - fcn_00508f80((unsigned short) i, 0)) < 6) {
				if (!ranged || (f = fcn_0050f980(i, *e, 1), !(f < lo) && !(f > hi))) {
					out[cnt++] = (unsigned short) i;
				}
			}
		}
		tries--;
		i = (step + i) % 0x300;
	}
	tries = 0x300;
	i = gm_RandomMod(0x300);
	while (cnt < max && tries != 0) {
		t = ((Entity_4a5960*)g_7f4ca0)[i].type;
		if (t != 8 && t != 7 && t != 5 && t != 9 && t != 0x14) {
			if (((Entity_4a5960*)g_7f4ca0)[i].job == 0 && fcn_005cf720(*e, (unsigned short) i, &q, 0) != 0
			    && abs(a2 - fcn_00508f80((unsigned short) i, 0)) < 6) {
				if (!ranged || (f = fcn_0050f980(i, *e, 1), !(f < lo) && !(f > hi))) {
					out[cnt++] = (unsigned short) i;
				}
			}
		}
		tries--;
		i = (i + step) % 0x300;
	}
	return cnt;
}
