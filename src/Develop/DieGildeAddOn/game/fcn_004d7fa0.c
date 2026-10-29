char* __cdecl fcn_004cef30(int id);
int __cdecl fcn_0042e410(int code);
char* __cdecl fcn_004ceac0(int a, char* s);
int __cdecl fcn_004d2f70(char* s);
char* __cdecl fcn_004d34f0(char* s);
int __cdecl fcn_00455350(char* a, char* b, void* c);
char __cdecl fcn_0045b990(int a, void* b, void* c, void* d, void* e);
int __cdecl fcn_004c67c0(int a, void* b);
double __cdecl fcn_004ff040(char* s);
int __cdecl fcn_0064d228(float v);
void* __cdecl memcpy(void* dst, const void* src, unsigned int n);

/* ADDRESS: GOLDTL 0x004d7fa0 */
int __cdecl fcn_004d7fa0(int a, int b)
{
	int level;
	int count80;
	int countC0;
	int i;
	char* base;
	char* s;
	char* e;
	char* e2;
	char* found;
	int tmp[12];
	int t2[8];
	int v;
	int r;
	double ratio;
	double val;

	level = *(int*) 0x772f2c;
	if (level < 1) {
		return level;
	}
	if (b == *(int*) 0x772e9c) {
		base = (char*) 0x772f74;
	} else {
		base = (char*) 0x772f34;
	}
	count80 = 0;
	for (i = 0; i < 0x10; i++) {
		v = *(int*) (0x772f34 + i * 4);
		if (v != -1) {
			s = fcn_004cef30(v);
			if (s[8] != 0 && s[8] != 4) {
				count80++;
			}
		}
	}
	countC0 = 0;
	for (i = 0; i < 0x10; i++) {
		v = *(int*) (0x772f74 + i * 4);
		if (v != -1) {
			s = fcn_004cef30(v);
			if (s[8] != 0 && s[8] != 4) {
				countC0++;
			}
		}
	}
	if (b == *(int*) 0x772e9c) {
		ratio = (double) countC0 / (double) count80;
	} else {
		ratio = (double) count80 / (double) countC0;
	}
	if (ratio < 0.5 || (fcn_0042e410(0x64) & 0xffff) <= 0x14) {
		found = 0;
		i = 0;
		while (i < 0x10 && found == 0) {
			v = *(int*) (base + i * 4);
			if (v != -1) {
				found = fcn_004cef30(v);
			}
			i++;
		}
		if (found == 0) {
			return 0;
		}
		e = (char*) fcn_004ceac0(a, found);
		*(int*) e = *(int*) (found + 4);
		*(int*) (e + 4) = 5;
		return (int) e;
	}
	for (i = 0; i < 0x10; i++) {
		v = *(int*) (base + i * 4);
		if (v == -1) {
			continue;
		}
		s = fcn_004cef30(v);
		e = (char*) fcn_004ceac0(a, s);
		memcpy(tmp, e, 0x2c);
		val = fcn_004ff040(s) * 100.0;
		r = (int) val;
		if (r < 0x14 || (fcn_0042e410(0x64) & 0xffff) > 0x1e) {
			r = fcn_004d2f70(s);
			if (r == 0) {
				continue;
			}
			e2 = (char*) r;
			*(int*) (tmp + 0) = *(int*) (s + 4);
			*(int*) (tmp + 1) = 2;
			*(int*) (tmp + 5) = *(int*) (e2 + 4);
			fcn_004c67c0(a, tmp);
		} else {
			e2 = (char*) fcn_004d34f0(s);
			fcn_00455350(e2, e2 + 0x4c, t2);
			r = fcn_0045b990(*(int*) (*(int*) 0x67a370 + 0xb0),
			    t2, &t2[1], &t2[2], &t2[3]);
			if (r != 0) {
				continue;
			}
			*(int*) (tmp + 0) = *(int*) (s + 4);
			*(int*) (tmp + 1) = 3;
			*(int*) (tmp + 3) = a;
			*(int*) (tmp + 5) = countC0;
			fcn_004c67c0(a, tmp);
		}
	}
	(void) found;
	return 0;
}
