int __cdecl fcn_0050dc90(void*);
int __cdecl fcn_00505370(void*);
int __cdecl fcn_0064d41a(char*, char*, ...);
int __cdecl fcn_0042f120(char*, int, char*);
int __cdecl fcn_00426d50(char*);
int __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(int);
void __cdecl fcn_00428340(int, int, int, int);

/* ADDRESS: GOLDTL 0x00515c60 */
void __cdecl fcn_00515c60(unsigned char* a0, unsigned short* a1)
{
	char v5[260];
	char v6[4];
	char v7[48];
	int v8;
	int v9;
	int z;
	int v3;
	int* v4;
	int r;

	v9 = 0;
	v8 = 0;
	z = 0;
	v3 = fcn_0050dc90(a0);
	v4 = (int*) 0x7e4260;
	do {
		if (v9) {
			goto found;
		}
		v8 = *v4;
		if (v8 && v8 == v3) {
			v9 = v8;
		}
		v4++;
	} while ((int) v4 < 0x7e42e0);
	if (!v9) {
		return;
	}
found:
	if (*(unsigned char*) (v9 + 8) <= 1) {
		return;
	}
	if (a1 && *(int*) (*(int*) (v9 + 0x184) + 0x30) != *(int*) ((char*) a1 + 2)) {
		return;
	}
	if (fcn_00505370(a0)) {
		v9 = *(int*) 0x868050 + *a0 * 0x24d;
	}
	else {
		v9 = *(int*) 0x99ec10 + *a1 * 0x41;
		if (v9) {
			v9++;
			v3 = v9;
			goto format;
		}
		v9 = z;
	}
	v9++;
	v3 = v9;
format:
	fcn_0064d41a(v5, (char*) 0x6a1f54, (char*) 0x6790c8, v9, v3);
	r = fcn_0042f120(v5, *(int*) 0x6b7fdc, v6);
	if (!r) {
		return;
	}
	fcn_0064d41a(v7, (char*) 0x68b0d8, *(int*) (v8 + 4));
	r = fcn_00426d50(v5);
	if (!r) {
		*(int*) 0x699b10 = -1;
		return;
	}
	v3 = *(int*) (*(int*) (v8 + 0x184) + 0x28);
	if (v3 != -1) {
		v3 = fcn_00426cc0(v3);
		if (v3) {
			fcn_00428720(v3);
		}
	}
	fcn_00428340(r, 2, *(int*) (v8 + 0x184), 0x4c3800);
	*(int*) (r + 0xc94) = *(int*) (v8 + 0x184);
	*(int*) (*(int*) (v8 + 0x184) + 0x28) = *(int*) (r + 0x100);
	*(int*) 0x699b10 = *(int*) (r + 0x100);
}
