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
void __cdecl gm_GetLawEntry(int a, void* out);

/* ADDRESS: GOLDTL 0x004909f0 */
/* ADDRESS: GOLDDE 0x0047f8a0 */
int __cdecl ai_EvaluateLaw0x04(char* entity, int unused, int* out)
{
	float fA;
	float fB;
	float fC;
	float score;
	int curVal;
	char info[0x24];

	(void) unused;
	fcn_00507b00((int) (unsigned char) entity[0x164]);
	score = ((float) gm_GetEntitySkill(entity, 3)
		- ((float) (fcn_004fbd20(3) & 0xff) + 1.0f) * 0.00396825420f)
		* 0.0238095243f;
	fA = (float) ((*(float*) (entity + 0xf4) - 2.0) * *(float*) (entity + 0xfc));
	fC = (float) ((*(float*) (entity + 0x100) - 2.0) * *(float*) (entity + 0x108));
	fB = (float) ((*(float*) (entity + 0x10c) - 2.0) * *(float*) (entity + 0x114));
	score = score * 1.1f;
	gm_GetLawEntry(4, info);
	curVal = *(int*) (info + 0x18);
	if (score < 1.0f && curVal == 0) {
		if (fB > fA) {
			*out = 1;
			return 1;
		}
		return 0;
	}
	if (score > 1.0 && curVal == 1) {
		if (fC > fA) {
			*out = 0;
			return curVal;
		}
	}
	return 0;
}
