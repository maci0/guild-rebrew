// FUNCTION: GOLDTL 0x465540
long __cdecl fcn_00465540(char* s)
{
	char* p;

	if (s == 0) {
		return -102;
	}
	p = *(char**) (s + 0x7c);
	if (p == 0) {
		return -102;
	}
	return *(long*) (p + 0x18);
}
