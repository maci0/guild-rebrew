
// fcn_004f97a0 — a < 5 ? [0x99f580 + a] : 0x7e (both byte returns).

/* ADDRESS: GOLDTL 0x004fbd20 */
/* ADDRESS: GOLDDE 0x004e7970 */
unsigned char __cdecl gm_GetCitySkillAverage(int a)
{
	if (a >= 5) {
		return 0x7e;
	}
	return *(unsigned char*) (0x99f580 + a);
}
