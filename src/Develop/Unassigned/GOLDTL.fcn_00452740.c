int __cdecl fcn_00452420(void);
int __cdecl fcn_0045cb10(int, int);
void __cdecl fcn_004557c0(int, int);
void __cdecl fcn_004372d0(int, int, int, int, int);

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
	int stride;
	int base;
	float sum;
	float avg;
	char phase;

	obj = (unsigned char *) arg;
	if (*(void **) (obj + 0x310) == 0) {
		fcn_00452420();
		return;
	}
	phase = ((char (__cdecl *) (void *)) * (void **) (obj + 0x310))(obj);
	if (phase == 0) {
		fcn_00452420();
		return;
	}
	*(int *) 0x10432a8 += *(int *) (obj + 0xd8) * 2;
	*(int *) 0x1042a04 += *(int *) (obj + 0xd8) * 4;
	n = *(int *) (obj + 0xd8);
	cnt = 0;
	if (n > 0) {
		for (i = 0; i < n; i++) {
			p = *(int *) (obj + 0x28) + i * 0x54;
			if ((*(unsigned char *) (p + 0x51) & 1) != 0 && *(char *) (p + 0x4f) != 0) {
				if (*(char *) (p + 0x50) == 0)
					v = *(int *) (obj + 0xdc);
				else
					v = fcn_0045cb10(*(int *) (obj + 0xe0), p);
				cnt++;
				*(int *) (*(int *) (obj + 0x2c) - 4 + cnt * 4) = v;
				*(int *) (*(int *) (obj + 0x30) - 4 + cnt * 4) = p;
			}
		}
	}
	fcn_004557c0((int) (obj + 0xe8),
				 ~-((*(unsigned char *) (obj + 0x2fc) & 0x20) != 0) & *(unsigned int *) 0x6b8014);
	first = **(int **) 0x6b5de0;
	(*(void (__cdecl **) (int)) (first + 0x94))(*(int *) 0x6b5de0);
	if (cnt > 0) {
		for (k = 0; k < cnt; k++) {
			item = *(int *) (*(int *) (obj + 0x2c) + k * 4);
			if (item != 0) {
				int color;
				int vidx;
				int vobj;
				int vert;

				vidx = **(int **) 0x6b5de0;
				base = (*(int (__cdecl **) (int)) (vidx + 0xf4))(*(int *) 0x6b5de0);
				color = (*(unsigned char *) (item + 0x5a) >> 1) & 0xff;
				fcn_004372d0((color << 8) | *(unsigned char *) (item + 0x58),
							 ((*(unsigned char *) (item + 0x5a) & 0xff) << 8) | *(unsigned char *) (item + 0x59),
							 *(int *) (item + 0x6c), base, 1);
				if (*(int *) 0x67bc4c - *(int *) 0x6b8718 < k)
					*(int *) 0x6b8718 = 0;
				sum = 0.0f;
				avg = 0.0f;
				if ((*(unsigned char *) 0x6b8710 & 0x20) == 0) {
					vert = (-(*(int *) 0x6b8718 != 0) & 0xfffff000) + 0x2000;
					(*(void (__cdecl **) (int, int, int, int *))
					 (**(int **) 0x104095c + 0x2c))(*(int *) 0x104095c,
												   *(int *) 0x6b8714 * *(int *) 0x6b8718,
												   (cnt - k) * *(int *) 0x6b8714,
												   (int *) &sum);
					for (i = k; i < cnt; i++) {
						if (*(int *) (*(int *) (obj + 0x2c) + i * 4)
							== **(int **) (obj + 0x2c)) {
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
							avg += 1.0f;
							cnt = cnt;
						}
					}
					sum /= avg;
					(*(void (__cdecl **) (int, int, int)) (**(int **) 0x6b5de0 + 0xc8))(
						*(int *) 0x6b5de0, 0x9a, (int) sum);
				} else {
					vert = (-(*(int *) 0x6b8718 != 0) & 0xfffff000) + 0x2000;
					(*(void (__cdecl **) (int, int, int, int *, int))
					 (**(int **) 0x104095c + 0x2c))(*(int *) 0x104095c,
												   *(int *) 0x6b8714 * *(int *) 0x6b8718,
												   (cnt - k) * *(int *) 0x6b8714,
												   (int *) &sum, vert);
					for (i = k; i < cnt; i++) {
						if (*(int *) (*(int *) (obj + 0x2c) + i * 4)
							== **(int **) (obj + 0x2c)) {
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
							vert += 0x14;
						}
					}
				}
				(*(void (__cdecl **) (int)) (**(int **) 0x104095c + 0x30))(*(int *) 0x104095c);
				(*(void (__cdecl **) (int, int, int, int)) (**(int **) 0x6b5de0 + 0x118))(
					*(int *) 0x6b5de0, 1, *(int *) 0x6b8718, vert);
				*(int *) 0x6b8718 += cnt;
				*(int *) (*(int *) (obj + 0x2c) + k * 4) = 0;
			}
		}
	}
	*(int *) 0x1052bac += cnt;
	*(int *) 0x1042a08 += cnt;
}
/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")

/* Layout scaffolding: shifts the next source object to its reference
 * VA. 0x90 filler, not reconstruction. Generated by the text lead pass. */
#pragma data_seg(".text")
unsigned char _tlead_GOLDTL_fcn_00452740[80] = {
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90,
    0x90
};
