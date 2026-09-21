// FUNCTION: GOLD 0x005024f0
// SIZE: 42
// fcn_005024f0 — table[[0x7e3f30] + a[0] + a[0]*588] == 0xa.

int __cdecl fcn_005024f0(char* a)
{
	int c;
	c = (unsigned char) a[0];
	return *(unsigned char*) ((char*) *(char**) 0x7e3f30 + c + c * 588) == 0xa;
}
