#include <stdlib.h>

int __cdecl fcn_004e6f10(unsigned char);
void __cdecl fcn_004e8b40(unsigned char, char*);
void __cdecl fcn_004f4830(int, int*);
int __cdecl gm_MapEntityStatRange(unsigned char);

/* ADDRESS: GOLDTL 0x004e7990 */
float __cdecl fcn_004e7990(int a0, int a1, int a2, int a3)
{
	float v;
	char v9[0x18];
	int v10[9];
	float v14;
	int i;
	int j;
	int code;
	int v7;
	int* tbl;

	v = 0.0f;
	i = fcn_004e6f10(*(unsigned char*) (a1 + 0x166));
	if (i >= 1 && i <= 6) {
		j = 0;
		tbl = (int*) 0x664f38;
		do {
			if (gm_MapEntityStatRange(*(unsigned char*) (a0 + 0x164)) == *tbl) {
				v = *(float*) ((i + j * 10) * 4 + 0x664f3c);
				if (a2 >= 2) {
					v = v + (float) abs((int) v);
				}
				break;
			}
			tbl += 10;
			j++;
		} while ((int) tbl < 0x665190);
	}
	code = *(int*) (a1 + 0x1cc);
	if (code & 0x1000) {
		code = 0x26;
	} else if (code & 0x2000) {
		code = 0x27;
	} else if (code & 0x800) {
		code = 0x25;
	} else if (code & 0x400) {
		code = 0x24;
	} else {
		code = (code & 0x200) ? 0x23 : 0;
	}
	if (code != 0) {
		if ((*(int*) (a0 + 0x1cc) & 0x3c00) == 0) {
			v7 = (*(int*) (a0 + 0x1cc) & 0x200) ? 0x23 : 0;
			if (v7 == 0) {
				j = 0;
				tbl = (int*) 0x665198;
				do {
					if (*tbl == code) {
						v = v + *(float*) ((fcn_004e6f10(*(unsigned char*) (a0 + 0x166)) + j * 10) * 4 +
								   0x66519c);
						break;
					}
					tbl += 10;
					j++;
				} while ((int) tbl < 0x665260);
			}
		}
		if (a2 >= 3) {
			v = v + *(float*) 0x6640cc;
		}
	}
	if (a3 != 0) {
		fcn_004e8b40(*(unsigned char*) (a1 + 0x166), v9);
		fcn_004f4830(2, v10);
		v14 = *(float*) (v9 + 4);
		if (v10[6] == 2) {
			v14 = v14 * *(float*) 0x662a6c;
		}
		if (*(char*) (a0 + 0xc) == *(char*) (a1 + 0xc)) {
			return v14 + v;
		}
		if (a2 == 0) {
			return v - v14;
		}
	}
	return v;
}
