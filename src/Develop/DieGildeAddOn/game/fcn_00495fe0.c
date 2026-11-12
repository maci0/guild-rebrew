typedef struct {
	unsigned int x;
	unsigned short y;
} Sel495fe0;

typedef struct {
	unsigned char mode;
	unsigned char pad0[3];
	int f1;
	int f2;
	int f3;
	int f4;
	int f5;
} Out495fe0;

int __cdecl fcn_00495400(int a, int b, int c, Out495fe0* a4, Out495fe0* a5);
int* __cdecl fcn_00506d50(Sel495fe0* out, int id);
int __cdecl fcn_005463a0(int a, ...);
int __cdecl fcn_0042e410(unsigned short a);
int __cdecl fcn_004fbd20(int a);
int __cdecl fcn_004fa5b0(int a, char* obj, int* frame);
extern float g_662a94; extern float g_6628a8; extern float g_66413c;
int __cdecl fcn_00502cd0(int a, int b, int c, int d);

/* ADDRESS: GOLDTL 0x00495fe0 */
int __cdecl fcn_00495fe0(int a0, char* obj, int flag, int* out1, int* out2)
{
	union { Out495fe0 msg; float ratios[5]; } action;
	Sel495fe0 sel; Sel495fe0 attributes; union { Out495fe0 msg; unsigned int values[5]; } extra;
	int marks[5];

	int cands[5];
	int frame[0x88];
	int loop;
	int best1;
	unsigned int costs[5];
	int maxIdx;

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

	maxIdx = 0;

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
		action.msg.mode = 0xe;
		action.msg.f1 = 0;
		action.msg.f2 = 0;


		extra.msg.mode = 0;
		extra.msg.f1 = 0;
		extra.msg.f2 = 0;
		r = fcn_00495400(5, *(unsigned short*) obj, 0, &action.msg, &extra.msg);
		if (r == 0) {
			return r;
		}
		goto tail;
	}

	pi = fcn_00506d50(&sel, tmp8);
	attributes.x = pi[0];
	attributes.y = *(unsigned short*) (pi + 1);
	if (*(int*) (obj + 0x170) == 0 && obj[2] != 3) {
		action.msg.mode = 0;
		action.msg.f1 = 0;
		action.msg.f2 = 0;
		action.msg.f5 = 0x3f28f5c3;

		extra.msg.mode = 0;
		extra.msg.f1 = 0;
		extra.msg.f2 = 0;
		r = fcn_00495400(4, *(unsigned short*) obj, 1, &action.msg, &extra.msg);
		if (r == 0) {
			return r;
		}
		goto tail;
	}
	r = fcn_005463a0(2, 2, *(unsigned short*) obj, 0, 0x60);
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
		pct = ((unsigned char*) &attributes.x)[loop];
		frame[0] = 1;
		if (best1 < (int) pct) {
			if (best1 > 0) {
				maxIdx = best1;
				idx2 = idx1;
			}
			idx1 = loop; best1 = (int) pct;
		} else if (maxIdx < (int) pct) {
			idx2 = loop;
			maxIdx = (int) pct;
		}
		marks[loop] = 1;
		extra.values[loop] = fcn_004fbd20(loop) & 0xff;
		if ((extra.values[loop] & 0xff) == 0) {
			extra.values[loop] = 0xfc;
		}
		r = fcn_004fa5b0(cands[loop], obj, frame);
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
		costs[loop] = (unsigned int) (int) ((double) (unsigned int) kind + ((r & 2) ? g_662a94 : g_6628a8));
		if (*(unsigned int*) (obj + 0x194) < costs[loop]) {
			marks[loop] = 0;
		} else if ((float) tmp8 != g_66413c) {
			
			action.ratios[loop] = (float) ((double) tmp8 / (double) (unsigned int) extra.values[loop]);
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
				kind = (idx1 == 3) ? 0x17 : 0x14;
			}
			r = fcn_00502cd0(*(int*) (*(int*) (obj + 0x170) + 0x5d), 1, 0, kind);
			if (r == 0) {
				action.msg.mode = 2;
				action.msg.f1 = kind;
				action.msg.f2 = 1;
				action.msg.f5 = 0x3ee147ae;

				extra.msg.mode = 4;
				extra.msg.f1 = *(int*) (*(int*) (obj + 0x170) + 1);
				extra.msg.f2 = 1;
				r = fcn_00495400(5, *(unsigned short*) obj, 1, &action.msg, &extra.msg);
				goto tail;
			}
		}
		*(unsigned char*) out1 = 0xe;
		out1[1] = idx1;
		out1[4] = costs[idx1];
		return 5;
	}
	action.msg.mode = 0xf;
	action.msg.f1 = 0;
	action.msg.f2 = 0;


	extra.msg.mode = 0;
	extra.msg.f1 = 0;
	extra.msg.f2 = 0;
	r = fcn_00495400(5, *(unsigned short*) obj, 0, &action.msg, &extra.msg);
tail:
	if (r == 0) {
		return r;
	}
	for (i = 0; i < 6; i++) {
		out1[i] = ((int*) &action.msg)[i];
	}
	for (i = 0; i < 6; i++) {
		out2[i] = ((int*) &extra.msg)[i];
	}
	return r;
}
