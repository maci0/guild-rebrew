char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl atoi(char*);
#include "client_packet_builder.h"
void __cdecl fcn_004c4670(int, int, int, char*);
void __cdecl fcn_004c5360(void);


/* ADDRESS: GOLDTL 0x004b0a20 */
int __cdecl fcn_004b0a20(int* a1, int slot, char* arg)
{
	char c = 0;
	char* e;

	if (*arg != '-')
		return 0;
	c = (char) atoi(arg + 1);
	if (a1 == 0 || slot >= 8)
		return 0;
	e = gm_LookupEntityRecordById(a1[slot * 2 + 1]);
	if (e == 0)
		return 0;
	cm_BeginPacketFieldDelta(e, *(int*) (e + 4));
	fcn_004c4670(1, 1, 0x1b1, &c);
	fcn_004c5360();
	return 1;
}
