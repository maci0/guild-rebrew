int __cdecl fcn_0050dc90(void*);
int __cdecl fcn_00505370(void*);
int __cdecl fcn_0064d41a(char*, char*, ...);
int __cdecl fcn_0042f120(char*, int, char*);
int __cdecl evt_LoadScript(char*);
int __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(int);
void __cdecl fcn_00428340(int, int, int, int);

/* ADDRESS: GOLDTL 0x00515c60 */
void __cdecl fcn_00515c60(unsigned char* a0, unsigned char* a1)
{
	volatile int z;
	char v6[4];
	char v7[48];
	char v5[260];
	int v9;
	int v8;
	int v3;
	int* p;
	int r;

	z = 0;
	v9 = 0;
	v8 = 0;
	v3 = fcn_0050dc90(a0);
	p = (int*) 0x7e4260;
loop:
	if (v9) {
		goto found;
	}
	v8 = *p;
	if (v8 && v8 == v3) {
		v9 = v8;
	}
	p++;
	if ((int) p < 0x7e42e0) {
		goto loop;
	}
	if (!v9) {
		return;
	}
found:
	if (*(unsigned char*) (v9 + 8) <= 1) {
		return;
	}
	if (a1 && *(int*) (*(int*) (v9 + 0x184) + 0x30) != *(int*) (a1 + 2)) {
		return;
	}
	if (fcn_00505370(a0)) {
		v3 = *(int*) 0x868050 + *a0 * 0x24d;
	}
	else {
		v3 = *(int*) 0x99ec10 + *(unsigned short*) a1 * 0x41;
		if (!v3) {
			v3 = z;
		}
	}
	v3++;
	fcn_0064d41a(v5, (char*) 0x6a1f54, (char*) 0x6790c8, v3, v3);
	r = fcn_0042f120(v5, *(int*) 0x6b7fdc, v6);
	if (!r) {
		return;
	}
	fcn_0064d41a(v7, (char*) 0x68b0d8, *(int*) (v8 + 4));
	r = evt_LoadScript(v5);
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
