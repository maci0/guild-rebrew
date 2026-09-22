// FUNCTION: GOLDTL 0x4fffb0
// SIZE: 60

int __cdecl fcn_004fffb0(int a1)
{
	unsigned short w;
	unsigned int i;
	int v;

	i = (unsigned int) a1 & 0xffff;
	w = *(unsigned short*) (0x7f4caa + i * 540);
	v = w;
	return v < *(float*) (0x7f4cc0 + i * 540);
}
