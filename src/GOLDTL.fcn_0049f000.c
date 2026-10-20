extern char* g_entity_type_table;
extern unsigned char g_90e094[];
extern unsigned char g_773d75;

int __cdecl fcn_00509570(int);
int __cdecl fcn_0050d320(int, unsigned char);
int __cdecl fcn_005463a0(int, int, int);
int __cdecl fcn_005462a0(void);
int __cdecl fcn_00507d10(char);
int __cdecl fcn_00507910(char);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_00507400(int, int);
int __cdecl fcn_005072c0(int);
int __cdecl fcn_004a4bb0(unsigned int, int, unsigned int, int*, unsigned int*, int);
int __cdecl fcn_0050d170(int);

/* ADDRESS: GOLDTL 0x0049f000 */
unsigned int __cdecl fcn_0049f000(unsigned int a0, char* a1, unsigned int a2, int* a3, unsigned int* a4)
{
	int v8;
	int v9;
	unsigned int v10;
	int v11;
	int v12[17];
	int v13[17];
	unsigned int v14[6];
	int v15[6];
	unsigned char* v16;
	int* v17;
	unsigned int* v18;
	int* v19;
	unsigned int* v2;
	int* v3;
	unsigned int* v4;
	unsigned char v5;
	unsigned short v6;
	int v7;

	v11 = (int) a1;
	v7 = fcn_00509570((int) a1);
	if (!(a1[2] == 5 && *(int*) (a1 + 0x194) >= 4 && v7 != 0)) {
		return 0;
	}
	v8 = fcn_0050d320((int) a1, g_773d75);
	if (((v8 + ((v8 >> 31) & 0x1f)) >> 5) < 5000) {
		return 0;
	}
	v9 = fcn_005463a0(1, 0, 0x24);
	while (v9 != 0) {
		if (*(int*) (v9 + 0xac) == *(int*) (v11 + 4)) {
			return 0;
		}
		v9 = fcn_005462a0();
	}
	fcn_00507d10(*(char*) (v11 + 0x164));
	v17 = v12;
	for (v9 = 0xf; v9 != 0; v9--) {
		*v17 = 0;
		v17++;
	}
	v16 = (unsigned char*) (v7 + 0x75);
	v7 = 0;
	do {
		v5 = *v16;
		v13[v7 / 4 + 1] = fcn_00507d10(v5);
		v7 += 4;
		v16 += 1;
	} while (v7 < 0x3c);
	v7 = 0;
	do {
		if (g_90e094[v7] != 0) {
			v9 = fcn_00507910(g_entity_type_table[g_90e094[v7] * 0x24d]);
			v12[v9] += 1;
		}
		v7 += 0xa9;
	} while (v7 < 0xa900);
	v6 = (unsigned short) fcn_0042e410(4);
	v10 = (unsigned int) fcn_0042e410(0x10) & 0xffff;
	v7 = 0x10;
	do {
		if (v10 != 0 && v13[v10] == 0 && v12[v10] < (int) (v6 + 1)) {
			if (v10 == 0xffffffff) {
				return 0;
			}
			v7 = fcn_00507400(v10, 1);
			v15[1] = fcn_005072c0(v7);
			if (v15[1] == 0) {
				return 0;
			}
			v15[0] = 5;
			v15[2] = 1;
			v14[0] = 0;
			v14[1] = 0;
			v14[2] = 0;
			v11 = fcn_004a4bb0(a0, v11, a2, v15, v14, 1);
			if (v11 == 0) {
				return 0;
			}
			if (v8 < fcn_0050d170(v15[1])) {
				return 0;
			}
			v17 = v15;
			v19 = a3;
			for (v9 = 0; v9 < 6; v9++) {
				*v19 = *v17;
				v17++;
				v19++;
			}
			a3[4] = v7;
			v18 = v14;
			v4 = a4;
			for (v9 = 0; v9 < 6; v9++) {
				*v4 = *v18;
				v18++;
				v4++;
			}
			return 0x34;
		}
		v10 = (v10 + 1) & 0x8000000f;
		if ((int) v10 < 0) {
			v10 = (v10 - 1 | 0xfffffff0) + 1;
		}
		v7 -= 1;
	} while (v7 != 0);
	return 0;
}
