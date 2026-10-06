// FUNCTION: GOLD 0x4e5b50
// FUNCTION: GOLDTL 0x4e7660

#include <string.h>

extern char g_68d960[];
extern char* g_14a6554;

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_0064d41a(char*, char*, ...);

void __cdecl fcn_004e7660(char* x, char* out)
{
	char buf[0x100];
	int* p;
	char* e;
	int i;

	p = (int*) (x + 0x5c);
	for (i = 0; i < 8; i++, p++) {
		e = fcn_00508e40(*p);
		if (e != 0)
			fcn_0064d41a(buf, g_68d960, *(int*) (e + 4), e + 0x30);
		else
			fcn_0064d41a(buf, g_68d960, -1, g_14a6554);
		strcat(out, buf);
	}
}
