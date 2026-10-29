void *__cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_00485650(void *, int);
void __cdecl fcn_00486c40(void *, int, int);
void __cdecl fcn_00489010(void *, int);
void __cdecl ai_MeisterCollectTrans(void *);
void __cdecl ai_MeisterTrade(void *, int);
void __cdecl fcn_00487000(void *);
void __cdecl fcn_00487970(int, void *, int);
void __cdecl fcn_00487c00(int, void *, int);
void __cdecl fcn_00487470(void *);
void __cdecl fcn_004888a0(void *);
void __cdecl fcn_00488c00(void *);
int __cdecl ai_CalcAngriff(void *, int);
unsigned short __cdecl gm_RandomMod(int);
float __cdecl gm_RandomFloat01(void);
int __cdecl _ftol(void);
int __cdecl fcn_0064d41a(char *, char *, ...);
void __cdecl fcn_004c5530(void *);
void *__cdecl gm_StartFilteredEntitySearch(int);
void *__cdecl gm_FindNextFilteredEntity(void);
int __cdecl fcn_004fa6f0(int, int *, int *);
int __cdecl fcn_0050f950(unsigned short, unsigned short);
void *__cdecl gm_SetupEntityQuery(void *);
void *__cdecl gm_SearchTable67(int);

/* AI master patrol decision (0x00480330, 2340 bytes). First-pass semantic
 * reconstruction; frame/slot layout and codegen do not match the target yet. */
/* ADDRESS: GOLDTL 0x00480330 */
void __cdecl ai_CalcMeisterWache(void *arg)
{
	unsigned char *e;
	unsigned char *it;
	unsigned short *p;
	unsigned short *best;
	unsigned short *cur;
	unsigned char pkt[0xf8];
	char text[0x400];
	int ids[8];
	int slot;
	int count;
	int seen;
	int half;
	int n;
	int i;
	int j;
	int r;
	int dist;
	int idx1;
	int idx2;
	unsigned short u;
	float f;

	e = (unsigned char *) arg;
	slot = 0;
	idx1 = 0;
	idx2 = 0;
	r = (int) fcn_00502cd0(*(int *) (*(int *) (e + 0x16c) + 0x5d), 2, 6, 0);
	if (r != 0) {
		slot = r;
		*(int *) 0x100b0ac = 0;
		*(int *) 0x100b0a8 = 0;
		fcn_00485650(e, r);
		fcn_00486c40(e, r, *(int *) (*(int *) (e + 0x16c) + 0x39));
		fcn_00489010(e, r);
		ai_MeisterCollectTrans(e);
		ai_MeisterTrade(e, r);
	}
	fcn_00487000(e);
	fcn_00487970(slot, e, 10);
	fcn_00487c00(slot, e, 10);
	fcn_00487470(e);
	fcn_004888a0(e);
	fcn_00488c00(e);
	if ((*(unsigned short *) 0x7f4c04 < 7)
		|| ((*(int *) (e + 4) + (*(unsigned int *) 0x7f4c04 & 0xffff)) % 3 != 0)) {
		*(unsigned int *) (e + 0x1b4) &= 0xffffffdf;
		return;
	}
	if ((*(unsigned int *) (e + 0x1b4) & 0x20) != 0)
		return;
	seen = 0;
	count = 0;
	*(unsigned int *) (e + 0x1b4) |= 0x20;
	p = (unsigned short *) 0x7f4ca0;
	do {
		if ((*((unsigned char *) p + 8) != 0) && (*p != 0xffff) && (*((unsigned char *) p + 2) != '\n')
			&& (*(int *) ((char *) p + 0x16c) == *(int *) (e + 0x16c))
			&& (*((unsigned char *) p + 0x165) != 0)
			&& (*(int *) ((char *) p + 0x184) != 0)
			&& (*(int *) (*(int *) ((char *) p + 0x184) + 0x2c)
				== *(int *) (*(int *) ((char *) p + 0x16c) + 1))) {
			seen++;
			if (*(int *) ((char *) p + 0x17c) == 0)
				count++;
		}
		p = (unsigned short *) ((char *) p + 0x21c);
	} while ((int) p < (int) 0x85a0a0);
	if (*(int *) 0x100dc20 == *(int *) (e + 0x16c)) {
		*(int *) 0x100dc34 = count;
		if (*(int *) (e + 0x1c0) != -1)
			*(int *) 0x100dc24 = (int) gm_SearchTable67(*(int *) (e + 0x1c0));
	}
	half = seen >> 1;
	if (seen - half <= half)
		half = seen - half;
	if (count < half) {
		fcn_0064d41a(text, "ai_CalcMeisterWache(): Meister %s hat gerade keine Leute...", e + 0x30);
		return;
	}
	if (*(unsigned char *) (*(unsigned short *) (*(int *) (e + 0x16c) + 0x27) * 0x21c + 0x7f4ca2) == 6
		|| *(unsigned char *) (*(unsigned short *) (*(int *) (e + 0x16c) + 0x27) * 0x21c + 0x7f4ca2) == 7) {
		u = gm_RandomMod(3);
		if (u == 0 || (*(int *) (e + 0x1c0) == -1 || gm_RandomMod(2) == 0))
			goto code72;
code93:
		fcn_0064d41a(text, "ai_CalcMeisterWache(): Meister %s m\366chte in der Stadt patroullieren", e + 0x30);
		best = (unsigned short *) 0x99ef80;
		idx1 = 8;
		cur = (unsigned short *) 0x99ef80;
		idx2 = 8;
		do {
			i = 8;
			p = cur;
			do {
				if ((*((unsigned char *) best + 4) == 0)
					|| ((*((unsigned char *) p + 4) != 0)
						&& (((unsigned int) (*best >> 3) + best[1])
							< ((unsigned int) (*p >> 3) + p[1]))))
					best = p;
				p = p + 0x60;
				i--;
			} while (i != 0);
			cur = cur + 0xc;
		} while ((int) cur < (int) 0x99f040);
		r = 0;
		it = (unsigned char *) gm_StartFilteredEntitySearch(1);
		if (it != 0) {
			do {
				if ((*(int *) (it + 0x61) != 0)
					&& (fcn_004fa6f0(*(int *) (it + 0x61) + 0x4c, &idx1, &idx2) != 0)
					&& (best == (unsigned short *) ((idx2 + idx1 * 8) * 0x18 + 0x99ef80))) {
					if (r == 0) {
codeb:
						r = (int) it;
					} else {
						i = *(short *) (it + 0x27);
						if (i != -1) {
							dist = fcn_0050f950(*(unsigned short *) e, *(unsigned short *) (r + 0x27));
							j = fcn_0050f950(*(unsigned short *) e, (unsigned short) i);
							if (dist < j)
								goto codeb;
						}
					}
				}
				it = (unsigned char *) gm_FindNextFilteredEntity();
			} while (it != 0);
			if (r != 0) {
				fcn_0064d41a(text, "ai_CalcMeisterWache(): Meister %s patroulliert bei '%s'", e + 0x30);
				for (i = 0; i < 0x3e; i++)
					((int *) pkt)[i] = 0;
				n = *(int *) (e + 0x16c);
				pkt[4] = 0x43;
				*(int *) (pkt + 8) = *(int *) (*(unsigned short *) (n + 0x27) * 0x21c + 0x7f4ca4);
				*(int *) (pkt + 0xc) = *(int *) (n + 1);
				*(int *) (pkt + 0x28) = *(int *) 0x7f4c00;
				*(int *) (pkt + 0x2c) = *(int *) 0x7f4c04;
				*(int *) (pkt + 0x30) = *(int *) 0x7f4c08;
				*(unsigned short *) (pkt + 0x34) = *(unsigned short *) 0x7f4c0c;
				pkt[0x36] = 2;
				*(int *) (pkt + 0x58) = *(int *) (r + 1);
				*(int *) (pkt + 0x5c) = *(int *) (n + 1);
				pkt[0x89] = (unsigned char) (gm_RandomMod(4) + 2);
				i = count;
				if (count > 3)
					i = 4;
				j = 0;
				if (i > 0) {
					it = (unsigned char *) 0x7f4e05;
					do {
						if ((int) it > (int) 0x85a204)
							break;
						if ((*(short *) (it - 0x165) != -1)
							&& (*(int *) (it + 7) == *(int *) (e + 0x16c))
							&& (*it != 0)
							&& (*(int *) (it + 0x17) == 0)
							&& (*(int *) (it + 0x1f) != 0)
							&& (*(int *) (*(int *) (it + 0x1f) + 0x2c)
								== *(int *) (*(int *) (it + 7) + 1))) {
							ids[j] = *(int *) (it - 0x161);
							j++;
						}
						it += 0x21c;
					} while (j < i);
					if (j > 3)
						goto fill;
				}
				for (; j < 4; j++)
					ids[j] = -1;
fill:
				if (ids[0] == -1)
					return;
				fcn_004c5530(pkt);
				return;
			}
		}
	} else {
		f = gm_RandomFloat01();
		if ((f <= 0.85f) || (count < 3 || *(int *) 0x7f4c00 < 7 - *(int *) 0x7747b4)) {
			u = gm_RandomMod(3);
code72:
			if (u == 4)
				goto code77;
			if (u == 0)
				goto code93;
			if (u == 1) {
				fcn_0064d41a(text, "ai_CalcMeisterWache(): Meister %s m\366chte Betrieb pr\374fen", e + 0x30);
				best = (unsigned short *) 0x99ef80;
				idx1 = 8;
				cur = (unsigned short *) 0x99ef80;
				idx2 = 8;
				do {
					i = 8;
					p = cur;
					do {
						if ((*((unsigned char *) best + 4) == 0)
							|| ((*((unsigned char *) p + 4) != 0)
								&& (((unsigned int) (*best >> 3) + best[1])
									< ((unsigned int) (*p >> 3) + p[1]))))
							best = p;
						p = p + 0x60;
						i--;
					} while (i != 0);
					cur = cur + 0xc;
				} while ((int) cur < (int) 0x99f040);
				r = 0;
				it = (unsigned char *) gm_StartFilteredEntitySearch(1);
				if (it != 0) {
					do {
						if ((*(int *) (it + 0x61) != 0)
							&& (fcn_004fa6f0(*(int *) (it + 0x61) + 0x4c, &idx1, &idx2) != 0)
							&& (best == (unsigned short *) ((idx2 + idx1 * 8) * 0x18 + 0x99ef80))) {
							if (r == 0) {
codeb2:
								r = (int) it;
							} else {
								i = *(short *) (it + 0x27);
								if ((i != -1) && ((*(unsigned char *) (it + 0x5a) & 1) == 0)) {
									dist = fcn_0050f950(*(unsigned short *) e,
														*(unsigned short *) (r + 0x27));
									j = fcn_0050f950(*(unsigned short *) e, (unsigned short) i);
									if (j < dist)
										goto codeb2;
								}
							}
						}
						it = (unsigned char *) gm_FindNextFilteredEntity();
					} while (it != 0);
					if (r != 0) {
						fcn_0064d41a(text, "ai_CalcMeisterWache(): Meister %s \374berpr\374ft '%s'",
									 e + 0x30);
						for (i = 0; i < 0x3e; i++)
							((int *) pkt)[i] = 0;
						pkt[4] = 100;
						n = *(int *) (e + 0x16c);
						*(int *) (pkt + 8) = *(int *) (*(unsigned short *) (n + 0x27) * 0x21c + 0x7f4ca4);
						*(int *) (pkt + 0xc) = *(int *) (n + 1);
						*(int *) (pkt + 0x28) = *(int *) 0x7f4c00;
						*(int *) (pkt + 0x2c) = *(int *) 0x7f4c04;
						*(int *) (pkt + 0x30) = *(int *) 0x7f4c08;
						*(unsigned short *) (pkt + 0x34) = *(unsigned short *) 0x7f4c0c;
						pkt[0x36] = 1;
						*(int *) (pkt + 0x5c) = *(int *) (r + 1);
						*(int *) (pkt + 0x60) = *(int *) (n + 1);
						it = (unsigned char *) gm_SetupEntityQuery((void *) n);
						if (it != 0) {
							*(int *) (pkt + 0x64) = *(int *) (it + 2);
							ids[0] = -1;
							ids[2] = -1;
							ids[4] = -1;
							ids[6] = -1;
							if (e + 0x30 != 0) {
								it = (unsigned char *) 0x7f4e05;
								j = 0;
								do {
									if ((int) it > (int) 0x85a204)
										break;
									if ((*(short *) (it - 0x165) != -1)
										&& (*(int *) (it + 7) == *(int *) (e + 0x16c))
										&& (*it != 0)
										&& (*(int *) (it + 0x17) == 0)
										&& (*(int *) (it + 0x1f) != 0)
										&& (*(int *) (*(int *) (it + 0x1f) + 0x2c)
											== *(int *) (*(int *) (it + 7) + 1))) {
										ids[0] = *(int *) (it - 0x161);
										j++;
										ids[2] = ids[0];
									}
									it += 0x21c;
								} while (j == 0);
								goto fill;
							}
						}
						goto codea01;
					}
				}
			} else if (u < 2) {
				return;
			}
		} else {
code77:
			r = ai_CalcAngriff(e, count);
			if (r == 0)
				goto code93;
		}
	}
	fcn_0064d41a(text, "ai_CalcMeisterWache(): Meister %s patroulliert im Umland", e + 0x30);
	for (i = 0; i < 0x3e; i++)
		((int *) pkt)[i] = 0;
	pkt[4] = 0x65;
	*(int *) (pkt + 8) = *(int *) (*(unsigned short *) (*(int *) (e + 0x16c) + 0x27) * 0x21c + 0x7f4ca4);
	*(int *) (pkt + 0xc) = *(int *) (*(int *) (e + 0x16c) + 1);
	*(int *) (pkt + 0x28) = *(int *) 0x7f4c00;
	*(int *) (pkt + 0x2c) = *(int *) 0x7f4c04;
	*(int *) (pkt + 0x30) = *(int *) 0x7f4c08;
	*(unsigned short *) (pkt + 0x34) = *(unsigned short *) 0x7f4c0c;
	pkt[0x36] = 2;
	u = gm_RandomMod(8);
	{
		char *src = "sp_AUFLAUERLEGEN_NORDEN" + (u & 0xffff) * 0x20;
		char *dst = (char *) (pkt + 0x58);
		while (*src != 0)
			*dst++ = *src++;
		*dst = 0;
	}
	*(int *) (pkt + 0x78) = *(int *) (*(int *) (e + 0x16c) + 1);
	it = (unsigned char *) gm_SetupEntityQuery(*(void **) (e + 0x16c));
	if (it == 0) {
codea01:
		fcn_0064d41a(text, "ai_CalcMeisterWache() : gm_GetGebaeudeHauptraum() failed !!!", (int) e);
		return;
	}
	*(int *) (pkt + 0x7c) = *(int *) (it + 2);
	i = count;
	if (count > 5)
		i = 6;
	j = 0;
	n = 0;
	if (i > 0) {
		it = (unsigned char *) 0x7f4e05;
		do {
			if ((int) it > (int) 0x85a204)
				break;
			if ((*(short *) (it - 0x165) != -1)
				&& (*(int *) (it + 7) == *(int *) (e + 0x16c))
				&& (*it != 0)
				&& (*(int *) (it + 0x17) == 0)
				&& (*(int *) (it + 0x1f) != 0)
				&& (*(int *) (*(int *) (it + 0x1f) + 0x2c)
					== *(int *) (*(int *) (it + 7) + 1))) {
				ids[n] = *(int *) (it - 0x161);
				n++;
				j++;
			}
			it += 0x21c;
		} while (j < i);
	}
	for (; n < 6; n++)
		ids[n] = -1;
	if ((ids[0] != -1) && (j > 1))
		fcn_004c5530(pkt);
}
