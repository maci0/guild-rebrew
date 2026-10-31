typedef struct Blk24 {
	unsigned char kind;
	char pad1[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Blk24;

typedef struct F8 {
	int mask;
	int b;
} F8;

int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);
int __cdecl fcn_004a4fb0(int* a, int* b, char* q, int c);
int __cdecl fcn_00495400(int kind, int id, int n, Blk24* b1, Blk24* b2);
void __cdecl gm_ResolveEntityById(void** out, int, int, int id);

extern float g_66417c;

/* ADDRESS: GOLDTL 0x00498e20 */
int __cdecl fcn_00498e20(int a1, char* e, int a3, Blk24* o1, Blk24* o2)
{
	Blk24 b2;
	Blk24 b1;
	int v0;
	int v1;
	int found;
	char* q;
	int r;
	F8 f;

	if (a1 != 0 || e[2] == 3) {
		return 0;
	}
	if (o1->kind != 0) {
		return 0;
	}
	f.mask = 0xa07d7bb0;
	f.b = 1;
	if (fcn_004a5e60(e, 4, f, 0, 100.0f, &found) == 0) {
		return 0;
	}
	gm_ResolveEntityById((void**) (&q), 0, 0, found);
	if (fcn_004a4fb0(&v0, &v1, q, 0) == 0) {
		return 0;
	}
	b1.kind = 2;
	b1.a = v0;
	b1.b = 1;
	b1.f = g_66417c;
	if (v1 != -1) {
		b2.kind = 1;
		b2.a = v1;
	} else {
		b2.kind = 4;
		b2.a = *(int*) (q + 1);
	}
	b2.b = 1;
	b2.f = g_66417c;
	r = fcn_00495400(0x15, *(unsigned short*) e, 1, &b1, &b2);
	if (r == 0) {
		return 0;
	}
	*o1 = b1;
	*o2 = b2;
	return r;
}
