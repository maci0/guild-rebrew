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

extern float g_664368;
extern float g_66436c;
extern float g_6628d8;
extern unsigned char g_773d75;

int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);
int __cdecl gm_ResolveEntityById(void** out, int a, int b, int c);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0050b810(int a, unsigned char b);
int __cdecl fcn_004a4fb0(int* a, int* b, char* q, int c);
int __cdecl fcn_00495400(int kind, int id, int n, Blk24* b1, Blk24* b2);
float __cdecl fcn_004fc460(char* p);
unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_0050d170(int n);

/* ADDRESS: GOLDTL 0x0049d930 */
int __cdecl fcn_0049d930(int a1, char* e, char* q, Blk24* o1, Blk24* o2)
{
	int v0;
	int v1;
	int val;
	Blk24 b2;
	Blk24 b1;
	float buf[10];
	char* rec;
	int kind;
	int r;
	F8 f = {0x8000, 0};

	if (q != 0 || e[0x166] != 0xf || o1->kind != 0) {
		return 0;
	}
	if (a1 != 0 && e[0x130] != 7 && e[0x130] != 6) {
		return 0;
	}
	if (fcn_004a5e60(e, 2, f, 0, 100.0f, &a1) == 0) {
		return 0;
	}
	gm_ResolveEntityById((void**) &q, 0, 0, a1);
	if (q == 0) {
		return 0;
	}
	rec = (char*) fcn_00502cd0(*(int*) (q + 0x5d), 2, 6, 0, 0x115);
	val = fcn_0050b810(*(int*) (rec + 0x14), g_773d75);
	if (!(*(unsigned char*) (q + 0x5a) & 4)) {
		if (*(char*) (q + 0x5c) < gm_RandomMod(0x40) + 0x25) {
			b1.kind = 4;
			b1.a = *(int*) (q + 1);
			b1.b = 1;
			if (*(char*) (q + 0x5c) < 0x21) {
				b1.d = 50;
			} else {
				b1.d = *(char*) (q + 0x5c) < 0x42 ? 30 : 10;
			}
			b2.kind = 1;
			b2.a = *(int*) (rec + 2);
			b2.b = val;
			b2.d = 1;
			r = fcn_00495400(0xf, *(unsigned short*) e, 0, &b1, &b2);
			if (r != 0) {
				*o1 = b1;
				*o2 = b2;
				return r;
			}
		}
	}
	if (fcn_004a4fb0(&v0, &v1, q, 0) != 0) {
		b1.kind = 2;
		b1.a = v0;
		b1.b = 1;
		if (v1 != -1) {
			b2.kind = 1;
			b2.a = v1;
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
	if (!(*(unsigned char*) (q + 0x5a) & 0x41)) {
		fcn_004fc460((char*) buf);
	if (*(unsigned char*) q == 0x24) {
		kind = 0x25;
		if (gm_RandomMod(0x200) + buf[6] < 1250.0f) {
			return 0;
		}
	} else if (*(unsigned char*) q == 0x25) {
		kind = 0x26;
		if (gm_RandomMod(0x400) + buf[6] < 5000.0f) {
			return 0;
		}
	} else {
		return 0;
	}
		if (!((float) fcn_0050d170(kind) * 0.4f > (float) val)) {
			o1->kind = 4;
			o1->a = kind;
			o1->b = 1;
			o1->d = 0;
			o2->kind = 4;
			o2->a = *(int*) (q + 1);
			o2->b = 1;
			o2->d = 0;
			return 0x31;
		}
	}
	return 0;
}
