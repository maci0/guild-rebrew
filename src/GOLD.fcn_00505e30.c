// FUNCTION: GOLD 0x00505e30
// fcn_00505e30 — float of short [0x770b8a + (a&0xffff)*540].

float __cdecl fcn_00505e30(int a)
{
	return (float) (unsigned short) *(unsigned short*) (0x770b8a + (a & 0xffff) * 540);
}
