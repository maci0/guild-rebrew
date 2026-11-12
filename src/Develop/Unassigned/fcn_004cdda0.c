#include <string.h>
#include "client_packet_queue.h"

void* __cdecl gm_FindRecordById(int);
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
	p = (void*) gm_FindRecordById(*(int*) (a1 + 0x10));
	if (p == 0)
		return -1;
	if (*(int*) ((char*) p + 0x29) != 0) {
		fcn_004be280(*(void**) ((char*) p + 0x29));
		*(int*) ((char*) p + 0x29) = 0;
	}
	n = *(int*) (a1 + 0x14);
	memcpy(buf, g_aed340, n * 64);
	node = buf + 0x40;
	prev = 0;
	i = 0;
	if (n > 0) {
		i = n;
		do {
			*(char**) (node - 8) = prev;
			*(char**) (node - 4) = node;
			prev = node - 0x40;
			node += 0x40;
		} while (--n);
	}
	*(int*) (buf + i * 0x40 - 4) = 0;
	*(void**) ((char*) p + 0x29) = fcn_004be2a0(buf);
	if (a2 != 0)
		a2[0] = 1;
	return 0;
}
