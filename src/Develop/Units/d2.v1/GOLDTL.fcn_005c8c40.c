/*
 * Scripted scene driver, one step per frame.
 *
 * Creates a script object, runs its state through 0x4693b0 and then drives
 * the three side objects through the 0x471af0 gate while the selected slot
 * at 0x102cbc0 + index * 0x8c reports a state. The object table at 0x777d14
 * (stride 0x18) is refreshed for every entry whose stored handle no longer
 * matches the live handle, and the frame is re-run while 0x5373e0 accepts
 * this function.
 */

int __cdecl fcn_0057ec20(int);
void __cdecl fcn_0057e880(int, int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_00533a60(int, int, int*, int, int, int, int);
int __cdecl fcn_005c8400(void);
int __cdecl fcn_005c86b0(void);
int __cdecl fcn_005c89a0(void);
int __cdecl d2_CreateRadioGroup(int, int, int, int);
void __cdecl fcn_004695a0(int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_005a5440(int, char*, int, int, int);
void __cdecl fcn_00471a30(int, int);
void __cdecl fcn_005c8770(int);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_0046ed00(int, int, int);
int __cdecl fcn_00471f80(int, ...);
int __cdecl fcn_0050b750(int);
void __cdecl fcn_004c4510(int, int);
void __cdecl fcn_004c4570(int, int, int, int*);
void __cdecl fcn_004c4670(int, int, int, int*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_0050dc90(int);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005c8c40 */
void __cdecl fcn_005c8c40(void)
{
	int out[3];
	int idx;
	int ofs;
	int save;
	int v2;
	int v3;
	int v4;
	int i;
	int n;
	int h;
	int cur;
	int obj;
	int q;
	int t1;
	int t2;
	int delta;
	int state;

	if (fcn_0057ec20(0x800) == 0) {
		return;
	}
	fcn_0057e880(0x13, 0, 0, 0);
	save = fcn_00470820(0, 0, (char*) 0x6ac890);
	fcn_00471b60(save);
	d2_SetForm(save, 0);
	fcn_005340f0(*(int*) 0x772514);
	d2_SetForm(save, 3);
	fcn_00533a60(*(int*) 0x772514, 0, out, 3, *(int*) 0x14b5294, *(int*) 0x14b5298, *(int*) 0x14b529c);
	v2 = fcn_005c8400();
	v3 = fcn_005c86b0();
	v4 = fcn_005c89a0();
	idx = d2_CreateRadioGroup(3, out[0], out[1], out[2]);
	ofs = idx * 0x8c;
	*(int*) (ofs + 0x102cbc0) = *(int*) (ofs + 0x102cbc0) | 1;
	fcn_004695a0(idx, *(int*) 0x77533c);
	if (v4 == -1) {
		fcn_00472640(out[2], 0);
	}
	for (;;) {
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		}
		state = *(int*) (ofs + 0x102cbc8);
		if (state == 0) {
			fcn_00471af0(v2, 1);
			fcn_00471af0(v3, 0);
			fcn_00471af0(v4, 0);
		} else if (state == 1) {
			fcn_00471af0(v3, 1);
			fcn_00471af0(v2, 0);
			fcn_00471af0(v4, 0);
		} else if (state == 2) {
			fcn_00471af0(v4, 1);
			fcn_00471af0(v3, 0);
			fcn_00471af0(v2, 0);
		}
		if (v2 != -1) {
			d2_SetForm(v2, 1);
			fcn_005a5440(*(int*) (0x7f4e18 + (*(unsigned short*) 0x774970) * 0x21c), (char*) 0x776aa0, v2, 1, 0);
		}
		if (v3 != -1 && *(int*) 0x100f1dc != -1 && *(int*) 0x775338 > 0) {
			for (i = 0; i < *(int*) 0x775338; i++) {
				if (*(int*) 0x67d370 == *(int*) (0x778900 + i * 4)) {
					fcn_00471a30(save, 0);
					fcn_005c8770(*(int*) (*(int*) 0x1015ea0 + 0x2f0 + (*(int*) 0x67d370) * 0x2f4));
					fcn_00471a30(save, 1);
					break;
				}
			}
		}
		if (v4 != -1) {
			d2_SetForm(v4, 0);
			if (*(int*) 0x100f1dc != -1) {
				t1 = fcn_00472830(v4, 3);
				t2 = fcn_00472830(v4, 2);
				if (*(int*) 0x67d370 == *(int*) 0x776c90) {
					fcn_0046ed00(0, 0x3e, t1);
					fcn_0046ed00(0, 0x3e, t2);
				} else if (*(int*) 0x67d370 == *(int*) 0x777ca0) {
					fcn_0046ed00(0, -0x3e, t1);
					fcn_0046ed00(0, -0x3e, t2);
				}
			}
			i = 0x777d14;
			while (i < 0x778914) {
				h = *(int*) (i - 0x10);
				if (h != -1) {
					cur = fcn_00471f80(h);
					if (*(int*) (i - 4) != cur) {
						cur = fcn_00471f80(*(int*) (i - 0x10), *(unsigned char*) 0x773d75);
						n = fcn_0050b750(cur);
						obj = *(int*) i;
						fcn_004c4510(obj, *(int*) (obj + 1));
						delta = (int) (*(unsigned short*) i) - (int) (*(unsigned short*) 0xaed32c) + 0x39;
						fcn_004c4570(4, 1, delta, &n);
						fcn_004c5360();
						q = fcn_0050dc90(*(int*) i);
						n = n - *(int*) (*(int*) i + 0x39);
						fcn_004c4510(q, *(int*) (q + 4));
						fcn_004c4670(4, 1, (q - *(int*) 0xaed32c) + 0x1b8, &n);
						fcn_004c5360();
						*(int*) (i - 4) = fcn_00471f80(*(int*) (i - 0x10));
					}
				}
				i += 0x18;
			}
		}
		if (fcn_005373e0(0x5c8c40, 0x657c7) != 0) {
			continue;
		}
		*(int*) 0x77533c = *(int*) (ofs + 0x102cbc8);
		fcn_00469510(idx);
		fcn_00471e30(save);
		if (v2 != -1) {
			fcn_00471e30(v2);
		}
		if (v3 != -1) {
			fcn_00471e30(v3);
		}
		if (v4 != -1) {
			fcn_00471e30(v4);
		}
		fcn_0057e880(0x13, 0, 0, 0);
		return;
	}
}
