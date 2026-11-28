#include "offer.h"



extern Offer gm_SpecialObjectOffers[];

char* __cdecl gm_LookupSpecialObject(int id)
{
	int index;
	int entryId;

	entryId = *(int*) gm_SpecialObjectOffers;
	index = 0;
	while (entryId != 0) {
		if (entryId == id) {
			return (char*) gm_SpecialObjectOffers + index * 0x1c;
		}
		index++;
		entryId = *(int*) ((char*) gm_SpecialObjectOffers + index * 0x1c);
	}
	return 0;
}
