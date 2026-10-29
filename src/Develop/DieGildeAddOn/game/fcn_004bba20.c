#include <string.h>

int __cdecl fcn_00508e40(int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x004bba20 */
int __cdecl fcn_004bba20(int* a0)
{
	char buf[0x200];
	char* p;
	int len;
	int big;

	p = (char*) fcn_00508e40(*a0);
	if (p == 0) {
		return 1;
	}
	fcn_0051af00(buf, 0x12e7 + *(unsigned short*) ((char*) a0 + 4));
	len = strlen(buf);
	big = (unsigned int) len > 0x100u;
	fcn_00545d40(*(int*) (p + 4), *(int*) (p + 4), buf, big, 0x603, 0);
	return 0;
}
