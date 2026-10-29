char* __cdecl fcn_0045bde0(char*);
char __cdecl fcn_00444860(float, float, int, char*, float*, float*);

/* ADDRESS: GOLDTL 0x0046acf0 */
int __cdecl fcn_0046acf0(int a0, int a1, int a2, int a3, int a4)
{
	char* q;
	char* name;
	char* p;
	char* obj;
	char* e;
	char* t;
	char* d;
	char* s;
	int* list;
	int i;
	int j;
	int cnt;
	int px;
	int py;
	float f1;
	float f2;

	*(int*) 0x102d028 = 0;
	*(int*) 0x102d02c = 0;
	*(char*) 0x1015d00 = 0;
	for (q = (char*) 0x10382d8; q < (char*) 0x1040618; q += 0x2bc) {
		if (!*(int*) (q - 8)) {
			continue;
		}
		if (!*(int*) q) {
			continue;
		}
		if (!*(int*) (q + 4)) {
			continue;
		}
		for (i = 0; i < 2; i++) {
			if (i == 0) {
				name = q + 0x1c;
			}
			else if (i == 1) {
				name = q + 0x5c;
			}
			else {
				continue;
			}
			if (!*name) {
				continue;
			}
			obj = fcn_0045bde0(name);
			if (!obj) {
				continue;
			}
			if (!fcn_00444860((float) a0, (float) a1, 0, obj, &f2, &f1)) {
				continue;
			}
			goto found;
		}
	}
	return -1;
found:
	px = (int) ((double) *(unsigned int*) (obj + 0x64) * f1);
	py = (int) ((double) *(unsigned int*) (obj + 0x64) * f2);
	if (i == 1) {
		py += 0x100;
	}
	*(int*) 0x102d028 = px;
	*(int*) 0x102d02c = py;
	d = (char*) 0x1015d00;
	s = obj;
	while ((*d++ = *s++) != 0) {
	}
	a0 = *(int*) (q - 0x14) - 1;
	p = q - 0x194 + a0 * 4;
	for (; a0 >= 0; a0--) {
		t = (char*) 0x1015f40 + *(int*) p * 0x3cc;
		cnt = *(int*) (t + 0x2c);
		list = *(int**) (t + 0x28);
		{
			for (j = 0; j < cnt; j++) {
				obj = (char*) 0x1015ea0 + list[j] * 0x2f4;
				if (px < *(int*) (obj + 0x10)) {
					continue;
				}
				if (px > *(int*) (obj + 0x10) + *(int*) (obj + 0x18)) {
					continue;
				}
				if (py < *(int*) (obj + 0x14)) {
					continue;
				}
				if (py > *(int*) (obj + 0x14) + *(int*) (obj + 0x1c)) {
					continue;
				}
				if (*(int*) (obj + 0x20) == 0x40) {
					*(int*) 0x67d388 = *(int*) (obj + 0x88);
					continue;
				}
				*(int*) 0x67d370 = list[j];
				if (*(int*) (obj + 0x40)) {
					*(int*) 0x67d388 = **(int**) (obj + 0x40);
				}
				return *(int*) (obj + 8);
			}
		}
		p -= 4;
	}
	*(int*) 0x67d370 = -1;
	return -1;
}
