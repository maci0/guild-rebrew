// FUNCTION: GOLDTL 0x4e6b40
// SIZE: 38

void __cdecl fcn_004e6b10(int);

void __cdecl fcn_004e6b40(void)
{
	int a;

	for (a = 0x9a9660; a < 0x9afde0; a += 0x114) {
		if (*(int*) a != -1) {
			fcn_004e6b10(*(int*) a);
		}
	}
}
