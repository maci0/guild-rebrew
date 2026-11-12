/* Compiler literal pool used by this body. */







int __cdecl gm_MapEntityStatRange(int a);
float __cdecl gm_GetEntitySkill(char* p, int a);
unsigned char __cdecl fcn_004f97a0(int a);
void __cdecl fcn_004f4830(int a, void* out);

/* ADDRESS: GOLDTL 0x004918a0 */
int __cdecl fcn_004918a0(char* p, int unused, int* out)
{
	float a;
	float b;
	float c;
	float v;
	float partial;
	int m;
	char tmp[0x24];

	(void) unused;
	gm_MapEntityStatRange((int) (unsigned char) p[0x164]);
	partial = ((float) gm_GetEntitySkill(p, 3)
		- ((float) fcn_004f97a0(3) + 1.0f) * 0.003968254197388887f)
		* 0.02380952425301075f;
	a = (float) ((*(float*) (p + 0xf4) - 2.0) * *(float*) (p + 0xfc));
	c = (float) ((*(float*) (p + 0x100) - 2.0) * *(float*) (p + 0x108));
	b = (float) ((*(float*) (p + 0x10c) - 2.0) * *(float*) (p + 0x114));
	v = (float) (partial * 1.1f);
	fcn_004f4830(0x14, tmp);
	m = *(int*) (tmp + 0x18);
	if (v < 1.0f && m == 0) {
		if (b > a) {
			*out = 1;
			return 1;
		}
		return 0;
	}
	if (v > 1.0 && m == 1) {
		if (c > a) {
			*out = 0;
			return m;
		}
	}
	return 0;
}
