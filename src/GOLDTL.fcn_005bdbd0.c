// FUNCTION: GOLDTL 0x5bdbd0

int __cdecl fcn_0064d470(char*, void*);

char __cdecl fcn_005bdbd0(char* obj, char* list)
{
	if (fcn_0064d470(obj, (void*) 0x6ac430) != 0) {
		((char**) list)[*(int*) (list + 0x400)] = obj;
		((int*) list)[*(int*) (list + 0x400) + 0x80] = 0x16;
		*(int*) (list + 0x400) = *(int*) (list + 0x400) + 1;
	}
	return *(int*) (list + 0x400) < 0x80;
}
