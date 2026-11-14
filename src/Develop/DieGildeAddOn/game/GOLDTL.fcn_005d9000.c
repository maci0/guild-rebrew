#pragma intrinsic(strcat)
#include "client_data.h"
int __cdecl fcn_004a5e60(void *, int, int, int, float, float, int *);
int __cdecl gm_ResolveEntityById(void *, int, int, int);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl gm_WalkEntityChain(int);
void __cdecl fcn_004c51a0(int, int, int, int);
void __cdecl fcn_004c4510(void *, int);
void __cdecl fcn_004c4570(int, int, int, void *);
void __cdecl fcn_004c4670(int, int, int, void *);
void __cdecl fcn_004c5360(void);
unsigned int __cdecl fcn_004a55c0(void *, unsigned int, unsigned int *, float, float, unsigned short *);
int __cdecl srv_GetEntityOfficeSlot(void *, void *, void *);
void __cdecl fcn_004e8240(void *, int, int, int, int);
void __cdecl fcn_00545d40(int, int, char *, int, int, char *);
void __cdecl io_FormatTextBuffer(char *, int, ...);
int __cdecl fcn_0064d41a(char *, char *, ...);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x005d9000 */
void __cdecl fcn_005d9000(unsigned char *e, int mode)
{
	char msg[0x400];
	char t1[0x400];
	char t2[0x400];
	char t3[0x400];
	char t4[0x400];
	void *slots[8];
	unsigned char *ent;
	unsigned char *p;
	unsigned char *best;
	unsigned short w;
	int n;
	int i;
	int r;
	int v;
	int bv;
	int score;
	int a;
	unsigned short b;
	int found; int j;
	char delta;

	if (mode < 0 || mode > 5)
		return;
	io_FormatTextBuffer(msg, 0x1df7, *(unsigned short *) e);
	if (mode == 0) {
		if (fcn_004a5e60(e, 2, 0x80, 0, 0.0f, 100.0f, &found) == 0)
			return;
		gm_ResolveEntityById(&ent, 0, 0, found);
		w = *(unsigned short *) (ent + 0x27);
		best = (unsigned char *) &g_7f4ca0 + w * 0x21c;
		v = gm_WalkEntityChain(*(unsigned short *) best);
		r = gm_RandomMod(3) + 2;
		score = (int) ((double) r * ((double) v * 0.01));
		fcn_004c51a0(*(int *) (best + 4), -1, *(unsigned char *) &g_773d75, score);
		io_FormatTextBuffer(t1, 0x1df8, *(unsigned short *) best, ent, *(unsigned short *) best, score,
					 0x868080 + *(unsigned char *) &g_773d75 * 0x2f4);
	} else if (mode == 1) {
		io_FormatTextBuffer(t1, 0x1df9);
		io_FormatTextBuffer(t2, 0x1dfa);
		fcn_0064d41a(t3, "%s%s%s", msg, t1, t2);
		io_FormatTextBuffer(t2, 0x1dfb);
		fcn_0064d41a(t4, "%s%s", msg, t1, t2);
		strcat(msg, t1);
		p = (unsigned char *) &g_7f4ca2;
		do {
			if (*(short *) (p - 2) != -1) {
				if (*(int *) (p + 0x22) < -0x14) {
					if (gm_RandomMod(2) == 0) {
						if (*p == 6 || *p == 7)
							fcn_00545d40(*(int *) (p + 2), -1, t4, 1, 0x601, 0);
					} else {
						v = *(int *) (p + 0x22) / 2;
						if (v < 0)
							v = -v;
						a = v;
						fcn_004c4510(p - 2, *(int *) (p + 2));
						fcn_004c4570(4, 1, 0x24, &a);
						fcn_004c5360();
						if (*p == 6 || *p == 7)
							fcn_00545d40(*(int *) (p + 2), -1, t3, 1, 0x601, 0);
					}
				} else if (*p == 6 || *p == 7) {
					fcn_00545d40(*(int *) (p + 2), -1, msg, 1, 0x601, 0);
				}
			}
			p += 0x21c;
			if ((int) p > (int) 0x85a0a1)
				return;
		} while (1);
	} else if (mode == 2) {
		if (fcn_004a5e60(e, 2, 0xa07c43b0, 1, 0.0f, 100.0f, &found) == 0)
			return;
		gm_ResolveEntityById(&ent, 0, 0, found);
		w = *(unsigned short *) (ent + 0x27);
		r = (char) gm_RandomMod(0x10);
		delta = (char) (ent[0x5c] - r - 10);
		if (delta < 1)
			return;
		fcn_004c4510(ent, *(int *) (ent + 1));
		fcn_004c4570(1, 1, 0x5c, &delta);
		fcn_004c5360();
		io_FormatTextBuffer(t1, 0x1dfc, *(unsigned short *) ((unsigned char *) &g_7f4ca0 + w * 0x21c),
					 ent);
	} else if (mode == 3) {
		a = 0x400800;
		if (fcn_004a55c0(e, 1, (unsigned int*) &a, 0.0f, 100.0f, &b) == 0)
			return;
		best = (unsigned char *) &g_7f4ca0 + (b & 0xffff) * 0x21c;
		if (srv_GetEntityOfficeSlot(best, &n, &i) == 0)
			return;
		fcn_004e8240((void *) i, 0, 0, 4, 0xff);
		io_FormatTextBuffer(t1, 0x1dfd, *(unsigned short *) best, *(unsigned short *) best,
					 *(unsigned short *) best);
	} else if (mode == 4) {
		a = 0x300000;
		delta = (char) gm_RandomMod(0x15);
		if (fcn_004a55c0(e, 1, (unsigned int*) &a, 0.0f, 100.0f, &b) == 0)
			return;
		best = (unsigned char *) &g_7f4ca0 + (b & 0xffff) * 0x21c;
		n = gm_RandomMod(5) & 0xffff;
		for (i = 5; i != 0; i--) {
			if (*(unsigned char *) (best + 0x80 + n) < 0xe7)
				break;
			n = (n + 1) % 5;
		}
		if (i == 0)
			return;
		fcn_004c4510(best, *(int *) (best + 4));
		fcn_004c4670(1, 1, n + 0x80, &delta);
		fcn_004c5360();
		io_FormatTextBuffer(t1, 0x1dfe, *(unsigned short *) best, *(unsigned short *) best, n + 0x16b7);
	} else {
		n = 0;
		p = (unsigned char *) &g_7f4ca2;
		do {
			if (n > 7)
				break;
			a = *p;
			if (a == 6 || a == 7 || a == 5) {
				slots[n] = p - 2;
				n++;
			}
			p += 0x21c;
		} while ((int) p < (int) 0x85a0a2);
		best = (unsigned char *) slots[0];
		bv = gm_WalkEntityChain(*(unsigned short *) best);
		for (j = 1; j < n; j++) {
			v = gm_WalkEntityChain(*(unsigned short *) (unsigned char *) slots[j]);
			if (v < bv) {
				bv = v;
				best = (unsigned char *) slots[j];
			}
		}
		if (fcn_004a5e60(best, 4, 0xb07d43b4, 1, 0.0f, 100.0f, &found) == 0)
			return;
		r = (gm_RandomMod(5) & 0xffff) + 3;
		score = (int) ((float) r * bv * 0.01f);
		gm_ResolveEntityById(&ent, 0, 0, found);
		fcn_004c51a0(*(int *) (best + 4), -1, *(unsigned char *) &g_773d75, score);
		io_FormatTextBuffer(t1, 0x1dff, *(unsigned short *) best, ent, *(unsigned short *) best, score);
	}
	strcat(msg, t1);
	p = (unsigned char *) &g_7f4ca2;
	do {
		if (*p == 6 || *p == 7)
			fcn_00545d40(*(int *) (p + 2), -1, msg, 1, 0x5fe, 0);
		p += 0x21c;
	} while ((int) p < (int) 0x85a0a2);
}
