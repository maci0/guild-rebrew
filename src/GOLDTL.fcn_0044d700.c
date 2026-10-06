#include <string.h>

char* __cdecl fcn_0064f026(char* s, const char* delim);

// FUNCTION: GOLD 0x0044ee20
// FUNCTION: GOLDTL 0x44d700
void __cdecl fcn_0044d700(int unused, char* out)
{
	char* t;

	t = fcn_0064f026(0, " ");
	*out = 0;
	if (strcmp(t, "LOCAL") == 0) {
		*out = 1;
		return;
	}
	if (strcmp(t, "ANIM") == 0) {
		*out = 2;
	}
}
