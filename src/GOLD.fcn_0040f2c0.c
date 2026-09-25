// FUNCTION: GOLD 0x40f2c0
// SIZE: 81

int __cdecl fcn_0041dd90(void*);
void __cdecl fcn_004273d0(void*, int, char*);

int __cdecl fcn_0040f2c0(char** a1, int* a2, int* a3, int* a4)
{
	char* p;

	p = *a1;
	if (fcn_0041dd90(p) == 0) {
		fcn_004273d0(*(void**) 0x6332b8, *(int*) ((char*) *(void**) 0x6332b8 + 0x118), (char*) 0x5f2a40);
		return 0;
	}
	*(float*) (p + 0x60) = (float) *a2;
	*(float*) (p + 0x64) = (float) *a3;
	*(float*) (p + 0x68) = (float) *a4;
	return 0;
}
