int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_004849b0(int, int, int);
void __cdecl fcn_00487360(int);
void __cdecl fcn_00487970(int, int, int);
void __cdecl fcn_00487c00(int, int, int);
void __cdecl fcn_00487470(int);
void __cdecl fcn_00488a20(int);
void __cdecl fcn_00488e10(int);
void __cdecl fcn_004833a0(int);
int __cdecl fcn_00486640(int, void *, int);
void __cdecl fcn_004868d0(int, void *);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_005b1e40(int);
int __cdecl fcn_00503d10(int);
int __cdecl gm_eval_SlotVoll(int, int, int);
void __cdecl fcn_0064d41a(char *, char *, ...);
void __cdecl fcn_0047e220(int);
void __cdecl fcn_0047e0e0(int, int);
void __cdecl fcn_00487e60(int, int);
void __cdecl fcn_00529160(int, int, int, int);
void __cdecl fcn_004831f0(int);
void __cdecl ai_MeisterCollectTrans(int);
void __cdecl ai_MeisterTrade(int, int);
void __cdecl fcn_00487f90(void *);

typedef struct {
	int v[0x16];
} ENTRY;
typedef struct {
	int v[0x10];
} RECORD;

/* ADDRESS: GOLDTL 0x00483480 */
void __cdecl fcn_00483480(int a0)
{
	void *rec1;
	int i;
	struct ARG {
		int kind;
		void *owner;
		void *entry;
		void *rec;
		int zero;
		int k;
		int cur;
		int z1;
		int z2;
	} arg;
	int order[0x20];
	char msg[0x100];
	void *rec0;
	int found;
	void *sp;
	int gate;
	short mode;

	found = 0;
	rec0 = (void *) fcn_00502cd0(*(int *) (*(int *) (a0 + 0x16c) + 0x5d), 2, 6, 0, 0xff);
	if (rec0 == 0) {
		return;
	}
	rec1 = (void *) fcn_00502cd0(*(int *) (*(int *) (a0 + 0x16c) + 0x5d), 2, 6, 0, 0x2a);
	if (rec1 == 0) {
		return;
	}
	fcn_004849b0(a0, (int) rec0, (int) rec1);
	fcn_00487360(a0);
	fcn_00487970((int) rec1, a0, 0x4b);
	fcn_00487c00((int) rec1, a0, 0x19);
	fcn_00487470(a0);
	fcn_00488a20(a0);
	fcn_00488e10(a0);
	fcn_004833a0(a0);
	mode = *(short *) 0x7f4c04;
	if (mode == 8 || mode == 0xd) {
		if ((*(unsigned int *) (a0 + 0x1b4) & 0x100) == 0) {
			*(unsigned short *) (a0 + 0x1bc) = 0;
			*(unsigned int *) (a0 + 0x1b4) |= 0x100;
		} else if (*(unsigned short *) (a0 + 0x1bc) != 0) {
			int n;

			n = *(int *) 0x100b0ac;
			if (n > 0) {
				for (i = 0; i < n; i++) {
					sp = (void *) (i * 0x58 + 0x100d0c0);
					if (*(int *) sp == (int) *(unsigned short *) (a0 + 0x1bc)) {
						if (*(int *) ((char *) sp + 0x40) >=
							    (int) *(unsigned short *) (*(int *) sp * 0x41 + 0x36 + *(int *) 0x99ec10) &&
						    fcn_00486640(a0, sp, 1) != 0) {
							*(unsigned int *) ((char *) sp + 0x54) |= 8;
							fcn_004868d0(a0, sp);
							*(unsigned short *) (a0 + 0x1bc) = *(unsigned short *) sp;
							goto tail;
						}
						goto type6;
					}
				}
				goto shuffle;
			}
		}
	} else {
		int n;

		n = *(int *) 0x100b0ac;
		for (i = 0; i < n; i++) {
			sp = (void *) (i * 0x58 + 0x100d0c0);
			if (*(int *) sp == (int) *(unsigned short *) (a0 + 0x1bc)) {
				if (*(int *) ((char *) sp + 0x40) >=
					    (int) *(unsigned short *) (*(int *) sp * 0x41 + 0x36 + *(int *) 0x99ec10) &&
				    fcn_00486640(a0, sp, 1) != 0) {
					*(unsigned int *) ((char *) sp + 0x54) |= 8;
					fcn_004868d0(a0, sp);
					*(unsigned short *) (a0 + 0x1bc) = *(unsigned short *) sp;
					found = 1;
				}
				break;
			}
		}
		*(unsigned int *) (a0 + 0x1b4) &= 0xfffffeffu;
		if (found != 0) {
			goto tail;
		}
	}
type6:
	if (*(char *) ((int) *(unsigned short *) (*(int *) (a0 + 0x16c) + 0x27) * 0x21c + 0x7f4ca2) == 6) {
		gate = fcn_005b1e40(*(int *) (a0 + 0x16c));
		if (gate != 0) {
			for (i = 0; i < 0x20; i++) {
				sp = (void *) (i * 0x58 + 0x100d0c0);
				if (*(int *) sp == gate) {
					int have;
					int res;

					if ((int) *(unsigned char *) ((int) rec1 + 0x1c) >= *(int *) ((char *) sp + 0x1c) &&
					    (int) *(unsigned char *) ((int) rec1 + 0x1d) >= *(int *) ((char *) sp + 0x20) &&
					    *(int *) ((char *) sp + 0x40) >=
						    (int) *(unsigned short *) (*(int *) sp * 0x41 + 0x36 + *(int *) 0x99ec10) &&
					    (res = fcn_00503d10(*(int *) sp)) != 0) {
						have = gm_eval_SlotVoll(res, *(int *) sp, 1000000);
						if ((int) *(unsigned short *) (*(int *) sp * 0x41 + 0x36 + *(int *) 0x99ec10) +
							    *(int *) ((char *) sp + 0x3c) <= have) {
							if (fcn_00486640(a0, sp, 1) != 0) {
								*(unsigned int *) ((char *) sp + 0x54) |= 8;
								fcn_004868d0(a0, sp);
								*(unsigned short *) (a0 + 0x1bc) = *(unsigned short *) sp;
								fcn_0064d41a(msg,
									"Produktion von %s starten, da Humanplayer es so will.",
									*(int *) sp * 0x41 + 1 + *(int *) 0x99ec10);
								goto tail;
							}
							if (fcn_00486640(a0, sp, 0) != 0) {
								fcn_004868d0(a0, sp);
								*(unsigned short *) (a0 + 0x1bc) = *(unsigned short *) sp;
								fcn_0064d41a(msg,
									"Produktion von %s starten obwohl Rohstoffe fehlen, da der spieler es so will",
									*(int *) sp * 0x41 + 1 + *(int *) 0x99ec10);
								goto tail;
							}
						}
					}
					break;
				}
			}
		}
	}
shuffle:
	for (i = 0; i < 0x20; i++) {
		order[i] = i;
	}
	i = 0;
	do {
		int r;
		int j;

		r = gm_RandomMod(0x20) & 0xffff;
		j = order[i];
		i++;
		order[i - 1] = order[r];
		order[r] = j;
	} while (i < 0x20);
	for (i = 0; i < *(int *) 0x100b0ac; i++) {
		int off;
		int typ;
		int have;
		int res;

		off = order[i] * 0x58;
		if ((*(unsigned int *) (off + 0x100d114) & 0x400) != 0) {
			continue;
		}
		typ = *(int *) (off + 0x100d0c0);
		if ((*(char *) (typ * 0x41 + *(int *) 0x99ec10) == 0x17 ||
		     *(char *) (typ * 0x41 + *(int *) 0x99ec10) == 0x25) &&
		    *(int *) (off + 0x100d0fc) < 5) {
			continue;
		}
		if ((int) *(unsigned char *) ((int) rec1 + 0x1c) >= *(int *) (off + 0x100d0dc) &&
		    (int) *(unsigned char *) ((int) rec1 + 0x1d) >= *(int *) (off + 0x100d0e0) &&
		    *(int *) (off + 0x100d100) >=
			    (int) *(unsigned short *) (typ * 0x41 + 0x36 + *(int *) 0x99ec10) &&
		    (res = fcn_00503d10(typ)) != 0) {
			have = gm_eval_SlotVoll(res, typ, 1000000);
			if ((int) *(unsigned short *) (typ * 0x41 + 0x36 + *(int *) 0x99ec10) +
				    *(int *) (off + 0x100d0fc) <= have &&
			    fcn_00486640(a0, (void *) (off + 0x100d0c0), 1) != 0) {
				*(unsigned int *) (off + 0x100d114) |= 8;
				fcn_004868d0(a0, (void *) (off + 0x100d0c0));
				*(unsigned short *) (a0 + 0x1bc) = *(unsigned short *) (off + 0x100d0c0);
				fcn_0064d41a(msg, "Produktion von %s starten",
					*(int *) (off + 0x100d0c0) * 0x41 + 1 + *(int *) 0x99ec10);
				goto tail;
			}
		}
	}
	for (i = 0; i < *(int *) 0x100b0ac; i++) {
		int off;
		int typ;
		int have;
		int res;

		off = order[i] * 0x58;
		if ((*(unsigned int *) (off + 0x100d114) & 0x400) != 0) {
			continue;
		}
		typ = *(int *) (off + 0x100d0c0);
		if ((*(char *) (typ * 0x41 + *(int *) 0x99ec10) == 0x17 ||
		     *(char *) (typ * 0x41 + *(int *) 0x99ec10) == 0x25) &&
		    *(int *) (off + 0x100d0fc) < 5) {
			continue;
		}
		if ((int) *(unsigned char *) ((int) rec1 + 0x1c) >= *(int *) (off + 0x100d0dc) &&
		    (int) *(unsigned char *) ((int) rec1 + 0x1d) >= *(int *) (off + 0x100d0e0) &&
		    *(int *) (off + 0x100d100) >=
			    (int) *(unsigned short *) (typ * 0x41 + 0x36 + *(int *) 0x99ec10) &&
		    (res = fcn_00503d10(typ)) != 0) {
			have = gm_eval_SlotVoll(res, typ, 1000000);
			if ((int) *(unsigned short *) (typ * 0x41 + 0x36 + *(int *) 0x99ec10) +
				    *(int *) (off + 0x100d0fc) <= have &&
			    fcn_00486640(a0, (void *) (off + 0x100d0c0), 0) != 0) {
				fcn_004868d0(a0, (void *) (off + 0x100d0c0));
				*(unsigned short *) (a0 + 0x1bc) = *(unsigned short *) (off + 0x100d0c0);
				fcn_0064d41a(msg, "Produktion von %s starten obwohl Rohstoffe fehlen",
					*(int *) (off + 0x100d0c0) * 0x41 + 1 + *(int *) 0x99ec10);
				goto tail;
			}
		}
	}
	*(unsigned short *) (a0 + 0x1bc) = 0;
tail:
	fcn_0047e220((int) rec1);
	fcn_0047e0e0(a0, (int) rec1);
	{
		unsigned int *fl;
		int n;

		fl = (unsigned int *) 0x100d114;
		n = *(int *) 0x100b0ac;
		for (i = n; i > 0; i--) {
			if ((*fl & 8) != 0) {
				int *src;
				unsigned short *pt;
				int k;

				src = (int *) ((char *) fl - 0x50);
				pt = (unsigned short *) (fl[-0x15] * 0x41 + 0x26 + *(int *) 0x99ec10);
				for (k = 0; k < 4; k++) {
					if (*(int *) (*src * 0x40 + 0x100b0e8) < (int) (unsigned int) *pt) {
						*fl &= 0xfffffff7u;
					}
					pt++;
					src++;
				}
			}
			fl += 0x16;
		}
		for (i = 0; i < *(int *) 0x100b0ac; i++) {
			unsigned int *fl2;

			fl2 = (unsigned int *) (i * 0x58 + 0x100d114);
			if ((*fl2 & 0x400) != 0) {
				*fl2 &= 0xfffffff7u;
			}
		}
	}
	{
		int *pp;
		int n;

		pp = (int *) 0x100b0c4;
		for (n = *(int *) 0x100b0a8; n > 0; n--) {
			if ((pp[0xe] & 0x400) != 0 && (pp[0xe] & 0x10) != 0 && *pp >= 0) {
				unsigned int *fl;

				fl = (unsigned int *) (*pp * 0x58 + 0x100d114);
				*fl |= 0x10;
			}
			pp += 0x10;
		}
	}
	if (*(int *) 0x100dc20 == *(int *) (a0 + 0x16c)) {
		int *pp;

		pp = (int *) 0x100d0c4;
		for (i = 0; i < *(int *) 0x100b0ac && *(int *) 0x100dc38 < 4; i++) {
			int dst;
			int *src;
			int j;

			src = pp - 1;
			dst = *(int *) 0x100dc38 * 0x58 + 0x100dc60;
			*(ENTRY *) dst = *(ENTRY *) src;
			for (j = 0; j < 4; j++) {
				int id;

				id = pp[j];
				if (id >= 0) {
					int *s2;
					int *d2;

					s2 = (int *) (id * 0x40 + 0x100b0c0);
					d2 = (int *) ((*(int *) (*(int *) 0x100dc38 * 4 + 0x100dc40) +
						       *(int *) 0x100dc38 * 4) * 0x40 + 0x100df20);
					*(RECORD *) d2 = *(RECORD *) s2;
					*(int *) (*(int *) 0x100dc38 * 4 + 0x100dc40) += 1;
				}
			}
			*(int *) 0x100dc38 += 1;
			pp += 0x16;
		}
	}
	fcn_00487e60(a0, 4);
	arg.cur = 0;
	sp = (void *) 0x7f4ca2;
	while ((int) sp < 0x85a0a2) {
		if (*((char *) sp + 6) != 0 && *(short *) ((char *) sp - 2) != -1 &&
		    *(char *) sp != 0xa) {
			if (*(int *) ((char *) sp + 0x16a) == *(int *) (a0 + 0x16c) &&
			    *((char *) sp + 0x163) != 0 &&
			    *(int *) ((char *) sp + 0x182) != 0 &&
			    *(int *) (*(int *) ((char *) sp + 0x182) + 0x2c) ==
				    *(int *) (*(int *) ((char *) sp + 0x16a) + 1) &&
			    (*(char **) ((char *) sp + 0x17a) == 0 ||
			     **(char **) ((char *) sp + 0x17a) == 4)) {
				fcn_00529160(*(int *) (a0 + 0x16c), 0, *(short *) ((char *) sp - 2), 0);
				arg.cur++;
			}
		}
		sp = (void *) ((char *) sp + 0x21c);
	}
	if (*(int *) 0x100dc20 == *(int *) (a0 + 0x16c)) {
		*(int *) 0x100dc34 = arg.cur;
	}
	fcn_004831f0(a0);
	arg.k = 0;
	{
		unsigned int *fl;
		int n;

		fl = (unsigned int *) 0x100d114;
		n = *(int *) 0x100b0ac;
		for (i = n; i > 0; i--) {
			if ((*fl & 8) != 0) {
				arg.k++;
			}
			if ((*fl & 0x10) != 0) {
				arg.k++;
			}
			fl += 0x16;
		}
	}
	if (arg.cur <= arg.k) {
		arg.k = arg.cur;
	}
	if (arg.cur == 0 || arg.k == 0) {
		ai_MeisterCollectTrans(a0);
		ai_MeisterTrade(a0, (int) rec1);
		return;
	}
	arg.owner = (void *) a0;
	arg.rec = rec1;
	arg.zero = 0;
	arg.z2 = 0;
	arg.z1 = 0;
	for (i = 0; i < *(int *) 0x100b0ac; i++) {
		unsigned int fv;
		unsigned int *fl;

		fl = (unsigned int *) (i * 0x58 + 0x100d114);
		fv = *fl;
		if ((fv & 0x10) == 0) {
			if ((fv & 8) != 0) {
				arg.kind = 4;
				arg.entry = (void *) ((char *) fl - 0x54);
				fcn_00487f90(&arg);
				if (*(int *) 0x100dc20 == *(int *) (a0 + 0x16c) && *(int *) 0x100dc3c < 4) {
					int dst;

					dst = *(int *) 0x100dc3c * 0x58 + 0x100ddc0;
					*(ENTRY *) dst = *(ENTRY *) arg.entry;
					*(int *) 0x100dc3c += 1;
				}
			}
		} else if ((fv & 0x400) != 0) {
			arg.kind = 0x8c;
			arg.entry = (void *) ((char *) fl - 0x54);
			fcn_00487f90(&arg);
			if (*(int *) 0x100dc20 == *(int *) (a0 + 0x16c) && *(int *) 0x100dc3c < 4) {
				int dst;

				dst = *(int *) 0x100dc3c * 0x58 + 0x100ddc0;
				*(ENTRY *) dst = *(ENTRY *) arg.entry;
				*(int *) 0x100dc3c += 1;
			}
		}
	}
	ai_MeisterCollectTrans(a0);
	ai_MeisterTrade(a0, (int) rec1);
}
