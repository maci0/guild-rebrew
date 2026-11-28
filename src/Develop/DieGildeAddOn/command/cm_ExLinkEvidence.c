


#include "Develop/Unassigned/evidence_link.h"




// SIZE 0x8

#include "Develop/client_types.h"
extern Pair_99f800 g_99f800[0x800];

int __cdecl gs_AllocEvidenceSlot(int, int);

int __cdecl cm_ExLinkEvidence(char* cmd, char* response)
{
	int index;

	index = gs_AllocEvidenceSlot(*(int*) (cmd + 0x14), *(int*) (cmd + 0x10));
	if (index > -1) {
		g_99f800[index].owner = *(int*) (cmd + 0x14);
		g_99f800[index].key = *(int*) (cmd + 0x10);
	}
	if (response != 0) {
		*response = 1;
	}
	return 0;
}
