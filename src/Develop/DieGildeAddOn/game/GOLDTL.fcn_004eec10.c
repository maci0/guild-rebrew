


#include <string.h>

int __cdecl ahm_CheckFlag(void*);
int __cdecl fcn_004c6d30(int*);

int __cdecl ahm_SendFireCommand(char* obj)
{
	int buf[6];

	if (ahm_CheckFlag(obj) == 0) {
		return -1;
	}
	memset(buf, 0, sizeof(buf));
	buf[0] = 0x46697245;
	buf[1] = *(int*) (obj + 4);
	return fcn_004c6d30(buf);
}
