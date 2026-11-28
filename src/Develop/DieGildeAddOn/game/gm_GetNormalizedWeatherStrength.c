

extern float g_6ad634;

float __cdecl d3_ClampNormalizeFloat(float x);

/* ADDRESS: GOLDDE 0x005c9b10 */
float __cdecl gm_GetNormalizedWeatherStrength(void)
{
	return d3_ClampNormalizeFloat(g_6ad634);
}
