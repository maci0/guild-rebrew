extern char gm_EntityIdField[];
#include "Develop/client_types.h"

int __cdecl amt_GetRoleTemplate(int idx, Rec18_68da68* out);
char* __cdecl gm_LookupEntityRecordById(int id);

/* ADDRESS: GOLDTL 0x00508f80 */
/* ADDRESS: GOLDDE 0x004f4100 */
int __cdecl gm_GetEntityOfficeRank(unsigned short slotId, int directOnly)
{
	Rec18_68da68 rec;
	int value;
	char* entity;
	int idx;

	idx = slotId * 0x21c;
	if (*(int*) ((int) &gm_EntityIdField + idx) == -1 || *(unsigned char*) (((int) &gm_EntityIdField + 0x4) + idx) <= 0)
		return 0;
	if (!amt_GetRoleTemplate(*(unsigned char*) (((int) &gm_EntityIdField + 0x163) + idx), &rec))
		return 1;
	value = (*(unsigned int*) ((char*) &rec + 8) & 0xff) + 1;
	if ((char) *(unsigned int*) ((char*) &rec + 8) == '\n')
		return value;
	if (directOnly != 0)
		return value;
	entity = gm_LookupEntityRecordById(*(int*) (((int) &gm_EntityIdField + 0x5c) + idx));
	if (entity != 0) {
		if (value > gm_GetEntityOfficeRank(*(unsigned short*) entity, 1))
			return value;
		return gm_GetEntityOfficeRank(*(unsigned short*) entity, 1);
	}
	return value;
}
