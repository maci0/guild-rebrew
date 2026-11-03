unsigned short __cdecl gm_RandomMod(unsigned short n);
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_00508d80(unsigned int n, int *arr);
int __cdecl fcn_0047dd60(void *p);
void __cdecl fcn_00511b70(int n, int *out, unsigned char *src);
void __cdecl fcn_004c44a0(void);
void __cdecl fcn_004c44b0(void);
int __cdecl fcn_004c44c0(void);
void __cdecl fcn_004c3ff0(void);
void __cdecl fcn_004c4940(void);
void __cdecl fcn_004c4b00(void);
char *__cdecl fcn_004c4480(int h);
int __cdecl fcn_004c4fc0(int, int, int, int, int, int, int, int);
void __cdecl fcn_004c5150(int, int, int, int);
void __cdecl fcn_004c4510(char *p, int h);
void __cdecl fcn_004c4570(int, int, int, void *p);
int __cdecl fcn_004c5420(int, int, int, int, int);
int __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_00535960(void);
int __cdecl fcn_004c4450(int h);
int __cdecl fcn_004e8af0(int c, void *out);
int __cdecl fcn_004e8b40(int i, void *out);
int __cdecl fcn_004e8a80(int i, void *out);
int __cdecl fcn_004e8210(int a, void *p, int b);
void __cdecl fcn_004fee50(void *p, int h);
int __cdecl gm_MapEntityStatRange(int);
int __cdecl fcn_00507400(int, int);
int __cdecl fcn_0050b750(int, int);
void __cdecl fcn_004ad1c0(void);

/* ADDRESS: GOLDTL 0x00511c60 */
int __cdecl fcn_00511c60(void)
{
	int v36;
	int v42;
	char v37;
	int v38;
	int v49;
	float v50;
	int v25[50];
	int v35[6];
	int v39[6];
	int v41[6];
	int v27[30];
	int v40[6];
	int v34[6];
	int v26[30];
	int v33[30];
	int i;
	int n;
	int m;
	int k;
	char *p;

	v25[1] = 0x12;
	v25[5] = 0x12;
	v25[9] = 0x12;
	v25[16] = 0x1d;
	v25[17] = 0x1d;
	v25[22] = 0x1d;
	v25[23] = 0x1d;
	v25[26] = 0x1d;
	v25[2] = 0x14;
	v25[6] = 0x14;
	v25[10] = 0x14;
	m = 0;
	v25[0] = 0x10;
	v25[3] = 0x18;
	v25[4] = 0x10;
	v25[7] = 0x18;
	v25[8] = 0x10;
	v25[11] = 0x18;
	v25[12] = 0x16;
	v25[13] = 0x18;
	v25[14] = 0x19;
	v25[15] = 0x1b;
	v25[18] = 0x16;
	v25[19] = 0x18;
	v25[20] = 0x19;
	v25[21] = 0x1b;
	v25[24] = 0x19;
	v25[25] = 0x1b;
	v25[27] = 0x20;
	v25[28] = 0x22;
	v25[29] = 0x25;
	fcn_00508d80(4, &v25[0]);
	fcn_00508d80(4, &v25[4]);
	fcn_00508d80(4, &v25[8]);
	fcn_00508d80(6, &v25[12]);
	fcn_00508d80(6, &v25[18]);
	fcn_00508d80(6, &v25[24]);
	for (i = 0; i < 0x1e; i++) {
		v26[i] = 0;
	}
	for (i = 0; i < 0x1e; i++) {
		v25[i] = v25[i + 1] + gm_RandomMod(3);
	}
	n = 0;
	p = (char *) 0x7f4ca0;
	while ((int) p < 0x85a0a0) {
		if (n >= 0x1e) {
			break;
		}
		if (n >= 0xc) {
			break;
		}
		if (fcn_0047dd60(p) != 0) {
			if (*(unsigned char *) (p + 2) != 5) {
				v26[n] = (int) p;
				n++;
			}
		}
		p += 0x21c;
	}
	for (i = 0; i < 0x1e; i++) {
		v27[i] = i;
	}
	fcn_00508d80(4, &v27[0]);
	fcn_00508d80(4, &v27[4]);
	fcn_00508d80(4, &v27[8]);
	fcn_00508d80(6, &v27[12]);
	fcn_00508d80(6, &v27[18]);
	fcn_00508d80(6, &v27[24]);
	fcn_00511b70(0x1e - n, &v33[n], (unsigned char *) &v27[n]);
	i = n;
	while (i < 0x1e) {
		fcn_004c44a0();
		if (m < 3 && i > 0xc) {
			if ((gm_RandomMod(4) & 0xffff) == 0) {
				k = fcn_004c4fc0(0x10, -1, -1, 0x10, -1, 0, 0, 0);
				m++;
			} else {
				k = fcn_004c4fc0(3, -1, -1, 0x10, -1,
						 (unsigned char) v33[i], 0, 2);
			}
		} else {
			k = fcn_004c4fc0(3, -1, -1, 0x10, -1,
					 (unsigned char) v33[i], 0, 2);
		}
		fcn_004c44b0();
		while (fcn_004c44c0() == 0) {
			fcn_004c3ff0();
			fcn_004c4940();
			fcn_004c4b00();
		}
		v26[i] = (int) fcn_004c4480(k);
		i++;
	}
	v25[30] = 1;
	v25[31] = 3;
	v25[32] = 3;
	v25[35] = 5;
	v25[33] = 4;
	v25[34] = 4;
	v25[36] = 6;
	v25[37] = 7;
	v25[38] = 7;
	v25[39] = 7;
	v25[41] = 10000;
	v25[42] = 10000;
	v25[40] = 1000;
	v25[43] = 20000;
	v25[44] = 20000;
	v25[45] = 40000;
	v25[46] = 50000;
	v25[47] = 60000;
	v25[48] = 80000;
	v25[49] = 100000;
	for (i = 0; i < 0x1e; i++) {
		v36 = 2;
		fcn_004e8af0(v27[i], v34);
		fcn_004e8b40(v34[2] & 0xff, v35);
		v37 = (char) (int) ((float) gm_RandomMod(0x2a) +
				    (float) ((v35[2] & 0xff) / 3 + 1) *
				    *(float *) 0x66536c);
		v42 = (gm_RandomMod(2) & 0xffff) + v25[(v35[2] & 0xff) + 30];
		v38 = v25[(v35[2] & 0xff) + 40];
		v42 = v38;
		v49 = fcn_0050b750(v38 - (int) ((float) v38 *
						 gm_RandomFloat01() *
						 *(float *) 0x664158),
				   *(unsigned char *) 0x773d75);
		p = (char *) v26[i];
		fcn_004c5150(*(int *) (p + 4), -1, *(unsigned char *) 0x773d75,
			     v49);
		fcn_004c4510(p, *(int *) (p + 4));
		fcn_004c4570(1, 1, 0xd, &v36);
		if (*(unsigned char *) (p + 2) == 3) {
			fcn_004c4570(1, 1, 0x84, &v37);
			if ((gm_RandomMod(2) & 0xffff) != 0) {
				v50 = gm_RandomFloat01() + *(float *) 0x6628a0;
				v42 = (gm_RandomMod(8) & 0xffff) + 1;
				v38 = (int) ((float) v42 * v50 *
					     (float) v49 *
					     *(float *) 0x662910);
				fcn_004c4570(4, 1, 0x1ac, &v38);
			}
		}
		fcn_004c5360();
		fcn_004fee50(p, v25[i] & 0xffff);
		k = fcn_004e8210((unsigned char) v33[i], p, 0xff);
		if (k != -1) {
			while (fcn_004c4450(k) == 0) {
				fcn_00535960();
			}
		}
		if (*(unsigned char *) (p + 0x166) == 0x18 ||
		    *(unsigned char *) (p + 0x166) == 0x1a ||
		    *(unsigned char *) (p + 0x166) == 0x1b) {
			k = fcn_004c5420(*(int *) (p + 4), 0x1cc, 4, 0x80, 0);
		} else if (*(unsigned char *) (p + 0x166) == 0x16 ||
			   *(unsigned char *) (p + 0x166) == 0x17 ||
			   *(unsigned char *) (p + 0x166) == 0x19) {
			k = fcn_004c5420(*(int *) (p + 4), 0x1cc, 4, 0x40, 0);
		} else {
			k = -1;
		}
		if (k != -1) {
			while (fcn_004c4450(k) == 0) {
				fcn_00535960();
			}
		}
		if (*(unsigned char *) (p + 0x166) == 0x1b) {
			fcn_004e8a80(0x25, v39);
			fcn_004e8210(v39[0], p, 0xff);
		} else if (*(unsigned char *) (p + 0x166) == 0x1a) {
			fcn_004e8a80(0x24, v40);
			fcn_004e8210(v40[0], p, 0xff);
		} else if (*(unsigned char *) (p + 0x166) == 0x19) {
			fcn_004e8a80(0x23, v41);
			fcn_004e8210(v41[0], p, 0xff);
		}
	}
	do {
		m = 0;
		i = 0;
		n = 0;
		do {
			if (n != 0 && m != 0) {
				break;
			}
			p = (char *) v26[i];
			if (*(unsigned short *) (p + 0xa) >= 0x17) {
				if (m == 0 &&
				    *(unsigned char *) (p + 9) == 0 &&
				    *(int *) (p + 0x5c) == -1) {
					m = (int) p;
				} else if (n == 0 &&
					   *(unsigned char *) (p + 9) == 1 &&
					   *(int *) (p + 0x5c) == -1) {
					n = (int) p;
				}
			}
			i++;
		} while (i < 0x1e);
		if (m == 0 || n == 0) {
			break;
		}
		v42 = *(unsigned short *) (n + 0xa) - 0x12;
		v36 = n;
		fcn_004c4510((char *) m, *(int *) (m + 4));
		fcn_004c4570(4, 1, 0x5c, (char *) (n + 4));
		fcn_004c5360();
		fcn_004c4510((char *) n, *(int *) (n + 4));
		fcn_004c4570(4, 1, 0x5c, (char *) (m + 4));
		fcn_004c5360();
		if (v42 > 5) {
			if ((gm_RandomMod(2) & 0xffff) != 0) {
				k = *(unsigned char *) (m + 0x164);
			} else {
				k = *(unsigned char *) (n + 0x164);
			}
			k = fcn_00507400(gm_MapEntityStatRange(k), 1);
			v38 = 2;
			k = fcn_004c4fc0(8, *(int *) (m + 4), *(int *) (n + 4),
					 v42, -1, k, 0, 2);
			if (k != -1) {
				while (fcn_004c4450(k) == 0) {
					fcn_00535960();
				}
			}
			p = fcn_004c4480(k);
			k = gm_RandomMod(0x400);
			fcn_004c5150(*(int *) (p + 4), -1,
				     *(unsigned char *) 0x773d75,
				     ((k & 0xffff) + 0x200) << 5);
			fcn_004c4510(p, *(int *) (p + 4));
			fcn_004c4570(1, 1, 0xd, &v38);
			fcn_004c5360();
		}
		k = gm_RandomMod(0x20);
		fcn_004c54c0(*(int *) (m + 4), *(int *) (n + 4),
			     (k & 0xffff) + 0x60, 0);
		k = gm_RandomMod(0x20);
		k = fcn_004c54c0(*(int *) (n + 4), *(int *) (m + 4),
				 (k & 0xffff) + 0x60, 0);
		if (k != -1) {
			while (fcn_004c4450(k) == 0) {
				fcn_00535960();
			}
		}
	} while (v36 != 0);
	i = 8;
	do {
		v36 = 2;
		v42 = (gm_RandomMod(9) & 0xffff) + 1;
		k = fcn_00507400((gm_RandomMod(2) & 0xffff) + 1,
				 (gm_RandomMod(0xc) & 0xffff) + 1);
		k = fcn_004c4fc0(3, -1, -1, gm_RandomMod(4) + 0xf, -1, k, 0, 0);
		if (k != -1) {
			while (fcn_004c4450(k) == 0) {
				fcn_00535960();
			}
		}
		p = fcn_004c4480(k);
		k = gm_RandomMod(0x400);
		fcn_004c5150(*(int *) (p + 4), -1, *(unsigned char *) 0x773d75,
			     ((k & 0xffff) + 0x200) << 5);
		fcn_004c4510(p, *(int *) (p + 4));
		fcn_004c4570(1, 1, 0xd, &v36);
		fcn_004c4570(1, 1, 0x167, &v42);
		fcn_004c5360();
		k = fcn_00507400((gm_RandomMod(2) & 0xffff) + 1,
				 (gm_RandomMod(0xc) & 0xffff) + 1);
		k = fcn_004c4fc0(3, -1, -1, gm_RandomMod(4) + 0xe, -1, k, 0, 0);
		if (k != -1) {
			while (fcn_004c4450(k) == 0) {
				fcn_00535960();
			}
		}
		p = fcn_004c4480(k);
		k = gm_RandomMod(0x400);
		fcn_004c5150(*(int *) (p + 4), -1, *(unsigned char *) 0x773d75,
			     ((k & 0xffff) + 0x200) << 5);
		fcn_004c4510(p, *(int *) (p + 4));
		fcn_004c4570(1, 1, 0xd, &v36);
		fcn_004c4570(1, 1, 0x167, &v42);
		fcn_004c5360();
		i--;
	} while (i != 0);
	fcn_004ad1c0();
	return 1;
}
