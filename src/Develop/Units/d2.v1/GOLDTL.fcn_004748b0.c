extern void __cdecl fcn_00473fe0(void);
extern void __cdecl fcn_0046b2b0(int a);
extern int __cdecl CountDisplayCounters(void);
extern void __cdecl fcn_00469c40(int a, int b, int c);
extern int __cdecl fcn_00469c30(short a, short b, int c);
extern void __cdecl fcn_00474300(void);
extern int __cdecl fcn_00474780(void);
extern void __cdecl fcn_00466fe0(int a, int b);
extern void __cdecl fcn_00474040(void);
extern void __cdecl fcn_00475220(void *p);
extern int __cdecl d2_GetValueStep(void *p);
extern void __cdecl fcn_00412830(int a);
extern int __cdecl fcn_0046b520(void *p, int a);
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_100f1cc;
extern int g_100f1d4;
extern int g_100f1d8;
extern int g_100f1e0;
extern int g_100f898;
extern int g_100f89c;
extern int g_100f940;
extern int g_100f950;
extern int g_14ce8d0;
extern int g_14ce8d8;
extern int g_14ce8dc;
extern int g_14ce8e0;
extern int g_6772c0;
extern int g_67d370;
extern int g_67d3b0;
extern int g_67d8ec;
extern int g_6b5c84;
extern int g_7725e4;
extern int g_7725e8;
/* ADDRESS: GOLDTL 0x004748b0 */
int __cdecl fcn_004748b0(void)
{
	unsigned int *p;
	unsigned int *v1;
	int v7;
	int v8;
	int i;

	if (g_7725e8 && !g_14ce8dc) {
		p = *(unsigned int **) &g_7725d0;
		if (!g_14ce8d0 || p == 0
		    || !(*(unsigned char *) ((char *) p + 0x28) & 2)) {
			g_7725e8 = 0;
			g_6772c0 = g_100f1d8;
			g_6b5c84 = g_100f1e0;
			fcn_00473fe0();
		}
	}
	p = *(unsigned int **) &g_7725d0;
	v7 = (short) *(short *) &g_14ce8c2;
	if (!g_14ce8d0) {
		g_7725e4 = 0;
	}
	if (p == 0 && g_67d8ec != -1) {
		fcn_0046b2b0(g_67d8ec);
		g_67d8ec = -1;
		p = *(unsigned int **) &g_7725d0;
	}
	if (g_67d370 != -1) {
		v8 = *(int *) &g_1015ea0 + g_67d370 * 0x2f4;
		if (*(int *) (v8 + 0x20) == 0x41) {
			v1 = *(unsigned int **) (v8 + 0xc);
			if (g_67d370 == (int) v1[0x4d]) {
				if (!g_14ce8d0) {
					goto label_474b14;
				}
				if (p == v1 || g_7725e4) {
					goto label_474afe;
				}
				if (p != 0) {
					*(int *) (*(int *) &g_1015ea0 + 0x3c + p[0x4d] * 0x2f4) = 0;
				}
				*(int *) (*(int *) &g_1015ea0 + 0x3c + v1[0x4d] * 0x2f4) = 1;
				g_100f1d4 = g_6772c0 - v7;
				g_100f940 = v1[0x4b];
				g_100f950 = 0;
				v8 = *(int *) (*(int *) &g_1015ea0 + 0x40 + v1[0x4d] * 0x2f4);
				i = 0;
				if (v8 != 0) {
					while (i < *(int *) (v8 + 0x2c)) {
						if (*(int *) (*(int *) (v8 + 0x28) + i * 4) == (int) v1[0x4d]) {
							g_100f1cc = i;
						}
						i++;
					}
				}
				p = v1;
				*(unsigned int **) &g_7725d0 = v1;
				if ((*(unsigned char *) ((char *) v1 + 0x28) & 0x40) && !v1[6]
				    && !v1[7] && !CountDisplayCounters() && !v1[0x4b]) {
					v1[0x4b] = 0xffffffff;
					p = *(unsigned int **) &g_7725d0;
				}
				if (*(unsigned char *) ((char *) p + 0x28) & 1) {
					g_100f898 = fcn_0046b520((char *) p + 0x2c, p[0x4e]);
					g_100f898 += p[1];
					g_100f89c = p[2];
					if (g_67d8ec != -1) {
						fcn_00469c40(g_100f898, g_100f89c - 7,
						    g_67d8ec);
					} else {
						g_67d8ec = fcn_00469c30(
						    (short) g_100f898,
						    (short) (g_100f89c - 7),
						    g_67d3b0 + 8);
					}
				} else if (g_67d8ec != -1) {
					fcn_0046b2b0(g_67d8ec);
					g_67d8ec = -1;
				}
				p = *(unsigned int **) &g_7725d0;
			}
		}
	}
label_474afe:
	if (g_14ce8d0) {
		if (p == 0) {
			goto label_474b96;
		}
		g_7725e4 = 1;
	}
label_474b14:
	if (p != 0 && g_67d370 == (int) p[0x4d]
	    && (*(unsigned char *) ((char *) p + 0x28) & 2)
	    && g_14ce8d8) {
		if ((int) p[0x4b] < (int) p[6] && p[0x4b] != 0xffffffff
		    && p[0x4f] != 0xffffffff) {
			v7 = d2_GetValueStep(p);
			p[0x4b] += v7;
			p = *(unsigned int **) &g_7725d0;
		}
		if (!p[6] && !p[7] && !CountDisplayCounters() && !p[0x4b]
		    && (*(unsigned char *) ((char *) p + 0x28) & 0x40)) {
			p[0x4b] = 0xffffffff;
			p = *(unsigned int **) &g_7725d0;
		}
	}
label_474b96:
	if (g_14ce8e0) {
		if (p == 0) {
			goto label_474ca4;
		}
		if (*(unsigned char *) ((char *) p + 0x28) & 1) {
			fcn_00412830(0x10);
			p = *(unsigned int **) &g_7725d0;
		}
		*(int *) (*(int *) &g_1015ea0 + 0x3c + p[0x4d] * 0x2f4) = 0;
		*(unsigned int **) &g_7725d0 = 0;
		g_7725e4 = 0;
		if (g_67d8ec == -1) {
			goto label_474ca4;
		}
		fcn_0046b2b0(g_67d8ec);
		g_67d8ec = -1;
		p = *(unsigned int **) &g_7725d0;
	}
	if (p != 0) {
		if (!g_14ce8d0) {
			g_100f950 = 1;
			g_14ce8d8 = 0;
		}
		fcn_00474300();
		if (fcn_00474780()) {
			return 1;
		}
		if (*(unsigned int **) &g_7725d0 != 0
		    && (*(unsigned char *) (*(int *) &g_7725d0 + 0x28) & 0x10)
		    && g_67d370 == (int) (*(unsigned int **) &g_7725d0)[0x4d]
		    && g_14ce8d8) {
			v1 = *(unsigned int **) &g_7725d0;
			v1[0x53] = v1[0x53] + 1;
			if ((int) (v1[0x54] + 0xffffffff + v1[0x52]) < (int) v1[0x53]) {
				v1[0x53] = v1[0x52];
			}
			fcn_00466fe0(v1[0], v1[0x53]);
		}
	}
label_474ca4:
	fcn_00474040();
	if (g_67d370 != -1) {
		v7 = *(int *) &g_1015ea0 + g_67d370 * 0x2f4;
		if (*(unsigned char *) (v7 + 0x1d0) & 0x40) {
			fcn_00475220((void *) (v7 + 0xcc));
		}
	}
	return 0;
}
