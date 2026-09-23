// FUNCTION: GOLDTL 0x546f80
// SIZE: 37

void __cdecl fcn_00546f80(void)
{
	int a;
	signed char* p;

	for (a = 0x7dcae0; a < 0x7e1ae0; a += 0x50) {
		p = (signed char*) a;
		*p = (signed char) (*p - 1);
		if (*p <= 0) {
			*(int*) (a + 8) = 0;
			*(int*) (a + 0xc) = 0;
			*(char*) (a + 0x10) = 0;
		}
	}
}
