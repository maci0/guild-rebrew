


#include "Develop/Unassigned/evidence_link.h"




// SIZE 0x8

#include "Develop/client_types.h"
extern Pair_99f800 cm_CrimeEvidenceLinks[0x800];
extern char g_6903a8[];

int __cdecl gs_AllocEvidenceSlot(int b, int a);
int __cdecl sprintf(char* buf, const char* fmt, ...);

/* ADDRESS: GOLDDE 0x004e1810 */
int __cdecl gs_AddBeweis(int a, int b)
{
	char buf[0x200];
	int k;

	k = gs_AllocEvidenceSlot(b, a);
	if (k > -1) {
		cm_CrimeEvidenceLinks[k].owner = b;
		cm_CrimeEvidenceLinks[k].key = a;
		sprintf(buf, g_6903a8, b, a, k);
		return 1;
	}
	return 0;
}
