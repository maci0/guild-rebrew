// FUNCTION: GOLDTL 0x41bd80
// SIZE: 64

void __cdecl fcn_0041bd80(char* p)
{
	int i;

	for (i = 0; i < 0x100; i++) {
		p[i] = *(char*) (0x6b6008 + i);
		p[i + 0x100] = *(char*) (0x6b6108 + i);
		p[i + 0x200] = *(char*) (0x6b6208 + i);
	}
}
