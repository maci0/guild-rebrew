#include <string.h>

char* __cdecl gm_FindSlotById(int arg1, int arg2);

/* ADDRESS: GOLDTL 0x004cc260 */
/* ADDRESS: GOLDDE 0x004b9a40 */
int __cdecl cm_ExSetMarktSlot(void* input, char* response)
{
	char* slot;

	slot = gm_FindSlotById(*(unsigned char*) ((char*) input + 0x10),
		*(unsigned short*) ((char*) input + 0x11));
	if (slot == 0) {
		return 1;
	}
	memcpy(slot, (char*) input + 0x11, 0x80);
	if (response != 0) {
		*response = 1;
		*(char*) (response + 1) = 0;
		*(int*) (response + 6) = 0;
	}
	return 0;
}
