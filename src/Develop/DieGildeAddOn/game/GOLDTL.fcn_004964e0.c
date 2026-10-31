typedef struct Share {
	unsigned char kind;
	char pad[3];
	float val;
} Share;

typedef struct Deal {
	char pad0[0x30];
	Share a[4];
	char pad50[0x20];
	Share b[4];
	unsigned char flags;
	char pad91[3];
} Deal;
/* SIZE 0x94 */

typedef struct Rate {
	float f;
	int x4;
	int x8;
} Rate;

typedef struct Actor {
	unsigned short w0;
	char pad2[2];
	int id4;
	char pad8[0x88];
	Rate rate[13];
	char pad12c[4];
	unsigned char kind;      /* 0x130 */
	char pad131[0x166 - 0x131];
	unsigned char kind166;   /* 0x166 */
	unsigned char f167;
	unsigned char f168;      /* 0x168 */
} Actor;

typedef struct Entry {
	char pad0[0xb0];
	int id;                  /* 0xb0 */
	int val;                 /* 0xb4 */
	int ref1;                /* 0xb8 */
	int ref2;                /* 0xbc */
} Entry;

extern char g_1008540[];
extern char* gm_RichterKatholisch;
extern char* gm_RichterEvangelisch;
extern char* g_77261c;

char* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl fcn_0050f980(int a, int b, int c);
char* __cdecl fcn_005463a0(int type, int a, int b);
char* __cdecl he_fn_Handlung(void);
int __cdecl fcn_004f4830(int idx, void* dst);
int __cdecl fcn_004a4410(float* a0, float* a1, int idx, Actor* e, int a4,
	char* a5, int a6);
int __cdecl fcn_004a4680(float* a0, float* a1, int idx, Actor* e, int* rec);

/* Prices the stored goods of the selected warehouse and reports the
   cheapest one as action type 7; otherwise falls back to the plain
   building-deal calculators. */
/* ADDRESS: GOLDTL 0x004964e0 */
int __cdecl fcn_004964e0(float* a0, float* a1, int idx, Actor* e, int a4,
	char* a5, int a6)
{
	Deal* t;
	Entry* p;
	char* sv[3];
	char* s;
	float fv[3];
	float best;
	int bi;
	int i;
	int v;
	int w;
	int rec[9];

	if (a4 != 0) {
		*a0 = -1e30f;
		*a1 = -1e30f;
		return 0;
	}
	*a0 = 0.0f;
	*a1 = 0.0f;
	t = (Deal*) (g_1008540 + idx * 0x94);
	if (e->f168 != 0) {
		goto calc;
	}
	if (e->kind166 != 0xd) {
		v = gm_RichterKatholisch != 0 ? *(int*) (gm_RichterKatholisch + 4) : -1;
		w = gm_RichterEvangelisch != 0 ? *(int*) (gm_RichterEvangelisch + 4) : -1;
		for (p = (Entry*) fcn_005463a0(1, 0, 0x2c); p != 0;
			p = (Entry*) he_fn_Handlung()) {
			if (p->id != e->id4) {
				continue;
			}
			if (p->val == v || p->val == w) {
				break;
			}
			fv[0] = 100.0f;
			fv[1] = 100.0f;
			fv[2] = 100.0f;
			sv[0] = gm_LookupEntityRecordById(p->val);
			sv[1] = gm_LookupEntityRecordById(p->ref1);
			sv[2] = gm_LookupEntityRecordById(p->ref2);
			if (sv[0] != 0 && sv[0] != g_77261c) {
				fv[0] = fcn_0050f980(e->w0, *(unsigned short*) sv[0], 1);
			}
			if (sv[1] != 0 && sv[1] != g_77261c) {
				fv[1] = fcn_0050f980(e->w0, *(unsigned short*) sv[1], 1);
			}
			if (sv[2] != 0 && sv[2] != g_77261c) {
				fv[2] = fcn_0050f980(e->w0, *(unsigned short*) sv[2], 1);
			}
			best = 100.0f;
			bi = -1;
			for (i = 0; i < 3; i++) {
				if (fv[i] < best) {
					best = fv[i];
					bi = i;
				}
			}
			if (bi != -1) {
				s = sv[bi];
				a5[0] = 7;
				*(int*) (a5 + 4) = *(int*) (s + 4);
				*(int*) (a5 + 8) = 1;
				goto calc;
			}
			goto fallback;
		}
	}
fallback:
	fcn_004f4830(0x10, rec);
	if (rec[6] == 0) {
		return fcn_004a4410(a0, a1, idx, e, 0, a5, a6);
	}
	return fcn_004a4680(a0, a1, idx, e, rec);
calc:
	for (i = 0; i < 4; i++) {
		if (t->a[i].val > *(float*) 0x6628a8) {
			if (t->a[i].kind == e->kind) {
				best = *(float*) 0x6628ac;
			} else {
				best = *(float*) 0x662910;
			}
			*a0 += e->rate[t->a[i].kind].f * t->a[i].val * best;
		}
		if (t->b[i].val > *(float*) 0x6628a8) {
			if (t->b[i].kind == e->kind) {
				best = *(float*) 0x6628ac;
			} else {
				best = *(float*) 0x662910;
			}
			*a1 += e->rate[t->b[i].kind].f * t->b[i].val * best;
		}
	}
	return 1;
}
