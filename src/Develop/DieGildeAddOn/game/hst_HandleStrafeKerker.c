char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl atoi(char*);
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
void __cdecl cm_AppendPacketFieldValue(int, int, int, char*);
void __cdecl cm_RequestChangeAttribute(void);


/* ADDRESS: GOLDTL 0x004b0a20 */
int __cdecl hst_HandleStrafeKerker(int* record, int slot, char* arg)
{
	char c = 0;
	char* e;

	if (*arg != '-')
		return 0;
	c = (char) atoi(arg + 1);
	if (record == 0 || slot >= 8)
		return 0;
	e = gm_LookupEntityRecordById(record[slot * 2 + 1]);
	if (e == 0)
		return 0;
	cm_BeginPacketFieldDelta(e, *(int*) (e + 4));
	cm_AppendPacketFieldValue(1, 1, 0x1b1, &c);
	cm_RequestChangeAttribute();
	return 1;
}
