
// Draws a two-colour bar: the current value (fcn_00507e30) against the
// stored one at p[idx + 0x80], one segment image per 21 units and a half
// segment for an odd count. Values within 1% draw as one plain bar. When
// cur > max the odd stored-value segment reuses image `bar`, not `bar + 1`;
// the binary does this (its tail is cross-jumped with the other arm).

#include <math.h>

typedef struct BarImg {
	char pad0[0x50];
	short w;
	char pad52[2];
} BarImg;
// SIZE 0x54

extern char* g_772500;
#include "Develop/DieGildeAddOn/game/game_data.h"

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_0046f740(int x, int y, int a3, int win);

void __cdecl fcn_00534210(int x, int y, char* p, int idx, int bar)
{
	int w;
	int cur;
	int max;
	int m;
	int d;
	int n;
	int r;
	int half;
	int i;

	w = ((BarImg*) g_772500)[bar].w + 2;
	cur = fcn_00507e30(p, idx);
	max = (unsigned char) p[idx + 0x80];
	if (cur > max) {
		m = cur;
	} else {
		m = max;
	}
	d = cur - max;
	if (fabs(d) / m > 0.01f) {
		if (cur < max) {
			n = (int) (max * 0.0476190485f);
			r = n % 2;
			half = n / 2;
			for (i = 0; i < half; i++) {
				fcn_0046f740(x + i * w, y, bar + 2, d2_CurrentWindowId);
			}
			if (r) {
				fcn_0046f740(x + i * w, y, bar + 3, d2_CurrentWindowId);
			}
			n = (int) (cur * 0.0476190485f);
			r = n % 2;
			half = n / 2;
			for (i = 0; i < half; i++) {
				fcn_0046f740(x + i * w, y, bar, d2_CurrentWindowId);
			}
			if (r) {
				fcn_0046f740(x + i * w, y, bar + 1, d2_CurrentWindowId);
			}
		} else if (cur > max) {
			n = (int) (cur * 0.0476190485f);
			r = n % 2;
			half = n / 2;
			for (i = 0; i < half; i++) {
				fcn_0046f740(x + i * w, y, bar + 4, d2_CurrentWindowId);
			}
			if (r) {
				fcn_0046f740(x + i * w, y, bar + 5, d2_CurrentWindowId);
			}
			n = (int) (max * 0.0476190485f);
			r = n % 2;
			half = n / 2;
			for (i = 0; i < half; i++) {
				fcn_0046f740(x + i * w, y, bar, d2_CurrentWindowId);
			}
			if (r) {
				fcn_0046f740(x + i * w, y, bar, d2_CurrentWindowId);
			}
		}
	} else {
		n = (int) (max * 0.0476190485f);
		r = n % 2;
		half = n / 2;
		for (i = 0; i < half; i++) {
			fcn_0046f740(x + i * w, y, bar, d2_CurrentWindowId);
		}
		if (r) {
			fcn_0046f740(x + i * w, y, bar + 1, d2_CurrentWindowId);
		}
	}
}
