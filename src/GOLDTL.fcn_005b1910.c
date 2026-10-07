// FUNCTION: GOLD 0x005a8490
// FUNCTION: GOLDTL 0x5b1910

float __cdecl fcn_005b1910(int* rng)
{
	rng[1] = rng[1] * 0x41c64e6d + 0x3039;
	return (float) ((unsigned int) *(unsigned short*) ((char*) rng + 6) % 0x7fff) * 3.051850945e-05f;
}
