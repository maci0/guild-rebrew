// FUNCTION: GOLDTL 0x42e340
// SIZE: 50

void __cdecl fcn_0042e260(int);

void __cdecl fcn_0042e340(void)
{
	int o;
	char* base;

	base = *(char**) 0x6b5c20;
	for (o = 0; o < 0xc5440; o += 0x194) {
		if (*(unsigned char*) (base + o + 9) != 0) {
			fcn_0042e260(*(int*) (base + o + 0x14));
			base = *(char**) 0x6b5c20;
		}
	}
}
