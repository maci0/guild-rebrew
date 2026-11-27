extern float g_6628a8;
extern float g_6628bc;
extern float g_6628cc;
extern float g_662da8;
extern float g_662a3c;
extern float g_662b28;

/* ADDRESS: GOLDTL 0x004f0eb0 */
float __cdecl gm_CalcArtilleryVolleyCost(int level, int percent, int count)
{
	float step;
	float sum;
	int k;
	int pc;
	double percent_term;

	if (level < 4) {
		if (level <= 0) {
			level = 0;
		}
	}
	else {
		level = 4;
	}
	k = level + 1;
	if (percent < 100) {
		pc = percent;
		if (percent <= 0) {
			pc = 0;
		}
	}
	else {
		pc = 100;
	}
	percent_term = pc * 0.25f + 25.0f;
	if (count < 3) {
		if (count <= 1) {
			count = 1;
		}
	}
	else {
		count = 3;
	}
	step = k * percent_term * g_662b28 + g_662a3c;
	sum = g_6628a8;
	while (count-- > 0) {
		sum += step;
		step *= 0.5f;
	}
	return sum;
}
