// FUNCTION: GOLD 0x58fef0
// FUNCTION: GOLDTL 0x005987c0

double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
void __cdecl fcn_00455350(int, int, float*);

int __cdecl fcn_005987c0(float* pos, int* list)
{
	float best;
	float v[4];
	float p[4];
	float dx;
	float dy;
	float dz;
	float d;
	int res;
	int i;

	res = 0;
	best = 1.0e8f;
	p[0] = pos[0];
	p[1] = 0;
	p[2] = pos[2];
	for (i = 0; i < 256; i++) {
		if (list[i] != 0) {
			fcn_00455350(list[i], list[i] + 0x4c, v);
			v[1] = 0;
			dx = v[0] - p[0];
			dy = v[1] - p[1];
			dz = v[2] - p[2];
			d = (float) sqrt(dx * dx + dy * dy + dz * dz);
			if (d < best && d < 100.0) {
				best = d;
				res = list[i];
			}
		}
	}
	return res;
}
