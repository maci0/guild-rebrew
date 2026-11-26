#include <string.h>

int __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_ConsumeRandomEntitySlotBit(char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x004bb8e0 */
int __cdecl fcn_004bb8e0(int* request)
{
	char buf[0x400];
	char* p;
	size_t len;

	p = (char*) gm_LookupEntityRecordById(*request);
	if (p == 0)
		return 1;
	if (gm_ConsumeRandomEntitySlotBit(p) == 0)
		return 0x400;
	io_FormatTextBuffer(buf, 0x12e7 + *(unsigned short*) ((char*) request + 4));
	len = strlen(buf);
	fcn_00545d40(*(int*) (p + 4), *(int*) (p + 4), buf, len > 0x100, 0x603, 0);
	return 0;
}
