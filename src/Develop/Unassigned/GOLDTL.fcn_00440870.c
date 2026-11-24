#include <math.h>

typedef struct IDev IDev;
// SIZE 0x158
typedef struct IDevVtbl {
	void* s0[11];
	long (__stdcall* Lock)(IDev*, int, int, void**, int);
	long (__stdcall* Unlock)(IDev*);
	void* s1[37];
	long (__stdcall* f_c8)(IDev*, int, int);
	void* s2[10];
	long (__stdcall* f_f4)(IDev*, int, int);
	void* s3[9];
	long (__stdcall* f_11c)(IDev*, int, int, int, int, int);
	void* s4[4];
	long (__stdcall* f_130)(IDev*, int);
	void* s5[6];
	long (__stdcall* f_14c)(IDev*, int, void*, int);
	void* s6[1];
	long (__stdcall* f_154)(IDev*, void*, int);
} IDevVtbl;

struct IDev {
	IDevVtbl* v;
};

void __cdecl d3_NormalizeVector(float* v);
void __cdecl fcn_004372d0(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x00440870 */
void __cdecl fcn_00440870(char* o, char* c)
{
	char* m;
	char* map;
	char* bmp;
	char* r;
	char* ent;
	char* obj;
	int* t;
	int* e;
	int i;
	int j;
	int a;
	int row;
	int rowbase;
	int stride;
	int mask;
	int bd;
	int idx;
	unsigned char sb;
	unsigned int c0;
	unsigned int c1;
	unsigned int c2;
	unsigned int col;
	float fa;
	float fb;
	float px;
	float py;
	float pz;
	float h2;
	float hh;
	float f;
	float v[3];
	float d;

	m = o;
	if (m == 0 || c == 0 || *(char*) (c + 0x1ee) == 0 || *(char*) (c + 0x1bc) == 0
	    || *(int*) (c + 0x1a0) == 0 || *(int*) (c + 0x1a4) == 0) {
		return;
	}
	v[0] = *(float*) 0x1042160;
	v[1] = *(float*) 0x1042164;
	v[2] = *(float*) 0x1042168;
	d3_NormalizeVector(v);
	d = 0.5f
	    - (float) fabs(*(float*) 0x662d48 * v[2] + *(float*) 0x662d44 * v[1] + *(float*) 0x662d40 * v[0]);
	mask = *(int*) (m + 0xc);
	bmp = *(char**) (m + 0x18);
	stride = *(int*) m;
	((IDev*) *(void**) (c + 0x1a4))->v->Lock((IDev*) *(void**) (c + 0x1a4), 0, 0, (void**) &o, 0x2000);
	map = *(char**) (c + 0x1b8);
	t = (int*) (map + 0xc);
	e = (int*) (map + 4);
	if (*e >= 0) {
		do {
			a = t[-2];
			row = *((unsigned char*) t + 4);
			rowbase = (a & mask) * stride;
			fa = (float) a;
			fb = (float) t[-1];
			px = fa * *(float*) (m + 0x70) + fb * *(float*) (m + 0x60);
			py = fa * *(float*) (m + 0x74) + fb * *(float*) (m + 0x64);
			pz = fa * *(float*) (m + 0x78) + fb * *(float*) (m + 0x68);
			r = *(char**) (m + 0x7da0) + row * 0x158;
			bd = *((unsigned char*) r + 8);
			h2 = d * *(float*) (r + 0x14) + (float) bd;
			if ((*((unsigned char*) r + 0xa) & 1) != 0) {
				for (j = t[-1]; j <= *t; j++) {
					idx = (j & mask) + rowbase;
					hh = (float) *((unsigned char*) bmp + idx);
					*(float*) o = px + *(float*) (r + 0x38 + ((j & 3) + (a & 3) * 4) * 0x10);
					*(float*) (o + 4) = hh * *(float*) (m + 0x84) + *(float*) (r + 0x3c + ((j & 3) + (a & 3) * 4) * 0x10) + py;
					*(float*) (o + 8) = pz + *(float*) (r + 0x40 + ((j & 3) + (a & 3) * 4) * 0x10);
					f = h2 + *(float*) (r + 0x44 + ((j & 3) + (a & 3) * 4) * 0x10);
					if (0.0f <= f && f > *(float*) 0x6628a4) {
						f = *(float*) 0x6628a4;
					} else if (0.0f > f) {
						f = 0.0f;
					}
					col = (unsigned int) (int) f;
					*(unsigned int*) (o + 0xc) = ((col | 0xffffff00) << 8 | (col & 0xff)) << 8 | (col & 0xff);
					*(float*) (o + 0x10) = (float) j + *(float*) (r + 0x148);
					*(float*) (o + 0x14) = (float) a + *(float*) (r + 0x14c);
					px = px + *(float*) (m + 0x60);
					o += 0x18;
				}
			} else {
				for (j = t[-1]; j <= *t; j++) {
					idx = (j & mask) + rowbase;
					hh = (float) *((unsigned char*) bmp + idx);
					*(float*) o = px + *(float*) (r + 0x38 + ((j & 3) + (a & 3) * 4) * 0x10);
					*(float*) (o + 4) = hh * *(float*) (m + 0x84) + *(float*) (r + 0x3c + ((j & 3) + (a & 3) * 4) * 0x10) + py;
					*(float*) (o + 8) = pz + *(float*) (r + 0x40 + ((j & 3) + (a & 3) * 4) * 0x10);
					f = h2 + *(float*) (r + 0x44 + ((j & 3) + (a & 3) * 4) * 0x10);
					if (0.0f <= f && f > *(float*) 0x6628a4) {
						f = *(float*) 0x6628a4;
					} else if (0.0f > f) {
						f = 0.0f;
					}
					col = (unsigned int) (int) f;
					sb = *((unsigned char*) *(char**) (m + 0x1c) + idx);
					f = (float) (sb & 0x7f) * 2.0f * *(float*) (m + 0x90) + *(float*) 0x67bbdc;
					if ((sb & 0x80) != 0) {
						f = f + *(float*) 0x6b86c4;
					}
					c0 = (unsigned int) (int) f;
					if (c0 > 0xff) {
						c0 = 0xff;
					}
					f = (float) (sb & 0x7f) * 2.0f * *(float*) (m + 0x94) + *(float*) 0x67bbe0;
					if ((sb & 0x80) != 0) {
						f = f + *(float*) 0x6b86c8;
					}
					c1 = (unsigned int) (int) f;
					if (c1 > 0xff) {
						c1 = 0xff;
					}
					f = (float) (sb & 0x7f) * 2.0f * *(float*) (m + 0x98) + *(float*) 0x67bbe4;
					if ((sb & 0x80) != 0) {
						f = f + *(float*) 0x6b86cc;
					}
					c2 = (unsigned int) (int) f;
					if (c2 > 0xff) {
						c2 = 0xff;
					}
					*(unsigned int*) (o + 0xc) = ((col << 8 | (c0 & 0xff)) << 8 | (c1 & 0xff)) << 8 | (c2 & 0xff);
					*(float*) (o + 0x10) = (float) j + *(float*) (r + 0x148);
					*(float*) (o + 0x14) = (float) *e + *(float*) (r + 0x14c);
					px = px + *(float*) (m + 0x60);
					o += 0x18;
				}
			}
			t += 5;
			e = t - 2;
			if (*e < 0) {
				break;
			}
		} while (1);
	}
	((IDev*) *(void**) (c + 0x1a4))->v->Unlock((IDev*) *(void**) (c + 0x1a4));
	*(int*) 0x10432a8 = *(int*) 0x10432a8 + *(int*) (c + 0x1b0);
	*(int*) 0x1042a08 = *(int*) 0x1042a08 + *(int*) (c + 0x1b0);
	*(int*) 0x1042a04 = *(int*) 0x1042a04 + *(int*) (c + 0x1ac);
	*(int*) 0x1052bac = *(int*) 0x1052bac + *(int*) (c + 0x1ac);
	((IDev*) *(void**) 0x6b5de0)->v->f_130((IDev*) *(void**) 0x6b5de0, 0x142);
	((IDev*) *(void**) 0x6b5de0)->v->f_14c((IDev*) *(void**) 0x6b5de0, 0, *(void**) (c + 0x1a4), 0x18);
	((IDev*) *(void**) 0x6b5de0)->v->f_154((IDev*) *(void**) 0x6b5de0, *(void**) (c + 0x1a0), 0);
	for (i = 0; i < *(int*) (c + 0x1a8); i++) {
		ent = *(char**) (*(char**) (c + 0x1b4) + i * 0x14 + 0x10);
		obj = *(char**) (ent + 4);
		fcn_004372d0(*((unsigned char*) ent + 8), *((unsigned char*) ent + 0xa) & 1, 0,
		             (*((unsigned char*) ent + 0xa) >> 1) & 1, 0);
		((IDev*) *(void**) 0x6b5de0)->v->f_c8((IDev*) *(void**) 0x6b5de0, 0x2f, 0);
		((IDev*) *(void**) 0x6b5de0)->v->f_f4((IDev*) *(void**) 0x6b5de0, 0, *(int*) (obj + 0x50));
		((IDev*) *(void**) 0x6b5de0)->v->f_11c(
		    (IDev*) *(void**) 0x6b5de0, 4, *(int*) (*(char**) (c + 0x1b4) + i * 0x14),
		    *(int*) (*(char**) (c + 0x1b4) + i * 0x14 + 4), *(int*) (*(char**) (c + 0x1b4) + i * 0x14 + 8),
		    *(int*) (*(char**) (c + 0x1b4) + i * 0x14 + 0xc));
	}
}
