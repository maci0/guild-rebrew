


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
	char pad8[0x1a8 - 8];
	int count;
	char pad1ac[0x21c - 0x1ac];
} Obj;

extern char g_7f4ca0[];
extern unsigned char g_773d75;
extern int g_99f768;

void __cdecl fcn_004f4830(int kind, Offer* o);
char* __cdecl fcn_0050e4a0(int n);
char* __cdecl fcn_00502cd0(int obj, int mode, ...);
void __cdecl fcn_004c51a0(int a, int b, char c, int d);
int __cdecl gm_AccumulateTyped2(Obj* o);

int __cdecl fcn_004fc800(unsigned short id, Slots* s, unsigned char flags)
{
	int amt;
	Offer offer;
	int i;
	int n;
	int v;
	float f;
	char* p;

	fcn_004f4830(0xd, &offer);
	amt = offer.amount;
	p = fcn_0050e4a0(1);
	fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x115);
	for (i = 0; i < 6; i++) {
		if (s->used[i] == 0) {
			break;
		}
	}
	if (i >= 6) {
		return 0;
	}
	n = ((Obj*)g_7f4ca0)[id].count;
	f = n * (amt * 0.01f);
	if (!(f > 0.0f)) {
		f = 0.0f;
	}
	v = (int) f;
	if (n > 0) {
		s->used[i] = 3;
		s->value[i] = v;
		s->amount[i] = amt;
		if (flags & 1) {
			p = fcn_0050e4a0(1);
			p = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x115);
			if (gm_AccumulateTyped2(&((Obj*)g_7f4ca0)[id]) >= v) {
				fcn_004c51a0(*(int*) (p + 2), ((Obj*)g_7f4ca0)[id].owner, (*(char*)&g_773d75), v);
			}
		}
		if (flags & 2) {
			g_99f768 += v;
			((Obj*)g_7f4ca0)[id].count = 0;
		}
	}
	return 1;
}
