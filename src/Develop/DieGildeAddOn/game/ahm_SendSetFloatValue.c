


#include <string.h>

int __cdecl ahm_CheckFlag(void*);
int __cdecl cm_RequestAhmCommand(int*);

int __cdecl ahm_SendSetFloatValue(char* object, int value)
{
	int buf[6];

	if (ahm_CheckFlag(object) == 0) {
		return -1;
	}
	memset(buf, 0, sizeof(buf));
	buf[0] = 0x61536d53;
	buf[1] = *(int*) (object + 4);
	buf[4] = value;
	return cm_RequestAhmCommand(buf);
}
