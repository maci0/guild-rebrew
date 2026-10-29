/* Compiler literal pool used by this body. */
extern float flt_lit1;
extern double dbl_lit2;
extern double dbl_lit1;
extern float flt_lit1_42;
extern float flt_lit1_252;
extern float flt_lit1_1;

int __cdecl fcn_00507b00(int a);
float __cdecl fcn_00507f10(char* p, int a);
int __cdecl fcn_004fbd20(int a);
void __cdecl fcn_004f4830(int a, void* out);

/* ADDRESS: GOLDTL 0x004918a0 */
int __cdecl fcn_004918a0(char* p, int unused, int* out)
{
	float a;
	float b;
	float c;
	float v;
	int m;
	char tmp[0x24];

	(void) unused;
	fcn_00507b00((int) (unsigned char) p[0x164]);
	v = ((float) fcn_00507f10(p, 3)
		- ((float) (fcn_004fbd20(3) & 0xff) + flt_lit1) * flt_lit1_252)
		* flt_lit1_42 * flt_lit1_1;
	a = (float) ((*(float*) (p + 0xf4) - dbl_lit2) * *(float*) (p + 0xfc));
	c = (float) ((*(float*) (p + 0x100) - dbl_lit2) * *(float*) (p + 0x108));
	b = (float) ((*(float*) (p + 0x10c) - dbl_lit2) * *(float*) (p + 0x114));
	fcn_004f4830(0x14, tmp);
	m = *(int*) (tmp + 0x18);
	if (v < flt_lit1 && m == 0) {
		if (b > a) {
			*out = 1;
			return 1;
		}
		return 0;
	}
	if (v > dbl_lit1 && m == 1) {
		if (c > a) {
			*out = 0;
			return m;
		}
	}
	return 0;
}
