


extern float flt_0_0;
extern float flt_1_0;
extern float g_665284;

float __cdecl ahm_GetEssenceValue(int entityId, int which);

float __cdecl ahm_ConsumeEssenceCapacity(int entityId, int which, int* cap)
{
	float v;
	float d;
	int n;
	int m;

	v = ahm_GetEssenceValue(entityId, which);
	if (v < flt_0_0 || v >= flt_1_0) {
		return flt_0_0;
	}
	d = flt_1_0 - v;
	n = (int) (g_665284 * d);
	m = *cap < n ? *cap : n;
	*cap = m;
	return d * ((float) m / n);
}
