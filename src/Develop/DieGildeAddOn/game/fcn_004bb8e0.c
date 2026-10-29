#include <string.h>

int __cdecl fcn_00508e40(int);
int __cdecl fcn_00508a20(char*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x004bb8e0 */
int __cdecl fcn_004bb8e0(int* a0)
{
	char buf[0x400];
	char* p;
	int len;

	p = (char*) fcn_00508e40(*a0);
	if (p == 0)
		return 1;
	if (fcn_00508a20(p) == 0)
		return 0x400;
	fcn_0051af00(buf, 0x12e7 + *(unsigned short*) ((char*) a0 + 4));
	len = strlen(buf);
	fcn_00545d40(*(int*) (p + 4), *(int*) (p + 4), buf, len > 0x100, 0x603, 0);
	return 0;
}
