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
int __cdecl fcn_005b1e40(int);
int __cdecl fcn_00503d10(int);
int __cdecl gm_eval_SlotVoll(int, int, int);
int __cdecl fcn_0064d3f8(void);
void __cdecl fcn_0064d41a(char *, char *, ...);
void __cdecl fcn_0047e220(int);
void __cdecl fcn_0047e0e0(int, int);
void __cdecl fcn_00487e60(int, int);
void __cdecl fcn_00529160(int, int, int, int);
void __cdecl fcn_004831f0(int);
void __cdecl ai_MeisterCollectTrans(int);
void __cdecl ai_MeisterTrade(int, int);
void __cdecl fcn_00487f90(void *);

/* ADDRESS: GOLDTL 0x00483480 */
void __cdecl fcn_00483480(int a0)
{
	char msg[0x100];
	int order[0x20];
	int rnd[0x20];
	int *slot;
	int *sp;
	unsigned short *pt;
	int i;
	int j;
	int k;
	int n;
	int flags;
	int ok;
	int cur;
	int mode8;
	int cnt;
	int sel;
	void *rec0;
	void *rec1;
	int found;

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
	if (*(short *) 0x7f4c04 == 8 || *(short *) 0x7f4c04 == 0xd) {
		if ((*(unsigned int *) (a0 + 0x1b4) & 0x100) == 0) {
			*(unsigned short *) (a0 + 0x1bc) = 0;
			*(unsigned int *) (a0 + 0x1b4) |= 0x100;
		} else if (*(unsigned short *) (a0 + 0x1bc) != 0 && *(int *) 0x100b0ac > 0) {
			i = 0;
			slot = (int *) 0x100d0c0;
			while (i < *(int *) 0x100b0ac) {
				if (*slot == *(unsigned short *) (a0 + 0x1bc)) {
					sp = (int *) (i * 0x58 + 0x100d0c0);
					if ((int) *(unsigned short *)
						    (*(int *) (i * 0x58 + 0x100d0c0) * 0x41 + 0x36 + *(int *) 0x99ec10) <=
					    *(int *) (i * 0x58 + 0x100d100) &&
					    fcn_00486640(a0, sp, 1) != 0) {
						*(unsigned int *) (i * 0x58 + 0x100d114) |= 8;
						fcn_004868d0(a0, sp);
						*(unsigned short *) (a0 + 0x1bc) = *(unsigned short *) sp;
						found = 1;
					}
					break;
				}
				i++;
				slot += 0x16;
			}
		}
	} else {
		i = 0;
		slot = (int *) 0x100d0c0;
		while (i < *(int *) 0x100b0ac) {
			if (*slot == *(unsigned short *) (a0 + 0x1bc)) {
				sp = (int *) (i * 0x58 + 0x100d0c0);
				if ((int) *(unsigned short *)
					    (*(int *) (i * 0x58 + 0x100d0c0) * 0x41 + 0x36 + *(int *) 0x99ec10) <=
				    *(int *) (i * 0x58 + 0x100d100) &&
				    fcn_00486640(a0, sp, 1) != 0) {
					*(unsigned int *) (i * 0x58 + 0x100d114) |= 8;
					fcn_004868d0(a0, sp);
					*(unsigned short *) (a0 + 0x1bc) = *(unsigned short *) sp;
					found = 2;
				}
				break;
			}
			i++;
			slot += 0x16;
		}
		*(unsigned int *) (a0 + 0x1b4) &= 0xfffffeffu;
	}
	if (*(char *) ((int) *(unsigned short *) (*(int *) (a0 + 0x16c) + 0x27) * 0x21c + 0x7f4ca2) == 6) {
		int gate;

		gate = fcn_005b1e40(*(int *) (a0 + 0x16c));
		if (gate != 0) {
			slot = (int *) 0x100d0c0;
			while ((int) slot < 0x100dbc0) {
				if (*slot == gate) {
					sp = slot;
					if (*(int *) ((int) slot - (int) 0x100d0c0 + 0x100d0dc) <=
						    (int) (unsigned int) *(unsigned char *) ((int) rec1 + 0x1c) &&
					    *(int *) ((int) slot - (int) 0x100d0c0 + 0x100d0e0) <=
						    (int) (unsigned int) *(unsigned char *) ((int) rec1 + 0x1d)) {
						pt = (unsigned short *) (*sp * 0x41 + 0x36 + *(int *) 0x99ec10);
						if ((int) *pt <= *(int *) ((int) sp - (int) 0x100d0c0 + 0x100d100) &&
						    fcn_00503d10(*sp) != 0) {
							int have;

							have = gm_eval_SlotVoll(fcn_00503d10(*sp), *sp, 1000000);
							if ((int) *(unsigned short *) (*sp * 0x41 + 0x36 + *(int *) 0x99ec10) +
								    *(int *) ((int) sp - (int) 0x100d0c0 + 0x100d0fc) <= have) {
								if (fcn_00486640(a0, sp, 1) != 0) {
									*(unsigned int *) ((int) sp - (int) 0x100d0c0 + 0x100d114) |= 8;
									fcn_004868d0(a0, sp);
									*(unsigned short *) (a0 + 0x1bc) = *(unsigned short *) sp;
									fcn_0064d41a(msg,
										"Produktion von %s starten, da Humanplayer es so will.",
										*sp * 0x41 + 1 + *(int *) 0x99ec10);
									found = 3;
								} else if (fcn_00486640(a0, sp, 0) != 0) {
									fcn_004868d0(a0, sp);
									*(unsigned short *) (a0 + 0x1bc) = *(unsigned short *) sp;
									fcn_0064d41a(msg,
										"Produktion von %s starten obwohl Rohstoffe fehlen, da der spieler es so will",
										*sp * 0x41 + 1 + *(int *) 0x99ec10);
									found = 3;
								}
							}
						}
					}
					break;
				}
				slot += 0x16;
			}
		}
	}
	for (i = 0; i < 0x20; i++) {
		order[i] = i;
	}
	i = 0;
	do {
		unsigned int uv;

		uv = (unsigned int) fcn_0064d3f8() & 0xffff;
		j = order[i];
		i++;
		rnd[i] = order[uv];
		order[uv] = j;
	} while (i < 0x20);
	if (found == 0) {
		int pass;

		for (pass = 0; pass < 2; pass++) {
			for (n = 0; n < *(int *) 0x100b0ac; n++) {
				int off;

				off = order[n] * 0x58;
				sp = (int *) (off + 0x100d0c0);
				if ((*(unsigned int *) (off + 0x100d114) & 0x400) == 0) {
					int typ;

					typ = *sp;
					pt = (unsigned short *) (typ * 0x41 + 0x36 + *(int *) 0x99ec10);
					if (!((*(char *) (typ * 0x41 + *(int *) 0x99ec10) == 0x17 ||
					       *(char *) (typ * 0x41 + *(int *) 0x99ec10) == 0x25) &&
					      *(int *) (off + 0x100d0fc) < 5)) {
						if (*(int *) (off + 0x100d0dc) <=
							    (int) (unsigned int) *(unsigned char *) ((int) rec1 + 0x1c) &&
						    *(int *) (off + 0x100d0e0) <=
							    (int) (unsigned int) *(unsigned char *) ((int) rec1 + 0x1d) &&
						    (int) *pt <= *(int *) (off + 0x100d100) &&
						    fcn_00503d10(typ) != 0) {
							int have;

							have = gm_eval_SlotVoll(fcn_00503d10(typ), *sp, 1000000);
							if ((int) *(unsigned short *)
								    (*sp * 0x41 + 0x36 + *(int *) 0x99ec10) +
								    *(int *) (off + 0x100d0fc) <= have &&
							    fcn_00486640(a0, sp, pass == 0 ? 1 : 0) != 0) {
								*(unsigned int *) (off + 0x100d114) |= 8;
								fcn_004868d0(a0, sp);
								*(unsigned short *) (a0 + 0x1bc) = *(unsigned short *) sp;
								if (pass == 0) {
									fcn_0064d41a(msg, "Produktion von %s starten",
										*sp * 0x41 + 1 + *(int *) 0x99ec10);
								} else {
									fcn_0064d41a(msg,
										"Produktion von %s starten obwohl Rohstoffe fehlen",
										*sp * 0x41 + 1 + *(int *) 0x99ec10);
								}
								found = 4;
							}
						}
					}
				}
				if (found != 0) {
					break;
				}
			}
			if (found != 0) {
				break;
			}
		}
	}
	if (found == 0) {
		*(unsigned short *) (a0 + 0x1bc) = 0;
	}
	fcn_0047e220((int) rec1);
	fcn_0047e0e0(a0, (int) rec1);
	cnt = *(int *) 0x100b0ac;
	if (cnt > 0) {
		int *fp;

		fp = (int *) 0x100d114;
		for (i = cnt; i > 0; i--) {
			if ((*(unsigned char *) fp & 8) != 0) {
				int *src;

				src = fp - 0x14;
				pt = (unsigned short *) (fp[-0x15] * 0x41 + 0x26 + *(int *) 0x99ec10);
				for (k = 0; k < 4; k++) {
					if (*(int *) (*src * 0x40 + 0x100b0e8) < (int) (unsigned int) *pt) {
						*fp &= 0xfffffff7u;
					}
					pt++;
					src++;
				}
			}
			fp += 0x16;
		}
		for (i = 0; i < cnt; i++) {
			int *fp2;

			fp2 = (int *) (i * 0x58 + 0x100d114);
			if ((*fp2 & 0x400) != 0) {
				*fp2 &= 0xfffffff7u;
			}
		}
	}
	if (*(int *) 0x100b0a8 > 0) {
		int *pp;

		pp = (int *) 0x100b0c4;
		for (i = *(int *) 0x100b0a8; i > 0; i--) {
			if ((pp[0xe] & 0x400) != 0 && (pp[0xe] & 0x10) != 0 && *pp >= 0) {
				unsigned int *fl;

				fl = (unsigned int *) (*pp * 0x58 + 0x100d114);
				*fl |= 0x10;
			}
			pp += 0x10;
		}
	}
	if (*(int *) 0x100dc20 == *(int *) (a0 + 0x16c) && *(int *) 0x100dc38 < 4) {
		int *pp;

		pp = (int *) 0x100d0c4;
		for (i = 0; i < cnt; i++) {
			int dst;
			int *src;

			if (*(int *) 0x100dc38 >= 4) {
				break;
			}
			src = pp - 1;
			dst = *(int *) 0x100dc38 * 0x58 + 0x100dc60;
			for (k = 0; k < 0x16; k++) {
				*(int *) (dst + k * 4) = src[k];
			}
			for (j = 0; j < 4; j++) {
				int id;

				id = pp[j];
				if (id >= 0) {
					int *s2;
					int *d2;

					s2 = (int *) (id * 0x40 + 0x100b0c0);
					d2 = (int *) ((*(int *) (*(int *) 0x100dc38 * 4 + 0x100dc40) +
						       *(int *) 0x100dc38 * 4) * 0x40 + 0x100df20);
					for (k = 0; k < 0x10; k++) {
						d2[k] = s2[k];
					}
					*(int *) (*(int *) 0x100dc38 * 4 + 0x100dc40) += 1;
				}
			}
			*(int *) 0x100dc38 += 1;
			pp += 0x16;
		}
	}
	fcn_00487e60(a0, 4);
	cur = 0;
	sp = (int *) 0x7f4ca2;
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
				cur++;
			}
		}
		sp = (int *) ((char *) sp + 0x21c);
	}
	if (*(int *) 0x100dc20 == *(int *) (a0 + 0x16c)) {
		*(int *) 0x100dc34 = cur;
	}
	fcn_004831f0(a0);
	k = 0;
	if (*(int *) 0x100b0ac > 0) {
		unsigned int *fl;

		fl = (unsigned int *) 0x100d114;
		for (i = *(int *) 0x100b0ac; i > 0; i--) {
			if ((*fl & 8) != 0) {
				k++;
			}
			if ((*fl & 0x10) != 0) {
				k++;
			}
			fl += 0x16;
		}
	}
	if (cur <= k) {
		k = cur;
	}
	if (cur == 0 || k == 0) {
		ai_MeisterCollectTrans(a0);
		ai_MeisterTrade(a0, (int) rec1);
		return;
	}
	n = 0;
	for (i = 0; i < *(int *) 0x100b0ac; i++) {
		unsigned int fv;
		unsigned int *fl;

		fl = (unsigned int *) (i * 0x58 + 0x100d114);
		fv = *fl;
		if ((fv & 0x10) == 0) {
			if ((fv & 8) != 0) {
				int arg[2];

				arg[0] = (int) (fl - 0x15);
				arg[1] = 4;
				fcn_00487f90(arg);
			}
		} else if ((fv & 0x400) != 0) {
			int arg[2];

			arg[0] = (int) (fl - 0x15);
			arg[1] = 0x8c;
			fcn_00487f90(arg);
		}
		if (*(int *) 0x100dc20 == *(int *) (a0 + 0x16c) && *(int *) 0x100dc3c < 4) {
			int *src;
			int dst;

			src = (int *) (i * 0x58 + 0x100d0c0);
			dst = *(int *) 0x100dc3c * 0x58 + 0x100ddc0;
			for (k = 0; k < 0x16; k++) {
				*(int *) (dst + k * 4) = src[k];
			}
			*(int *) 0x100dc3c += 1;
		}
	}
	ai_MeisterCollectTrans(a0);
	ai_MeisterTrade(a0, (int) rec1);
}
