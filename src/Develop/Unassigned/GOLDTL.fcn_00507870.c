#include "client_packet_builder.h"
void __cdecl cm_AppendCommandSyncField(int a, int b, int c, int* d);
void __cdecl cm_SendSetAttribute(void);

/* ADDRESS: GOLDTL 0x00507870 */
int __cdecl fcn_00507870(char* e)
{
	int v;

	v = 0;
	if (*(char**) (e + 0x16c) != 0 && **(char**) (e + 0x16c) == 0x20) {
		v = 0xc;
	} else if (*(char**) (e + 0x16c) != 0 && **(char**) (e + 0x16c) == 0x1f) {
		v = 0xb;
	} else {
		v = *(unsigned char*) (e + 0x165) - 1;
	}
	cm_BeginPacketFieldDelta(e, *(int*) (e + 4));
	cm_AppendCommandSyncField(1, 1, 0x165, &v);
	cm_SendSetAttribute();
	v = 0;
	cm_BeginPacketFieldDelta(e, *(int*) (e + 4));
	cm_AppendCommandSyncField(4, 1, 0x174, &v);
	cm_SendSetAttribute();
	return -1;
}
