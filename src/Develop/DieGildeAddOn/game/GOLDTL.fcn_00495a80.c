extern float g_662a94; /* -1.0f */
extern float g_66413c; /* 252.0f */

typedef struct {
	unsigned char mode;
	unsigned char pad0[3];
	int f1;
	int f2;
	int f3;
	int f4;
	int f5;
} Out495a80;

int __cdecl fcn_00495400(int, int, int, Out495a80*, Out495a80*);
int __cdecl fcn_004fa5b0(int, char*, int*);
int __cdecl fcn_004f97a0(int); /* 0x4fbd20, metadata name is stale */
int __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl fcn_005463a0(int, int, int, int, int);
unsigned short __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x00495a80 */
int __cdecl fcn_00495a80(int a0, char* a1, int a2, char* a3, char* a4)
{
	int left;
	int i;
	int k;
	int r;
	int keep[5];
	int used[5];
	unsigned int weight[5];
	int buf[0x88];
	union { Out495a80 msg; float ratios[5]; } extra;
	union { Out495a80 msg; unsigned int count[5]; } action;

	(void) a0;
	left = 5;
	keep[0] = 0x3a;
	keep[1] = 0x1a;
	keep[2] = 0x17;
	keep[3] = 0x18;
	keep[4] = 0x19;
	if (a2 != 0) {
		return 0;
	}
	if (*(int*) (a1 + 0x170) == 0 && *(char*) (a1 + 2) != 3) {
		extra.msg.mode = 0;
		extra.msg.f1 = 0;
		extra.msg.f2 = 0;
		extra.msg.f5 = 0x3f28f5c3;
		action.msg.mode = 0;
		action.msg.f1 = 0;
		action.msg.f2 = 0;
		r = fcn_00495400(4, *(unsigned short*) a1, 1, &extra.msg, &action.msg);
		if (r != 0) {
			*(Out495a80*) a3 = extra.msg;
			*(Out495a80*) a4 = action.msg;
		}
		return r;
	}
	if (fcn_005463a0(2, 2, *(unsigned short*) a1, 0, 0x60) != 0) {
		return 0;
	}
	if (*(char*) a3 == 0x0e) {
		int slot;
		float f;

		i = *(int*) (a3 + 4);
		for (k = 0; k < 0x88; k++) {
			buf[k] = 0;
		}
		buf[0] = 1;
		r = fcn_004fa5b0(keep[i], a1, buf);
		f = (r & 2) ? g_662a94 : 0.0f;
		if (*(unsigned char*) (a1 + i + 0x80) < 0x2a) {
			slot = 1;
		} else if (*(unsigned char*) (a1 + i + 0x80) < 0x54) {
			slot = 2;
		} else if (*(unsigned char*) (a1 + i + 0x80) < 0x7e) {
			slot = 4;
		} else if (*(unsigned char*) (a1 + i + 0x80) < 0xa8) {
			slot = 6;
		} else if (*(unsigned char*) (a1 + i + 0x80) < 0xd2) {
			slot = 9;
		} else {
			slot = 12;
		}
		/* native: fild; fadd; call _ftol (0x64d228) */
		slot = (int) ((float) slot + f);
		if (slot < *(int*) (a1 + 0x194)) {
			return 0;
		}
		if ((float) *(unsigned char*) (a1 + i + 0x80) == g_66413c) {
			return 0;
		}
		*(int*) (a3 + 0x10) = slot;
		return 4;
	}
	for (i = 0; (unsigned int) i < 5; i++) {
		float f;

		for (k = 0; k < 0x88; k++) {
			buf[k] = 0;
		}
		buf[0] = 1;
		used[i] = 1;
		action.count[i] = fcn_004f97a0(i) & 0xff;
		if (action.count[i] == 0) {
			action.count[i] = 0xfc;
		}
		r = fcn_004fa5b0(keep[i], a1, buf);
		f = (r & 2) ? g_662a94 : 0.0f;
		if (*(unsigned char*) (a1 + 0x80 + i) < 0x2a) {
			weight[i] = 1;
		} else if (*(unsigned char*) (a1 + 0x80 + i) < 0x54) {
			weight[i] = 2;
		} else if (*(unsigned char*) (a1 + 0x80 + i) < 0x7e) {
			weight[i] = 4;
		} else if (*(unsigned char*) (a1 + 0x80 + i) < 0xa8) {
			weight[i] = 6;
		} else if (*(unsigned char*) (a1 + 0x80 + i) < 0xd2) {
			weight[i] = 9;
		} else {
			weight[i] = 12;
		}
		/* native: fild qword; fadd; call _ftol (0x64d228) */
		weight[i] = (unsigned int) ((float) weight[i] + f);
		if (weight[i] > *(unsigned int*) (a1 + 0x194)) {
			used[i] = 0;
			left--;
		} else if ((float) *(unsigned char*) (a1 + 0x80 + i) == g_66413c) {
			used[i] = 0;
			left--;
		} else {
			extra.ratios[i] = (float) *(unsigned char*) (a1 + 0x80 + i) / (float) action.count[i];
		}
	}
	if (left == 0) {
		return 0;
	}
	i = (unsigned short) gm_RandomMod(5);
	while (used[i] == 0) {
		i = (i + 1) % 5;
	}
	if (*(char*) (a1 + 2) == 3) {
		if (i == 4) {
			if ((*(unsigned char*) (a1 + 0x1e8) & 4) == 0) {
				return 0;
			}
		} else if (i == 3) {
			if ((*(unsigned char*) (a1 + 0x1e8) & 8) == 0) {
				return 0;
			}
		} else if (i == 2) {
			if ((*(unsigned char*) (a1 + 0x1e8) & 2) == 0) {
				return 0;
			}
		}
		goto fill;
	}
	if (i > 1) {
		int slot;

		if (i == 4) {
			slot = 0x15;
		} else {
			slot = (i == 3) ? 0x17 : 0x14;
		}
		if (fcn_00502cd0(*(int*) (*(char**) (a1 + 0x170) + 0x5d), 1, 0, slot) == 0) {
			extra.msg.mode = 2;
			extra.msg.f1 = slot;
			extra.msg.f2 = 1;
			extra.msg.f5 = 0x3ee147ae;
			action.msg.mode = 4;
			action.msg.f1 = *(int*) (*(char**) (a1 + 0x170) + 1);
			action.msg.f2 = 1;
			r = fcn_00495400(4, *(unsigned short*) a1, 1, &extra.msg, &action.msg);
			if (r != 0) {
				*(Out495a80*) a3 = extra.msg;
				*(Out495a80*) a4 = action.msg;
			}
			return r;
		}
	}
fill:
	*(unsigned char*) a3 = 0x0e;
	*(int*) (a3 + 4) = i;
	*(int*) (a3 + 0x10) = (int) weight[i];
	return 4;
}
