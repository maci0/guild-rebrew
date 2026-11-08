


int __cdecl gm_RemoveObjectByType(void*, int);

int __cdecl fcn_005062d0(void* a1, int a2)
{
	return gm_RemoveObjectByType((char*) a1 + 0x5d, a2) == -2 ? -3 : 0;
}
