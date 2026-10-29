#ifdef REBREW_GOLD
#define fcn_0046b2b0 fcn_0046e700
#endif
void __cdecl fcn_0046b2b0(int);


/* ADDRESS: GOLDTL 0x004bf150 */
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
