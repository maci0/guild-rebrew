


unsigned short* __cdecl gm_QueryEntities(int, int, int, int, int);
int __cdecl gm_LookupSpecialObject(unsigned int);

/* ADDRESS: GOLDDE 0x005a8540 */
int __cdecl gm_HasActiveSpecialObjectOnEntity(char* entity, int objekt_id)
{
	unsigned short* obj;

	obj = gm_QueryEntities(0, 2, 7, 0, objekt_id);
	if (obj != 0 && gm_LookupSpecialObject(*obj) != 0 && *(int*) ((char*) obj + 0x21) != 0 &&
	    *(int*) ((char*) obj + 0x25) == *(int*) (entity + 1)) {
		return 1;
	}
	return 0;
}
