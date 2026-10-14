extern float g_662d34;
extern float g_6628d8;
extern float g_6628cc;
/* ADDRESS: GOLD 0x00504e80 */
/* ADDRESS: GOLDTL 0x00507ed0 */

float __cdecl fcn_00507ed0(float a, float b)
{
	return (((a - b * b) * g_662d34 + g_6628d8)
	      + ((a * a - b) * g_6628d8 + g_662d34)) * g_6628cc;
}
