#include "offer.h"



extern Offer g_6abb08[];

char* __cdecl gm_LookupSpecialObject(int id)
{
	int index;
	int entryId;

	entryId = *(int*) g_6abb08;
	index = 0;
	while (entryId != 0) {
		if (entryId == id) {
			return (char*) g_6abb08 + index * 0x1c;
		}
		index++;
		entryId = *(int*) ((char*) g_6abb08 + index * 0x1c);
	}
	return 0;
}
