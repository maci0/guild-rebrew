


extern float flt_1_0;
extern float g_665280;
extern float g_6628cc;

float __cdecl ahm_GetEssenceValue(char*, int);

/* ADDRESS: GOLDDE 0x004d9120 */
int __cdecl ahm_CalcResearchDuration(char* entity, char* recipe)
{
	int t;

	t = 0x3840 - (int) ((flt_1_0 - *(float*) (recipe + 4)) * g_665280);
	return t - (int) (ahm_GetEssenceValue(entity, 0) * t * g_6628cc);
}
