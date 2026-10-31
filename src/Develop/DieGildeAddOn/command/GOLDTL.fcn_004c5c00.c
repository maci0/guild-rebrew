char g_68ae64[] = "cm_RequestChrMoveToUniverse(): dummyname is too long...";



#include <string.h>

void __cdecl fcn_004c4330(void*);

#include "Develop/Units/Error/error_message.h"

void __cdecl cm_RequestChrMoveToUniverse(int a1, int a2, int a3, char* a4)
{
	char buf[0x9c];

	buf[0] = 0x30;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	*(int*) (buf + 0x18) = a3;
	if (strlen(a4) < 0x20) {
		strcpy(buf + 0x1c, a4);
	} else {
		ReportClientMessage(g_68ae64);
	}
	fcn_004c4330(buf);
}
