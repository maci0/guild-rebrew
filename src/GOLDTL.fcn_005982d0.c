

int __cdecl fcn_0064d470(char*, void*);

char __cdecl fcn_005982d0(char* obj, char* list)
{
	char* p;

	if (fcn_0064d470(obj, (void*) 0x68d6f8) != 0) {
		p = *(char**) (obj + 0x1fc);
		if (p == 0 || *(int*) (p + 0x220) != 1) {
			((char**) list)[*(int*) (list + 0x80)] = obj;
			*(int*) (list + 0x80) = *(int*) (list + 0x80) + 1;
		}
	}
	return *(int*) (list + 0x80) < 0x20;
}
