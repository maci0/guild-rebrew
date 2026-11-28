

// SIZE 0x8
#include "Develop/Unassigned/evidence_link.h"


extern Pair_99f800 cm_CrimeEvidenceLinks[0x800];

/* The scan is a goto loop tested at the top: a for or while loop gives the
 * same instructions but lays the -1 exit out ahead of the shared epilogue. */
/* ADDRESS: GOLDDE 0x004e1950 */
int __cdecl gs_AllocEvidenceSlot(int owner, int key)
{
	int found;
	int res;
	int i;

	found = 0;
	res = -1;
	i = 0;
loop:
	if (i >= 0x800) {
		goto end;
	}
	if (found == 0 && cm_CrimeEvidenceLinks[i].owner == -1 && cm_CrimeEvidenceLinks[i].key == -1) {
		res = i;
		found = 1;
	}
	if (cm_CrimeEvidenceLinks[i].owner == owner && cm_CrimeEvidenceLinks[i].key == key) {
		return -2;
	}
	i++;
	goto loop;
end:
	if (found == 0) {
		return -1;
	}
	return res;
}
