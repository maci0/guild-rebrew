


#include "Develop/Unassigned/evidence_link.h"




// SIZE 0x8

#include "client_types.h"
extern Pair_99f800 g_99f800[0x800];

int __cdecl cm_ExClearEvidenceLink(char* command, char* response)
{
	int i;

	for (i = 0; i < 0x800; i++) {
		if (g_99f800[i].owner == *(int*) (command + 0x14) && g_99f800[i].key == *(int*) (command + 0x10)) {
			g_99f800[i].owner = -1;
			g_99f800[i].key = -1;
			if (response != 0) {
				*response = 1;
			}
			return 0;
		}
	}
	return 1;
}
