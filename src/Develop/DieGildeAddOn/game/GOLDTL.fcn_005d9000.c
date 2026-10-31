#pragma intrinsic(strcat)

void *__cdecl fcn_004a5e60(void *, int, int, int, int, float, void *);
int __cdecl gm_ResolveEntityById(void *, int, int, int);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl gm_WalkEntityChain(int);
void __cdecl fcn_004c51a0(int, int, int, int);
void __cdecl fcn_004c4510(void *, int);
void __cdecl fcn_004c4570(int, int, int, void *);
void __cdecl fcn_004c4670(int, int, int, void *);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004a55c0(void *, int, void *, int, float, void *, int, int);
int __cdecl srv_GetEntityOfficeSlot(void *, void *, void *);
void __cdecl fcn_004e8240(void *, int, int, int, int);
void __cdecl fcn_00545d40(int, int, char *, int, int, char *);
void __cdecl io_FormatTextBuffer(char *, int, ...);
int __cdecl fcn_0064d41a(char *, char *, ...);

/* ADDRESS: GOLDTL 0x005d9000 */
void __cdecl fcn_005d9000(unsigned char *e, int mode)
{
	char msg[0x400];
	char t1[0x400];
	char t2[0x400];
	char t3[0x400];
	char t4[0x418];
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
	int b;

	if (mode < 0 || mode > 5)
		return;
	io_FormatTextBuffer(msg, 0x1df7, *(unsigned short *) e);
	if (mode == 0) {
		if ((ent = (unsigned char *) fcn_004a5e60(e, 2, 0, 0, 0x80, 100.0f, &slots[0])) == 0)
			return;
		gm_ResolveEntityById(&slots[0], 0, 0, 0);
		w = *(unsigned short *) (ent + 0x27);
		best = (unsigned char *) 0x7f4ca0 + w * 0x21c;
		v = gm_WalkEntityChain(*(unsigned short *) best);
		r = gm_RandomMod(3) + 2;
		score = (int) ((float) r * (float) v * 100.0f);
		fcn_004c51a0(*(int *) (best + 4), -1, *(unsigned char *) 0x773d75, score);
		io_FormatTextBuffer(msg, 0x1df8, *(unsigned short *) best, ent, *(unsigned short *) best, score,
					 0x868080 + *(unsigned char *) 0x773d75 * 0x2f4);
	} else if (mode == 1) {
		io_FormatTextBuffer(t1, 0x1df9);
		io_FormatTextBuffer(t2, 0x1dfa, t1);
		fcn_0064d41a(t3, "%s%s%s", msg, t1, t2);
		io_FormatTextBuffer(t2, 0x1dfb, t3);
		fcn_0064d41a(t4, "%s%s", msg, t2);
		strcat(msg, t4);
		p = (unsigned char *) 0x7f4ca2;
		do {
			if (*(short *) (p - 2) != -1) {
				if (*(int *) (p + 0x22) < -0x14) {
					if (gm_RandomMod(2) == 0) {
						if (*p == 6 || *p == 7)
							fcn_00545d40(*(int *) (p + 2), -1, msg, 0, 0x601,
										 "_NACHRICHTEN_HS_63");
					} else {
						v = *(int *) (p + 0x22) / 2;
						if (v < 0)
							v = -v;
						a = v;
						fcn_004c4510(p - 2, *(int *) (p + 2));
						fcn_004c4570(4, 1, 0x24, &a);
						fcn_004c5360();
						if (*p == 6 || *p == 7)
							fcn_00545d40(*(int *) (p + 2), -1, msg, 1, 0x601,
										 "_NACHRICHTEN_HS_63");
					}
				} else if (*p == 6 || *p == 7) {
					fcn_00545d40(*(int *) (p + 2), -1, msg, 0, 0x601, "_NACHRICHTEN_HS_63");
				}
			}
			p += 0x21c;
			if ((int) p > (int) 0x85a0a1)
				return;
		} while (1);
	} else if (mode == 2) {
		if ((ent = (unsigned char *) fcn_004a5e60(e, 2, 0, 0, 0x80, 100.0f, &slots[0])) == 0)
			return;
		gm_ResolveEntityById(&slots[0], 0, 0, 0);
		w = *(unsigned short *) (ent + 0x27);
		r = (char) gm_RandomMod(0x10);
		if ((char) ((char) ent[0x5c] - r - 10) < 1)
			return;
		fcn_004c4510(ent, *(int *) (ent + 1));
		n = 0x5c;
		fcn_004c4570(1, 1, 0x5c, &n);
		fcn_004c5360();
		io_FormatTextBuffer(msg, 0x1dfc, *(unsigned short *) ((unsigned char *) 0x7f4ca0 + w * 0x21c),
					 ent, n, n);
	} else if (mode == 3) {
		a = 0x400800;
		if (fcn_004a55c0(e, 1, &a, 0, 100.0f, &b, 0, 0) == 0)
			return;
		best = (unsigned char *) 0x7f4ca0 + (b & 0xffff) * 0x21c;
		if (srv_GetEntityOfficeSlot(best, &n, &i) == 0)
			return;
		fcn_004e8240((void *) i, 0, 0, 4, 0xff);
		io_FormatTextBuffer(msg, 0x1dfd, *(unsigned short *) best, *(unsigned short *) best,
					 *(unsigned short *) best, n, i);
	} else if (mode == 4) {
		a = 0x300000;
		r = gm_RandomMod(0x15);
		if (fcn_004a55c0(e, 1, &a, 0, 100.0f, &b, 0, 0) == 0)
			return;
		best = (unsigned char *) 0x7f4ca0 + (b & 0xffff) * 0x21c;
		n = gm_RandomMod(5) & 0xffff;
		for (i = 5; i != 0; i--) {
			if (*(unsigned char *) (best + 0x80 + n) < 0xe7)
				break;
			n = (n + 1) % 5;
		}
		if (i == 0)
			return;
		fcn_004c4510(best, *(int *) (best + 4));
		v = 1;
		fcn_004c4670(1, 1, n + 0x80, &v);
		fcn_004c5360();
		io_FormatTextBuffer(msg, 0x1dfe, *(unsigned short *) best, *(unsigned short *) best, n + 0x16b7,
					 v, r, 1);
	} else {
		n = 0;
		p = (unsigned char *) 0x7f4ca2;
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
		if (n == 0)
			return;
		best = (unsigned char *) slots[0];
		bv = gm_WalkEntityChain(*(unsigned short *) best);
		for (i = 1; i < n; i++) {
			v = gm_WalkEntityChain(*(unsigned short *) (unsigned char *) slots[i]);
			if (v < bv) {
				bv = v;
				best = (unsigned char *) slots[i];
			}
		}
		if ((ent = (unsigned char *) fcn_004a5e60(e, 2, 0, 0, 0x80, 100.0f, &slots[0])) == 0)
			return;
		r = (gm_RandomMod(5) & 0xffff) + 3;
		score = bv * r;
		gm_ResolveEntityById(&slots[0], 0, 0, 0);
		fcn_004c51a0(*(int *) (best + 2), -1, *(unsigned char *) 0x773d75, score);
		io_FormatTextBuffer(msg, 0x1dff, *(unsigned short *) best, ent, *(unsigned short *) best, score,
					 *(int *) (best + 2), 5);
	}
	p = (unsigned char *) 0x7f4ca2;
	do {
		if ((*p == 6 || *p == 7) && *(short *) (p - 2) != -1)
			fcn_00545d40(*(int *) (p + 2), -1, msg, 0, 0x5fe, "_NACHRICHTEN_HS_63");
		p += 0x21c;
	} while ((int) p < (int) 0x85a0a2);
}
