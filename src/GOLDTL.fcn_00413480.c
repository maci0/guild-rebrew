#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

extern char* g_6b8014;

void __cdecl fcn_00438100(char*, char*, int);
void __cdecl fcn_00455540(char*, float*, float*);

/* ADDRESS: GOLDTL 0x00413480 */
int __cdecl fcn_00413480(char* a0, float a1, float* a2, float* a3, float* a4, float* a5)
{
	float lo[4];
	float hi[4];
	float t[4];
	char* m;
	float* p;
	float* q;
	char* e;
	int n;
	int i;
	int j;

	if (*(int*) (a0 + 0x218) != 4)
		return 1;
	if ((*(unsigned char*) (a0 + 0x216) & 0x20) == 0)
		fcn_00438100(a0, g_6b8014, 0);
	m = *(char**) (*(char**) (a0 + 0x1cc) + 0x318);
	n = *(int*) (m + 0x44);
	i = 0;
	if (n > 0) {
		p = (float*) *(char**) (m + 0x27c);
		e = *(char**) (a0 + 0x1ec);
		do {
			if (p[1] * *(float*) (e + 0x1c) + p[2] * *(float*) (e + 0x2c) + p[0] * *(float*) (e + 0xc) + *(float*) (e + 0x3c) <= a1) {
				q = (float*) *(char**) (m + 0x27c) + i * 3;
				lo[0] = q[0];
				lo[1] = q[1];
				lo[2] = q[2];
				hi[0] = q[0];
				hi[1] = q[1];
				hi[2] = q[2];
				break;
			}
			i++;
			p += 3;
		} while (i < n);
	}
	if (i < n) {
		p = (float*) *(char**) (m + 0x27c) + i * 3;
		e = *(char**) (a0 + 0x1ec);
		n -= i;
		do {
			if (p[1] * *(float*) (e + 0x1c) + p[2] * *(float*) (e + 0x2c) + p[0] * *(float*) (e + 0xc) + *(float*) (e + 0x3c) <= a1) {
				for (j = 0; j < 3; j++) {
					lo[j] = MIN(lo[j], p[j]);
					hi[j] = MAX(hi[j], p[j]);
				}
			}
			p += 3;
			n--;
		} while (n);
	}
	t[0] = lo[0];
	t[1] = lo[1];
	t[2] = lo[2];
	fcn_00455540(a0, t, a2);
	t[0] = hi[0];
	t[1] = lo[1];
	t[2] = lo[2];
	fcn_00455540(a0, t, a3);
	t[0] = hi[0];
	t[1] = lo[1];
	t[2] = hi[2];
	fcn_00455540(a0, t, a4);
	t[0] = lo[0];
	t[1] = lo[1];
	t[2] = hi[2];
	fcn_00455540(a0, t, a5);
	return 0;
}
