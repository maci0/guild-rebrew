


void __cdecl cm_RequestChangeFloat(int, int, float);

/* ADDRESS: GOLDDE 0x0055e1c0 */
void __cdecl gm_IncreaseEntityStat(char* entity, int steps)
{
	float f;
	float x;
	float s;
	float t;
	int n;

	if (entity != 0) {
		f = (float) (steps & 0xffff);
		if (f <= *(float*) (entity + 0x20)) {
			cm_RequestChangeFloat(*(int*) (entity + 4), 0x1c, *(float*) (entity + 0x18) - *(float*) (entity + 0x1c));
		} else {
			x = *(float*) (entity + 0x18);
			s = *(float*) (entity + 0x14);
			for (n = (int) (f - *(float*) (entity + 0x20)); n > 0; n--) {
				t = s / x;
				x = x - s + t;
			}
			cm_RequestChangeFloat(*(int*) (entity + 4), 0x1c, x - *(float*) (entity + 0x1c));
		}
	}
}
