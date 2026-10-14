/* ADDRESS: GOLDTL 0x00773d38 */
extern int g_773d38;



#include <string.h>

void __cdecl fcn_004c4330(void*);

int __cdecl fcn_0064d3f8(void);

void __cdecl fcn_004c5820(void* a1)
{
	char buf[0x9c];

	buf[0] = 0x22;
	memcpy(buf + 0x10, a1, 0x2d);
	*(int*) (buf + 0x10) = g_773d38;
	*(int*) (buf + 0x35) = 1;
	*(int*) (buf + 0x39) = fcn_0064d3f8();
	fcn_004c4330(buf);
}
