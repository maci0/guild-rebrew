/* gm_AllocateObjectSlot — scan the fixed object pool (stride 0x43) for the
 * first slot whose active flag is 0; return its address, or NULL once the
 * pool is exhausted (limit 0x5008 slots). */

// FUNCTION: SERVER 0x100165a0

#include <stdlib.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"


char* __cdecl gm_AllocateObjectSlot(void)
{
	char* node;
	int i;
	char* result;

	node = (char*) g_query_base;
	result = NULL;
	i = 0;
	while (result == NULL && i < 0x5008) {
		if (*(short*) node != 0) {
			i++;
			node += 0x43;
		} else {
			result = node;
		}
	}
	return result;
}
