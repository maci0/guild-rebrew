#include <string.h>
#include "client_packet_queue.h"

void* __cdecl gm_FindRecordById(int);
void __cdecl rt_FreeRoutePoints(void*);
void* __cdecl rt_CloneRoutePoints(void*);

/* ADDRESS: GOLDTL 0x004cdda0 */
int __cdecl cm_ExSetEntityRoute(char* command, unsigned char* response, unsigned char* unused)
{
	char buf[0x240];
	void* p;
	char* prev = 0;
	char* node;
	int n;
	int i;

	if (response != 0) {
		response[0] = 2;
		response[1] = 0;
		*(int*) (response + 6) = 0;
	}
	p = (void*) gm_FindRecordById(*(int*) (command + 0x10));
	if (p == 0)
		return -1;
	if (*(int*) ((char*) p + 0x29) != 0) {
		rt_FreeRoutePoints(*(void**) ((char*) p + 0x29));
		*(int*) ((char*) p + 0x29) = 0;
	}
	n = *(int*) (command + 0x14);
	memcpy(buf, g_aed340, n * 64);
	node = buf;

	for (i = 0; i < n; i++) {
		*(char**) (node + 0x38) = prev;
		*(char**) (node + 0x3c) = node + 0x40;
		prev = node;
		node += 0x40;
	}
	*(int*) (buf + i * 0x40 - 4) = 0;
	*(void**) ((char*) p + 0x29) = rt_CloneRoutePoints(buf);
	if (response != 0)
		response[0] = 1;
	return 0;
}
