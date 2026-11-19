extern int g_772f2c;
extern unsigned short* g_772f24;
extern unsigned short* g_772e9c;
extern char* g_772eb4;
extern int g_67a370;

char* __cdecl fcn_004cef30(int id);
int* __cdecl fcn_004ceac0(char*, char*);
float __cdecl fcn_004ff040(char*);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_004d2f70(char*);
char* __cdecl fcn_004d34f0(char*);
void __cdecl fcn_00455350(char*, char*, float*);
char __cdecl fcn_0045b990(int, float*, int*, int*, float*);

/* ADDRESS: GOLDTL 0x004d4430 */
void __cdecl fcn_004d4430(char* a0)
{
	int* p;
	int* base;
	int i;
	int n;
	int v;
	int* x;
	int t;
	char* e;
	char* r;
	float pos[4]; /* native frame has one more word than three floats */
	int col;
	int row;
	float height;

	if (g_772f2c < 1) {
		return;
	}
	p = (int*) (a0 + 0x98);
	for (n = 16; n != 0; n--, p = (int*) ((char*) p + 0x2c)) {
		if (g_772f2c > 1) {
			if (p[0] == 3 || p[0] == 4) {
				continue;
			}
			if (p[0] == 2) {
				if (*(char*) (fcn_004cef30(p[3]) + 8) != 0) {
					continue;
				}
			}
		}
		p[-1] = -1;
		p[0] = 0;
	}
	if ((int) g_772f24 == (int) g_772e9c) {
		base = (int*) (g_772eb4 + 0xc0);
	} else {
		base = (int*) (g_772eb4 + 0x80);
	}
	for (i = 0; i < 16; i++) {
		if (base[i] == -1) {
			continue;
		}
		e = fcn_004cef30(base[i]);
		fcn_004ceac0(a0, e);
		v = (int) (fcn_004ff040(e) * 100.0);
		if (v >= 20 || (unsigned short) fcn_0042e410(100) <= 0x1e) {
			t = fcn_004d2f70(e);
			if (t == 0) {
				continue;
			}
			x = fcn_004ceac0(a0, e);
			x[0] = *(int*) (e + 4);
			x[1] = 2;
			x[4] = *(int*) (t + 4);
		} else {
			r = fcn_004d34f0(e);
			fcn_00455350(r, r + 0x4c, pos);
			if (fcn_0045b990(*(int*) (g_67a370 + 0xb0), pos, &col, &row, &height)) {
				continue;
			}
			x = fcn_004ceac0(a0, e);
			x[0] = *(int*) (e + 4);
			x[1] = 3;
			x[4] = col;
			x[5] = row;
		}
	}
}
