#include "client_scene_resources.h"

/* ADDRESS: GOLD 0x00461130 */
unsigned char __cdecl fcn_00461130(SCENE_RESOURCE* resource)
{
	char* s;
	void* p;

	s = (char*) resource;

	if (s == 0)
		return 0;
	if (*(unsigned char *)0x633450 == 0)
		return 0;
	if ((*(unsigned char *)(s + 0x68) & 2) != 0)
		return 0;
	p = *(void **)(s + 0x60);
	if (p != 0) {
		*(int *)0x146356c = ((int (__stdcall *)(void*))(*(void ***)p)[2])(p);
		*(int *)(s + 0x60) = 0;
	}
	p = *(void **)(s + 0x64);
	if (p != 0) {
		*(int *)0x146356c = ((int (__stdcall *)(void*))(*(void ***)p)[2])(p);
		*(int *)(s + 0x64) = 0;
	}
	if (*(int *)(s + 0x4c) != 0 && *(unsigned char *)s != 0x2a)
		fcn_00460e40(resource, 0);
	return 0;
}
