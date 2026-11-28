


int __cdecl gm_RemoveObjectByType(void*, int);

/* ADDRESS: GOLDDE 0x004f1650 */
int __cdecl gm_RemoveObjectWrapper(void* object, int type)
{
	return gm_RemoveObjectByType((char*) object + 0x5d, type) == -2 ? -3 : 0;
}
