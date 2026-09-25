// FUNCTION: GOLDTL 0x40e150
// SIZE: 65

int __cdecl fcn_0064d470(char*, int);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_0040e150(char** a1, int* a2)
{
	char* p;

	p = *a1;
	if (p == 0) {
		fcn_00425bf0(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676384);
		return 0;
	}
	return fcn_0064d470(p + 8, *a2) != 0;
}
