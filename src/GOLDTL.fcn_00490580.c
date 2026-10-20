unsigned char __cdecl fcn_004fbd20(int a);
int __cdecl fcn_004f5dd0(int a);
int __cdecl fcn_004f4830(int idx, void* dst);
char* __cdecl fcn_004e90d0(int a);
int __cdecl fcn_00507b00(int a);
float __cdecl fcn_00507f10(char* entity, int index);
float __cdecl fcn_0050f980(int a, int b, int c);

/* ADDRESS: GOLDTL 0x00490580 */
int __cdecl fcn_00490580(char* e, int a1, int* a2)
{
	float y;
	int n;
	float z;
	float w;
	int info[9];
	float m;
	int job;
	char* p;
	float r;

	job = fcn_00507b00(*(unsigned char*) (e + 0x164));
	m = (fcn_00507f10(e, 4) - (fcn_004fbd20(4) + 1.0f) * 0.003968254f)
		* 0.023809524f;
	y = (float) ((*(float*) (e + 0xf4) - 2.0) * *(float*) (e + 0xfc));
	w = (float) ((*(float*) (e + 0x100) - 2.0) * *(float*) (e + 0x108));
	z = (float) ((*(float*) (e + 0x10c) - 2.0) * *(float*) (e + 0x114));
	n = fcn_004f5dd0(*(int*) (e + 4));
	if (job == 0xb || job == 0xc)
		m = m + 7.0f;
	else if (job == 9 || job == 1 || job == 3 || job == 2)
		m = m + 3.0f;
	else
		m = m + 5.0f;
	m = (float) n / ((float) (0x28 - (int) *(unsigned short*) (e + 0xa)) * 0.1f + m);
	fcn_004f4830(1, info);
	if (m > 1.0f && info[6] == 0) {
		if (m > 1.4f || z > y) {
			*a2 = 1;
			return 1;
		}
		return 0;
	}
	if (m < 0.5f && info[6] == 1
		&& (w > y || *(unsigned char*) (e + 0x166) == 0x11)) {
		*a2 = 0;
		return 1;
	}
	p = fcn_004e90d0(0x11);
	if (p != 0) {
		r = fcn_0050f980(*(unsigned short*) p, *(unsigned short*) e, 1);
		if (info[6] == 1) {
			if (r > 0.75f) {
				*a2 = 0;
				return 1;
			}
		} else if (info[6] == 0 && r < 0.25f) {
			*a2 = 1;
			return 1;
		}
	}
	return 0;
}
