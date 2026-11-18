


int __cdecl gm_RemoveObjectByType(void*, int);

int __cdecl fcn_005062d0(void* object, int type)
{
	return gm_RemoveObjectByType((char*) object + 0x5d, type) == -2 ? -3 : 0;
}
