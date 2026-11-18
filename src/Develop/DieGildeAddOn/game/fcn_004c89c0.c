#include <string.h>

int __cdecl fcn_004c4dc0(char*, int);
char* __cdecl gm_AllocObjekt(int parent_id, int type, int param3);

/* ADDRESS: GOLDTL 0x004c89c0 */
int __cdecl fcn_004c89c0(char* packet, char* response)
{
	char* p;
	int parentId;

	if (*(int*) 0x14cbca0 != -1) {
		*(int*) 0x699364 = *(int*) (packet + 0x35);
	}
	parentId = fcn_004c4dc0(packet, *(int*) (packet + 0x10));
	*(int*) (packet + 0x10) = parentId;
	p = gm_AllocObjekt(parentId, *(unsigned short*) (packet + 0x14), 1);
	if (p == 0) {
		return 1;
	}
	*(int*) 0x68a9d8 = *(int*) (p + 2);
	memcpy(p + 0x1c, packet + 0x16, 0x1f);
	if (response != 0) {
		*response = 1;
	}
	return 0;
}
