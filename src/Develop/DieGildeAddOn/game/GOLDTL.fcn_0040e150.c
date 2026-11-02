#include <string.h>
#include "Develop/DieGildeAddOn/game/ch_script.h"
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl CharacterSitsDown(char** object)
{
    unsigned char* p;

    p = (unsigned char*) *object;
    if (p == 0) {
        fcn_00425bf0(*(void**) 0x6b7e98,
            *(int*) ((char*) *(void**) 0x6b7e98 + 0x118),
            (char*) 0x67635c);
        return 0;
    }
    if ((p[0x8c] >> 4) & 1) {
        return 1;
    }
    return 0;
}



int __cdecl fcn_0040e150(char** a1, int* a2)
{
	char* p;

	p = *a1;
	if (p == 0) {
		fcn_00425bf0(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676384);
		return 0;
	}
	return strstr(p + 8, (char*) *a2) != 0;
}
