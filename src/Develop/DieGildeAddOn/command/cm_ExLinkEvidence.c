


#include "Develop/Unassigned/evidence_link.h"




// SIZE 0x8

#include "Develop/client_types.h"
extern Pair_99f800 cm_CrimeEvidenceLinks[0x800];

int __cdecl gs_AllocEvidenceSlot(int, int);

/* ADDRESS: GOLDDE 0x004b7450 */
int __cdecl cm_ExLinkEvidence(char* cmd, char* response)
{
	int index;

	index = gs_AllocEvidenceSlot(*(int*) (cmd + 0x14), *(int*) (cmd + 0x10));
	if (index > -1) {
		cm_CrimeEvidenceLinks[index].owner = *(int*) (cmd + 0x14);
		cm_CrimeEvidenceLinks[index].key = *(int*) (cmd + 0x10);
	}
	if (response != 0) {
		*response = 1;
	}
	return 0;
}
