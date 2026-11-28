extern char d2_RadioGroups[];
extern char d2_RadioGroups[];



#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl d2_ClearRadioGroup(int i)
{
	memset((void*) (d2_RadioGroups + i * 140), 0, 0x8c);
}
unsigned char _dpad_10161d0[92656];
