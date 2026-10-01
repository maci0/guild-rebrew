/* gm_RandomQuadratic.  Split out of spiel622.c: the reference places
 * gm_RandomFloat01 (0x1001a0f0) between gm_RandomMod and this function,
 * and order-sources orders whole objects by their first VA.  Prelude
 * shared verbatim with spiel622.c. */

#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "entity.h"

#pragma intrinsic(memcpy, memset)

extern unsigned char g_slot_table[0x300 * 0x21c];

double __cdecl gm_RandomFloat01(void);
extern const float g_const_0_0; /* 0x100256cc */

/* Allocates and initializes a game entity structure. Allocates
 * memory via m_AllocTracked and zeroes the initial fields. */

extern int g_some_limit;
extern unsigned int g_player_record_dst;
extern unsigned int g_player_record_src;

// FUNCTION: SERVER 0x1001a110
// gm_RandomQuadratic

float __cdecl gm_RandomQuadratic(void)
{
	float rand_val;

	rand_val = (float) gm_RandomFloat01();
	rand_val = (rand_val + rand_val) - g_const_1_0f;
	if (rand_val < g_const_0_0) {
		return g_const_neg_1_0 * rand_val * rand_val;
	}
	return g_const_1_0f * rand_val * rand_val;
}
