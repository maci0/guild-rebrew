/* gm_RandomFloat01 - proper C */

// FUNCTION: GOLDTL 0x42e450
// SIZE: 22


#include "rebrew_types.h"
#include "rebrew_globals.h"
extern int __cdecl rand(void);

/* Returns a random float in [0, 1): the raw 32-bit random value scaled
 * by the 0x10025fbc constant. */

double __cdecl gm_RandomFloat01(void)
{
	return (float) rand() * g_const_1_over_32767;
}
