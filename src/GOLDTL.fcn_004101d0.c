// FUNCTION: GOLDTL 0x4101d0

int __cdecl fcn_0041dd90(void*);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_004101d0(char** a1, int* a2, int* a3, int* a4)
{
	char* p;

	p = *a1;
	if (fcn_0041dd90(p) == 0) {
		fcn_00425bf0(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676ac0);
		return 0;
	}
	*(float*) (p + 0x68) = (float) *a2;
	*(float*) (p + 0x6c) = (float) *a3;
	*(float*) (p + 0x70) = (float) *a4;
	return 0;
}
