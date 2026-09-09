/* gm_RandomFloat01 - proper C */

// FUNCTION: SERVER 0x1001a0f0
// SIZE: 22

extern float g_const_5fbc;
int __cdecl fcn_1001b542(void); /* rand-like helper */

/* Returns a random float in [0, 1): the raw 32-bit random value scaled
 * by the 0x10025fbc constant. */

double __cdecl gm_RandomFloat01(void)
{
	return (float) fcn_1001b542() * g_const_5fbc;
}
