extern void __cdecl fcn_00473fe0(void);
extern void __cdecl fcn_0046b2b0(int a);
extern int __cdecl fcn_004737e0(void);
extern void __cdecl fcn_00469c40(int a, int b, int c);
extern int __cdecl fcn_00469c30(short a, short b, int c);
extern void __cdecl fcn_00474300(void);
extern int __cdecl fcn_00474780(void);
extern void __cdecl fcn_00466fe0(int a, int b);
extern void __cdecl fcn_00474040(void);
extern void __cdecl fcn_00475220(void *p);
extern int __cdecl fcn_004722c0(void *p);
extern void __cdecl fcn_00412830(int a);
extern int __cdecl fcn_0046b520(void *p, int a);

/* ADDRESS: GOLDTL 0x004748b0 */
int __cdecl fcn_004748b0(void)
{
	unsigned int *p;
	unsigned int *v1;
	int v7;
	int v8;
	int i;

	if (*(int *) 0x7725e8 && !*(int *) 0x14ce8dc) {
		p = *(unsigned int **) 0x7725d0;
		if (!*(int *) 0x14ce8d0 || p == 0
		    || !(*(unsigned char *) ((char *) p + 0x28) & 2)) {
			*(int *) 0x7725e8 = 0;
			*(int *) 0x6772c0 = *(int *) 0x100f1d8;
			*(int *) 0x6b5c84 = *(int *) 0x100f1e0;
			fcn_00473fe0();
		}
	}
	p = *(unsigned int **) 0x7725d0;
	v7 = (short) *(short *) 0x14ce8c2;
	if (!*(int *) 0x14ce8d0) {
		*(int *) 0x7725e4 = 0;
	}
	if (p == 0 && *(int *) 0x67d8ec != -1) {
		fcn_0046b2b0(*(int *) 0x67d8ec);
		*(int *) 0x67d8ec = -1;
		p = *(unsigned int **) 0x7725d0;
	}
	if (*(int *) 0x67d370 != -1) {
		v8 = *(int *) 0x1015ea0 + *(int *) 0x67d370 * 0x2f4;
		if (*(int *) (v8 + 0x20) == 0x41) {
			v1 = *(unsigned int **) (v8 + 0xc);
			if (*(int *) 0x67d370 == (int) v1[0x4d]) {
				if (!*(int *) 0x14ce8d0) {
					goto label_474b14;
				}
				if (p == v1 || *(int *) 0x7725e4) {
					goto label_474afe;
				}
				if (p != 0) {
					*(int *) (*(int *) 0x1015ea0 + 0x3c + p[0x4d] * 0x2f4) = 0;
				}
				*(int *) (*(int *) 0x1015ea0 + 0x3c + v1[0x4d] * 0x2f4) = 1;
				*(int *) 0x100f1d4 = *(int *) 0x6772c0 - v7;
				*(int *) 0x100f940 = v1[0x4b];
				*(int *) 0x100f950 = 0;
				v8 = *(int *) (*(int *) 0x1015ea0 + 0x40 + v1[0x4d] * 0x2f4);
				i = 0;
				if (v8 != 0) {
					while (i < *(int *) (v8 + 0x2c)) {
						if (*(int *) (*(int *) (v8 + 0x28) + i * 4) == (int) v1[0x4d]) {
							*(int *) 0x100f1cc = i;
						}
						i++;
					}
				}
				p = v1;
				*(unsigned int **) 0x7725d0 = v1;
				if ((*(unsigned char *) ((char *) v1 + 0x28) & 0x40) && !v1[6]
				    && !v1[7] && !fcn_004737e0() && !v1[0x4b]) {
					v1[0x4b] = 0xffffffff;
					p = *(unsigned int **) 0x7725d0;
				}
				if (*(unsigned char *) ((char *) p + 0x28) & 1) {
					*(int *) 0x100f898 = fcn_0046b520((char *) p + 0x2c, p[0x4e]);
					*(int *) 0x100f898 += p[1];
					*(int *) 0x100f89c = p[2];
					if (*(int *) 0x67d8ec != -1) {
						fcn_00469c40(*(int *) 0x100f898, *(int *) 0x100f89c - 7,
						    *(int *) 0x67d8ec);
					} else {
						*(int *) 0x67d8ec = fcn_00469c30(
						    (short) *(int *) 0x100f898,
						    (short) (*(int *) 0x100f89c - 7),
						    *(int *) 0x67d3b0 + 8);
					}
				} else if (*(int *) 0x67d8ec != -1) {
					fcn_0046b2b0(*(int *) 0x67d8ec);
					*(int *) 0x67d8ec = -1;
				}
				p = *(unsigned int **) 0x7725d0;
			}
		}
	}
label_474afe:
	if (*(int *) 0x14ce8d0) {
		if (p == 0) {
			goto label_474b96;
		}
		*(int *) 0x7725e4 = 1;
	}
label_474b14:
	if (p != 0 && *(int *) 0x67d370 == (int) p[0x4d]
	    && (*(unsigned char *) ((char *) p + 0x28) & 2)
	    && *(int *) 0x14ce8d8) {
		if ((int) p[0x4b] < (int) p[6] && p[0x4b] != 0xffffffff
		    && p[0x4f] != 0xffffffff) {
			v7 = fcn_004722c0(p);
			p[0x4b] += v7;
			p = *(unsigned int **) 0x7725d0;
		}
		if (!p[6] && !p[7] && !fcn_004737e0() && !p[0x4b]
		    && (*(unsigned char *) ((char *) p + 0x28) & 0x40)) {
			p[0x4b] = 0xffffffff;
			p = *(unsigned int **) 0x7725d0;
		}
	}
label_474b96:
	if (*(int *) 0x14ce8e0) {
		if (p == 0) {
			goto label_474ca4;
		}
		if (*(unsigned char *) ((char *) p + 0x28) & 1) {
			fcn_00412830(0x10);
			p = *(unsigned int **) 0x7725d0;
		}
		*(int *) (*(int *) 0x1015ea0 + 0x3c + p[0x4d] * 0x2f4) = 0;
		*(unsigned int **) 0x7725d0 = 0;
		*(int *) 0x7725e4 = 0;
		if (*(int *) 0x67d8ec == -1) {
			goto label_474ca4;
		}
		fcn_0046b2b0(*(int *) 0x67d8ec);
		*(int *) 0x67d8ec = -1;
		p = *(unsigned int **) 0x7725d0;
	}
	if (p != 0) {
		if (!*(int *) 0x14ce8d0) {
			*(int *) 0x100f950 = 1;
			*(int *) 0x14ce8d8 = 0;
		}
		fcn_00474300();
		if (fcn_00474780()) {
			return 1;
		}
		if (*(unsigned int **) 0x7725d0 != 0
		    && (*(unsigned char *) (*(int *) 0x7725d0 + 0x28) & 0x10)
		    && *(int *) 0x67d370 == (int) (*(unsigned int **) 0x7725d0)[0x4d]
		    && *(int *) 0x14ce8d8) {
			v1 = *(unsigned int **) 0x7725d0;
			v1[0x53] = v1[0x53] + 1;
			if ((int) (v1[0x54] + 0xffffffff + v1[0x52]) < (int) v1[0x53]) {
				v1[0x53] = v1[0x52];
			}
			fcn_00466fe0(v1[0], v1[0x53]);
		}
	}
label_474ca4:
	fcn_00474040();
	if (*(int *) 0x67d370 != -1) {
		v7 = *(int *) 0x1015ea0 + *(int *) 0x67d370 * 0x2f4;
		if (*(unsigned char *) (v7 + 0x1d0) & 0x40) {
			fcn_00475220((void *) (v7 + 0xcc));
		}
	}
	return 0;
}
