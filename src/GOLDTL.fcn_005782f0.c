// FUNCTION: GOLD 0x0056fe50
// FUNCTION: GOLDTL 0x5782f0

void __cdecl fcn_004c5480(int, int, float);

void __cdecl fcn_005782f0(char* o, int v)
{
	float f;
	float x;
	float s;
	float t;
	int n;

	if (o != 0) {
		f = (float) (v & 0xffff);
		if (f <= *(float*) (o + 0x20)) {
			fcn_004c5480(*(int*) (o + 4), 0x1c, *(float*) (o + 0x18) - *(float*) (o + 0x1c));
		} else {
			x = *(float*) (o + 0x18);
			s = *(float*) (o + 0x14);
			for (n = (int) (f - *(float*) (o + 0x20)); n > 0; n--) {
				t = s / x;
				x = x - s + t;
			}
			fcn_004c5480(*(int*) (o + 4), 0x1c, x - *(float*) (o + 0x1c));
		}
	}
}
