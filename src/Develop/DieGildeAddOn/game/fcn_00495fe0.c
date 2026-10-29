typedef struct {
	int f0;
	int f1;
	int x;
	unsigned short y;
	unsigned short pad;
} Sel495fe0;

typedef struct {
	unsigned char mode;
	unsigned char pad0[3];
	int f1;
	int f2;
	int f3;
	int f4;
} Out495fe0;

int __cdecl fcn_00495400(int a, int b, int c, Out495fe0* a4, Sel495fe0* a5, int x);
int* __cdecl fcn_00506d50(Sel495fe0* out, int id);
int __cdecl fcn_005463a0(int a);
unsigned short __cdecl fcn_0042e410(int a);
int __cdecl fcn_004fbd20(int a);
void __cdecl fcn_004fa5b0(int a, char* obj, int* frame);
int __cdecl fcn_0064d228();
int __cdecl fcn_00502cd0(int a, int b, int c, int d);

/* ADDRESS: GOLDTL 0x00495fe0 */
int __cdecl fcn_00495fe0(int a0, char* obj, int flag, int* out1, int* out2)
{
	Out495fe0 o1;
	Sel495fe0 sel;
	int marks[5];
	int vals[5];
	int cands[5];
	int frame[0x88];
	int loop;
	int best1;
	int best2;
	int maxIdx;
	int maxVal;
	int idx1;
	int idx2;
	int kind;
	int i;
	int r;
	int n;
	unsigned short w1;
	unsigned short w2;
	unsigned char pct;
	unsigned char tmp8;
	int* pi;

	(void) a0;
	best1 = 0;
	best2 = 0;
	maxIdx = 0;
	maxVal = 0;
	cands[0] = 0x3a;
	cands[1] = 0x1a;
	cands[2] = 0x17;
	cands[3] = 0x18;
	cands[4] = 0x19;
	if (flag != 0) {
		return 0;
	}
	tmp8 = (unsigned char) obj[0x164];
	if (tmp8 == 0) {
		o1.mode = 0xe;
		o1.f1 = 0;
		o1.f2 = 0;
		o1.f3 = 0;
		o1.f4 = 0;
		out2[0] = 0;
		out2[1] = 0;
		out2[2] = 0;
		r = fcn_00495400(5, *(unsigned short*) obj, 0, &o1, &sel, 0);
		if (r == 0) {
			return r;
		}
		goto tail;
	}
	sel.f0 = 0;
	sel.f1 = 0;
	sel.x = 0;
	sel.y = 0;
	pi = fcn_00506d50(&sel, tmp8);
	sel.x = pi[0];
	sel.y = *(unsigned short*) (pi + 1);
	if (*(int*) (obj + 0x170) == 0 && obj[2] != 3) {
		o1.mode = 0;
		o1.f1 = 0;
		o1.f2 = 0;
		o1.f3 = 0x3f28f5c3;
		o1.f4 = 0;
		out2[0] = 0;
		out2[1] = 0;
		out2[2] = 0;
		r = fcn_00495400(4, *(unsigned short*) obj, 1, &o1, &sel, 0);
		if (r == 0) {
			return r;
		}
		goto tail;
	}
	r = fcn_005463a0(2);
	if (r != 0) {
		return 0;
	}
	w1 = fcn_0042e410(5);
	w2 = fcn_0042e410(5);
	idx1 = (int) w1;
	idx2 = (int) w2;
	loop = 0;
	do {
		for (i = 0; i < 0x88; i++) {
			frame[i] = 0;
		}
		pct = ((unsigned char*) &sel.x)[loop];
		frame[0] = 1;
		if (best1 < (int) pct) {
			if (best1 > 0) {
				maxIdx = best1;
				idx2 = idx1;
			}
			best1 = (int) pct;
		} else if (maxIdx < (int) pct) {
			idx2 = loop;
			maxIdx = (int) pct;
		}
		marks[loop] = 1;
		vals[loop] = fcn_004fbd20(loop) & 0xff;
		if ((vals[loop] & 0xff) == 0) {
			vals[loop] = 0xfc;
		}
		fcn_004fa5b0(cands[loop], obj, frame);
		tmp8 = (unsigned char) obj[loop + 0x80];
		if (tmp8 < 0x2a) {
			kind = 1;
		} else if (tmp8 < 0x54) {
			kind = 2;
		} else if (tmp8 < 0x7e) {
			kind = 4;
		} else if (tmp8 < 0xa8) {
			kind = 6;
		} else if (tmp8 < 0xd2) {
			kind = 9;
		} else {
			kind = 0xc;
		}
		out2[0] = 0;
		out2[1] = 0;
		out2[2] = 0;
		vals[loop] = fcn_0064d228();
		if (*(unsigned int*) (obj + 0x194) < (unsigned int) vals[loop]) {
			marks[loop] = 0;
		} else if ((float) tmp8 != 0.0f) {
			out2[1] = vals[loop];
			marks[loop] = (int) ((float) tmp8 / (float) vals[loop]);
		} else {
			marks[loop] = 0;
		}
		loop++;
	} while (loop < 5);
	i = marks[idx2] + marks[idx1];
	if (i != 0) {
		if (i == 2) {
			r = fcn_0042e410(2) == 0;
		} else {
			r = marks[idx1] == 0;
		}
		if (r) {
			idx1 = idx2;
		}
		if (obj[2] == 3) {
			if (idx1 == 4) {
				if ((obj[0x1e8] & 4) == 0) {
					return 0;
				}
			} else if (idx1 == 3) {
				if ((obj[0x1e8] & 8) == 0) {
					return 0;
				}
			} else if (idx1 == 2 && (obj[0x1e8] & 2) == 0) {
				return 0;
			}
		} else if (1 < idx1) {
			if (idx1 == 4) {
				kind = 0x15;
			} else {
				kind = (idx1 == 3) ? 0x17 : 0x1a;
			}
			r = fcn_00502cd0(*(int*) (*(int*) (obj + 0x170) + 0x5d), 1, 0, kind);
			if (r == 0) {
				o1.mode = 2;
				o1.f1 = kind;
				o1.f2 = 1;
				o1.f3 = 0x3ee147ae;
				o1.f4 = 0;
				out2[0] = 4;
				out2[1] = *(int*) (*(int*) (obj + 0x170) + 1);
				out2[2] = 1;
				r = fcn_00495400(5, *(unsigned short*) obj, 1, &o1, &sel, 0);
				goto tail;
			}
		}
		*(unsigned char*) out1 = 0xe;
		out1[1] = idx1;
		out1[4] = vals[idx1];
		return 5;
	}
	o1.mode = 0xf;
	o1.f1 = 0;
	o1.f2 = 0;
	o1.f3 = 0;
	o1.f4 = 0;
	out2[0] = 0;
	out2[1] = 0;
	out2[2] = 0;
	r = fcn_00495400(5, *(unsigned short*) obj, 0, &o1, &sel, 0);
tail:
	if (r == 0) {
		return r;
	}
	for (i = 0; i < 6; i++) {
		out1[i] = ((int*) &o1)[i];
	}
	return r;
}
