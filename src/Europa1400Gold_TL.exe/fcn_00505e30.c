// FUNCTION: GOLDTL 0x508e80
// SIZE: 37

// fcn_00505e30 — float of short [0x7f4caa + (a&0xffff)*540].

float __cdecl fcn_00505e30(int a)
{
	return (float) (unsigned short) *(unsigned short*) (0x7f4caa + (a & 0xffff) * 540);
}
