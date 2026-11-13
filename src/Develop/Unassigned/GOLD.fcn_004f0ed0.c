#include <string.h>

int __cdecl gm_ResolveEntityById(void**, void**, void**, int);
int __cdecl gv_CheckSlotActive(void*, int);
char* __cdecl fcn_004ef570(void*, int, unsigned char);
int __cdecl fcn_004ef760(void*, void*);
void* __cdecl fcn_004ef7c0(void*, void*, void*, int (__cdecl*)(void*, void*), int);
int __cdecl gm_SubObjectNoKill(int, int, int);
int __cdecl gm_AddObjekt(int, int, int);
extern unsigned char* g_7e3f30;

/* ADDRESS: GOLD 0x004f0ed0 */
int __cdecl fcn_004f0ed0(char* request)
{
	char* entity;
	char* building;
	void* group;
	char* oldSlot;
	char* newSlot;
	char* src;
	char* srcEnd;
	char* dst;
	char* dstEnd;
	int type;
	int count;
	int value;
	unsigned short item;

	gm_ResolveEntityById(0, 0, (void**) &entity, *(int*) request);
	if (entity == 0)
		return -6;
	gm_ResolveEntityById((void**) &building, 0, 0, *(int*) (request + 4));
	if (building == 0 || *(unsigned short*) (building + 0x27) == 0xffff ||
	    (char*) (*(unsigned short*) (building + 0x27) * 0x21c + 0x770b80) == *(char**) 0x6f1bf8)
		return -1;
	if (g_7e3f30[(unsigned char) *building * 0x24d] != 0x1d)
		return -2;
	group = *(void**) (building + 0x65);
	if (group == 0)
		return -3;
	type = *(int*) (request + 8);
	if (!gv_CheckSlotActive(group, type))
		return -4;
	oldSlot = fcn_004ef570(group, type, (unsigned char) request[0xc]);
	if (oldSlot == 0 || *(unsigned short*) (oldSlot + 8) != *(unsigned short*) (entity + 0x50))
		return -7;
	src = *(char**) (oldSlot + 0x10);
	count = *(int*) (0x5ee054 + type * 4);
	newSlot = fcn_004ef7c0(entity, building, 0, fcn_004ef760, *(int*) (request + 0xd));
	if (newSlot == 0)
		return -7;
	dst = *(char**) (newSlot + 0x10);
	dstEnd = dst + *(int*) (0x5ee054 + *(int*) (request + 0xd) * 4) * 0x44;
	srcEnd = src + count * 0x44;
	for (; (unsigned long) dst < (unsigned long) dstEnd; dst += 0x44) {
		if (*(int*) dst == -1) {
			while ((unsigned long) src < (unsigned long) srcEnd && *(int*) src == -1)
				src += 0x44;
			if ((unsigned long) src >= (unsigned long) srcEnd)
				break;
			memcpy(dst, src, 0x44);
			memset(src, 0, 0x44);
			*(int*) src = -1;
			if ((unsigned long) src >= (unsigned long) srcEnd)
				break;
		}
	}
	*(int*) (newSlot + 4) = *(int*) (oldSlot + 4);
	*(int*) (oldSlot + 4) = -1;
	*(unsigned short*) (newSlot + 8) = *(unsigned short*) (oldSlot + 8);
	*(unsigned short*) (oldSlot + 8) = 0xffff;
	*(unsigned short*) (newSlot + 0xa) = (unsigned short) (*(int*) 0x770ae0 + 10);
	newSlot[0xc] = (char) 0xff;
	*(unsigned short*) (oldSlot + 0xa) = 0xff;
	if (*(int*) 0x1460ae0 != -1)
		*(int*) 0x61a634 = *(int*) (request + 0x15);
	if (*(int*) (request + 0x11) > 0) {
		item = *(unsigned short*) (0x7e3f94 + *(unsigned char*) 0x6f1bc5 * 0x2f4);
		gm_SubObjectNoKill(*(int*) (entity + 4), item, *(int*) (request + 0x11));
		value = (int) (*(int*) (request + 0x11) * *(float*) (0x5ee034 + *(int*) (request + 0xd) * 4));
		item = *(unsigned short*) (0x7e3f94 + *(unsigned char*) 0x6f1bc5 * 0x2f4);
		gm_AddObjekt(*(int*) (0x770b84 + *(unsigned short*) (building + 0x27) * 0x21c), item, value);
	}
	return 0;
}
