// FUNCTION: GOLD 0x4c6a20
// SIZE: 48
// FUNCTION: GOLDTL 0x4c75b0
// SIZE: 42

int __cdecl fcn_004c75b0(char* p, char* out)
{
	char c;

	c = *p;
	if (c != 0 && c != 5 && c != 6 && c != 7) {
		return 1;
	}
	if (out != 0) {
		*out = 1;
	}
	return 0;
}
