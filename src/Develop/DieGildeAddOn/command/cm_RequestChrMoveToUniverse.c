char str_cm_RequestChrMoveToUniverse_dummyname[] = "cm_RequestChrMoveToUniverse(): dummyname is too long...";



#include <string.h>

void __cdecl cm_EnqueueClientPacket(void*);

#include "Develop/Units/Error/error_message.h"

/* ADDRESS: GOLDDE 0x004b3530 */
void __cdecl cm_RequestChrMoveToUniverse(int a1, int a2, int a3, char* dummyName)
{
	char buf[0x9c];

	buf[0] = 0x30;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	*(int*) (buf + 0x18) = a3;
	if (strlen(dummyName) < 0x20) {
		strcpy(buf + 0x1c, dummyName);
	} else {
		ReportClientMessage(str_cm_RequestChrMoveToUniverse_dummyname);
	}
	cm_EnqueueClientPacket(buf);
}
