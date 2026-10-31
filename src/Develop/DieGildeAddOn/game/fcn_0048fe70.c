int __cdecl gm_LookupEntityRecordById(int id);
int __cdecl fcn_0047d220(char* p);
void* __cdecl fcn_004f18d0(char* a1, char* a2, int a3, int a4, int a5);
int __cdecl fcn_004f4550(int a, int b, int c, int* out);
int __cdecl fcn_0050d320(int a, char b);
int __cdecl fcn_004f4440(char* a1, int a2, int a3, int a4, int* out);
int __cdecl fcn_004f1790(int a, int* b);
int __cdecl fcn_0042e410(int a);

/* ADDRESS: GOLDTL 0x0048fe70 */
int __cdecl fcn_0048fe70(int a0, char* a1, int a2, int* a3, int* a4, int* a5)
{
	int cand[8];
	char* rec;
	int* v9;
	int* v4;
	int n;
	int i;
	int v;
	int out;
	int m;
	int t;

	v9 = 0;
	if (a2 != 0) {
		return 0;
	}
	if (a0 != 0) {
		return 0;
	}
	if (*(unsigned short*) (a1 + 0x50) == 0x7fff) {
		return 0;
	}
	if ((*(int*) 0x7f4c04 & 0xffff) % 6 != (unsigned) (*(int*) (a1 + 4)) % 6) {
		return 0;
	}
	if (*(int*) 0x7f4c00 % 3 != (unsigned) (*(int*) (a1 + 4)) % 3) {
		return 0;
	}
	if (*(char*) (a1 + 2) != 5) {
		rec = (char*) gm_LookupEntityRecordById(*(int*) (a1 + 0x5c));
		if (rec != 0) {
			if (*(char*) (rec + 2) == 5) {
				return 0;
			}
			if (*(char*) (rec + 9) == 0 && fcn_0047d220(rec) != 0) {
				return 0;
			}
		}
	}
	rec = *(char**) 0x90e094;
	for (i = 0; i < 8; i++) {
		cand[i] = 0;
	}
	n = 0;
	a2 = 0;
	do {
		if (*rec != 0 && (rec[0x5a] & 1) == 0
		    && *(char*) (*(int*) 0x868050 + (unsigned char) *rec * 0x24d) == 0x1d) {
			if (n < 8) {
				cand[n] = (int) rec;
				n++;
			}
			v9 = (int*) fcn_004f18d0(a1, rec, 0, 0x4f17f0, 0xff);
			if (v9 != 0) {
				break;
			}
		}
		rec += 0xa9;
		a2++;
	} while (a2 < 0x100);

	if (v9 != 0) {
		if (*v9 == 3) {
			return 0;
		}
		v = 3;
		if (*v9 >= 3) {
			return 0;
		}
		do {
			v4 = (int*) fcn_004f18d0(0, rec, 0, 0x4f1840, v);
			if (v4 != 0) {
				break;
			}
			v--;
		} while (v > *v9);
		if (v4 != 0) {
			out = fcn_004f4550((int) a1, *v9, *v4, &a2);
			m = fcn_0050d320((int) a1, *(char*) 0x773d75);
			if ((int) ((float) m * *(float*) 0x664160) <= out) {
				return 0;
			}
			a3[4] = 5;
			*(int*) ((char*) a3 + 0xc) = *(int*) (rec + 1);
			a3[1] = *v4;
			a3[2] = out;
			a4[1] = *v9;
			a4[4] = fcn_004f1790(*(int*) (rec + 0x65), v9);
			return 0x3e;
		}
	} else if (n != 0
	    && 0x23 <= (fcn_0042e410(8) & 0xffff) + *(unsigned short*) (a1 + 0xa)) {
		v9 = (int*) cand[fcn_0042e410(n) & 0xffff];
		v4 = (int*) fcn_004f18d0(0, (char*) v9, 0, 0x4f1840, 0xff);
		if (v4 != 0) {
			t = fcn_004f4440((int) a1, 0xff, *v4, 1, &out);
			m = fcn_0050d320((int) a1, *(char*) 0x773d75);
			if ((int) ((float) m * *(float*) 0x664160) < t) {
				return 0;
			}
			a3[4] = 4;
			*(int*) ((char*) a3 + 0xc) = *(int*) ((char*) v9 + 1);
			a3[2] = t;
			a3[1] = *v4;
			return 0x3e;
		}
	}
	return 0;
}
