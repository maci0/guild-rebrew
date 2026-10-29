#include <string.h>

void* __cdecl fcn_00501510(int);
void __cdecl fcn_004be280(void*);
void* __cdecl fcn_004be2a0(void*);

/* ADDRESS: GOLDTL 0x004cdda0 */
int __cdecl fcn_004cdda0(char* a1, unsigned char* a2, unsigned char* a3)
{
	char buf[0x240];
	void* p;
	char* prev;
	char* node;
	int n;
	int i;

	if (a2 != 0) {
		a2[0] = 2;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	p = (void*) fcn_00501510(*(int*) (a1 + 0x10));
	if (p == 0)
		return -1;
	if (*(int*) ((char*) p + 0x29) != 0) {
		fcn_004be280(*(void**) ((char*) p + 0x29));
		*(int*) ((char*) p + 0x29) = 0;
	}
	n = *(int*) (a1 + 0x14);
	memcpy(buf, (void*) 0xaed340, n * 64);
	node = buf;
	prev = 0;
	for (i = 0; i < n; i++) {
		*(char**) (node + 0x38) = prev;
		*(char**) (node + 0x3c) = node + 0x40;
		prev = node;
		node += 0x40;
	}
	*(int*) (node - 4) = 0;
	*(void**) ((char*) p + 0x29) = fcn_004be2a0(buf + 4);
	if (a3 != 0)
		a3[0] = 1;
	return 0;
}
