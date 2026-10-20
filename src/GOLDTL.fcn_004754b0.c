#include <string.h>

int __cdecl fcn_0064e2f9(void*, int);
int __cdecl fcn_0064e48f(void*, int, int);
int __cdecl fcn_0064ebe4(void*, int, int, void*);
int __cdecl fcn_0064e1fd(void*);
void* __cdecl fcn_0041db70(int, int);
void __cdecl fcn_0041ddd0(void*);

/* ADDRESS: GOLDTL 0x004754b0 */
int __cdecl fcn_004754b0(void* a0, void* a1, int a2, int a3)
{
	char hdr[0x28];
	unsigned char v10[4];
	void* f;
	int v4;
	int v8;
	int v9;
	int v12;
	int v16;
	int v17;
	int v18;
	int v19;
	int n;
	int last;
	int i;
	unsigned char* p;
	void* q;

	f = (void*) fcn_0064e2f9(a0, 0x6750e8);
	if (!f) {
		return 0;
	}
	fcn_0064e48f(f, 0xe, 0);
	fcn_0064ebe4(hdr, 1, 0x28, f);
	v19 = *(int*) (hdr + 0x20);
	if (!v19) {
		v19 = 0x100;
	}
	fcn_0064e48f(f, v19 * 4 + 0x36, 0);
	v16 = *(int*) (hdr + 4);
	v17 = *(int*) (hdr + 8);
	v18 = *(int*) (hdr + 0x10);
	if (v18 != 1) {
		fcn_0064ebe4(a1, v17, v16, f);
	}
	else {
		v12 = 0;
		v9 = 0;
		if (v17 > 0) {
			do {
				fcn_0064ebe4(v10, 1, 2, f);
				v4 = v10[1];
				v8 = v10[1];
				if (v10[0]) {
					v8 = v10[0] >> 2;
					p = (unsigned char*) (v16 * v9 + v12 + (int) a1);
					while (v8) {
						*(unsigned int*) p = (v4 << 24) | (v4 << 16) | (v4 << 8) | v4;
						v8--;
						p += 4;
					}
					v8 = v10[0] & 3;
					while (v8) {
						*p = (unsigned char) v4;
						v8--;
						p++;
					}
					v12 += v10[0];
				}
				else if (v8) {
					if (v8 != 1) {
						if (v8 != 2) {
							if (!(v4 & 1)) {
								fcn_0064ebe4((void*) (v16 * v9 + v12 + (int) a1), v8, 1, f);
							}
							else {
								fcn_0064ebe4((void*) (v16 * v9 + v12 + (int) a1), v8 + 1, 1, f);
							}
							v12 += v10[1];
						}
						else {
							fcn_0064ebe4(v10, 1, 2, f);
							v12 += v10[0];
							v9 += v10[1];
						}
					}
					else {
						v9 = v17;
					}
				}
				else {
					v12 = 0;
					v9++;
				}
			} while (v9 < (v17 < 0 ? -v17 : v17));
		}
	}
	fcn_0064e1fd(f);
	if ((a3 & 0xff) && v17 >= 1) {
		q = fcn_0041db70(v16, 0x67d924);
		n = v17 / 2;
		last = v17 - 1;
		i = 0;
		while (i < n) {
			memcpy(q, (char*) a1 + v16 * i, v16);
			memcpy((char*) a1 + v16 * i, (char*) a1 + v16 * last, v16);
			memcpy((char*) a1 + v16 * last, q, v16);
			i++;
			last--;
		}
		fcn_0041ddd0(q);
	}
	return 1;
}
