/* ADDRESS: GOLD 0x004f97a0 */
unsigned char __cdecl gm_GetCitySkillAverage(int index)
{
	if (index >= 5) {
		return 0x7e;
	}
	return *(unsigned char*) (0x91b460 + index);
}
