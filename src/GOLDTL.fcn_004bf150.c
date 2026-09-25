void __cdecl fcn_0046b2b0(int);

// FUNCTION: GOLDTL 0x4bf150
// SIZE: 77

void __cdecl fcn_004bf150(int* p)
{
	if (p[0] != -1)
		fcn_0046b2b0(p[0]);
	if (p[1] != -1)
		fcn_0046b2b0(p[1]);
	if (p[2] != -1)
		fcn_0046b2b0(p[2]);
	p[0] = -1;
	p[1] = -1;
	p[2] = -1;
}
