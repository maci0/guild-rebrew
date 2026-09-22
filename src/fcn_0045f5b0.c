// FUNCTION: GOLDTL 0x45f5b0
// SIZE: 39

int __cdecl gzread(int, void*, unsigned);

int __cdecl fcn_0045f5b0(int a1)
{
	char c;

	if (gzread(a1, &c, 1) == 1) {
		return c & 0xff;
	}
	return -1;
}
