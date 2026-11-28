extern float gm_TargetCityPopulation;
extern float gm_TargetCityPopulation;
extern char dbl_0_006[];
extern char dbl_0_006[];

/* ADDRESS: GOLD 0x0047dcf0 */
/* ADDRESS: GOLDTL 0x0047d1b0 */
int __cdecl ai_GetMaxActiveTradeActions(void)
{
	int v;

	v = (int) (*(float*) ((char*)&gm_TargetCityPopulation) * *(double*) dbl_0_006);
	if (v < 5) {
		return 5;
	}
	if (v > 0x10) {
		return 0x10;
	}
	return v;
}
