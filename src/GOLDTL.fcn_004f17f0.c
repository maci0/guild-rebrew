// FUNCTION: GOLDTL 0x4f17f0
// SIZE: 33

int __cdecl fcn_004f17f0(char* a1, char* a2)
{
	unsigned short v;

	v = *(unsigned short*) (a1 + 0x50);
	if (*(unsigned short*) (a2 + 8) == v && v != 0x7fff) {
		return 1;
	}
	return 0;
}
