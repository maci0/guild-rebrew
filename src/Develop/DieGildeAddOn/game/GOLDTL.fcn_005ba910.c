#include <string.h>

int __cdecl fcn_00470820(int, int, char*);
int __cdecl fcn_0052dee0(int, int, int);

/* ADDRESS: GOLDTL 0x005ba910 */
int __cdecl fcn_005ba910(char* a1, int a2)
{
	int v10;
	int v14;
	int v18;
	int v1c;
	int v20;
	int v24;
	int v28;
	int v2c;
	int v30;
	int v34;
	int v38;
	int v3c;
	int v40;
	int v44;
	int v48;
	int v4c;
	int v50;
	int v54;
	int v58;
	char v5c[4];
	int v60;
	int v64;
	int v68;
	int v6c;
	int v70;
	int v74;
	int v78;
	int v7c;
	int v80;
	int v84;
	int v88;
	int v8c;
	int v90;
	int v94;
	int v98;
	int v9c;
	int vA0;
	int vA4;
	int vA8;
	int vAC;
	int vB0;
	char vB4[8];
	int vBC;
	int vC0;
	char vC4[4];
	int vC8;
	char vCC[4];
	char vD0[4];
	int vD4[7];
	int vF0[7];
	int v10C[9];
	int v130;
	int v134;
	int v138;
	int v13C;
	char v140[8];
	int v148;
	char v14C[4];
	char v150[8];
	int v158;
	char v15C[0xb4];

	v158 = 0;
	memset(v15C, 0, sizeof v15C);
	v18 = 0;
	v44 = 0;
	v94 = 0;
	v7c = (int) a1;
	v88 = 0;
	v10C[0] = 0x51;
	v10C[1] = 0;
	v10C[2] = 0;
	v10C[3] = 0x30;
	v10C[4] = 0x71;
	v10C[5] = 0;
	v10C[6] = 0x11;
	v10C[7] = 0x52;
	v10C[8] = 0x93;
	v38 = 0;
	v68 = 0;
	v40 = 0;
	v3c = 0;
	v4c = 0;
	v60 = 0;
	v50 = 0x3f800000;
	v90 = -1;
	vD4[0] = -1;
	vD4[1] = -1;
	vD4[2] = -1;
	vD4[3] = -1;
	vD4[4] = -1;
	vD4[5] = -1;
	vD4[6] = -1;
	vF0[0] = 0x95;
	vF0[1] = 0x92;
	vF0[2] = 0x93;
	vF0[3] = 0x94;
	vF0[4] = 0x97;
	vF0[5] = 0x96;
	vF0[6] = 0x2db;
	vA4 = -1;
	v14 = (int) a1;
	v80 = a2 & 8;

	if (v80 != 0) {
		int i;
		vA4 = fcn_00470820(*(int*) 0x1040494 - 0x68, 0x106, (char*) 0x6ac3b4);
		for (i = 0; i < 7; i++) {
			vD4[i] = fcn_0052dee0(0, 0xc + i * 0x18, *(int*) (0x14a56e8 + i * 4));
			if (*(short*) 0x7746cc == vF0[i]) {
				*(int*) (*(int*) 0x1015ea0 + vD4[i] * 0x2f4 + 0x38) = 1;
				*(int*) (*(int*) 0x1015ea0 + vD4[i] * 0x2f4 + 0x3c) = 1;
			}
		}
		v14 = *(int*) 0x773d78;
	}

	*(char*) 0x77531c = 0;

	return vA0;
}
