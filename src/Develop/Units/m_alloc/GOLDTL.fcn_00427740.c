#include <string.h>

#pragma intrinsic(memset)

extern char g_679478[];

char* __cdecl m_alloc(int size, char* tag);

/* ADDRESS: GOLDTL 0x00427740 */
int __cdecl fcn_00427740(char* obj, int type, int count)
{
	int size;
	int* rec;

	size = 0;
	if (type == 1) {
		size = 4;
	} else if (type == 2) {
		size = 1;
	} else if (type == 6) {
		size = 0x60;
	} else if (type == 7) {
		size = 4;
	} else {
		__asm {
			int 3
		}
	}
	rec = (int*) (*(int*) (obj + 0x114) * 0x30 + *(int*) (obj + 0x108));
	*rec = (*rec ^ type) & 0xf ^ *rec;
	size = size * count;
	*(int*) (*(int*) (obj + 0x114) * 0x30 + 0x2c + *(int*) (obj + 0x108)) =
		(int) m_alloc(size, g_679478);
	memset((void*) *(int*) (*(int*) (obj + 0x114) * 0x30 + 0x2c
		+ *(int*) (obj + 0x108)), 0, size);
	*(int*) (*(int*) (obj + 0x114) * 0x30 + 0x24 + *(int*) (obj + 0x108)) = count;
	return *(int*) (obj + 0x108) + (*(int*) (obj + 0x114))++ * 0x30;
}
