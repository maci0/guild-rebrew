// FUNCTION: GOLDTL 0x4737e0

int __cdecl fcn_004737e0(void)
{
	int a;
	int n;

	n = 0;
	for (a = 0x1011980; a < 0x10119c8; a += 0xc) {
		if (*(int*) a != -1) {
			n++;
		}
	}
	return n;
}
