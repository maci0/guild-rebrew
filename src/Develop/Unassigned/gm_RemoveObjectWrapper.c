


int __cdecl gm_RemoveObjectByType(void*, int);

int __cdecl gm_RemoveObjectWrapper(void* object, int type)
{
	return gm_RemoveObjectByType((char*) object + 0x5d, type) == -2 ? -3 : 0;
}
