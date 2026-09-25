#include <string.h>

extern char* g_104049c;
extern unsigned int g_10404a0;

int __cdecl fcn_0065f220(const char* a, const char* b);

// FUNCTION: GOLDTL 0x45bde0
// SIZE: 96
char* __cdecl fcn_0045bde0(const char* name)
{
	char buf[0x40];
	unsigned int i;
	char* p;

	strcpy(buf, name);
	p = g_104049c;
	for (i = 0; i < g_10404a0; i++, p += 0x70) {
		if (*(int*) (p + 0x40) > 0 && fcn_0065f220(buf, p) == 0) {
			return p;
		}
	}
	return 0;
}
