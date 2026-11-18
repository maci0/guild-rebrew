


#include <string.h>

int __cdecl ahm_CheckFlag(void*);
int __cdecl fcn_004c6d30(int*);

int __cdecl fcn_004eeb50(char* object, int a2)
{
	int buf[6];

	if (ahm_CheckFlag(object) == 0) {
		return -1;
	}
	memset(buf, 0, sizeof(buf));
	buf[0] = 0x61536d53;
	buf[1] = *(int*) (object + 4);
	buf[4] = a2;
	return fcn_004c6d30(buf);
}
