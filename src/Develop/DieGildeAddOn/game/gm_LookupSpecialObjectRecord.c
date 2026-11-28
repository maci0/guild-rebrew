#include "offer.h"
extern Offer gm_SpecialObjectOffers[];

/* ADDRESS: GOLD 0x005ba7b0 */
/* ADDRESS: GOLDTL 0x005c6220 */
/* ADDRESS: GOLDDE 0x005a84a0 */
char* __cdecl gm_LookupSpecialObjectRecord(int key, int* out)
{
	int n;
	int v;

	v = *(int*) gm_SpecialObjectOffers;
	n = 0;
	while (v != 0) {
		if (v == key) {
			if (out != 0) {
				*out = n;
			}
			return (char*) gm_SpecialObjectOffers + n * 0x1c;
		}
		n++;
		v = *(int*) ((char*) gm_SpecialObjectOffers + n * 0x1c);
	}
	return 0;
}
