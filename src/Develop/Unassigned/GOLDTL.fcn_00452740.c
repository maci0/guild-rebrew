extern unsigned int g_6b7fac; void __cdecl fcn_00452420(void*);
int __cdecl fcn_0045cb10(int, char);
void __cdecl fcn_004557c0(char*, char*, int, float*);
void __cdecl fcn_004372d0(unsigned char, unsigned char, int, unsigned char, unsigned char);

/* ADDRESS: GOLDTL 0x00452740 */
void __cdecl fcn_00452740(void *arg)
{
	unsigned char *obj;
	int n;
	int i;
	int cnt;
	int p;
	int v;
	int item;
	int first;
	int k;
	float matrix[16];


	int emitted;


	obj = (unsigned char *) arg;
	if (*(void **) (obj + 0x310) == 0 ||
	    ((char (__cdecl *) (void *, unsigned int)) *(void **) (obj + 0x310))(obj, g_6b7fac) == 0) {
		fcn_00452420(obj);
		return;
	}
	*(int *) 0x10432a8 += *(int *) (obj + 0xd8) * 2;
	*(int *) 0x1042a04 += *(int *) (obj + 0xd8) * 4;
	n = *(int *) (obj + 0xd8);
	cnt = 0;
	if (n > 0) {
		for (i = 0; i < *(int*) (obj + 0xd8); i++) {
			p = *(int *) (obj + 0x28) + i * 0x54;
			if ((*(unsigned char *) (p + 0x51) & 1) != 0 && *(char *) (p + 0x4f) != 0) {
				if (*(char *) (p + 0x50) == 0)
					v = *(int *) (obj + 0xdc);
				else
					v = fcn_0045cb10(*(int *) (obj + 0xe0), *(char*) (p + 0x50));
				cnt++;
				*(int *) (*(int *) (obj + 0x2c) - 4 + cnt * 4) = v;
				*(int *) (*(int *) (obj + 0x30) - 4 + cnt * 4) = p;
			}
		}
	}
	fcn_004557c0((char*) obj + 0xe8,
				 (char*) (~-((*(unsigned char *) (obj + 0x2fc) & 0x20) != 0) & *(unsigned int *) 0x6b8014), 0, matrix);
	first = **(int **) 0x6b5de0;
	(*(int (__stdcall **) (int, int, float*)) (first + 0x94))(*(int *) 0x6b5de0, 0x100, matrix);
	if (cnt > 0) {
		for (k = 0; k < cnt; k++) {
			item = *(int *) (*(int *) (obj + 0x2c) + k * 4);
			if (item != 0) {
				int color;
				int vidx;
				int vobj;


				vidx = **(int **) 0x6b5de0;
				(*(int (__stdcall **) (int, int, int)) (vidx + 0xf4))(*(int *) 0x6b5de0, 0, *(int*) (item + 0x50));
				color = (*(unsigned char *) (item + 0x5a) >> 1) & 1;
				fcn_004372d0(*(unsigned char*) (item + 0x58),
							 *(unsigned char*) (item + 0x5a) & 1,
							 *(int *) (item + 0x6c), color, 1);
				if (*(int *) 0x67bc4c - *(int *) 0x6b8718 < cnt - k)
					*(int *) 0x6b8718 = 0;

				emitted = 0;
				if ((*(unsigned char *) 0x6b8710 & 0x20) == 0) { int vert; float sum; sum = 0.0f;
					v = (-(*(int *) 0x6b8718 != 0) & 0xfffff000) + 0x2000;
					(*(int (__stdcall **) (int, int, int, int *, int))
					 (**(int **) 0x104095c + 0x2c))(*(int *) 0x104095c,
												   *(int *) 0x6b8714 * *(int *) 0x6b8718,
												   (cnt - k) * *(int *) 0x6b8714,
												   &vert, v);
					for (i = k; i < cnt; i++) {
						if (*(int *) (*(int *) (obj + 0x2c) + i * 4)
							== *(int*) (*(int*) (obj + 0x2c) + k * 4)) {
							vobj = *(int *) (*(int *) (obj + 0x30) + i * 4);
							*(int *) vert = *(int *) (vobj + 0x38);
							*(int *) (vert + 4) = *(int *) (vobj + 0x3c);
							*(int *) (vert + 8) = *(int *) (vobj + 0x40);
							sum += *(float *) (vobj + 0x48);
							if ((*(unsigned char *) (item + 0x5a) & 1) == 0)
								*(int *) (vert + 0xc) = *(int *) (vobj + 0x4c);
							else {
								int a;

								a = *(unsigned char *) (vobj + 0x4f);
								*(int *) (vert + 0xc) =
									((((*(unsigned char *) (vobj + 0x4e) * a) >> 8 | (a << 8)) << 8
									  | ((*(unsigned char *) (vobj + 0x4d) * a) >> 8))
									 << 8) | ((*(unsigned char *) (vobj + 0x4c) * a) >> 8);
							}
							vert += 0x10;
							emitted++;
							if (i > k) *(int*) (*(int*) (obj + 0x2c) + i * 4) = 0;
						}
					}
					sum /= emitted;
					(*(int (__stdcall **) (int, int, int)) (**(int **) 0x6b5de0 + 0xc8))(
						*(int *) 0x6b5de0, 0x9a, *(int*) &sum);
				} else { int vert;
					v = (-(*(int *) 0x6b8718 != 0) & 0xfffff000) + 0x2000;
					(*(int (__stdcall **) (int, int, int, int *, int))
					 (**(int **) 0x104095c + 0x2c))(*(int *) 0x104095c,
												   *(int *) 0x6b8714 * *(int *) 0x6b8718,
												   (cnt - k) * *(int *) 0x6b8714,
												   &vert, v);
					for (i = k; i < cnt; i++) {
						if (*(int *) (*(int *) (obj + 0x2c) + i * 4)
							== *(int*) (*(int*) (obj + 0x2c) + k * 4)) {
							vobj = *(int *) (*(int *) (obj + 0x30) + i * 4);
							*(int *) vert = *(int *) (vobj + 0x38);
							*(int *) (vert + 4) = *(int *) (vobj + 0x3c);
							*(int *) (vert + 8) = *(int *) (vobj + 0x40);
							*(int *) (vert + 0xc) = *(int *) (vobj + 0x48);
							if ((*(unsigned char *) (item + 0x5a) & 1) == 0)
								*(int *) (vert + 0x10) = *(int *) (vobj + 0x4c);
							else {
								int a;

								a = *(unsigned char *) (vobj + 0x4f);
								*(int *) (vert + 0x10) =
									((((*(unsigned char *) (vobj + 0x4e) * a) >> 8 | (a << 8)) << 8
									  | ((*(unsigned char *) (vobj + 0x4d) * a) >> 8))
									 << 8) | ((*(unsigned char *) (vobj + 0x4c) * a) >> 8);
							}
							vert += 0x14; emitted++;
							if (i > k) *(int*) (*(int*) (obj + 0x2c) + i * 4) = 0;
						}
					}
				}
				(*(int (__stdcall **) (int)) (**(int **) 0x104095c + 0x30))(*(int *) 0x104095c);
				(*(int (__stdcall **) (int, int, int, int)) (**(int **) 0x6b5de0 + 0x118))(
					*(int *) 0x6b5de0, 1, *(int *) 0x6b8718, emitted);
				*(int *) 0x6b8718 += cnt;
				*(int *) (*(int *) (obj + 0x2c) + k * 4) = 0;
			}
		}
	}
	*(int *) 0x1052bac += cnt;
	*(int *) 0x1042a08 += cnt;
}
