#include <string.h>

unsigned short* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_005c6270(unsigned short*, int);
int __cdecl fcn_005086f0(unsigned short*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);


/* ADDRESS: GOLDTL 0x004bb820 */
int __cdecl fcn_004bb820(int* a1)
{
	char buf[0x400];
	unsigned short* e;

	e = gm_LookupEntityRecordById(a1[0]);
	if (e == 0)
		return 1;
	if (fcn_005c6270(e, 0x290) != 0)
		return 0x400;
	if (fcn_005086f0(e) == 0)
		return 0x400;
	io_FormatTextBuffer(buf, *(unsigned short*) (a1 + 1) + 0x12e7);
	fcn_00545d40(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
