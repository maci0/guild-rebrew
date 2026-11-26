


unsigned short* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl gm_LookupSpecialObject(unsigned int);

int __cdecl gm_HasActiveSpecialObjectOnEntity(char* entity, int objekt_id)
{
	unsigned short* obj;

	obj = fcn_00502cd0(0, 2, 7, 0, objekt_id);
	if (obj != 0 && gm_LookupSpecialObject(*obj) != 0 && *(int*) ((char*) obj + 0x21) != 0 &&
	    *(int*) ((char*) obj + 0x25) == *(int*) (entity + 1)) {
		return 1;
	}
	return 0;
}
