int __cdecl fcn_00413680();
int __cdecl fcn_00426cc0();
int __cdecl fcn_00426fd0();
int __cdecl fcn_00428340();
int __cdecl fcn_00428720();
int __cdecl fcn_00429670();
int __cdecl fcn_004379a0();
int __cdecl fcn_00442d50();
int __cdecl fcn_004432d0();
int __cdecl fcn_004550b0();
int __cdecl fcn_004550e0();
int __cdecl fcn_00455350();
int __cdecl fcn_00456b60();
int __cdecl fcn_004bd4e0();
int __cdecl fcn_004c4450();
int __cdecl fcn_004c4480();
int __cdecl fcn_004c4510();
int __cdecl fcn_004c4570();
int __cdecl fcn_004c4f30();
int __cdecl fcn_004c5150();
int __cdecl fcn_004c5360();
int __cdecl fcn_004c5420();
int __cdecl fcn_004c5620();
int __cdecl fcn_004c5790();
int __cdecl fcn_004c5fd0();
int __cdecl fcn_00500bb0();
int __cdecl fcn_00500cb0();
int __cdecl fcn_00500e20();
int __cdecl gm_ResolveEntityById();
int __cdecl gm_LookupEntityRecordById();
int __cdecl gm_GetEntityTableEntry();
int __cdecl fcn_0050cad0();
int __cdecl fcn_0050f910();
int __cdecl fcn_00510820();
int __cdecl fcn_005165b0();
int __cdecl fcn_00415300();
int __cdecl fcn_004234e0();
int __cdecl io_FormatTextBuffer();
int __cdecl fcn_0052d9d0();
int __cdecl fcn_00546190();
int __cdecl fcn_00546280();
int __cdecl fcn_00573e10();
int __cdecl fcn_00574150();
int __cdecl fcn_005742e0();
int __cdecl fcn_00598510();
int __cdecl lc_GetGebaeudeBauplatz();
double __cdecl sqrt();

/* ADDRESS: GOLDTL 0x005744c0 */
void __cdecl fcn_005744c0(int a0)
{
	int v5;
	int v8;
	int v9;
	int v11;
	int v13;
	int v24;
	int v27;
	int v30;
	int v36;
	int v41;
	int v40;
	char listbuf[0x2c0];
	unsigned char* v14;
	unsigned char* v15;
	int v18[32];
	int v19[32];
	char v16[64];
	char v22[512];
	float v17;
	float v20;
	float v21;
	float v29;
	float v31;
	float v32;
	float v33;
	float v34;
	float v37;
	float v38;
	float v39;
	unsigned short v35;
	char v6;
	char v7;

	v5 = a0;
	v30 = *(int*) 0x6b8010;
	v40 = 0;
	v41 = 0;
	v8 = *(int*) (v5 + 0x84);
	v15 = 0;
	if (v8 != -1 && !fcn_004c4450(v8)) {
		return;
	}
	*(int*) (v5 + 0x84) = -1;
	v8 = *(int*) (v5 + 0x70) + 2;
	switch (v8) {
	case 0:
	case 1:
		gm_ResolveEntityById(&v15, 0, 0, *(int*) (v5 + 0xb8));
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
			fcn_004c5fd0(*(int*) (v15 + 4));
			v8 = 0x1f;
			fcn_004c5790(0xc, v19);
			*(int*) 0x6b8010 = v30;
		}
		fcn_004432d0(*(int*) 0x6b8010, 1);
		fcn_00546190(v5);
		break;

	case 2:
		if (fcn_00500cb0((void*) (v5 + 0x52), 0x7f4c00) <= 0
			&& (*(unsigned char*) (v5 + 0x78) & 2)) {
			if (*(int*) (v5 + 0xac) != *(int*) (*(int*) 0x773da8 + 4)) {
				v8 = gm_LookupEntityRecordById(*(int*) (v5 + 0xac));
				if (!v8) {
					goto label_57469a;
				}
				v13 = *(int*) (v5 + 0xb4);
				v9 = (v8 & 0xffffff00) | *(unsigned char*) 0x773d75;
				v27 = *(int*) (v5 + 0xac);
				*(int*) (v5 + 0xcc) = fcn_004c5150(-1, v27, v9, v13);
				v8 = gm_GetEntityTableEntry(v8);
				if (v8) {
					*(int*) (v8 + 0x54) = *(int*) (v8 + 0x54) + *(int*) (v5 + 0xb4);
				}
			}
			else {
				v13 = *(int*) (v5 + 0xb4);
				*(int*) (v5 + 0xcc) = fcn_0050f910(v13);
			}
label_5746e0:
			v8 = *(int*) (v5 + 0x70);
			*(int*) (v5 + 0x84) = fcn_004c5620(v8 + 1, (void*) v5);
			return;
		}
		break;

	case 3:
		*(int*) (v5 + 0x84) = -1;
		v13 = *(int*) (v5 + 0xcc);
		if (!(*(unsigned char*) (v5 + 0x78) & 4) && fcn_004c4450(v13)) {
			v13 = *(int*) (v5 + 0xcc);
			if (fcn_004c4450(v13) == 2) {
label_5745ff:
				*(int*) (v5 + 0x84) = fcn_004c5620(-1, (void*) v5);
				return;
			}
			goto label_5746e0;
		}
		break;

	case 4:
		if (*(unsigned char*) (v5 + 0x78) & 2) {
			v13 = fcn_004c4f30((v8 & 0xffffff00) | *(unsigned char*) (v5 + 0xb0),
				*(int*) (v5 + 0xac), 0, 1);
			v8 = *(int*) (v5 + 0x70);
			*(int*) (v5 + 0xcc) = v13;
			*(int*) (v5 + 0x84) = fcn_004c5620(v8 + 1, (void*) v5);
			return;
		}
		break;

	case 5:
		*(int*) (v5 + 0x84) = -1;
		v13 = *(int*) (v5 + 0xcc);
		if (!(*(unsigned char*) (v5 + 0x78) & 4) && fcn_004c4450(v13)) {
			v13 = *(int*) (v5 + 0xcc);
			if (fcn_004c4450(v13) == 2) {
label_57469a:
				*(int*) (v5 + 0x84) = fcn_004c5620(-1, (void*) v5);
				return;
			}
			v15 = (unsigned char*) fcn_004c4480(*(int*) (v5 + 0xcc));
			if (!v15) {
				goto label_5745ff;
			}
			*(int*) (v5 + 0xb8) = *(int*) (v15 + 4);
			*(int*) (v5 + 0x10) = *(int*) (v15 + 4);
			goto label_5746e0;
		}
		break;

	case 6:
		*(int*) (v5 + 0x84) = -1;
		gm_ResolveEntityById(&v15, 0, 0, *(int*) (v5 + 0xb8));
		if (!v15) {
			*(int*) (v5 + 0x70) = -1;
			return;
		}
		v8 = fcn_005742e0(v5 + 0xe4, v5 + 0xd4, v15, v5 + 0xf0, v5);
		if (v8) {
			fcn_00510820(*(int*) (v15 + 0x61), v15, 2);
			v8 = *(int*) 0x868050 + *(unsigned char*) v15 * 0x24d;
			if (*(int*) 0x774800) {
				*(int*) (v5 + 0xc4) = fcn_00574150(v5);
				*(int*) (v5 + 0xc0) = 10;
			}
			else {
				v11 = fcn_00574150(v5);
				*(int*) (v5 + 0xc4) = v11;
				*(int*) (v5 + 0xc0) = *(int*) (v8 + 0x243) * 0x3fc / v11;
			}
			*(int*) (v5 + 0xc8) = 0;
			fcn_00500bb0((void*) (v5 + 0x52), 0, 1, 0);
			*(int*) (v5 + 0x70) = *(int*) (v5 + 0x70) + 1;
			return;
		}
		goto label_574753;

	case 7:
		*(int*) (v5 + 0x84) = -1;
		fcn_004432d0(0, 1);
		gm_ResolveEntityById(&v15, 0, 0, *(int*) (v5 + 0xb8));
		if (v15 && lc_GetGebaeudeBauplatz(v16, v15)) {
			v8 = 0;
			v21 = 1e+35f;
			v29 = 0.0f;
			v11 = 0;
			do {
				v14 = (unsigned char*) (v11 + *(int*) 0x90e094);
				if (v14 != v15 && *v14
					&& (v24 = *(int*) (v14 + 0x61)) != 0) {
					fcn_00455350((void*) v24, (void*) (v24 + 0x4c), &v17);
					v17 = v17 - v37;
					v31 = v31 - v38;
					v32 = v32 - v39;
					v29 = (float) sqrt(v17 * v17 + v31 * v31 + v32 * v32);
					if (v29 < v21
						&& fcn_00445600((void*) *(int*) (v11 + 0x61 + *(int*) 0x90e094),
							0x100, 0, (char*) 0x68149c)) {
						v21 = v29;
						v8 = v11 + *(int*) 0x90e094;
					}
				}
				v11 += 0xa9;
			} while (v11 < 0xa900);
			if (!v8) {
				*(int*) (v5 + 0x84) = fcn_004c5620(-1, (void*) v5);
				fcn_004432d0(v30, 1);
				return;
			}
			v8 = 0x21;
			fcn_004379a0(*(int*) 0x67a370, listbuf, 0x2c0, (void*) 0x5982d0, v18);
			*(char*) (v5 + 0xd0) = 0;
			v21 = 0.0f;
			if (1 <= v41) {
				v11 = 0;
				do {
					v8 = v18[v11];
					v14 = (unsigned char*) fcn_00445600(
						(void*) *(int*) (*(int*) 0x90e094 + 0x61), 0x100, 0,
						(char*) 0x68149c);
					if (v8 && *(int*) (v8 + 0x218) != 1 && v14) {
						v24 = fcn_00426fd0((char*) 0x6a7dd4);
						if (v24) {
							fcn_00428340((void*) v24, 4, v14, (void*) v8,
								(void*) 0x573d90, (void*) v5);
							*(int*) (v24 + 0x104) = 0;
							*(int*) (v24 + 0xc8c) = 1;
							fcn_00429670((void*) v24);
						}
						*(char*) (v5 + 0xd0) = *(char*) (v5 + 0xd0) + 1;
					}
					v11 += 1;
				} while (v11 < v41);
			}
			*(int*) (v5 + 0x52) = *(int*) 0x7f4c00;
			*(int*) (v5 + 0x56) = *(int*) 0x7f4c04;
			*(int*) (v5 + 0x5a) = *(int*) 0x7f4c08;
			*(unsigned short*) (v5 + 0x5e) = *(unsigned short*) 0x7f4c0c;
			fcn_00500bb0((void*) (v5 + 0x52), 0, 10, 0);
			*(int*) (v5 + 0x70) = *(int*) (v5 + 0x70) + 1;
			fcn_004432d0(v30, 1);
			return;
		}
label_574753:
		*(int*) (v5 + 0x84) = fcn_004c5620(-1, (void*) v5);
		fcn_004432d0(v11, 1);
		return;

	case 8:
		v13 = v5 + 0x52;
		*(int*) (v5 + 0x84) = -1;
		fcn_00500bb0((void*) (v5 + 0x52), 0, 0x14, 0);
		if (!*(char*) (v5 + 0xd0)) {
			fcn_004432d0(0, 1);
			gm_ResolveEntityById(&v15, 0, 0, *(int*) (v5 + 0xb8));
			v8 = lc_GetGebaeudeBauplatz(v16, v15);
			if (!v8) {
				*(int*) (v5 + 0x84) = fcn_004c5620(-1, (void*) v5);
				fcn_004432d0(v30, 1);
				return;
			}
			fcn_004379a0(*(int*) 0x67a370, listbuf, 0x2c0, (void*) 0x5982d0, v18);
			v8 = 0;
			if (1 <= v41) {
				do {
					if (*(int*) 0x773dd8) {
						fcn_004550b0(v18[v8], *(int*) 0x773dd8);
					}
					fcn_00442d50(v18[v8], 1);
					v8 += 1;
				} while (v8 < v41);
			}
			*(int*) (v5 + 0x60) = *(int*) 0x7f4c00;
			*(int*) (v5 + 0x64) = *(int*) 0x7f4c04;
			*(int*) (v5 + 0x68) = *(int*) 0x7f4c08;
			*(unsigned short*) (v5 + 0x6c) = *(unsigned short*) 0x7f4c0c;
			*(int*) v13 = *(int*) 0x7f4c00;
			*(int*) (v5 + 0x56) = *(int*) 0x7f4c04;
			*(int*) (v5 + 0x5a) = *(int*) 0x7f4c08;
			*(unsigned short*) (v5 + 0x5e) = *(unsigned short*) 0x7f4c0c;
			fcn_00500bb0((void*) v13, 0, 10, 0);
			*(int*) (v5 + 0x70) = *(int*) (v5 + 0x70) + 1;
			*(int*) (v5 + 0xb4) = 0;
			fcn_004432d0(v30, 1);
			return;
		}
		break;

	case 9:
		v8 = fcn_0050cad0((void*) (v5 + 0x60), 0x7f4c00);
		v8 += *(int*) (v5 + 0xb4);
		v36 = v8;
		if (v8 < *(int*) (v5 + 0xc0)) {
			fcn_00500bb0((void*) (v5 + 0x52), 0, 0x1e, 0);
			return;
		}
		*(int*) (v5 + 0x60) = *(int*) (v5 + 0x52);
		*(int*) (v5 + 0x64) = *(int*) (v5 + 0x56);
		*(int*) (v5 + 0x68) = *(int*) (v5 + 0x5a);
		*(unsigned short*) (v5 + 0x6c) = *(unsigned short*) (v5 + 0x5e);
		if (!v15) {
			gm_ResolveEntityById(&v15, 0, 0, *(int*) (v5 + 0xb8));
		}
		if (*(int*) (v5 + 0xbc) == -1 && 2 <= *(int*) (v5 + 200)) {
			fcn_004432d0(0, 1);
			v8 = 0;
			fcn_00413680((int) v19, (int) 0x6a7d60, *(int*) (v5 + 4), 0);
			v11 = fcn_00445600(0, 0x1c0, 0, (char*) v19);
			fcn_00455350((void*) v11, (void*) (v11 + 0x4c), &v20);
			v21 = 1e+35f;
			v24 = 0;
			do {
				v14 = (unsigned char*) (v24 + *(int*) 0x90e094);
				if (v14 != v15 && *v14
					&& (v13 = *(int*) (v14 + 0x61)) != 0) {
					fcn_00455350((void*) v13, (void*) (v13 + 0x4c), &v17);
					v17 = v17 - v20;
					v31 = v31 - v33;
					v32 = v32 - v34;
					v29 = (float) sqrt(v17 * v17 + v31 * v31 + v32 * v32);
					if (v29 < v21
						&& (v13 = fcn_00445600((void*) *(int*) (v24 + 0x61 + *(int*) 0x90e094),
							0x100, 0, (char*) 0x68149c)) != 0) {
						v21 = v29;
						v8 = v13;
					}
				}
				v24 += 0xa9;
			} while (v24 < 0xa900);
			if (v8 && v11 && (v24 = fcn_00426fd0((char*) 0x6a7db8)) != 0) {
				fcn_00428340((void*) v24, 3, (void*) v11, (void*) v8, (void*) 2);
				*(int*) (v24 + 0xc8c) = 1;
				*(int*) (v24 + 0x104) = 0;
				*(int*) (v5 + 0xbc) = *(int*) (v24 + 0x100);
				fcn_00429670((void*) v24);
			}
			fcn_004432d0(v30, 1);
			v8 = v36;
		}
		v11 = *(int*) (v5 + 0xc0);
		*(int*) (v5 + 200) = *(int*) (v5 + 200) + v8 / v11;
		*(int*) (v5 + 0xb4) = v8 % v11;
		fcn_00500bb0((void*) (v5 + 0x52), 0, v11, 0);
		if (!*(int*) 0x6b8010) {
			if (*(int*) (v5 + 200) <= *(int*) (v5 + 0xc4)) {
				fcn_00573e10(v5);
			}
			if (*(int*) (v5 + 200) == 2 && (*(unsigned char*) (v5 + 0x78) & 2)) {
				fcn_004c5790(0xc, v19);
			}
		}
		if (*(int*) (v5 + 0xc4) < *(int*) (v5 + 200)) {
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
				v6 = (char) v8;
				if (v8 == 1) {
					*(char*) 0x773dd4 = v6;
				}
				else if (v8 == 2) {
					*(char*) 0x773dd4 = v6;
				}
				else if (v8 == 3) {
					*(char*) 0x773dd4 = v6;
				}
				else {
					*(char*) 0x773dd4 = 0;
				}
				fcn_005165b0(*(int*) (v15 + 0x61));
			}
			v14 = v15;
			if (*(int*) 0x773dd8) {
				fcn_004550e0(*(int*) (v15 + 0x61), *(int*) 0x773dd8);
				v14 = v15;
			}
			v8 = *(int*) (v14 + 0x61);
			if (v8 && *(int*) (v8 + 0x218) == 1) {
				fcn_00442d50(v8, 1);
				v14 = v15;
			}
			v7 = *(char*) (*(unsigned short*) (v14 + 0x27) * 0x21c + 0x7f4ca2);
			if (v7 == 6 || v7 == 5 || v7 == 7) {
				fcn_0052d9d0((void*) v14);
			}
			fcn_00598510();
			if (*(int*) (*(int*) (v15 + 0x61) + 0x1ec)
				&& fcn_00413680(*(int*) (v15 + 0x61), *(int*) 0x6b8014,
					&v17, &v21)) {
				v8 = fcn_00426fd0((char*) 0x6a7da0);
				if (v8) {
					fcn_00428340((void*) v8, 6,
						(void*) (int) v17, (void*) (int) v20,
						(void*) (int) v21, (void*) *(int*) (v15 + 0x61));
					*(int*) (v8 + 0x104) = 0;
				}
			}
			fcn_004bd4e0(*(int*) (v15 + 0x61), *(int*) v15);
			if (*(unsigned char*) (v5 + 0x78) & 2) {
				fcn_004c5420(*(int*) (v15 + 4), 0x5a, 2, 0, 1);
				v14 = v15;
				if (4 <= *(int*) v15 && *(int*) v15 <= 7) {
					fcn_004c4510(v15, *(int*) (v15 + 4));
					fcn_004c4570(1, 0xe, 0x69, &v20);
					fcn_004c5360();
					v14 = v15;
				}
				if (*(char*) (*(unsigned short*) (v14 + 0x27) * 0x21c + 0x7f4ca2) == 6) {
					if (4 <= *(int*) v14 && *(int*) v14 <= 7) {
						io_FormatTextBuffer((void*) v22, 0x1c2f, (void*) v14);
						v13 = *(int*) (v15 + 4);
						v9 = *(int*) (*(unsigned short*) (v15 + 0x27) * 0x21c + 0x7f4ca4);
						v27 = *(int*) (v5 + 0x10);
						v24 = 1;
					}
					else {
						io_FormatTextBuffer((void*) v22, 0x1c27, (void*) v14);
						v13 = *(int*) (v15 + 4);
						v27 = *(int*) (v5 + 0x10);
						v24 = 0;
						v9 = *(int*) (*(unsigned short*) (v15 + 0x27) * 0x21c + 0x7f4ca4);
					}
					fcn_00456b60(v9, v27, (void*) v22, v24, 0x5f6, v13, -1, 0,
						(char*) 0x6a7d8c);
					fcn_004234e0(*(int*) 0x7747b8, 0x6a7d7c, 1, 0x3f, 0x7f, 0, 0);
					v14 = v15;
				}
				v7 = *(char*) (*(unsigned short*) (v14 + 0x27) * 0x21c + 0x7f4ca2);
				if (v7 == 6 || v7 == 5) {
					v9 = 0x7f4ca4;
					do {
						if ((*(char*) (v9 - 2) == 6 || *(char*) (v9 - 2) == 7)
							&& *(int*) v9 != *(int*) (*(unsigned short*) (v14 + 0x27) * 0x21c + 0x7f4ca4)) {
							io_FormatTextBuffer((void*) v22, 0x1c30,
								(void*) *(unsigned short*) (v14 + 0x27),
								(void*) (*(int*) v14 * 0xe + 0x48e));
							fcn_00456b60(*(int*) v9, -1, (void*) v22, 0, 0x607,
								*(int*) (v15 + 4), -1, 0, (char*) 0x6a7d68);
							v14 = v15;
						}
						v9 += 0x87 * 4;
					} while (v9 < 0x85a0a4);
				}
				fcn_004c5790(0xc, v19);
			}
			if (4 <= *(int*) v15 && *(int*) v15 <= 7) {
				v14 = (unsigned char*) *(int*) (*(unsigned short*) (v15 + 0x27) * 0x21c + 0x7f4e10);
				if (!v14 || *(unsigned char*) v14 <= *(int*) v15) {
					*(int*) (*(unsigned short*) (v15 + 0x27) * 0x21c + 0x7f4e10) = (int) v15;
				}
			}
			fcn_00500e20(*(unsigned short*) (v15 + 0x27) * 0x21c + 0x7f4ca0);
			fcn_004432d0(v30, 1);
			*(int*) (v5 + 0x7c) = 0;
			fcn_00546190(v5);
			return;
		}
		break;
	}
}
