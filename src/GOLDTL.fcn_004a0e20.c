

typedef struct Blk24 {
	unsigned char kind;
	char pad1[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Blk24;
// SIZE 0x18

typedef struct Share {
	int amount;
	int kind;
	int goal;
} Share;
// SIZE 0xc

typedef struct Rec6 {
	unsigned char c[6];
} Rec6;
// SIZE 0x6

#define MAXV(a, b) (((a) > (b)) ? (a) : (b))

extern unsigned char g_773d75;

unsigned char* __cdecl fcn_00508e40(int id);
int __cdecl fcn_0047d220(unsigned char* p);
void __cdecl fcn_004942a0(char* e, Share* out);
Rec6 __cdecl fcn_00506d50(int idx);
unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_0050d320(char* e, unsigned char b);

/* r[] is block-scoped so it shares the slot of the Rec6 return temporary.
 * `p[8] > 0` on the unsigned byte gives the reference's jbe. */
int __cdecl fcn_004a0e20(int a1, char* e, int a3, Blk24* o1, Blk24* o2)
{
	Share sh[3];
	Rec6 s;
	unsigned char* p;
	unsigned char* best;
	int i;
	int k;

	if (a3 != 0) {
		return 0;
	}
	if (a1 != 0) {
		return 0;
	}
	if (e[2] != 5) {
		p = fcn_00508e40(*(int*) (e + 0x5c));
		if (p != 0) {
			if (p[2] == 5 || p[2] == 6 || p[2] == 7) {
				return 0;
			}
			if (p[9] == 0 && fcn_0047d220(p) != 0) {
				return 0;
			}
		}
	}
	best = 0;
	for (i = 0; i < 5; i++) {
		p = fcn_00508e40(((int*) (e + 0x68))[i]);
		if (p != 0 && p[8] > 0 && p[0x164] != 0 && !(*(int*) (p + 0x1c8) & 0x10000)) {
			if (best == 0 || *(unsigned short*) (p + 0xa) > *(unsigned short*) (best + 0xa)) {
				best = p;
			}
		}
	}
	if (best == 0) {
		return 0;
	}
	fcn_004942a0(e, sh);
	s = fcn_00506d50(best[0x164]);
	{
		float r[3];

		for (i = 0; i < 3; i++) {
			r[i] = best[0x80 + sh[i].kind] / MAXV((float) s.c[sh[i].kind], 1.0f) + best[0x80 + sh[i].goal] / MAXV((float) s.c[sh[i].goal], 1.0f);
		}
		if (gm_RandomMod(2) != 0) {
			k = r[0] > r[1] ? 0 : 1;
			if (!(r[k] > r[2])) {
				k = 2;
			}
		} else {
			k = r[0] < r[1] ? 0 : 1;
			if (!(r[k] < r[2])) {
				k = 2;
			}
		}
	}
	if (fcn_0050d320(e, g_773d75) < sh[k].amount * 10) {
		return 0;
	}
	o1->kind = 7;
	o1->a = *(int*) (best + 4);
	o1->d = sh[k].amount;
	o2->kind = 0xe;
	o2->a = sh[k].kind;
	o2->d = sh[k].goal;
	return 0x3b;
}
