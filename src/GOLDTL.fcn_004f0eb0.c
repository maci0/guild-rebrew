extern float g_6628a8;
extern float g_6628bc;
extern float g_6628cc;
extern float g_662da8;
extern float g_662a3c;
extern float g_662b28;

/* ADDRESS: GOLDTL 0x004f0eb0 */
float __cdecl fcn_004f0eb0(int level, int percent, int count)
{
	float step;
	float sum;
	float k;

	if (level >= 4) {
		level = 4;
	}
	else if (level <= 0) {
		level = 0;
	}
	k = level + 1;
	if (percent >= 100) {
		percent = 100;
	}
	else if (percent <= 0) {
		percent = 0;
	}
	if (count >= 3) {
		count = 3;
	}
	else if (count <= 1) {
		count = 1;
	}
	step = k * (percent * g_6628bc + g_662da8) * g_662b28 + g_662a3c;
	sum = g_6628a8;
	while (count-- > 0) {
		sum += step;
		step *= g_6628cc;
	}
	return sum;
}
