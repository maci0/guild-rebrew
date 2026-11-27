/* Compiler literal pool used by this body. */







int __cdecl gm_MapEntityStatRange(int a);
float __cdecl gm_GetEntitySkill(char* p, int a);
unsigned char __cdecl fcn_004f97a0(int a);
void __cdecl gm_GetLawEntry(int a, void* out);

/* ADDRESS: GOLDTL 0x004918a0 */
int __cdecl ai_EvaluateLaw0x14(char* entity, int unused, int* out)
{
	float fA;
	float fB;
	float fC;
	float score;
	float partial;
	int curVal;
	char info[0x24];

	(void) unused;
	gm_MapEntityStatRange((int) (unsigned char) entity[0x164]);
	partial = ((float) gm_GetEntitySkill(entity, 3)
		- ((float) fcn_004f97a0(3) + 1.0f) * 0.003968254197388887f)
		* 0.02380952425301075f;
	fA = (float) ((*(float*) (entity + 0xf4) - 2.0) * *(float*) (entity + 0xfc));
	fC = (float) ((*(float*) (entity + 0x100) - 2.0) * *(float*) (entity + 0x108));
	fB = (float) ((*(float*) (entity + 0x10c) - 2.0) * *(float*) (entity + 0x114));
	score = (float) (partial * 1.1f);
	gm_GetLawEntry(0x14, info);
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
