extern float g_662a94; /* -1.0f */
extern float g_6628a8; /* 0.0f */
extern float g_66413c; /* 252.0f */

int __cdecl fcn_00495400(int, unsigned short, int, void*, void*);
int __cdecl fcn_004fa5b0(int, char*, int*);
int __cdecl fcn_004f97a0(int); /* 0x4fbd20, metadata name is stale */
int __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl fcn_005463a0(int, int, unsigned short, int, int);
int __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x00495a80 */
int __cdecl fcn_00495a80(int a0, char* a1, int a2, char* a3, char* a4)
{
	int left;
	int i;
	int k;
	int r;
	int slot;
	int b;
	int idx;
	int keep[5];
	int used[5];
	unsigned int count[5];
	unsigned int weight[5];
	int buf[0x88];
	char msg0[0x18];
	char msg1[0x18];
	float* ratio;
	char* ptr;

	left = 5;
	keep[0] = 0x3a;
	keep[1] = 0x1a;
	keep[2] = 0x17;
	keep[3] = 0x18;
	keep[4] = 0x19;
	r = 0;
	if (a2 != 0) {
		return 0;
	}
	/* uncertain: native overlays the ratio array with msg0 (stack 0x18..0x2b) */
	ratio = (float*) msg0;
	if (*(int*) (a1 + 0x170) == 0 && *(char*) (a1 + 2) != 3) {
		*(char*) (msg0) = 0;
		*(int*) (msg0 + 4) = 0;
		*(int*) (msg0 + 8) = 0;
		*(int*) (msg0 + 0x14) = 0x3f28f5c3;
		*(char*) (msg1) = 0;
		*(int*) (msg1 + 4) = 0;
		*(int*) (msg1 + 8) = 0;
		r = fcn_00495400(4, *(unsigned short*) a1, 1, msg0, msg1);
		goto copy_out;
	}
	if (fcn_005463a0(2, 2, *(unsigned short*) a1, 0, 0x60) != 0) {
		return 0;
	}
	if (*(char*) a3 == 0x0e) {
		i = *(int*) (a3 + 4);
		for (k = 0; k < 0x88; k++) {
			buf[k] = 0;
		}
		buf[0] = 1;
		r = fcn_004fa5b0(keep[i], a1, buf);
		b = *(unsigned char*) (a1 + i + 0x80);
		if (b < 0x2a) {
			slot = 1;
		} else if (b < 0x54) {
			slot = 2;
		} else if (b < 0x7e) {
			slot = 4;
		} else if (b < 0xa8) {
			slot = 6;
		} else if (b < 0xd2) {
			slot = 9;
		} else {
			slot = 12;
		}
		{
			float f;

			if ((r & 2) != 0) {
				f = g_662a94;
			} else {
				f = g_6628a8;
			}
			/* native: fild; fadd; call _ftol (0x64d228) */
			slot = (int) ((float) slot + f);
		}
		if (slot < *(int*) (a1 + 0x194)) {
			return 0;
		}
		if (!((float) b > g_66413c)) {
			return 0;
		}
		*(int*) (a3 + 0x10) = slot;
		return 4;
	}
	for (i = 0; i < 5; i++) {
		float f;

		for (k = 0; k < 0x88; k++) {
			buf[k] = 0;
		}
		buf[0] = 1;
		used[i] = 1;
		count[i] = fcn_004f97a0(i) & 0xff;
		if (count[i] == 0) {
			count[i] = 0xfc;
		}
		r = fcn_004fa5b0(keep[i], a1, buf);
		if ((r & 2) != 0) {
			f = g_662a94;
		} else {
			f = g_6628a8;
		}
		b = *(unsigned char*) (a1 + 0x80 + i);
		if (b < 0x2a) {
			weight[i] = 1;
		} else if (b < 0x54) {
			weight[i] = 2;
		} else if (b < 0x7e) {
			weight[i] = 4;
		} else if (b < 0xa8) {
			weight[i] = 6;
		} else if (b < 0xd2) {
			weight[i] = 9;
		} else {
			weight[i] = 12;
		}
		/* native: fild qword; fadd; call _ftol (0x64d228) */
		weight[i] = (unsigned int) ((float) weight[i] + f);
		if (weight[i] > *(unsigned int*) (a1 + 0x194)) {
			used[i] = 0;
			left--;
		} else if ((float) b > g_66413c) {
			ratio[i] = (float) b / (float) count[i];
		} else {
			used[i] = 0;
			left--;
		}
	}
	if (left == 0) {
		return 0;
	}
	idx = gm_RandomMod(5) & 0xffff;
	while (used[idx] == 0) {
		idx = (idx + 1) % 5;
	}
	if (*(char*) (a1 + 2) == 3) {
		if (idx == 4) {
			if ((*(unsigned char*) (a1 + 0x1e8) & 4) == 0) {
				return 0;
			}
		} else if (idx == 3) {
			if ((*(unsigned char*) (a1 + 0x1e8) & 8) == 0) {
				return 0;
			}
		} else if (idx == 2) {
			if ((*(unsigned char*) (a1 + 0x1e8) & 2) == 0) {
				return 0;
			}
		}
		goto fill;
	}
	if (idx <= 1) {
		goto fill;
	}
	if (idx == 4) {
		slot = 0x15;
	} else if (idx == 2) {
		slot = 0x14;
	} else {
		slot = 0x17;
	}
	ptr = *(char**) (a1 + 0x170);
	if (fcn_00502cd0(*(int*) (ptr + 0x5d), 1, 0, slot) != 0) {
		goto fill;
	}
	*(char*) (msg0) = 2;
	*(int*) (msg0 + 4) = slot;
	*(int*) (msg0 + 8) = 1;
	*(int*) (msg0 + 0x14) = 0x3ee147ae;
	*(char*) (msg1) = 4;
	*(int*) (msg1 + 4) = *(int*) (ptr + 1);
	*(int*) (msg1 + 8) = 1;
	r = fcn_00495400(4, *(unsigned short*) a1, 1, msg0, msg1);
copy_out:
	if (r == 0) {
		return 0;
	}
	for (k = 0; k < 6; k++) {
		*(int*) (a3 + k * 4) = *(int*) (msg0 + k * 4);
	}
	for (k = 0; k < 6; k++) {
		*(int*) (a4 + k * 4) = *(int*) (msg1 + k * 4);
	}
	return r;
fill:
	*(char*) a3 = 0x0e;
	*(int*) (a3 + 4) = idx;
	*(int*) (a3 + 0x10) = (int) weight[idx];
	return 4;
}
