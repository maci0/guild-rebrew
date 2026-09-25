// FUNCTION: GOLD 0x5dc020
// SIZE: 240
// FUNCTION: GOLDTL 0x005e8b10
// SIZE: 235

#pragma pack(push, 2)
// SIZE 0xe
typedef struct {
	int a;
	unsigned short b;
	int c;
	int d;
} Stamp;
#pragma pack(pop)

// SIZE 0x1f0
typedef struct {
	int a;
	int b;
	int c;
	float t0[24];
	float t1[24];
	float t2[24];
	float t3[24];
	float t4[24];
	float phase;
} Weather;

extern Stamp g_7f4c00;
extern Weather g_7763a0;
extern int g_6ad62c;
extern float g_6ad628;
extern float g_6ad630;
extern float g_6ad634;

double __cdecl sin(double);
#pragma intrinsic(sin)
int __cdecl fcn_00500d20(Stamp*, Stamp*);

void __cdecl fcn_005e8b10(void)
{
	int r;
	Stamp s;
	float v;
	int i;

	s.a = g_7763a0.a;
	s.b = (unsigned short) g_7763a0.b;
	s.c = g_7763a0.c;
	s.d = 0;
	r = fcn_00500d20(&s, &g_7f4c00);
	v = r * (1.0f / 60.0f);
	if (!(v < 0.0f)) {
		i = g_7f4c00.b;
		g_6ad62c = 0;
		g_7763a0.phase += v * g_7763a0.t4[i];
		g_6ad628 = g_7763a0.t0[i];
		g_6ad630 = g_7763a0.t1[i];
		g_6ad634 = ((float) sin(g_7763a0.phase) + 1.0f) * g_7763a0.t3[i] * 0.5f + g_7763a0.t2[i];
		g_7763a0.a = g_7f4c00.a;
		g_7763a0.b = i;
		g_7763a0.c = g_7f4c00.c;
	}
}
