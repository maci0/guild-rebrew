// FUNCTION: GOLDTL 0x4107b0

int __cdecl fcn_0041dd90(void*);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_004107b0(char** a1)
{
	char* p;

	p = *a1;
	if (fcn_0041dd90(p) == 0) {
		fcn_00425bf0(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676cf8);
		return 0;
	}
	p[0xd5] |= 2;
	return 0;
}
