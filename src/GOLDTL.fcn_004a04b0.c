/* Evaluate a walk-order request: pick the direction costs, query a path and
 * report the resulting two packet records. */

extern unsigned char g_773d75;

int __cdecl fcn_00503fe0(int, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0050b810(int, int);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_00495400(int, int, int, int*, int*);
int __cdecl fcn_004a48a0(int, int);
int __cdecl fcn_004a4fb0(int*, int*, int*);
int __cdecl fcn_0050d170(int);
int __cdecl fcn_0050d320(int, int);
int __cdecl fcn_0050bb50(int, int);
int __cdecl _ftol(void);

/* ADDRESS: GOLDTL 0x004a04b0 */
int __cdecl fcn_004a04b0(int a0, unsigned short* a1, int a2, int* a3, int* a4)
{
	unsigned char* v4;
	int v5;
	int v6;
	int v7;
	int v8;
	int v9;
	int v12;
	unsigned int v18;
	unsigned char c;
	int out1[6];
	int out2[6];
	int out3[6];
	int out4[6];

	if (a2 != 0 || *(char*) a3 != 0 || a0 != 0) {
		return 0;
	}
	c = *(unsigned char*) ((int) a1 + 0x169);
	if (c > 0x21) {
		return 0;
	}
	if (c == 0x1e) {
		v18 = 0x17;
	} else if (c == 0x1f) {
		v18 = 0x18;
	} else if (c == 0x20) {
		v18 = 0x19;
	} else {
		v18 = 0x1a;
	}
	v4 = (unsigned char*) fcn_00503fe0(1, 5, v18);
	if (!v4) {
		return 0;
	}
	v5 = fcn_00502cd0(*(int*) (v4 + 0x5d), 2, 6, 0, 0x142);
	v6 = fcn_0050b810(*(int*) (v5 + 0x14), g_773d75);
	c = v4[0x5c];
	if ((signed char) c < (int) ((gm_RandomMod(0x10) & 0xffff) + 0x32) &&
	    !(v4[0x5a] & 4)) {
		out1[1] = *(int*) (v4 + 1);
		out1[0] = 4;
		out1[2] = 1;
		if ((signed char) c < '!') {
			v12 = 0x32;
		} else {
			v12 = ((signed char) c >= 'B') ? 0x14 + 10 : 10;
		}
		out1[4] = v12;
		out2[0] = 1;
		out2[1] = *(int*) (v5 + 2);
		out2[2] = v6;
		out2[4] = 1;
		v7 = fcn_00495400(0xf, *a1, 0, out1, out2);
		if (v7) {
			for (v9 = 0; v9 < 6; v9++) {
				a3[v9] = out1[v9];
				a4[v9] = out2[v9];
			}
			return v7;
		}
		v8 = fcn_004a48a0((int) v4, v12);
		if (v6 < v8) {
			v12 = v8;
			v9 = 1;
			goto label_4a0628;
		}
	}
	if (!fcn_004a4fb0(&a2, &a0, v4)) {
		v12 = *(int*) 0x868050 + (unsigned int) *v4 * 0x24d;
		if (v4[0x5a] & 0x45) {
			return 0;
		}
		if (*(unsigned char*) (v12 + 0x247) >=
		    *(unsigned char*) (v12 + 0x248)) {
			return 0;
		}
		v12 = *v4 + 1;
		fcn_0050d170(v12);
		v7 = _ftol();
		if (v7 < v6) {
			*(char*) a3 = 4;
			a3[1] = v12;
			a3[2] = 1;
			a3[3] = *(int*) (v4 + 1);
			*(char*) a4 = 1;
			a4[1] = *(int*) (v5 + 2);
			a4[2] = 1;
			return 0x39;
		}
		v6 = fcn_0050d320((int) a1, g_773d75);
		if (v6 < 80000) {
			return 0;
		}
		a1 = (unsigned short*) (v6 - 80000);
		if (_ftol() < v7 + 0x20) {
			return 0;
		}
		*(char*) a3 = 1;
		a3[1] = *(int*) (v5 + 2);
		a3[4] = 1;
		*(char*) a4 = 0x12;
		a4[2] = v7 + 0x20;
		return 0x39;
	}
	out3[0] = 2;
	out3[1] = a2;
	out3[2] = 1;
	out3[3] = *(int*) (v5 + 2);
	out3[5] = 0x39;
	out4[5] = v6;
	if (a0 != -1) {
		out4[0] = 1;
		out4[1] = a0;
	} else {
		out4[0] = 4;
		out4[1] = *(int*) (v4 + 1);
	}
	out4[2] = 1;
	out4[4] = 0;
	fcn_0050bb50(a2, g_773d75);
	v9 = _ftol();
	if (v9 < v6) {
		goto label_4a0628;
	}
	v5 = fcn_00495400(0x39, *a1, 1, out3, out4);
	if (!v5) {
		return 0;
	}
	for (v7 = 0; v7 < 6; v7++) {
		a3[v7] = out3[v7];
		a4[v7] = out4[v7];
	}
	return v5;
label_4a0628:
	v6 = fcn_0050d320((int) a1, g_773d75);
	if (v6 < 80000) {
		return 0;
	}
	a1 = (unsigned short*) (v6 - 80000);
	if (_ftol() < v12 + 0x20) {
		return 0;
	}
	*(char*) a3 = 1;
	a3[1] = *(int*) (v5 + 2);
	a3[4] = 1;
	*(char*) a4 = 0x12;
	a4[2] = v12 + 0x20;
	return 0x39;
}
