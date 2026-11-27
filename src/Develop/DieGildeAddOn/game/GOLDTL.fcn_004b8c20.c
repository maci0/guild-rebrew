#include <string.h>

unsigned short* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(void*, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
void __cdecl gm_ModifyHealth(int, int);


/* ADDRESS: GOLDTL 0x004b8c20 */
int __cdecl fcn_004b8c20(int* request)
{
	char buf[0x200];
	unsigned short* e;
	int n;

	n = gm_RandomMod(3) + 2;
	e = gm_LookupEntityRecordById(request[0]);
	if (e == 0)
		return 1;
	if (gm_HasActiveSpecialObject(e, 0x290) != 0)
		return 0x400;
	if (*(int*) (e + 0xca) < n)
		return 0x400;
	io_FormatTextBuffer(buf, *(unsigned short*) (request + 1) + 0x12e7, n);
	he_PostEntityMessage(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x603, 0);
	gm_ModifyHealth(*(int*) (e + 2), -n);
	return 0;
}
