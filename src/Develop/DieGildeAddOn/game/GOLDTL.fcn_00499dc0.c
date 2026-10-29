// SIZE 0x18
typedef struct {
	unsigned char valid;
	char pad1[3];
	int v[5];
} Pos;

// SIZE 0x10
typedef struct {
	int id;
	int a;
	int b;
	char* item;
} Slot;

// SIZE 0xc
typedef struct {
	int total;
	int blocked;
	int free;
} Counts;

// SIZE 0x8
typedef struct {
	int mask;
	int b;
} F8;

extern int g_7f4e0c[];

int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);
void __cdecl gm_ResolveEntityById(char** out, int a2, int a3, int a4);
void __cdecl fcn_004a51d0(char* e, int n, Slot* slots, Counts* cnt);
int __cdecl fcn_00495400(int kind, int id, int a3, Pos* b, Pos* a);
unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x00499dc0 */
int __cdecl fcn_00499dc0(int a1, char* e, int busy, Pos* out1, Pos* out2)
{
	Pos a;
	Pos b;
	Slot slot;
	Counts cnt;
	F8 f;
	char* p;
	int kind;
	int found;
	int count;
	int sum;
	int roll;
	int r;
	char* q;

	kind = a1;
	if (kind == 0) {
		kind = 0x1c;
	}
	if (busy != 0) {
		return 0;
	}
	if (a1 != 0) {
		return 0;
	}
	f.mask = 0x90010;
	f.b = 0;
	if (fcn_004a5e60(e, 4, f, 0, 100.0f, &found) == 0) {
		return 0;
	}
	gm_ResolveEntityById(&p, 0, 0, found);
	if (p == 0) {
		return 0;
	}
	count = 0;
	sum = 0;
	q = (char*) g_7f4e0c + 0x59;
	do {
		if (*(char**) (q - 0x59) == p) {
			count++;
			sum += *(unsigned char*) q;
		}
		q += 0x21c;
	} while (q < (char*) 0x85a265);
	roll = (unsigned short) gm_RandomMod(4);
	if ((float) roll + (float) sum / (float) count < 6.0f) {
		return 0;
	}
	slot.id = 0x161;
	slot.a = 0;
	slot.b = 0;
	slot.item = 0;
	fcn_004a51d0(e, 1, &slot, &cnt);
	if (cnt.total == 6 && cnt.free == 0) {
		return 0;
	}
	if (cnt.blocked == 1) {
		return 0;
	}
	if (cnt.total < 6 && cnt.free == 0) {
		a.valid = 2;
		a.v[0] = slot.id;
		a.v[1] = 1;
		a.v[4] = 0.05f;
		b.valid = 7;
		b.v[0] = *(int*) (e + 4);
		b.v[1] = 1;
		r = fcn_00495400(kind, *(unsigned short*) e, 2, &a, &b);
		if (r != 0) {
			*out1 = a;
			*out2 = b;
		}
		return r;
	}
	if (cnt.free == 0) {
		return 0;
	}
	a.valid = 1;
	a.v[0] = slot.b;
	a.v[1] = 1;
	b.valid = 4;
	b.v[0] = *(int*) (e + 1);
	b.v[1] = -1;
	b.v[3] = 0x1b;
	*out1 = a;
	*out2 = b;
	return 0x1b;
}
