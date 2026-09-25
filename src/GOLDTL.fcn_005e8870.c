// FUNCTION: GOLD 0x5dbd80
// SIZE: 672
// FUNCTION: GOLDTL 0x005e8870
// SIZE: 668

typedef struct Vec24 {
	float v[24];
} Vec24;
// SIZE 0x60

typedef struct Wave {
	int id;
	int kind;
	int phase;
	Vec24 a;
	Vec24 b;
	float amp[24];
	float freq[24];
	float shift[24];
	float t;
} Wave;
// SIZE 0x1f0

extern Wave g_7763a0;
extern float g_666100;
extern int g_7763c4;
extern int g_776424;
extern float g_7764e4;
extern float g_776484;
extern int g_6ad628;
extern int g_6ad62c;
extern int g_6ad630;
extern float g_6ad634;

float __cdecl gm_RandomFloat01(void);
double __cdecl sin(double);
double __cdecl fabs(double);
#pragma intrinsic(sin, fabs)

void __cdecl fcn_005e8870(int mode, int id, Vec24* a, Vec24* b)
{
	int i;

	g_7763a0.id = id;
	g_7763a0.kind = 6;
	g_7763a0.phase = 0;
	g_7763a0.a = *a;
	g_7763a0.b = *b;
	for (i = 0; i < 24; i++) {
		a->v[i] *= -1.0f;
		b->v[i] *= -1.0f;
	}
	switch (mode) {
	case 0:
		for (i = 0; i < 24; i++) {
			g_7763a0.amp[i] = gm_RandomFloat01() * g_666100 * 0.25f + 1.0f;
			g_7763a0.freq[i] = gm_RandomFloat01() * g_666100 * 0.3f + 0.2f;
			g_7763a0.shift[i] = (gm_RandomFloat01() + 5.0f) * 6.2831855f;
		}
		break;
	case 1:
		for (i = 0; i < 24; i++) {
			g_7763a0.amp[i] = gm_RandomFloat01() * g_666100 * 0.05f + 1.0f;
			g_7763a0.freq[i] = gm_RandomFloat01() * g_666100 * 0.4f + 0.1f;
			g_7763a0.shift[i] = (gm_RandomFloat01() + 3.0f) * 3.1415927f;
		}
		break;
	case 2:
		for (i = 0; i < 24; i++) {
			g_7763a0.amp[i] = gm_RandomFloat01() * g_666100 * 0.5f + 1.0f;
			g_7763a0.freq[i] = gm_RandomFloat01() * g_666100 * 0.2f + 0.3f;
			g_7763a0.shift[i] = (gm_RandomFloat01() + 5.0f) * 6.2831855f;
		}
		break;
	case 3:
		for (i = 0; i < 24; i++) {
			g_7763a0.amp[i] = gm_RandomFloat01() * g_666100 * 0.25f + 1.0f;
			g_7763a0.freq[i] = gm_RandomFloat01() * g_666100 * 0.5f;
			g_7763a0.shift[i] = (gm_RandomFloat01() + 3.0f) * 3.1415927f;
		}
		break;
	default:
		for (i = 0; i < 24; i++) {
			g_7763a0.amp[i] = gm_RandomFloat01() * g_666100 * 0.5f + 1.0f;
			g_7763a0.freq[i] = gm_RandomFloat01() * g_666100 * 0.5f;
			g_7763a0.shift[i] = (gm_RandomFloat01() + 2.0f) * 6.2831855f;
		}
		break;
	}
	g_7763a0.t = gm_RandomFloat01() * 6.2831855f;
	g_6ad628 = g_7763c4;
	g_6ad62c = 0;
	g_6ad630 = g_776424;
	g_6ad634 = fabs(sin(g_7763a0.t) * g_7764e4) + g_776484;
}
