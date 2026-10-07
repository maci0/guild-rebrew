// FUNCTION: GOLD 0x551690
// FUNCTION: GOLDTL 0x559760

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x168];
	char* who;
	char pad174[0x7c];
	int flag;
	char pad1f4[0x28];
};

// SIZE 0x8
typedef struct F8 {
	int mask;
	int b;
} F8;

extern int g_7e4538;
extern int g_7e453c;
extern unsigned short g_7f4c04;
extern unsigned short g_774970;
extern char g_7f4ca0[];
extern unsigned char* g_90e094;
extern int g_6643d8[];

int __cdecl fcn_004a55c0(struct house*, int, int*, float, float, unsigned short*);
int __cdecl fcn_004a5e60(struct house*, int, F8, int, float, int*);
double __cdecl gm_RandomFloat01(void);
void __cdecl fcn_005015e0(int*, int, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
unsigned short __cdecl fcn_0042e410(int);
int __cdecl fcn_004c5d60(int, int, int);

int __cdecl fcn_00559760(char* s, int n, int m)
{
	int tgt;
	int flt[2];
	int x;
	struct house* h;
	int idx;
	F8 f;

	tgt = -1;
	flt[0] = 0x20a0;
	flt[1] = 0x402c20;
	if (n + (g_7e453c != 0) + (g_7e4538 != 0 ? 2 : 0) * 2 >= 10) {
		goto fail;
	}
	if (s[9] != 0) {
		goto fail;
	}
	if (g_7f4c04 < 11) {
		goto fail;
	}
	if ((float) (n - m) / (n + 1) < 0.66f) {
		flt[0] = 0x402c20;
		flt[1] = 0x20a0;
	}
	if (fcn_004a55c0(&((struct house*)g_7f4ca0)[g_774970], 1, &flt[0], 0.0f, 100.0f, (unsigned short*) &x) == 0
	    && fcn_004a55c0(&((struct house*)g_7f4ca0)[g_774970], 1, &flt[1], 0.0f, 100.0f, (unsigned short*) &x) == 0) {
		goto fail;
	}
	f.mask = 0xa7f4c3a0;
	h = &((struct house*)g_7f4ca0)[(unsigned short) x];
	f.b = 1;
	if (h->who != 0) {
		tgt = *(int*) (h->who + 1);
	} else {
		if (fcn_004a5e60(&((struct house*)g_7f4ca0)[g_774970], 0, f, 0, 100.0f, &tgt) == 0) {
			goto fail;
		}
	}
	if (!(gm_RandomFloat01() > n * 0.1f)) {
		goto fail;
	}
	fcn_005015e0(&n, 0, 0, tgt);
	if (n != 0) {
		idx = (n - (*(int*)&g_90e094)) / 0xa9;
		fcn_004c5420(h->handle, 0x1c8, 4, 0x40000000, 0);
		*(int*) s = h->handle;
		*(int*) (s + 4) = tgt;
		s[8] = 1;
		s[9] = 9;
		if (h->flag != 0) {
			s[9] = 0x29;
		}
		s[0xa] = (char) g_6643d8[fcn_0042e410(0x10)];
		s[0xb] = (char) idx;
		s[0xc] = -1;
		return fcn_004c5d60(h->handle, tgt, -1);
	}
fail:
	return -1;
}
