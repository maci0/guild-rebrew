extern char nt_ClientSocket[];
extern char g_699364[];
extern char g_68a9d8[];
#include <string.h>

int __cdecl cm_ResolveSpecialEntityId(char*, int);
char* __cdecl gm_AllocObjekt(int parent_id, int type, int param3);

/* ADDRESS: GOLDTL 0x004c89c0 */
/* ADDRESS: GOLDDE 0x004b61a0 */
int __cdecl cm_ExAllocObjektCmd(char* packet, char* response)
{
	char* p;
	int parentId;

	if (*(int*) &nt_ClientSocket != -1) {
		*(int*) &g_699364 = *(int*) (packet + 0x35);
	}
	parentId = cm_ResolveSpecialEntityId(packet, *(int*) (packet + 0x10));
	*(int*) (packet + 0x10) = parentId;
	p = gm_AllocObjekt(parentId, *(unsigned short*) (packet + 0x14), 1);
	if (p == 0) {
		return 1;
	}
	*(int*) &g_68a9d8 = *(int*) (p + 2);
	memcpy(p + 0x1c, packet + 0x16, 0x1f);
	if (response != 0) {
		*response = 1;
	}
	return 0;
}
