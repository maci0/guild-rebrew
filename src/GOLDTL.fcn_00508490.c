// FUNCTION: GOLD 0x505440
// FUNCTION: GOLDTL 0x00508490

typedef struct
{
	int a;
	float b;
	int c;
} S0c;
// SIZE 0xc

extern float g_6628a8;

int __cdecl fcn_00508220(int k, S0c* s);
unsigned short __cdecl gm_RandomMod(unsigned short n);
void __cdecl fcn_004c4510(char* p, int id);
void __cdecl fcn_004c4570(int a, int b, int c, int* v);
void __cdecl fcn_004c5360(void);
float __cdecl fcn_004ff210(unsigned short id, int v);

float __cdecl fcn_00508490(char* p)
{
	S0c s;
	int r;
	int flags;
	int nf;

	flags = *(int*) (p + 0x2c);
	if (flags & 0xf) {
		return g_6628a8;
	}
	if (!fcn_00508220(1, &s)) {
		return g_6628a8;
	}
	r = gm_RandomMod((unsigned short) s.c);
	if (r == 0) {
		return g_6628a8;
	}
	nf = ((r ^ flags) & 0xf) ^ flags;
	fcn_004c4510(p, *(int*) (p + 4));
	fcn_004c4570(4, 1, 0x2c, &nf);
	fcn_004c5360();
	return fcn_004ff210(*(unsigned short*) p, -(int) (r * s.b));
}
