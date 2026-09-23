// FUNCTION: GOLDTL 0x5338a0
// SIZE: 34

void __cdecl fcn_005338a0(void)
{
	int a;

	for (a = 0x7e46c0; a < 0x7e5fc0; a += 0xc8) {
		if (*(int*) a != 0) {
			*(int*) (*(int*) a + 0x224) = 0;
		}
		*(int*) a = 0;
	}
}
