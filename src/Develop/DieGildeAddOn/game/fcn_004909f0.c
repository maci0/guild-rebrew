/* Compiler literal pool used by this body. */
/* ADDRESS: GOLDTL 0x6628a0 */
extern float flt_lit1;
/* ADDRESS: GOLDTL 0x662a48 */
extern double dbl_lit2;
/* ADDRESS: GOLDTL 0x6629c8 */
extern double dbl_lit1;
/* ADDRESS: GOLDTL 0x664168 */
extern float flt_lit1_42;
/* ADDRESS: GOLDTL 0x66416c */
extern float flt_lit1_252;
/* ADDRESS: GOLDTL 0x664174 */
extern float flt_lit1_1;

int __cdecl fcn_00507b00(int a);
float __cdecl gm_GetEntitySkill(char* p, int a);
int __cdecl fcn_004fbd20(int a);
void __cdecl fcn_004f4830(int a, void* out);

/* ADDRESS: GOLDTL 0x004909f0 */
int __cdecl fcn_004909f0(char* p, int unused, int* out)
{
	float a;
	float b;
	float c;
	float v;
	int m;
	char tmp[0x24];

	(void) unused;
	fcn_00507b00((int) (unsigned char) p[0x164]);
	v = ((float) gm_GetEntitySkill(p, 3)
		- ((float) (fcn_004fbd20(3) & 0xff) + flt_lit1) * flt_lit1_252)
		* flt_lit1_42 * flt_lit1_1;
	a = (float) ((*(float*) (p + 0xf4) - dbl_lit2) * *(float*) (p + 0xfc));
	c = (float) ((*(float*) (p + 0x100) - dbl_lit2) * *(float*) (p + 0x108));
	b = (float) ((*(float*) (p + 0x10c) - dbl_lit2) * *(float*) (p + 0x114));
	fcn_004f4830(4, tmp);
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
