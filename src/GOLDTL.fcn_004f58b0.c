// FUNCTION: GOLDTL 0x004f58b0

// SIZE 0x8
#include "client_types.h"
typedef Pair_99f800 Pair;

extern Pair_99f800 g_99f800[0x800];

/* The scan is a goto loop tested at the top: a for or while loop gives the
 * same instructions but lays the -1 exit out ahead of the shared epilogue. */
int __cdecl fcn_004f58b0(int owner, int key)
{
	int found;
	int res;
	int i;

	found = 0;
	res = -1;
	i = 0;
loop:
	if (i >= 0x800) {
		goto end;
	}
	if (found == 0 && g_99f800[i].owner == -1 && g_99f800[i].key == -1) {
		res = i;
		found = 1;
	}
	if (g_99f800[i].owner == owner && g_99f800[i].key == key) {
		return -2;
	}
	i++;
	goto loop;
end:
	if (found == 0) {
		return -1;
	}
	return res;
}
