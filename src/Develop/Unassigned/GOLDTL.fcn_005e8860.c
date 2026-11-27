

extern float g_6ad634;

float __cdecl d3_ClampNormalizeFloat(float x);

float __cdecl gm_GetNormalizedWeatherStrength(void)
{
	return d3_ClampNormalizeFloat(g_6ad634);
}
