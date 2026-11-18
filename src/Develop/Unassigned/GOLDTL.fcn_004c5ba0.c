


#include <string.h>

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5ba0(int a1, int a2, int a3, char* text)
{
	char buf[0x9c];

	buf[0] = 0x2f;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	*(int*) (buf + 0x18) = a3;
	strcpy(buf + 0x1c, text);
	fcn_004c4330(buf);
}
