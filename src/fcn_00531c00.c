// FUNCTION: GOLDTL 0x531c00
// SIZE: 51

void __cdecl fcn_00531c00(int a1)
{
	int i;
	int a;

	for (i = 0, a = 0x7e6068; a < 0x7ea368; a += 0x10c, i++) {
		if (*(int*) a == a1) {
			*(int*) (0x7e6068 + i * 268) = 0;
			return;
		}
	}
}
