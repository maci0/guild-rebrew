


#include "Develop/Unassigned/evidence_link.h"




// SIZE 0x8

#include "Develop/client_types.h"
extern Pair_99f800 cm_CrimeEvidenceLinks[0x800];

/* ADDRESS: GOLDDE 0x004b7490 */
int __cdecl cm_ExClearEvidenceLink(char* command, char* response)
{
	int i;

	for (i = 0; i < 0x800; i++) {
		if (cm_CrimeEvidenceLinks[i].owner == *(int*) (command + 0x14) && cm_CrimeEvidenceLinks[i].key == *(int*) (command + 0x10)) {
			cm_CrimeEvidenceLinks[i].owner = -1;
			cm_CrimeEvidenceLinks[i].key = -1;
			if (response != 0) {
				*response = 1;
			}
			return 0;
		}
	}
	return 1;
}
