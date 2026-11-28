


void* __cdecl gm_QueryEntities(int, int, int, int);
int __cdecl gm_LookupSpecialObject(int);

/* ADDRESS: GOLDDE 0x005a84f0 */
int __cdecl gm_HasActiveSpecialObject(char* entity, int objId)
{
	char* match;

	match = (char*) gm_QueryEntities(*(int*) (entity + 0x178), 1, 0, objId);
	if (match != 0) {
		if (gm_LookupSpecialObject(*(unsigned short*) match) != 0) {
			if (*(int*) (match + 0x21) != 0) {
				return 1;
			}
		}
	}
	return 0;
}
