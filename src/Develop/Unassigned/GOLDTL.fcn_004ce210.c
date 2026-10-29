extern int g_9badd0;

#include <string.h>

int __cdecl fcn_004c4330(void*);

/* ADDRESS: GOLDTL 0x004ce210 */
int __cdecl fcn_004ce210(int a1)
{
	char buf[0x9c];

	memset(buf + 0x10, 0, 0x80);
	*(int*) (buf + 0x14) = g_9badd0;
	buf[0] = 0x5f;
	*(int*) (buf + 0x10) = 1;
	*(int*) (buf + 0x18) = a1;
	return fcn_004c4330(buf);
}
