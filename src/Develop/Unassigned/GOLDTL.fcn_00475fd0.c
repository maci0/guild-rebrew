
// The len/count stores written once per arm; msvc6 merges the tails from
// the data store onward.

typedef struct Pair0475fd0 {
	int len;
	int data;
} Pair0475fd0;

typedef struct IfA0475fd0 IfA0475fd0;
typedef struct IfAVtbl0475fd0 {
	void* pad[0x10];
	int(__stdcall* Get)(IfA0475fd0* self, int a, Pair0475fd0* out, int b, int c);
} IfAVtbl0475fd0;
struct IfA0475fd0 {
	IfAVtbl0475fd0* vtbl;
};

typedef struct IfB0475fd0 IfB0475fd0;
typedef struct IfBVtbl0475fd0 {
	void* pad[9];
	int(__stdcall* Get)(IfB0475fd0* self, Pair0475fd0* out, int a, int b);
} IfBVtbl0475fd0;
struct IfB0475fd0 {
	IfBVtbl0475fd0* vtbl;
};

typedef struct S0475fd0 {
	char pad0[0xc];
	int len;
	int count;
	unsigned char bits;
	char pad15[7];
	int data;
	IfA0475fd0* a;
	IfB0475fd0* b;
	char pad28[0x3c - 0x28];
	int ready;
	char pad40[0x50 - 0x40];
	int open;
} S0475fd0;
// SIZE 0x54

int __cdecl fcn_00475fd0(S0475fd0* s)
{
	Pair0475fd0 p;

	if (s == 0 || s->open == 0) {
		return 0;
	}
	if (s->ready != 0) {
		return 1;
	}
	if (s->a != 0) {
		s->a->vtbl->Get(s->a, 0, &p, 0, 0);
		s->data = p.data;
		s->len = p.len;
		s->count = p.len / (s->bits >> 3);
	} else if (s->b != 0) {
		if (s->b->vtbl->Get(s->b, &p, 0, 0) < 0) {
			return 0;
		}
		s->data = p.data;
		s->len = p.len;
		s->count = p.len / (s->bits >> 3);
	}
	s->ready = 1;
	return 1;
}
