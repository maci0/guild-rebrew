void __cdecl fcn_00445aa0(int a, unsigned int i, float f);

// FUNCTION: GOLD 0x00449da0
// FUNCTION: GOLDTL 0x445d20
char __cdecl fcn_00445d20(int a, float* v)
{
	float x;
	unsigned int i;

	x = *v;
	i = (unsigned int) x;
	fcn_00445aa0(a, i, x - i);
	return 1;
}
