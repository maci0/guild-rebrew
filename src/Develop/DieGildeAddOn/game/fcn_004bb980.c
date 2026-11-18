#include <string.h>

void* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_00508b20(char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x004bb980 */
int __cdecl fcn_004bb980(int* a0)
{
	char buf[0x400];
	char* entity;

	entity = (char*) gm_LookupEntityRecordById(*a0);
	if (entity == 0)
		return 1;
	if (fcn_00508b20(entity) == 0)
		return 0x400;
	io_FormatTextBuffer(buf, 0x12e7 + *(unsigned short*) ((char*) a0 + 4));
	fcn_00545d40(*(int*) (entity + 4), *(int*) (entity + 4), buf, 0x100 < strlen(buf), 0x603, 0);
	return 0;
}
