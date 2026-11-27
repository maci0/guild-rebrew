


extern float g_6628a8;
extern float g_6628a0;
extern float g_665284;

float __cdecl ahm_GetEssenceValue(int entityId, int which);

float __cdecl ahm_ConsumeEssenceCapacity(int entityId, int which, int* cap)
{
	float v;
	float d;
	int n;
	int m;

	v = ahm_GetEssenceValue(entityId, which);
	if (v < g_6628a8 || v >= g_6628a0) {
		return g_6628a8;
	}
	d = g_6628a0 - v;
	n = (int) (g_665284 * d);
	m = *cap < n ? *cap : n;
	*cap = m;
	return d * ((float) m / n);
}
