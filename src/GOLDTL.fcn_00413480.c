extern char* g_6b8014;

void __cdecl fcn_00438100(char*, char*, int);
void __cdecl fcn_00455540(char*, float*, float*);

/* ADDRESS: GOLDTL 0x00413480 */
int __cdecl fcn_00413480(char* a0, float a1, float* a2, float* a3, float* a4, float* a5)
{
	float lo[3];
	float hi[3];
	float t[3];
	char* m;
	char* list;
	char* e;
	float v;
	int n;
	int i;
	int j;

	if (*(int*) (a0 + 0x218) != 4)
		return 1;
	if (!(*(unsigned char*) (a0 + 0x216) & 0x20))
		fcn_00438100(a0, g_6b8014, 0);
	m = *(char**) (a0 + 0x1cc);
	m = *(char**) (m + 0x318);
	n = *(int*) (m + 0x44);
	i = 0;
	if (n > 0) {
		list = *(char**) (m + 0x27c);
		e = *(char**) (a0 + 0x1ec);
		do {
			v = *(float*) (list) * *(float*) (e + 0xc) + *(float*) (list + 4) * *(float*) (e + 0x1c) + *(float*) (list + 8) * *(float*) (e + 0x2c) + *(float*) (e + 0x3c);
			if (v <= a1) {
				lo[0] = *(float*) (list);
				lo[1] = *(float*) (list + 4);
				lo[2] = *(float*) (list + 8);
				hi[0] = *(float*) (list);
				hi[1] = *(float*) (list + 4);
				hi[2] = *(float*) (list + 8);
				break;
			}
			i++;
			list += 12;
		} while (i < n);
	}
	if (i < n) {
		list = *(char**) (m + 0x27c) + i * 12;
		e = *(char**) (a0 + 0x1ec);
		n -= i;
		do {
			v = *(float*) (list) * *(float*) (e + 0xc) + *(float*) (list + 4) * *(float*) (e + 0x1c) + *(float*) (list + 8) * *(float*) (e + 0x2c) + *(float*) (e + 0x3c);
			if (v <= a1) {
				for (j = 0; j < 3; j++) {
					if (*(float*) (list + j * 4) <= lo[j])
						lo[j] = *(float*) (list + j * 4);
					if (hi[j] <= *(float*) (list + j * 4))
						hi[j] = *(float*) (list + j * 4);
				}
			}
			list += 12;
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
