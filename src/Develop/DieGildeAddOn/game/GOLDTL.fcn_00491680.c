typedef struct Stat {
	int v[9];
} Stat;

int __cdecl gm_MapEntityStatRange(int raw_idx);
void __cdecl fcn_004f4830(int idx, Stat* st);

/* ADDRESS: GOLDTL 0x00491680 */
int __cdecl ai_EvaluateLaw0x12(char* entity, int unused, int* out)
{
	Stat st;
	float w;
	float y;
	float z;
	int job;

	job = gm_MapEntityStatRange(*(unsigned char*) (entity + 0x164));
	w = (float) (*(float*) (entity + 0x100) - 2.0);
	y = (*(float*) (entity + 0xf4) - 2.0) * *(float*) (entity + 0xfc);
	z = (*(float*) (entity + 0x10c) - 2.0) * *(float*) (entity + 0x114);
	if (job == 5 || job == 6) {
		w = w * 1.5f;
	} else if (job == 7) {
		w = w * 0.9f;
	}
	fcn_004f4830(0x12, &st);
	if (w < 0.5f && st.v[6] == 0) {
		if (!(y > z)) {
			return 0;
		}
		*out = 1;
		return 1;
	}
	if (!(w > 0.5) || st.v[6] != 1 || !(z > y)) {
		return 0;
	}
	*out = 0;
	return st.v[6];
}
