#include <string.h>

#pragma intrinsic(memcpy)

extern char* cm_CommandQueueHead;
extern unsigned char g_aed340[];

/* ADDRESS: GOLDTL 0x004c4250 */
int __cdecl cm_ReassembleQueuedCommand(char* obj)
{
	char* e;
	char* prev;
	int i;

	if (*(int*) (obj + 0xc) == 0) {
		return 0;
	}
	for (e = cm_CommandQueueHead; e != 0; e = *(char**) (e + 0x95)) {
		if (*(unsigned char*) (e + 3) == *(unsigned char*) (obj + 3) &&
				*(int*) (e + 8) == *(int*) (obj + 0xc)) {
			break;
		}
	}
	if (e == 0) {
		return 0;
	}
	*(int*) (obj + 0xc) = 0;
	*(int*) 0x1005764 = *(unsigned short*) (e + 0x10);
	memcpy(g_aed340, e + 0x12, 0x7e);
	*(char*) e = 0;
	i = 0x7e;
	while (i < *(int*) 0x1005764) {
		prev = e;
		e = cm_CommandQueueHead;
		if (e == 0) {
			return 0;
		}
		while (!(*(unsigned char*) (e + 3) == *(unsigned char*) (prev + 3) &&
			*(int*) (e + 8) == *(int*) (prev + 0xc))) {
			e = *(char**) (e + 0x95);
			if (e == 0) {
				return 0;
			}
		}
		memcpy(g_aed340 + i, e + 0x10, 0x80);
		*(int*) (prev + 0xc) = 0;
		*(char*) e = 0;
		i += 0x80;
	}
	*(int*) (e + 0xc) = 0;
	return *(int*) 0x1005764;
}
unsigned char _dpad_9badd0[712560];
