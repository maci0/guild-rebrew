extern char gm_EntityIdField[];
#include "Develop/client_types.h"

int __cdecl amt_GetRoleTemplate(int idx, Rec18_68da68* out);
char* __cdecl gm_LookupEntityRecordById(int a1);

/* ADDRESS: GOLDTL 0x00508eb0 */
/* ADDRESS: GOLDDE 0x004f4030 */
int __cdecl amt_GetEffectiveRoleLevel(unsigned short id, int a1)
{
	Rec18_68da68 rec;
	int level;
	char* entity;
	int idx;

	idx = id * 0x21c;
	if (*(int*) ((int) &gm_EntityIdField + idx) == -1 || *(unsigned char*) (((int) &gm_EntityIdField + 0x4) + idx) <= 0)
		return 0;
	if (!amt_GetRoleTemplate(*(unsigned char*) (((int) &gm_EntityIdField + 0x162) + idx), &rec))
		return 1;
	level = (*(unsigned int*) ((char*) &rec + 8) & 0xff) + 1;
	if ((char) *(unsigned int*) ((char*) &rec + 8) == '\n')
		return level;
	if (a1 != 0)
		return level;
	entity = gm_LookupEntityRecordById(*(int*) (((int) &gm_EntityIdField + 0x5c) + idx));
	if (entity != 0) {
		if (level > amt_GetEffectiveRoleLevel(*(unsigned short*) entity, 1))
			return level;
		return amt_GetEffectiveRoleLevel(*(unsigned short*) entity, 1);
	}
	return level;
}
