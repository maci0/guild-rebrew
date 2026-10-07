// FUNCTION: GOLD 0x0040d6e0
// FUNCTION: GOLDTL 0x40e610

int __cdecl fcn_0064d470(char*, char*);

int __cdecl fcn_0040e610(char* s, char* p)
{
	if (fcn_0064d470(s, p + 0x84) != 0) {
		((char**) p)[*(int*) (p + 0x80)] = s;
		(*(int*) (p + 0x80))++;
	}
	return *(int*) (p + 0x80) < 0x20;
}
