char __cdecl fcn_00413680(int, int, void*, void*);
int __cdecl fcn_00415300(int);
int __cdecl fcn_004234e0(int, int, int, int, int, int, int);
int __cdecl fcn_00426cc0(int);
int __cdecl fcn_00426fd0(char*);
void __cdecl fcn_00428340(int, int, ...);
int __cdecl fcn_00428720(int);
void __cdecl fcn_00429670(int);
void __cdecl fcn_004379a0(int, int, int, int, void*);
void __cdecl fcn_00442be0(int);
void __cdecl fcn_00442d50(int, int);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_004550b0(int, int);
void __cdecl fcn_004550e0(int, int);
void __cdecl fcn_00455350(char*, char*, float*);
void __cdecl fcn_004bd4e0(int, int);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_004c4480(int);
void __cdecl fcn_004c4510(void*, int);
void __cdecl fcn_004c4570(int, int, int, void*);
int __cdecl fcn_004c4f30(unsigned char, int, int, int);
int __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_004c5360();
void __cdecl fcn_004c5420(int, int, int, int, int);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_004c5790(int, void*);
void __cdecl fcn_004c5fd0(int);
void __cdecl fcn_005001e0(void*, int);
void __cdecl fcn_00500bb0(void*, int, int, int);
int __cdecl fcn_00500cb0(int*, int*);
int __cdecl fcn_00500e20(int);
void __cdecl fcn_005015e0(void*, int, int, int);
int __cdecl fcn_00509570(int);
int __cdecl fcn_0050cad0(int*, int*);
int __cdecl fcn_0050f910(int);
int __cdecl fcn_00510820(int, void*, int);
void __cdecl fcn_005165b0(int);
void __cdecl fcn_0052d9d0(void*);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_00546190(int);
void __cdecl fcn_00573e10(int);
int __cdecl fcn_00574150();
int __cdecl fcn_005742e0(void*, void*, void*, void*, void*);
void __cdecl fcn_00598510();
int __cdecl fcn_005985f0(void*, int);
int __cdecl fcn_00508e40(int);
int __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_0064d228();
int __cdecl fcn_0064d41a(char*, char*, ...);

double __cdecl sqrt();

/* ADDRESS: GOLDTL 0x005744c0 */
void __cdecl fcn_005744c0(int a0)
{
	int v5;
	int v8;
	unsigned char v9;
	int v11;
	int v13;
	int v24;
	int v31;
	int v27;
	unsigned char* v14;
	int v30;
	float v29;
	float v21;
	unsigned char* v15;
	float v17[4];
	char v20[14];
	int v36;
	char v16[0x54];
	int v18[33];
	char v19[128];
	char v22[0x200];

	v5 = a0;
	v30 = *(int*) 0x6b8010;
	v15 = 0;
	if (*(int*) (v5 + 0x84) != -1 && !fcn_004c4450(*(int*) (v5 + 0x84))) {
		return;
	}
	*(int*) (v5 + 0x84) = -1;
	v8 = *(int*) (v5 + 0x70) + 2;
	switch (v8) {
	case 2:
		if (fcn_00500cb0((void*) (v5 + 0x52), (void*) 0x7f4c00) > 0
			|| !(*(unsigned char*) (v5 + 0x78) & 2)) {
			break;
		}
		if (*(int*) (v5 + 0xac) != *(int*) (*(int*) 0x773da8 + 4)) {
			v8 = fcn_00508e40(*(int*) (v5 + 0xac));
			if (v8) {
				*(int*) (v5 + 0xcc) = fcn_004c5150(-1, *(int*) (v5 + 0xac),
					(v8 & 0xffffff00) | *(unsigned char*) 0x773d75, *(int*) (v5 + 0xb4));
				v8 = fcn_00509570(v8);
				if (v8) {
					*(int*) (v8 + 0x54) = *(int*) (v8 + 0x54) + *(int*) (v5 + 0xb4);
				}
			}
			else {
LfailB:
				*(int*) (v5 + 0x84) = fcn_004c5620(-1, (void*) v5);
				return;
			}
		}
		else {
			*(int*) (v5 + 0xcc) = fcn_0050f910(*(int*) (v5 + 0xb4));
		}
		*(int*) (v5 + 0x84) = fcn_004c5620(*(int*) (v5 + 0x70) + 1, (void*) v5);
		return;

	case 3:
		*(int*) (v5 + 0x84) = -1;
		if (*(unsigned char*) (v5 + 0x78) & 4) {
			break;
		}
		if (!fcn_004c4450(*(int*) (v5 + 0xcc))) {
			break;
		}
		if (fcn_004c4450(*(int*) (v5 + 0xcc)) == 2) {
			*(int*) (v5 + 0x84) = fcn_004c5620(-1, (void*) v5);
			return;
		}
		*(int*) (v5 + 0x84) = fcn_004c5620(*(int*) (v5 + 0x70) + 1, (void*) v5);
		return;

	case 4:
		if (!(*(unsigned char*) (v5 + 0x78) & 2)) {
			break;
		}
		v13 = fcn_004c4f30((v8 & 0xffffff00) | *(unsigned char*) (v5 + 0xb0),
			*(int*) (v5 + 0xac), 0, 1);
		*(int*) (v5 + 0xcc) = v13;
		*(int*) (v5 + 0x84) = fcn_004c5620(*(int*) (v5 + 0x70) + 1, (void*) v5);
		return;

	case 5:
		*(int*) (v5 + 0x84) = -1;
		if (*(unsigned char*) (v5 + 0x78) & 4) {
			break;
		}
		if (!fcn_004c4450(*(int*) (v5 + 0xcc))) {
			break;
		}
		if (fcn_004c4450(*(int*) (v5 + 0xcc)) == 2) {
			goto LfailB;
		}
		v15 = (unsigned char*) fcn_004c4480(*(int*) (v5 + 0xcc));
		if (v15) {
			*(int*) (v5 + 0xb8) = *(int*) (v15 + 1);
			*(int*) (v5 + 0x10) = *(int*) (v15 + 1);
		}
		else {
			*(int*) (v5 + 0x84) = fcn_004c5620(-1, (void*) v5);
			return;
		}
		*(int*) (v5 + 0x84) = fcn_004c5620(*(int*) (v5 + 0x70) + 1, (void*) v5);
		return;

	case 6:
		*(int*) (v5 + 0x84) = -1;
		fcn_005015e0(&v15, 0, 0, *(int*) (v5 + 0xb8));
		if (!v15) {
			*(int*) (v5 + 0x70) = -1;
			return;
		}
		v8 = fcn_005742e0((void*) (v5 + 0xe4), (void*) (v5 + 0xd4), (void*) v15,
			(void*) (v5 + 0xf0), (void*) v5);
		if (!v8) {
			*(int*) (v5 + 0x84) = fcn_004c5620(-1, (void*) v5);
			fcn_004432d0(v30, 1);
			return;
		}
		fcn_00510820(*(int*) (v15 + 0x61), v15, 2);
		v8 = *(unsigned char*) v15;
		v27 = *(int*) 0x868050 + v8 * 0x24d;
		if (*(int*) 0x774800) {
			*(int*) (v5 + 0xc4) = fcn_00574150(v5);
			*(int*) (v5 + 0xc0) = 10;
		}
		else {
			v11 = fcn_00574150(v5);
			*(int*) (v5 + 0xc4) = v11;
			*(int*) (v5 + 0xc0) = *(unsigned int*) (v27 + 0x243) * 0x3fc / v11;
		}
		*(int*) (v5 + 0xc8) = 0;
		fcn_00500bb0((void*) (v5 + 0x52), 0, 1, 0);
		*(int*) (v5 + 0x70) = *(int*) (v5 + 0x70) + 1;
		return;

	case 7:
		*(int*) (v5 + 0x84) = -1;
		fcn_004432d0(0, 1);
		fcn_005015e0(&v15, 0, 0, *(int*) (v5 + 0xb8));
		if (!v15 || !fcn_005985f0(v16, (int) v15)) {
			*(int*) (v5 + 0x84) = fcn_004c5620(-1, (void*) v5);
			fcn_004432d0(v30, 1);
			return;
		}
		v13 = 0;
		v21 = 1e+35f;
		v29 = 0.0f;
		v11 = 0;
		do {
			v14 = (unsigned char*) (v11 + *(int*) 0x90e094);
			if (v14 != v15 && *v14 && (v24 = *(int*) (v14 + 0x61)) != 0) {
				fcn_00455350((char*) v24, (char*) (v24 + 0x4c), v17);
				v17[0] = v17[0] - *(float*) (v16 + 0x40);
				v17[1] = v17[1] - *(float*) (v16 + 0x44);
				v17[2] = v17[2] - *(float*) (v16 + 0x48);
				v29 = (float) sqrt(v17[0] * v17[0] + v17[1] * v17[1] + v17[2] * v17[2]);
				if (v29 < v21
					&& fcn_00445600(*(int*) (v11 + *(int*) 0x90e094 + 0x61),
						0x100, 0, 0x68149c)) {
					v21 = v29;
					v13 = v11 + *(int*) 0x90e094;
				}
			}
			v11 += 0xa9;
		} while (v11 < 0xa900);
		if (!v13) {
			*(int*) (v5 + 0x84) = fcn_004c5620(-1, (void*) v5);
			fcn_004432d0(v30, 1);
			return;
		}
		for (v11 = 0; v11 < 33; v11++) {
			v18[v11] = 0;
		}
		fcn_004379a0(*(int*) 0x67a370, *(int*) (v16 + 0x50), 0x2c0, 0x5982d0, v18);
		*(unsigned char*) (v5 + 0xd0) = 0;
		v21 = 0.0f;
		if (v18[32] > 0) {
			v11 = 0;
			do {
				v8 = v18[v11];
				v14 = (unsigned char*) fcn_00445600(*(int*) (v13 + 0x61), 0x100, 0, 0x68149c);
				if (v8 && *(int*) (v8 + 0x218) != 1 && v14) {
					v24 = fcn_00426fd0((char*) 0x6a7dd4);
					if (v24) {
						fcn_00428340(v24, 4, v14, v8, 0x573d90, v5);
						*(int*) (v24 + 0x104) = 0;
						*(int*) (v24 + 0xc8c) = 1;
						fcn_00429670(v24);
					}
					*(unsigned char*) (v5 + 0xd0) = *(unsigned char*) (v5 + 0xd0) + 1;
				}
				v11 += 1;
			} while (v11 < v18[32]);
		}
		*(int*) (v5 + 0x52) = *(int*) 0x7f4c00;
		*(int*) (v5 + 0x56) = *(int*) 0x7f4c04;
		*(int*) (v5 + 0x5a) = *(int*) 0x7f4c08;
		*(unsigned short*) (v5 + 0x5e) = *(unsigned short*) 0x7f4c0c;
		fcn_00500bb0((void*) (v5 + 0x52), 0, 10, 0);
		*(int*) (v5 + 0x70) = *(int*) (v5 + 0x70) + 1;
		fcn_004432d0(v30, 1);
		return;

	case 8:
		*(int*) (v5 + 0x84) = -1;
		fcn_00500bb0((void*) (v5 + 0x52), 0, 0x14, 0);
		if (*(unsigned char*) (v5 + 0xd0)) {
			break;
		}
		fcn_004432d0(0, 1);
		fcn_005015e0(&v15, 0, 0, *(int*) (v5 + 0xb8));
		if (!fcn_005985f0(v16, (int) v15)) {
			*(int*) (v5 + 0x84) = fcn_004c5620(-1, (void*) v5);
			fcn_004432d0(v30, 1);
			return;
		}
		for (v11 = 0; v11 < 33; v11++) {
			v18[v11] = 0;
		}
		fcn_004379a0(*(int*) 0x67a370, *(int*) (v16 + 0x50), 0x2c0, 0x5982d0, v18);
		for (v11 = 0; v11 < v18[32]; v11++) {
			if (*(int*) 0x773dd8) {
				fcn_004550b0(v18[v11], *(int*) 0x773dd8);
			}
			fcn_00442be0(v18[v11]);
		}
		*(int*) (v5 + 0x60) = *(int*) 0x7f4c00;
		*(int*) (v5 + 0x64) = *(int*) 0x7f4c04;
		*(int*) (v5 + 0x68) = *(int*) 0x7f4c08;
		*(unsigned short*) (v5 + 0x6c) = *(unsigned short*) 0x7f4c0c;
		*(int*) (v5 + 0x52) = *(int*) 0x7f4c00;
		*(int*) (v5 + 0x56) = *(int*) 0x7f4c04;
		*(int*) (v5 + 0x5a) = *(int*) 0x7f4c08;
		*(unsigned short*) (v5 + 0x5e) = *(unsigned short*) 0x7f4c0c;
		fcn_00500bb0((void*) (v5 + 0x52), 0, 10, 0);
		*(int*) (v5 + 0x70) = *(int*) (v5 + 0x70) + 1;
		*(int*) (v5 + 0xb4) = 0;
		fcn_004432d0(v30, 1);
		return;

	case 9:
		v8 = fcn_0050cad0((void*) (v5 + 0x60), (void*) 0x7f4c00);
		v36 = v8 + *(int*) (v5 + 0xb4);
		if (v36 < *(int*) (v5 + 0xc0)) {
			fcn_00500bb0((void*) (v5 + 0x52), 0, 0x1e, 0);
			return;
		}
		*(int*) (v5 + 0x60) = *(int*) (v5 + 0x52);
		*(int*) (v5 + 0x64) = *(int*) (v5 + 0x56);
		*(int*) (v5 + 0x68) = *(int*) (v5 + 0x5a);
		*(unsigned short*) (v5 + 0x6c) = *(unsigned short*) (v5 + 0x5e);
		if (!v15) {
			fcn_005015e0(&v15, 0, 0, *(int*) (v5 + 0xb8));
		}
		if (*(int*) (v5 + 0xbc) == -1 && *(int*) (v5 + 0xc8) >= 2) {
			fcn_004432d0(0, 1);
			fcn_0064d41a(v19, (char*) 0x6a7d60, *(int*) (v5 + 4));
			v8 = fcn_00445600(0, 0x1c0, 0, v19);
			fcn_00455350((char*) v8, (char*) (v8 + 0x4c), (float*) v20);
			v21 = 1e+35f;
			v13 = 0;
			v11 = 0;
			do {
				v14 = (unsigned char*) (v11 + *(int*) 0x90e094);
				if (v14 != v15 && *v14 && (v24 = *(int*) (v14 + 0x61)) != 0) {
					fcn_00455350((char*) v24, (char*) (v24 + 0x4c), v17);
					v17[0] = v17[0] - *(float*) (v20 + 0);
					v17[1] = v17[1] - *(float*) (v20 + 4);
					v17[2] = v17[2] - *(float*) (v20 + 8);
					v29 = (float) sqrt(v17[0] * v17[0] + v17[1] * v17[1] + v17[2] * v17[2]);
					if (v29 < v21
						&& (v24 = fcn_00445600(*(int*) (v11 + *(int*) 0x90e094 + 0x61),
							0x100, 0, 0x68149c)) != 0) {
						v21 = v29;
						v13 = v24;
					}
				}
				v11 += 0xa9;
			} while (v11 < 0xa900);
			if (v13 && v8 && (v24 = fcn_00426fd0((char*) 0x6a7db8)) != 0) {
				fcn_00428340(v24, 3, v8, v13, 2);
				*(int*) (v24 + 0xc8c) = 1;
				*(int*) (v24 + 0x104) = 0;
				*(int*) (v5 + 0xbc) = *(int*) (v24 + 0x100);
				fcn_00429670(v24);
			}
			fcn_004432d0(v30, 1);
		}
		v11 = *(int*) (v5 + 0xc0);
		*(int*) (v5 + 0xc8) = *(int*) (v5 + 0xc8) + v36 / v11;
		*(int*) (v5 + 0xb4) = v36 % v11;
		fcn_00500bb0((void*) (v5 + 0x52), 0, v11, 0);
		if (*(int*) 0x6b8010 == 0) {
			if (*(int*) (v5 + 0xc8) <= *(int*) (v5 + 0xc4)) {
				fcn_00573e10(v5);
			}
			if (*(int*) (v5 + 0xc8) == 2 && (*(unsigned char*) (v5 + 0x78) & 2)) {
				for (v11 = 0; v11 < 31; v11++) {
					((int*) v19)[v11] = 0;
				}
				fcn_004c5790(0xc, v19);
			}
		}
		if (*(int*) (v5 + 0xc8) > *(int*) (v5 + 0xc4)) {
			fcn_004432d0(0, 1);
			if (*(int*) (v5 + 0xbc) != -1) {
				v8 = fcn_00426cc0(*(int*) (v5 + 0xbc));
				if (v8) {
					fcn_00428720(v8);
				}
				*(int*) (v5 + 0xbc) = -1;
			}
			if (v30) {
				fcn_00415300(*(int*) (v15 + 0x61));
				*(unsigned char*) (*(int*) (v15 + 0x61) + 0x217) |= 1;
			}
			fcn_00573e10(v5);
			if (*(int*) (v15 + 0x61)) {
				v8 = fcn_00500e20(0x7f4c00);
				if (v8 == 1) {
					*(char*) 0x773dd4 = (char) v8;
				}
				else if (v8 == 0) {
					*(char*) 0x773dd4 = 0;
				}
				else if (v8 == 2) {
					*(char*) 0x773dd4 = (char) v8;
				}
				else if (v8 == 3) {
					*(char*) 0x773dd4 = (char) v8;
				}
				fcn_005165b0(*(int*) (v15 + 0x61));
			}
			if (*(int*) 0x773dd8) {
				fcn_004550e0(*(int*) (v15 + 0x61), *(int*) 0x773dd8);
			}
			v8 = *(int*) (v15 + 0x61);
			if (v8 && *(int*) (v8 + 0x218) == 1) {
				fcn_00442d50(v8, 1);
			}
			v9 = *(char*) (*(unsigned short*) (v15 + 0x27) * 0x21c + 0x7f4ca2);
			if (v9 == 6 || v9 == 5 || v9 == 7) {
				fcn_0052d9d0((void*) v15);
			}
			fcn_00598510();
			if (*(int*) (*(int*) (v15 + 0x61) + 0x1ec)) {
				if (fcn_00413680(*(int*) (v15 + 0x61), *(int*) 0x6b8014, v17, &v21)) {
					v31 = (int) (v21 * 1.8);
					v8 = fcn_00426fd0((char*) 0x6a7da0);
					if (v8) {
						fcn_00428340(v8, 6, (int) v17[0], (int) v17[1], (int) v17[2],
							(int) v21, v31, *(int*) (v15 + 0x61));
						*(int*) (v8 + 0x104) = 0;
					}
				}
			}
			fcn_004bd4e0(*(int*) (v15 + 0x61), *(unsigned char*) v15);
			if (*(unsigned char*) (v5 + 0x78) & 2) {
				fcn_004c5420(*(int*) (v15 + 1), 0x5a, 2, 0, 1);
				if (*(unsigned char*) v15 >= 4 && *(unsigned char*) v15 <= 7) {
					*(int*) v20 = *(int*) 0x7f4c00;
					*(int*) (v20 + 4) = *(int*) 0x7f4c04;
					*(int*) (v20 + 8) = *(int*) 0x7f4c08;
					*(unsigned short*) (v20 + 12) = *(unsigned short*) 0x7f4c0c;
					fcn_004c4510(v15, *(int*) (v15 + 1));
					fcn_004c4570(1, 0xe, 0x69, v20);
					fcn_004c5360();
				}
				if (*(char*) (*(unsigned short*) (v15 + 0x27) * 0x21c + 0x7f4ca2) == 6) {
					if (*(unsigned char*) v15 >= 4 && *(unsigned char*) v15 <= 7) {
						fcn_0051af00(v22, 0x1c2f, v15);
						fcn_00545e80(*(int*) (*(unsigned short*) (v15 + 0x27) * 0x21c + 0x7f4ca4),
							*(int*) (v5 + 0x10), v22, 1, 0x5f6, *(int*) (v15 + 1), -1, 0,
							(char*) 0x6a7d8c);
					}
					else {
						fcn_0051af00(v22, 0x1c27, v15);
						fcn_00545e80(*(int*) (*(unsigned short*) (v15 + 0x27) * 0x21c + 0x7f4ca4),
							*(int*) (v5 + 0x10), v22, 0, 0x5f6, *(int*) (v15 + 1), -1, 0,
							(char*) 0x6a7d8c);
					}
					fcn_004234e0(*(int*) 0x7747b8, 0x6a7d7c, 1, 0x3f, 0x7f, 0, 0);
				}
				v9 = *(char*) (*(unsigned short*) (v15 + 0x27) * 0x21c + 0x7f4ca2);
				if (v9 == 6 || v9 == 5) {
					v27 = 0x7f4ca4;
					do {
						if ((*(char*) (v27 - 2) == 6 || *(char*) (v27 - 2) == 7)
							&& *(int*) v27 != *(int*) (*(unsigned short*) (v15 + 0x27) * 0x21c + 0x7f4ca4)) {
							fcn_0051af00(v22, 0x1c30, *(unsigned short*) (v15 + 0x27),
								(void*) (*(unsigned char*) v15 * 0xe + 0x48e));
							fcn_00545e80(*(int*) v27, -1, v22, 0, 0x607, *(int*) (v15 + 1), -1, 0,
								(char*) 0x6a7d68);
						}
						v27 += 0x21c;
					} while (v27 < 0x85a0a4);
				}
				for (v11 = 0; v11 < 31; v11++) {
					((int*) v19)[v11] = 0;
				}
				fcn_004c5790(0xc, v19);
			}
			v9 = *(unsigned char*) v15;
			if (v9 >= 4 && v9 <= 7) {
				v27 = *(unsigned short*) (v15 + 0x27) * 0x21c + 0x7f4e10;
				v8 = *(int*) v27;
				if (!v8 || *(unsigned char*) v8 > (unsigned char) v9) {
					*(int*) v27 = (int) v15;
				}
			}
			fcn_005001e0((void*) (*(unsigned short*) (v15 + 0x27) * 0x21c + 0x7f4ca0),
				(int) v15);
			fcn_004432d0(v30, 1);
			*(int*) (v5 + 0x7c) = 0;
			fcn_00546190(v5);
			return;
		}
		break;

	case 0:
	case 1:
		fcn_005015e0(&v15, 0, 0, *(int*) (v5 + 0xb8));
		fcn_004432d0(0, 1);
		if (*(int*) (v5 + 0xbc) != -1) {
			v8 = fcn_00426cc0(*(int*) (v5 + 0xbc));
			if (v8) {
				fcn_00428720(v8);
			}
			*(int*) (v5 + 0xbc) = -1;
		}
		*(int*) (v5 + 0xc8) = *(int*) (v5 + 0xc4) + 1;
		fcn_00573e10(v5);
		if ((*(unsigned char*) (v5 + 0x78) & 2) && v15) {
			fcn_004c5fd0(*(int*) (v15 + 1));
			for (v11 = 0; v11 < 31; v11++) {
				((int*) v19)[v11] = 0;
			}
			fcn_004c5790(0xc, v19);
		}
		fcn_004432d0(v30, 1);
		fcn_00546190(v5);
		return;
	}
	return;
}
