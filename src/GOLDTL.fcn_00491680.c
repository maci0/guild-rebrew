typedef struct Stat {
	int v[9];
} Stat;

int __cdecl gm_MapEntityStatRange(int raw_idx);
void __cdecl fcn_004f4830(int idx, Stat* st);

/* ADDRESS: GOLDTL 0x00491680 */
int __cdecl fcn_00491680(char* e, int unused, int* out)
{
	Stat st;
	float w;
	float y;
	float z;
	int job;

	job = gm_MapEntityStatRange(*(unsigned char*) (e + 0x164));
	w = *(float*) (e + 0x100) - 2.0;
	y = (*(float*) (e + 0xf4) - 2.0) * *(float*) (e + 0xfc);
	z = (*(float*) (e + 0x10c) - 2.0) * *(float*) (e + 0x124);
	if (job == 5 || job == 6) {
		w = w * 1.5f;
	} else if (job == 7) {
		w = w * 0.9f;
	}
	fcn_004f4830(0x12, &st);
	if (w < 6.2831855f && st.v[6] == 0) {
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
