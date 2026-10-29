#include <string.h>

#pragma intrinsic(memcpy)

extern char* g_aed324;
extern unsigned char g_aed340[];

/* ADDRESS: GOLDTL 0x004c4250 */
int __cdecl fcn_004c4250(char* obj)
{
	char* e;
	char* prev;
	int i;

	if (*(int*) (obj + 0xc) == 0) {
		return 0;
	}
	e = g_aed324;
	if (e == 0) {
		return 0;
	}
	while (!(*(unsigned char*) (obj + 3) == *(unsigned char*) (e + 3) &&
			*(int*) (obj + 0xc) == *(int*) (e + 8))) {
		e = *(char**) (e + 0x95);
		if (e == 0) {
			return 0;
		}
	}
	*(int*) (obj + 0xc) = 0;
	*(int*) 0x1005764 = *(unsigned short*) (e + 0x10);
	memcpy(g_aed340, e + 0x12, 0x7e);
	*(char*) e = 0;
	i = 0x7e;
	while (i < *(int*) 0x1005764) {
		prev = e;
		e = g_aed324;
		if (e == 0) {
			return 0;
		}
		while (!(*(unsigned char*) (prev + 3) == *(unsigned char*) (e + 3) &&
			*(int*) (prev + 0xc) == *(int*) (e + 8))) {
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
