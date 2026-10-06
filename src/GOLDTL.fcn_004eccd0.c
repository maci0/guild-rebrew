// FUNCTION: GOLD 0x004eaf50
// FUNCTION: GOLDTL 0x4eccd0

extern float g_6628a0;
extern float g_665280;
extern float g_6628cc;

float __cdecl fcn_004ec8a0(char*, int);

int __cdecl fcn_004eccd0(char* a1, char* a2)
{
	int t;

	t = 0x3840 - (int) ((g_6628a0 - *(float*) (a2 + 4)) * g_665280);
	return t - (int) (fcn_004ec8a0(a1, 0) * t * g_6628cc);
}
