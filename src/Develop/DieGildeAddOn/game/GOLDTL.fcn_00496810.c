#include "client_dialog_helpers.h"

int __cdecl fcn_00495400(int, short, int, Cmd *, Cmd *);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0042e410(int, ...);
int __cdecl fcn_004a5340(short *, int, unsigned int *, int, float);
int __cdecl fcn_004e9310(int, int, void *);
int __cdecl fcn_0042e450(void);

/* ADDRESS: GOLDTL 0x00496810 */
int __cdecl fcn_00496810(int a1, short *ent, int mode, Cmd *out1, Cmd *out2, int extra)
{
	Cmd c1;
	Cmd c2;
	unsigned short nl[8];
	unsigned int target;
	int r;
	int t;
	int i;
	int best;
	int bestI;
	float bestVal;
	float value;
	unsigned char *e;

	(void) a1;
	(void) extra;
	if (mode != 0) {
		return 0;
	}
	if (*(int *) ((char *) ent + 0x170) == 0 && *(char *) ((char *) ent + 2) != 3) {
		c1.kind = 0;
		c1.f1 = 0;
		c1.f2 = 0;
		c2.kind = 0;
		c2.f1 = 0;
		c2.f2 = (int) 0x3f28f5c3;
		r = fcn_00495400(9, *ent, 1, &c1, &c2);
		if (r != 0) {
			*out1 = c1;
			*out2 = c2;
			return r;
		}
		return 0;
	}
	if ((*(unsigned int *) ((char *) ent + 0x1e8) & 0x400) == 0 || fcn_0042e410(8) == 0) {
		if (*(char *) ((char *) ent + 2) == 3) {
			if ((*(unsigned char *) ((char *) ent + 0x1e8) & 2) == 0) {
				return 0;
			}
		} else {
			r = fcn_00502cd0(*(int *) (*(int *) ((char *) ent + 0x170) + 0x5d), 2, 6, 0, 0x14);
			if (r == 0) {
				c1.kind = 2;
				c1.f1 = 0x14;
				c1.f2 = 1;
				c2.kind = 0;
				c2.f1 = 0;
				c2.f2 = (int) 0x3e6147ae;
				r = fcn_00495400(9, *ent, 1, &c1, &c2);
				if (r != 0) {
					*out1 = c1;
					*out2 = c2;
					return r;
				}
				return 0;
			}
		}
		t = fcn_0050d320(ent, g_773d75);
		t = (int) ((float) t * 0.66f);
		if (out1->kind == 0) {
			if (*(char *) ((char *) ent + 0x168) == 0) {
				if ((*(unsigned int *) ((char *) ent + 0x1cc) & 0x1c000) != 0) {
					return 0;
				}
				target = 0x10000500;
				i = (int) fcn_0042e410(0x19, &t) & 0xffff;
				r = fcn_004a5340(ent, 1, &target, 0, (float) i + 10.0f);
				if (r == 0) {
					return 0;
				}
				e = (unsigned char *) ((i & 0xffff) * 0x21c + 0x7f4ca0);
			} else {
				r = fcn_004e9310(*(unsigned char *) ((char *) ent + 0x168), 6, nl);
				if (r < 1) {
					return 0;
				}
				best = -1;
				bestI = 0;
				bestVal = 100.0f;
				for (i = 0; i < r; i++) {
					if ((unsigned char *) (nl[i] * 0x21c + 0x7f4ca0) !=
						    *(unsigned char **) 0x77261c) {
						value = (float) fcn_0050f980(*ent, nl[i], 1);
						if (value < bestVal) {
							bestVal = value;
							bestI = i;
						}
					}
				}
				if (best < 0 && bestI == 0 && bestVal == 100.0f) {
					best = 0;
				}
				e = (unsigned char *) (nl[bestI] * 0x21c + 0x7f4ca0);
				t = (int) bestVal;
			}
			if (e != 0) {
				out1->kind = 7;
				out1->f1 = *(int *) (e + 4);
				out1->f2 = 1;
				r = gm_WalkEntityChain(ent, *(unsigned short *) ent);
				t = gm_WalkEntityChain((short *) e, *(unsigned short *) e);
				r = r + t;
				target = (r ^ (r >> 31)) - (r >> 31);
				if (1600.0f < (float) target * 0.0007843137f) {
					r = gm_WalkEntityChain(ent, *(unsigned short *) ent);
					t = gm_WalkEntityChain((short *) e, *(unsigned short *) e);
					r = r + t;
					target = (r ^ (r >> 31)) - (r >> 31);
				}
				target = (unsigned int) (int) ((float) target * 0.0007843137f);
				r = (int) target;
				if (r <= 0) {
					return 0;
				}
				if (r + 320000 <= 0) {
					r = r + 320000;
				}
				out2->kind = 0x12;
				out2->f1 = 0;
				fcn_0042e450();
				out2->f2 = (int) ((float) (r - (int) target) * 500.0f);
				(void) gm_WalkEntityChain(ent, *(unsigned short *) ent);
				out2->f3 = (int) ((float) gm_WalkEntityChain((short *) e, *(unsigned short *) e) * 500.0f);
				return 9;
			}
		} else if (out1->kind == 7 &&
			   (e = (unsigned char *) fcn_00508e40(out1->f1)) != 0 &&
			   e != *(unsigned char **) 0x77261c) {
			int dist;

			dist = (int) ((float) t * 0.15f);
			if ((float) dist < 160000.0f) {
				dist = 160000;
			}
			out2->kind = 0x12;
			out2->f1 = 0;
			r = (int) target;
			fcn_0042e450();
			dist = (int) target - r;
			out2->f2 = (int) ((float) dist * 500.0f);
			(void) gm_WalkEntityChain(ent, *(unsigned short *) ent);
			out2->f3 = (int) ((float) gm_WalkEntityChain((short *) e, *(unsigned short *) e) * 500.0f);
			return 9;
		}
	}
	return 0;
}
