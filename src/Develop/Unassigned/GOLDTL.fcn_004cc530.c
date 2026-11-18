


unsigned short* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_005077c0(int, int);
void __cdecl fcn_004fdfe0(unsigned short*);

int __cdecl fcn_004cc530(char* command, char* result)
{
	unsigned short* p;

	p = gm_LookupEntityRecordById(*(int*) (command + 0x10));
	if (p == 0) {
		return 1;
	}
	fcn_005077c0(*p, *(unsigned char*) (command + 0x14));
	fcn_004fdfe0(p);
	if (result != 0) {
		result[0] = 1;
		result[1] = 0;
		*(int*) (result + 6) = 0;
	}
	return 0;
}
