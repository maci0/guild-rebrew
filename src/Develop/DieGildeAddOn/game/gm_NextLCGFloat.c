
/* ADDRESS: GOLDTL 0x005b1910 */
/* ADDRESS: GOLDDE 0x00596310 */
float __cdecl gm_NextLCGFloat(int* rng)
{
	rng[1] = rng[1] * 0x41c64e6d + 0x3039;
	return (float) ((unsigned int) *(unsigned short*) ((char*) rng + 6) % 0x7fff) * 3.051850945e-05f;
}
