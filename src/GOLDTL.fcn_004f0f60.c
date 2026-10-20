extern float g_6628bc;
extern float g_664330;
extern float g_664154;
extern float g_6652cc;
extern float g_6628a0;

/* ADDRESS: GOLDTL 0x004f0f60 */
void __cdecl fcn_004f0f60(int level, int* out)
{
	float base; float p; float x; int i;
	if (level < 4) { if (level <= 0) { level = 0; } } else { level = 4; }
	out[0] = level;
	out[1] = level + 2;
	base = level * g_6628bc + g_6628a0;
	for (i = 1; i <= 3; i++) {
		p = i * base;
		x = g_664330 * p;
		out[i + 1] = (int)(x * g_664154);
		out[i + 4] = (int)(p * g_6652cc * g_664154);
	}
}
