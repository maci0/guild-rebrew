#include <string.h>

int __cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x004bba20 */
int __cdecl fcn_004bba20(int* a0)
{
	char buf[0x200];
	char* entity;
	int len;
	int big;

	entity = (char*) gm_LookupEntityRecordById(*a0);
	if (entity == 0) {
		return 1;
	}
	io_FormatTextBuffer(buf, 0x12e7 + *(unsigned short*) ((char*) a0 + 4));
	len = strlen(buf);
	big = (unsigned int) len > 0x100u;
	he_PostEntityMessage(*(int*) (entity + 4), *(int*) (entity + 4), buf, big, 0x603, 0);
	return 0;
}
