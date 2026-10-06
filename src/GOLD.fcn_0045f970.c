#include <string.h>

#include "g_fb9074.h"

/* GOLD twin of GOLDTL fcn_0045bde0: the texture slot is 0x80 bytes here,
 * 0x70 in GOLDTL. */

extern TexSlot* g_fb9074;
extern unsigned int g_fb9084;

int __cdecl fcn_005eab80(const char* a, const char* b);

// FUNCTION: GOLD 0x45f970
char* __cdecl fcn_0045f970(const char* name)
{
	char buf[0x40];
	unsigned int i;
	char* p;

	strcpy(buf, name);
	p = (char*) g_fb9074;
	for (i = 0; i < g_fb9084; i++, p += 0x80) {
		if (*(int*) (p + 0x40) > 0 && fcn_005eab80(buf, p) == 0) {
			return p;
		}
	}
	return 0;
}
