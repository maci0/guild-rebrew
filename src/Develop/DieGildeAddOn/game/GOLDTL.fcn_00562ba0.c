int __cdecl fcn_004c4450(int a0);
int __cdecl fcn_004c4480(int a0);
int __cdecl gm_GetEntityTableEntry(int a0);
int __cdecl fcn_004c51a0(int a0, int a1, int a2, int a3);
void __cdecl fcn_00529160(int a0, int a1, int a2, int a3);
int __cdecl gm_StartFilteredEntitySearch(int a0, int a1, int a2);
int __cdecl fcn_004c5da0(int a0, int a1, int a2, int a3, int a4, int a5);
int __cdecl gm_LookupEntityRecordById(int a0);
void __cdecl fcn_00500bb0(int* p, int a1, int a2, int a3);
int __cdecl fcn_00500cb0(int a0, int a1);
int __cdecl fcn_00494740(int a0, int a1, int a2);
int __cdecl fcn_005c6270(int a0, int a1);
void __cdecl fcn_005100f0(int a0, int a1);
void __cdecl io_FormatTextBuffer(char* buf, int id, int a2, int a3);
void __cdecl fcn_00545d40(int a0, int a1, char* buf, int a3, int a4, char* text);
int __cdecl fcn_004f4f60(int a0, int a1, int a2, int a3, int a4);
void __cdecl fcn_004c54c0(int a0, int a1, int a2, int a3);
int __cdecl fcn_0055be70(int* a0);
int __cdecl fcn_005463a0(int a0, int a1, int a2);
int __cdecl fcn_004c58b0(int a0, int a1);
void __cdecl fcn_004c57e0(int a0, int a1);
void __cdecl fcn_00546190(int a0);

/* ADDRESS: GOLDTL 0x00562ba0 */
void __cdecl fcn_00562ba0(int a0)
{
	int v3;
	int v6;
	int v4;
	int v7;
	int v9;
	int v13;
	int state;
	int a[3];
	char v1;
	char buf[1024];
	char* text;
	char* v14;
	int v10[4];
	char v11[4];

	v3 = a0;
	state = *(int*) (a0 + 0x70);
	if (state > 0 && (*(int*) (a0 + 0xc8) == 0 || *(int*) (a0 + 0xc8) == -1)) {
		*(int*) (a0 + 0x70) = -2;
	}
	switch (*(int*) (a0 + 0x70)) {
	case 0:
		v6 = *(int*) (v3 + 0xcc);
		if (v6 != -1 && fcn_004c4450(v6) == 0) {
			return;
		}
		v7 = fcn_004c4480(*(int*) (v3 + 0xcc));
		if (v7 != 0) {
			v4 = gm_GetEntityTableEntry(*(unsigned short*) (v3 + 8) * 0x21c + 0x7f4ca0);
			if (v4 != 0) {
				*(int*) (v4 + 0x28) = *(int*) (v4 + 0x28) + *(int*) (v3 + 0xd8);
			}
			*(int*) (v3 + 0xc8) = *(int*) (v7 + 4);
			fcn_004c51a0(-1, *(int*) (*(unsigned short*) (v3 + 8) * 0x21c + 0x7f4ca4), (int) *(unsigned char*) 0x773d75, *(int*) (v3 + 0xd8));
			fcn_00529160(0, 0, *(unsigned short*) v7, v3);
			*(int*) (v3 + 0xcc) = -1;
			*(int*) (v3 + 0x70) = *(int*) (v3 + 0x70) + 1;
			return;
		}
		*(int*) (v3 + 0x70) = -1;
		*(int*) (v3 + 0xcc) = -1;
		return;
	case 1:
		v6 = gm_StartFilteredEntitySearch(1, 1, *(int*) (v3 + 0xd0));
		if (v6 != 0) {
			v9 = *(int*) (v6 + 1);
			*(int*) (v3 + 0xcc) = fcn_004c5da0(*(int*) (v3 + 0xc8), v9, -1, 0, 1, 0x6a659c);
			*(int*) (v3 + 0x70) = *(int*) (v3 + 0x70) + 1;
			return;
		}
		goto label_562e74;
	case 2:
		*(int*) (v3 + 0xcc) = -1;
		v6 = gm_LookupEntityRecordById(*(int*) (v3 + 0xc8));
		if (v6 != 0) {
			if (*(int*) (*(int*) (v6 + 0x184) + 0x128) != 0) {
				*(int*) (v3 + 0x52) = *(int*) 0x7f4c00;
				*(int*) (v3 + 0x56) = *(int*) 0x7f4c04;
				*(int*) (v3 + 0x5a) = *(int*) 0x7f4c08;
				*(unsigned short*) (v3 + 0x5e) = *(unsigned short*) 0x7f4c0c;
				fcn_00500bb0((int*) (v3 + 0x52), 0, 4, 0);
				*(int*) (v3 + 0x70) = 2;
				return;
			}
			*(int*) (v3 + 0x70) = 7;
			return;
		}
		break;
	case 3:
		fcn_004c5da0(*(int*) (v3 + 0xc8), *(int*) (v3 + 0x10), -1, 0, 1, 0x6a659c);
		*(int*) (v3 + 0x70) = *(int*) (v3 + 0x70) + 1;
		return;
	case 4:
		v6 = v3 + 0x52;
		if (0 <= fcn_00500cb0(v6, 0x7f4c00)) {
			return;
		}
		v6 = *(unsigned short*) (v3 + 8) * 0x21c;
		v7 = gm_LookupEntityRecordById(*(int*) (v3 + 0xb4));
		if (v7 == 0) {
			*(int*) (v3 + 0x70) = -1;
			return;
		}
		v4 = fcn_00494740(v6 + 0x7f4ca0, v7, (int) v11);
		if (fcn_005c6270(v7, 0x2c0)) {
			fcn_005100f0(*(int*) (v6 + 0x7f4ca4), -1);
			if (*(char*) (v6 + 0x7f4ca2) == 6 || *(char*) (v6 + 0x7f4ca2) == 7) {
				io_FormatTextBuffer(buf, 0x1012, *(unsigned short*) v7, 2);
				fcn_00545d40(*(int*) (v6 + 0x7f4ca4), -1, buf, 0, 0x5fa, 0);
			}
			if (*(char*) (v7 + 2) != 6 && *(char*) (v7 + 2) != 7) {
				goto label_563129;
			}
			io_FormatTextBuffer(buf, 0x1010, 0, 0);
			v9 = *(int*) (v7 + 4);
			text = (char*) 0x6a6538;
			v13 = 0x5fb;
		} else {
			if (fcn_005c6270(v7, 0x17c) == 0) {
				v1 = *(char*) (v7 + 2);
				if (v4 != 0) {
					if (v1 == 6 || v1 == 7) {
						io_FormatTextBuffer(buf, 0x173b, 2, 0);
						fcn_00545d40(*(int*) (v7 + 4), -1, buf, 0, 0x5fb, (char*) 0x6a6538);
					}
					if (*(char*) (v6 + 0x7f4ca2) == 6 || *(char*) (v6 + 0x7f4ca2) == 7) {
						io_FormatTextBuffer(buf, 0x173a, *(unsigned short*) v7, 0);
						fcn_00545d40(*(int*) (v6 + 0x7f4ca4), -1, buf, 0, 0x5fa, 0);
					}
					if (fcn_005c6270(v7, 0x2b4)) {
						fcn_005100f0(*(int*) (v3 + 0xb4), -1);
					} else {
						fcn_005100f0(*(int*) (v3 + 0xb4), -2);
					}
				} else {
					if (v1 == 6 || v1 == 7) {
						io_FormatTextBuffer(buf, 0x173d, 0, 0);
						fcn_00545d40(*(int*) (v7 + 4), -1, buf, 0, 0x5fb, 0);
					}
					if (*(char*) (v6 + 0x7f4ca2) == 6 || *(char*) (v6 + 0x7f4ca2) == 7) {
						io_FormatTextBuffer(buf, 0x173c, *(unsigned short*) v7, 0);
						fcn_00545d40(*(int*) (v6 + 0x7f4ca4), -1, buf, 0, 0x5fa, 0);
					}
				}
				fcn_004f4f60(0x15, 1, *(int*) (*(unsigned short*) (v3 + 8) * 0x21c + 0x7f4ca4), *(int*) (v3 + 0xb4), *(int*) (v3 + 0xac));
				if (*(char*) (v7 + 2) != 6 && *(char*) (v7 + 2) != 7) {
					fcn_004c54c0(*(int*) (v6 + 0x7f4ca4), *(int*) (v7 + 4), -0x19, 1);
					*(int*) (v3 + 0x70) = *(int*) (v3 + 0x70) + 1;
					return;
				}
				goto label_563129;
			}
			if (*(char*) (v6 + 0x7f4ca2) != 6 && *(char*) (v6 + 0x7f4ca2) != 7) {
				goto label_563129;
			}
			io_FormatTextBuffer(buf, 0xff3, 0, 0);
			v9 = *(int*) (v6 + 0x7f4ca4);
			text = 0;
			v13 = 0x5fa;
		}
		fcn_00545d40(v9, -1, buf, 0, v13, text);
label_563129:
		*(int*) (v3 + 0x70) = *(int*) (v3 + 0x70) + 1;
		return;
	case 5:
		v6 = gm_LookupEntityRecordById(*(int*) (v3 + 0xc8));
		if (v6 == 0) {
			*(int*) (v3 + 0x70) = -1;
			return;
		}
		if (*(int*) (*(int*) (v6 + 0x184) + 0x128) != 0) {
			*(int*) (v3 + 0x52) = *(int*) 0x7f4c00;
			*(int*) (v3 + 0x56) = *(int*) 0x7f4c04;
			*(int*) (v3 + 0x5a) = *(int*) 0x7f4c08;
			*(unsigned short*) (v3 + 0x5e) = *(unsigned short*) 0x7f4c0c;
			fcn_00500bb0((int*) (v3 + 0x52), 0, 4, 0);
			return;
		}
		break;
	case 7:
		v6 = gm_StartFilteredEntitySearch(1, 1, *(int*) (v3 + 0xd0));
		v4 = gm_LookupEntityRecordById(*(int*) (v3 + 0xb4));
		if (v6 != 0 && v4 != 0) {
			v10[0] = v6;
			v10[1] = 0x457a0000;
			v10[2] = v3;
			v10[3] = 0;
			if (fcn_0055be70(v10) != 0) {
				v9 = *(int*) (v6 + 1);
				v13 = *(int*) (v4 + 4);
				*(int*) (v3 + 0xcc) = fcn_004f4f60(0x15, 1, *(int*) (*(unsigned short*) (v3 + 8) * 0x21c + 0x7f4ca4), v13, v9);
				*(int*) (v3 + 0x70) = 8;
				*(int*) (v3 + 0xd4) = *(int*) (v10[3] + 4);
				*(int*) (v3 + 0x52) = *(int*) 0x7f4c00;
				*(int*) (v3 + 0x56) = *(int*) 0x7f4c04;
				*(int*) (v3 + 0x5a) = *(int*) 0x7f4c08;
				*(unsigned short*) (v3 + 0x5e) = *(unsigned short*) 0x7f4c0c;
				return;
			}
		}
label_562e74:
		*(int*) (v3 + 0x70) = 4;
		return;
	case 8:
		v6 = *(int*) (v3 + 0xcc);
		if (v6 != -1 && fcn_004c4450(v6) == 0) {
			return;
		}
		v6 = gm_StartFilteredEntitySearch(1, 1, *(int*) (v3 + 0xac));
		v4 = fcn_005463a0(1, 1, *(int*) (v3 + 0xd4));
		if (v6 != 0 && v4 != 0 && *(int*) (v4 + 0xd4) == *(int*) (v3 + 4) && *(int*) (v3 + 0xcc) != -1) {
			v6 = gm_LookupEntityRecordById(*(int*) (v3 + 0xd4));
			v7 = fcn_004c4480(*(int*) (v3 + 0xcc));
			if (v7 != 0 && v6 != 0) {
				fcn_004c58b0(*(int*) v7, *(int*) (v6 + 4));
			}
			*(int*) (v3 + 0x70) = 9;
			fcn_00500bb0((int*) (v3 + 0x52), 0, 10, 0);
			return;
		}
		break;
	case 9:
		v6 = fcn_005463a0(1, 1, *(int*) (v3 + 0xd4));
		if (v6 == 0) {
			*(int*) (v3 + 0x70) = -1;
			return;
		}
		if (*(int*) (v6 + 0xd4) == *(int*) (v3 + 4)) {
			fcn_00500bb0((int*) (v3 + 0x52), 0, 6, 0);
			return;
		}
		fcn_004c5da0(*(int*) (v3 + 0xc8), *(int*) (v3 + 0x10), -1, 0, 1, 0x6a659c);
		*(int*) (v3 + 0x52) = *(int*) 0x7f4c00;
		*(int*) (v3 + 0x56) = *(int*) 0x7f4c04;
		*(int*) (v3 + 0x5a) = *(int*) 0x7f4c08;
		*(unsigned short*) (v3 + 0x5e) = *(unsigned short*) 0x7f4c0c;
		fcn_00500bb0((int*) (v3 + 0x52), 0, 4, 0);
		*(int*) (v3 + 0x70) = 5;
		return;
	case -2:
	case -1:
		if (*(int*) (v3 + 0xc8) != -1) {
			fcn_004c57e0(*(int*) (v3 + 0xc8), 1);
		}
		fcn_00546190(v3);
		return;
	}
	*(int*) (v3 + 0x70) = -1;
}
