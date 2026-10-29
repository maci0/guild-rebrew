#include <string.h>

extern char g_6b7fe8;
int __cdecl fcn_0065f220(char*, char*);

/* ADDRESS: GOLDTL 0x0042e4d0 */
int __cdecl fcn_0042e4d0(char* a, char* b)
{
	if (g_6b7fe8 != 0)
		return fcn_0065f220(a, b);
	return strcmp(a, b);
}
