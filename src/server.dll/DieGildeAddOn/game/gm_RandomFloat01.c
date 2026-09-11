/* gm_RandomFloat01 - proper C */

// FUNCTION: SERVER 0x1001a0f0
// SIZE: 22

extern float g_const_1_over_32767;
extern int __cdecl rand(void);

/* Returns a random float in [0, 1): the raw 32-bit random value scaled
 * by the 0x10025fbc constant. */

double __cdecl gm_RandomFloat01(void)
{
	return (float) rand() * g_const_1_over_32767;
}
