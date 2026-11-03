#include <string.h>

void *__cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_00485650(char *, char *);
void __cdecl fcn_00486c40(char *, char *, int);
void __cdecl fcn_00489010(char *, char *);
void __cdecl ai_MeisterCollectTrans(char *);
void __cdecl ai_MeisterTrade(char *, char *);
void __cdecl fcn_00487000(char *);
void __cdecl fcn_00487970(char *, char *, int);
void __cdecl fcn_00487c00(char *, char *, int);
void __cdecl fcn_00487470(char *);
void __cdecl fcn_004888a0(char *);
void __cdecl fcn_00488c00(char *);
char *__cdecl ai_CalcAngriff(char *, int);
unsigned short __cdecl gm_RandomMod(int);
double __cdecl gm_RandomFloat01(void);
void __cdecl fcn_0064d41a(char *, char *, ...);
void *__cdecl fcn_004c5530(char *);
void *__cdecl gm_StartFilteredEntitySearch(int, int);
void *__cdecl gm_FindNextFilteredEntity(void);
int __cdecl fcn_004fa6f0(int, int *, int *);
int __cdecl fcn_0050f950(unsigned short, unsigned short);
char *__cdecl gm_SetupEntityQuery(char *);
void *__cdecl gm_SearchTable67(int);

/* ADDRESS: GOLDTL 0x00480330 */
void __cdecl ai_CalcMeisterWache(char *meister)
{
	char msg[0xf8];
	char buf[0x400];
	char *bld;
	char *p;
	char *res;
	char *cand;
	char *it;
	char *volatile name;
	unsigned short action;
	unsigned char kind;
	int idx1;
	int idx2;
	int dist;
	int count;
	int j;
	int i;
	int seen;
	int n;

	res = fcn_00502cd0(*(int *) (*(int *) (meister + 0x16c) + 0x5d), 2, 6, 0, 0x2a);
	if (res != 0) {
		*(int *) 0x100b0ac = 0;
		*(int *) 0x100b0a8 = 0;
		fcn_00485650(meister, res);
		fcn_00486c40(meister, res, *(int *) (*(int *) (meister + 0x16c) + 0x39));
		fcn_00489010(meister, res);
		ai_MeisterCollectTrans(meister);
		ai_MeisterTrade(meister, res);
	}
	fcn_00487000(meister);
	fcn_00487970(res, meister, 10);
	fcn_00487c00(res, meister, 10);
	fcn_00487470(meister);
	fcn_004888a0(meister);
	fcn_00488c00(meister);
	if (((unsigned short) *(int *) 0x7f4c04 < 7)
		|| ((*(int *) (meister + 4) + (*(unsigned int *) 0x7f4c04 & 0xffff)) % 3 != 0)) {
		*(unsigned int *) (meister + 0x1b4) &= 0xffffffdf;
		return;
	}
	if (*(unsigned int *) (meister + 0x1b4) & 0x20) {
		return;
	}
	*(unsigned int *) (meister + 0x1b4) |= 0x20;
	seen = 0;
	count = 0;
	for (p = (char *) 0x7f4ca0; (int) p < 0x85a0a0; p += 0x21c) {
		if (*(unsigned char *) (p + 8) == 0) {
			continue;
		}
		if (*(unsigned short *) p == 0xffff) {
			continue;
		}
		if (*(unsigned char *) (p + 2) == 0x0a) {
			continue;
		}
		if (*(int *) (p + 0x16c) != *(int *) (meister + 0x16c)) {
			continue;
		}
		if (*(unsigned char *) (p + 0x165) == 0) {
			continue;
		}
		if (*(int *) (p + 0x184) == 0) {
			continue;
		}
		if (*(int *) (*(int *) (p + 0x184) + 0x2c) != *(int *) (*(int *) (meister + 0x16c) + 1)) {
			continue;
		}
		seen++;
		if (*(int *) (p + 0x17c) == 0) {
			count++;
		}
	}
	if (*(int *) 0x100dc20 == *(int *) (meister + 0x16c)) {
		*(int *) 0x100dc34 = count;
		if (*(int *) (meister + 0x1c0) != -1) {
			*(int *) 0x100dc24 = (int) gm_SearchTable67(*(int *) (meister + 0x1c0));
		}
	}
	i = seen >> 1;
	if (i >= seen - i) {
		i = seen - i;
	}
	if (count < i) {
		fcn_0064d41a(buf, "ai_CalcMeisterWache(): Meister %s hat gerade keine Leute...", meister + 0x30);
		return;
	}
	bld = *(char **) (meister + 0x16c);
	kind = *(unsigned char *) (*(unsigned short *) (bld + 0x27) * 0x21c + 0x7f4ca2);
	if (kind == 6 || kind == 7) {
		action = gm_RandomMod(3);
		if (action != 0 && *(int *) (meister + 0x1c0) != -1 && gm_RandomMod(2) != 0) {
			goto city;
		}
	} else {
		if (gm_RandomFloat01() > 0.85) {
			if (count >= 3 && *(int *) 0x7f4c00 >= 7 - *(int *) 0x7747b4) {
				cand = ai_CalcAngriff(meister, count);
				if (cand != 0) {
					goto umland;
				}
				goto city;
			}
		}
		action = gm_RandomMod(3);
	}
	if (action == 4) {
		cand = ai_CalcAngriff(meister, count);
		if (cand != 0) {
			goto umland;
		}
		goto city;
	}
	if (action != 0) {
		goto check;
	}
city:

	fcn_0064d41a(buf, "ai_CalcMeisterWache(): Meister %s m\xf6" "chte in der Stadt patroullieren", meister + 0x30);
	cand = (char *) 0x99ef80;
	idx1 = idx2 = 8;
	for (p = cand; (int) p < 0x99f040; p += 0x18) {
		i = 8;
		it = p;
		do {
			if ((*(unsigned char *) (cand + 4) == 0)
				|| ((*(unsigned char *) (it + 4) != 0)
					&& (((unsigned int) (*(unsigned short *) cand >> 3) + *(unsigned short *) (cand + 2))
						< ((unsigned int) (*(unsigned short *) it >> 3) + *(unsigned short *) (it + 2))))) {
				cand = it;
			}
			it += 0xc0;
			i--;
		} while (i != 0);
	}
	res = 0;
	it = gm_StartFilteredEntitySearch(1, 6);
	while (it != 0) {
		if ((*(int *) (it + 0x61) != 0)
			&& (fcn_004fa6f0(*(int *) (it + 0x61) + 0x4c, &idx1, &idx2) != 0)
			&& (cand == (char *) ((idx1 + idx2 * 8) * 0x18 + 0x99ef80))) {
			if (res == 0) {
				res = it;
			} else {
				i = *(short *) (it + 0x27);
				if (i != -1) {
					dist = fcn_0050f950(*(unsigned short *) meister, *(unsigned short *) (res + 0x27));
					j = fcn_0050f950(*(unsigned short *) meister, (unsigned short) i);
					if (j > dist) {
						res = it;
					}
				}
			}
		}
		it = gm_FindNextFilteredEntity();
	}
	if (res == 0) {
		goto umland;
	}
	fcn_0064d41a(buf, "ai_CalcMeisterWache(): Meister %s patroulliert bei '%s'", meister + 0x30, res + 5);
	memset(msg, 0, sizeof(msg));
	msg[4] = 0x43;
	bld = *(char **) (meister + 0x16c);
	i = *(unsigned short *) (bld + 0x27);
	*(int *) (msg + 8) = *(int *) (i * 0x21c + 0x7f4ca4);
	*(int *) (msg + 0xc) = *(int *) (bld + 1);
	*(int *) (msg + 0x28) = *(int *) 0x7f4c00;
	*(int *) (msg + 0x2c) = *(int *) 0x7f4c04;
	*(int *) (msg + 0x30) = *(int *) 0x7f4c08;
	*(unsigned short *) (msg + 0x34) = *(unsigned short *) 0x7f4c0c;
	msg[0x36] = 2;
	*(int *) (msg + 0x58) = *(int *) (res + 1);
	*(int *) (msg + 0x5c) = *(int *) (bld + 1);
	msg[0x89] = (unsigned char) (gm_RandomMod(4) + 2);
	i = count;
	if (i >= 4) {
		i = 4;
	}
	j = 0;
	if (i > 0) {
		p = (char *) 0x7f4e05;
		do {
			if ((int) p >= 0x85a205) {
				break;
			}
			if ((*(short *) (p - 0x165) != -1) && (*(int *) (p + 7) == *(int *) (meister + 0x16c))
				&& (*(unsigned char *) p != 0) && (*(int *) (p + 0x17) == 0)
				&& (*(int *) (p + 0x1f) != 0)
				&& (*(int *) (*(int *) (p + 0x1f) + 0x2c) == *(int *) (*(int *) (p + 7) + 1))) {
				*(int *) (msg + 0x70 + j * 4) = *(int *) (p - 0x161);
				j++;
			}
			p += 0x21c;
		} while (j < i);
	}
	if (j < 4) {
		for (; j < 4; j++) {
			*(int *) (msg + 0x70 + j * 4) = -1;
		}
	}
	if (*(int *) (msg + 0x70) == -1) {
		return;
	}
	fcn_004c5530(msg);
	return;
check:
	if (action != 1) {
		if (action < 2) {
			return;
		}
		goto umland;
	}
	/* pruefen */
	name = meister + 0x30;
	fcn_0064d41a(buf, "ai_CalcMeisterWache(): Meister %s m\xf6" "chte Betrieb pr\xfc" "fen", name);
	cand = (char *) 0x99ef80;
	idx1 = idx2 = 8;
	for (p = cand; (int) p < 0x99f040; p += 0x18) {
		i = 8;
		it = p;
		do {
			if ((*(unsigned char *) (cand + 4) == 0)
				|| ((*(unsigned char *) (it + 4) != 0)
					&& (((unsigned int) (*(unsigned short *) cand >> 3) + *(unsigned short *) (cand + 2))
						< ((unsigned int) (*(unsigned short *) it >> 3) + *(unsigned short *) (it + 2))))) {
				cand = it;
			}
			it += 0xc0;
			i--;
		} while (i != 0);
	}
	res = 0;
	it = gm_StartFilteredEntitySearch(1, 6);
	while (it != 0) {
		if ((*(int *) (it + 0x61) != 0)
			&& (fcn_004fa6f0(*(int *) (it + 0x61) + 0x4c, &idx1, &idx2) != 0)
			&& (cand == (char *) ((idx1 + idx2 * 8) * 0x18 + 0x99ef80))) {
			if (res == 0) {
				res = it;
			} else {
				i = *(short *) (it + 0x27);
				if ((i != -1) && ((*(unsigned char *) (it + 0x5a) & 1) == 0)) {
					dist = fcn_0050f950(*(unsigned short *) meister,
										*(unsigned short *) (res + 0x27));
					j = fcn_0050f950(*(unsigned short *) meister, (unsigned short) i);
					if (j < dist) {
						res = it;
					}
				}
			}
		}
		it = gm_FindNextFilteredEntity();
	}
	if (res != 0) {
		fcn_0064d41a(buf, "ai_CalcMeisterWache(): Meister %s \xfc" "berpr\xfc" "ft '%s'", name, res + 5);
		memset(msg, 0, sizeof(msg));
		msg[4] = 0x64;
		bld = *(char **) (meister + 0x16c);
		i = *(unsigned short *) (bld + 0x27);
		*(int *) (msg + 8) = *(int *) (i * 0x21c + 0x7f4ca4);
		*(int *) (msg + 0xc) = *(int *) (bld + 1);
		*(int *) (msg + 0x28) = *(int *) 0x7f4c00;
		*(int *) (msg + 0x2c) = *(int *) 0x7f4c04;
		*(int *) (msg + 0x30) = *(int *) 0x7f4c08;
		*(unsigned short *) (msg + 0x34) = *(unsigned short *) 0x7f4c0c;
		msg[0x36] = 1;
		*(int *) (msg + 0x5c) = *(int *) (res + 1);
		*(int *) (msg + 0x60) = *(int *) (bld + 1);
		it = gm_SetupEntityQuery(bld);
		if (it == 0) {
			goto failed;
		}
		*(int *) (msg + 0x64) = *(int *) (it + 2);
		*(int *) (msg + 0x58) = -1;
		if (name != 0) {
			return;
		}
		p = (char *) 0x7f4e05;
		n = 0;
		do {
			if ((int) p >= 0x85a205) {
				break;
			}
			if ((*(short *) (p - 0x165) != -1) && (*(int *) (p + 7) == *(int *) (meister + 0x16c))
				&& (*(unsigned char *) p != 0) && (*(int *) (p + 0x17) == 0)
				&& (*(int *) (p + 0x1f) != 0)
				&& (*(int *) (*(int *) (p + 0x1f) + 0x2c)
					== *(int *) (*(int *) (p + 7) + 1))) {
				*(int *) (msg + 0x58) = *(int *) (p - 0x161);
				n++;
			}
			p += 0x21c;
		} while (n == 0);
		if (*(int *) (msg + 0x58) == -1) {
			return;
		}
		fcn_004c5530(msg);
		return;
	}
	goto umland;
	return;
umland:
	fcn_0064d41a(buf, "ai_CalcMeisterWache(): Meister %s patroulliert im Umland", meister + 0x30);
	memset(msg, 0, sizeof(msg));
	msg[4] = 0x65;
	bld = *(char **) (meister + 0x16c);
	i = *(unsigned short *) (bld + 0x27);
	*(int *) (msg + 8) = *(int *) (i * 0x21c + 0x7f4ca4);
	*(int *) (msg + 0xc) = *(int *) (bld + 1);
	*(int *) (msg + 0x28) = *(int *) 0x7f4c00;
	*(int *) (msg + 0x2c) = *(int *) 0x7f4c04;
	*(int *) (msg + 0x30) = *(int *) 0x7f4c08;
	*(unsigned short *) (msg + 0x34) = *(unsigned short *) 0x7f4c0c;
	msg[0x36] = 2;
	action = gm_RandomMod(8);
	strcpy(msg + 0x58, (char *) 0x6a4770 + (action & 0xffff) * 0x20);
	*(int *) (msg + 0x78) = *(int *) (bld + 1);
	it = gm_SetupEntityQuery(bld);
	if (it == 0) {
failed:
		fcn_0064d41a(buf, "ai_CalcMeisterWache() : gm_GetGebaeudeHauptraum() failed !!!");
		return;
	}
	*(int *) (msg + 0x7c) = *(int *) (it + 2);
	i = count;
	if (i >= 6) {
		i = 6;
	}
	j = 0;
	n = 0;
	if (i > 0) {
		p = (char *) 0x7f4e05;
		do {
			if ((int) p >= 0x85a205) {
				break;
			}
			if ((*(short *) (p - 0x165) != -1) && (*(int *) (p + 7) == *(int *) (meister + 0x16c))
				&& (*(unsigned char *) p != 0) && (*(int *) (p + 0x17) == 0)
				&& (*(int *) (p + 0x1f) != 0)
				&& (*(int *) (*(int *) (p + 0x1f) + 0x2c) == *(int *) (*(int *) (p + 7) + 1))) {
				*(int *) (msg + 0x38 + n * 4) = *(int *) (p - 0x161);
				n++;
				j++;
			}
			p += 0x21c;
		} while (j < i);
	}
	for (; n < 6; n++) {
		*(int *) (msg + 0x38 + n * 4) = -1;
	}
	if (*(int *) (msg + 0x38) != -1 && j > 1) {
		fcn_004c5530(msg);
	}
}
