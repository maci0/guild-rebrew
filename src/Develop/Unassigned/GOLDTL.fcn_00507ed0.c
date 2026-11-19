extern float g_662d34;
extern float g_6628d8;
extern float g_6628cc;

/* ADDRESS: GOLDTL 0x00507ed0 */
float __cdecl fcn_00507ed0(float a, float b)
{
	return (((a - b * b) * 0.6f + 0.4f)
	      + ((a * a - b) * 0.4f + 0.6f)) * g_6628cc;
}
