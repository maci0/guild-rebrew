#include <stdlib.h>

#include "g_7f4ca2.h"

typedef struct Stat {
	int v[9];
} Stat;
// SIZE 0x24

int __cdecl fcn_004f4830(int idx, void* dst);
struct unit* __cdecl fcn_005463a0(int n, ...);
int __cdecl he_fn_Handlung(void);
int __cdecl gm_RandomMod(unsigned short n);
int __cdecl gm_QueryEntitySum(int, int);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(unsigned char, unsigned char, unsigned short, char*);
void __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_004c4ef0(char*);
void __cdecl fcn_004c5360(void);

extern Slot7f4ca2 g_7f4ca2[768];
extern char g_7f4ca4[];
extern unsigned char g_773d75;
extern int g_aed32c;

/* Nudges the stock level of the entity's home building towards the level the
   entity is drifting to, then rebalances the building's per-kind stock against
   the entity's total. */
/* ADDRESS: GOLDTL 0x00482b60 */
void __cdecl fcn_00482b60(char* e)
{
	Stat st;
	char* o;
	int n;
	int i;
	int sum;
	int d;
	int t;
	int r;
	int total;

	if (*(int*) (e + 0x1c8) & 8) {
		return;
	}
	if (!fcn_004f4830(0xe, &st)) {
		return;
	}
	o = *(char**) (e + 0x16c);
	n = 0;
	if (fcn_005463a0(2, 0, 0x23, 3, *(int*) (o + 1))) {
		do {
			n++;
		} while (he_fn_Handlung());
	}
	o = *(char**) (e + 0x16c);
	if (abs(*(int*) (o + 0x65) - st.v[6]) > 3) {
		if (*(int*) (o + 0x65) > st.v[6]) {
			t = *(int*) (o + 0x65) - 1;
		} else {
			t = *(int*) (o + 0x65) + 1;
		}
	} else if (n == 0) {
		if (*(int*) (o + 0x65) <= st.v[6] - 2) {
			goto stock_done;
		}
		o = *(char**) (e + 0x16c);
		t = *(int*) (o + 0x65) - (gm_RandomMod(3) & 0xffff) - 1;
		if (t < st.v[6] - 2) {
			t = st.v[6] - 2;
		}
		if (t < 4) {
			t = 4;
		}
	} else {
		if (n <= 3 || *(int*) (o + 0x65) >= st.v[6]) {
			goto stock_done;
		}
		o = *(char**) (e + 0x16c);
		t = *(int*) (o + 0x65) + (gm_RandomMod(3) & 0xffff) + 1;
		if (t > st.v[6] + 3) {
			t = st.v[6] + 3;
		}
	}
	o = *(char**) (e + 0x16c);
	fcn_004c4510(o, *(int*) (o + 1));
	fcn_004c4570(4, 1,
	             (unsigned short) (*(unsigned short*) (e + 0x16c) -
	                               *(unsigned short*) &g_aed32c) + 0x65,
	             &t);
	fcn_004c5360();
stock_done:
	sum = 0;
	for (i = 1; i < 4; i++) {
		o = *(char**) (e + 0x16c);
		r = gm_QueryEntitySum(*(int*) (o + 0x5d), i);
		total = *(int*) (e + 0x1b8);
		if (r < total * 3 / 0x14) {
			d = total * 5 / 0x14 - r;
			sum += d;
			fcn_004c4eb0("Bankmeister");
			fcn_004c5150(*(int*) (o + 1), -1, (char) i, d);
			t = (int) (d * 1.03);
			fcn_004c5150(
				-1,
				*(int*) (g_7f4ca4 +
				         *(unsigned short*) (o + 0x27) * 0x21c),
				(char) g_773d75, t);
			fcn_004c4ef0("Bankmeister");
		} else if (r > total * 6 / 0x14) {
			d = r - total * 4 / 0x14;
			sum -= d;
			fcn_004c4eb0("Bankmeister");
			fcn_004c5150(
				*(int*) (g_7f4ca4 +
				         *(unsigned short*) (o + 0x27) * 0x21c),
				-1, (char) g_773d75, d);
			t = (int) (d * 1.03);
			fcn_004c5150(-1, *(int*) (o + 1), (char) i, t);
			fcn_004c4ef0("Bankmeister");
		}
	}
	o = *(char**) (e + 0x16c);
	t = gm_QueryEntitySum(*(int*) (o + 0x5d), (char) g_773d75);
	total = *(int*) (e + 0x1b8);
	if ((double) t > 1.5 * (double) total && total - sum > 0) {
		o = *(char**) (e + 0x16c);
		fcn_004c5150(
			*(int*) (o + 1),
			*(int*) (g_7f4ca4 + *(unsigned short*) (o + 0x27) * 0x21c),
			(char) g_773d75, (int) ((total - sum) * 0.8));
	} else {
		o = *(char**) (e + 0x16c);
		if (g_7f4ca2[*(unsigned short*) (o + 0x27)].kind != 6 &&
		    g_7f4ca2[*(unsigned short*) (o + 0x27)].kind != 7 &&
		    t > total * 2) {
			fcn_004c5150(
				*(int*) (g_7f4ca4 +
				         *(unsigned short*) (o + 0x27) * 0x21c),
				*(int*) (o + 1), (char) g_773d75,
				(int) (total * 2.25 - t));
		}
	}
	*(int*) (e + 0x1c8) |= 8;
}
