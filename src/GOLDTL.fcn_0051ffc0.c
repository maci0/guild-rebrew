#include <string.h>

#include "Develop/DieGildeAddOn/game/ch_queue.h"

extern char* g_6b5c20;
extern char* g_868054;
extern char* g_99ec10;

int __cdecl fcn_0051fd50(int a, int b, unsigned int handle);
int __cdecl fcn_0051fd00(int a);
int __cdecl fcn_0051fd30(int a);
int __cdecl fcn_0041dd90(void* object);
int __cdecl fcn_00430910(void* buf, int size, int count, unsigned int handle);

/* ADDRESS: GOLDTL 0x0051ffc0 */
int __cdecl fcn_0051ffc0(unsigned int handle)
{
	CH_QUEUE_SLOT rec;
	int count;
	char flag;
	char* src;
	char* object;
	int i;
	int n;
	int idx;

	count = 0;
	for (i = 0x7f4e24; i < 0x85a224; i += 0x21c) {
		if (*(int*) i != 0) {
			count += 1;
		}
	}
	if (fcn_00430910(&count, 4, 1, handle) < 1) {
		return 0;
	}
	for (i = 0x7f4e24; i < 0x85a224; i += 0x21c) {
		n = *(int*) i;
		if (n != 0 && !fcn_0051fd50(n, *(int*) (i - 0x180), handle)) {
			return 0;
		}
	}
	count = 0;
	for (i = 0; i < 0x5008; i++) {
		idx = *(unsigned short*) (g_868054 + i * 0x43);
		if (*(char*) (g_99ec10 + idx * 0x41) == 0x1d) {
			count += 1;
		}
	}
	if (fcn_00430910(&count, 4, 1, handle) < 1) {
		return 0;
	}
	i = 0;
	do {
		idx = *(unsigned short*) (g_868054 + i);
		if (*(char*) (g_99ec10 + idx * 0x41) == 0x1d) {
			if (fcn_0051fd50(*(int*) (g_868054 + i + 0x3b),
			                 *(int*) (g_868054 + i + 2), handle) == 0) {
				return 0;
			}
		}
		i += 0x43;
	} while (i < 0x14f218);
	i = 0;
	do {
		src = g_6b5c20 + i;
		if (*(char*) (src + 9) != 0) {
			*(int*) (src + 0x14) = *(int*) *(int*) (src + 0x14);
			*(int*) (src + 0x24) = fcn_0051fd00(*(int*) (src + 0x24));
			*(int*) (src + 0x28) = fcn_0051fd00(*(int*) (src + 0x28));
		} else {
			memset(src, 0, 0x194);
		}
		i += 0x194;
	} while (i < 0xc5440);
	i = 0;
	for (;;) {
		memset(&rec, 0, 0x194);
		flag = 0;
		src = g_6b5c20 + i;
		idx = *(int*) (src + 0x14);
		if (idx >= 0 && idx < 0x300) {
			object = *(char**) (0x14d0020 + idx * 4);
			if (!fcn_0041dd90(object)) {
				__asm { int 3 }
			}
			if (object != 0 && *(int*) (*(char**) (object + 0x34) + 0x204) != 0) {
				flag = *(char*) (src + 9);
				memcpy(&rec, src, 0x194);
			}
			if (fcn_00430910(&flag, 1, 1, handle) < 1) {
				return 0;
			}
			if (fcn_00430910((char*) &rec + 0xc, 4, 1, handle) < 1) {
				return 0;
			}
			if (fcn_00430910((char*) &rec + 0x14, 4, 1, handle) < 1) {
				return 0;
			}
			if (fcn_00430910((char*) &rec + 0x30, 0x20, 1, handle) < 1) {
				return 0;
			}
			if (fcn_00430910((char*) &rec + 0x50, 0x20, 1, handle) < 1) {
				return 0;
			}
			if (fcn_00430910((char*) &rec + 0xf0, 0xa0, 1, handle) < 1) {
				return 0;
			}
			if (fcn_00430910((char*) &rec + 0x190, 1, 1, handle) < 1) {
				return 0;
			}
			if (fcn_00430910((char*) &rec + 0x24, 4, 1, handle) < 1) {
				return 0;
			}
			if (fcn_00430910((char*) &rec + 0x28, 4, 1, handle) < 1) {
				return 0;
			}
		}
		i += 0x194;
		if (i >= 0xc5440) {
			break;
		}
	}
	i = 0;
	do {
		src = g_6b5c20 + i;
		if (*(char*) (src + 9) != 0) {
			*(int*) (src + 0x14) = *(int*) (0x14d0020 + *(int*) (src + 0x14) * 4);
			*(int*) (src + 0x24) = fcn_0051fd30(*(int*) (src + 0x24));
			*(int*) (src + 0x28) = fcn_0051fd30(*(int*) (src + 0x28));
		}
		i += 0x194;
	} while (i < 0xc5440);
	return 1;
}
