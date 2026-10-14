

int __cdecl fcn_0064d470(const char*, const char*);

void __cdecl fcn_00515ef0(char* e)
{
	if (fcn_0064d470(e, "gate")) {
		e[0x214] &= 0xbf;
		*(int*) (e + 0x224) = 1;
	} else {
		*(int*) (e + 0x224) = 0;
	}
}
