// FUNCTION: GOLDTL 0x4737c0

void __cdecl fcn_004737c0(void)
{
	int a;

	for (a = 0x1011980; a < 0x10119c8; a += 0xc) {
		*(int*) (a + 4) = 0;
		*(int*) a = -1;
	}
}
