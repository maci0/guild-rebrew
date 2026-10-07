void __cdecl fcn_0046b2b0(int);

// FUNCTION: GOLD 0x4be8e0
// FUNCTION: GOLDTL 0x4bf150

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
