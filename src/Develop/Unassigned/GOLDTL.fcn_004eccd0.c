


extern float g_6628a0;
extern float g_665280;
extern float g_6628cc;

float __cdecl ahm_GetEssenceValue(char*, int);

int __cdecl fcn_004eccd0(char* a1, char* a2)
{
	int t;

	t = 0x3840 - (int) ((g_6628a0 - *(float*) (a2 + 4)) * g_665280);
	return t - (int) (ahm_GetEssenceValue(a1, 0) * t * g_6628cc);
}
