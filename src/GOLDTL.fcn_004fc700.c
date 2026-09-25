// FUNCTION: GOLD 0x004fa060
// SIZE: 256
// FUNCTION: GOLDTL 0x004fc700
// SIZE: 256

// SIZE 0x24
typedef struct {
	char pad0[0x18];
	int amount;
	char pad1c[0x24 - 0x1c];
} Offer;

// SIZE 0x38
typedef struct {
	unsigned char used[6];
	char pad6[2];
	int value[6];
	int amount[6];
} Slots;

// SIZE 0x21c
typedef struct {
	char pad0[4];
	int owner;
	char pad8[0x19c - 8];
	int count;
	char pad1a0[0x21c - 0x1a0];
} Obj;

extern Obj g_7f4ca0[];
extern int g_773d48;
extern int g_99f724;

void __cdecl fcn_004f4830(int kind, Offer* o);
char* __cdecl fcn_0050e4a0(int n);
char* __cdecl fcn_00502cd0(int obj, int mode, ...);
void __cdecl fcn_004c51a0(int a, int b, int c, int d);

int __cdecl fcn_004fc700(unsigned short id, Slots* s, unsigned char flags)
{
	Offer offer;
	int i;
	int n;
	int v;
	float f;
	char* p;

	fcn_004f4830(10, &offer);
	for (i = 0; i < 6; i++) {
		if (s->used[i] == 0) {
			break;
		}
	}
	if (i >= 6) {
		return 0;
	}
	n = g_7f4ca0[id].count;
	f = n * (offer.amount * 0.01f);
	if (!(f > 0.0f)) {
		f = 0.0f;
	}
	v = (int) f;
	if (n > 0) {
		s->used[i] = 2;
		s->value[i] = v;
		s->amount[i] = offer.amount;
		if (flags & 1) {
			p = fcn_0050e4a0(1);
			p = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x115);
			fcn_004c51a0(*(int*) (p + 2), g_7f4ca0[id].owner, 0, v);
			g_773d48++;
		}
		if (flags & 2) {
			g_99f724 += v;
		}
	}
	return 1;
}
