#include <string.h>

typedef struct {
	int used;
	char pad4[0x120];
} fcn_004bc060_slot;
// SIZE 0x124

extern int g_7728e4;

void __cdecl fcn_004030e0(int);

/* ADDRESS: GOLD 0x004bbb50 */
/* ADDRESS: GOLDTL 0x004bc060 */

void __cdecl fcn_004bc060(fcn_004bc060_slot* s)
{
	fcn_004030e0(s->used);
	memset(s, 0, sizeof(*s));
	g_7728e4--;
}
