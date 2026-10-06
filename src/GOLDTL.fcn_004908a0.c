// FUNCTION: GOLDTL 0x4908a0

int __cdecl fcn_00507b00(int job);
float __cdecl fcn_00507f10(char* e, int k);
unsigned char __cdecl fcn_004f97a0(int a);
int __cdecl fcn_004f4830(int idx, void* dst);

int __cdecl fcn_004908a0(char* e, int unused, int* out)
{
	int info[9];
	float m;
	float t;
	float y;
	float z;
	float w;
	int job;

	job = fcn_00507b00(*(unsigned char*) (e + 0x164));
	t = fcn_00507f10(e, 4);
	m = (t - (fcn_004f97a0(4) + 1.0f) * 0.003968254f) * 0.023809524f;
	y = (*(float*) (e + 0xf4) - 2.0) * *(float*) (e + 0xfc);
	w = (*(float*) (e + 0x100) - 2.0) * *(float*) (e + 0x108);
	z = (*(float*) (e + 0x10c) - 2.0) * *(float*) (e + 0x114);
	if (job == 7) {
		m = m * 1.1f;
	} else if (job == 11 || job == 12) {
		m = m * 0.9f;
	}
	fcn_004f4830(3, info);
	if (m < 1.0f && info[6] == 0) {
		if (!(z > y)) {
			return 0;
		}
		*out = 1;
		return 1;
	}
	if (!(m > 1.0) || info[6] != 1 || !(w > y)) {
		return 0;
	}
	*out = 0;
	return info[6];
}
