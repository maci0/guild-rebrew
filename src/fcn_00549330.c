// FUNCTION: GOLDTL 0x549330
// SIZE: 47

void __cdecl fcn_00549330(char* p, int a2)
{
	*(unsigned short*) (p + 8) = (unsigned short) a2;
	if (a2 != 0xffff) {
		*(int*) (p + 0xc) = *(int*) (0x7f4ca4 + a2 * 540);
		return;
	}
	*(int*) (p + 0xc) = -1;
}
