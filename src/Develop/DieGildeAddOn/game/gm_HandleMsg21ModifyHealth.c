#include <string.h>

extern unsigned char g_773d75;

char* __cdecl gm_LookupEntityRecordById(int id);
unsigned short __cdecl fcn_0042e410(int a);
int __cdecl gm_ConvertUnitsToAmount(int a, char b);
void __cdecl io_FormatTextBuffer(char* buf, int fmt, ...);
void __cdecl he_PostEntityMessage(int a, int b, char* buf, int c, int d, int e);
void __cdecl gm_ModifyHealth(int a, int b);

/* ADDRESS: GOLDTL 0x004b8d00 */
int __cdecl gm_HandleMsg21ModifyHealth(int* request)
{
	char buf[0x200];
	char* p;
	int n;

	p = gm_LookupEntityRecordById(*request);
	if (p == 0) {
		return 1;
	}
	io_FormatTextBuffer(buf, 0x12e7 + *(unsigned short*) ((char*) request + 4),
		gm_ConvertUnitsToAmount(1, g_773d75),
		n = (unsigned short) fcn_0042e410(3) + 3);
	he_PostEntityMessage(*(int*) (p + 4), *(int*) (p + 4), buf,
		strlen(buf) > 0x100, 0x603, 0);
	gm_ModifyHealth(*(int*) (p + 4), n);
	return 0;
}
