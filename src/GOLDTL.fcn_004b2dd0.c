int __cdecl fcn_004b20e0(int, int);
int __cdecl fcn_004b2a10(int, int);
void __cdecl fcn_004b2670(int);

// FUNCTION: GOLD 0x4b2c90
// FUNCTION: GOLDTL 0x4b2dd0

int __cdecl fcn_004b2dd0(int a, int b, int c)
{
	if (fcn_004b20e0(a, b + 1) == 0)
		return 0;
	b += 2;
	if (fcn_004b2a10(a, b) == 0)
		return 0;
	if (c != 0)
		fcn_004b2670(b);
	return 1;
}
