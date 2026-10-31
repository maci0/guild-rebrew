


unsigned short* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_005077c0(int, int);
void __cdecl fcn_004fdfe0(unsigned short*);

int __cdecl fcn_004cc530(char* a1, char* a2)
{
	unsigned short* p;

	p = gm_LookupEntityRecordById(*(int*) (a1 + 0x10));
	if (p == 0) {
		return 1;
	}
	fcn_005077c0(*p, *(unsigned char*) (a1 + 0x14));
	fcn_004fdfe0(p);
	if (a2 != 0) {
		a2[0] = 1;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	return 0;
}
