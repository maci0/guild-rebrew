#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

extern float g_666100;

/* ADDRESS: GOLDTL 0x005ea460 */
/* ADDRESS: GOLDDE 0x005caf80 */
float __cdecl d3_ClampNormalizeFloat(float x)
{
	return MAX(MIN(x, g_666100), 0.0f) / g_666100;
}
