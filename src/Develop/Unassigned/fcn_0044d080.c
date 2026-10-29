#include <string.h>

extern char g_662d1c[];

char* __cdecl fcn_0064f026(char*, char*);

/* ADDRESS: GOLDTL 0x0044d080 */
void __cdecl fcn_0044d080(int a1, int* o)
{
	char* s;

	s = fcn_0064f026(0, g_662d1c);
	*(char*) ((char*) o[4] + o[2] * 0xe0 + 0xc0) = 0;
	if (strcmp(s, "MIX") == 0) {
		*(char*) ((char*) o[4] + o[2] * 0xe0 + 0xc0) = 1;
		return;
	}
	if (strcmp(s, "ADD") == 0) {
		*(char*) ((char*) o[4] + o[2] * 0xe0 + 0xc0) = 2;
	}
}
