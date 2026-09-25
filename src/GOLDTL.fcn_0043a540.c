void __cdecl fcn_0043a3f0(char* a, char* e, int v);

// FUNCTION: GOLDTL 0x43a540
// SIZE: 89
char __cdecl fcn_0043a540(char* a, int* v)
{
	unsigned int i;

	if (*(char**) (a + 0x1ec) != 0) {
		for (i = 0; i < *(unsigned char*) (*(char**) (a + 0x1ec) + 0x163c); i++) {
			fcn_0043a3f0(a, *(char**) (a + 0x1ec) + i * 0x4a4 + 0xf4, *v);
		}
	}
	return 1;
}
