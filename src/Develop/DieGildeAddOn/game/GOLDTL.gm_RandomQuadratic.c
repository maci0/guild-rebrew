/* gm_RandomQuadratic.  Split out of spiel622.c.  Prelude shared with spiel622.c. */

extern double __cdecl gm_RandomFloat01(void);
extern float g_const_1_0;
extern float g_const_0_0;
extern float g_const_neg_1_0;

// FUNCTION: GOLDTL 0x42e470
// SIZE: 48
// gm_RandomQuadratic

float __cdecl gm_RandomQuadratic(void)
{
	float rand_val;

	rand_val = (float) gm_RandomFloat01();
	rand_val = (rand_val + rand_val) - g_const_1_0;
	if (!(rand_val > g_const_0_0)) {
		return g_const_1_0 * rand_val * rand_val;
	}
	return g_const_neg_1_0 * rand_val * rand_val;
}
