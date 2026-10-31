


extern char g_68b2d8[];

unsigned short* __cdecl gm_LookupEntityRecordById(int);
#include "Develop/Units/Error/error_message.h"
void __cdecl fcn_00529160(int, int, int, int);

int __cdecl cm_ExChangePlayerHe(char* x, char* out)
{
	unsigned short* e;

	e = gm_LookupEntityRecordById(*(int*) (x + 0x10));
	if (e == 0)
		ReportClientMessage(g_68b2d8);
	if (*e != 0xffff)
		fcn_00529160(*(int*) ((char*) e + 0x16c), *(int*) (x + 0x14), *e, 0);
	if (out != 0) {
		out[0] = 1;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
