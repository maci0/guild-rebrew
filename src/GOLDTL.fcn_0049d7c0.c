// FUNCTION: GOLDTL 0x49d7c0
// SIZE: 341

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

typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);
int __cdecl fcn_005015e0(char**, char**, char**, int);
int __cdecl fcn_004a4fb0(int* a, int* b, char* q, int c);
int __cdecl fcn_00495400(int kind, int id, int n, Blk24* b1, Blk24* b2);

int __cdecl fcn_0049d7c0(int a1, char* e, int a3, Blk24* o1, Blk24* o2)
{
	int v[2];
	Blk24 b2;
	Blk24 b1;
	int found;
	char* q;
	int tries;
	int r;
	F8 f;

	if (a3 != 0 || e[0x166] != 0xf || o1->kind != 0) {
		return 0;
	}
	if (a1 != 0 && e[0x130] != 6 && e[0x130] != 9) {
		return 0;
	}
	tries = 4;
	f.mask = 2;
	f.b = 0;
	do {
		if (fcn_004a5e60(e, 2, f, 0, 100.0f, &found) != 0) {
			fcn_005015e0(&q, 0, 0, found);
			if (q != 0 && fcn_004a4fb0(&v[0], &v[1], q, 0) != 0) {
				b1.kind = 2;
				b1.a = v[0];
				b1.b = 1;
				if (v[1] != -1) {
					b2.kind = 1;
					b2.a = v[1];
				} else {
					b2.kind = 4;
					b2.a = *(int*) (q + 1);
				}
				b2.b = 1;
				b2.f = 0.44f;
				r = fcn_00495400(0x15, *(unsigned short*) e, 1, &b1, &b2);
				if (r != 0) {
					*o1 = b1;
					*o2 = b2;
					return r;
				}
			}
		}
	} while (--tries);
	return 0;
}
