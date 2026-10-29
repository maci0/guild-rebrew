
// fcn_00505e30 — float of short [0x7f4caa + (a&0xffff)*540].

/* ADDRESS: GOLDTL 0x00508e80 */
float __cdecl fcn_00505e30(int a)
{
	return (float) (unsigned short) *(unsigned short*) (0x7f4caa + (a & 0xffff) * 540);
}
