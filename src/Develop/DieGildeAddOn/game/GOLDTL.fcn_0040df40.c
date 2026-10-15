#include "Develop/DieGildeAddOn/game/ch_script.h"
int __cdecl fcn_00445600(int, int, int, int);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl CharacterSitting(char** object)
{
    unsigned char* p;

    p = (unsigned char*) *object;
    if (p == 0) {
        fcn_00425bf0(*(void**) 0x6b7e98,
            *(int*) ((char*) *(void**) 0x6b7e98 + 0x118),
            (char*) 0x6762d4);
        return 0;
    }
    return (p[0x8c] >> 4) & 1;
}



int __cdecl fcn_0040df40(char** a1, int* a2)
{
	char* p;

	p = *a1;
	if (p == 0) {
		fcn_00425bf0(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x6762fc);
		return 0;
	}
	return fcn_00445600(*(int*) (p + 0x34), 0x140, 0, *a2);
}
