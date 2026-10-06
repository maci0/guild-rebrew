// FUNCTION: GOLD 0x004c9740
// FUNCTION: GOLDTL 0x4ca2e0

#include <string.h>

extern int g_14cbca0;
extern int g_699364;
extern char g_68a9d8[];

int __cdecl fcn_004c4dc0(char*, int);
char* __cdecl fcn_00502fe0(int, int, int);

int __cdecl fcn_004ca2e0(char* x, char* out)
{
	char* obj;
	char* dst;

	if (g_14cbca0 != -1)
		g_699364 = *(int*) (x + 0x10);
	*(int*) (x + 0x14) = fcn_004c4dc0(x, *(int*) (x + 0x14));
	obj = fcn_00502fe0(*(int*) (x + 0x14), 0x1b5, 1);
	if (obj == 0)
		return 1;
	(*(int*)g_68a9d8) = *(int*) (obj + 2);
	obj[0x12] = 0x40;
	x += 0x18;
	dst = obj + 0x1c;
	memcpy(dst, x, 7);
	obj[0x22] = 0;
	if (out != 0) {
		out[0] = 1;
		out[1] = 3;
		*(char**) (out + 6) = obj;
	}
	return 0;
}
