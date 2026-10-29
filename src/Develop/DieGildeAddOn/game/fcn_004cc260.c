#include <string.h>

char* __cdecl gm_FindSlotById(int arg1, int arg2);

/* ADDRESS: GOLDTL 0x004cc260 */
int __cdecl fcn_004cc260(void* a1, char* a2)
{
	char* r;

	r = gm_FindSlotById(*(unsigned char*) ((char*) a1 + 0x10),
		*(unsigned short*) ((char*) a1 + 0x11));
	if (r == 0) {
		return 1;
	}
	memcpy(r, (char*) a1 + 0x11, 0x80);
	if (a2 != 0) {
		*a2 = 1;
		*(char*) (a2 + 1) = 0;
		*(int*) (a2 + 6) = 0;
	}
	return 0;
}
