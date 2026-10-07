extern float g_662d34;
extern float g_6628d8;
extern float g_6628cc;
// FUNCTION: GOLD 0x504e80
// FUNCTION: GOLDTL 0x507ed0

float __cdecl fcn_00507ed0(float a, float b)
{
	return (((a - b * b) * g_662d34 + g_6628d8)
	      + ((a * a - b) * g_6628d8 + g_662d34)) * g_6628cc;
}
