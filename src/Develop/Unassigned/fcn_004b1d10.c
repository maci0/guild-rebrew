#include <string.h>

int __cdecl fcn_0064eeec(const char*);
void __cdecl fcn_004c5530(void*);

/* ADDRESS: GOLDTL 0x004b1d10 */
int __cdecl fcn_004b1d10(int a1, int a2, char* s)
{
	char buf[0xf8];
	int v;
	int w;

	if (*s != '-') {
		return 0;
	}
	v = fcn_0064eeec(s + 1);
	if (v > 10) {
		v = 10;
	}
	else if (v <= 1) {
		v = 1;
	}
	memset(buf, 0, 0xf8);
	w = *(int*) (*(int*) 0x773da8 + 4);
	*(char*) (buf + 4) = 0x59;
	*(int*) (buf + 0x58) = v;
	*(int*) (buf + 0x2c) = *(int*) 0x7f4c04;
	*(int*) (buf + 8) = w;
	*(int*) (buf + 0x28) = *(int*) 0x7f4c00;
	*(int*) (buf + 0x0c) = -1;
	*(unsigned short*) (buf + 0x36) = 2;
	*(int*) (buf + 0x30) = *(int*) 0x7f4c08;
	*(unsigned short*) (buf + 0x34) = *(unsigned short*) 0x7f4c0c;
	*(unsigned short*) (buf + 0x2c) = 0xb;
	fcn_004c5530(buf);
	return 1;
}
