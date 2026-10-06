// FUNCTION: GOLDTL 0x500db0

void __cdecl fcn_00500db0(char* p, char* q)
{
	*(int*) q = *(short*) (p + 2) - 0x578;
	*(unsigned short*) (q + 4) = (unsigned short) *(char*) (p + 4);
	*(int*) (q + 6) = *(signed char*) (p + 5);
	*(int*) (q + 0xa) = *(int*) (p + 6);
}
